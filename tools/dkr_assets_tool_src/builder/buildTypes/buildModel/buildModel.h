#pragma once

#include <optional>
#include <vector>
#include <map>

#include "builder/buildInfo.h"

#include "helpers/fileHelper.h"
#include "fileTypes/batch.hpp"

#include "buildModelBlock.h"
#include "buildModelMaterial.h"

namespace DkrAssetsTool {

// Generic version of ObjBuildModel/GltfBuildModel
class BuildModel {
public:
    void generate_object_model(BuildInfo &info);
    
protected:
    std::optional<std::string> _currentMaterialId = std::nullopt;
    std::vector<BuildModelBlock> _blocks;
    
    std::vector<BuildModelMaterial> _materials;
    std::map<std::string, int> _materialIds;
    
    void _add_new_triangle_to_current_block(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC,
        Vec2f uv0, Vec2f uv1, Vec2f uv2);
    void _add_new_triangle_to_current_block(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC);
    void _new_block();
    
    void _add_material(std::string id, fs::path texturePath="");
    void _set_material(std::string id);
    
    std::optional<std::reference_wrapper<BuildModelMaterial>> _try_get_material(std::string id);
    
    size_t _total_number_of_triangles();
    size_t _total_number_of_vertices();
    size_t _total_number_of_textures();
    size_t _total_number_of_batches();
    size_t _total_number_of_batches_to_allocate();
};

}