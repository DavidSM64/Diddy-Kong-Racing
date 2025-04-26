#include "assetTable.h"

#include "helpers/dataHelper.h"

using namespace DkrAssetsTool;

AssetTable::AssetTable(BytesView view, DkrAssetTableType type) : _view(view) {
    switch(type) {
        case DkrAssetTableType::FixedTable:
            _parse_fixed_table();
            break;
        case DkrAssetTableType::VariableTable:
            _parse_variable_table();
            break;
        case DkrAssetTableType::MenuTextTable:
            _parse_menutext_table();
            break;
        case DkrAssetTableType::GameTextTable:
            _parse_gametext_table();
            break;
        case DkrAssetTableType::TTGhostTable:
            _parse_ttghost_table();
            break;
        case DkrAssetTableType::MiscTable:
            _parse_misc_table();
            break;
        case DkrAssetTableType::AudioTable:
            _parse_audio_table();
            break;
    }
}

AssetTable::~AssetTable() {
    
}


size_t AssetTable::number_of_entries() {
    return _entries.size();
}

size_t AssetTable::total_size() {
    return _totalSize;
}

int32_t AssetTable::get_entry_offset(size_t entryIndex) {
    if(entryIndex >= _entries.size()) {
        DebugHelper::error("(AssetTable::get_entry_offset) Entry out of bounds! ", entryIndex);
    }
    return _entries[entryIndex].offset;
}

int32_t AssetTable::get_entry_size(size_t entryIndex) {
    if(entryIndex >= _entries.size()) {
        DebugHelper::error("(AssetTable::get_entry_size) Entry out of bounds! ", entryIndex);
    }
    return _entries[entryIndex].length;
}

// TODO: Reduce duplicate code.

void AssetTable::_parse_fixed_table() {
    uint32_t offset = 0;
    int numEntries = _view.get_s32_be(0);
    offset += 4;
    for(int i = 0; i < numEntries; i++) {
        int32_t entryValue = _view.get_s32_be(offset);
        int32_t entrySize = _view.get_s32_be(offset + 4) - entryValue;
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 4;
    }
    _totalSize = DataHelper::align16(offset);
}

void AssetTable::_parse_variable_table() {
    uint32_t offset = 0;
    while(true) {
        int32_t entryValue = (_view.get_s32_be(offset));
        int32_t nextEntryValue = (_view.get_s32_be(offset + 4));
        if(entryValue == -1 || nextEntryValue == -1) {
            _totalSize = DataHelper::align16(offset);
            return;
        }
        int32_t entrySize = nextEntryValue - entryValue;
        if(entryValue < 0) {
            DebugHelper::error("(AssetTable::_parse_variable_table) Invalid table entry ", DebugHelper::to_hex(entryValue), " at rom offset ", DebugHelper::to_hex(offset));
        }
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 4;
    }
    
}

// Similar to _parse_variable_table, but it starts at index 1. (The 0th index tells how many text entries are in each language)
void AssetTable::_parse_menutext_table() {
    uint32_t offset = 4; 
    while(true) {
        int32_t entryValue = (_view.get_s32_be(offset));
        int32_t nextEntryValue = (_view.get_s32_be(offset + 4));
        if(entryValue == -1 || nextEntryValue == -1) {
            _totalSize = DataHelper::align16(offset);
            return;
        }
        int32_t entrySize = nextEntryValue - entryValue;
        
        if(entryValue < 0) {
            DebugHelper::error("(AssetTable::_parse_menutext_table) Invalid table entry ", DebugHelper::to_hex(entryValue), " at rom offset ", DebugHelper::to_hex(offset));
        }
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 4;
    }
}

// Similar to _parse_variable_table, but some entries might have the highest bit set to indicate that it is dialog instead of a textbox.
// So we want to disregard the negative value check.
void AssetTable::_parse_gametext_table() {
    uint32_t offset = 0; 
    while(true) {
        int32_t entryValue = (_view.get_s32_be(offset));
        int32_t nextEntryValue = (_view.get_s32_be(offset + 4));
        if(entryValue == -1 || nextEntryValue == -1) {
            _totalSize = DataHelper::align16(offset);
            return;
        }
        int32_t entrySize = (nextEntryValue & 0x7FFFFFFF) - (entryValue & 0x7FFFFFFF);
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 4;
    }
}

// Similar to _parse_variable_table, but ttghosts are 8 bytes per entry. We only care about the offsets though.
void AssetTable::_parse_ttghost_table() {
    uint32_t offset = 0; 
    while(true) {
        
        int32_t entryValue = (_view.get_s32_be(offset + 4));
        int32_t nextEntryValue = (_view.get_s32_be(offset + 12));
        if(entryValue == -1 || nextEntryValue == -1) {
            _totalSize = DataHelper::align16(offset);
            return;
        }
        int32_t entrySize = nextEntryValue - entryValue;
        
        if(entryValue < 0) {
            DebugHelper::error("(AssetTable::_parse_ttghost_table) Invalid table entry ", DebugHelper::to_hex(entryValue), " at rom offset ", DebugHelper::to_hex(offset));
        }
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 8;
    }
}

// Similar to _parse_variable_table, but each entry must be multiplied by 4.
void AssetTable::_parse_misc_table() {
    uint32_t offset = 0;
    while(true) {
        int32_t entryValue = (_view.get_s32_be(offset));
        int32_t nextEntryValue = (_view.get_s32_be(offset + 4));
        if(entryValue == -1 || nextEntryValue == -1) {
            _totalSize = DataHelper::align16(offset);
            return;
        }
        int32_t entrySize = nextEntryValue - entryValue;
        
        entryValue *= 4;
        entrySize *= 4;
        
        if(entryValue < 0) {
            DebugHelper::error("(AssetTable::_parse_misc_table) Invalid table entry ", DebugHelper::to_hex(entryValue), " at rom offset ", DebugHelper::to_hex(offset));
        }
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 4;
    }
}

// Similar to _parse_variable_table, but the table itself doesn't start at index 0, so I have to manually add it.
void AssetTable::_parse_audio_table() {
    uint32_t offset = 0;
    
    int32_t firstEntrySize = _view.get_s32_be(offset);
     _entries.push_back({0, firstEntrySize});
    
    while(true) {
        int32_t entryValue = (_view.get_s32_be(offset));
        int32_t nextEntryValue = (_view.get_s32_be(offset + 4));
        if(entryValue == -1 || nextEntryValue == -1) {
            _totalSize = DataHelper::align16(offset);
            return;
        }
        int32_t entrySize = nextEntryValue - entryValue;
        
        
        if(entryValue < 0) {
            DebugHelper::error("(AssetTable::_parse_audio_table) Invalid table entry ", DebugHelper::to_hex(entryValue), " at rom offset ", DebugHelper::to_hex(offset));
        }
        
        _entries.push_back({entryValue, entrySize});
        
        offset += 4;
    }
}

std::unordered_map<std::string, DkrAssetTableType> tableTypeMap = {
    {"GameText", DkrAssetTableType::GameTextTable},
    {"MenuText", DkrAssetTableType::MenuTextTable},
    {"TTGhost", DkrAssetTableType::TTGhostTable},
    {"Miscellaneous", DkrAssetTableType::MiscTable},
    {"Audio", DkrAssetTableType::AudioTable},
};

DkrAssetTableType AssetTable::table_type_from_section_type(const std::string &sectionType) {
    auto it = tableTypeMap.find(sectionType);
    if(it != tableTypeMap.end()) {
        return it->second;
    }
    return DkrAssetTableType::VariableTable;
}