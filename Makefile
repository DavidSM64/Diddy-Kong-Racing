# Makefile to rebuild DKR split image

############################ Shell ###########################

SHELL := /bin/bash

######################### Setup Check ########################

ifeq ($(wildcard ./assets/.*),)
    $(error Error, /assets/ folder was not found. Did you run the ./setup.sh script?)
endif

################ Target Executable and Sources ###############

# BUILD_DIR is location where all build artifacts are placed
BUILD_DIR = build

##################### Compiler Options #######################

IRIX_ROOT := tools/ido5.3_compiler

ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips-linux-gnu-
else ifeq ($(shell type mips64-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-linux-gnu-
else
  CROSS := mips64-elf-
endif

# check that either QEMU_IRIX is set or qemu-irix package installed
ifndef QEMU_IRIX
  QEMU_IRIX := $(shell which qemu-irix 2>/dev/null)
  ifeq (, $(QEMU_IRIX))
    $(error Please install qemu-irix package or set QEMU_IRIX env var to the full qemu-irix binary path)
  endif
endif

AS = $(CROSS)as
CC := $(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/bin/cc
CPP := cpp -P -Wno-trigraphs
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy --pad-to=0xC00000 --gap-fill=0xFF

MIPSISET := -mips1
OPT_FLAGS := -O2

ASFLAGS = -mtune=vr4300 -march=vr4300 $(INCLUDE_FLAGS)
INCLUDE_CFLAGS := -I include -I $(BUILD_DIR) -I $(BUILD_DIR)/include -I src -I .
CFLAGS = -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -Xfullwarn -signed $(OPT_FLAGS) $(INCLUDE_CFLAGS) $(MIPSISET)
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
TEXBUILDER = $(TOOLS_DIR)/dkr_texbuilder
COMPRESS = $(TOOLS_DIR)/dkr_decompressor -c
CHEAT_ENCRYPTOR = $(TOOLS_DIR)/dkr_cheats_encryptor

LIB_DIRS := lib
ASM_DIRS := asm asm/boot asm/assets data lib/asm
SRC_DIRS := src src/mips1 lib/src
ASSETS_DIRS := animations audio billboards bin cheats fonts levels objects particles text textures textures/2d textures/3d tt_ghosts ucode 

GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(wildcard src/*.c lib/src/*.c)
GLOBAL_ASM_O_FILES = $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Object files
O_FILES := 	$(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
            $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o))


####################### ASSETS #########################

# TODO: Clean this up if possible

ASSETS_DIR = assets/us_1.0

ASSETS_OBJCOPY = $(CROSS)objcopy --input-target=binary --output-target=binary

ANIMATIONS_IN_DIR = $(ASSETS_DIR)/animations
ANIMATIONS_OUT_DIR = $(BUILD_DIR)/animations
ANIMATIONS = $(wildcard $(ANIMATIONS_IN_DIR)/*.bin $(ANIMATIONS_IN_DIR)/*.cbin)
ANIMATIONS_BUILT = $(patsubst $(ANIMATIONS_IN_DIR)/%.bin,$(ANIMATIONS_OUT_DIR)/%.bin,$(ANIMATIONS))
ANIMATIONS_BUILT += $(patsubst $(ANIMATIONS_IN_DIR)/%.cbin,$(ANIMATIONS_OUT_DIR)/%.cbin,$(ANIMATIONS))

AUDIO_IN_DIR = $(ASSETS_DIR)/audio
AUDIO_OUT_DIR = $(BUILD_DIR)/audio
AUDIO = $(wildcard $(AUDIO_IN_DIR)/*.bin)
AUDIO_BUILT := $(patsubst $(AUDIO_IN_DIR)/%.bin,$(AUDIO_OUT_DIR)/%.bin,$(AUDIO))

BINS_IN_DIR = $(ASSETS_DIR)/bin
BINS_OUT_DIR = $(BUILD_DIR)/bin
BINS = $(wildcard $(BINS_IN_DIR)/*.bin)
BINS_BUILT := $(patsubst $(BINS_IN_DIR)/%.bin,$(BINS_OUT_DIR)/%.bin,$(BINS))

BILLBOARDS_IN_DIR = $(ASSETS_DIR)/billboards
BILLBOARDS_OUT_DIR = $(BUILD_DIR)/billboards
BILLBOARDS = $(wildcard $(BILLBOARDS_IN_DIR)/*.bin)
BILLBOARDS_BUILT := $(patsubst $(BILLBOARDS_IN_DIR)/%.bin,$(BILLBOARDS_OUT_DIR)/%.bin,$(BILLBOARDS))

CHEATS_IN_DIR = $(ASSETS_DIR)/cheats
CHEATS_OUT_DIR = $(BUILD_DIR)/cheats
CHEATS = $(wildcard $(CHEATS_IN_DIR)/*.cheats)
CHEATS_BUILT := $(patsubst %.cheats,%.bin,$(patsubst $(CHEATS_IN_DIR)/%.cheats,$(CHEATS_OUT_DIR)/%.cheats,$(CHEATS)))

FONTS_IN_DIR = $(ASSETS_DIR)/fonts
FONTS_OUT_DIR = $(BUILD_DIR)/fonts
FONTS = $(wildcard $(FONTS_IN_DIR)/*.bin)
FONTS_BUILT := $(patsubst $(FONTS_IN_DIR)/%.bin,$(FONTS_OUT_DIR)/%.bin,$(FONTS))

LEVELS_IN_DIR = $(ASSETS_DIR)/levels
LEVELS_OUT_DIR = $(BUILD_DIR)/levels
LEVELS = $(wildcard $(LEVELS_IN_DIR)/*.bin $(LEVELS_IN_DIR)/*.cbin)
LEVELS_BUILT = $(patsubst $(LEVELS_IN_DIR)/%.bin,$(LEVELS_OUT_DIR)/%.bin,$(LEVELS))
LEVELS_BUILT += $(patsubst $(LEVELS_IN_DIR)/%.cbin,$(LEVELS_OUT_DIR)/%.cbin,$(LEVELS))

OBJECTS_IN_DIR = $(ASSETS_DIR)/objects
OBJECTS_OUT_DIR = $(BUILD_DIR)/objects
OBJECTS = $(wildcard $(OBJECTS_IN_DIR)/*.bin $(OBJECTS_IN_DIR)/*.cbin)
OBJECTS_BUILT = $(patsubst $(OBJECTS_IN_DIR)/%.bin,$(OBJECTS_OUT_DIR)/%.bin,$(OBJECTS))
OBJECTS_BUILT += $(patsubst $(OBJECTS_IN_DIR)/%.cbin,$(OBJECTS_OUT_DIR)/%.cbin,$(OBJECTS))

PARTICLES_IN_DIR = $(ASSETS_DIR)/particles
PARTICLES_OUT_DIR = $(BUILD_DIR)/particles
PARTICLES = $(wildcard $(PARTICLES_IN_DIR)/*.bin)
PARTICLES_BUILT := $(patsubst $(PARTICLES_IN_DIR)/%.bin,$(PARTICLES_OUT_DIR)/%.bin,$(PARTICLES))

TEXT_IN_DIR = $(ASSETS_DIR)/text
TEXT_OUT_DIR = $(BUILD_DIR)/text
TEXT = $(wildcard $(TEXT_IN_DIR)/*.bin)
TEXT_BUILT := $(patsubst $(TEXT_IN_DIR)/%.bin,$(TEXT_OUT_DIR)/%.bin,$(TEXT))

TEXTURES_IN_DIR = $(ASSETS_DIR)/textures
TEXTURES_2D_IN_DIR = $(ASSETS_DIR)/textures/2d
TEXTURES_3D_IN_DIR = $(ASSETS_DIR)/textures/3d
TEXTURES_OUT_DIR = $(BUILD_DIR)/textures
TEXTURES_2D_OUT_DIR = $(BUILD_DIR)/textures/2d
TEXTURES_3D_OUT_DIR = $(BUILD_DIR)/textures/3d
TEXTURES_BIN = $(wildcard $(TEXTURES_IN_DIR)/*.bin)
TEXTURES_2D = $(wildcard $(TEXTURES_2D_IN_DIR)/*.png)
TEXTURES_3D = $(wildcard $(TEXTURES_3D_IN_DIR)/*.png)
TEXTURES_BUILT = $(patsubst $(TEXTURES_IN_DIR)/%.bin,$(TEXTURES_OUT_DIR)/%.bin,$(TEXTURES_BIN))
TEXTURES_BUILT += $(patsubst $(TEXTURES_2D_IN_DIR)/%.png,$(TEXTURES_2D_OUT_DIR)/%.bin,$(TEXTURES_2D))
TEXTURES_BUILT += $(patsubst $(TEXTURES_3D_IN_DIR)/%.png,$(TEXTURES_3D_OUT_DIR)/%.bin,$(TEXTURES_3D))

TT_GHOSTS_IN_DIR = $(ASSETS_DIR)/tt_ghosts
TT_GHOSTS_OUT_DIR = $(BUILD_DIR)/tt_ghosts
TT_GHOSTS = $(wildcard $(TT_GHOSTS_IN_DIR)/*.bin)
TT_GHOSTS_BUILT := $(patsubst $(TT_GHOSTS_IN_DIR)/%.bin,$(TT_GHOSTS_OUT_DIR)/%.bin,$(TT_GHOSTS))

UCODE_IN_DIR = $(ASSETS_DIR)/ucode
UCODE_OUT_DIR = $(BUILD_DIR)/ucode
UCODE = $(wildcard $(UCODE_IN_DIR)/*.bin)
UCODE_BUILT := $(patsubst $(UCODE_IN_DIR)/%.bin,$(UCODE_OUT_DIR)/%.bin,$(UCODE))

ALL_ASSETS_BUILT := $(ANIMATIONS_BUILT) $(AUDIO_BUILT) $(BILLBOARDS_BUILT) $(BINS_BUILT) $(CHEATS_BUILT) $(FONTS_BUILT) $(LEVELS_BUILT) $(OBJECTS_BUILT) $(TEXTURES_BUILT) $(PARTICLES_BUILT) $(TEXT_BUILT) $(TT_GHOSTS_BUILT) $(UCODE_BUILT)

####################### LIBULTRA #########################

$(BUILD_DIR)/lib/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/lib/%.o: MIPSISET := -mips2
$(BUILD_DIR)/lib/src/osSetTimer.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/osTimer.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/osViBlack.o: OPT_FLAGS := -O1
$(BUILD_DIR)/lib/src/osViSwapBuffer.o : OPT_FLAGS := -O1

######################## Targets #############################

default: all

TARGET = dkr
LD_SCRIPT = $(TARGET).ld

all: $(BUILD_DIR)/$(TARGET).z64

clean: 
ifneq ($(wildcard ./build/.*),) 
	rm -r $(BUILD_DIR)
else 
	@echo "/build/ directory has already been deleted." 
endif 
    
clean_lib:
ifneq ($(wildcard ./build/lib/.*),) 
	rm -r $(BUILD_DIR)/lib/src/*.o
else 
	@echo "/build/lib directory has already been deleted." 
endif 

$(BUILD_DIR):
	mkdir $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(LIB_DIRS) $(ASM_DIRS) $(SRC_DIRS) $(ASSETS_DIRS))

# This is here to prevent make from deleting all the asset files after the build completes/fails.
dont_remove_asset_files: $(ALL_ASSETS_BUILT)

######## Asset Targets ########

$(ANIMATIONS_OUT_DIR)/%.bin: $(ANIMATIONS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(ANIMATIONS_OUT_DIR)/%.cbin: $(ANIMATIONS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@
    
$(AUDIO_OUT_DIR)/%.bin: $(AUDIO_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(BILLBOARDS_OUT_DIR)/%.bin: $(BILLBOARDS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(BINS_OUT_DIR)/%.bin: $(BINS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
$(CHEATS_OUT_DIR)/%.bin: $(CHEATS_IN_DIR)/%.cheats
	$(CHEAT_ENCRYPTOR) $^ $@
    
$(FONTS_OUT_DIR)/%.bin: $(FONTS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
$(LEVELS_OUT_DIR)/%.bin: $(LEVELS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(LEVELS_OUT_DIR)/%.cbin: $(LEVELS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@
    
$(OBJECTS_OUT_DIR)/%.bin: $(OBJECTS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(OBJECTS_OUT_DIR)/%.cbin: $(OBJECTS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@

$(TEXTURES_2D_OUT_DIR)/%.bin: $(TEXTURES_2D_IN_DIR)/%.png 
	$(TEXBUILDER) $^ $@ 

$(TEXTURES_3D_OUT_DIR)/%.bin: $(TEXTURES_3D_IN_DIR)/%.png 
	$(TEXBUILDER) $^ $@ 

$(TEXTURES_OUT_DIR)/%.bin: $(TEXTURES_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(PARTICLES_OUT_DIR)/%.bin: $(PARTICLES_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(TEXT_OUT_DIR)/%.bin: $(TEXT_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(TT_GHOSTS_OUT_DIR)/%.bin: $(TT_GHOSTS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
$(UCODE_OUT_DIR)/%.bin: $(UCODE_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
###############################

$(BUILD_DIR)/%.o: %.s Makefile $(MAKEFILE_SPLIT) | $(BUILD_DIR) $(ALL_ASSETS_BUILT)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) $(VERSION_CFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

$(BUILD_DIR)/$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@ $(O_FILES) $(LIBS)

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) $< $@ -O binary
    
# final z64 updates checksum
$(BUILD_DIR)/$(TARGET).z64: $(BUILD_DIR)/$(TARGET).bin
	cp $< $@
	$(N64CRC) $@
	sha1sum -c $(TARGET).sha1

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
