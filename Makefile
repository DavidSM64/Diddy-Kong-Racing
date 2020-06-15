# Makefile to rebuild DKR split image

############################ Shell ###########################

SHELL := /bin/bash

################ Target Executable and Sources ###############

# BUILD_DIR is location where all build artifacts are placed
BUILD_DIR = build

##################### Compiler Options #######################
#IRIX_ROOT := tools/ido5.3_compiler

ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips-linux-gnu-
else ifeq ($(shell type mips64-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-linux-gnu-
else
  CROSS := mips64-elf-
endif

# check that either QEMU_IRIX is set or qemu-irix package installed
#ifndef QEMU_IRIX
#  QEMU_IRIX := $(shell which qemu-irix 2>/dev/null)
#  ifeq (, $(QEMU_IRIX))
#    $(error Please install qemu-irix package or set QEMU_IRIX env var to the full qemu-irix binary path)
#  endif
#endif

AS = $(CROSS)as
#CC = $(CROSS)gcc
CC := $(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/bin/cc
CPP := cpp -P -Wno-trigraphs
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy --pad-to=0xC00000 --gap-fill=0xFF

INCLUDE_FLAGS := -I$(BUILD_DIR)
ASFLAGS = -mtune=vr4300 -march=vr4300 $(INCLUDE_FLAGS)
CFLAGS  = -Wall -O2 -mtune=vr4300 -march=vr4300 -G 0 -c
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

ASM_DIRS := asm asm/boot asm/assets
SRC_DIRS := src
ASSETS_DIRS := animations bin cheats levels objects text textures ucode 

S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))

BUILD_ASM_DIRS := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/**/))

# Object files
O_FILES := 	$(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o))


####################### ASSETS #########################

ASSETS_DIR = assets/us_1.0

ASSETS_OBJCOPY = $(CROSS)objcopy --input-target=binary --output-target=binary

TEXTURES_IN_DIR = $(ASSETS_DIR)/textures
TEXTURES_OUT_DIR = $(BUILD_DIR)/textures
TEXTURES = $(wildcard $(TEXTURES_IN_DIR)/*.png $(TEXTURES_IN_DIR)/*.bin)
TEXTURES_BUILT := $(patsubst $(TEXTURES_IN_DIR)/%.png,$(TEXTURES_OUT_DIR)/%.bin,$(TEXTURES))
TEXTURES_BIN_BUILT := $(patsubst $(TEXTURES_IN_DIR)/%.bin,$(TEXTURES_OUT_DIR)/%.bin,$(TEXTURES))

REGEX_TEXTURE_NAME := $(TEXTURES_IN_DIR)[/](([^.]*[.][^.]*)[.]0[.][^.]*[.][^.]*[.][^.]*)[.]png
define build_texture
	$(shell \
        if [[ $1 =~ $(REGEX_TEXTURE_NAME) ]] ; then \
            $(TEXBUILDER) $(TEXTURES_IN_DIR) $(TEXTURES_OUT_DIR) $${BASH_REMATCH[2]} $${BASH_REMATCH[1]} ; \
        fi \
    )
endef

BINS_IN_DIR = $(ASSETS_DIR)/bin
BINS_OUT_DIR = $(BUILD_DIR)/bin
BINS = $(wildcard $(BINS_IN_DIR)/*.bin)
BINS_BUILT := $(patsubst $(BINS_IN_DIR)/%.bin,$(BINS_OUT_DIR)/%.bin,$(BINS))

ANIMATIONS_IN_DIR = $(ASSETS_DIR)/animations
ANIMATIONS_OUT_DIR = $(BUILD_DIR)/animations
ANIMATIONS = $(wildcard $(ANIMATIONS_IN_DIR)/*.bin $(ANIMATIONS_IN_DIR)/*.cbin)
ANIMATIONS_BUILT = $(patsubst $(ANIMATIONS_IN_DIR)/%.bin,$(ANIMATIONS_OUT_DIR)/%.bin,$(ANIMATIONS))
ANIMATIONS_BUILT += $(patsubst $(ANIMATIONS_IN_DIR)/%.cbin,$(ANIMATIONS_OUT_DIR)/%.cbin,$(ANIMATIONS))

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

TEXT_IN_DIR = $(ASSETS_DIR)/text
TEXT_OUT_DIR = $(BUILD_DIR)/text
TEXT = $(wildcard $(TEXT_IN_DIR)/*.bin)
TEXT_BUILT := $(patsubst $(TEXT_IN_DIR)/%.bin,$(TEXT_OUT_DIR)/%.bin,$(TEXT))

UCODE_IN_DIR = $(ASSETS_DIR)/ucode
UCODE_OUT_DIR = $(BUILD_DIR)/ucode
UCODE = $(wildcard $(UCODE_IN_DIR)/*.bin)
UCODE_BUILT := $(patsubst $(UCODE_IN_DIR)/%.bin,$(UCODE_OUT_DIR)/%.bin,$(UCODE))

CHEATS_IN_DIR = $(ASSETS_DIR)/cheats
CHEATS_OUT_DIR = $(BUILD_DIR)/cheats
CHEATS = $(wildcard $(CHEATS_IN_DIR)/*.cheats)
CHEATS_BUILT := $(patsubst %.cheats,%.bin,$(patsubst $(CHEATS_IN_DIR)/%.cheats,$(CHEATS_OUT_DIR)/%.cheats,$(CHEATS)))

ALL_ASSETS_BUILT := $(ANIMATIONS_BUILT) $(BINS_BUILT) $(CHEATS_BUILT) $(LEVELS_BUILT) $(OBJECTS_BUILT) $(TEXTURES_BUILT) $(TEXTURES_BIN_BUILT) $(TEXT_BUILT) $(UCODE_BUILT)


######################## Targets #############################

default: all

TARGET = dkr
LD_SCRIPT = $(TARGET).ld

all: $(BUILD_DIR)/$(TARGET).z64

clean: 
	rm -r $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(ASM_DIRS) $(ASSETS_DIRS))

# This is here to prevent make from deleting all the asset files after the build completes/fails.
dont_remove_asset_files: $(ALL_ASSETS_BUILT)

######## Asset Targets ########

$(ANIMATIONS_OUT_DIR)/%.bin: $(ANIMATIONS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(ANIMATIONS_OUT_DIR)/%.cbin: $(ANIMATIONS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@

$(BINS_OUT_DIR)/%.bin: $(BINS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
$(CHEATS_OUT_DIR)/%.bin: $(CHEATS_IN_DIR)/%.cheats
	$(CHEAT_ENCRYPTOR) $^ $@
    
$(LEVELS_OUT_DIR)/%.bin: $(LEVELS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(LEVELS_OUT_DIR)/%.cbin: $(LEVELS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@
    
$(OBJECTS_OUT_DIR)/%.bin: $(OBJECTS_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(OBJECTS_OUT_DIR)/%.cbin: $(OBJECTS_IN_DIR)/%.cbin 
	$(COMPRESS) $^ $@

$(TEXTURES_OUT_DIR)/%.bin: $(TEXTURES_IN_DIR)/%.png 
	$(call build_texture,$^)
	@echo $@

$(TEXTURES_OUT_DIR)/%.bin: $(TEXTURES_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@

$(TEXT_OUT_DIR)/%.bin: $(TEXT_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
$(UCODE_OUT_DIR)/%.bin: $(UCODE_IN_DIR)/%.bin 
	$(ASSETS_OBJCOPY) $^ $@
    
###############################

$(BUILD_DIR)/%.o: %.s Makefile $(MAKEFILE_SPLIT) | $(BUILD_DIR) $(ALL_ASSETS_BUILT)
	$(AS) $(ASFLAGS) -o $@ $<

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

test: $(BUILD_DIR)/$(TARGET).z64
	$(EMULATOR) $(EMU_FLAGS) $<

load: $(BUILD_DIR)/$(TARGET).z64
	$(LOADER) $(LOADER_FLAGS) $<

.PHONY: all clean default diff test

