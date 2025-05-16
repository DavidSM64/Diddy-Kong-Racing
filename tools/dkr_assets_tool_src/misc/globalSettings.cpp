#include "globalSettings.h"

#include <any> 
#include <iostream> 
#include <sstream> 
#include <typeindex> 
#include <unordered_map> 
#include <thread> 
#include <functional>
#include <mutex>

#include "helpers/debugHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"

#include "args.h"

using namespace DkrAssetsTool;

std::unordered_map<std::string, std::any> settingValues;

template <typename T>
T GlobalSettings::get_value(std::string key, T defaultValue) {
    auto it = settingValues.find(StringHelper::simplify(key));
    if (it != settingValues.end()) { 
        try { 
            return std::any_cast<T>(it->second); 
        } catch (const std::bad_any_cast&) { 
            return defaultValue; 
        } 
    } 
    return defaultValue;
}

template std::string GlobalSettings::get_value<std::string>(std::string key, std::string defaultValue);
template fs::path GlobalSettings::get_value<fs::path>(std::string key, fs::path defaultValue);
template int GlobalSettings::get_value<int>(std::string key, int defaultValue);
template bool GlobalSettings::get_value<bool>(std::string key, bool defaultValue);
template double GlobalSettings::get_value<double>(std::string key, double defaultValue);

template <typename T>
void GlobalSettings::set_value(std::string key, T value) {
    settingValues[StringHelper::simplify(key)] = value;
}

template void GlobalSettings::set_value<std::string>(std::string key, std::string value);
template void GlobalSettings::set_value<fs::path>(std::string key, fs::path value);
template void GlobalSettings::set_value<int>(std::string key, int value);
template void GlobalSettings::set_value<bool>(std::string key, bool value);
template void GlobalSettings::set_value<double>(std::string key, double value);

void GlobalSettings::parse_values_from_json_file(fs::path pathToJsonFile) {
    JsonFile settingsJson(pathToJsonFile);

    std::vector<std::string> allPointers = settingsJson.get_all_pointers();

    for (std::string& jsonPtr : allPointers) {
        std::any jsonPtrValue = settingsJson.get_any(jsonPtr);
        if (jsonPtrValue.has_value()) {
            settingValues[StringHelper::simplify(jsonPtr)] = jsonPtrValue;
        }
    }
}

static void print_any(std::stringstream& ss, const std::any& anyValue) {
    // This is more compact then doing a bunch of try-catch blocks for each cast.
    static const std::unordered_map<std::type_index, std::function<void(std::stringstream&, const std::any&)>> handlers = {
        { typeid(bool), [](std::stringstream& ss, const std::any& a) { ss << (std::any_cast<bool>(a) ? "true" : "false"); }},
        { typeid(int), [](std::stringstream& ss, const std::any& a) { ss << std::any_cast<int>(a); }},
        { typeid(double), [](std::stringstream& ss, const std::any& a) { ss << std::any_cast<double>(a); }},
        { typeid(std::string), [](std::stringstream& ss, const std::any& a) { ss << "\"" << std::any_cast<std::string>(a) << "\""; }},
    };

    auto it = handlers.find(anyValue.type());
    if (it != handlers.end()) {
        it->second(ss, anyValue);
    } else {
        DebugHelper::error("Bad std::any value! Unknown type to cast!");
    }
}

void GlobalSettings::print_all_values() {
    std::stringstream ss;

    ss << "------ Settings ------" << std::endl;
    for (auto& setting : settingValues) {
        if (!setting.second.has_value()) {
            continue;
        }
        ss << "\"" << setting.first << "\": ";
        print_any(ss, setting.second);
        ss << std::endl;
    }
    ss << "----------------------";

    DebugHelper::info(ss.str());
}

std::string GlobalSettings::get_dkr_version() {
    return Args::get_dkr_version();
}

std::mutex _findDecompRootMutex;
std::optional<fs::path> _cachedDecompRootResult = std::nullopt;

std::optional<fs::path> GlobalSettings::find_decomp_root() {
    // This code could possibly be called from multiple threads. A mutex is needed since I'm caching the result.
    _findDecompRootMutex.lock();

    // First we see if the result was already found before.
    if (_cachedDecompRootResult.has_value()) {
        _findDecompRootMutex.unlock();
        return _cachedDecompRootResult;
    }

    // Next see if `decomp_root` was defined in the settings before trying to find it automatically.
    fs::path rootFromSettings = get_value<std::string>("decomp_root", "");
    if (!rootFromSettings.empty() && FileHelper::path_exists(rootFromSettings)) {
        _findDecompRootMutex.unlock();
        return rootFromSettings;
    }

    // Lastly, we'll check the existance of some known files/folders to see if we can find it auto-magically.
    fs::path curDir = FileHelper::get_working_directory();

    const std::vector<fs::path> lookForPaths = {
        "src/", "baseroms/", "tools/", "Makefile"
    };

    while (!curDir.empty()) {
        if (FileHelper::does_folder_contain_paths(curDir, lookForPaths)) {
            _cachedDecompRootResult = curDir; // We found it! Cache it so we don't have to get it later.
            _findDecompRootMutex.unlock();
            return _cachedDecompRootResult; 
        }
        curDir = curDir.parent_path();
    }

    _findDecompRootMutex.unlock();
    return std::nullopt; // Could not find the decomp. :(
}

fs::path GlobalSettings::get_decomp_path(std::string key, fs::path defaultSubpath) {
    if(!defaultSubpath.empty()) {
        DebugHelper::assert_(defaultSubpath.generic_string()[0] != '/',
            "(GlobalSettings::get_decomp_path) HEY! defaultSubpath should not start with '/', it goes at the END.");
    }
    std::optional<fs::path> decompRoot = find_decomp_root();
    DebugHelper::assert_(decompRoot.has_value(), 
        "(GlobalSettings::get_decomp_path) Could not find the DKR decomp folder!");
    return decompRoot.value() / get_value<fs::path>(key, defaultSubpath);
}

fs::path GlobalSettings::get_decomp_path_to_output_assets(bool fallbackToVanillaPath) {
    std::optional<fs::path> decompPath = get_decomp_path("/assets_subpath", "assets/");
    DebugHelper::assert_(decompPath.has_value(), "(GlobalSettings::get_decomp_path_to_output_assets) Could not find the DKR decomp folder!");
    fs::path out = decompPath.value() / get_dkr_version();
    
    // Use vanilla directory if the output directory doesn't exist yet.
    if(!FileHelper::path_exists(out) && fallbackToVanillaPath) {
        return get_decomp_path_to_vanilla_assets();
    }
    
    return out;
}

fs::path GlobalSettings::get_decomp_path_to_vanilla_assets() {
    std::optional<fs::path> decompPath = get_decomp_path("/assets_subpath", "assets/");
    DebugHelper::assert_(decompPath.has_value(), "(GlobalSettings::get_decomp_path_to_output_assets) Could not find the DKR decomp folder!");
    return (decompPath.value() / ".vanilla") / get_dkr_version();
}

size_t GlobalSettings::get_max_thread_count() {
    int value = get_value<int>("/threads", 0);
    return (value > 0) ? (size_t)value : std::thread::hardware_concurrency();
}