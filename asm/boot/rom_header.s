# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # 64-bit instructions are used

# header
.byte  0x80, 0x37, 0x12, 0x40 # PI BSD Domain 1 register
.word  0x0000000F # clock rate setting
.word  0x80100400 # entry point
.word  0x00001447 # release
.word  0x53D440E7 # checksum1
.word  0x7519B011 # checksum2
.word  0x00000000 # unknown
.word  0x00000000 # unknown
.ascii "Diddy Kong Racing   " # ROM name: 20 bytes
.word  0x00000000 # unknown
.word  0x0000004E # cartridge
.ascii "DY"       # cartridge ID
.ascii "E"        # country
.byte  0x00       # version
