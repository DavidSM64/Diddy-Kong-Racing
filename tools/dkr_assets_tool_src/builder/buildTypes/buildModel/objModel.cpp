#include "objModel.h"

#include <sstream>
#include "helpers/fileHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"

#include "libs/TriangulatePolygon.hpp"

using namespace DkrAssetsTool;

typedef struct ObjFaceComponent {
    int vertexIndex = -1;
    int uvIndex = -1;
    int normalIndex = -1; // Not used in DKR, since normals are generated automatically.
} ObjFaceComponent;

typedef struct ObjTriangle {
    ObjFaceComponent a;
    ObjFaceComponent b;
    ObjFaceComponent c;
    
    ObjTriangle(ObjFaceComponent newA, ObjFaceComponent newB, ObjFaceComponent newC)
    : a(newA), b(newB), c(newC) {}
} ObjTriangle;

ObjFaceComponent parse_face_component(std::string component) {
    std::vector<std::string> faceComponents;
    StringHelper::split(component, '/', faceComponents);
    ObjFaceComponent out;
    
    out.vertexIndex = std::stoi(faceComponents[0]) - 1;
    
    if((faceComponents.size() > 1) && (!faceComponents[1].empty())) {
        out.uvIndex = std::stoi(faceComponents[1]) - 1;
    }
    
    if((faceComponents.size() > 2) && (!faceComponents[2].empty())) {
        out.normalIndex = std::stoi(faceComponents[2]) - 1;
    }
    
    return out;
}

std::vector<ObjTriangle> triangulate_polygon(const std::vector<std::string> &components, const std::vector<BuildModelVertex> &vertices) {
    size_t numberOfOutTriangles = components.size() - 3;
    
    std::vector<ObjTriangle> out;
    
    if(numberOfOutTriangles == 1) {
        // No need to triangulate.
        out.push_back({
            parse_face_component(components[1]),
            parse_face_component(components[2]),
            parse_face_component(components[3])
        });
    } else {
        std::vector<ObjFaceComponent> faceComponents(components.size() - 1);
        std::vector<triangulate::Point> polygonPoints;
        
        for(size_t i = 1; i < components.size(); i++) {
            faceComponents[i - 1] = parse_face_component(components[i]);
            const BuildModelVertex &vertex = vertices.at(faceComponents[i - 1].vertexIndex);
            Vec3f vertexPos = vertex.position();
            polygonPoints.emplace_back(vertexPos.x, vertexPos.y, vertexPos.z);
        }
        
        const auto triangles = triangulate::triangulate(polygonPoints);
        
        for(auto &tri : triangles) {
            int index0 = DataHelper::vector_index_of(polygonPoints, tri.p0);
            int index1 = DataHelper::vector_index_of(polygonPoints, tri.p1);
            int index2 = DataHelper::vector_index_of(polygonPoints, tri.p2);
            
            DebugHelper::assert_(index0 >= 0, "(triangulate_polygon) Invalid point 0");
            DebugHelper::assert_(index1 >= 0, "(triangulate_polygon) Invalid point 1");
            DebugHelper::assert_(index2 >= 0, "(triangulate_polygon) Invalid point 2");
            
            out.emplace_back(faceComponents[index0], faceComponents[index1], faceComponents[index2]);
        }
    }
    
    return out;
}

ObjBuildModel::ObjBuildModel(fs::path filepath) {
    std::string objText = FileHelper::read_text_file(filepath);
    
    std::vector<std::string> lines;
    StringHelper::split_and_trim(objText, '\n', lines);
    
    std::vector<BuildModelVertex> vertices;
    std::vector<Vec2f> uvs;
    
    std::string currentMaterial = "";
    
    for(std::string &line : lines) {
        if(line[0] == '#' || line.empty()) {
            // Skip this line if it is empty or a comment.
            continue;
        }
        std::vector<std::string> components;
        StringHelper::split(line, ' ', components);
        if(components[0] == "v") {
            // Parse position coordinates.
            double x = std::stod(components[1]);
            double y = std::stod(components[2]);
            double z = std::stod(components[3]);
           
           if(components.size() < 6) {
                // Add the new vertex
                vertices.emplace_back(Vec3f(x, y, z));
                continue;
           }
           
           double r = std::stod(components[4]);
           double g = std::stod(components[5]);
           double b = std::stod(components[6]);
           vertices.emplace_back(Vec3f(x, y, z), Vec4f(r, g, b, 1.0f));
           continue;
        }
        if(components[0] == "vn") {
            // User-generated normals are not used in DKR.
            continue;
        }
        if(components[0] == "vt") {
            double u = std::stod(components[1]);
            double v = std::stod(components[2]);
            
            uvs.emplace_back(Vec2f(u, v));
            continue;
        }
        if(components[0] == "f") {
            std::vector<ObjTriangle> tris = triangulate_polygon(components, vertices);
            
            for(ObjTriangle &tri : tris) {
                BuildModelVertex &vertexA = vertices[tri.a.vertexIndex];
                BuildModelVertex &vertexB = vertices[tri.b.vertexIndex];
                BuildModelVertex &vertexC = vertices[tri.c.vertexIndex];
                if(currentMaterial.empty() || (tri.a.uvIndex == -1)) {
                    // Add triangle without UV coordinates.
                    _add_new_triangle_to_current_block(vertexA, vertexB, vertexC);
                } else {
                    Vec2f uv0 = _get_adjusted_uv(uvs[tri.a.uvIndex], currentMaterial);
                    Vec2f uv1 = _get_adjusted_uv(uvs[tri.b.uvIndex], currentMaterial);
                    Vec2f uv2 = _get_adjusted_uv(uvs[tri.c.uvIndex], currentMaterial);
                    
                    // Add the new triangle with UV coordinates.
                    _add_new_triangle_to_current_block(vertexA, vertexB, vertexC, uv0, uv1, uv2);
                }
            }
            continue;
        }
        if(components[0] == "usemtl") {
            currentMaterial = components[1];
            _set_material(currentMaterial);
            continue;
        }
        if(components[0] == "o") {
            continue;
        }
        if(components[0] == "mtllib") {
            fs::path mtlFilepath = StringHelper::join(components, " ", 1);
            auto tryGetFilepath = FileHelper::determine_full_filepath(mtlFilepath, filepath.parent_path());
            if(!tryGetFilepath.has_value()) {
                DebugHelper::error("Could not find the .mtl file: ", mtlFilepath);
            }
            _parse_mtllib(tryGetFilepath.value());
            continue;
        }
    }
}

Vec2f ObjBuildModel::_get_adjusted_uv(Vec2f uv, std::string materialId) {
    auto tryGetMaterial = _try_get_material(materialId);
    DebugHelper::assert_(tryGetMaterial.has_value(),
        "(ObjBuildModel::_get_adjusted_uv) Failed parsing UV coordinates. Could not get the material \"", materialId, "\"");
    
    BuildModelMaterial &material = tryGetMaterial.value();
    
    int texWidth, texHeight;
    material.get_texture_width_and_height(texWidth, texHeight);
    
    if(texWidth == 0 || texHeight == 0) {
        DebugHelper::warn("Could not process UV! width = ", texWidth, ", height = ", texHeight);
        return uv;
    }
    
    uv.u *= (texWidth * 32.0);
    uv.v *= (texHeight * 32.0);
            
    return uv;
}

void ObjBuildModel::_parse_mtllib(fs::path pathToLib) {
    std::string mtlText = FileHelper::read_text_file(pathToLib);
    
    std::vector<std::string> lines;
    StringHelper::split_and_trim(mtlText, '\n', lines);
    
    std::string currentMaterial = "";
    fs::path currentTexture = "";
    
    for(std::string &line : lines) {
        if(line[0] == '#' || line.empty()) {
            // Skip this line if it is empty or a comment.
            continue;
        }
        std::vector<std::string> components;
        StringHelper::split(line, ' ', components);
        
        if(components[0] == "newmtl") {
            if(!currentMaterial.empty()) {
                _add_material(currentMaterial, currentTexture);
            }
            currentMaterial = components[1];
            continue;
        }
        if(components[0] == "map_Kd") {
            fs::path texturePath = StringHelper::join(components, " ", 1);
            auto tryGetFilepath = FileHelper::determine_full_filepath(texturePath, pathToLib.parent_path());
            if(!tryGetFilepath.has_value()) {
                DebugHelper::error("Could not find the texture image: ", texturePath);
            }
            currentTexture = tryGetFilepath.value();
            continue;
        }
    }
    
    if(!currentMaterial.empty()) {
        _add_material(currentMaterial, currentTexture);
    }
}
