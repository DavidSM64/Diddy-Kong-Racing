#!/usr/bin/env python3

import argparse
import os
import sys
import subprocess
import tempfile

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))
src_dir = root_dir + "src/"

# Project-specific
CPP_FLAGS = [
    "-Iinclude",
    "-Iinclude/libc",
    "-Iinclude/PR",
    "-Iinclude/sys",
    "-Iassets",
    "-Isrc",
    "-Ilibultra",
    "-Ilibultra/src/gu",
    "-Ilibultra/src/libc",
    "-Ilibultra/src/io",
    "-Ilibultra/src/sc",
    "-Ilibultra/src/audio",
    "-Ilibultra/src/os",
    "-D_LANGUAGE_C",
    "-DF3DDKR_GBI",
    "-D_MIPS_SZLONG=32",
    "-DBUILD_VERSION=4",
    "-DTARGET_N64",
    "-D_FINALROM",
    "-DNDEBUG",
    "-DVERSION_us_v1",
    "-DANTI_TAMPER",
    "-D BUILD_VERSION_STRING=\"2.0G\"",
    "-DM2CTX",
    "-D__sgi",
    "-U__GNUC__",
]

def import_c_file(in_file) -> str:
    in_file = os.path.relpath(in_file, root_dir)

    cpp_command = ["gcc", "-E", "-P", "-dD", *CPP_FLAGS, in_file]

    with tempfile.NamedTemporaryFile(suffix=".c") as tmp:
        stock_macros = subprocess.check_output(["gcc", "-E", "-P", "-dM", tmp.name], cwd=root_dir, encoding="utf-8")

    try:
        out_text = subprocess.check_output(cpp_command, cwd=root_dir, encoding="utf-8")
    except subprocess.CalledProcessError:
        print(
            "Failed to preprocess input file, when running command:\n"
            + " ".join(cpp_command),
            file=sys.stderr,
            )
        sys.exit(1)

    if not out_text:
        print("Output is empty - aborting")
        sys.exit(1)

    defines = {}
    source_lines = []
    for line in out_text.splitlines(keepends=True):
        if line.startswith("#define"):
            sym = line.split()[1].split("(")[0]
            defines[sym] = line
        elif line.startswith("#undef"):
            sym = line.split()[1]
            if sym in defines:
                del defines[sym]
        else:
            source_lines.append(line)

    for line in stock_macros.strip().splitlines():
        sym = line.split()[1].split("(")[0]
        if sym in defines:
            del defines[sym]

    return "".join(defines.values()) + "".join(source_lines)

def main():
    parser = argparse.ArgumentParser(
        description="""Create a context file which can be used for m2c / decomp.me"""
    )
    parser.add_argument(
        "c_file",
        help="""File from which to create context""",
    )
    args = parser.parse_args()

    output = import_c_file(args.c_file)

    with open(os.path.join(root_dir, "ctx.c"), "w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()
