#pragma once

#include <vector>
#include <optional>

#include "helpers/mathHelper.h"
#include "fileTypes/types.hpp"
#include "fileTypes/vertex.hpp"

namespace DkrAssetsTool {

// NOTE: Normals are not set in DKR, they are generated automatically in-game.
class BuildModelVertex {
public:
    BuildModelVertex(); // Null Vertex (Blank, All zeroes)
    BuildModelVertex(const Vec3f position); // position only (Color set to white, UV is zero)
    BuildModelVertex(const Vec3f position, const Vec4f color); // position & color (UV is zero)
    
    ~BuildModelVertex();
    
    bool operator==(const BuildModelVertex& other) const;
    bool operator!=(const BuildModelVertex& other) const;
    friend std::ostream& operator<<(std::ostream& os, const BuildModelVertex& vertex);

    // Read-Only copies
    Vec3f position() const;
    Vec4f color() const;
    
    bool is_color_white() const;
    
    void write_to(DkrVertex *outVertex, float modelScale);
    
    void add_morph_target(Vec3f newTarget);
    bool has_targets() const;
    bool is_animated() const; // Different from has_targets(), because it is possible that the targets don't move.
    
    Vec3f animated_position(const std::vector<float> &weights) const;
    
private:
    Vec3f _position;
    Vec4f _color;
    
    std::optional<std::vector<Vec3f>> _targetPositions = std::nullopt;
};

}
