#include <iostream>
#include <string>

#include "libs/argparse.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/debugHelper.h"

#include "misc/args.h"
#include "misc/globalSettings.h"

#include "extract/extractor.h"
#include "builder/builder.h"
#include "prebuild/prebuild.h"
#include "test/test.h"

using namespace DkrAssetsTool;

/*******************************************************************************************************/

int main(int argc, char *argv[]) {
    DebugHelper::get().set_asserts();
    
    GlobalSettings::parse_values_from_json_file("dkr_assets_tool_settings.json");
    //GlobalSettings::print_all_values();

    Args::parse(argc, argv);

    switch (Args::get_command()) {
        default:
            Args::print_help();
            break;
        case Args::ToolCommand::EXTRACT:
            AssetExtractor::extract_all(Args::get<fs::path>("-o", ""));
            break;
    }
    
    /*
    argparse::ArgumentParser args(DKRAT_NAME, DKRAT_VERSION);
    
    DkrAssetsSettings settings;
    
    argparse::ArgumentParser extract("extract");
    
    argparse::ArgumentParser builder("build");
    
    argparse::ArgumentParser prebuild("prebuild");
    
    argparse::ArgumentParser tester("test");
    
    builder.add_argument("-i", "--input")
        .default_value("")
        .help("Input JSON filepath. (Optional, if not specified then all assets are built to output path)");
    
    builder.add_argument("-o", "--output")
        .required()
        .help("Output path.");
    
    args.add_subparser(extract);
    args.add_subparser(builder);
    args.add_subparser(prebuild);
    args.add_subparser(tester);
        
    args.add_argument("-dkrv", "--dkr_version")
        .default_value(settings.dkrVersion)
        .help("Which version of DKR to use. Overrides default.");
        
    args.add_argument("-vb", "--verbose")
        .default_value(DEFAULT_VERBOSE_VALUE)
        .implicit_value(true)
        .help("Which version of DKR to use. Overrides default.");
    
    try {
        args.parse_args(argc, argv);
    } catch (const std::exception &err) {
        if(args.is_subcommand_used(extract)) {
            std::cout << extract << std::endl;
        } else if(args.is_subcommand_used(builder)) {
            std::cout << builder << std::endl;
        }
        DebugHelper::error(err.what());
    }
    
    settings.dkrVersion = args.get<std::string>("-dkrv");
    DebugHelper::get().set_verbose(args.get<bool>("-vb"));
    DebugHelper::get().set_asserts(USING_ASSERTS);
    
    if(args.is_subcommand_used(extract)) {
        //settings.print();
        DkrExtract extract(settings);
        return 0;
    }
    if(args.is_subcommand_used(builder)) {
        std::string inputPath = builder.get<std::string>("-i");
        std::string outputPath = builder.get<std::string>("-o");
        if(!inputPath.empty()) {
            DkrAssetBuilder builder(settings, inputPath, outputPath); // build single asset
        } else {
            DkrAssetBuilder builder(settings, outputPath); // build ALL assets
        }
        return 0;
    }
    if(args.is_subcommand_used(tester)) {
        //settings.print();
        TestDKRAT test(settings);
        return 0;
    }
    if(args.is_subcommand_used(prebuild)) {
        //settings.print();
        PreBuild prebuild(settings);
        return 0;
    }
    
    return 0;
    */
}
