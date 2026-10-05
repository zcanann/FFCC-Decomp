#include <dolphin.h>
#include <dolphin/os.h>

#include "dolphin/os/__os.h"
#include "dolphin/os/OSBootRegion.h"
#include <dolphin/dvd/__dvd.h>

static void* SaveStart;
static void* SaveEnd;
static BOOL Prepared;

typedef struct {
    char date[16];
    u32 entry;
    u32 size;
    u32 rebootSize;
    u32 reserved2;
} AppLoaderStruct;

static AppLoaderStruct Header ATTRIBUTE_ALIGN(32);

/*
 * --INFO--
 * PAL Address: 0x8017F11C
 * PAL Size: 16b
 * EN Address: 0x8017E06C
 * EN Size: 16b
 * JP Address: 0x80179718
 * JP Size: 16b
 */
static asm void Run(register void* entryPoint) {
    nofralloc

    sync
    isync
    mtlr entryPoint
    blr
}

/*
 * --INFO--
 * PAL Address: 0x8017F12C
 * PAL Size: 12b
 * EN Address: 0x8017E07C
 * EN Size: 12b
 * JP Address: 0x80179728
 * JP Size: 12b
 */
static void Callback(s32, DVDCommandBlock*) {
    Prepared = TRUE;
}

static inline int IsStreamEnabled(void) {
    if (DVDGetCurrentDiskID()->streaming) {
        return TRUE;
    }

    return FALSE;
}

/*
 * --INFO--
 * PAL Address: 0x8017F138
 * PAL Size: 832b
 * EN Address: 0x8017E088
 * EN Size: 832b
 * JP Address: 0x80179734
 * JP Size: 832b
 */
void __OSReboot(u32 resetCode, u32 bootDol) {
    OSContext exceptionContext;
    DVDCommandBlock streamCancelBlock;
    DVDCommandBlock appLoaderReadBlock;
    DVDCommandBlock rebootReadBlock;
    u32 rebootSize;
    u32 offset;
#if SDK_REVISION < 1
    OSTime start;
#endif

    (void)resetCode;
    (void)bootDol;

    OSDisableInterrupts();

    g_unk_817FFFFC = 0;
    g_unk_817FFFF8 = 0;
    g_unk_800030E2 = 1;
    BOOT_REGION_START = (u32)SaveStart;
    BOOT_REGION_END = (u32)SaveEnd;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    DVDInit();
    DVDSetAutoInvalidation(TRUE);
    DVDResume();

    Prepared = FALSE;
    __DVDPrepareResetAsync(Callback);
    __OSMaskInterrupts(0xFFFFFFE0);
    __OSUnmaskInterrupts(0x400);
    OSEnableInterrupts();

#if SDK_REVISION < 1
    start = OSGetTime();
#endif

    while (Prepared != TRUE) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
        if (!DVDCheckDisk())
#endif
        {
            __OSDoHotReset(g_unk_817FFFFC);
        }
    }

    if (!__OSIsGcam && IsStreamEnabled()) {
        AISetStreamVolLeft(0);
        AISetStreamVolRight(0);
        DVDCancelStreamAsync(&streamCancelBlock, NULL);

#if SDK_REVISION < 1
        start = OSGetTime();
#endif

        while (DVDGetCommandBlockStatus(&streamCancelBlock)) {
#if SDK_REVISION < 1
            if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
            if (!DVDCheckDisk())
#endif
            {
                __OSDoHotReset(g_unk_817FFFFC);
            }
        }

        AISetStreamPlayState(AI_STREAM_STOP);
    }

    DVDReadAbsAsyncPrio(&appLoaderReadBlock, &Header, sizeof(AppLoaderStruct), 0x2440, NULL, 0);

#if SDK_REVISION < 1
    start = OSGetTime();
#endif

    while (DVDGetCommandBlockStatus(&appLoaderReadBlock)) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
        if (!DVDCheckDisk())
#endif
        {
            __OSDoHotReset(g_unk_817FFFFC);
        }
    }

    offset = Header.size + 0x20;
    rebootSize = OSRoundUp32B(Header.rebootSize);
    DVDReadAbsAsyncPrio(&rebootReadBlock, (void*)0x81300000, rebootSize, offset + 0x2440, NULL, 0);

#if SDK_REVISION < 1
    start = OSGetTime();
#endif

    while (DVDGetCommandBlockStatus(&rebootReadBlock)) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || OS_TIMER_CLOCK < (OSGetTime() - start))
#else
        if (!DVDCheckDisk())
#endif
        {
            __OSDoHotReset(g_unk_817FFFFC);
        }
    }

    ICInvalidateRange((void*)0x81300000, rebootSize);

    OSDisableInterrupts();
    ICFlashInvalidate();
    Run((void*)0x81300000);
}
