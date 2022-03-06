#include "extract_ttghost.h"

ExtractTTGhost::ExtractTTGhost(std::string key, std::vector<uint8_t> data, std::string outFilepath, 
json::JSON &configJSON) 
: Extract(key, data, outFilepath) {    
    json::JSON out = json::Object();
    
    out["type"] = "TTGhosts";
    out["header"] = json::Object();
    out["nodes"] = json::Array();
    
    out["header"]["level"] = data[0];
    
    out["header"]["vehicle"] = get_enum_string_from_value("Vehicle", data[1]);
    
    //out["header"]["unk02"] = data[2]; // Always 0x09?
    out["header"]["time"] = get_big_endian_halfword(data, 4);
    
    int nodeCount = get_big_endian_halfword(data, 6);
    
    for(int i = 0; i < nodeCount; i++) {
        json::JSON node = json::Object();
        
        int offset = (i * 12) + 8;
        
        node["x"]  = (int16_t)get_big_endian_halfword(data, offset);
        node["y"]  = (int16_t)get_big_endian_halfword(data, offset + 2);
        node["z"]  = (int16_t)get_big_endian_halfword(data, offset + 4);
        // Yes, this order is correct.
        node["rz"] = (int16_t)get_big_endian_halfword(data, offset + 6);
        node["rx"] = (int16_t)get_big_endian_halfword(data, offset + 8);
        node["ry"] = (int16_t)get_big_endian_halfword(data, offset + 10);
        
        out["nodes"].append(node);
    }
    
    write_json(out, outFilepath);
    print_extracted();
}

ExtractTTGhost::~ExtractTTGhost(){
}
