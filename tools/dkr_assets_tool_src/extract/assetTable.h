#pragma once

#include <vector>
#include <unordered_map>

#include "helpers/debugHelper.h"
#include "rom.h"

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
    AssetTable(DkrExtractROM *rom, uint32_t offset, DkrAssetTableType type = DkrAssetTableType::VariableTable);
    ~AssetTable();
    
    size_t size();
    
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
    
    DkrExtractROM *_rom;
    uint32_t _romOffset;
    
    std::vector<DkrTableEntryInfo> _entries;
};
