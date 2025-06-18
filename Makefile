BASENAME  = dkr
REGION  := us
VERSION  := v77
NON_MATCHING ?= 0

# NM is shorthand for NON_MATCHING
ifneq ($(NM),)
	NON_MATCHING := 1
endif

# Experimental option for nonmatching builds. GCC may not function identically to ido.
COMPILER ?= ido
$(eval $(call validate-option,NON_MATCHING,ido gcc))

# Define a custom boot file if desired to use something other than the vanilla one
BOOT_CUSTOM ?= mods/boot_custom.bin

LIBULTRA_VERSION_DEFINE := -DBUILD_VERSION=4 -DBUILD_VERSION_STRING=\"2.0G\"

# Whether to hide commands or not
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
  V := @
endif

PRINT = printf
GREP  = grep -rl

# Colors

# Whether to colorize build messages
COLOR ?= 1
GCC_COLOR := -fno-diagnostics-color

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
PINK    := \033[0;35m
CYAN    := \033[0;36m
COLORIZE := -c
GCC_COLOR :=
endif

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

# Directories
BIN_DIRS  = assets
BUILD_DIR = build
SRC_DIR   = src
LIBULTRA_DIR = libultra
ASM_DIRS  = asm asm/data asm/assets asm/nonmatchings
HASM_DIRS = $(SRC_DIR)/hasm $(LIBULTRA_DIR)/src/os $(LIBULTRA_DIR)/src/gu $(LIBULTRA_DIR)/src/libc
LIBULTRA_SRC_DIRS  = $(LIBULTRA_DIR) $(LIBULTRA_DIR)/src $(LIBULTRA_DIR)/src/audio $(LIBULTRA_DIR)/src/audio/mips1 
LIBULTRA_SRC_DIRS += $(LIBULTRA_DIR)/src/debug $(LIBULTRA_DIR)/src/gu $(LIBULTRA_DIR)/src/io
LIBULTRA_SRC_DIRS += $(LIBULTRA_DIR)/src/libc $(LIBULTRA_DIR)/src/os $(LIBULTRA_DIR)/src/sc

# Files requiring pre/post-processing
GLOBAL_ASM_C_FILES := $(shell $(GREP) GLOBAL_ASM $(SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_O_FILES := $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file).o)

SRC_DIRS = $(SRC_DIR) $(LIBULTRA_SRC_DIRS)
SYMBOLS_DIR = ver/symbols

TOOLS_DIR = tools

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(OS),Windows_NT)
	$(error Native Windows is currently unsupported for building this repository, use WSL instead c:)
else ifeq ($(UNAME_S),Linux)
	ifneq ($(filter aarch%,$(UNAME_M)),)
		DETECTED_OS := linux-arm
	else
		DETECTED_OS := linux
	endif
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := macos
endif

RECOMP_DIR := $(TOOLS_DIR)/ido-recomp/$(DETECTED_OS)

# Files

S_FILES         = $(foreach dir,$(ASM_DIRS) $(HASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES         = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
BIN_FILES       = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))

O_FILES := $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

O_FILES_LD := $(filter-out $(BUILD_DIR)/asm/assets/assets.s.o, \
	$(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
	$(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o))

find-command = $(shell which $(1) 2>/dev/null)

# Tools

ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips-linux-gnu-
else ifeq ($(shell type mips64-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-linux-gnu-
else ifeq ($(shell type mips64-elf-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-elf-
else
# No binutil packages were found, so we have to download the source & build it.
ifeq ($(wildcard $(TOOLS_DIR)/binutils/.*),)
  DUMMY != $(TOOLS_DIR)/get-binutils.sh >&2 || echo FAIL
endif 
  CROSS := $(TOOLS_DIR)/binutils/mips64-elf-
endif

AS       = $(CROSS)as
LD       = $(CROSS)ld
OBJCOPY  = $(CROSS)objcopy
VENV     = .venv
PYTHON   = $(VENV)/bin/python3
GCC      = gcc

#Options
CC       = $(RECOMP_DIR)/cc
SPLAT    ?= $(PYTHON) -m splat split
CRC      = $(TOOLS_DIR)/n64crc $(BUILD_DIR)/$(BASENAME).$(REGION).$(VERSION).z64 $(COLORIZE)
FIXCHECKSUMS = $(PYTHON) $(TOOLS_DIR)/python/calc_func_checksums.py $(REGION) $(VERSION)

OPT_FLAGS      = -O2

MIPSISET       = -mips1

DEFINES := _FINALROM NDEBUG TARGET_N64 F3DDKR_GBI
DEFINES += VERSION_$(REGION)_$(VERSION)
MATCHDEFS := 

VERIFY = verify

ifeq ($(NON_MATCHING),1)
	MATCHDEFS += NON_MATCHING=1
	MATCHDEFS += AVOID_UB=1
	VERIFY = no_verify
	MIPSISET = -mips2
	C_STANDARD := -std=gnu99
else
	MATCHDEFS += ANTI_TAMPER=1
    # Override compiler choice on matching builds.
	COMPILER := ido
	C_STANDARD := -std=gnu90
endif

DEFINES += $(MATCHDEFS)
C_DEFINES := $(foreach d,$(DEFINES),-D$(d)) $(LIBULTRA_VERSION_DEFINE) -D_MIPS_SZLONG=32
ASM_DEFINES = $(foreach d,$(DEFINES),$(if $(findstring =,$(d)),--defsym $(d),)) --defsym _MIPS_SIM=1 --defsym mips=1 --defsym VERSION_$(REGION)_$(VERSION)=1

# If NON_MATCHING and using a custom boot file, (Right now just 6102).
# Define this so it will change the entrypoint in the header
BOOT_CIC :=
ifeq ($(NON_MATCHING),1)
ifeq ("$(wildcard $(BOOT_CUSTOM))","")
	BOOT_CIC := 6103
else
# Determine the CIC type automatically by checking the boot bin.
	BOOT_CIC := $(shell $(PYTHON) $(TOOLS_DIR)/python/extract_custom_boot.py)
# The above returns 0 if it errors out, so course correct if it somehow happens.
	ifeq ($(BOOT_CIC),0)
		BOOT_CIC := 6103
	endif
endif
else
	BOOT_CIC := 6103
endif

ASM_DEFINES += --defsym BOOT_$(BOOT_CIC)=1

C_DEFINES += -DCIC_ID=$(BOOT_CIC)

INCLUDE_CFLAGS  = -I . -I include -I include/libc  -I include/PR -I include/sys -I $(BIN_DIRS) -I $(SRC_DIR) -I $(LIBULTRA_DIR)
INCLUDE_CFLAGS += -I $(LIBULTRA_DIR)/src/gu -I $(LIBULTRA_DIR)/src/libc -I $(LIBULTRA_DIR)/src/io  -I $(LIBULTRA_DIR)/src/sc 
INCLUDE_CFLAGS += -I $(LIBULTRA_DIR)/src/audio -I $(LIBULTRA_DIR)/src/os

ASFLAGS        = -march=vr4300 -32 -G0 $(ASM_DEFINES) $(INCLUDE_CFLAGS)
OBJCOPYFLAGS   = -O binary

# Pad to 12MB if matching, otherwise build to a necessary minimum of 1.004MB
ifeq ($(NON_MATCHING),1)
  OBJCOPYFLAGS += --pad-to=0x101000 --gap-fill=0xFF
else
  OBJCOPYFLAGS += --pad-to=0xC00000 --gap-fill=0xFF
endif


#IDO Warnings to Ignore. These are coding style warnings we don't follow
CC_WARNINGS := -fullwarn -Xfullwarn -woff 838,649,624,835,516

CFLAGS := -G 0 -non_shared -verbose -Xcpluscomm -nostdinc -Wab,-r4300_mul
CFLAGS += $(C_DEFINES)
CFLAGS += $(INCLUDE_CFLAGS)

CHECK_WARNINGS := -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-parameter -Wno-switch -Werror-implicit-function-declaration
ifeq ($(DETECTED_OS), macos)
	ifeq ($(NON_MATCHING),0)
		CHECK_WARNINGS += -Wno-unused-value -Wno-deprecated-non-prototype -Wno-array-bounds -Wno-self-assign -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-variable
		CHECK_WARNINGS += -Wno-pointer-to-int-cast -Wno-constant-conversion -Wno-int-to-pointer-cast
	endif
else
	ifeq ($(NON_MATCHING),0)
		CHECK_WARNINGS += -Wno-unused-variable -Wno-unused-value -Wno-unused-but-set-variable
	endif
endif
CC_CHECK := $(GCC) -fsyntax-only -fno-builtin -funsigned-char $(C_STANDARD) -DAVOID_UB -DCC_CHECK -D_LANGUAGE_C -DNON_MATCHING -DNON_EQUIVALENT $(CHECK_WARNINGS) $(INCLUDE_CFLAGS) $(C_DEFINES) $(GCC_COLOR)

# Only add -m32 for x86_64 machines.
ifneq ($(filter x86_64%,$(UNAME_M)),)
	CC_CHECK += -m32
endif

TARGET     = $(BUILD_DIR)/$(BASENAME).$(REGION).$(VERSION)
LD_FLAGS  :=
ifeq ($(NON_MATCHING), 0)
LD_SCRIPT  = ver/$(BASENAME).$(REGION).$(VERSION).ld
else
LD_SCRIPT  = mods/dkr.custom.ld
LD_FLAGS += $(O_FILES_LD)
endif

LD_FLAGS   += -T $(LD_SCRIPT) -T $(SYMBOLS_DIR)/undefined_syms.txt -Map $(TARGET).map

ASM_PROCESSOR_DIR := $(TOOLS_DIR)/asm-processor
ASM_PROCESSOR      = $(PYTHON) $(ASM_PROCESSOR_DIR)/build.py

### Optimisation Overrides
####################### LIBULTRA #########################

ifeq ($(COMPILER),ido)
$(BUILD_DIR)/$(LIBULTRA_DIR)/%.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/audio/%.c.o: OPT_FLAGS := -O3
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/audio/mips1/%.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/os/%.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/io/%.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/io/vimgr.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/io/pimgr.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/io/motor.c.o: OPT_FLAGS := -O2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/xprintf.c.o : OPT_FLAGS := -O3
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/audio/env.c.o: OPT_FLAGS := -g
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/llcvt.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/llcvt.c.o: MIPSISET := -mips3 -32
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/ll.c.o: OPT_FLAGS := -O1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/ll.c.o: MIPSISET := -mips3 -32
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/ldiv.c.o: OPT_FLAGS := -O3
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/ldiv.c.o: MIPSISET := -mips2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/xldtob.c.o: OPT_FLAGS := -O3
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/xldtob.c.o: MIPSISET := -mips2

$(BUILD_DIR)/$(LIBULTRA_DIR)/%.c.o: MIPSISET := -mips2
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/audio/mips1/%.c.o: MIPSISET := -mips1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/io/pimgr.c.o: MIPSISET := -mips1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/sc/sched.c.o: MIPSISET := -mips1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/io/motor.c.o: MIPSISET := -mips1
$(BUILD_DIR)/$(LIBULTRA_DIR)/src/audio/env.c.o: MIPSISET := -mips1

#Ignore warnings for libultra files
$(BUILD_DIR)/$(LIBULTRA_DIR)/%.c.o: CC_WARNINGS := -w
$(BUILD_DIR)/$(LIBULTRA_DIR)/%.c.o: CC_CHECK := :

# Allow dollar sign to be used in var names for this file alone
# It allows us to return the current stack pointer
$(BUILD_DIR)/$(SRC_DIR)/get_stack_pointer.c.o: OPT_FLAGS += -dollar
endif

### Targets

ifeq ($(COMPILER),gcc)
	DUMMY != $(PYTHON) $(TOOLS_DIR)/python/gcc_generate.py gcc_safe_files.mk
	include gcc_safe_files.mk
endif

$(GCC_SAFE_FILES): CC := $(CROSS)gcc
$(GCC_SAFE_FILES): CC_WARNINGS := 
$(GCC_SAFE_FILES): MIPSISET := -mips3
$(GCC_SAFE_FILES): OPT_FLAGS := -Os
$(GCC_SAFE_FILES): CFLAGS := -DNDEBUG -DAVOID_UB -DNON_MATCHING $(INCLUDE_CFLAGS) $(C_DEFINES) \
	-EB \
	-march=vr4300 \
	-mabi=32 \
	-mno-check-zero-division \
	-mno-abicalls \
	-mgp32 \
	-mfp32 \
	-mhard-float \
	-ffreestanding \
	-fno-builtin \
	-fno-common \
	-mno-long-calls \
	-ffast-math \
	-funsafe-math-optimizations \
	-fno-merge-constants \
	-fno-strict-aliasing \
	-fno-zero-initialized-in-bss \
	-fsingle-precision-constant \
	-funsigned-char \
	-fwrapv \
	-falign-functions=16 \
	-G 0

default: all

all: $(VERIFY)

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(HASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

verify: $(TARGET).z64
	$(V)$(FIXCHECKSUMS)
	$(V)$(CRC)
ifeq ($(NON_MATCHING),0)
	@(sha1sum -c --quiet ver/verification/$(BASENAME).$(REGION).$(VERSION).sha1 \
	&& $(PRINT) "$(GREEN)Verify:$(NO_COL)\
	 $(YELLOW)OK$(NO_COL)\n")
	$(V)$(PRINT) "$(YELLOW)    __\n .\`_  _\`.\n| | \`| | |\n| |_|._| |\n \`. __ .\'$(NO_COL)\n\n"
else
	$(V)$(PRINT) "$(GREEN)Build Complete!$(NO_COL)\n"
endif

no_verify: $(TARGET).z64
	$(V)$(CRC)
	$(V)$(PRINT) "$(GREEN)Build Complete!$(NO_COL)\n"

extract:
	$(SPLAT) ver/splat/$(BASENAME).$(REGION).$(VERSION).yaml
	$(TOOLS_DIR)/dkr_assets_tool extract -dkrv $(REGION).$(VERSION) >&2 || echo FAIL

extractall:
	$(SPLAT) ver/splat/$(BASENAME).us.v77.yaml
	$(SPLAT) ver/splat/$(BASENAME).pal.v77.yaml
	$(SPLAT) ver/splat/$(BASENAME).jpn.v79.yaml
	$(SPLAT) ver/splat/$(BASENAME).us.v80.yaml
	$(SPLAT) ver/splat/$(BASENAME).pal.v80.yaml

setup:
#Set up a python venv so we don't get warnings about breaking system packages.
	$(V)python3 -m venv $(VENV)
#Installing the splat dependencies
	$(V)$(PYTHON) -m pip install -r requirements.txt
	$(V)$(PYTHON) ver/splat/update_baserom_names.py
	$(V)make -C $(TOOLS_DIR)

clean:
	rm -rf $(BUILD_DIR)

clean_src:
	rm -rf $(BUILD_DIR)/asm
	rm -rf $(BUILD_DIR)/libultra
	rm -rf $(BUILD_DIR)/src

clean_assets:
	rm -rf $(ASM_DIRS)
	rm -rf $(BIN_DIRS)
	
cleanall:
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(ASM_DIRS)
	rm -rf $(BIN_DIRS)
	rm -f $(SYMBOLS_DIR)/*auto.$(REGION).$(VERSION).txt
	rm -f ver/$(BASENAME).$(REGION).$(VERSION).ld

distcleanall: cleanall
	rm -rf asm
	rm -rf assets
	rm -f $(SYMBOLS_DIR)/*auto.*.txt
	rm -f ver/dkr.us.v77.ld
	rm -f ver/dkr.us.v80.ld
	rm -f ver/dkr.pal.v77.ld
	rm -f ver/dkr.pal.v80.ld
	rm -f ver/dkr.jpn.v79.ld
	rm -f $(SYMBOLS_DIR)/*auto.us.v77.txt
	rm -f $(SYMBOLS_DIR)/*auto.pal.v77.txt
	rm -f $(SYMBOLS_DIR)/*auto.jpn.v79.txt
	rm -f $(SYMBOLS_DIR)/*auto.us.v80.txt
	rm -f $(SYMBOLS_DIR)/*auto.pal.v80.txt

#When you just need to wipe old symbol names and re-extract
cleanextract: distclean extract

#Put the build folder into expected for use with asm-differ. Only run this with a matching build.
expected: verify
	mkdir -p expected
	rm -rf expected/$(BUILD_DIR)
	cp -r $(BUILD_DIR)/ expected/

#Run this to use the asset builder to customize assets
assets: all

ASSETS_OUTPUT := assets/assets.bin

ifeq ($(NON_MATCHING),1)
# The -m flag will attempt to compile assets. Only want to do this on non-matching builds.
MODDED_ARG := -m
endif

build_assets:
	$(info Building Assets...)
	@$(TOOLS_DIR)/dkr_assets_tool build -o $(ASSETS_OUTPUT) -dkrv $(REGION).$(VERSION) $(MODDED_ARG) >&2 || exit 1

###############################

$(GLOBAL_ASM_O_FILES): CC := $(ASM_PROCESSOR) $(CC) -- $(AS) $(ASFLAGS) --

$(TARGET).elf: dirs $(LD_SCRIPT) $(O_FILES) | build_assets
	@$(PRINT) "$(GREEN)Linking: $(BLUE)$@$(NO_COL)\n"
	$(V)$(LD) $(LD_FLAGS) -o $@

ifndef PERMUTER
$(GLOBAL_ASM_O_FILES): $(BUILD_DIR)/%.c.o: %.c | build_assets
	$(call print,Compiling:,$<,$@)
	$(V)$(CC_CHECK) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) -c $(CFLAGS) $(CC_WARNINGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
endif

# non asm-processor recipe
$(BUILD_DIR)/%.c.o: %.c | build_assets
	$(call print,Compiling:,$<,$@)
	$(V)$(CC_CHECK) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) -c $(CFLAGS) $(CC_WARNINGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/llcvt.c.o: $(LIBULTRA_DIR)/src/libc/llcvt.c | build_assets
	$(call print,Compiling mips3:,$<,$@)
	@$(CC) -c $(CFLAGS) $(CC_WARNINGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(V)$(PYTHON) $(TOOLS_DIR)/python/patchmips3.py $@ || rm $@

$(BUILD_DIR)/$(LIBULTRA_DIR)/src/libc/ll.c.o: $(LIBULTRA_DIR)/src/libc/ll.c | build_assets
	$(call print,Compiling mips3:,$<,$@)
	@$(CC) -c $(CFLAGS) $(CC_WARNINGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(V)$(PYTHON) $(TOOLS_DIR)/python/patchmips3.py $@ || rm $@

$(BUILD_DIR)/%.s.o: %.s | build_assets
	$(call print,Assembling:,$<,$@)
	$(V)$(AS) $(ASFLAGS) -MD $(BUILD_DIR)/$*.d -o $@ $< 

# Specifically override the header file from what splat extracted to be replaced by what we have in the hasm folder
$(BUILD_DIR)/asm/header.s.o: src/hasm/header.s | build_assets
	$(call print,Assembling Header:,$<,$@)
	$(V)$(AS) $(ASFLAGS) -o $(BUILD_DIR)/asm/header.s.o $<

ifeq ($(NON_MATCHING),1)
# If doing a NON_MATCHING build, and the custom boot file exists, use that.
ifneq ("$(wildcard $(BOOT_CUSTOM))","")
$(BUILD_DIR)/assets/boot.bin.o: $(BOOT_CUSTOM) | build_assets
	$(call print,Linking Custom Boot:,$<,$@)
	$(V)$(LD) -r -b binary -o $@ $<
endif
endif

$(BUILD_DIR)/%.bin.o: %.bin | build_assets
	$(call print,Linking Binary:,$<,$@)
	$(V)$(LD) -r -b binary -o $@ $<

$(TARGET).bin: $(TARGET).elf | build_assets
	$(call print,Objcopy:,$<,$@)
	$(V)$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

$(TARGET).z64: $(TARGET).bin | build_assets
	$(call print,CopyRom:,$<,$@)
	$(V)$(PYTHON) $(TOOLS_DIR)/python/CopyRom.py $< $@

### Settings
.PHONY: all clean cleanextract default assets
SHELL = /bin/bash -e -o pipefail

-include $(BUILD_DIR)/**/*.d
