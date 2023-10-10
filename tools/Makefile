CC := gcc
CXX := g++
CFLAGS := -I . -Wall -Wextra -Wno-unused-parameter -pedantic -std=c99 -O2 -s
CXXFLAGS := -I . -Wall -Wextra -std=c++17
LDFLAGS := -lm
PROGRAMS := n64crc dkr_assets_tool

BUILD_DIR := dkr_assets_tool_classes/_build

ENUMS_HEADER := ../include/enums.h

# From: https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make/18258352#18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

default: all

n64crc_SOURCES := n64crc.c

all: $(PROGRAMS) recomp

clean:
	rm -Rf $(PROGRAMS) $(BUILD_DIR)
	@make -C ido-static-recomp clean VERSION=5.3

distclean: clean

n64crc: n64crc.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

dkr_assets_tool_CPP_FILES := dkr_assets_tool.cpp \
                          $(call rwildcard,dkr_assets_tool_classes,*.cpp)

dkr_assets_tool_C_FILES := $(call rwildcard,dkr_assets_tool_classes,*.c)

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
	@make -C ido-static-recomp setup
	@make -C ido-static-recomp VERSION=5.3
	@printf "done\n"

.PHONY: all clean distclean default

