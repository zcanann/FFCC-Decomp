#include "ffcc/THPSimple.h"
#include "ffcc/file.h"
#include "dolphin/dvd.h"
#include "dolphin/thp/THPDraw.h"
#include "dolphin/thp/THPFile.h"
#include "dolphin/thp/THPInfo.h"
#include "dolphin/thp/THPPlayer.h"
#include "dolphin/thp/THPBuffer.h"
#include "dolphin/thp/THPVideoDecode.h"
#include "dolphin/thp/THPAudio.h"
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
    f32 unk_CC;                    // 0xCC
    s32 unk_D0;                    // 0xD0
    THPReadBuffer readBuffer[8];   // 0xD4
    u32* yImage;                   // 0x134
    u32* uImage;                   // 0x138
    u32* vImage;                   // 0x13C
    s32 curFrame;                  // 0x140
    THPAudioBuffer audioBuffer[3]; // 0x144
    s32 audioDecodeIndex;          // 0x168
    s32 audioPlayIndex;            // 0x16C
    u8 pad170[4];                  // 0x170
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
extern u16 lbl_802111E8[];
extern s16 WorkBuffer_32_[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void checkError()
{
    s32 status = DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb);

    if ((status == 0xB) || ((status - 4U) < 3) || (status == -1)) {
        File.DrawError(SimpleControl.fileInfo, status);
    }
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
 * PAL Address: 0x8010585c
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleInit(s32 audioMixMode)
{
    u32 interruptState;
    s16* workBuffer;

    File.CheckQueue();
    memset(&SimpleControl, 0, sizeof(SimpleControl));
    LCEnable();

    if (THPInit() == FALSE) {
        return 0;
    }

    interruptState = OSDisableInterrupts();
    lbl_8032EE4C = 0;
    lbl_8032EE54 = (s16*)NULL;
    lbl_8032EE58 = (s16*)NULL;
    lbl_8032EE5C = audioMixMode;
    lbl_8032EE50 = AIRegisterDMACallback(THPAudioMixCallback);

    if ((lbl_8032EE50 == NULL) && (lbl_8032EE5C != 0)) {
        AIRegisterDMACallback((AIDCallback)NULL);
        OSRestoreInterrupts(interruptState);
        return 0;
    }

    OSRestoreInterrupts(interruptState);

    if (lbl_8032EE5C == 0) {
        memset(WorkBuffer_32_, 0, 0x500);
        DCFlushRange(WorkBuffer_32_, 0x500);
        workBuffer = reinterpret_cast<s16*>(reinterpret_cast<u8*>(WorkBuffer_32_) + lbl_8032EE4C * 0x280);
        AIInitDMA((u32)workBuffer, 0x280);
        AIStartDMA();
    }

    lbl_8032EE48 = 1;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80105808
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void THPSimpleQuit(void)
{
    u32 interruptState;

    LCDisable();
    interruptState = OSDisableInterrupts();
    if (lbl_8032EE50 != NULL) {
        AIRegisterDMACallback(lbl_8032EE50);
    }
    OSRestoreInterrupts(interruptState);
    lbl_8032EE48 = 0;
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
    SimpleControl.unk_CC = 0.0f;
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
    THPSimpleControl* control = &SimpleControl;

    if ((control->isOpen != 0) && (control->isPreLoaded == 0)) {
        if (control->hasAudio == 0) {
            control->isBufferSet = 0;
        } else if (control->isBufferSet == 1) {
            return 0;
        }

        if (control->isReadFrameAsync == 0) {
            control->isOpen = 0;
            DVDClose(&control->fileInfo);
            return 1;
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80105174
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleCalcNeedMemory(void)
{
    if (SimpleControl.isOpen == 0) {
        return 0;
    }

    s32 need = ((SimpleControl.header.mBufferSize + 0x1F) * 8) & ~0xFF;
    need += (SimpleControl.videoInfo.mXSize * SimpleControl.videoInfo.mYSize + 0x1F) & ~0x1F;
    need += (((SimpleControl.videoInfo.mXSize * SimpleControl.videoInfo.mYSize) >> 2) + 0x1F) & ~0x1F;
    need += (((SimpleControl.videoInfo.mXSize * SimpleControl.videoInfo.mYSize) >> 2) + 0x1F) & ~0x1F;

    if (SimpleControl.hasAudio != 0) {
        need += ((SimpleControl.header.mAudioMaxSamples * 4 + 0x1F) & ~0x1F) * 3;
    }

    return need + 0x1000;
}

/*
 * --INFO--
 * PAL Address: 0x80104fcc
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleSetBuffer(u8* buffer)
{
    u32 lumaSize;
    u32 chromaSize;
    u32 frameBufferSize;
    u8* cur;

    if ((SimpleControl.isOpen == 0) || (SimpleControl.isPreLoaded != 0)) {
        return 0;
    }
    if (SimpleControl.isBufferSet == 1) {
        return 0;
    }

    lumaSize = (SimpleControl.videoInfo.mXSize * SimpleControl.videoInfo.mYSize + 0x1F) & ~0x1F;
    chromaSize = (((SimpleControl.videoInfo.mXSize * SimpleControl.videoInfo.mYSize) >> 2) + 0x1F) & ~0x1F;

    SimpleControl.yImage = reinterpret_cast<u32*>(buffer);
    DCInvalidateRange(SimpleControl.yImage, lumaSize);
    buffer += lumaSize;

    SimpleControl.uImage = reinterpret_cast<u32*>(buffer);
    DCInvalidateRange(SimpleControl.uImage, chromaSize);
    buffer += chromaSize;

    SimpleControl.vImage = reinterpret_cast<u32*>(buffer);
    DCInvalidateRange(SimpleControl.vImage, chromaSize);
    buffer += chromaSize;

    frameBufferSize = (SimpleControl.header.mBufferSize + 0x1F) & ~0x1F;
    cur = buffer;
    for (int i = 0; i < 8; i++) {
        SimpleControl.readBuffer[i].mPtr = cur;
        SimpleControl.readBuffer[i].mFrameNumber = 0;
        SimpleControl.readBuffer[i].mIsValid = 0;
        cur += frameBufferSize;
    }

    SimpleControl.unk_9C = reinterpret_cast<u32>(cur);
    SimpleControl.curFrame = -1;

    if (SimpleControl.hasAudio != 0) {
        u32 audioBufferSize = ((SimpleControl.audioInfo.mSndNumSamples * 4) + 0x1F) & ~0x1F;

        SimpleControl.audioBuffer[0].mBuffer = reinterpret_cast<s16*>(cur);
        SimpleControl.audioBuffer[0].mCurPtr = SimpleControl.audioBuffer[0].mBuffer;
        SimpleControl.audioBuffer[0].mValidSample = 0;
        cur += audioBufferSize;

        SimpleControl.audioBuffer[1].mBuffer = reinterpret_cast<s16*>(cur);
        SimpleControl.audioBuffer[1].mCurPtr = SimpleControl.audioBuffer[1].mBuffer;
        SimpleControl.audioBuffer[1].mValidSample = 0;
        cur += audioBufferSize;

        SimpleControl.audioBuffer[2].mBuffer = reinterpret_cast<s16*>(cur);
        SimpleControl.audioBuffer[2].mCurPtr = SimpleControl.audioBuffer[2].mBuffer;
        SimpleControl.audioBuffer[2].mValidSample = 0;
        cur += audioBufferSize;

        SimpleControl.unk_9C = reinterpret_cast<u32>(cur);
    }

    return 1;
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
 * PAL Address: 0x80104e50
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __THPSimpleDVDCallback(long result, DVDFileInfo*)
{
    s32 oldReadIndex;

    if (result == -1) {
        SimpleControl.readError = 1;
        return;
    }
    if (result == -3) {
        return;
    }

    SimpleControl.isReadFrameAsync = 0;
    SimpleControl.readBuffer[SimpleControl.readIndex].mFrameNumber = SimpleControl.curAudioTrack;
    SimpleControl.curAudioTrack++;
    SimpleControl.readBuffer[SimpleControl.readIndex].mIsValid = 1;
    SimpleControl.readOffset += SimpleControl.readSize;

    oldReadIndex = SimpleControl.readIndex;
    SimpleControl.readIndex = (SimpleControl.readIndex + 1) & 7;
    SimpleControl.readSize = *reinterpret_cast<s32*>(SimpleControl.readBuffer[oldReadIndex].mPtr);

    if ((SimpleControl.readBuffer[SimpleControl.readIndex].mIsValid == 0) && (SimpleControl.readError == 0) &&
        (SimpleControl.isPreLoaded == 1)) {
        if ((SimpleControl.header.mNumFrames - 1) < static_cast<u32>(SimpleControl.curAudioTrack)) {
            if (SimpleControl.isLooping != 1) {
                return;
            }
            SimpleControl.curAudioTrack = 0;
            SimpleControl.readOffset = static_cast<s32>(SimpleControl.header.mMovieDataSize);
            SimpleControl.readSize = static_cast<s32>(SimpleControl.header.mFirstFrameSize);
        }

        SimpleControl.isReadFrameAsync = 1;
        if (!DVDReadAsyncPrio(&SimpleControl.fileInfo, SimpleControl.readBuffer[SimpleControl.readIndex].mPtr,
                              SimpleControl.readSize, SimpleControl.readOffset,
                              static_cast<DVDCallback>(__THPSimpleDVDCallback), 2)) {
            SimpleControl.isReadFrameAsync = 0;
            SimpleControl.readError = 1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80104c30
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimplePreLoad(s32 loop)
{
    s32 i;
    s32 status;
    u32 readCount = 8;

    if ((SimpleControl.isOpen == 0) || (SimpleControl.isPreLoaded != 0)) {
        return 0;
    }

    if ((loop == 0) && (SimpleControl.header.mNumFrames < 8)) {
        readCount = SimpleControl.header.mNumFrames;
    }

    for (i = 0; i < static_cast<s32>(readCount); i++) {
        while (!DVDReadAsyncPrio(&SimpleControl.fileInfo, SimpleControl.readBuffer[SimpleControl.readIndex].mPtr,
                                 SimpleControl.readSize, SimpleControl.readOffset, static_cast<DVDCallback>(0), 2)) {
            status = DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb);
            if ((status == 0xB) || ((status - 4U) < 3) || (status == -1)) {
                File.DrawError(SimpleControl.fileInfo, status);
            }
        }

        while ((status = DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb)) != DVD_STATE_END) {
            status = DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb);
            if ((status == 0xB) || ((status - 4U) < 3) || (status == -1)) {
                File.DrawError(SimpleControl.fileInfo, status);
            }
        }

        SimpleControl.readOffset += SimpleControl.readSize;
        SimpleControl.readSize = *reinterpret_cast<s32*>(SimpleControl.readBuffer[SimpleControl.readIndex].mPtr);
        SimpleControl.readBuffer[SimpleControl.readIndex].mIsValid = 1;
        SimpleControl.readBuffer[SimpleControl.readIndex].mFrameNumber = SimpleControl.curAudioTrack;
        SimpleControl.curAudioTrack++;
        SimpleControl.readIndex = (SimpleControl.readIndex + 1) & 7;

        if (((SimpleControl.header.mNumFrames - 1) < static_cast<u32>(SimpleControl.curAudioTrack)) &&
            (SimpleControl.isLooping == 1)) {
            SimpleControl.curAudioTrack = 0;
            SimpleControl.readOffset = static_cast<s32>(SimpleControl.header.mMovieDataSize);
            SimpleControl.readSize = static_cast<s32>(SimpleControl.header.mFirstFrameSize);
        }
    }

    SimpleControl.isLooping = static_cast<u8>(loop);
    SimpleControl.isPreLoaded = 1;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80104c1c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void THPSimpleAudioStart(void)
{
    SimpleControl.isBufferSet = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80104c08
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void THPSimpleAudioStop(void)
{
    SimpleControl.isBufferSet = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80104b20
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleLoadStop(void)
{
    if ((SimpleControl.isOpen == 0) || (SimpleControl.isBufferSet != 0)) {
        return 0;
    }

    SimpleControl.isPreLoaded = 0;
    if (SimpleControl.isReadFrameAsync != 0) {
        DVDCancel(&SimpleControl.fileInfo.cb);
        SimpleControl.isReadFrameAsync = 0;
    }

    for (int i = 0; i < 8; i++) {
        SimpleControl.readBuffer[i].mFrameNumber = 0;
        SimpleControl.readBuffer[i].mIsValid = 0;
    }
    for (int i = 0; i < 3; i++) {
        SimpleControl.audioBuffer[i].mValidSample = 0;
    }

    SimpleControl.curFrame = -1;
    SimpleControl.readOffset = static_cast<s32>(SimpleControl.header.mMovieDataSize);
    SimpleControl.readSize = static_cast<s32>(SimpleControl.header.mFirstFrameSize);
    SimpleControl.readIndex = 0;
    SimpleControl.curAudioTrack = 0;
    SimpleControl.readError = 0;
    SimpleControl.readFrame = 0;
    SimpleControl.audioDecodeIndex = 0;
    SimpleControl.audioPlayIndex = 0;
    SimpleControl.unk_C4 = SimpleControl.unk_C8;
    SimpleControl.unk_D0 = 0;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8010462c
 * PAL Size: 1268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 THPSimpleDecode(s32 audioTrack)
{
    s32 status;
    s32 decodeResult;
    u32 interruptState;

    interruptState = OSDisableInterrupts();
    if ((SimpleControl.readBuffer[SimpleControl.readIndex].mIsValid == 0) && (SimpleControl.isReadFrameAsync == 0) &&
        (SimpleControl.readError == 0) && (SimpleControl.isPreLoaded == 1)) {
        if ((SimpleControl.header.mNumFrames - 1) < static_cast<u32>(SimpleControl.curAudioTrack)) {
            if (SimpleControl.isLooping != 1) {
                goto restore_interrupts_1;
            }
            SimpleControl.curAudioTrack = 0;
            SimpleControl.readOffset = static_cast<s32>(SimpleControl.header.mMovieDataSize);
            SimpleControl.readSize = static_cast<s32>(SimpleControl.header.mFirstFrameSize);
        }

        SimpleControl.isReadFrameAsync = 1;
        if (!DVDReadAsyncPrio(&SimpleControl.fileInfo, SimpleControl.readBuffer[SimpleControl.readIndex].mPtr,
                              SimpleControl.readSize, SimpleControl.readOffset,
                              static_cast<DVDCallback>(__THPSimpleDVDCallback), 2)) {
            SimpleControl.isReadFrameAsync = 0;
            SimpleControl.readError = 1;
        }
    }

restore_interrupts_1:
    OSRestoreInterrupts(interruptState);

    if ((SimpleControl.isReadFrameAsync != 0) &&
        (((status = DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb), status == 0xB) || ((status - 4U) < 3)) ||
         (status == -1))) {
        File.DrawError(SimpleControl.fileInfo, status);
    }

    if (SimpleControl.readBuffer[SimpleControl.readFrame].mIsValid == 0) {
        return 2;
    }

    u32* compSizeTable = reinterpret_cast<u32*>(SimpleControl.readBuffer[SimpleControl.readFrame].mPtr + 8);
    u8* compData = SimpleControl.readBuffer[SimpleControl.readFrame].mPtr + 8 + SimpleControl.compInfo.mNumComponents * 4;

    if (SimpleControl.hasAudio == 0) {
        for (u32 i = 0; i < SimpleControl.compInfo.mNumComponents; i++) {
            if (SimpleControl.compInfo.mFrameComp[i] == 0) {
                decodeResult = THPVideoDecode(compData, SimpleControl.yImage, SimpleControl.uImage, SimpleControl.vImage,
                                              reinterpret_cast<void*>(SimpleControl.unk_9C));
                if (decodeResult != 0) {
                    return 1;
                }
                SimpleControl.curFrame = SimpleControl.readBuffer[SimpleControl.readFrame].mFrameNumber;
            }
            compData += compSizeTable[i];
        }
    } else {
        if ((audioTrack < 0) || (static_cast<u32>(audioTrack) >= SimpleControl.audioInfo.mSndNumTracks)) {
            return 4;
        }
        if (SimpleControl.audioBuffer[SimpleControl.audioDecodeIndex].mValidSample != 0) {
            return 3;
        }

        for (u32 i = 0; i < SimpleControl.compInfo.mNumComponents; i++) {
            if (SimpleControl.compInfo.mFrameComp[i] == 1) {
                u32 samples = THPAudioDecode(SimpleControl.audioBuffer[SimpleControl.audioDecodeIndex].mBuffer,
                                             compData + compSizeTable[i] * audioTrack, 0);
                u32 lock = OSDisableInterrupts();
                SimpleControl.audioBuffer[SimpleControl.audioDecodeIndex].mValidSample = samples;
                SimpleControl.audioBuffer[SimpleControl.audioDecodeIndex].mCurPtr =
                    SimpleControl.audioBuffer[SimpleControl.audioDecodeIndex].mBuffer;
                OSRestoreInterrupts(lock);
                SimpleControl.audioDecodeIndex++;
                if (SimpleControl.audioDecodeIndex > 2) {
                    SimpleControl.audioDecodeIndex = 0;
                }
            } else if (SimpleControl.compInfo.mFrameComp[i] == 0) {
                decodeResult = THPVideoDecode(compData, SimpleControl.yImage, SimpleControl.uImage, SimpleControl.vImage,
                                              reinterpret_cast<void*>(SimpleControl.unk_9C));
                if (decodeResult != 0) {
                    return 1;
                }
                SimpleControl.curFrame = SimpleControl.readBuffer[SimpleControl.readFrame].mFrameNumber;
            }
            compData += compSizeTable[i];
        }
    }

    SimpleControl.readBuffer[SimpleControl.readFrame].mIsValid = 0;
    SimpleControl.readFrame = (SimpleControl.readFrame + 1) & 7;

    interruptState = OSDisableInterrupts();
    if ((SimpleControl.readBuffer[SimpleControl.readIndex].mIsValid == 0) && (SimpleControl.isReadFrameAsync == 0) &&
        (SimpleControl.readError == 0) && (SimpleControl.isPreLoaded == 1)) {
        if ((SimpleControl.header.mNumFrames - 1) < static_cast<u32>(SimpleControl.curAudioTrack)) {
            if (SimpleControl.isLooping != 1) {
                goto restore_interrupts_2;
            }
            SimpleControl.curAudioTrack = 0;
            SimpleControl.readOffset = static_cast<s32>(SimpleControl.header.mMovieDataSize);
            SimpleControl.readSize = static_cast<s32>(SimpleControl.header.mFirstFrameSize);
        }

        SimpleControl.isReadFrameAsync = 1;
        if (!DVDReadAsyncPrio(&SimpleControl.fileInfo, SimpleControl.readBuffer[SimpleControl.readIndex].mPtr,
                              SimpleControl.readSize, SimpleControl.readOffset,
                              static_cast<DVDCallback>(__THPSimpleDVDCallback), 2)) {
            SimpleControl.isReadFrameAsync = 0;
            SimpleControl.readError = 1;
        }
    }

restore_interrupts_2:
    OSRestoreInterrupts(interruptState);

    if ((SimpleControl.isReadFrameAsync != 0) &&
        (((status = DVDGetCommandBlockStatus(&SimpleControl.fileInfo.cb), status == 0xB) || ((status - 4U) < 3)) ||
         (status == -1))) {
        File.DrawError(SimpleControl.fileInfo, status);
    }

    return 0;
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
 * PAL Address: 0x80104240
 * PAL Size: 852b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MixAudio(short* output, short* input, unsigned long samples)
{
    u16 volume;
    f32 volumeIndex;
    s32 mixedSample;
    s16* audioPtr;
    u32 availableSamples;
    u32 i;

    if (input == NULL) {
        if ((SimpleControl.isOpen == 0) || (SimpleControl.isBufferSet != 1) || (SimpleControl.hasAudio == 0)) {
            memset(output, 0, samples << 2);
        } else {
            do {
                availableSamples = SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mValidSample;
                if (availableSamples == 0) {
                    memset(output, 0, samples << 2);
                    return;
                }
                if (samples <= availableSamples) {
                    availableSamples = static_cast<u32>(samples);
                }

                audioPtr = SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mCurPtr;
                for (i = availableSamples; i != 0; i--) {
                    volumeIndex = SimpleControl.unk_C8;
                    if (SimpleControl.unk_D0 != 0) {
                        SimpleControl.unk_D0 -= 1;
                        volumeIndex = SimpleControl.unk_C4 + SimpleControl.unk_CC;
                    }
                    SimpleControl.unk_C4 = volumeIndex;
                    volume = lbl_802111E8[static_cast<s32>(volumeIndex)];

                    mixedSample = static_cast<s32>((static_cast<u32>(volume) * static_cast<s32>(*audioPtr)) >> 15);
                    if (mixedSample < -0x8000) {
                        mixedSample = -0x8000;
                    }
                    if (mixedSample > 0x7FFF) {
                        mixedSample = 0x7FFF;
                    }
                    *output = static_cast<s16>(mixedSample);

                    mixedSample = static_cast<s32>((static_cast<u32>(volume) * static_cast<s32>(audioPtr[1])) >> 15);
                    if (mixedSample < -0x8000) {
                        mixedSample = -0x8000;
                    }
                    if (mixedSample > 0x7FFF) {
                        mixedSample = 0x7FFF;
                    }
                    output[1] = static_cast<s16>(mixedSample);

                    output += 2;
                    audioPtr += 2;
                }

                samples -= availableSamples;
                SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mValidSample -= availableSamples;
                SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mCurPtr = audioPtr;
                if (SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mValidSample == 0) {
                    SimpleControl.audioPlayIndex += 1;
                    if (SimpleControl.audioPlayIndex > 2) {
                        SimpleControl.audioPlayIndex = 0;
                    }
                }
            } while (samples != 0);
        }
    } else if ((SimpleControl.isOpen == 0) || (SimpleControl.isBufferSet != 1) || (SimpleControl.hasAudio == 0)) {
        memcpy(output, input, samples << 2);
    } else {
        do {
            availableSamples = SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mValidSample;
            if (availableSamples == 0) {
                memcpy(output, input, samples << 2);
                return;
            }
            if (samples <= availableSamples) {
                availableSamples = static_cast<u32>(samples);
            }

            audioPtr = SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mCurPtr;
            for (i = availableSamples; i != 0; i--) {
                volumeIndex = SimpleControl.unk_C8;
                if (SimpleControl.unk_D0 != 0) {
                    SimpleControl.unk_D0 -= 1;
                    volumeIndex = SimpleControl.unk_C4 + SimpleControl.unk_CC;
                }
                SimpleControl.unk_C4 = volumeIndex;
                volume = lbl_802111E8[static_cast<s32>(volumeIndex)];

                mixedSample = static_cast<s32>(*input) +
                              static_cast<s32>((static_cast<u32>(volume) * static_cast<s32>(*audioPtr)) >> 15);
                if (mixedSample < -0x8000) {
                    mixedSample = -0x8000;
                }
                if (mixedSample > 0x7FFF) {
                    mixedSample = 0x7FFF;
                }
                *output = static_cast<s16>(mixedSample);

                mixedSample = static_cast<s32>(input[1]) +
                              static_cast<s32>((static_cast<u32>(volume) * static_cast<s32>(audioPtr[1])) >> 15);
                if (mixedSample < -0x8000) {
                    mixedSample = -0x8000;
                }
                if (mixedSample > 0x7FFF) {
                    mixedSample = 0x7FFF;
                }
                output[1] = static_cast<s16>(mixedSample);

                output += 2;
                input += 2;
                audioPtr += 2;
            }

            samples -= availableSamples;
            SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mValidSample -= availableSamples;
            SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mCurPtr = audioPtr;
            if (SimpleControl.audioBuffer[SimpleControl.audioPlayIndex].mValidSample == 0) {
                SimpleControl.audioPlayIndex += 1;
                if (SimpleControl.audioPlayIndex > 2) {
                    SimpleControl.audioPlayIndex = 0;
                }
            }
        } while (samples != 0);
    }
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
