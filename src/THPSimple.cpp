#include "ffcc/THPSimple.h"
#include "dolphin/dvd.h"
#include "dolphin/thp/THPDraw.h"
#include "dolphin/thp/THPFile.h"
#include "dolphin/thp/THPInfo.h"
#include <dolphin/ai.h>
#include <dolphin/os.h>
#include <dolphin/os/OSCache.h>
#include <string.h>

struct THPSimpleControl {
    DVDFileInfo fileInfo;          // 0x00
    THPHeader header;              // 0x3C
    THPFrameCompInfo compInfo;     // 0x6C
    THPVideoInfo videoInfo;        // 0x80
    THPAudioInfo audioInfo;        // 0x8C
    u32 unk_9C;                    // 0x9C
    u32 isOpen;                    // 0xA0
    u8 isPreLoaded;                // 0xA4
    u8 isBufferSet;                // 0xA5
    u8 isLooping;                  // 0xA6
    u8 hasAudio;                   // 0xA7
    s32 readOffset;                // 0xA8
    s32 readError;                 // 0xAC
    s32 isReadFrameAsync;          // 0xB0
    s32 readFrame;                 // 0xB4
    s32 readIndex;                 // 0xB8
    s32 readSize;                  // 0xBC
    s32 curAudioTrack;             // 0xC0
    f32 unk_C4;                    // 0xC4
    f32 unk_C8;                    // 0xC8
    u32 unk_CC;                    // 0xCC
    s32 unk_D0;                    // 0xD0
    u8* readBuffer[3];             // 0xD4
    s32 readFrameNumber[3];        // 0xE0
    s32 readStatus[3];             // 0xEC
    u8 padF8[0x3C];                // 0xF8
    u32* yImage;                   // 0x134
    u32* uImage;                   // 0x138
    u32* vImage;                   // 0x13C
    s32 curFrame;                  // 0x140
    u8 pad144[0x30];               // 0x144
};

THPSimpleControl SimpleControl;
static THPVideoInfo sVideoInfoWork;
static THPAudioInfo sAudioInfoWork;
static u8 sReadBuffer[0x40];

extern s32 lbl_8032EE48;
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
 * PAL Address: 0x80105284
 * PAL Size: 1412b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleOpen(const char* path)
{
    u32 componentIdx;
    s32 componentOffset;

    if ((lbl_8032EE48 == 0) || (SimpleControl.isOpen != 0)) {
        return 0;
    }

    memset(&sVideoInfoWork, 0, sizeof(sVideoInfoWork));
    memset(&sAudioInfoWork, 0, sizeof(sAudioInfoWork));

    if (!DVDOpen(path, &SimpleControl.fileInfo)) {
        return 0;
    }

    while (!DVDReadAsyncPrio(&SimpleControl.fileInfo, sReadBuffer, 0x40, 0, (DVDCallback)0, 2)) {
        checkError();
    }
    while (DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb) != DVD_STATE_END) {
        checkError();
    }
    memcpy(&SimpleControl.header, sReadBuffer, sizeof(THPHeader));

    if (strcmp(SimpleControl.header.mMagic, "THP") != 0) {
        DVDClose(&SimpleControl.fileInfo);
        return 0;
    }

    if (SimpleControl.header.mVersion != 0x11000) {
        DVDClose(&SimpleControl.fileInfo);
        return 0;
    }

    while (!DVDReadAsyncPrio(&SimpleControl.fileInfo, sReadBuffer, 0x20, SimpleControl.header.mCompInfoDataOffsets,
                             (DVDCallback)0, 2)) {
        checkError();
    }
    while (DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb) != DVD_STATE_END) {
        checkError();
    }
    memcpy(&SimpleControl.compInfo, sReadBuffer, sizeof(THPFrameCompInfo));

    SimpleControl.hasAudio = 0;
    componentOffset = static_cast<s32>(SimpleControl.header.mCompInfoDataOffsets + sizeof(THPFrameCompInfo));

    for (componentIdx = 0; componentIdx < SimpleControl.compInfo.mNumComponents; componentIdx++) {
        if (SimpleControl.compInfo.mFrameComp[componentIdx] == 1) {
            while (!DVDReadAsyncPrio(&SimpleControl.fileInfo, sReadBuffer, 0x20, componentOffset, (DVDCallback)0, 2)) {
                checkError();
            }
            while (DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb) != DVD_STATE_END) {
                checkError();
            }

            memcpy(&SimpleControl.audioInfo, sReadBuffer, sizeof(THPAudioInfo));
            componentOffset += sizeof(THPAudioInfo);
            SimpleControl.hasAudio = 1;
        } else if (SimpleControl.compInfo.mFrameComp[componentIdx] == 0) {
            while (!DVDReadAsyncPrio(&SimpleControl.fileInfo, sReadBuffer, 0x20, componentOffset, (DVDCallback)0, 2)) {
                checkError();
            }
            while (DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb) != DVD_STATE_END) {
                checkError();
            }

            memcpy(&SimpleControl.videoInfo, sReadBuffer, sizeof(THPVideoInfo));
            componentOffset += sizeof(THPVideoInfo);
        } else {
            return 0;
        }
    }

    SimpleControl.readOffset = static_cast<s32>(SimpleControl.header.mMovieDataOffsets);
    SimpleControl.readSize = static_cast<s32>(SimpleControl.header.mFirstFrameSize);
    SimpleControl.readIndex = 0;
    SimpleControl.curAudioTrack = 0;
    SimpleControl.readError = 0;
    SimpleControl.curFrame = -1;
    SimpleControl.readFrame = 0;
    SimpleControl.unk_D0 = 0;
    SimpleControl.unk_CC = 0;
    SimpleControl.isPreLoaded = 0;
    SimpleControl.isBufferSet = 0;
    SimpleControl.isLooping = 0;
    SimpleControl.isOpen = 1;
    SimpleControl.unk_C4 = 0.0f;
    SimpleControl.unk_C8 = 0.0f;

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x801051f4
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleClose(void)
{
    if ((SimpleControl.isOpen != 0) && (SimpleControl.isPreLoaded == 0)) {
        if (SimpleControl.hasAudio == 0) {
            SimpleControl.isBufferSet = 0;
        } else if (SimpleControl.isBufferSet == 1) {
            return 0;
        }

        if (SimpleControl.isReadFrameAsync == 0) {
            SimpleControl.isOpen = 0;
            DVDClose(&SimpleControl.fileInfo);
            return 1;
        }
    }

    return 0;
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
	                 static_cast<s16>(y), static_cast<s16>(SimpleControl.videoInfo.mXSize),
	                 static_cast<s16>(SimpleControl.videoInfo.mYSize), static_cast<s16>(polyWidth), drawHeight);
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
