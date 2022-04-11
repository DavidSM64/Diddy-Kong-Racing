/**
 * This tool handles everything assets-related including extracting and building.
 */
 
#include <iostream> 
#include <string> 
#include <vector> 

#include "dkr_assets_tool_classes/common/util.h"
#include "dkr_assets_tool_classes/extractor/extractor.h"
#include "dkr_assets_tool_classes/builder/builder.h"
#include "dkr_assets_tool_classes/make_asset_files/asset_enums_header.h"
#include "dkr_assets_tool_classes/make_asset_files/asset_asm_data.h"
#include "dkr_assets_tool_classes/compiler/compiler.h"

/**************************************************************************/

void print_usage() {
    std::cout << "---- Usages -------------------------------------------------------------" << std::endl;
    std::cout << "Extracting assets: ./dkr_assets_tool -e <version> <configs path> <baseroms path> <output path>" << std::endl;
    std::cout << "Building an asset: ./dkr_assets_tool -b <version> <assets path> <source path> <output path>" << std::endl;
    std::cout << "Build enums cache: ./dkr_assets_tool -bc <version> <enums.h path>" << std::endl;
    std::cout << "Creating includes: ./dkr_assets_tool -i <version> <assets path> <include directory> <build directory> <asm output directory>" << std::endl;
    std::cout << "Compiling assets:  ./dkr_assets_tool -c <version> <assets path>" << std::endl;
    std::cout << "Compress file:     ./dkr_assets_tool -fc <input_filename> <output_filename>" << std::endl;
    std::cout << "Decompress file:   ./dkr_assets_tool -fd <input_filename> <output_filename>" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}

/**************************************************************************/

struct Command {
    std::string flag;
    int args;
    void (*func)(const std::vector<std::string>&);
};

void extract(const std::vector<std::string>& args);
void build(const std::vector<std::string>& args);
void asset_includes(const std::vector<std::string>& args);
void asset_compile(const std::vector<std::string>& args);
void asset_compress(const std::vector<std::string>& args);
void asset_decompress(const std::vector<std::string>& args);
void build_enums_cache(const std::vector<std::string>& args);

static const std::vector<Command> COMMANDS = {
    // Extract
    {
        .flag = "-e",
        .args = 5,
        .func = &extract,
    },
    // Build
    {
        .flag = "-b",
        .args = 4,
        .func = build,
    },
    // Build enums cache
    {
        .flag = "-bc",
        .args = 2,
        .func = build_enums_cache,
    },
    // Asset includes
    {
        .flag = "-i",
        .args = 5,
        .func = asset_includes,
    },
    // Asset compile
    {
        .flag = "-c",
        .args = 2,
        .func = asset_compile,
    },
    // Asset compress file
    {
        .flag = "-fc",
        .args = 2,
        .func = asset_compress,
    },
    // Asset decompress file
    {
        .flag = "-fd",
        .args = 2,
        .func = asset_decompress,
    },
};

void extract(const std::vector<std::string>& args) {
    std::string version      = args[0]; // us_1.0
    std::string assetsDir    = args[1]; // <root>/assets
    std::string configsPath  = args[2]; // <root>/extract-ver
    std::string baseromsPath = args[3]; // <root>/baseroms
    std::string outputPath   = args[4]; // <root>

    set_assets_folder_path(assetsDir + "/vanilla");
    set_version(version);

    Extractor extractor(version, configsPath, baseromsPath, outputPath);
}

void build(const std::vector<std::string>& args) {
    std::string version    = args[0]; // us_1.0
    std::string assetsDir  = args[1]; // <root>/assets
    std::string sourcePath = args[2]; // Input .json filepath
    std::string outputPath = args[3]; // Output .bin filepath

    set_assets_folder_path(assetsDir);
    set_version(version);

    Builder builder(sourcePath, outputPath);
}

void asset_includes(const std::vector<std::string>& args) {
    std::string version      = args[0]; // us_1.0
    std::string assetsDir    = args[1]; // <root>/assets
    std::string includeDir   = args[2]; // <root>/include
    std::string buildDir     = args[3]; // <root>/build
    std::string assetsAsmDir = args[4]; // <root>/asm/assets

    set_assets_folder_path(assetsDir);
    set_version(version);

    AssetEnumsHeader assetEnumsHeader(includeDir);
    AssetAsmIncludes assetAsmIncludes(assetsDir + "/" + version, buildDir + "/" + version, assetsAsmDir);
}

void asset_compile(const std::vector<std::string>& args) {
    std::string version   = args[0]; // us_1.0
    std::string assetsDir = args[1]; // <root>/assets

    set_assets_folder_path(assetsDir);
    set_version(version);
    
    AssetCompiler compiler;
}

void asset_compress(const std::vector<std::string>& args) {
    DKRCompression compression;
    std::string inputFilename = args[0];
    std::string outputFilename = args[1];
    std::vector<uint8_t> inputBinary, outputBinary;
    
    if(compression.readBinaryFile(inputBinary, inputFilename)) {
        if(inputBinary.size() == 0) {
            compression.writeBinaryFile(inputBinary, outputFilename);
        } else {
            outputBinary = compression.compressBuffer(inputBinary);
            compression.writeBinaryFile(outputBinary, outputFilename);
        }
    } else {
        display_error_and_abort("Could not read file: ", inputFilename);
    }
}

void asset_decompress(const std::vector<std::string>& args) {
    DKRCompression compression;
    std::string inputFilename = args[0];
    std::string outputFilename = args[1];
    std::vector<uint8_t> inputBinary, outputBinary;
    
    if(compression.readBinaryFile(inputBinary, inputFilename)) {
        if(inputBinary.size() == 0) {
            compression.writeBinaryFile(inputBinary, outputFilename);
        } else {
            outputBinary = compression.decompressBuffer(inputBinary);
            compression.writeBinaryFile(outputBinary, outputFilename);
        }
    } else {
        display_error_and_abort("Could not read file: ", inputFilename);
    }
}

void build_enums_cache(const std::vector<std::string>& args) {
    std::string version         = args[0]; // us_1.0
    std::string enumsHeaderPath = args[1]; // <root>/include/enums.h

    set_version(version);
    generate_enums_cache(enumsHeaderPath);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_usage();
        return 1;
    }
    std::string flag = argv[1];
    auto it = std::find_if(COMMANDS.begin(), COMMANDS.end(), [&flag](const Command& cmd) {
        return cmd.flag == flag;
    });
    if (it == COMMANDS.end()) {
        print_usage();
        return 1;
    }
    if (argc - 2 != it->args) {
        display_error_and_abort("Expected ", it->args, " args but was given ", argc - 2, ".");
        return 1;
    }
    std::vector<std::string> args(argv + 2, argv + argc);
    it->func(args);
    return 0;
}
