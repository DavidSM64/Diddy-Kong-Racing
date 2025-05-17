#pragma once

#include <map>

// Refactor TODO: Combine this with extract/assetTable.h?
#include "extract/assetTable.h"

#include "helpers/c/cContext.h"

#include "libs/bytes_view.hpp"

namespace DkrAssetsTool {
    
class BuildAssetTable {
public:
    BuildAssetTable(std::string assetType="Binary");
    BuildAssetTable(DkrAssetTableType tableType);
    ~BuildAssetTable();
    
    // GameText uses the highest bit to determine if the entry is a textbox or dialog.
    void add_entry(int32_t size, bool highestBitSet=false);
    
    void add_object_animation_ids_entry(int32_t objectModelId);
    
    BytesView get_view(CContext &cContext);
    
    size_t get_size_of_entries() const;
    
private:
    std::vector<DkrTableEntryInfo> _entries;
    DkrAssetTableType _type;
    std::vector<uint8_t> _data;
    
    bool _isDirty = false;
    size_t _currentOffset = 0;
    
    BytesView _reset_data(size_t newSize);
    void _compile_entries_to_data(CContext &cContext);
    int _find_index_of_object_model_id(int32_t objectModelId);
};

}
