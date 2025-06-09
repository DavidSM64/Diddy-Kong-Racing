#pragma once
#include <unordered_map>

#include "helpers/fileHelper.h"

#include "helpers/gltf/gltfFile.h"
#include "helpers/gltf/gltfHelper.h"

#include "buildModel.h"
#include "buildModelAnimation.h"

namespace DkrAssetsTool {

class GltfBuildModel : public BuildModel {
public:
    GltfBuildModel(GltfFile &gltf, CContext &cContext, bool isObjectModel = false);
private:
    void _process_node_base(GltfFile &gltf, int nodeIndex, const Mat4x4f &parentMatrix);
    void _process_mesh_base(GltfFile &gltf, int meshIndex, const Mat4x4f &nodeMatrix);
    
    std::vector<BuildModelVertex> _make_vertices_from_primitive_data(std::optional<std::vector<float>> &positions, 
      std::optional<std::vector<uint8_t>> &colors, std::optional<std::vector<float>> &morphTargets, 
      const Mat4x4f &nodeMatrix);
    int _get_image_index_for_material(GltfFile &gltf, int materialIndex);
    int _get_image_sampler_index_for_material(GltfFile &gltf, int materialIndex);
    std::vector<Vec2f> _adjust_uvs(GltfFile &gltf, int materialIndex, std::optional<std::vector<float>> &uvs);
    
    uint32_t _get_render_flags_from_extras(tinygltf::Value& extras, std::string jsonPointer, CContext &cContext);
    
    bool _isObjectModel = false;
    
    std::unordered_map<int, int> _imageIndexForMaterialCache;
    std::unordered_map<int, int> _imageSamplerIndexForMaterialCache;
    
    int _lastMaterialChecked = -1;
    
    std::unordered_map<int, std::string> _gltfMaterialIndexToId;
};

}
