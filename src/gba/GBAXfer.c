#include "dolphin/gba/GBAPriv.h"
#include "dolphin/si/SIBios.h"

void __GBAHandler(s32 chan, u32 error, OSContext* context) {
    GBATransferCallback proc;
    GBACallback callback;
    OSContext exceptionContext;

    if (__GBAReset != 0) {
        return;
    }

    if ((error & 0xf) == 0) {
        __GBA[chan].ret = GBA_READY;
    } else {
        __GBA[chan].ret = GBA_NOT_READY;
    }

    proc = __GBA[chan].proc;
    if (proc != NULL) {
        __GBA[chan].proc = NULL;
        proc(chan);
    }

    if (__GBA[chan].callback != NULL) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        callback = __GBA[chan].callback;
        __GBA[chan].callback = NULL;
        callback(chan, __GBA[chan].ret);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void __GBASyncCallback(s32 chan) {
    OSWakeupThread(&__GBA[chan].threadQueue);
}

s32 __GBASync(s32 chan) {
    s32 enabled;
    s32 ret;

    enabled = OSDisableInterrupts();
    while (__GBA[chan].callback != NULL) {
        OSSleepThread(&__GBA[chan].threadQueue);
    }

    ret = __GBA[chan].ret;
    OSRestoreInterrupts(enabled);

    return ret;
}

void TypeAndStatusCallback(s32 chan, u32 type) {
    GBAControl* gba;
    GBATransferCallback proc;
    GBACallback callback;
    OSContext exceptionContext;
    OSContext* context;

    gba = &__GBA[chan];

    if ((type & 0xFF) != 0 || (type & 0xffff0000) != 0x40000) {
        gba->ret = GBA_NOT_READY;
    } else {
        if (SITransfer(chan, gba->output, gba->outputBytes, gba->input, gba->inputBytes,
                       __GBAHandler, gba->delay))
        {
            return;
        }
        gba->ret = GBA_BUSY;
    }

    if (gba->proc != NULL) {
        proc = gba->proc;
        gba->proc = NULL;
        proc(chan);
    }

    if (gba->callback != NULL) {
        context = OSGetCurrentContext();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        callback = gba->callback;
        gba->callback = NULL;
        callback(chan, gba->ret);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
        __OSReschedule();
    }
}

s32 __GBATransfer(s32 chan, s32 w1, s32 w2, GBATransferCallback callback) {
    s32 enabled;
    GBAControl* gba;
    gba = &__GBA[chan];
    enabled = OSDisableInterrupts();
    gba->proc = callback;
    gba->outputBytes = w1;
    gba->inputBytes = w2;
    SIGetTypeAsync(chan, TypeAndStatusCallback);
    OSRestoreInterrupts(enabled);

    return GBA_READY;
}

OSTime __GBASetDelay(s32 chan, OSTime delay) {
    OSTime oldDelay;
    GBAControl* gba;
    gba = &__GBA[chan];
    oldDelay = gba->delay;
    gba->delay = delay;
    return oldDelay;
}
