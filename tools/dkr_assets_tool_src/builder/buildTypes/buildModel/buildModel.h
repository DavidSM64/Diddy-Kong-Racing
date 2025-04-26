#pragma once

#include <optional>
#include <vector>

#include "helpers/fileHelper.h"
#include "fileTypes/batch.hpp"

#include "buildModelBlock.h"

namespace DkrAssetsTool {

// Generic version of ObjBuildModel/GltfBuildModel
class BuildModel {
public:
    void generate_object_model(fs::path dstPath);
    
protected:
    std::optional<std::string> _currentMaterialId = std::nullopt;
    std::vector<BuildModelBlock> _blocks;
    
    void _add_new_triangle_to_current_block(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC,
        Vec2f uv0, Vec2f uv1, Vec2f uv2);
    void _add_new_triangle_to_current_block(const BuildModelVertex& vertA, const BuildModelVertex& vertB, const BuildModelVertex& vertC);
    void _new_block();
    
    size_t _total_number_of_triangles();
    size_t _total_number_of_vertices();
    size_t _total_number_of_textures();
    size_t _total_number_of_batches();
    size_t _total_number_of_batches_to_allocate();
};

}