#!/usr/bin/env python3

import argparse
import os
import subprocess
import sys

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.join(script_dir, "..")
asm_dir = os.path.join(root_dir, "asm")
build_dir = os.path.join(root_dir, "build")
elf_path = os.path.join(build_dir, "dkr.us.v77.elf")

def get_func_sizes():
    try:
        result = subprocess.run(["objdump", "-x", elf_path], stdout=subprocess.PIPE)
        nm_lines = result.stdout.decode().split("\n")
    except:
        print(
            f"Error: Could not run objdump on {elf_path} - make sure that the project is built"
        )
        sys.exit(1)

    sizes = {}
    total = 0

    for line in nm_lines:
        #This will filter out "weak" functions like fcos.
        if "g     F" in line or "l     F" in line:
            components = line.split()
            size = int(components[4], 16)
            name = components[5]
            if not name.startswith(".L") or not name.startswith("D_"):
                total += size
                sizes[name] = size

    return sizes, total

def get_nonmatching_funcs():
    funcs = set()

    for root, dirs, files in os.walk(asm_dir):
        for f in files:
            if f.endswith(".s") and not f.startswith(".L"):
                funcs.add(f[:-2])

    return funcs

def get_funcs_sizes(sizes, matchings, nonmatchings):
    msize = 0
    nmsize = 0

    for func in matchings:
        msize += sizes[func]

    for func in nonmatchings:
        if func not in sizes:
            pass
            # print(func)
        else:
            nmsize += sizes[func]

    return msize, nmsize

def lerp(a, b, alpha):
    return a + (b - a) * alpha

def main(args):
    func_sizes, total_size = get_func_sizes()
    all_funcs = set(func_sizes.keys())

    nonmatching_funcs = get_nonmatching_funcs()
    matching_funcs = all_funcs - nonmatching_funcs

    matching_size, nonmatching_size = get_funcs_sizes(
        func_sizes, matching_funcs, nonmatching_funcs
    )

    if len(all_funcs) == 0:
        funcs_matching_ratio = 0.0
        matching_ratio = 0.0
    else:
        funcs_matching_ratio = (len(matching_funcs) / len(all_funcs)) * 100
        matching_ratio = (matching_size / total_size) * 100

    if args.shield_json:
        import json
        from colour import Color

        # https://shields.io/endpoint
        color = Color("#50ca22", hue=lerp(0, 105/255, matching_ratio / 100))
        print(json.dumps({
            "schemaVersion": 1,
            "label": f"progress",
            "message": f"{matching_ratio:.2f}%",
            "color": color.hex,
        }))
    else:
        if matching_size + nonmatching_size != total_size:
            print("Warning: category/total size mismatch!\n")
        print(
            f"{len(matching_funcs)} matched functions / {len(all_funcs)} total ({funcs_matching_ratio:.2f}%)"
        )
        print(
            f"{matching_size} matching bytes / {total_size} total ({matching_ratio:.2f}%)"
        )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Calculate the progress of the project"
    )
    parser.add_argument("--shield-json", action="store_true")
    args = parser.parse_args()

    main(args)
