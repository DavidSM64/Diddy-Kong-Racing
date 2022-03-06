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
    std::cout << "Building an asset: ./dkr_assets_tool -b <assets path> <source path> <output path>" << std::endl;
    std::cout << "Creating includes: ./dkr_assets_tool -i <assets path> <include directory> <build directory> <asm output directory>" << std::endl;
    std::cout << "Compiling assets:  ./dkr_assets_tool -c <assets path> <version>" << std::endl;
    std::cout << "Compress file:     ./dkr_assets_tool -fc <input_filename> <output_filename>" << std::endl;
    std::cout << "Decompress file:   ./dkr_assets_tool -fd <input_filename> <output_filename>" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
}

/**************************************************************************/

typedef enum _ToolType {
    TT_DO_NOTHING,
    TT_EXTRACT,
    TT_BUILD,
    TT_ASSET_INCLUDES,
    TT_ASSET_COMPILE,
    TT_ASSET_COMPRESS_FILE,
    TT_ASSET_DECOMPRESS_FILE,
} ToolType;

typedef struct _CmdArgOptions {
    ToolType type;
    std::vector<std::string> paths;
} CmdArgOptions;

CmdArgOptions options;

/**************************************************************************/

typedef enum _CurrentParseOption {
    PO_NONE,
    PO_TYPE
} CurrentParseOption;

template <class T>
void invalid_arg_error(T arg) {
    std::cout << "Error: Invalid argument \"" << arg << "\"" << std::endl;
}

std::string get_cmd_from_parse_option(ToolType type) {
    switch(type) {
        case TT_EXTRACT: return "-e";
        case TT_BUILD: return "-b";
        case TT_ASSET_INCLUDES: return "-i";
        case TT_ASSET_COMPILE: return "-c";
        case TT_ASSET_COMPRESS_FILE: return "-fc";
        case TT_ASSET_DECOMPRESS_FILE: return "-fd";
    }
    return "(Invalid option)";
}

bool parse_options(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv+argc);

    if(argc == 1) {
        return false; // Display usage
    }
    
    // Parse options from command line.
    bool parsingCmd = false;
    int curOptionState = 0;
    int curOptionArgs = 0;
    CurrentParseOption curOption = PO_NONE;
    for (size_t i = 1; i < args.size(); ++i) {
        if(args[i][0] == '-') {
            if(parsingCmd) {
                std::cout << "Error: Not enough args for the current command \"" 
                    << get_cmd_from_parse_option(options.type) << "\"" << std::endl;
                return false;
            }
            if(args[i] == "-e") {
                curOption = PO_TYPE;
                curOptionState = 1;
                options.type = TT_EXTRACT;
                parsingCmd = true;
            } else if(args[i] == "-b") {
                curOption = PO_TYPE;
                curOptionState = 2;
                options.type = TT_BUILD;
                parsingCmd = true;
            } else if(args[i] == "-i") {
                curOption = PO_TYPE;
                curOptionState = 3;
                options.type = TT_ASSET_INCLUDES;
                parsingCmd = true;
            } else if(args[i] == "-c") {
                curOption = PO_TYPE;
                curOptionState = 4;
                options.type = TT_ASSET_COMPILE;
                parsingCmd = true;
            } else if(args[i] == "-fc") {
                curOption = PO_TYPE;
                curOptionState = 5;
                options.type = TT_ASSET_COMPRESS_FILE;
                parsingCmd = true;
            } else if(args[i] == "-fd") {
                curOption = PO_TYPE;
                curOptionState = 6;
                options.type = TT_ASSET_DECOMPRESS_FILE;
                parsingCmd = true;
            } else if(args[i] == "-h") {
                return false;
            } else  {
                std::cout << "Error: Invalid option " << args[i] << std::endl;
                return false;
            }
            curOptionArgs = 0;
        } else {
            if(!parsingCmd) {
                std::cout << "Error: Too many args for the current command \"" 
                    << get_cmd_from_parse_option(options.type) << "\"" << std::endl;
                return false;
            }
            switch(curOption) {
                case PO_TYPE:
                    switch(curOptionState) {
                        case 1: // Extractor
                            switch(curOptionArgs) {
                                case 0: // version
                                case 1: // configs directory
                                case 2: // baseroms directory
                                    options.paths.push_back(args[i]);
                                    break;
                                case 3: // output directory
                                    options.paths.push_back(args[i]);
                                    // End of arguments.
                                    parsingCmd = false;
                                    curOption = PO_NONE;
                                    break;
                            }
                            break;
                        case 2: // Builder
                            switch(curOptionArgs) {
                                case 0: // Assets directory
                                case 1: // Source path
                                    options.paths.push_back(args[i]);
                                    break;
                                case 2:  // Output path
                                    options.paths.push_back(args[i]);
                                    // End of arguments.
                                    parsingCmd = false;
                                    curOption = PO_NONE;
                                    break;
                            }
                            break;
                        case 3: // Asset header 
                            switch(curOptionArgs) {
                                case 0: // Assets directory
                                case 1: // Enum file output path
                                case 2: // Build directory
                                    options.paths.push_back(args[i]);
                                    break;
                                case 3: // Asm output directory
                                    options.paths.push_back(args[i]);
                                    // End of arguments.
                                    parsingCmd = false;
                                    curOption = PO_NONE;
                                    break;
                            }
                            break;
                        case 4: // Compile assets 
                        case 5: // Compress file
                        case 6: // Decompress file
                            switch(curOptionArgs) {
                                case 0: // Assets directory / Input filename
                                    options.paths.push_back(args[i]);
                                    break;
                                case 1: // version / Output filename
                                    options.paths.push_back(args[i]);
                                    // End of arguments.
                                    parsingCmd = false;
                                    curOption = PO_NONE;
                                    break;
                            }
                            break;
                    }
                    break;
                default: // This should hopefully never get called
                    std::cout << "Error: You should not be seeing this message." << std::endl;
                    return false;
            }
            curOptionArgs++;
        }
    }
    
    if(parsingCmd) {
        std::cout << "Error: Not enough args for the current command \"" 
            << get_cmd_from_parse_option(options.type) << "\"" << std::endl;
        return false;
    }
    
    return true;
}

/**************************************************************************/

int main(int argc, char *argv[]) {
    if(!parse_options(argc, argv)) {
        print_usage();
        return 1;
    }
    
    switch(options.type) {
        case TT_EXTRACT:
            {
                Extractor extractor(options.paths[0], options.paths[1], options.paths[2], options.paths[3]);
            }
            break;
        case TT_BUILD:
            {
                Builder builder(options.paths[0], options.paths[1], options.paths[2]);
            }
            break;
        case TT_ASSET_INCLUDES:
            {
                setAssetsFolderPath(options.paths[0]);
                AssetEnumsHeader assetEnumsHeader(options.paths[1]);
                AssetAsmIncludes assetAsmIncludes(options.paths[0], options.paths[2], options.paths[3]);
            }
            break;
        case TT_ASSET_COMPILE:
            {
                AssetCompiler compiler(options.paths[0], options.paths[1]);
            }
            break;
        case TT_ASSET_COMPRESS_FILE:
        case TT_ASSET_DECOMPRESS_FILE:
            {
                DKRCompression compression;
                std::string inputFilename = options.paths[0];
                std::string outputFilename = options.paths[1];
                std::vector<uint8_t> inputBinary, outputBinary;
                
                if(compression.readBinaryFile(inputBinary, inputFilename))
                {
                    if(inputBinary.size() == 0) {
                        compression.writeBinaryFile(inputBinary, outputFilename);
                    } else {
                        if (options.type == TT_ASSET_COMPRESS_FILE) 
                        {
                            outputBinary = compression.compressBuffer(inputBinary);
                        } 
                        else if (options.type == TT_ASSET_DECOMPRESS_FILE) 
                        {
                            outputBinary = compression.decompressBuffer(inputBinary);
                        }
                        compression.writeBinaryFile(outputBinary, outputFilename);
                    }
                }
                else 
                {
                    std::cout << "Could not read file: " << inputFilename << std::endl;
                    return 1;
                }
            }
            break;
    }
    
    return 0;
}
 
