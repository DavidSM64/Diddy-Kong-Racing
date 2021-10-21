/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1991 */

// The RAM_POS above is just a hack to put it after osViMgr.c

#include "libultra_internal.h"
#include "viint.h"

/*
 * Video Interface (VI) mode type
 */
#define OS_VI_NTSC_LPN1		0	/* NTSC */
#define OS_VI_NTSC_LPF1		1
#define OS_VI_NTSC_LAN1		2
#define OS_VI_NTSC_LAF1		3
#define OS_VI_NTSC_LPN2		4
#define OS_VI_NTSC_LPF2		5
#define OS_VI_NTSC_LAN2		6
#define OS_VI_NTSC_LAF2		7
#define OS_VI_NTSC_HPN1		8
#define OS_VI_NTSC_HPF1		9
#define OS_VI_NTSC_HAN1		10
#define OS_VI_NTSC_HAF1		11
#define OS_VI_NTSC_HPN2		12
#define OS_VI_NTSC_HPF2		13

#define OS_VI_PAL_LPN1		14	/* PAL */
#define OS_VI_PAL_LPF1		15
#define OS_VI_PAL_LAN1		16
#define OS_VI_PAL_LAF1		17
#define OS_VI_PAL_LPN2		18
#define OS_VI_PAL_LPF2		19
#define OS_VI_PAL_LAN2		20
#define OS_VI_PAL_LAF2		21
#define OS_VI_PAL_HPN1		22
#define OS_VI_PAL_HPF1		23
#define OS_VI_PAL_HAN1		24
#define OS_VI_PAL_HAF1		25
#define OS_VI_PAL_HPN2		26
#define OS_VI_PAL_HPF2		27

#define OS_VI_MPAL_LPN1		28	/* MPAL - mainly Brazil */
#define OS_VI_MPAL_LPF1		29
#define OS_VI_MPAL_LAN1		30
#define OS_VI_MPAL_LAF1		31
#define OS_VI_MPAL_LPN2		32
#define OS_VI_MPAL_LPF2		33
#define OS_VI_MPAL_LAN2		34
#define OS_VI_MPAL_LAF2		35
#define OS_VI_MPAL_HPN1		36
#define OS_VI_MPAL_HPF1		37
#define OS_VI_MPAL_HAN1		38
#define OS_VI_MPAL_HAF1		39
#define OS_VI_MPAL_HPN2		40
#define OS_VI_MPAL_HPF2		41

/*
 * Video Interface (VI) special features
 */
#define	OS_VI_GAMMA_ON			0x0001
#define	OS_VI_GAMMA_OFF			0x0002
#define	OS_VI_GAMMA_DITHER_ON		0x0004
#define	OS_VI_GAMMA_DITHER_OFF		0x0008
#define	OS_VI_DIVOT_ON			0x0010
#define	OS_VI_DIVOT_OFF			0x0020
#define	OS_VI_DITHER_FILTER_ON		0x0040
#define	OS_VI_DITHER_FILTER_OFF		0x0080

/*
 * Video Interface (VI) mode attribute bit
 */
#define OS_VI_BIT_NONINTERLACE		0x0001          /* lo-res */
#define OS_VI_BIT_INTERLACE		0x0002          /* lo-res */
#define OS_VI_BIT_NORMALINTERLACE	0x0004          /* hi-res */
#define OS_VI_BIT_DEFLICKINTERLACE	0x0008          /* hi-res */
#define OS_VI_BIT_ANTIALIAS		0x0010
#define OS_VI_BIT_POINTSAMPLE		0x0020
#define OS_VI_BIT_16PIXEL		0x0040
#define OS_VI_BIT_32PIXEL		0x0080
#define OS_VI_BIT_LORES			0x0100
#define OS_VI_BIT_HIRES			0x0200
#define OS_VI_BIT_NTSC			0x0400
#define OS_VI_BIT_PAL			0x0800

OSViMode osViModeTable[42] = {
    {OS_VI_NTSC_LPN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(525),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LPF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LAN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_ANTIALIAS_MODE_1 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(525),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LAF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LPN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_ANTIALIAS_MODE_3 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(525),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LPF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LAN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(525),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_LAF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_HPN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_HPF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_HAN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_HAF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_HPN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_3 |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(2560),       //origin
          SCALE(1, 0),        //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(5120),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_NTSC_HPF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(57, 34, 5, 62), //burst
         VSYNC(524),           //vSync
         HSYNC(3093, 0),       //hSync
         LEAP(3093, 3093),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(2560),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(35, 509),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(5120),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_PAL_LPN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(625),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),         //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(640),         //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      }}},
    {OS_VI_PAL_LPF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),         //origin
          SCALE(1, 0.25),      //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(640),          //origin
          SCALE(1, 0.75),       //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_LAN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_ANTIALIAS_MODE_1 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(625),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),         //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(640),         //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      }}},
    {OS_VI_PAL_LAF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),         //origin
          SCALE(1, 0.25),      //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(640),          //origin
          SCALE(1, 0.75),       //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_LPN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_ANTIALIAS_MODE_3 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(625),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(1280),        //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      }}},
    {OS_VI_PAL_LPF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(1, 0.25),      //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(1280),         //origin
          SCALE(1, 0.75),       //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_LAN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(625),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(1280),        //origin
          SCALE(1, 0),         //yScale
          HSTART(95, 569),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      }}},
    {OS_VI_PAL_LAF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(1, 0.25),      //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(1280),         //origin
          SCALE(1, 0.75),       //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_HPN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(1, 0),         //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(2560),         //origin
          SCALE(1, 0),          //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_HPF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(0.5, 0.5),     //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(2560),         //origin
          SCALE(0.5, 0.5),      //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_HAN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(1, 0),         //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(2560),         //origin
          SCALE(1, 0),          //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_HAF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),        //origin
          SCALE(0.5, 0.5),     //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(2560),         //origin
          SCALE(0.5, 0.5),      //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_HPN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_3 |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(2560),        //origin
          SCALE(1, 0),         //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(5120),         //origin
          SCALE(1, 0),          //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_PAL_HPF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(58, 35, 4, 64), //burst
         VSYNC(624),           //vSync
         HSYNC(3177, 21),      //hSync
         LEAP(3183, 3182),     //leap
         HSTART(128, 768),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(2560),        //origin
          SCALE(0.5, 0.5),     //yScale
          HSTART(93, 567),     //vStart
          BURST(107, 2, 9, 0), //vBurst
          VINTR(2),            //vIntr
      },
      {
          //[1]
          ORIGIN(5120),         //origin
          SCALE(0.5, 0.5),      //yScale
          HSTART(95, 569),      //vStart
          BURST(105, 2, 13, 0), //vBurst
          VINTR(2),             //vIntr
      }}},
    {OS_VI_MPAL_LPN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(525),           //vSync
         HSYNC(3089, 4),       //hSync
         LEAP(3097, 3098),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LPF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LAN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_ANTIALIAS_MODE_1 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(525),           //vSync
         HSYNC(3089, 4),       //hSync
         LEAP(3097, 3098),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LAF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(640),        //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(640),        //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LPN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_ANTIALIAS_MODE_3 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(525),           //vSync
         HSYNC(3089, 4),       //hSync
         LEAP(3097, 3098),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LPF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LAN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(525),           //vSync
         HSYNC(3089, 4),       //hSync
         LEAP(3097, 3098),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_LAF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(320),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(2, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0.25),     //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(1280),       //origin
          SCALE(1, 0.75),     //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_HPN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_HPF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_HAN1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(1, 0),        //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_HAF1, //type
     {
         //comRegs
         VI_CTRL_TYPE_16 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_DIVOT_ON |
             VI_CTRL_SERRATE_ON |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(1280),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(2560),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_HPN2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_3 |
             0x3000,           //ctrl
         WIDTH(1280),          //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(2560),       //origin
          SCALE(1, 0),        //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(5120),       //origin
          SCALE(1, 0),        //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
    {OS_VI_MPAL_HPF2, //type
     {
         //comRegs
         VI_CTRL_TYPE_32 |
             VI_CTRL_GAMMA_DITHER_ON |
             VI_CTRL_GAMMA_ON |
             VI_CTRL_SERRATE_ON |
             VI_CTRL_ANTIALIAS_MODE_2 |
             0x3000,           //ctrl
         WIDTH(640),           //width
         BURST(57, 30, 5, 70), //burst
         VSYNC(524),           //vSync
         HSYNC(3088, 0),       //hSync
         LEAP(3100, 3100),     //leap
         HSTART(108, 748),     //hStart
         SCALE(1, 0),          //xScale
         VCURRENT(0),          //vCurrent
     },
     {//fldRegs
      {
          //[0]
          ORIGIN(2560),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(35, 509),    //vStart
          BURST(2, 2, 11, 0), //vBurst
          VINTR(2),           //vIntr
      },
      {
          //[1]
          ORIGIN(5120),       //origin
          SCALE(0.5, 0.5),    //yScale
          HSTART(37, 511),    //vStart
          BURST(4, 2, 14, 0), //vBurst
          VINTR(2),           //vIntr
      }}},
};

// TODO: Convert the following arrays into OSViMode structs.
s32 D_800E4620[20] = {
    0x00000000, 0x0000320E, 0x00000140, 0x03E52239, 
    0x0000020D, 0x00000C15, 0x0C150C15, 0x006C02EC, 
    0x00000200, 0x00000000, 0x00000280, 0x00000400, 
    0x002501FF, 0x000E0204, 0x00000002, 0x00000280,
    0x00000400, 0x002501FF, 0x000E0204, 0x00000002
};

s32 D_800E4670[20] = {
    0x0E000000, 0x0000320E, 0x00000140, 0x0404233A, 
    0x00000271, 0x00150C69, 0x0C6F0C6E, 0x00800300, 
    0x00000200, 0x00000000, 0x00000280, 0x00000400, 
    0x005F0239, 0x0009026B, 0x00000002, 0x00000280, 
    0x00000400, 0x005F0239, 0x0009026B, 0x00000002
};

s32 D_800E46C0[20] = {
    0x1C000000, 0x0000320E, 0x00000140, 0x04651E39, 
    0x0000020D, 0x00040C11, 0x0C190C1A, 0x006C02EC, 
    0x00000200, 0x00000000, 0x00000280, 0x00000400, 
    0x002501FF, 0x000E0204, 0x00000002, 0x00000280, 
    0x00000400, 0x002501FF, 0x000E0204, 0x00000002
};

OSViMode osViModeNtscLan1 = {
    OS_VI_NTSC_LAN1,  // type
    {
        // comRegs
        VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
            VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | 0x3000,  // ctrl
        WIDTH(320),                                                // width
        BURST(57, 34, 5, 62),                                      // burst
        VSYNC(525),                                                // vSync
        HSYNC(3093, 0),                                            // hSync
        LEAP(3093, 3093),                                          // leap
        HSTART(108, 748),                                          // hStart
        SCALE(2, 0),                                               // xScale
        VCURRENT(0),                                               // vCurrent
    },
    {// fldRegs
     {
         //[0]
         ORIGIN(640),         // origin
         SCALE(1, 0),         // yScale
         HSTART(37, 511),     // vStart
         BURST(4, 2, 14, 0),  // vBurst
         VINTR(2),            // vIntr
     },
     {
         //[1]
         ORIGIN(640),         // origin
         SCALE(1, 0),         // yScale
         HSTART(37, 511),     // vStart
         BURST(4, 2, 14, 0),  // vBurst
         VINTR(2),            // vIntr
     }}};

s32 osViModePalLan1[20] = {
    0x10000000, 0x0000311E, 0x00000140, 0x0404233A, 
    0x00000271, 0x00150C69, 0x0C6F0C6E, 0x00800300, 
    0x00000200, 0x00000000, 0x00000280, 0x00000400, 
    0x005F0239, 0x0009026B, 0x00000002, 0x00000280, 
    0x00000400, 0x005F0239, 0x0009026B, 0x00000002
};
/*
//TODO: Figure out why this doesn't match from libreultra
OSViMode osViModePalLan1 = {
    OS_VI_PAL_LAN1,  // type
    {
        // comRegs
        VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
            VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | 0x3000,  // ctrl
        WIDTH(320),                                                // width
        BURST(58, 30, 4, 69),                                      // burst
        VSYNC(625),                                                // vSync
        HSYNC(3177, 23),                                           // hSync
        LEAP(3183, 3181),                                          // leap
        HSTART(128, 768),                                          // hStart
        SCALE(2, 0),                                               // xScale
        VCURRENT(0),                                               // vCurrent
    },
    {// fldRegs
     {
         //[0]
         ORIGIN(640),          // origin
         SCALE(1, 0),          // yScale
         HSTART(95, 569),      // vStart
         BURST(107, 2, 9, 0),  // vBurst
         VINTR(2),             // vIntr
     },
     {
         //[1]
         ORIGIN(640),          // origin
         SCALE(1, 0),          // yScale
         HSTART(95, 569),      // vStart
         BURST(107, 2, 9, 0),  // vBurst
         VINTR(2),             // vIntr
     }}};
*/

OSViMode osViModeMpalLan1 = {
    OS_VI_MPAL_LAN1,  // type
    {
        // comRegs
        VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON |
            VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | 0x3000,  // ctrl
        WIDTH(320),                                                // width
        BURST(57, 30, 5, 70),                                      // burst
        VSYNC(525),                                                // vSync
        HSYNC(3089, 4),                                            // hSync
        LEAP(3097, 3098),                                          // leap
        HSTART(108, 748),                                          // hStart
        SCALE(2, 0),                                               // xScale
        VCURRENT(0),                                               // vCurrent
    },
    {// fldRegs
     {
         //[0]
         ORIGIN(640),         // origin
         SCALE(1, 0),         // yScale
         HSTART(37, 511),     // vStart
         BURST(4, 2, 14, 0),  // vBurst
         VINTR(2),            // vIntr
     },
     {
         //[1]
         ORIGIN(640),         // origin
         SCALE(1, 0),         // yScale
         HSTART(37, 511),     // vStart
         BURST(4, 2, 14, 0),  // vBurst
         VINTR(2),            // vIntr
     }}};

// This needs to be moved.
u32 __osPiAccessQueueEnabled = 0;
