# Makefile to build DKR

############################ Shell ###########################

SHELL := /bin/bash

################## Preprocessor definitions ##################

# Currently, only US 1.0 is supported.
VERSION := us_1.0

NON_MATCHING ?= 0
$(eval $(call validate-option,NON_MATCHING,0 1))

ifeq ($(VERSION),us_1.0)
  DEFINES += VERSION_US_1_0=1
endif
ifeq ($(NON_MATCHING),1)
  DEFINES += NON_MATCHING=1
endif

############################ Setup ###########################

# Don't do setup checks if cleaning.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),clean_lib)
ifneq ($(MAKECMDGOALS),clean_src)
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

########## Recomp ##########

# List of IDO tools required for the repo.
# NOTE: If you are adding a tool here, make sure to update the Makefile in `/tools/ido-static-recomp/`!
RECOMP_TOOLS := cc cfe uopt ugen as1 ujoin uld usplit umerge

RECOMP_DIR := ./tools/ido5.3_recomp/
RECOMP_TOOLS_PATHS = $(addprefix $(RECOMP_DIR),$(RECOMP_TOOLS))

# Checks if all the recomp tools exist.
$(foreach p,$(RECOMP_TOOLS_PATHS),$(if $(wildcard $(p)),,$(info $(p) does not exist!) $(eval runRecomp:=yes)))

# If any of the tools do not exist, then recomp needs to run to build them.
ifeq ($(runRecomp),yes)
  DUMMY != make -s -C tools/ido-static-recomp >&2 || echo FAIL
endif

######## Extract Assets & Microcode ########

DUMMY != python3 ./tools/python/check_if_need_to_extract.py $(VERSION) >&2 || echo FAIL

##### Generate linker file #####

DUMMY != ./generate_ld.sh $(VERSION) >&2 || echo FAIL
ifeq ($(DUMMY),FAIL)
  $(error Failed to generate the linker file)
endif

################################

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
CC := tools/ido5.3_recomp/cc
CPP := cpp -P -Wno-trigraphs
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy --pad-to=0xC00000 --gap-fill=0xFF

MIPSISET := -mips1
OPT_FLAGS := -O2

C_DEFINES := $(foreach d,$(DEFINES),-D$(d))
DEF_INC_CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(C_DEFINES)

ASFLAGS = -mtune=vr4300 -march=vr4300 -mabi=32 $(foreach d,$(DEFINES),--defsym $(d))
INCLUDE_CFLAGS := -I include -I $(BUILD_DIR) -I src -I .
CFLAGS = -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -Xfullwarn -signed $(OPT_FLAGS) $(MIPSISET) $(INCLUDE_CFLAGS) $(DEF_INC_CFLAGS)
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
TEXBUILDER = $(TOOLS_DIR)/dkr_texbuilder
COMPRESS = $(TOOLS_DIR)/dkr_decompressor -c

LIB_DIRS := lib/
ASM_DIRS := asm/ asm/boot/ asm/assets/ lib/asm/
SRC_DIRS := $(sort $(dir $(wildcard src/*/ src/**/*/))) $(sort $(dir $(wildcard lib/src/*/ lib/src/**/*/)))

GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(SRC_DIRS)
GLOBAL_ASM_O_FILES = $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)*.s))
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)*.c))

# Object files
O_FILES := 	$(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
            $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o))


####################### ASSETS #########################

# TODO: Clean this up if possible

# All the asset subfolders to create in the build folder.
ASSETS_DIRS := audio bin fonts ids levels levels/headers levels/models levels/names levels/objectMaps misc objects objects/animations objects/headers objects/models particles particles/behaviors particles/particles sprites text text/game text/menu textures textures/2d textures/3d tt_ghosts unknown_0 ucode

ASSETS_DIR = assets/$(VERSION)
UCODE_DIR = ucode/$(VERSION)

ASSETS_COPY = cp

AUDIO_IN_DIR = $(ASSETS_DIR)/audio
AUDIO_OUT_DIR = $(BUILD_DIR)/audio
ALL_ASSETS_BUILT += $(patsubst $(AUDIO_IN_DIR)/%.bin,$(AUDIO_OUT_DIR)/%.bin,$(wildcard $(AUDIO_IN_DIR)/*.bin))

BIN_IN_DIR = $(ASSETS_DIR)/bin
BIN_OUT_DIR = $(BUILD_DIR)/bin
ALL_ASSETS_BUILT += $(patsubst $(BIN_IN_DIR)/%.bin,$(BIN_OUT_DIR)/%.bin,$(wildcard $(BIN_IN_DIR)/*.bin))

FONTS_IN_DIR = $(ASSETS_DIR)/fonts
FONTS_OUT_DIR = $(BUILD_DIR)/fonts
ALL_ASSETS_BUILT += $(patsubst $(FONTS_IN_DIR)/%.bin,$(FONTS_OUT_DIR)/%.bin,$(wildcard $(FONTS_IN_DIR)/*.bin))

IDS_IN_DIR = $(ASSETS_DIR)/ids
IDS_OUT_DIR = $(BUILD_DIR)/ids
ALL_ASSETS_BUILT += $(patsubst $(IDS_IN_DIR)/%.bin,$(IDS_OUT_DIR)/%.bin,$(wildcard $(IDS_IN_DIR)/*.bin))

LEVELS_IN_DIR = $(ASSETS_DIR)/levels
LEVELS_OUT_DIR = $(BUILD_DIR)/levels
LEVEL_HEADERS_IN_DIR = $(LEVELS_IN_DIR)/headers
LEVEL_HEADERS_OUT_DIR = $(LEVELS_OUT_DIR)/headers
LEVEL_MODELS_IN_DIR = $(LEVELS_IN_DIR)/models
LEVEL_MODELS_OUT_DIR = $(LEVELS_OUT_DIR)/models
LEVEL_NAMES_IN_DIR = $(LEVELS_IN_DIR)/names
LEVEL_NAMES_OUT_DIR = $(LEVELS_OUT_DIR)/names
LEVEL_OBJMAPS_IN_DIR = $(LEVELS_IN_DIR)/objectMaps
LEVEL_OBJMAPS_OUT_DIR = $(LEVELS_OUT_DIR)/objectMaps
ALL_ASSETS_BUILT += $(patsubst $(LEVEL_HEADERS_IN_DIR)/%.bin,$(LEVEL_HEADERS_OUT_DIR)/%.bin,$(wildcard $(LEVEL_HEADERS_IN_DIR)/*.bin))
ALL_ASSETS_BUILT += $(patsubst $(LEVEL_MODELS_IN_DIR)/%.cbin,$(LEVEL_MODELS_OUT_DIR)/%.bin,$(wildcard $(LEVEL_MODELS_IN_DIR)/*.cbin))
ALL_ASSETS_BUILT += $(patsubst $(LEVEL_NAMES_IN_DIR)/%.bin,$(LEVEL_NAMES_OUT_DIR)/%.bin,$(wildcard $(LEVEL_NAMES_IN_DIR)/*.bin))
ALL_ASSETS_BUILT += $(patsubst $(LEVEL_OBJMAPS_IN_DIR)/%.cbin,$(LEVEL_OBJMAPS_OUT_DIR)/%.bin,$(wildcard $(LEVEL_OBJMAPS_IN_DIR)/*.cbin))

MISC_IN_DIR = $(ASSETS_DIR)/misc
MISC_OUT_DIR = $(BUILD_DIR)/misc
ALL_ASSETS_BUILT += $(patsubst $(MISC_IN_DIR)/%.bin,$(MISC_OUT_DIR)/%.bin,$(wildcard $(MISC_IN_DIR)/*.bin))

OBJECTS_IN_DIR = $(ASSETS_DIR)/objects
OBJECTS_OUT_DIR = $(BUILD_DIR)/objects
OBJECT_ANIMS_IN_DIR = $(OBJECTS_IN_DIR)/animations
OBJECT_ANIMS_OUT_DIR = $(OBJECTS_OUT_DIR)/animations
OBJECT_HEADERS_IN_DIR = $(OBJECTS_IN_DIR)/headers
OBJECT_HEADERS_OUT_DIR = $(OBJECTS_OUT_DIR)/headers
OBJECT_MODELS_IN_DIR = $(OBJECTS_IN_DIR)/models
OBJECT_MODELS_OUT_DIR = $(OBJECTS_OUT_DIR)/models
ALL_ASSETS_BUILT += $(patsubst $(OBJECTS_IN_DIR)/%.bin,$(OBJECTS_OUT_DIR)/%.bin,$(wildcard $(OBJECTS_IN_DIR)/*.bin))
ALL_ASSETS_BUILT += $(patsubst $(OBJECT_ANIMS_IN_DIR)/%.cbin,$(OBJECT_ANIMS_OUT_DIR)/%.bin,$(wildcard $(OBJECT_ANIMS_IN_DIR)/*.cbin))
ALL_ASSETS_BUILT += $(patsubst $(OBJECT_HEADERS_IN_DIR)/%.bin,$(OBJECT_HEADERS_OUT_DIR)/%.bin,$(wildcard $(OBJECT_HEADERS_IN_DIR)/*.bin))
ALL_ASSETS_BUILT += $(patsubst $(OBJECT_MODELS_IN_DIR)/%.cbin,$(OBJECT_MODELS_OUT_DIR)/%.bin,$(wildcard $(OBJECT_MODELS_IN_DIR)/*.cbin))

PARTICLES_IN_DIR = $(ASSETS_DIR)/particles
PARTICLES_OUT_DIR = $(BUILD_DIR)/particles
PART_BEHAVIORS_IN_DIR = $(PARTICLES_IN_DIR)/behaviors
PART_BEHAVIORS_OUT_DIR = $(PARTICLES_OUT_DIR)/behaviors
PART_PARTICLES_IN_DIR = $(PARTICLES_IN_DIR)/particles
PART_PARTICLES_OUT_DIR = $(PARTICLES_OUT_DIR)/particles
ALL_ASSETS_BUILT += $(patsubst $(PART_BEHAVIORS_IN_DIR)/%.bin,$(PART_BEHAVIORS_OUT_DIR)/%.bin,$(wildcard $(PART_BEHAVIORS_IN_DIR)/*.bin))
ALL_ASSETS_BUILT += $(patsubst $(PART_PARTICLES_IN_DIR)/%.bin,$(PART_PARTICLES_OUT_DIR)/%.bin,$(wildcard $(PART_PARTICLES_IN_DIR)/*.bin))

SPRITES_IN_DIR = $(ASSETS_DIR)/sprites
SPRITES_OUT_DIR = $(BUILD_DIR)/sprites
ALL_ASSETS_BUILT += $(patsubst $(SPRITES_IN_DIR)/%.bin,$(SPRITES_OUT_DIR)/%.bin,$(wildcard $(SPRITES_IN_DIR)/*.bin))

TEXT_IN_DIR = $(ASSETS_DIR)/text
TEXT_OUT_DIR = $(BUILD_DIR)/text
TEXT_GAME_IN_DIR = $(TEXT_IN_DIR)/game
TEXT_GAME_OUT_DIR = $(TEXT_OUT_DIR)/game
TEXT_MENU_IN_DIR = $(TEXT_IN_DIR)/menu
TEXT_MENU_OUT_DIR = $(TEXT_OUT_DIR)/menu
ALL_ASSETS_BUILT += $(patsubst $(TEXT_GAME_IN_DIR)/%.bin,$(TEXT_GAME_OUT_DIR)/%.bin,$(wildcard $(TEXT_GAME_IN_DIR)/*.bin))
ALL_ASSETS_BUILT += $(patsubst $(TEXT_MENU_IN_DIR)/%.bin,$(TEXT_MENU_OUT_DIR)/%.bin,$(wildcard $(TEXT_MENU_IN_DIR)/*.bin))

TEXTURES_IN_DIR = $(ASSETS_DIR)/textures
TEXTURES_OUT_DIR = $(BUILD_DIR)/textures
TEXTURES_2D_IN_DIR = $(TEXTURES_IN_DIR)/2d
TEXTURES_2D_OUT_DIR = $(TEXTURES_OUT_DIR)/2d
TEXTURES_3D_IN_DIR = $(TEXTURES_IN_DIR)/3d
TEXTURES_3D_OUT_DIR = $(TEXTURES_OUT_DIR)/3d
ALL_ASSETS_BUILT += $(patsubst $(TEXTURES_2D_IN_DIR)/%.png,$(TEXTURES_2D_OUT_DIR)/%.bin,$(wildcard $(TEXTURES_2D_IN_DIR)/*.png))
ALL_ASSETS_BUILT += $(patsubst $(TEXTURES_3D_IN_DIR)/%.png,$(TEXTURES_3D_OUT_DIR)/%.bin,$(wildcard $(TEXTURES_3D_IN_DIR)/*.png))

TT_GHOSTS_IN_DIR = $(ASSETS_DIR)/tt_ghosts
TT_GHOSTS_OUT_DIR = $(BUILD_DIR)/tt_ghosts
ALL_ASSETS_BUILT += $(patsubst $(TT_GHOSTS_IN_DIR)/%.bin,$(TT_GHOSTS_OUT_DIR)/%.bin,$(wildcard $(TT_GHOSTS_IN_DIR)/*.bin))

UNKNOWN_0_IN_DIR = $(ASSETS_DIR)/unknown_0
UNKNOWN_0_OUT_DIR = $(BUILD_DIR)/unknown_0
ALL_ASSETS_BUILT += $(patsubst $(UNKNOWN_0_IN_DIR)/%.bin,$(UNKNOWN_0_OUT_DIR)/%.bin,$(wildcard $(UNKNOWN_0_IN_DIR)/*.bin))

UCODE_IN_DIR = $(UCODE_DIR)
UCODE_OUT_DIR = $(BUILD_DIR)/ucode
UCODE = $(wildcard $(UCODE_IN_DIR)/*.bin)
ALL_ASSETS_BUILT += $(patsubst $(UCODE_IN_DIR)/%.bin,$(UCODE_OUT_DIR)/%.bin,$(UCODE))

#ALL_ASSETS_BUILT := $(ANIMATIONS_BUILT) $(AUDIO_BUILT) $(BILLBOARDS_BUILT) $(BINS_BUILT) $(CHEATS_BUILT) $(FONTS_BUILT) $(LEVELS_BUILT) $(OBJECTS_BUILT) $(TEXTURES_BUILT) $(PARTICLES_BUILT) $(TEXT_BUILT) $(TT_GHOSTS_BUILT) $(UCODE_BUILT) $(LUT_BUILT)

####################### LIBULTRA #########################

$(BUILD_DIR)/lib/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/lib/%.o: MIPSISET := -mips2
$(BUILD_DIR)/lib/src/al/%.o: OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/os/%.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/os/osViMgr.o: OPT_FLAGS := -O2
$(BUILD_DIR)/lib/src/unknown_0C91A0.o : OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/unknown_0D29F0.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/unknown_0CDE90.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/unknown_0D3160.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/unknown_0D3360.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/unknown_0D5EC0.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/unknown_0C9C90.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0
$(BUILD_DIR)/lib/src/osEepromWrite.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/osEepromRead.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/osSetTimer.o: OPT_FLAGS := -O1

# asm-processor currently does not support -O3, so this is my workaround.
$(BUILD_DIR)/lib/src/al/global_asm/%.o: OPT_FLAGS := -O2

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
else 
	@echo "/build/ directory has already been deleted." 
endif 
    
clean_lib:
ifneq ($(wildcard $(BUILD_DIR)/lib/.*),) 
	rm -r $(BUILD_DIR)/lib/src/*.o
else 
	@echo "build lib directory has already been deleted." 
endif 

clean_src: clean_lib
ifneq ($(wildcard ./build/src/.*),) 
	rm -r $(BUILD_DIR)/src/*.o
else 
	@echo "/build/lib directory has already been deleted." 
endif 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(LIB_DIRS) $(ASM_DIRS) $(SRC_DIRS) $(ASSETS_DIRS))

# Helps fix an issue with parallel jobs.
$(ALL_ASSETS_BUILT): | $(BUILD_DIR)

# This is here to prevent make from deleting all the asset files after the build completes/fails.
dont_remove_asset_files: $(ALL_ASSETS_BUILT)

######## Asset Targets ########

# All assets should output a .bin file

$(AUDIO_OUT_DIR)/%.bin: $(AUDIO_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(BIN_OUT_DIR)/%.bin: $(BIN_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(FONTS_OUT_DIR)/%.bin: $(FONTS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(IDS_OUT_DIR)/%.bin: $(IDS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(LEVEL_HEADERS_OUT_DIR)/%.bin: $(LEVEL_HEADERS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(LEVEL_MODELS_OUT_DIR)/%.bin: $(LEVEL_MODELS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@
    
$(LEVEL_NAMES_OUT_DIR)/%.bin: $(LEVEL_NAMES_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(LEVEL_OBJMAPS_OUT_DIR)/%.bin: $(LEVEL_OBJMAPS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@

$(MISC_OUT_DIR)/%.bin: $(MISC_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(OBJECTS_OUT_DIR)/%.bin: $(OBJECTS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(OBJECT_ANIMS_OUT_DIR)/%.bin: $(OBJECT_ANIMS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@
    
$(OBJECT_HEADERS_OUT_DIR)/%.bin: $(OBJECT_HEADERS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(OBJECT_MODELS_OUT_DIR)/%.bin: $(OBJECT_MODELS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@
    
$(PART_BEHAVIORS_OUT_DIR)/%.bin: $(PART_BEHAVIORS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(PART_PARTICLES_OUT_DIR)/%.bin: $(PART_PARTICLES_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(SPRITES_OUT_DIR)/%.bin: $(SPRITES_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(TEXT_GAME_OUT_DIR)/%.bin: $(TEXT_GAME_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(TEXT_MENU_OUT_DIR)/%.bin: $(TEXT_MENU_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(TEXTURES_2D_OUT_DIR)/%.bin: $(TEXTURES_2D_IN_DIR)/%.png
	$(TEXBUILDER) $^ $@ 

$(TEXTURES_3D_OUT_DIR)/%.bin: $(TEXTURES_3D_IN_DIR)/%.png
	$(TEXBUILDER) $^ $@ 

$(TEXT_MENU_OUT_DIR)/%.bin: $(TEXT_MENU_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(TT_GHOSTS_OUT_DIR)/%.bin: $(TT_GHOSTS_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@

$(UNKNOWN_0_OUT_DIR)/%.bin: $(UNKNOWN_0_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
$(UCODE_OUT_DIR)/%.bin: $(UCODE_IN_DIR)/%.bin 
	$(ASSETS_COPY) $^ $@
    
###############################

$(BUILD_DIR)/%.o: %.s | $(ALL_ASSETS_BUILT)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c | $(ALL_ASSETS_BUILT)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT) | $(ALL_ASSETS_BUILT)
	$(CPP) $(VERSION_CFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

$(BUILD_DIR)/$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT) | $(ALL_ASSETS_BUILT)
	$(LD) $(LDFLAGS) -o $@ $(O_FILES) $(LIBS)

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf | $(ALL_ASSETS_BUILT)
	$(OBJCOPY) $< $@ -O binary

$(BUILD_DIR)/$(TARGET).z64: $(BUILD_DIR)/$(TARGET).bin | $(ALL_ASSETS_BUILT)
	cp $< $@
	$(FIXCHECKSUMS)
	$(N64CRC) $@
ifeq ($(NON_MATCHING),0)
	sha1sum -c sha1/dkr.$(VERSION).sha1
else
	@echo "Build complete!"
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

.PHONY: all clean default diff test

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules
