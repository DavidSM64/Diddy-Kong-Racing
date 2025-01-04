# Make `OPT` -g for better debugging info.
OPT := -O2
CC := gcc
CXX := g++
CFLAGS := -I . -Wall -Wextra -Wno-unused-parameter -pedantic -std=c99 $(OPT) -s
# List of specific errors to ignore
IGNORE_W_ERRORS := -Wno-unused-parameter -Wno-misleading-indentation -Wno-extra
CXXFLAGS := -I . -I dkr_assets_tool_src/ -std=c++17 $(OPT)
LDFLAGS := -lm
PROGRAMS := n64crc dkr_assets_tool

OS := $(shell uname)

# MacOS has a slightly different name for grep, so check to see if it needs to be used.
ifeq ($(OS), Darwin)
	CXXFLAGS += -I/opt/homebrew/include 
	LDFLAGS += -I/opt/homebrew/lib -lpcre2-8
else
	CXXFLAGS += -Werror -Wall $(IGNORE_W_ERRORS) -lpcre2-8 
endif

BUILD_DIR := dkr_assets_tool_src/_build

ENUMS_HEADER := ../include/enums.h

# From: https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make/18258352#18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

default: all

n64crc_SOURCES := n64crc.c

all: $(PROGRAMS) recomp flips

# make clean for flips doesn't work, so just manually delete it on a clean. 
clean:
	rm -Rf $(PROGRAMS) $(BUILD_DIR)
	@make -C ido-static-recomp clean VERSION=5.3
	rm -f Flips/flips

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

#recomp likes to echo some strings on all calls to make, the >/dev/null will silence them.
recomp:
	@make -C ido-static-recomp VERSION=5.3 RELEASE=1 setup >/dev/null
	@make -C ido-static-recomp VERSION=5.3 RELEASE=1 >/dev/null

#Builds the CLI only version of flips. It will complain about it being debug, but this makes it much faster compile.
flips:
	@make -s -C Flips TARGET=cli

.PHONY: all clean distclean default

