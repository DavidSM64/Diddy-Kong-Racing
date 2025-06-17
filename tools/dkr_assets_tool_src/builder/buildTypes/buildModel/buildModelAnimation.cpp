#include "buildModelAnimation.h"

#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/gltf/gltfHelper.h"

#include <algorithm>

using namespace DkrAssetsTool;

/***************************************************************************************************************/

AnimWeights BuildModelAnimationInputs::get_weights_at_time(float time) {
    if(time < 0) {
        time = 0;
    }
    
    if(!weights.has_value()) {
        return {};
    }
    
    std::map<float, AnimWeights> &inputWeights = weights.value();
    
    if(inputWeights.find(time) != inputWeights.end()) {
        // No need to interpolate!
        return inputWeights.at(time);
    }
    
    auto upperBound = inputWeights.upper_bound(time);
    auto lowerBound = std::prev(upperBound);
    
    float lowerTime = lowerBound->first;
    float upperTime = upperBound->first;
    
    DebugHelper::info(time, " is between ", lowerTime, " and ", upperTime);
    
    // Should handle the edgecases of time being outside timeline range.
    if(lowerTime == upperTime) {
        return upperBound->second;
    }
    
    AnimWeights &lowerWeights = lowerBound->second;
    AnimWeights &upperWeights = upperBound->second;
    
    // Percentage of interpolation.
    float t = (time - lowerTime) / (upperTime - lowerTime);
    
    AnimWeights out(lowerWeights.size());
    
    for(size_t i = 0; i < lowerWeights.size(); i++) {
        // Linear interpolation of weights.
        out[i] = lowerWeights[i] + t * (upperWeights[i] - lowerWeights[i]);
    }
    
    return out;
}

AnimTranslations BuildModelAnimationInputs::get_translations_at_time(float time) {
    return {};
}

AnimRotations BuildModelAnimationInputs::get_rotations_at_time(float time) {
    return {};
}

AnimScales BuildModelAnimationInputs::get_scales_at_time(float time) {
    return {};
}

/***************************************************************************************************************/

BuildModelAnimation::BuildModelAnimation() {
}

BuildModelAnimation::BuildModelAnimation(GltfFile &gltf, tinygltf::Animation &animation) {
    for(size_t i = 0; i < animation.channels.size(); i++) {
        tinygltf::AnimationChannel &channel = animation.channels[i];
        
        if(channel.sampler < 0) {
            continue;
        }
        
        tinygltf::AnimationSampler &sampler = animation.samplers[channel.sampler];
        
        if(sampler.interpolation != "LINEAR") {
            DebugHelper::warn(sampler.interpolation + " is currently not supported. Will use LINEAR instead.");
        }
        
        // I believe animation inputs are always floats? Couldn't find anything 100% definitive in the spec.
        std::vector<float> inputTimes = GltfHelper::get_data_from_accessor<float>(gltf, sampler.input);
        size_t numberOfInputs = inputTimes.size();
        
        if(channel.target_path == "weights") { 
            // morph targets
            auto tryGetWeights = GltfHelper::get_weights_from_accessor(gltf, sampler.output);
            DebugHelper::assert_(tryGetWeights.has_value(),
                "(BuildModelAnimation::BuildModelAnimation) Failed to get weights from gltf accessor ", sampler.output);
            std::vector<float> &weights = tryGetWeights.value();
            size_t numberOfWeights = weights.size() / numberOfInputs;
            
            for(size_t j = 0; j < numberOfInputs; j++) {
                add_weights_input(inputTimes[j], weights, j * numberOfWeights, numberOfWeights);
            }
        } else if(channel.target_path == "translation") {
            DebugHelper::warn("(BuildModelAnimation::BuildModelAnimation) TODO: Support translation channel.path");
        } else if(channel.target_path == "rotation") { 
            DebugHelper::warn("(BuildModelAnimation::BuildModelAnimation) TODO: Support rotation channel.path");
        } else if(channel.target_path == "scale") {
            DebugHelper::warn("(BuildModelAnimation::BuildModelAnimation) TODO: Support scale channel.path");
        }
    }
}

void BuildModelAnimation::add_weights_input(float time, std::vector<float> &values, std::optional<size_t> offset, std::optional<size_t> length) {
    if(offset == std::nullopt) {
        offset = 0;
    }
    if(length == std::nullopt) {
        length = values.size() - offset.value();
    }
    
    if(_inputs.weights == std::nullopt) {
        _inputs.weights = std::map<float, std::vector<float>>();
    }
    
    _inputs.weights.value()[time] = std::vector<float>(values.begin() + offset.value(), values.begin() + offset.value() + length.value());
    
    if(time > _maxTime) {
        _maxTime = time;
    }
}

std::vector<float> BuildModelAnimation::get_timeline() {
    std::vector<float> timeline;
    int numberOfSections = 0;
    
    if(_inputs.weights.has_value()) {
        for(auto &pair : _inputs.weights.value()) {
            timeline.emplace_back(pair.first);
        }
        numberOfSections++;
    }
    
    if(_inputs.translations.has_value()) {
        for(auto &pair : _inputs.translations.value()) {
            if(DataHelper::vector_has(timeline, pair.first)) {
                continue;
            }
            timeline.emplace_back(pair.first);
        }
        numberOfSections++;
    }
    
    if(_inputs.rotations.has_value()) {
        for(auto &pair : _inputs.rotations.value()) {
            if(DataHelper::vector_has(timeline, pair.first)) {
                continue;
            }
            timeline.emplace_back(pair.first);
        }
        numberOfSections++;
    }
    
    if(_inputs.scales.has_value()) {
        for(auto &pair : _inputs.scales.value()) {
            if(DataHelper::vector_has(timeline, pair.first)) {
                continue;
            }
            timeline.emplace_back(pair.first);
        }
        numberOfSections++;
    }
    
    if(numberOfSections > 1) {
        std::sort(timeline.begin(), timeline.end());
    }
    
    return timeline;
}

float BuildModelAnimation::get_max_time() const {
    return _maxTime;
}

// Returns weights/translations/rotations/scales for a specific time input. Values will be set to std::nullopt if there is no data.
// Values will be interpolated if there is data, but the time input was not specified.
void BuildModelAnimation::get_inputs_for_time(float time, std::optional<AnimWeights> &outWeights, std::optional<AnimTranslations> &outTranslations, 
  std::optional<AnimRotations> &outRotations, std::optional<AnimScales> &outScales) {
    // Set new data
    if(_inputs.weights.has_value()) {
        outWeights = _inputs.get_weights_at_time(time);
    } else {
        outWeights = std::nullopt;
    }
    if(_inputs.translations.has_value()) {
        outTranslations = _inputs.get_translations_at_time(time);
    } else {
        outTranslations = std::nullopt;
    }
    if(_inputs.rotations.has_value()) {
        outRotations = _inputs.get_rotations_at_time(time);
    } else {
        outRotations = std::nullopt;
    }
    if(_inputs.scales.has_value()) {
        outScales = _inputs.get_scales_at_time(time);
    } else {
        outScales = std::nullopt;
    }
}

bool BuildModelAnimation::only_has_morph_targets() const {
    return _inputs.weights.has_value() && !_inputs.translations.has_value() && 
          !_inputs.rotations.has_value() && !_inputs.scales.has_value();
}
