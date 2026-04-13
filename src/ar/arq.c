#include <dolphin.h>
#include <dolphin/ar.h>

#include "dolphin/ar/__ar.h"

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - arq.c is already 100% code/data complete in objdiff, but promoting it to
 *   Matching still fails the final main.dol checksum
 *
 * Most useful result so far:
 * - a fresh Matching flip on the current SDK branch rebuilt cleanly and only
 *   failed at the final checksum stage, so the remaining issue is hidden
 *   object/linkage shape rather than visible C or data mismatch
 * - a follow-up PAL-map check showed the current split config is also stale in
 *   this neighborhood: arq.c should own `.sbss 0x8032F1D8..0x8032F200` through
 *   `__ARQ_init_flag`, but `splits.txt` currently cuts the unit off at
 *   `0x8032F1E8`
 * - extending that split immediately ran into the neighboring stale AX/GX
 *   handoff chain, so the real next step here is fixing the whole `.sbss`
 *   boundary cluster around `arq.c`, not rewriting the C
 * - a full pass on that cluster confirmed the old PAL map is still useful for
 *   the early AR/AX/GX window, but it stops being safe to trust verbatim once
 *   the chain reaches the later TRK/MSL/Odemu/RedSound tail in this repo state
 * - the keepable lesson from that failed split pass is that the early
 *   `.sbss` ownership really is stale here, but the tail needs to be
 *   re-anchored against the current build's actual symbol identities and total
 *   section size instead of copied straight from the old PAL addresses
 * - a follow-up read of the currently extracted target objects showed why this
 *   keeps stalling: under the stale split layout, AX-side units are currently
 *   "borrowing" ARQ state to satisfy their own .sbss sizes
 *   (`__ARQRequestPendingHi` lands in AXAlloc; `__ARQCallbackHi` /
 *   `__ARQCallbackLo` / `__ARQChunkSize` / `__ARQ_init_flag` land in AXAux),
 *   so fixing arq.c is not a one-endpoint edit
 * - that makes the real next step more specific: re-split the whole
 *   `arq -> AXAlloc -> AXAux -> ...` small-data chain coherently in one pass,
 *   instead of extending arq.c in isolation and leaving the borrowed-tail
 *   ownership intact
 * - a later full config probe did exactly that through the early TRK/MSL/Odemu
 *   tail, using source statics plus the PAL map to re-anchor the `.sbss`
 *   windows coherently; it failed before compile at the split stage instead of
 *   in ARQ itself
 * - the first hard failure from that probe was at the GX/TRK seam:
 *   once `GXMisc`/`GBA`/`serpoll` were shifted forward, DTK still resolved
 *   `gTRKInputPendingPtr` at the stale old address `0x8032F358`, causing an
 *   overlap with `FinishQueue`
 * - so the remaining blocker is broader than just the visible ARQ/AX windows:
 *   there is at least one second stale tail authority (symbol attribution,
 *   split ownership, or both) that still pins the later TRK/MSL region to the
 *   pre-shift layout, and that needs to be identified before another coherent
 *   `.sbss` re-split attempt is likely to land
 * - on the current latest-main SDK branch, a narrower re-split through the
 *   early AX chain made it much farther before failing: `arq -> AXAlloc ->
 *   AXAux -> AXCL -> AXOut -> AXSPB -> AXVPB` all lined up cleanly against the
 *   PAL-map local ordering and the extracted object symbols
 * - the first hard conflict now shows up at `AXProf`: this repo still has a
 *   live `.sbss 0x8032F2A0..0x8032F2B0` split there, which overlaps the
 *   PAL-backed `AXSPB 0x8032F280..0x8032F2A4` / `AXVPB 0x8032F2A8..0x8032F2B4`
 *   windows before the map's later `AXProf 0x8032F2B8..0x8032F2C8`
 * - that makes `AXProf` the current earliest trustworthy cutoff for the old
 *   PAL `.sbss` guidance on this branch: the ARQ/AX tail before it still looks
 *   stale, but the later ownership chain has already diverged by that point
 */

#ifdef DEBUG
const char* __ARQVersion = "<< Dolphin SDK - ARQ\tdebug build: Apr  5 2004 03:56:20 (0x2301) >>";
#else
const char* __ARQVersion = "<< Dolphin SDK - ARQ\trelease build: Sep  5 2002 05:34:29 (0x2301) >>";
#endif

static ARQRequest* __ARQRequestQueueHi;
static ARQRequest* __ARQRequestTailHi;
static ARQRequest* __ARQRequestQueueLo;
static ARQRequest* __ARQRequestTailLo;
BOOL __ARQ_init_flag;
u32 __ARQChunkSize;
ARQCallback __ARQCallbackLo;
ARQCallback __ARQCallbackHi;
ARQRequest* __ARQRequestPendingLo;
ARQRequest* __ARQRequestPendingHi;

static inline void __ARQPopTaskQueueHi(void) {
    if (__ARQRequestQueueHi) {
        if (__ARQRequestQueueHi->type == 0) {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->source, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->length);
        } else {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->source, __ARQRequestQueueHi->length);
        }
        __ARQCallbackHi = __ARQRequestQueueHi->callback;
        __ARQRequestPendingHi = __ARQRequestQueueHi;
        __ARQRequestQueueHi = __ARQRequestQueueHi->next;
    }
}

void __ARQServiceQueueLo(void) {
    if (__ARQRequestPendingLo == 0 && __ARQRequestQueueLo) {
        __ARQRequestPendingLo = __ARQRequestQueueLo;
        __ARQRequestQueueLo = __ARQRequestQueueLo->next;
    }

    if (__ARQRequestPendingLo) {
        if (__ARQRequestPendingLo->length <= __ARQChunkSize) {
            if (__ARQRequestPendingLo->type == 0) {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->length);
            } else {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->source, __ARQRequestPendingLo->length);
            }
            __ARQCallbackLo = __ARQRequestPendingLo->callback;
        } else if (__ARQRequestPendingLo->type == 0) {
            ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source, __ARQRequestPendingLo->dest, __ARQChunkSize);
        } else {
            ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->source, __ARQChunkSize);
        }

        __ARQRequestPendingLo->length -= __ARQChunkSize;
        __ARQRequestPendingLo->source += __ARQChunkSize;
        __ARQRequestPendingLo->dest += __ARQChunkSize;
    }
}

void __ARQCallbackHack(u32 unused) {}

void __ARQInterruptServiceRoutine() {
    if (__ARQCallbackHi) {
        __ARQCallbackHi((u32)__ARQRequestPendingHi);
        __ARQRequestPendingHi = NULL;
        __ARQCallbackHi = NULL;        
    } else if (__ARQCallbackLo) {
        __ARQCallbackLo((u32)__ARQRequestPendingLo);
        __ARQRequestPendingLo = NULL;
        __ARQCallbackLo = NULL;        
    }

    __ARQPopTaskQueueHi();

    if (__ARQRequestPendingHi == 0) {
        __ARQServiceQueueLo();
    }
}

void ARQInit(void) {
    if (__ARQ_init_flag != TRUE) {
        OSRegisterVersion(__ARQVersion);

        __ARQRequestQueueHi = __ARQRequestQueueLo = NULL;
        __ARQChunkSize = 0x1000;
        ARRegisterDMACallback(__ARQInterruptServiceRoutine);
        __ARQRequestPendingHi = NULL;
        __ARQRequestPendingLo = NULL;
        __ARQCallbackHi = NULL;
        __ARQCallbackLo = NULL;
        __ARQ_init_flag = TRUE;
    }
}

void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority, u32 source, u32 dest, u32 length, ARQCallback callback) {
    BOOL level;

    ASSERTLINE(437, request);
    ASSERTLINE(438, (type == ARQ_TYPE_MRAM_TO_ARAM) || (type == ARQ_TYPE_ARAM_TO_MRAM));
    ASSERTLINE(439, (priority == ARQ_PRIORITY_LOW) || (priority == ARQ_PRIORITY_HIGH));
    ASSERTLINE(442, (length % ARQ_DMA_ALIGNMENT) == 0);

    request->next = NULL;
    request->owner = owner;
    request->type = type;
    request->source = source;
    request->dest = dest;
    request->length = length;
    if (callback) {
        request->callback = callback;
    } else {
        request->callback = __ARQCallbackHack;
    }

    level = OSDisableInterrupts();
    switch(priority) {
    case ARQ_PRIORITY_LOW:
        if (__ARQRequestQueueLo) {
            __ARQRequestTailLo->next = request;
        } else {
            __ARQRequestQueueLo = request;
        }
        __ARQRequestTailLo = request;
        break;
    case ARQ_PRIORITY_HIGH:
        if (__ARQRequestQueueHi) {
            __ARQRequestTailHi->next = request;
        } else {
            __ARQRequestQueueHi = request;
        }
        __ARQRequestTailHi = request;
        break;
    }

    if ((__ARQRequestPendingHi == 0) && ( __ARQRequestPendingLo == 0)) {
        __ARQPopTaskQueueHi();
        if ( __ARQRequestPendingHi == 0) {
            __ARQServiceQueueLo();
        }
    }

    OSRestoreInterrupts(level);
}

void ARQSetChunkSize(u32 size) {
    u32 i;

    i = size & 0x1F;
    if (i) {
        __ARQChunkSize = size + (0x20 - i);
        return;
    }
    __ARQChunkSize = size;
}

