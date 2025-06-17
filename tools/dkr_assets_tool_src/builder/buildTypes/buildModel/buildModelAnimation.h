#pragma once

#include <cstdint>
#include <vector>
#include <optional>

#include "helpers/mathHelper.h"
#include "helpers/gltf/gltfFile.h"

#include "libs/bytes_view.hpp"

namespace DkrAssetsTool {
    
typedef std::vector<float> AnimWeights;

// Key: node index, Value: value for property
typedef std::map<int, Vec3f> AnimTranslations;
typedef std::map<int, Vec4f> AnimRotations;
typedef std::map<int, Vec3f> AnimScales;

struct BuildModelAnimationInputs {
    // Key: time in seconds, value: array of weights for that moment in time. (Morph target animation only)
    std::optional<std::map<float, AnimWeights>> weights = std::nullopt;
    
    // Key: time in seconds, value: array of translations for that moment in time.
    std::optional<std::map<float, AnimTranslations>> translations = std::nullopt;
    // Key: time in seconds, value: array of rotation (Quaternions) for that moment in time.
    std::optional<std::map<float, AnimRotations>> rotations = std::nullopt;
    // Key: time in seconds, value: array of scale values for that moment in time.
    std::optional<std::map<float, AnimScales>> scales = std::nullopt;
    
    AnimWeights get_weights_at_time(float time);
    AnimTranslations get_translations_at_time(float time);
    AnimRotations get_rotations_at_time(float time);
    AnimScales get_scales_at_time(float time);
};

class BuildModelAnimation {
public:
    BuildModelAnimation();
    BuildModelAnimation(GltfFile &gltf, tinygltf::Animation &animation);
    
    void add_weights_input(float time, std::vector<float> &values, std::optional<size_t> offset=std::nullopt, std::optional<size_t> length=std::nullopt);
    
    std::vector<float> get_timeline();
    float get_max_time() const;
    
    // Returns weights/translations/rotations/scales for a specific time input. Values will be set to std::nullopt if there is no data.
    // Values will be interpolated if there is data, but the time input was not specified.
    void get_inputs_for_time(float time, std::optional<AnimWeights> &outWeights, std::optional<AnimTranslations> &outTranslations, 
        std::optional<AnimRotations> &outRotations, std::optional<AnimScales> &outScales);
    
    // The logic is a bit simpler if there is only morph target animation.
    bool only_has_morph_targets() const;
    
private:
    BuildModelAnimationInputs _inputs;
    
    float _maxTime = 0.0f;
};

}
