.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

# Used in the title screen sequence.
.aligned_text "TIMBER"
.aligned_text "BUMPER"
.aligned_text "CONKER"
.aligned_text "TIPTUP"
.aligned_text "DRUMSTICK"
.aligned_text "PIPSY"
.aligned_text "BANJO"
.aligned_text "KRUNCH"
.aligned_text "WIZPIG"
.aligned_text "DIDDY"

.float 0.5

# Credits, 800E7D08
.aligned_text "CREDITS"

.aligned_text "Software Director"
.aligned_text "R.Harrison"

.aligned_text "Software Engineers"
.aligned_text "P.Mountain"
.aligned_text "J.Pegg"
.aligned_text "R.Gale"

.aligned_text "Art Director"
.aligned_text "K.Bayliss"

.aligned_text "3D Artists"
.aligned_text "L.Musgrave"
.aligned_text "K.Rabbette"
.aligned_text "D.Smith"
.aligned_text "J.Christensen"
.aligned_text "B.Smyth"
.aligned_text "P.Cunningham"

.aligned_text "Music"
.aligned_text "D.Wise"

.aligned_text "Sound Effects"
.aligned_text "G.Norgate"

.aligned_text "ALSO"

.aligned_text "Additional Design"
.aligned_text "M.Wakeley"

.aligned_text "Documentation"
.aligned_text "L.Loveday"
.aligned_text "Liason"
.aligned_text "E.Hochberg"

.aligned_text "Character Voices"
.aligned_text "K.Bayliss"
.aligned_text "J.Christensen"
.aligned_text "E.Fischer"
.aligned_text "K.Rabbette"
.aligned_text "L.Ray"
.aligned_text "L.Schuneman"
.aligned_text "C.Seavor"
.aligned_text "D.Smith"
.aligned_text "J.Stamper"
.aligned_text "K.Stamper"
.aligned_text "C.Sutherland"

.aligned_text "Rare Quality Assurance"
.aligned_text "H.Ward"
.aligned_text "G.Richards"
.aligned_text "S.Farmer"
.aligned_text "J.Williams"
.aligned_text "D.Wong"
.aligned_text "G.Jones"
.aligned_text "M.Penny"
.aligned_text "S.Brand"
.aligned_text "S.Malpass"
.aligned_text "A.Wilson"

.aligned_text "NOA Thanks To"
.aligned_text "M.Fukuda"
.aligned_text "K.Lobb"
.aligned_text "M.Kelbaugh"
.aligned_text "A.Williams"
.aligned_text "R.Johnson"
.aligned_text "M.Forrest"
.aligned_text "P.Sandhop"
.aligned_text "H.Sterchi"
.aligned_text "T.Hertzog"
.aligned_text "D.Bridgham"
.aligned_text "G.Richardson"
.aligned_text "B.Smith"

.aligned_text "NOA Thanks To"
.aligned_text "NOA Tree House"
.aligned_text "NOA Tree Branch"

.aligned_text "NCL Thank You's"
.aligned_text "K.Terasaki"
.aligned_text "M.Goto"
.aligned_text "H.Yamada"
.aligned_text "Mario Club"

.aligned_text "NOE Thank You's"
.aligned_text "J.Kraft"
.aligned_text "J.Bardakoff"

.aligned_text "Special Thanks To"
.aligned_text "J.Hochberg"
.aligned_text "H.Lincoln"
.aligned_text "M.Arakawa"

.aligned_text "Game Director"
.aligned_text "L.Schuneman"

.aligned_text "Producer"
.aligned_text "C.Stamper"

.aligned_text "Executive Producer"
.aligned_text "T.Stamper"

# Developer's best times for each track
.aligned_text "0:53:43"
.aligned_text "1:21:55"
.aligned_text "0:54:13"
.aligned_text "1:22:48"
.aligned_text "1:04:11"
.aligned_text "1:13:51"
.aligned_text "1:25:01"
.aligned_text "0:55:05"
.aligned_text "1:37:63"
.aligned_text "1:56:60"
.aligned_text "0:57:81"
.aligned_text "1:28:01"
.aligned_text "1:51:15"
.aligned_text "1:31:80"
.aligned_text "2:03:16"
.aligned_text "0:58:25"
.aligned_text "2:00:38"
.aligned_text "2:05:68"
.aligned_text "1:52:96"
.aligned_text "1:55:00"

.aligned_text "THE END?"

.aligned_text "TO BE CONTINUED ..."

.aligned_text "THE END"

# This appears if you use the "WHODIDTHIS" cheat. You have to beat wizpig to get cheat codes.
.aligned_text "NO CHEAT"
.aligned_text "THIS TIME."

### End of credits ###

.aligned_text " (ADV."

glabel D_800E8208
.aligned_text "OK?"

glabel D_800E820C
.aligned_text "~"

glabel D_800E8210
.aligned_text "DEL"

glabel D_800E8214
.aligned_text "OK"

# Used with the "DODGYROMMER" cheat.
glabel D_800E8218
.aligned_text "ROM checksum %08X,%d\n"

glabel D_800E8230
.aligned_text "OK?"

glabel D_800E8234
.aligned_text "OK?"

glabel D_800E8238
.aligned_text "OK?"

glabel D_800E823C
.aligned_text "OK?"

glabel D_800E8240
.aligned_text "OK?"

glabel D_800E8244
.aligned_text "SP"

glabel D_800E8248
.aligned_text "DEL"

glabel D_800E824C
.aligned_text "OK"

.aligned_text "loadFrontEndItem() - Item no %d out of range 0-%d\n"

glabel D_800E8284
.word 0x80081464
.word 0x80081454
.word 0x8008158C
.word 0x800814C4
.word 0x8008158C
.word 0x80081504
.word 0x800814E4
.word 0x8008158C
.word 0x8008158C
.word 0x8008158C
.word 0x800814A4
.word 0x800814B4
.word 0x80081474
.word 0x80081484
.word 0x80081494
.word 0x800814F4
.word 0x8008158C
.word 0x80081514
.word 0x8008158C
.word 0x800814D4
.word 0x80081524
.word 0x80081534
.word 0x8008158C
.word 0x80081544
.word 0x80081554
.word 0x80081564
.word 0x80081574
.word 0x8008158C
.word 0x80081584

glabel D_800E82F8
.word 0x80081634
.word 0x80081620
.word 0x800817AC
.word 0x800816AC
.word 0x800817AC
.word 0x800816FC
.word 0x800816C0
.word 0x800817AC
.word 0x800817AC
.word 0x800817AC
.word 0x80081684
.word 0x80081698
.word 0x80081648
.word 0x8008165C
.word 0x80081670
.word 0x800816E8
.word 0x800817AC
.word 0x80081710
.word 0x800817AC
.word 0x800816D4
.word 0x80081724
.word 0x80081738
.word 0x800817AC
.word 0x8008174C
.word 0x80081760
.word 0x80081774
.word 0x80081788
.word 0x800817AC
.word 0x8008179C

glabel D_800E836C
.word 0x800823E8
.word 0x80082454
.word 0x800824B8
.word 0x80082524
.word 0x8008256C
.word 0x80082608
.word 0x80082760
.word 0x800827C0

glabel D_800E838C
.word 0x40266666

glabel D_800E8390
.word 0x400AE148
.word 0x00000000

glabel D_800E8398
.word 0x407FE000

glabel D_800E839C
.word 0x00000000

glabel D_800E83A0
.word 0x407FE000

glabel D_800E83A4
.word 0x00000000

glabel D_800E83A8
.word 0x407FE000

glabel D_800E83AC
.word 0x00000000

glabel D_800E83B0
.word 0x3F2B851F

glabel D_800E83B4
.word 0x40351EB8

glabel D_800E83B8
.word 0x8008541C
.word 0x8008553C
.word 0x80085574
.word 0x80085690
.word 0x800856DC
.word 0x80085728
.word 0x80085828
.word 0x80085774
.word 0x800857C0
.word 0x800857F0

glabel D_800E83E0
.word 0x80085C30
.word 0x80085BF8
.word 0x80085BF8
.word 0x80085C00
.word 0x80085C00
.word 0x80085C08
.word 0x80085C14
.word 0x80085C24

glabel D_800E8400
.word 0x80086834
.word 0x80086888
.word 0x800868C0
.word 0x80086920
.word 0x80086998

glabel D_800E8414
.word 0x3DCCCCCD

glabel D_800E8418
.word 0x80086B54
.word 0x80086CDC
.word 0x80086D54
.word 0x80086F74
.word 0x80087084
.word 0x80087110
.word 0x800871C4
.word 0x800871C4
.word 0x800871C4
.word 0x80087158

glabel D_800E8440
.word 0x800878D4
.word 0x800878D4
.word 0x800878D4
.word 0x800878F0
.word 0x800878BC
.word 0x800878F0
.word 0x800878E0
.word 0x800878F0
.word 0x800878D4

glabel D_800E8464
.word 0x80087930
.word 0x80087948
.word 0x80087948
.word 0x80087964
.word 0x80087930
.word 0x80087964
.word 0x80087954
.word 0x80087964
.word 0x80087948

glabel D_800E8488
.word 0x800879A4
.word 0x800879A4
.word 0x800879A4
.word 0x80087B50
.word 0x800879A4
.word 0x80087B50
.word 0x800879A4
.word 0x80087B50
.word 0x800879BC
.word 0x800879BC

glabel D_800E84B0
.word 0x80087D18
.word 0x80087D28
.word 0x80087D54
.word 0x80087D94
.word 0x80087DAC
.word 0x80087DEC
.word 0x80087E04
.word 0x80087E1C

glabel D_800E84D0
.word 0x3FF19999

glabel D_800E84D4
.word 0x9999999A

glabel D_800E84D8
.word 0x3F99999A
.word 0x00000000

glabel D_800E84E0
.word 0x3FB99999

glabel D_800E84E4
.word 0x9999999A

glabel D_800E84E8
.word 0x3FB99999

glabel D_800E84EC
.word 0x9999999A

glabel D_800E84F0
.word 0x3F99999A

glabel D_800E84F4
.word 0x8009246C
.word 0x8009251C
.word 0x80092740
.word 0x8009287C
.word 0x8009287C

glabel D_800E8508
.word 0x80094DD0
.word 0x80094FB0
.word 0x80095084
.word 0x80095588
.word 0x80095110
.word 0x800951CC

glabel D_800E8520
.word 0x3F99999A

glabel D_800E8524
.word 0x80095650
.word 0x800956C8
.word 0x800956C8
.word 0x80095668
.word 0x80095650
.word 0x80095668
.word 0x80095680
.word 0x80095698
.word 0x800956B0

glabel D_800E8548
.word 0x80095948
.word 0x80095964
.word 0x80095B34
.word 0x80095D30
.word 0x80095D50
.word 0x80095EA8
.word 0x80095EC8
.word 0x800964AC
.word 0x800964DC

glabel D_800E856C
.word 0x3DCCCCCD

glabel D_800E8570
.word 0x3D99999A

glabel D_800E8574
.word 0x8009BA98
.word 0x8009BAD8
.word 0x8009BB08
.word 0x8009BB48
.word 0x8009BB9C

glabel D_800E8588
.word 0x8009D0B8
.word 0x8009D104
.word 0x8009D0C8
.word 0x8009D0D8
.word 0x8009D0E8
.word 0x8009D0F8

glabel D_800E85A0
.word 0x8009D944
.word 0x8009D944
.word 0x8009D944
.word 0x8009D91C
.word 0x8009D8F0
.word 0x8009D8D4
.word 0x8009D8D4
.word 0x8009D8D4
.word 0x8009D618
.word 0x8009D638
.word 0x8009D7A0
.word 0x8009D840
.word 0x8009D968
.word 0x8009D998
.word 0x8009D9B0
.word 0x8009D9B0

glabel D_800E85E0
.word 0x8009DC60
.word 0x8009DEF0
.word 0x8009E37C
.word 0x8009E37C
.word 0x8009DFB0
.word 0x8009DFEC
.word 0x8009E098
.word 0x8009E194
.word 0x8009E23C
.word 0x8009E37C
.word 0x8009DC60

glabel D_800E860C
.word 0x8009E2D0
.word 0x8009E2F4
.word 0x8009E354
.word 0x8009E354
.word 0x8009E314
.word 0x8009E354
.word 0x8009E314
.word 0x8009E2E4
.word 0x8009E354
.word 0x8009E334
.word 0x00000000
.word 0x00000000
.word 0x00000000
