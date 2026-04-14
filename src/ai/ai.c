#include <dolphin/ai.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/hw_regs.h>

#include "dolphin/gx/__gx.h"

#ifdef DEBUG
const char* __AIVersion = "<< Dolphin SDK - AI\tdebug build: Apr  5 2004 03:56:18 (0x2301) >>";
#else
const char* __AIVersion = "<< Dolphin SDK - AI\trelease build: Sep  5 2002 05:34:25 (0x2301) >>";
#endif

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - baseline source already reports 100% in objdiff, but promoting ai.c still
 *   breaks final main.dol linkage
 * - the visible source-side issue is the AI state globals in .sbss
 * - target wants them exported and laid out in the exact PAL-map order
 * - current plausible source still compiles them as local-binding statics
 *
 * Most useful probe so far:
 * - exporting the AI state globals and declaring them in reverse source order
 *   makes MWCC emit the exact target .sbss layout
 * - that confirms the layout lever is declaration / binding shape, not control flow
 * - on the current main-based SDK branch that exact layout is:
 *   __AIS_Callback / __AID_Callback / __CallbackStack / __OldStack /
 *   __AI_init_flag / __AID_Active / bound_32KHz / bound_48KHz / min_wait /
 *   max_wait / buffer
 * - promoting ai.c with that exact rebuilt layout still fails final main.dol,
 *   so the remaining blocker is no longer the visible AI .sbss ordering itself
 * - on the current latest-main SDK branch, declaration order alone no longer
 *   reproduces that exported layout; the source needed explicit zero
 *   initializers on the reverse-ordered globals to make MWCC export all eleven
 *   ai-state symbols in the exact target order
 * - even with that exact .sbss shape, promoting ai.c still failed final
 *   checksum, and objdiff reopened a small relocation-identity seam in
 *   AIRegisterDMACallback against target-side PAD imports rather than ai-local
 *   state
 * - a keepable follow-up on this branch did fix the visible AI global tail:
 *   declaring the three non-static OSTime globals as `buffer`, `max_wait`,
 *   then `min_wait` makes MWCC lay them out in the target PAL-map order
 *   `min_wait / max_wait / buffer` without affecting the rest of the unit
 * - promoting ai.c after that tail fix still fails only at the final
 *   main.dol checksum, so the remaining blocker is now even more clearly the
 *   hidden pad/ai/os symbol-binding seam rather than the visible ai-local tail
 * - a fresh pad/Pad.c probe narrowed one of those hidden dependencies further:
 *   when Pad.c is promoted after removing the dead GCCP01 BarrelBits slot, the
 *   target ai.o still imports `recalibrated$401` specifically, while the
 *   rebuilt source Pad.o emits `recalibrated$400`
 * - a direct current-branch disassembly read finally exposed the deeper shape
 *   of that seam: target `ai.o`'s sbss-bound relocations are uniformly `0x18`
 *   earlier than the rebuilt source object, so obvious ai-local references
 *   land on the preceding pad symbols in the extracted target object
 *   (`__AI_init_flag -> recalibrated$400`, `__AIS_Callback -> WaitingBits`,
 *   `__AID_Callback -> CheckingBits`, `__CallbackStack -> PendingBits`,
 *   `__AID_Active -> __PADSpec`, `__OldStack -> SamplingCallback`, etc.)
 * - because that same exact `0x18` early drift also shows up in `OS.o`'s
 *   `OSInit` pad-state accesses, this now looks like a coherent small-data
 *   seam / extracted-symbol-identity problem across the whole pad/ai/os
 *   cluster, not a plausible source rewrite inside `ai.c`
 * - a fresh map-backed metadata probe extended that same seam one unit later:
 *   marking the Pad.c state block and AI callback/timing tail local in
 *   `symbols.txt` to match the EN map makes `ai.c -> Matching` fail much
 *   earlier with `ar.o` undefineds on `min_wait_8032F1A0`,
 *   `max_wait_8032F1A8`, and `buffer_8032F1B0`
 * - direct objdiff on that probe shows target `ARRegisterDMACallback` binding
 *   its callback load/store to `min_wait_8032F1A0` instead of source
 *   `__AR_Callback`, which is the same uniform `0x18`-early small-data drift
 *   seen earlier at the pad/ai and ai/os seams
 * - a fresh current-branch retest of the older "export every AI state symbol"
 *   idea did move the rebuilt object, but not in a keepable direction:
 *   explicit zero-initialized non-static declarations for all eleven AI state
 *   globals flipped source `.sbss` into the reverse-declared exported order
 *   `buffer / max_wait / min_wait / bound_48KHz / bound_32KHz /
 *   __AID_Active / __AI_init_flag / __OldStack / __CallbackStack /
 *   __AID_Callback / __AIS_Callback`
 * - that export-all probe nudged the visible text match slightly upward
 *   (`99.62867% -> 99.64594%`), but `ai.c -> Matching` still only failed at
 *   the final checksum and did not resolve the remaining pad-side relocation
 *   identities in `AIRegisterDMACallback`
 * - so on latest main this is still not an authored-source fix; it only
 *   proves the linker blocker is deeper than whether the AI state symbols are
 *   local or global
 *
 * Why this is not keepable yet:
 * - the only source shape that produced the target .sbss order was not plausible
 *   original code
 * - promoting that probe still failed final linkage anyway
 * - the extracted target ai.o also carries PAD-side undefineds such as
 *   CheckingBits / PendingBits / SamplingCallback / __PADSpec
 * - so there is still at least one hidden object-attribution / linkage issue
 *   beyond the visible .sbss layout mismatch
 */

static AISCallback __AIS_Callback;
static AIDCallback __AID_Callback;
static u8* __CallbackStack;
static u8* __OldStack;
static BOOL __AI_init_flag;
static BOOL __AID_Active;
static OSTime bound_32KHz;
static OSTime bound_48KHz;
OSTime buffer;
OSTime max_wait;
OSTime min_wait;

typedef struct {
    OSTime t_start;
    OSTime t1;
    OSTime t2;
    OSTime t3;
    OSTime t4;
    OSTime t_end;
} STRUCT_TIMELOG;
#if DEBUG
STRUCT_TIMELOG profile;
#endif

// prototypes
void __AI_set_stream_sample_rate(u32 rate);
void __AIDHandler(__OSInterrupt interrupt, OSContext* context);
void __AISHandler(__OSInterrupt interrupt, OSContext* context);
void __AICallbackStackSwitch(void* cb);
void __AI_SRC_INIT(void);

AIDCallback AIRegisterDMACallback(AIDCallback callback) {
    AIDCallback old_callback;
    BOOL old;

    old_callback = __AID_Callback;
    old = OSDisableInterrupts();
    __AID_Callback = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}

void AIInitDMA(u32 start_addr, u32 length) {
    BOOL old;

    old = OSDisableInterrupts();
    __DSPRegs[24] = (__DSPRegs[24] & 0xFFFFFC00) | (start_addr >> 16);
    __DSPRegs[25] = (__DSPRegs[25] & 0xFFFF001F) | (start_addr & 0xFFFF);
    ASSERTMSGLINE(316, (length & 0x1F) == 0, "AIStartDMA: length must be multiple of 32 bytes");
    __DSPRegs[27] = (__DSPRegs[27] & 0xFFFF8000) | ((length >> 5) & 0xFFFF);
    OSRestoreInterrupts(old);
}

void AIStartDMA(void) {
    __DSPRegs[27] = __DSPRegs[27] | 0x8000;
}

void AIStopDMA(void) {
    __DSPRegs[27] = __DSPRegs[27] & ~0x8000;
}

u32 AIGetDMAStartAddr(void) {
    return ((__DSPRegs[24] << 16) & 0x03FF0000) |  (__DSPRegs[25] & 0xFFE0);
}

void AISetStreamPlayState(u32 state) {
    BOOL old;
    u8 vol_left;
    u8 vol_right;

    if (state != AIGetStreamPlayState()) {
        if (AIGetStreamSampleRate() == 0 && state == AI_STREAM_START) {
            vol_left = AIGetStreamVolRight();
            vol_right = AIGetStreamVolLeft();
            AISetStreamVolRight(0);
            AISetStreamVolLeft(0);
            old = OSDisableInterrupts();
            __AI_SRC_INIT();
            SET_REG_FIELD(0, __AIRegs[0], 1, 5, 1);
            SET_REG_FIELD(0, __AIRegs[0], 1, 0, AI_STREAM_START);
            OSRestoreInterrupts(old);
            AISetStreamVolLeft(vol_left);
            AISetStreamVolRight(vol_right);
            return;
        }
        SET_REG_FIELD(653, __AIRegs[0], 1, 0, state);
    }
}

u32 AIGetStreamPlayState(void) {
    return __AIRegs[0] & 1;
}

void AISetDSPSampleRate(u32 rate) {
    BOOL old;
    u32 play_state;
    u32 afr_state;
    u8 vol_left;
    u8 vol_right;

    if (rate != AIGetDSPSampleRate()) {
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFBF);
        if (rate == AI_SAMPLERATE_32KHZ) {
            vol_left = AIGetStreamVolLeft();
            vol_right = AIGetStreamVolRight();
            play_state = AIGetStreamPlayState();
            afr_state = AIGetStreamSampleRate();
            AISetStreamVolLeft(0U);
            AISetStreamVolRight(0U);
            old = OSDisableInterrupts();
            __AI_SRC_INIT();
            SET_REG_FIELD(0, __AIRegs[0], 1, 5, 1);
            SET_REG_FIELD(743, __AIRegs[0], 1, 1, afr_state);
            SET_REG_FIELD(744, __AIRegs[0], 1, 0, play_state);
            __AIRegs[0] |= 0x40;
            OSRestoreInterrupts(old);
            AISetStreamVolLeft(vol_left);
            AISetStreamVolRight(vol_right);
        }
    }
}

u32 AIGetDSPSampleRate(void) {
    return GET_REG_FIELD(__AIRegs[0], 1, 6) ^ 1;
}

void __AI_set_stream_sample_rate(u32 rate) {
    BOOL old;
    u32 play_state;
    u8 vol_left;
    u8 vol_right;
    u32 dsp_src_state;

    if (rate != AIGetStreamSampleRate()) {
        play_state = AIGetStreamPlayState();
        vol_left = AIGetStreamVolLeft();
        vol_right = AIGetStreamVolRight();
        AISetStreamVolRight(0);
        AISetStreamVolLeft(0);
        dsp_src_state = __AIRegs[0] & 0x40;
        SET_REG_FIELD(0, __AIRegs[0], 1, 6, 0);
        old = OSDisableInterrupts();
        __AI_SRC_INIT();
        __AIRegs[0] |= dsp_src_state;
        SET_REG_FIELD(0, __AIRegs[0], 1, 5, 1);
        SET_REG_FIELD(887, __AIRegs[0], 1, 1, rate);
        OSRestoreInterrupts(old);
        AISetStreamPlayState(play_state);
        AISetStreamVolLeft(vol_left);
        AISetStreamVolRight(vol_right);
    }
}

u32 AIGetStreamSampleRate(void) {
    return GET_REG_FIELD(__AIRegs[0], 1, 1);
}

void AISetStreamVolLeft(u8 vol) {
    SET_REG_FIELD(945, __AIRegs[1], 8, 0, vol);
}

u8 AIGetStreamVolLeft(void) {
    return GET_REG_FIELD(__AIRegs[1], 8, 0);
}

void AISetStreamVolRight(u8 vol) {
    SET_REG_FIELD(986, __AIRegs[1], 8, 8, vol);
}

u8 AIGetStreamVolRight(void)
{
    return (__AIRegs[1] & (0xFF << 8)) >> 8;
}

void AIInit(u8* stack) {
    if (__AI_init_flag != TRUE) {
        OSRegisterVersion(__AIVersion);

        bound_32KHz = OSNanosecondsToTicks(31524);
        bound_48KHz = OSNanosecondsToTicks(42024);
        min_wait = OSNanosecondsToTicks(42000);
        max_wait = OSNanosecondsToTicks(63000);
        buffer = OSNanosecondsToTicks(3000);
        AISetStreamVolRight(0);
        AISetStreamVolLeft(0);
        __AIRegs[3] = 0;
        __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
        __AI_set_stream_sample_rate(AI_SAMPLERATE_48KHZ);
        AISetDSPSampleRate(AI_SAMPLERATE_32KHZ);
#if DEBUG
        OSReport("AIInit(): DSP is 32KHz\n");
#endif
        __AIS_Callback = NULL;
        __AID_Callback = NULL;
        __CallbackStack = stack;
        if (stack) {
            ASSERTMSGLINE(1107, ((u32)stack & 7) == 0, "AIInit: stack must be 8-byte aligned");
        }
        __OSSetInterruptHandler(5, __AIDHandler);
        __OSUnmaskInterrupts(0x04000000);
        __OSSetInterruptHandler(8, __AISHandler);
        __OSUnmaskInterrupts(0x800000);
        __AI_init_flag = TRUE;
    }
}

void AIReset(void) {
    __AI_init_flag = FALSE;
}

void __AISHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptionContext;

    __AIRegs[0] |= 8;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (__AIS_Callback) {
        __AIS_Callback(__AIRegs[2]);
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

void __AIDHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptionContext;
    u16 tmp;

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA0) | 8;
    __DSPRegs[5] = tmp;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (__AID_Callback && !__AID_Active) {
        __AID_Active = TRUE;
        if (__CallbackStack) {
            __AICallbackStackSwitch(__AID_Callback);
        } else {
            __AID_Callback();
        }
        __AID_Active = FALSE;
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

asm void __AICallbackStackSwitch(register void* cb) {
    nofralloc
    mflr r0
    stw r0, 0x4(r1)
    stwu r1, -0x18(r1)
    stw r31, 0x14(r1)
    mr r31, r3
    lis r5, __OldStack@ha
    addi r5, r5, __OldStack@l
    stw r1, 0x0(r5)
    lis r5, __CallbackStack@ha
    addi r5, r5, __CallbackStack@l
    lwz r1, 0x0(r5)
    subi r1, r1, 0x8
    mtlr r31
    blrl
    lis r5, __OldStack@ha
    addi r5, r5, __OldStack@l
    lwz r1, 0x0(r5)
    lwz r0, 0x1c(r1)
    lwz r31, 0x14(r1)
    addi r1, r1, 0x18
    mtlr r0
    blr
}

void __AI_SRC_INIT(void) {
    OSTime rising_32khz = 0;
    OSTime rising_48khz = 0;
    OSTime diff = 0;
    OSTime t1 = 0;
    OSTime temp;
    u32 temp0;
    u32 temp1;
    u32 done = 0;
    u32 volume = 0;
    u32 Init_Cnt = 0;
    u32 walking = 0;

    walking = 0;
    Init_Cnt = 0;
    temp = 0;

#if DEBUG
    profile.t_start = OSGetTime();
#endif

    while (!done) {
        SET_REG_FIELD(0, __AIRegs[0], 1, 5, 1);
        SET_REG_FIELD(0, __AIRegs[0], 1, 1, 0);
        SET_REG_FIELD(0, __AIRegs[0], 1, 0, AI_STREAM_START);
        temp0 = __AIRegs[2];
        while (temp0 == __AIRegs[2]) {
        }
        rising_32khz = OSGetTime();
        SET_REG_FIELD(0, __AIRegs[0], 1, 1, 1);
        SET_REG_FIELD(0, __AIRegs[0], 1, 0, AI_STREAM_START);
        temp1 = __AIRegs[2];
        while (temp1 == __AIRegs[2]) {
        }
        rising_48khz = OSGetTime();
        diff = rising_48khz - rising_32khz;
        SET_REG_FIELD(0, __AIRegs[0], 1, 1, 0);
        SET_REG_FIELD(0, __AIRegs[0], 1, 0, AI_STREAM_STOP);
        if (diff < bound_32KHz - buffer) {
            temp = min_wait;
            done = 1;
            Init_Cnt++;
        } else if (diff >= bound_32KHz + buffer && diff < bound_48KHz - buffer) {
            temp = max_wait;
            done = 1;
            Init_Cnt++;
        } else {
            done = 0;
            walking = 1;
            Init_Cnt++;
        }
    }
    while (rising_48khz + temp > OSGetTime()) {
    }
#if DEBUG
    profile.t_end = OSGetTime();
#endif
}

