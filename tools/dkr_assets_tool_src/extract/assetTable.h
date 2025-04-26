#pragma once

#include <vector>
#include <unordered_map>

#include "libs/bytes_view.hpp"
#include "helpers/debugHelper.h"

namespace DkrAssetsTool {

enum DkrAssetTableType {
    FixedTable, // Starts with the length
    VariableTable, // Ends with -1
    MenuTextTable,
    GameTextTable,
    TTGhostTable,
    MiscTable,
    AudioTable,
};

struct DkrTableEntryInfo {
    int32_t offset;
    int32_t length;
};

class AssetTable {
public:
    AssetTable(BytesView view, DkrAssetTableType type = DkrAssetTableType::VariableTable);
    ~AssetTable();
    
    size_t number_of_entries();
    size_t total_size();
    
    int32_t get_entry_offset(size_t entryIndex);
    int32_t get_entry_size(size_t entryIndex);
    
    static DkrAssetTableType table_type_from_section_type(const std::string &sectionType);
    
private:
    void _parse_fixed_table();
    void _parse_variable_table();
    void _parse_menutext_table();
    void _parse_gametext_table();
    void _parse_ttghost_table();
    void _parse_misc_table();
    void _parse_audio_table();
    
    BytesView _view;
    
    std::vector<DkrTableEntryInfo> _entries;
    
    size_t _totalSize = 0;
};

}
