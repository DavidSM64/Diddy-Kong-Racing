#pragma once

#include <string>

namespace DkrAssetsTool {

// Helps with getting values from the passed-in arguments.
namespace Args {
    enum ToolCommand {
        NOCMD,
        EXTRACT,
        BUILD,
        PREBUILD
    };

    void parse(int argc, char* argv[]);

    ToolCommand get_command();

    template<typename T>
    T get(std::string key, T defaultValue);

    void print_help();
    std::string get_dkr_version();
};

}
