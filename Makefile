# Makefile to build DKR

############################ Shell ###########################

SHELL := /bin/bash

################## Preprocessor definitions ##################

# Currently, only US 1.0 is supported.
VERSION := us_1.0

NON_MATCHING ?= 0
$(eval $(call validate-option,NON_MATCHING,0 1))

COMPILE_ASSETS ?= 0
$(eval $(call validate-option,COMPILE_ASSETS,0 1))

ifeq ($(COMPILE_ASSETS),1)
  DUMMY != ./tools/dkr_assets_tool -c $(VERSION) ./assets >&2 || echo FAIL
  ifeq ($(DUMMY),FAIL)
    $(error Failed to compile assets)
  endif
endif

ifeq ($(VERSION),us_1.0)
  DEFINES += VERSION_US_1_0=1
endif
ifeq ($(NON_MATCHING),1)
  DEFINES += NON_MATCHING=1
endif
ifeq ($(NON_EQUIVALENT),1)
  DEFINES += NON_EQUIVALENT=1
  DEFINES += NON_MATCHING=1
  NON_MATCHING = 1
endif

# Whether to hide commands or not
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
  V := @
endif

# Whether to colorize build messages
COLOR ?= 1

############################ Setup ###########################

# Don't do setup checks if cleaning.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),clean_lib)
ifneq ($(MAKECMDGOALS),clean_src)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),reset)

################ Check if a baserom exists  ################

numberOfFilesInBaseromsDirectory := $(words $(wildcard baseroms/*))
ifeq ($(shell test $(numberOfFilesInBaseromsDirectory) -lt 1; echo $$?),0)
  $(error Make sure you have a DKR rom in the /baseroms/ directory)
endif

########## Make tools ##########

DUMMY != make -s -C tools >&2 || echo FAIL
ifeq ($(DUMMY),FAIL)
  $(error Failed to build tools)
endif

PRINT = printf

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
YELLOW  := \033[0;33m
BLINK   := \033[33;5m
endif

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

########## Recomp ##########

RECOMP_PROJECT := ./tools/ido-static-recomp/

DUMMY != ls $(RECOMP_PROJECT)ido >/dev/null || echo FAIL
ifeq ($(DUMMY),FAIL)
DUMMY != git submodule update --init
DUMMY != ls $(RECOMP_PROJECT)ido >/dev/null || echo FAIL
ifeq ($(DUMMY),FAIL)
$(error Missing submodule ido-static-recomp. Please run 'git submodule update --init')
endif
endif

# List of IDO tools required for the repo.
# NOTE: If you are adding a tool here, make sure to update the Makefile in `/tools/ido-static-recomp/`!
RECOMP_TOOLS := cc cfe uopt ugen as1 ujoin uld usplit umerge

RECOMP_DIR := $(RECOMP_PROJECT)build5.3/out/
RECOMP_TOOLS_PATHS = $(addprefix $(RECOMP_DIR),$(RECOMP_TOOLS))

# Checks if all the recomp tools exist.
$(foreach p,$(RECOMP_TOOLS_PATHS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(eval runRecomp:=yes)))

# If any of the tools do not exist, then recomp needs to run to build them.
ifeq ($(runRecomp),yes)
  DUMMY != cd $(RECOMP_PROJECT) && python3 build.py ido/5.3 -O2 && cp build5.3/out/usr/bin/cc build5.3/out/cc && cp build5.3/out/usr/lib/* build5.3/out/ && cd ../../ >&2 || echo FAIL
endif

######## Extract Assets & Microcode ########

DUMMY != python3 ./tools/python/check_if_need_to_extract.py $(VERSION) >&2 || echo FAIL

################################

endif
endif
endif
endif
endif
################ Target Executable and Sources ###############

# BUILD_DIR is location where all build artifacts are placed
# TODO: Support other versions of DKR
BUILD_DIR = build/$(VERSION)

##################### Compiler Options #######################

# Check if a binutils package is installed on the system.
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips-linux-gnu-
else ifeq ($(shell type mips64-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-linux-gnu-
else ifeq ($(shell type mips64-elf-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-elf-
else
# No binutil packages were found, so we have to download the source & build it.
ifeq ($(wildcard ./tools/binutils/.*),)
  DUMMY != ./tools/get-binutils.sh >&2 || echo FAIL
endif 
  CROSS := ./tools/binutils/mips64-elf-
endif

AS = $(CROSS)as
CC := $(RECOMP_DIR)cc
CPP := cpp -P -Wno-trigraphs
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
# Pad to 12MB if matching, otherwise build to a necessary minimum of 1.04KB
ifeq ($(NON_MATCHING),0)
  OBJCOPY = $(CROSS)objcopy --pad-to=0xC00000 --gap-fill=0xFF
else
  OBJCOPY = $(CROSS)objcopy --pad-to=0x101000 --gap-fill=0xFF
endif

MIPSISET := -mips1
OPT_FLAGS := -O2 -Xfullwarn #include -Xfullwarn here since it's not supported with -O3

INCLUDE_DIRS := include $(BUILD_DIR) $(BUILD_DIR)/include src include/libc .

C_DEFINES := $(foreach d,$(DEFINES),-D$(d))
DEF_INC_CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(C_DEFINES)


#IDO Warnings to Ignore. These are coding style warnings we don't follow
IDO_IGNORE_WARNINGS = -woff 838,649,624
ASFLAGS = -mtune=vr4300 -march=vr4300 -mabi=32 $(foreach d,$(DEFINES),--defsym $(d))
INCLUDE_CFLAGS := -I include -I $(BUILD_DIR) -I src -I . -I include/libc
CFLAGS = -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -DNDEBUG $(OPT_FLAGS) $(MIPSISET) $(INCLUDE_CFLAGS) $(DEF_INC_CFLAGS) $(IDO_IGNORE_WARNINGS)
LDFLAGS = undefined_syms.txt -T $(LD_SCRIPT) -Map $(BUILD_DIR)/dkr.map

####################### Other Tools #########################

# N64 tools
TOOLS_DIR = ./tools
EMULATOR = mupen64plus
EMU_FLAGS = --noosd
LOADER = loader64
LOADER_FLAGS = -vwf

FixPath = $(subst /,,$1)

N64CRC = $(TOOLS_DIR)/n64crc
FIXCHECKSUMS = python3 $(TOOLS_DIR)/python/calc_func_checksums.py $(VERSION)
COMPRESS = $(TOOLS_DIR)/dkr_assets_tool -fc
BUILDER = $(TOOLS_DIR)/dkr_assets_tool -b $(VERSION) ./assets

LIB_DIRS := lib/
ASM_DIRS := asm/ asm/boot/ asm/assets/ lib/asm/ lib/asm/non_decompilable
SRC_DIRS := $(sort $(dir $(wildcard src/* src/**/*))) $(sort $(dir $(wildcard lib/src/* lib/src/**/* lib/src/**/**/*)))

GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(SRC_DIRS)
GLOBAL_ASM_O_FILES = $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)*.s))
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)*.c))

# Object files
O_FILES := 	$(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
            $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o))
			
# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) $(BUILD_DIR)/$(LD_SCRIPT).d
			
# Check code syntax with host compiler
CC_CHECK := gcc
ifeq ($(shell getconf LONG_BIT), 64)
  # Ensure that gcc treats the code as 32-bit
  CC_CHECK_CFLAGS += -m32
endif
CC_CHECK_CFLAGS := -fsyntax-only -fsigned-char $(INCLUDE_CFLAGS) $(DEF_INC_CFLAGS) -std=gnu90 -Wall -Wextra -Wno-format-security -Wno-main -DNON_MATCHING -DAVOID_UB -D_LANGUAGE_C -DNDEBUG

#Warnings to ignore
CC_CHECK_CFLAGS += -Wno-builtin-declaration-mismatch -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

####################### ASSETS #########################

# All the asset subfolders to create in the build folder.
ASSETS_DIRS := audio bin fonts ids levels levels/headers levels/models levels/names levels/objectMaps misc objects objects/animations objects/headers objects/models particles particles/behaviors particles/particles sprites text text/game text/menu textures textures/2d textures/3d tt_ghosts unknown_0 ucode

DUMMY != mkdir -p $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(LIB_DIRS) $(ASM_DIRS) $(SRC_DIRS) $(ASSETS_DIRS)) >&2 || echo FAIL

ASSETS_DIR = assets/$(VERSION)
UCODE_DIR = ucode/$(VERSION)

ASSETS_COPY = cp

# Makes name uppercase, and also replaces '/' with '_' for subfolders.
# Doing all those subst calls *should* be faster than `$(shell echo '$1' | tr '[:lower:]' '[:upper:]')
GET_VAR_NAME = $(subst /,_,$(subst a,A,$(subst b,B,$(subst c,C,$(subst d,D,$(subst e,E,$(subst f,F,$(subst g,G,$(subst h,H,$(subst i,I,$(subst j,J,$(subst k,K,$(subst l,L,$(subst m,M,$(subst n,N,$(subst o,O,$(subst p,P,$(subst q,Q,$(subst r,R,$(subst s,S,$(subst t,T,$(subst u,U,$(subst v,V,$(subst w,W,$(subst x,X,$(subst y,Y,$(subst z,Z,$1)))))))))))))))))))))))))))

# $1 = Input/Output directories name
define DEFINE_BINARY_FILES
ALL_ASSETS_BUILT += $(patsubst $($1_IN_DIR)/%.bin,$($1_OUT_DIR)/%.bin,$(wildcard $($1_IN_DIR)/*.bin))
endef
# $1 = Input/Output directories name
define DEFINE_COMPRESSED_BINARY_FILES
ALL_ASSETS_BUILT += $(patsubst $($1_IN_DIR)/%.cbin,$($1_OUT_DIR)/%.bin,$(wildcard $($1_IN_DIR)/*.cbin))
endef
# $1 = Input/Output directories name
define DEFINE_JSON_FILES
ALL_ASSETS_BUILT += $(patsubst $($1_IN_DIR)/%.json,$($1_OUT_DIR)/%.bin,$(wildcard $($1_IN_DIR)/*.json))
endef
# $1 = Input/Output directories name
define DEFINE_JSON_AND_BINARY_FILES
$(eval $(call DEFINE_JSON_FILES,$1))
$(eval $(call DEFINE_BINARY_FILES,$1))
endef

# $1 = folder name, $2 = define function
define DEFINE_SECTION_FILES
$(eval VAR_NAME := $(call GET_VAR_NAME,$1))
$(eval $(VAR_NAME)_IN_DIR = $(ASSETS_DIR)/$1)
$(eval $(VAR_NAME)_OUT_DIR = $(BUILD_DIR)/$1)
$(eval $(call $2,$(VAR_NAME)))
endef

###### Define section files into the ALL_ASSETS_BUILT variable ######

$(call DEFINE_SECTION_FILES,audio,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,bin,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,fonts,DEFINE_JSON_AND_BINARY_FILES)
$(call DEFINE_SECTION_FILES,ids,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,levels,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,levels/headers,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,levels/models,DEFINE_COMPRESSED_BINARY_FILES)
$(call DEFINE_SECTION_FILES,levels/names,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,levels/objectMaps,DEFINE_COMPRESSED_BINARY_FILES)
$(call DEFINE_SECTION_FILES,misc,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,objects,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,objects/animations,DEFINE_COMPRESSED_BINARY_FILES)
$(call DEFINE_SECTION_FILES,objects/headers,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,objects/models,DEFINE_COMPRESSED_BINARY_FILES)
$(call DEFINE_SECTION_FILES,particles/behaviors,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,particles/particles,DEFINE_BINARY_FILES)
$(call DEFINE_SECTION_FILES,sprites,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,text/game,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,text/menu,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,textures/2d,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,textures/3d,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,tt_ghosts,DEFINE_JSON_FILES)
$(call DEFINE_SECTION_FILES,unknown_0,DEFINE_BINARY_FILES)

# Microcode
UCODE_IN_DIR = $(UCODE_DIR)
UCODE_OUT_DIR = $(BUILD_DIR)/ucode
UCODE = $(wildcard $(UCODE_IN_DIR)/*.bin)
ALL_ASSETS_BUILT += $(patsubst $(UCODE_IN_DIR)/%.bin,$(UCODE_OUT_DIR)/%.bin,$(UCODE))

####################### LIBULTRA #########################

$(BUILD_DIR)/lib/%.o: OPT_FLAGS := -O2 -Xfullwarn
$(BUILD_DIR)/lib/src/al/%.o: OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/os/%.o: OPT_FLAGS := -O1 -Xfullwarn
$(BUILD_DIR)/lib/src/os/osViMgr.o: OPT_FLAGS := -O2 -Xfullwarn
$(BUILD_DIR)/lib/src/os/osCreatePiManager.o: OPT_FLAGS := -O2 -Xfullwarn
$(BUILD_DIR)/lib/src/os/osMotor.o: OPT_FLAGS := -O2 -Xfullwarn
$(BUILD_DIR)/lib/src/libc/xprintf.o : OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/al/env.o: OPT_FLAGS := -g
#$(BUILD_DIR)/lib/src/libc/llcvt.o: OPT_FLAGS :=
#$(BUILD_DIR)/lib/src/libc/llcvt.o: MIPSISET := -mips3 32

$(BUILD_DIR)/lib/%.o: MIPSISET := -mips2
$(BUILD_DIR)/lib/src/mips1/%.o: MIPSISET := -mips1
$(BUILD_DIR)/lib/src/os/osMotor.o: MIPSISET := -mips1
$(BUILD_DIR)/lib/src/al/env.o: MIPSISET := -mips1

####################### MATH UTIL #########################

$(BUILD_DIR)/src/math_util.o: MIPSISET := -mips2

######################## Targets #############################

default: all

TARGET = dkr
LD_SCRIPT = $(TARGET).ld

all: $(BUILD_DIR)/$(TARGET).z64

reset: 
ifneq ($(wildcard ./build/.*),) 
	rm -r build
endif 
ifneq ($(wildcard ./assets/.*),) 
	rm -r assets
endif 
ifneq ($(wildcard ./ucode/.*),) 
	rm -r ucode
endif 
	@echo "Done." 

clean: 
ifneq ($(wildcard ./build/.*),) 
	rm -r build
	rm -r dkr.ld
else 
	@echo "/build/ directory has already been deleted." 
endif

distclean:
	rm -rf build
	rm -rf assets
	rm -rf ucode
	rm -rf dkr.ld
	rm -rf tools/ido-static-recomp/{,.[!.],..?}* # Deletes all files, including hidden ones.
	$(MAKE) -C tools distclean
    
clean_lib:
ifneq ($(wildcard $(BUILD_DIR)/lib/.*),)
	rm -r $(BUILD_DIR)/lib/src/*/*.o
else 
	@echo "build lib directory has already been deleted." 
endif 

clean_src: clean_lib
ifneq ($(wildcard $(BUILD_DIR)/src/.*),)
	rm -r $(BUILD_DIR)/src/*.o
else 
	@echo "/build/lib directory has already been deleted." 
endif 

# Helps fix an issue with parallel jobs.
$(ALL_ASSETS_BUILT): | $(BUILD_DIR)

# This is here to prevent make from deleting all the asset files after the build completes/fails.
dont_remove_asset_files: $(ALL_ASSETS_BUILT)

######## Asset Targets ########

$(BUILD_DIR)/enumsCache.bin: include/enums.h
	$(call print,Building enums.h cache:,$<,$@)
	$(V)$(TOOLS_DIR)/dkr_assets_tool -bc $(VERSION) $<

dkr.ld: $(BUILD_DIR)/enumsCache.bin
	@$(PRINT) "$(YELLOW)Generating Linker File...$(NO_COL)\n"
	$(V)./generate_ld.sh $(VERSION)

ALL_ASSETS_BUILT += dkr.ld # This is a hack, but it works I guess.

# All assets should output a .bin file

# $1 = folder name, $2 = Print Message
define CREATE_BINARY_ASSET_TARGET
$(eval VAR_NAME := $(call GET_VAR_NAME,$1))
$$($$(VAR_NAME)_OUT_DIR)/%.bin: $$($$(VAR_NAME)_IN_DIR)/%.bin
	$$(call print,$2:,$$<,$$@)
	$$(V)$$(ASSETS_COPY) $$^ $$@
endef

# $1 = folder name, $2 = Print Message
define CREATE_COMPRESSED_ASSET_TARGET
$(eval VAR_NAME := $(call GET_VAR_NAME,$1))
$$($$(VAR_NAME)_OUT_DIR)/%.bin: $$($$(VAR_NAME)_IN_DIR)/%.cbin
	$$(call print,$2:,$$<,$$@)
	$$(V)$$(COMPRESS) $$^ $$@
endef

# $1 = folder name, $2 = Print Message
define CREATE_JSON_ASSET_TARGET
$(eval VAR_NAME := $(call GET_VAR_NAME,$1))
$$($$(VAR_NAME)_OUT_DIR)/%.bin: $$($$(VAR_NAME)_IN_DIR)/%.json $(BUILD_DIR)/enumsCache.bin
	$$(call print,$2:,$$<,$$@)
	$$(V)$$(BUILDER) $$< $$@
endef

$(eval $(call CREATE_BINARY_ASSET_TARGET,audio,Copying Audio Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,bin,Copying Bin Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,fonts,Copying Fonts Binary))
$(eval $(call CREATE_JSON_ASSET_TARGET,fonts,Building Fonts))
$(eval $(call CREATE_BINARY_ASSET_TARGET,ids,Copying IDs Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,levels,Copying Levels Binary))
$(eval $(call CREATE_JSON_ASSET_TARGET,levels/headers,Building Level Header))
$(eval $(call CREATE_COMPRESSED_ASSET_TARGET,levels/models,Compressing Level Model Binary))
$(eval $(call CREATE_JSON_ASSET_TARGET,levels/names,Building Level Name))
$(eval $(call CREATE_COMPRESSED_ASSET_TARGET,levels/objectMaps,Compressing Level Object Map Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,misc,Copying Misc Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,objects,Copying Object Binary))
$(eval $(call CREATE_COMPRESSED_ASSET_TARGET,objects/animations,Compressing Object Animation Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,objects/headers,Copying Object Header Binary))
$(eval $(call CREATE_COMPRESSED_ASSET_TARGET,objects/models,Compressing Object Model Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,particles/behaviors,Copying Particle Behavior Binary))
$(eval $(call CREATE_BINARY_ASSET_TARGET,particles/particles,Copying Particle Binary))
$(eval $(call CREATE_JSON_ASSET_TARGET,sprites,Building Sprite))
$(eval $(call CREATE_JSON_ASSET_TARGET,text/game,Building Game Text))
$(eval $(call CREATE_JSON_ASSET_TARGET,text/menu,Building Menu Text))
$(eval $(call CREATE_JSON_ASSET_TARGET,textures/2d,Building Texture (2D)))
$(eval $(call CREATE_JSON_ASSET_TARGET,textures/3d,Building Texture (3D)))
$(eval $(call CREATE_JSON_ASSET_TARGET,tt_ghosts,Building T.T. Ghost))
$(eval $(call CREATE_BINARY_ASSET_TARGET,unknown_0,Copying Unknown_0 Binary))
    
# Microcode target
$(UCODE_OUT_DIR)/%.bin: $(UCODE_IN_DIR)/%.bin
	$(call print,Copying:,$<,$@)
	$(V)$(ASSETS_COPY) $^ $@
    
###############################

$(BUILD_DIR)/%.o: %.s | $(ALL_ASSETS_BUILT)
	$(call print,Assembling:,$<,$@)
	$(V)$(AS) $(ASFLAGS) -MD $(BUILD_DIR)/$*.d -o $@ $<
	
$(BUILD_DIR)/%.o: %.c | $(ALL_ASSETS_BUILT)
	$(call print,Compiling:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) $(CFLAGS) -o $@ $<
	
$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c | $(ALL_ASSETS_BUILT)
	$(call print,Compiling:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT) | $(ALL_ASSETS_BUILT)
	$(call print,Preprocessing linker script:,$<,$@)
	$(V)$(CPP) $(VERSION_CFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

$(BUILD_DIR)/$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT) | $(ALL_ASSETS_BUILT)
	@$(PRINT) "$(GREEN)Linking ELF file: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) $(LDFLAGS) -o $@ $(O_FILES) $(LIBS)

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf | $(ALL_ASSETS_BUILT)
	$(call print,Making .bin:,$<,$@)
	$(V)$(OBJCOPY) $< $@ -O binary

$(BUILD_DIR)/$(TARGET).z64: $(BUILD_DIR)/$(TARGET).bin | $(ALL_ASSETS_BUILT)
	$(call print,Making final z64 ROM:,$<,$@)
	$(V)cp $< $@
	$(V)$(FIXCHECKSUMS)
	$(V)$(N64CRC) $@
ifeq ($(NON_MATCHING),0)
	@(sha1sum -c --quiet sha1/dkr.$(VERSION).sha1 \
	&& $(PRINT) "$(BLUE)$@$(NO_COL)\
	: $(GREEN)OK$(NO_COL)\n")
	@$(PRINT) "$(YELLOW)    __\n .\`_  _\`.\n| | \`| | |\n| |_|._| |\n \`. __ .\'$(NO_COL)\n\n"
else
	@$(PRINT) "$(GREEN)Build Complete!$(NO_COL)\n"
endif

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).z64
	xxd $< > $@

$(BUILD_DIR)/$(TARGET).objdump: $(BUILD_DIR)/$(TARGET).elf
	$(OBJDUMP) -D $< > $@
    
$(GLOBAL_ASM_O_FILES): CC := $(PYTHON) tools/asm_processor/build.py $(CC) -- $(AS) $(ASFLAGS) --

test: $(BUILD_DIR)/$(TARGET).z64
	$(EMULATOR) $(EMU_FLAGS) $<

load: $(BUILD_DIR)/$(TARGET).z64
	$(LOADER) $(LOADER_FLAGS) $<

.PHONY: all clean distclean default diff test

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

-include $(DEP_FILES)
