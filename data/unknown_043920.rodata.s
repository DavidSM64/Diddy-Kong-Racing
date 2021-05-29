.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6280
.aligned_text "%.1f,%.1f,%.1f\n" # Used with the Print Coordinates cheat?
.aligned_text "Chk ovflow!!\n"
.aligned_text "Back\n"

glabel D_800E62A8
.word 0xC0A38800

glabel D_800E62AC
.word 0x00000000

glabel D_800E62B0
.word 0x3F999999

glabel D_800E62B4
.word 0x9999999A

glabel D_800E62B8
.word 0x3FE1F3B6

glabel D_800E62BC
.word 0x45A1CAC1

glabel D_800E62C0
.word 0x3F70624D

glabel D_800E62C4
.word 0xD2F1A9FC

glabel D_800E62C8
.word 0x3F999999

glabel D_800E62CC
.word 0x9999999A

glabel D_800E62D0
.word 0x3FE1F3B6

glabel D_800E62D4
.word 0x45A1CAC1

glabel D_800E62D8
.word 0x3F70624D

glabel D_800E62DC
.word 0xD2F1A9FC

glabel D_800E62E0
.word 0x3FC99999

glabel D_800E62E4
.word 0x9999999A

glabel D_800E62E8
.word 0x3F70624D

glabel D_800E62EC
.word 0xD2F1A9FC

glabel D_800E62F0
.word 0x3FE30A3D

glabel D_800E62F4
.word 0x70A3D70A

glabel D_800E62F8
.word 0x3F999999

glabel D_800E62FC
.word 0x9999999A

glabel D_800E6300
.word 0x407F4000

glabel D_800E6304
.word 0x00000000

glabel D_800E6308
.word 0x40845000

glabel D_800E630C
.word 0x00000000

glabel D_800E6310
.word 0xBFD33333

glabel D_800E6314
.word 0x33333333

glabel D_800E6318
.word 0x800446AC
.word 0x80044A04
.word 0x80044A04
.word 0x80044A04
.word 0x80044A04
.word 0x80044F54
.word 0x80044A04

glabel D_800E6334
.word 0x80044A2C
.word 0x80044A44
.word 0x80044A60
.word 0x80044A94
.word 0x80044ADC
.word 0x80044AC8
.word 0x00000000

glabel D_800E6350
.word 0x4072C000

glabel D_800E6354
.word 0x00000000

glabel D_800E6358
.word 0x800456A0
.word 0x800456A8
.word 0x800456B0
.word 0x800456BC
.word 0x800456CC
.word 0x800456D4
.word 0x800456B0
.word 0x800456DC

glabel D_800E6378
.word 0x49742400

glabel D_800E637C
.word 0x80045ADC
.word 0x80045AF8
.word 0x80045B30
.word 0x80045B30
.word 0x80045B58
.word 0x80045B70
.word 0x80045BB8
.word 0x80045ADC
.word 0x00000000

glabel D_800E63A0
.word 0x407F4000

glabel D_800E63A4
.word 0x00000000

glabel D_800E63A8
.word 0x3FF26666

glabel D_800E63AC
.word 0x66666666

glabel D_800E63B0
.word 0x3F90624D

glabel D_800E63B4
.word 0xD2F1A9FC

glabel D_800E63B8
.word 0x3F90624D

glabel D_800E63BC
.word 0xD2F1A9FC

glabel D_800E63C0
.word 0x3FF33333

glabel D_800E63C4
.word 0x33333333

glabel D_800E63C8
.word 0x3FA78D4F

glabel D_800E63CC
.word 0xDF3B645A

glabel D_800E63D0
.word 0x3FF33333

glabel D_800E63D4
.word 0x33333333

glabel D_800E63D8
.word 0x3F99999A
.word 0x00000000

glabel D_800E63E0
.word 0x3FA78D4F

glabel D_800E63E4
.word 0xDF3B645A

glabel D_800E63E8
.word 0x3FD33333

glabel D_800E63EC
.word 0x33333333

glabel D_800E63F0
.word 0x3B83126F
.word 0x00000000

glabel D_800E63F8
.word 0x3F999999

glabel D_800E63FC
.word 0x9999999A

glabel D_800E6400
.word 0x4072C000

glabel D_800E6404
.word 0x00000000

glabel D_800E6408
.word 0x3F947AE1

glabel D_800E640C
.word 0x47AE147B

glabel D_800E6410
.word 0x3FFB3333

glabel D_800E6414
.word 0x33333333

glabel D_800E6418
.word 0x3FD66666

glabel D_800E641C
.word 0x66666666

glabel D_800E6420
.word 0x3FC99999

glabel D_800E6424
.word 0x9999999A

glabel D_800E6428
.word 0x3FB1EB85

glabel D_800E642C
.word 0x1EB851EC

glabel D_800E6430
.word 0x3FE99999

glabel D_800E6434
.word 0x9999999A

glabel D_800E6438
.word 0x3FE4CCCC

glabel D_800E643C
.word 0xCCCCCCCD

glabel D_800E6440
.word 0x3FE4CCCC

glabel D_800E6444
.word 0xCCCCCCCD

glabel D_800E6448
.word 0x40418000

glabel D_800E644C
.word 0x00000000

glabel D_800E6450
.word 0xC61C4000
.word 0x00000000

glabel D_800E6458
.word 0x3FE99999

glabel D_800E645C
.word 0x9999999A

glabel D_800E6460
.word 0x3FA99999

glabel D_800E6464
.word 0x9999999A

glabel D_800E6468
.word 0x3DE147AE

glabel D_800E646C
.word 0x80048D40
.word 0x80048D40
.word 0x80048E50
.word 0x80048DAC
.word 0x80048E18
.word 0x80048DB8
.word 0x00000000

glabel D_800E6488
.word 0x3FE66666

glabel D_800E648C
.word 0x66666666

glabel D_800E6490
.word 0x40348000

glabel D_800E6494
.word 0x00000000

glabel D_800E6498
.word 0x40504000

glabel D_800E649C
.word 0x00000000

glabel D_800E64A0
.word 0x3FC55555

glabel D_800E64A4
.word 0x55555555

glabel D_800E64A8
.word 0x3FF170A3

glabel D_800E64AC
.word 0xD70A3D71

glabel D_800E64B0
.word 0x3FD99999

glabel D_800E64B4
.word 0x9999999A

glabel D_800E64B8
.word 0x3F847AE1

glabel D_800E64BC
.word 0x47AE147B

glabel D_800E64C0
.word 0x3F847AE1

glabel D_800E64C4
.word 0x47AE147B

glabel D_800E64C8
.word 0x3F90624D

glabel D_800E64CC
.word 0xD2F1A9FC

glabel D_800E64D0
.word 0x3FF33333

glabel D_800E64D4
.word 0x33333333

glabel D_800E64D8
.word 0x3F99999A
.word 0x00000000

glabel D_800E64E0
.word 0x3F90624D

glabel D_800E64E4
.word 0xD2F1A9FC

glabel D_800E64E8
.word 0x3FB33333

glabel D_800E64EC
.word 0x3C23D70A

glabel D_800E64F0
.word 0x3CA3D70A

glabel D_800E64F4
.word 0x3B83126F

glabel D_800E64F8
.word 0x3FE33333

glabel D_800E64FC
.word 0x33333333

glabel D_800E6500
.word 0x3FD33333

glabel D_800E6504
.word 0x33333333

glabel D_800E6508
.word 0x3F99999A
.word 0x00000000

glabel D_800E6510
.word 0x3F23A92A

glabel D_800E6514
.word 0x30553261

glabel D_800E6518
.word 0x3FFCCCCC

glabel D_800E651C
.word 0xCCCCCCCD

glabel D_800E6520
.word 0x3FD99999

glabel D_800E6524
.word 0x9999999A

glabel D_800E6528
.word 0x3ECCCCCD
.word 0x00000000

glabel D_800E6530
.word 0x3FAE1E1E

glabel D_800E6534
.word 0x1E1E1E1E

glabel D_800E6538
.word 0x3FA99999

glabel D_800E653C
.word 0x9999999A

glabel D_800E6540
.word 0x3FE4CCCC

glabel D_800E6544
.word 0xCCCCCCCD

glabel D_800E6548
.word 0x3FE4CCCC

glabel D_800E654C
.word 0xCCCCCCCD

glabel D_800E6550
.word 0x3FE66666

glabel D_800E6554
.word 0x66666666

glabel D_800E6558
.word 0x3FD99999

glabel D_800E655C
.word 0x9999999A

glabel D_800E6560
.word 0x3F76C16C

glabel D_800E6564
.word 0x16C16C17

glabel D_800E6568
.word 0x3ECCCCCD
.word 0x00000000

glabel D_800E6570
.word 0x40504000

glabel D_800E6574
.word 0x00000000

glabel D_800E6578
.word 0x3FC99999

glabel D_800E657C
.word 0x9999999A

glabel D_800E6580
.word 0x3FA66666

glabel D_800E6584
.word 0x3DCCCCCD

glabel D_800E6588
.word 0x3B03126F

glabel D_800E658C
.word 0x3C23D70A

glabel D_800E6590
.word 0x3FF33333

glabel D_800E6594
.word 0x33333333

glabel D_800E6598
.word 0x3FDCCCCC

glabel D_800E659C
.word 0xCCCCCCCD

glabel D_800E65A0
.word 0xBCA3D70A

glabel D_800E65A4
.word 0x3F5EB852

glabel D_800E65A8
.word 0x3F666666

glabel D_800E65AC
.word 0xC61C4000

glabel D_800E65B0
.word 0x8004EB84
.word 0x8004EBBC
.word 0x8004EBD8
.word 0x8004EBF4
.word 0x8004EBA0
.word 0x8004EC10
.word 0x8004EC50
.word 0x8004EC90
.word 0x8004EC90
.word 0x8004ED88
.word 0x8004EBF4
.word 0x8004ECD0
.word 0x8004ED10
.word 0x8004ED50

glabel D_800E65E8
.word 0x3F8F5C29

glabel D_800E65EC
.word 0x3CA3D70A

glabel D_800E65F0
.word 0xBCA3D70A

glabel D_800E65F4
.word 0x43848000

glabel D_800E65F8
.word 0x40977000

glabel D_800E65FC
.word 0x00000000

glabel D_800E6600
.word 0x3FB0A3D7

glabel D_800E6604
.word 0x0A3D70A4

glabel D_800E6608
.word 0x3FD33333

glabel D_800E660C
.word 0x33333333

glabel D_800E6610
.word 0x3FB99999

glabel D_800E6614
.word 0x9999999A

glabel D_800E6618
.word 0x3FD33333

glabel D_800E661C
.word 0x33333333

glabel D_800E6620
.word 0x3FB99999

glabel D_800E6624
.word 0x9999999A

glabel D_800E6628
.word 0x3F70624D

glabel D_800E662C
.word 0xD2F1A9FC

glabel D_800E6630
.word 0x3FE4CCCC

glabel D_800E6634
.word 0xCCCCCCCD

glabel D_800E6638
.word 0x3F999999

glabel D_800E663C
.word 0x99999999

glabel D_800E6640
.word 0x3FD99999

glabel D_800E6644
.word 0x9999999A

glabel D_800E6648
.word 0x3FF19999

glabel D_800E664C
.word 0x9999999A

glabel D_800E6650
.word 0xBFD33333

glabel D_800E6654
.word 0x33333333

glabel D_800E6658
.word 0x3FD33333

glabel D_800E665C
.word 0x33333333

glabel D_800E6660
.word 0x3CA3D70A
.word 0x00000000

glabel D_800E6668
.word 0x3FECCCCC

glabel D_800E666C
.word 0xCCCCCCCD

glabel D_800E6670
.word 0x3FE66666

glabel D_800E6674
.word 0x66666666

glabel D_800E6678
.word 0x3FFB3333

glabel D_800E667C
.word 0x33333333

glabel D_800E6680
.word 0x3FC33333

glabel D_800E6684
.word 0x33333333

glabel D_800E6688
.word 0x3FD33333

glabel D_800E668C
.word 0x33333333

glabel D_800E6690
.word 0x3FD47AE1

glabel D_800E6694
.word 0x47AE147B

glabel D_800E6698
.word 0xBFA47AE1

glabel D_800E669C
.word 0x47AE147B

glabel D_800E66A0
.word 0x3FA47AE1

glabel D_800E66A4
.word 0x47AE147B

glabel D_800E66A8
.word 0x3FECCCCC

glabel D_800E66AC
.word 0xCCCCCCCD

glabel D_800E66B0
.word 0x3FD33333

glabel D_800E66B4
.word 0x33333333

glabel D_800E66B8
.word 0x3FB99999

glabel D_800E66BC
.word 0x9999999A

glabel D_800E66C0
.word 0x3DCCCCCD
.word 0x00000000

glabel D_800E66C8
.word 0x3FA99999

glabel D_800E66CC
.word 0x9999999A

glabel D_800E66D0
.word 0x80052678
.word 0x80052978
.word 0x80052978
.word 0x800527AC
.word 0x8005280C
.word 0x80052858
.word 0x800528A4
.word 0x80052910

glabel D_800E66F0
.word 0x3FEF0A3D

glabel D_800E66F4
.word 0x70A3D70A

glabel D_800E66F8
.word 0x3FEBD70A

glabel D_800E66FC
.word 0x3D70A3D7

glabel D_800E6700
.word 0x3FECCCCC

glabel D_800E6704
.word 0xCCCCCCCD

glabel D_800E6708
.word 0x3FD33333

glabel D_800E670C
.word 0x33333333

glabel D_800E6710
.word 0x3FF99999

glabel D_800E6714
.word 0x9999999A

glabel D_800E6718
.word 0x3F999999

glabel D_800E671C
.word 0x9999999A

glabel D_800E6720
.word 0x3EE66666
.word 0x00000000

glabel D_800E6728
.word 0x3FEF0A3D

glabel D_800E672C
.word 0x70A3D70A

glabel D_800E6730
.word 0x3FC99999

glabel D_800E6734
.word 0x9999999A

glabel D_800E6738
.word 0x3FC99999

glabel D_800E673C
.word 0x9999999A

glabel D_800E6740
.word 0x3FF547AE

glabel D_800E6744
.word 0x147AE148

glabel D_800E6748
.word 0x3FE0F5C2

glabel D_800E674C
.word 0x8F5C28F6

glabel D_800E6750
.word 0x3FFCCCCC

glabel D_800E6754
.word 0xCCCCCCCD

glabel D_800E6758
.word 0x3FE66666
.word 0x00000000

glabel D_800E6760
.word 0x3FC99999

glabel D_800E6764
.word 0x9999999A

glabel D_800E6768
.word 0x3FB99999

glabel D_800E676C
.word 0x9999999A

glabel D_800E6770
.word 0x3FC99999
.word 0x9999999A

glabel D_800E6778
.word 0x3FA99999
.word 0x9999999A

glabel D_800E6780
.word 0x3FB99999

glabel D_800E6784
.word 0x9999999A

glabel D_800E6788
.word 0x3FD99999

glabel D_800E678C
.word 0x9999999A

glabel D_800E6790
.word 0x3FB99999

glabel D_800E6794
.word 0x9999999A

glabel D_800E6798
.word 0x3FF66666

glabel D_800E679C
.word 0x66666666

glabel D_800E67A0
.word 0x3DCCCCCD

glabel D_800E67A4
.word 0x80053FF0
.word 0x8005406C
.word 0x800540FC
.word 0x8005408C
.word 0x800540C4
.word 0x80054098
.word 0x00000000

glabel D_800E67C0
.word 0x40348000

glabel D_800E67C4
.word 0x00000000

glabel D_800E67C8
.word 0x3FD33333

glabel D_800E67CC
.word 0x33333333

glabel D_800E67D0
.word 0x3FB99999

glabel D_800E67D4
.word 0x9999999A

glabel D_800E67D8
.word 0x3FD33333

glabel D_800E67DC
.word 0x33333333

glabel D_800E67E0
.word 0x3FB99999

glabel D_800E67E4
.word 0x9999999A

glabel D_800E67E8
.word 0xBFD33333

glabel D_800E67EC
.word 0x33333333

glabel D_800E67F0
.word 0x3FD33333

glabel D_800E67F4
.word 0x33333333

glabel D_800E67F8
.word 0x3FECCCCC

glabel D_800E67FC
.word 0xCCCCCCCD

glabel D_800E6800
.word 0x3CA3D70A
.word 0x00000000

glabel D_800E6808
.word 0x3FFB3333

glabel D_800E680C
.word 0x33333333

glabel D_800E6810
.word 0x3FC33333

glabel D_800E6814
.word 0x33333333

glabel D_800E6818
.word 0x3FD47AE1

glabel D_800E681C
.word 0x47AE147B

glabel D_800E6820
.word 0xBFA47AE1

glabel D_800E6824
.word 0x47AE147B

glabel D_800E6828
.word 0x3FA47AE1

glabel D_800E682C
.word 0x47AE147B

glabel D_800E6830
.word 0x3FECCCCC

glabel D_800E6834
.word 0xCCCCCCCD

glabel D_800E6838
.word 0x3FF13333

glabel D_800E683C
.word 0x33333333

glabel D_800E6840
.word 0x3FC33333

glabel D_800E6844
.word 0x33333333

glabel D_800E6848
.word 0x3FE66666

glabel D_800E684C
.word 0x66666666

glabel D_800E6850
.word 0x44BB8000

glabel D_800E6854
.word 0x8005635C
.word 0x80056370
.word 0x80056380
.word 0x8005639C
.word 0x800563EC
.word 0x80056508
.word 0x8005655C
.word 0x80056508
.word 0x800563EC
.word 0x80056620
.word 0x800563CC
.word 0x80056380
.word 0x800565C0
.word 0x800565E0
.word 0x80056600
.word 0x800563EC
.word 0x80056828

glabel D_800E6894
.word 0x80056834
.word 0x80056840
.word 0x8005684C
.word 0x80056884
.word 0x80056884
.word 0x80056884
.word 0x80056884
.word 0x80056884
.word 0x80056884
.word 0x80056874
.word 0x80056880

glabel D_800E68C4
.word 0x461C4000

glabel D_800E68C8
.word 0x461C4000

glabel D_800E68CC
.word 0x3CCCCCCD

glabel D_800E68D0
.word 0x80057BBC
.word 0x80057BE4
.word 0x80057CD0
.word 0x80057C0C
.word 0x80057C34
.word 0x80057C5C
.word 0x80057C84
.word 0x80057CAC

glabel D_800E68F0
.word 0x4056F000

glabel D_800E68F4
.word 0x00000000

glabel D_800E68F8
.word 0x40568000

glabel D_800E68FC
.word 0x00000000

glabel D_800E6900
.word 0x40484000

glabel D_800E6904
.word 0x00000000

glabel D_800E6908
.word 0x3FEE6666

glabel D_800E690C
.word 0x66666666

glabel D_800E6910
.word 0x40504000

glabel D_800E6914
.word 0x00000000

glabel D_800E6918
.word 0x3FF4CCCC

glabel D_800E691C
.word 0xCCCCCCCD

glabel D_800E6920
.word 0xBFC99999

glabel D_800E6924
.word 0x9999999A

glabel D_800E6928
.word 0x3FF33333

glabel D_800E692C
.word 0x33333333

glabel D_800E6930
.word 0x3FF33333

glabel D_800E6934
.word 0x33333333

glabel D_800E6938
.word 0x3FE99999

glabel D_800E693C
.word 0x9999999A

glabel D_800E6940
.word 0x3FDCCCCC

glabel D_800E6944
.word 0xCCCCCCCD

glabel D_800E6948
.word 0xBCA3D70A

glabel D_800E694C
.word 0x49742400

glabel D_800E6950
.word 0x41038800

glabel D_800E6954
.word 0x00000000

glabel D_800E6958
.word 0x3F4CCCCD
.word 0x00000000

glabel D_800E6960
.word 0x41038800

glabel D_800E6964
.word 0x00000000

glabel D_800E6968
.word 0x8005AF80
.word 0x8005AFD8
.word 0x8005B004
.word 0x8005B030
.word 0x8005AFAC
.word 0x8005B05C
.word 0x8005B094
.word 0x8005B0CC
.word 0x8005B0CC
.word 0x8005B1B0
.word 0x8005B030
.word 0x8005B10C
.word 0x8005B144
.word 0x8005B17C

glabel D_800E69A0
.word 0x3FECCCCC

glabel D_800E69A4
.word 0xCCCCCCCD

glabel D_800E69A8
.word 0x3CA3D70A

glabel D_800E69AC
.word 0xBCA3D70A

glabel D_800E69B0
.word 0x43848000
.word 0x00000000

glabel D_800E69B8
.word 0x40977000

glabel D_800E69BC
.word 0x00000000

glabel D_800E69C0
.word 0x3F999999

glabel D_800E69C4
.word 0x9999999A

glabel D_800E69C8
.word 0x3FE30A3D

glabel D_800E69CC
.word 0x70A3D70A

glabel D_800E69D0
.word 0x3F70624D

glabel D_800E69D4
.word 0xD2F1A9FC

glabel D_800E69D8
.word 0x3FF4CCCC

glabel D_800E69DC
.word 0xCCCCCCCD

glabel D_800E69E0
.word 0x4062C000

glabel D_800E69E4
.word 0x00000000

glabel D_800E69E8
.word 0x3C23D70A
.word 0x00000000

glabel D_800E69F0
.word 0x3F847AE1

glabel D_800E69F4
.word 0x47AE147B

glabel D_800E69F8
.word 0x40418000

glabel D_800E69FC
.word 0x00000000

glabel D_800E6A00
.word 0x3D4CCCCD
.word 0x00000000
.word 0x00000000
.word 0x00000000
