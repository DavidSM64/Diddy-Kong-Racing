#include "miscHelper.h"

void MiscHelper::process_cheats_encryption(uint8_t *data, size_t dataSize) {
    uint8_t a, b, c, d;
    uint32_t sp0, sp1, sp2, sp3;
    
    size_t numWords = dataSize / 4;
    for(size_t i = 0; i < numWords; i++) {
        size_t offset = i * 4;
        a = (data[offset + 3] & 0xC0) >> 6;
        b = (data[offset + 0] & 0xC0);
        c = (data[offset + 1] & 0xC0) >> 2;
        d = (data[offset + 2] & 0xC0) >> 4;
        sp0 = a | b | c | d;
        
        a = (data[offset + 3] & 0x30) >> 4;
        b = (data[offset + 0] & 0x30) << 2;
        c = (data[offset + 1] & 0x30);
        d = (data[offset + 2] & 0x30) >> 2;
        sp1 = a | b | c | d;
        
        a = (data[offset + 3] & 0x0C) >> 2;
        b = (data[offset + 0] & 0x0C) << 4;
        c = (data[offset + 1] & 0x0C) << 2;
        d = (data[offset + 2] & 0x0C);
        sp2 = a | b | c | d;
        
        a = (data[offset + 3] & 0x03);
        b = (data[offset + 0]       ) << 6;
        c = (data[offset + 1] & 0x03) << 4;
        d = (data[offset + 2] & 0x03) << 2;
        sp3 = a | b | c | d;
        
        a = (sp0 & 0xAA) >> 1;
        b = (sp0 & 0x55) << 1;
        data[offset + 0] = a | b;
        
        a = (sp1 & 0xAA) >> 1;
        b = (sp1 & 0x55) << 1;
        data[offset + 1] = a | b;
        
        a = (sp2 & 0xAA) >> 1;
        b = (sp2 & 0x55) << 1;
        data[offset + 2] = a | b;
        
        a = (sp3 & 0xAA) >> 1;
        b = (sp3 & 0x55) << 1;
        data[offset + 3] = a | b;
    }
}
    
void MiscHelper::process_cheats_encryption(std::vector<uint8_t> &data) {
    process_cheats_encryption(&data[0], data.size());
}