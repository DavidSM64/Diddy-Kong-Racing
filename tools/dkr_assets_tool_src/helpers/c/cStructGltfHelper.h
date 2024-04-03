#include "helpers/c/cStructHelper.h"
#include "helpers/gltf/gltfHelper.h"

// Class that helps with interacting with both cStructs and Gltf files

class CStructGltfHelper {
public:
    // struct entry -> gltf node extra
    static void put_struct_entry_into_gltf_node_extra(CStructEntry *structMember, WriteableGltfFile &gltfFile,
        int gltfNode, uint8_t *bytes);
    
    // gltf node extra -> struct entry
    static void put_gltf_node_extra_into_struct_entry(CStructEntry *structMember, GltfFile &gltfFile,
        int gltfNode, uint8_t *bytes);
};
