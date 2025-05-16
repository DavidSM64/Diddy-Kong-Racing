#include "buildAssetTable.h"

#include "helpers/assetsHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/debugHelper.h"

using namespace DkrAssetsTool;

BuildAssetTable::BuildAssetTable(std::string assetType) {
    _type = AssetTable::table_type_from_section_type(assetType);
    _isDirty = true;
}

BuildAssetTable::BuildAssetTable(DkrAssetTableType tableType) : _type(tableType) {
    _isDirty = true;
}

BuildAssetTable::~BuildAssetTable() {
}

void BuildAssetTable::add_entry(int32_t size, bool highestBitSet) {
    DebugHelper::assert_(_type != DkrAssetTableType::ObjectAnimationIdsTable,
        "(BuildAssetTable::add_entry) Table is the incorrect type! Should NOT be a ObjectAnimationIdsTable.");
        
    if(_type == DkrAssetTableType::MiscTable) {
        size /= 4; // Misc table entries have to be divided by 4 (for some reason)
    }
    
    // GameText uses the highest bit to determine if the entry is a textbox or dialog.
    int32_t offset = _currentOffset | (highestBitSet ? (0x80000000) : 0);
    _entries.emplace_back(offset, size);
    _currentOffset += size;
    _isDirty = true;
}

int BuildAssetTable::_find_index_of_object_model_id(int32_t objectModelId) {
    int foundIndex = -1;
    for(size_t i = 0; i < _entries.size(); i++) {
        if(_entries[i].objectModelId == objectModelId) {
            foundIndex = i;
            break;
        }
    }
    return foundIndex;
}

void BuildAssetTable::add_object_animation_ids_entry(int32_t objectModelId) {
    DebugHelper::assert_(_type == DkrAssetTableType::ObjectAnimationIdsTable,
        "(BuildAssetTable::add_object_animation_ids_entry) Table is the incorrect type! Should be a ObjectAnimationIdsTable.");
    
    int foundIndex = _find_index_of_object_model_id(objectModelId);
    
    if(foundIndex < 0) {
        foundIndex = _entries.size();
        _entries.emplace_back(objectModelId, 0);
    }
    
    _entries[foundIndex].count++;
    _isDirty = true;
}

BytesView BuildAssetTable::get_view(CContext &cContext) {
    if(_isDirty) {
        _compile_entries_to_data(cContext);
    }
    return BytesView(_data);
}

size_t BuildAssetTable::get_size_of_entries() const {
    return _currentOffset;
}

BytesView BuildAssetTable::_reset_data(size_t newSize) {
    _data.clear();
    _data.resize(DataHelper::align16(newSize));
    return BytesView(_data);
}

void BuildAssetTable::_compile_entries_to_data(CContext &cContext) {
    int32_t totalSizeOfEntries = _currentOffset;
    
    switch(_type) {
        case DkrAssetTableType::FixedTable:
            {
                int32_t numberOfEntries = (int32_t)_entries.size();
                BytesView view = _reset_data((numberOfEntries + 2) * 4);
                
                view.set_s32_be(0, numberOfEntries); // First entry is the number of following entries.
                
                for(int32_t i = 0; i < numberOfEntries; i++) {
                    view.set_s32_be((1 + i) * 4, _entries[i].offset);
                }
                
                view.set_s32_be((1 + numberOfEntries) * 4, totalSizeOfEntries); // Last entry is the total size of the assets.
            }
            break;
        case DkrAssetTableType::VariableTable:
        case DkrAssetTableType::GameTextTable:
        case DkrAssetTableType::MiscTable:
        case DkrAssetTableType::AudioTable:
            {
                int32_t numberOfEntries = (int32_t)_entries.size();
                BytesView view = _reset_data((numberOfEntries + 2) * 4);
                
                int startOffset = 0;
                
                // The audio table skips the first entry for whatever reason.
                if(_type == DkrAssetTableType::AudioTable) {
                    numberOfEntries--;
                    startOffset = 1;
                }
                
                for(int i = 0; i < numberOfEntries; i++) {
                    view.set_s32_be(i * 4, _entries[startOffset + i].offset);
                }
                
                view.set_s32_be(numberOfEntries * 4, totalSizeOfEntries); // 2nd to last entry is the total size of the assets.
                view.set_s32_be((numberOfEntries + 1) * 4, -1);           // Last entry should be -1
            }
            break;
        case DkrAssetTableType::MenuTextTable:
            {
                int32_t numberOfEntries = (int32_t)_entries.size();
                JsonFile &menuTextSectionJson = AssetsHelper::get_asset_section_json("ASSET_MENU_TEXT");
                size_t numberOfMenuTextEntries = menuTextSectionJson.length_of_array("/menu-text-build-ids");
                
                BytesView view = _reset_data((numberOfEntries + 3) * 4);
                
                view.set_s32_be(0, numberOfMenuTextEntries); // First entry is the number of menu text entries.
                
                for(int32_t i = 0; i < numberOfEntries; i++) {
                    view.set_s32_be((1 + i) * 4, _entries[i].offset);
                }
                
                view.set_s32_be((1 + numberOfEntries) * 4, totalSizeOfEntries); // 2nd to last entry is the total size of the assets.
                view.set_s32_be((1 + numberOfEntries + 1) * 4, -1);             // Last entry should be -1
            }
            break;
        case DkrAssetTableType::TTGhostTable:
            {
                int32_t numberOfEntries = (int32_t)_entries.size();
                BytesView view = _reset_data((numberOfEntries + 2) * 8);
                
                for(int32_t i = 0; i < numberOfEntries; i++) {
                    std::string ttGhostBuildId = AssetsHelper::get_build_id_of_index("ASSET_TTGHOSTS", i);
                    JsonFile &ttGhostJson = AssetsHelper::get_asset_json("ASSET_TTGHOSTS", ttGhostBuildId);
                    std::string levelBuildId = ttGhostJson.get_string("/header/level");
                    std::string vehicleEnumStr = ttGhostJson.get_string("/header/vehicle");
                    
                    int levelIndex = AssetsHelper::get_asset_index("ASSET_LEVEL_HEADERS", levelBuildId) & 0xFF;
                    int vehicleEnumValue = cContext.get_int_value_of_symbol(vehicleEnumStr) & 0xFF;
                    
                    view.set_s32_be((i * 8) + 0, (levelIndex << 24) | (vehicleEnumValue << 16));
                    view.set_s32_be((i * 8) + 4, _entries[i].offset);
                }
                
                view.set_s32_be((numberOfEntries * 8) + 0, 0xFFFF0000); 
                view.set_s32_be((numberOfEntries * 8) + 4, totalSizeOfEntries); // 2nd to last entry is the total size of the assets.
                view.set_s32_be(((numberOfEntries + 1) * 8) + 0, 0xFFFF0000);
                view.set_s32_be(((numberOfEntries + 1) * 8) + 4, -1);           // Last entry should be -1
            }
            break;
        case DkrAssetTableType::ObjectAnimationIdsTable:
            {
                int32_t numberOfModels = AssetsHelper::get_asset_section_count("ASSET_OBJECT_MODELS");
                BytesView view = _reset_data((numberOfModels + 1) * sizeof(int16_t));
                
                int16_t currAnimOffset = 0;
                for(int32_t modelIndex = 0; modelIndex < numberOfModels; modelIndex++) {
                    view.set_s16_be(modelIndex * sizeof(int16_t), currAnimOffset);
                    
                    int foundIndex = _find_index_of_object_model_id(modelIndex);
                    
                    if(foundIndex < 0) {
                        continue;
                    }
                    
                    currAnimOffset += _entries[foundIndex].count;
                }
                
                // Last entry should be the total number of animations.
                view.set_s16_be(numberOfModels * sizeof(int16_t), currAnimOffset);
            }
            break;
        default:
            DebugHelper::error("Unknown table type: ", _type);
            break;
    }
    
    _isDirty = false;
}

