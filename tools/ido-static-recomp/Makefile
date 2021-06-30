# Originally from: https://github.com/farisawan-2000/libreultra/tree/master/tools/ido-5.3recomp/ido5.3_recomp

IRIX_ROOT := ../ido5.3_compiler
OUT := ../ido5.3_recomp
CXX := g++
GCC := gcc

DUMMY != echo "Statically recompiling IDO 5.3. This might take a while." >&2 || echo FAIL
DUMMY != mkdir -p $(OUT) >&2 || echo FAIL

cc: OPT_CFLAGS := -O2
cfe: OPT_CFLAGS := -O2
uopt: OPT_CFLAGS := -O2
ugen: OPT_CFLAGS := -O2
as1: OPT_CFLAGS := -O2
acpp: OPT_CFLAGS := -O2

RECOMP := recomp

all: cc cfe uopt ugen as1 err.english.cc

clean:
	$(RM) cc* cfe* uopt* ugen* as1* err.english.cc $(RECOMP)

recomp: recomp.cpp
	g++ recomp.cpp -o $(RECOMP) -g -lcapstone
    
err.english.cc: $(IRIX_ROOT)/usr/lib/err.english.cc
	cp $^ $(OUT)/$@

cc_c.c: $(IRIX_ROOT)/usr/bin/cc $(RECOMP)
	./$(RECOMP) $< > $@

%_c.c: $(IRIX_ROOT)/usr/lib/% $(RECOMP)
	./$(RECOMP) $< > $@

%: %_c.c 
	$(GCC) libc_impl.c $< -o $@ $(OPT_CFLAGS) -fno-strict-aliasing -lm -no-pie -DIDO53
	mv $@ $(OUT)/$@

.PHONY: all clean