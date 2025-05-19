#pragma once

#include <unordered_map>
#include <string>

namespace DkrAssetsTool {
    
class BuildInfo;

class BuildStats {
    public:
    
    private:
        std::unordered_map<std::string, int> _numberOfFilesInSection; 
};

}