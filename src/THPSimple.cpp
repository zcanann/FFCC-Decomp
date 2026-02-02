#include "ffcc/THPSimple.h"
#include "dolphin/thp/THPDraw.h"
#include "dolphin/dvd.h"
#include "dolphin/gx/GXFrameBuffer.h"

// SimpleControl structure (inferred from Ghidra decompilation)
struct THPSimpleControl {
    char _padding[0x80];    // 0x00-0x80
    int field_80;           // 0x80
    int field_84;           // 0x84
    char _padding2[0x14];   // 0x88-0x9C
    int field_100;          // 0x100
    char _padding3[0x28];   // 0x104-0x128
    short field_128;        // 0x128
    char _padding4[0x2];    // 0x12A-0x12C
    short field_132;        // 0x132
    char _padding5[0xCA];   // 0x134-0x1FC
    int field_308;          // 0x308
    int field_312;          // 0x312
    int field_316;          // 0x316
    int field_320;          // 0x320
};

static THPSimpleControl SimpleControl;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void checkError()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _kami_DVDREAD(DVDFileInfo*, void*, long, long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleInit(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleQuit(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleOpen(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleClose(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleCalcNeedMemory(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleSetBuffer(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ReadFrameAsync()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __THPSimpleDVDCallback(long, DVDFileInfo*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimplePreLoad(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleAudioStart(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleAudioStop(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleLoadStop(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPSimpleDecode(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CheckPrefetch()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void VideoDecode(unsigned char*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80104594
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int THPSimpleDrawCurrentFrame(int param_1, short param_2, short param_3, short param_4, short param_5)
{
    if (SimpleControl.field_320 < 0) {
        return -1;
    }
    
    THPGXYuv2RgbSetup(&GXNtsc240Ds);
    THPGXYuv2RgbDraw((u32*)SimpleControl.field_308, (u32*)SimpleControl.field_312, (u32*)SimpleControl.field_316,
                     param_2, param_3, SimpleControl.field_128, SimpleControl.field_132, param_4, param_5);
    THPGXRestore();
    
    return SimpleControl.field_320;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MixAudio(short*, short*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void THPAudioMixCallback()
{
	// TODO
}
