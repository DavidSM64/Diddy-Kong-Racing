def apply(config, args):
    config["baseimg"] = f"baseroms/baserom." + args.region + "." + args.version + ".z64"
    config["myimg"] = f"build/dkr." + args.region + "." + args.version + ".z64"
    config["mapfile"] = f"build/dkr." + args.region + "." + args.version + ".map"
    config["source_directories"] = ["src"]
    config["show_line_numbers_default"] = True
    config["expected_dir"] = "expected/"
    config["makeflags"] = ["REGION=" + args.region, "VERSION=" + args.version]

def add_custom_arguments(parser):
    parser.add_argument(
        "-r",
        "--REGION",
        dest="region",
        default="us",
        type=str,
        help="Set the region",
    )
    parser.add_argument(
        "-v",
        "--VERSION",
        dest="version",
        default="v77",
        type=str,
        help="Set the version",
    )
