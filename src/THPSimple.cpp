#include "ffcc/THPSimple.h"
#include "dolphin/thp/THPDraw.h"
#include <dolphin/ai.h>
#include <dolphin/os.h>
#include <dolphin/os/OSCache.h>

struct THPSimpleControl {
    u8 pad0[0x80];
    s32 texWidth;
    s32 texHeight;
    u8 pad88[0xAC];
    u32* yImage;
    u32* uImage;
    u32* vImage;
    s32 curFrame;
};

THPSimpleControl SimpleControl;

extern s32 lbl_8032EE4C;
extern void (*lbl_8032EE50)(void);
extern s16* lbl_8032EE54;
extern s16* lbl_8032EE58;
extern s32 lbl_8032EE5C;
extern s16 WorkBuffer_32_[];

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
s32 THPSimpleDrawCurrentFrame(GXRenderModeObj* obj, int x, int y, int polyWidth, int polyHeight)
{
	s16 drawHeight;

	if (SimpleControl.curFrame < 0) {
		return -1;
	}

	THPGXYuv2RgbSetup(obj);
	drawHeight = static_cast<s16>(polyHeight);
	THPGXYuv2RgbDraw(SimpleControl.yImage, SimpleControl.uImage, SimpleControl.vImage, static_cast<s16>(x),
	                 static_cast<s16>(y), static_cast<s16>(SimpleControl.texWidth),
	                 static_cast<s16>(SimpleControl.texHeight), static_cast<s16>(polyWidth), drawHeight);
	THPGXRestore();
	return SimpleControl.curFrame;
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
	u32 interruptState;
	s16* workBuffer;

	if (lbl_8032EE5C == 0) {
		lbl_8032EE4C ^= 1;
		workBuffer = reinterpret_cast<s16*>(reinterpret_cast<u8*>(WorkBuffer_32_) + lbl_8032EE4C * 0x280);
		AIInitDMA((u32)workBuffer, 0x280);
		interruptState = OSEnableInterrupts();
		MixAudio(workBuffer, (short*)0, 0xA0);
		DCFlushRange(workBuffer, 0x280);
		OSRestoreInterrupts(interruptState);
		return;
	}

	if (lbl_8032EE5C == 1) {
		if (lbl_8032EE54 != NULL) {
			lbl_8032EE58 = lbl_8032EE54;
		}
		lbl_8032EE50();
		lbl_8032EE54 = reinterpret_cast<s16*>(AIGetDMAStartAddr() + 0x80000000);
	} else {
		lbl_8032EE50();
		lbl_8032EE58 = reinterpret_cast<s16*>(AIGetDMAStartAddr() + 0x80000000);
	}

	lbl_8032EE4C ^= 1;
	workBuffer = reinterpret_cast<s16*>(reinterpret_cast<u8*>(WorkBuffer_32_) + lbl_8032EE4C * 0x280);
	AIInitDMA((u32)workBuffer, 0x280);
	interruptState = OSEnableInterrupts();
	if (lbl_8032EE58 != NULL) {
		DCInvalidateRange(lbl_8032EE58, 0x280);
	}
	MixAudio(workBuffer, lbl_8032EE58, 0xA0);
	DCFlushRange(workBuffer, 0x280);
	OSRestoreInterrupts(interruptState);
}
