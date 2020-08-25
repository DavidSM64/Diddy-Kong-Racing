CC := gcc
CXX := g++
CFLAGS := -I . -Wall -Wextra -Wno-unused-parameter -pedantic -std=c99 -O2 -s
LDFLAGS := -lm
PROGRAMS := n64crc 
CXX_PROGRAMS := dkr_cheats_encryptor dkr_decompressor dkr_extractor dkr_texbuilder

default: all

n64crc_SOURCES := n64crc.c

dkr_cheats_encryptor_SOURCES := dkr_cheats_encryptor.cpp

dkr_decompressor_SOURCES := dkr_decompressor.cpp $(wildcard dkr_decompressor_src/*.cpp dkr_decompressor_src/*.c)
dkr_decompressor_CXXFLAGS := -lstdc++fs -lcrypto -lssl

dkr_extractor_SOURCES := dkr_extractor.cpp $(wildcard dkr_decompressor_src/*.cpp dkr_decompressor_src/*.c dkr_extractor_classes/*.cpp n64graphics/*.c)
dkr_extractor_CXXFLAGS := -lstdc++fs -lcrypto -lssl -lpthread

dkr_texbuilder_SOURCES := dkr_texbuilder.cpp $(wildcard dkr_decompressor_src/*.cpp dkr_decompressor_src/*.c n64graphics/*.c)
dkr_texbuilder_CXXFLAGS := -lstdc++fs

all: $(PROGRAMS) $(CXX_PROGRAMS)

clean:
	$(RM) $(PROGRAMS) $(CXX_PROGRAMS)

define COMPILE
$(1): $($1_SOURCES)
	$(CC) $(CFLAGS) $($1_CFLAGS) $$^ -o $$@ $(LDFLAGS) $($1_LDFLAGS)
endef

define COMPILE_CXX
$(1): $($1_SOURCES)
	$(CXX) $$^ -o $$@ $($1_CXXFLAGS) $(LDFLAGS) $($1_LDFLAGS)
endef

$(foreach p,$(PROGRAMS),$(eval $(call COMPILE,$(p))))
$(foreach p,$(CXX_PROGRAMS),$(eval $(call COMPILE_CXX,$(p))))

.PHONY: all clean default
