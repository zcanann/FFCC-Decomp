#include <dolphin.h>
#include <dolphin/os.h>

#include "dolphin/os/__os.h"
#include <dolphin/dvd/__dvd.h>

extern volatile u32 BOOT_REGION_START AT_ADDRESS(0x812FDFF0);
extern volatile u32 BOOT_REGION_END AT_ADDRESS(0x812FDFEC);
extern volatile u8 g_unk_800030E2 AT_ADDRESS(0x800030E2);
extern volatile u32 g_unk_817FFFFC AT_ADDRESS(0x817FFFFC);
extern volatile u32 g_unk_817FFFF8 AT_ADDRESS(0x817FFFF8);

static int Prepared;

static void* SaveStart;
static void* SaveEnd;

typedef struct {
    char date[16];
    u32 entry;
    u32 size;
    u32 rebootSize;
    u32 reserved2;
} AppLoaderStruct;

static AppLoaderStruct FatalParam;

#ifdef __GEKKO__
static asm void Run(register void* entryPoint) {
    nofralloc

    sync
    isync
    mtlr entryPoint
    blr
}
#endif

static void Callback(s32, DVDCommandBlock*) {
    Prepared = TRUE;
}

static int IsStreamEnabled(void) {
    if (DVDGetCurrentDiskID()->streaming) {
        return TRUE;
    }

    return FALSE;
}

/*
 * --INFO--
 * PAL Address: 0x8017F138
 * PAL Size: 832b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __OSReboot(u32 resetCode, u32 bootDol) {
    OSContext exceptionContext;
    DVDCommandBlock streamCancelBlock;
    DVDCommandBlock appLoaderReadBlock;
    DVDCommandBlock rebootReadBlock;
    u32 rebootSize;
#if SDK_REVISION < 1
    OSTime start;
#endif

    (void)resetCode;
    (void)bootDol;

    OSDisableInterrupts();

    g_unk_817FFFFC = 0;
    g_unk_817FFFF8 = 0;
    g_unk_800030E2 = 1;
    BOOT_REGION_START = (u32)__OSRebootParams.regionStart;
    BOOT_REGION_END = (u32)__OSRebootParams.regionEnd;

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
        if (!DVDCheckDisk() || (OSGetTime() - start) > OS_TIMER_CLOCK)
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
            if (!DVDCheckDisk() || (OSGetTime() - start) > OS_TIMER_CLOCK)
#else
            if (!DVDCheckDisk())
#endif
            {
                __OSDoHotReset(g_unk_817FFFFC);
            }
        }

        AISetStreamPlayState(AI_STREAM_STOP);
    }

    DVDReadAbsAsyncPrio(&appLoaderReadBlock, &FatalParam, sizeof(AppLoaderStruct), 0x2440, NULL, 0);

#if SDK_REVISION < 1
    start = OSGetTime();
#endif

    while (DVDGetCommandBlockStatus(&appLoaderReadBlock)) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || (OSGetTime() - start) > OS_TIMER_CLOCK)
#else
        if (!DVDCheckDisk())
#endif
        {
            __OSDoHotReset(g_unk_817FFFFC);
        }
    }

    rebootSize = OSRoundUp32B(FatalParam.rebootSize);
    DVDReadAbsAsyncPrio(&rebootReadBlock, (void*)0x81300000, rebootSize, FatalParam.size + 0x20 + 0x2440, NULL, 0);

#if SDK_REVISION < 1
    start = OSGetTime();
#endif

    while (DVDGetCommandBlockStatus(&rebootReadBlock)) {
#if SDK_REVISION < 1
        if (!DVDCheckDisk() || (OSGetTime() - start) > OS_TIMER_CLOCK)
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

void OSSetSaveRegion(void* start, void* end) {
    SaveStart = start;
    SaveEnd = end;
}

void OSGetSaveRegion(void** start, void** end) {
    *start = SaveStart;
    *end = SaveEnd;
}

void OSGetSavedRegion(void** start, void** end) {
    *start = __OSRebootParams.regionStart;
    *end = __OSRebootParams.regionEnd;
}
