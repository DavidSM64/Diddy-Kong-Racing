#include <iostream>
#include <string>

#include "libs/argparse.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/debugHelper.h"

#include "misc/args.h"
#include "misc/globalSettings.h"

#include "extract/extractor.h"
#include "builder/builder.h"
#include "test/test.h"

using namespace DkrAssetsTool;

/*******************************************************************************************************/

int main(int argc, char *argv[]) {
    DebugHelper::get().set_asserts();
    
    std::optional<fs::path> decompRoot = GlobalSettings::find_decomp_root();
    DebugHelper::assert_(decompRoot.has_value(), "(main) Could not find the root to the decomp.");
    GlobalSettings::parse_values_from_json_file(decompRoot.value() / "tools/dkr_assets_tool_settings.json");
    
    //GlobalSettings::print_all_values();

    Args::parse(argc, argv);

    switch (Args::get_command()) {
        default:
            Args::print_help();
            break;
        case Args::ToolCommand::EXTRACT:
            AssetExtractor::extract_all();
            break;
        case Args::ToolCommand::BUILD:
            AssetBuilder::build_all(Args::get<std::string>("-o", ""));
            break;
    }
}
