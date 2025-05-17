#include "args.h"
#include "libs/argparse.hpp"
#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "misc/constants.hpp"

using namespace DkrAssetsTool;

Args::ToolCommand _currentCommand = Args::ToolCommand::NOCMD;
argparse::ArgumentParser _args(DKRAT_NAME, DKRAT_VERSION);

/*** Extract tool ***/
argparse::ArgumentParser _extract("extract");
argparse::ArgumentParser _builder("build");

void Args::parse(int argc, char* argv[]) {
    _extract.add_argument("-dkrv", "--dkrVersion")
        .required()
        .help("The version of DKR being used.");

    _extract.add_argument("-t", "--type")
        .default_value("")
        .help("Asset type to extract (Only for extracting a single asset)");

    _builder.add_argument("-i", "--input")
        .help("Input JSON filepath.");

    _builder.add_argument("-o", "--output")
        .required()
        .help("Output path.");

    _builder.add_argument("-dkrv", "--dkrVersion")
        .required()
        .help("The version of DKR being used.");
        
    _builder.add_argument("-m", "--modded")
        .flag()
        .help("Will try to compile assets if this flag is set.");

    _args.add_subparser(_extract);
    _args.add_subparser(_builder);

    try {
        _args.parse_args(argc, argv);
    } catch (const std::exception& err) {
        if (_args.is_subcommand_used(_extract)) {
            std::cout << _extract << std::endl;
        } else if (_args.is_subcommand_used(_builder)) {
            std::cout << _builder << std::endl;
        }
        DebugHelper::error(err.what());
    }

    if (_args.is_subcommand_used(_extract)) {
        _currentCommand = ToolCommand::EXTRACT;
    } else if (_args.is_subcommand_used(_builder)) {
        _currentCommand = ToolCommand::BUILD;
    }
}

Args::ToolCommand Args::get_command() {
    return _currentCommand;
}

template<typename T>
T Args::get(std::string key, T defaultValue) {
    try {
        switch (_currentCommand) {
            case ToolCommand::EXTRACT:
                return _extract.get<T>(key);
            case ToolCommand::BUILD:
                return _builder.get<T>(key);
            default:
                return defaultValue;
        }
    } catch (const std::bad_any_cast& err) {
        DebugHelper::warn("Could not get ", key, " from args. ", err.what());
    }
    
    return defaultValue;
}

template std::string Args::get<std::string>(std::string key, std::string defaultValue);
template int Args::get<int>(std::string key, int defaultValue);
template bool Args::get<bool>(std::string key, bool defaultValue);
template double Args::get<double>(std::string key, double defaultValue);

void Args::print_help() {
    std::cout << _args << std::endl;
}

std::string Args::get_dkr_version() {
    std::string ver = get<std::string>("-dkrv", "");
    DebugHelper::assert_(!ver.empty(), "(Args::get_dkr_version) You MUST specify a DKR version with \"-dkrv <version>\"");
    return ver;
}
