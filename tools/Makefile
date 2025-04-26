# Make `OPT` -g for better debugging info.
OPT := -g
CC := gcc
CXX := g++
CFLAGS := -I . -Wall -Wextra -Wno-unused-parameter -pedantic -std=c99 $(OPT) -s
# List of specific errors to ignore
IGNORE_W_ERRORS := -Wno-unused-parameter -Wno-misleading-indentation -Wno-extra
CXXFLAGS := -I . -I dkr_assets_tool_src/ -std=c++17 $(OPT)
LDFLAGS := -lm
PROGRAMS := n64crc dkr_assets_tool

UNAME_S := $(shell uname -s)

# MacOS has a slightly different name for grep, so check to see if it needs to be used.
ifeq ($(UNAME_S),Windows_NT)
	$(error Native Windows is currently unsupported for building this repository, use WSL instead c:)
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := macos
	CXXFLAGS += -I/opt/homebrew/include 
	LDFLAGS += -I/opt/homebrew/lib -lpcre2-8
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
	CXXFLAGS += -Werror -Wall $(IGNORE_W_ERRORS) -lpcre2-8 
	UNAME_M := $(shell uname -m)
# If we detect arm as a platform for linux, but not mac, we'll make this -arm to download that version (Mostly used for raspi)
	ifneq ($(filter aarch%,$(UNAME_M)),)
		DETECTED_OS := linux-arm
	endif
endif

BUILD_DIR := dkr_assets_tool_src/_build

ENUMS_HEADER := ../include/enums.h

# From: https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make/18258352#18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

RECOMP_DIR := ido-recomp/$(DETECTED_OS)

default: all

n64crc_SOURCES := n64crc.c

all: $(PROGRAMS) recomp flips

# make clean for flips doesn't work, so just manually delete it on a clean. 
clean:
	$(RM) -Rf $(PROGRAMS) $(BUILD_DIR)
	$(RM) -rf $(RECOMP_DIR)
	$(RM) -f Flips/flips

distclean: clean

n64crc: n64crc.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

dkr_assets_tool_CPP_FILES := $(call rwildcard,dkr_assets_tool_src,*.cpp)

dkr_assets_tool_C_FILES := $(call rwildcard,dkr_assets_tool_src,*.c)

dkr_assets_tool_OBJ_FILES := $(foreach file,$(dkr_assets_tool_C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
                             $(foreach file,$(dkr_assets_tool_CPP_FILES),$(BUILD_DIR)/$(file:.cpp=.o))

DUMMY != mkdir -p $(sort $(dir $(dkr_assets_tool_OBJ_FILES)))

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS)
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

dkr_assets_tool: $(dkr_assets_tool_OBJ_FILES)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) -lpthread

recomp:
	@echo "Fetching Recomp..."
	wget https://github.com/decompals/ido-static-recomp/releases/download/v1.2/ido-5.3-recomp-${DETECTED_OS}.tar.gz
	mkdir -p $(RECOMP_DIR)
	tar xf ido-5.3-recomp-${DETECTED_OS}.tar.gz -C $(RECOMP_DIR)
	$(RM) ido-5.3-recomp-${DETECTED_OS}.tar.gz

#Builds the CLI only version of flips. It will complain about it being debug, but this makes it much faster compile.
flips:
	@make -s -C Flips TARGET=cli

.PHONY: all clean distclean default

