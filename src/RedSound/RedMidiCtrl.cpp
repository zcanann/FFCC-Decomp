#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"

extern "C" {
void* memcpy(void*, const void*, unsigned long);
void* memmove(void*, const void*, unsigned long);
void* memset(void*, int, unsigned long);
int GetWaveBank__9CRedEntryFi(CRedEntry*, int);
}

int PTR_SineSwing__Fi_8021e9d0[] = {
    (int)SineSwing, (int)TriangleSwing, (int)SawSwing, (int)DutySwing,
    (int)RandomSwing, (int)DutySwing,     (int)DutySwing, (int)DutySwing,
    (int)SineSwingR, (int)TriangleSwingR, (int)SawSwingR, (int)DutySwingR,
    (int)RandomSwingR, (int)DutySwingR,   (int)DutySwingR, (int)DutySwingR,
};

int gRedCommandHandlerTable[] = {
    (int)__MidiCtrl_Stop,             (int)__MidiCtrl_Sleep,           (int)__MidiCtrl_WholeLoopStart,
    (int)__MidiCtrl_WholeLoopEnd,     (int)__MidiCtrl_LoopStart,       (int)__MidiCtrl_LoopEnd,
    (int)__MidiCtrl_LoopRepeat,       (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_TempoDirect,
    (int)__MidiCtrl_TempoChange,      (int)__MidiCtrl_ReverbDepthDirect, (int)__MidiCtrl_ReverbDepthChange,
    (int)__MidiCtrl_TimeSignature,    (int)__MidiCtrl_KeySignature,    (int)__MidiCtrl_PhraseSignature,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_KeyOnSame,       (int)__MidiCtrl_KeyOnNoteVelocity,
    (int)__MidiCtrl_KeyOnNote,        (int)__MidiCtrl_KeyOnVelocity,   (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_KeyOffSame,       (int)__MidiCtrl_KeyOffNoteVelocity, (int)__MidiCtrl_KeyOffNote,
    (int)__MidiCtrl_KeyOffVelocity,   (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_Wave,
    (int)__MidiCtrl_WaveWithBank,     (int)__MidiCtrl_VolumeDirect,    (int)__MidiCtrl_VolumeChange,
    (int)__MidiCtrl_ExpressionDirect, (int)__MidiCtrl_ExpressionChange, (int)__MidiCtrl_PanDirect,
    (int)__MidiCtrl_PanChange,        (int)__MidiCtrl_PortamentOn,     (int)__MidiCtrl_PortamentOff,
    (int)__MidiCtrl_SlurOn,           (int)__MidiCtrl_SlurOff,         (int)__MidiCtrl_Sweep,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_TenutoOn,        (int)__MidiCtrl_TenutoOff,
    (int)__MidiCtrl_ADSR_AL,          (int)__MidiCtrl_ADSR_AR,         (int)__MidiCtrl_ADSR_DL,
    (int)__MidiCtrl_ADSR_DR,          (int)__MidiCtrl_ADSR_SL,         (int)__MidiCtrl_ADSR_SR,
    (int)__MidiCtrl_ADSR_RL,          (int)__MidiCtrl_ADSR_RR,         (int)__MidiCtrl_ADSR_Default,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_SustainPedal,     (int)__MidiCtrl_ChannelAlloc,    (int)__MidiCtrl_ChannelPriority,
    (int)__MidiCtrl_ChannelFix,       (int)__MidiCtrl_VibrateOn,       (int)__MidiCtrl_VibrateOff,
    (int)__MidiCtrl_VibrateDepthDirect, (int)__MidiCtrl_VibrateDepthChange, (int)__MidiCtrl_VibrateRateDirect,
    (int)__MidiCtrl_VibrateRateChange, (int)__MidiCtrl_VibrateType,    (int)__MidiCtrl_VibrateDelay,
    (int)__MidiCtrl_TremoloOn,        (int)__MidiCtrl_TremoloOff,      (int)__MidiCtrl_TremoloDepthDirect,
    (int)__MidiCtrl_TremoloDepthChange, (int)__MidiCtrl_TremoloRateDirect, (int)__MidiCtrl_TremoloRateChange,
    (int)__MidiCtrl_TremoloType,      (int)__MidiCtrl_TremoloDelay,    (int)__MidiCtrl_ShakeOn,
    (int)__MidiCtrl_ShakeOff,         (int)__MidiCtrl_ShakeDepthDirect, (int)__MidiCtrl_ShakeDepthChange,
    (int)__MidiCtrl_ShakeRateDirect,  (int)__MidiCtrl_ShakeRateChange, (int)__MidiCtrl_ShakeType,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_FineTuneAbsolute, (int)__MidiCtrl_FineTuneRelative,
    (int)__MidiCtrl_KeyTransposeAbsolute, (int)__MidiCtrl_KeyTransposeRelative, (int)__MidiCtrl_PitchBend,
    (int)__MidiCtrl_PitchBendRange,   (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_ReverbOn,         (int)__MidiCtrl_ReverbOff,       (int)__MidiCtrl_ReverbMix,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_StepRelative,    (int)__MidiCtrl_StepRelative2,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_FuzzyOn,          (int)__MidiCtrl_FuzzyOff,        (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_NoSupport,       (int)__MidiCtrl_NoSupport,
    (int)__MidiCtrl_NoSupport,        (int)__MidiCtrl_Pass,
};

/*
 * --INFO--
 * PAL Address: 0x801C7478
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
int DataAddCompute(int* current, int target, int* delta)
{
    int value = *current;

    if (target != (value >> 0xc)) {
        return (((target << 0xc) | 0x800) - value) / *delta;
    }

    *delta = 0;
    return 0;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801C74C8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void KeyOnReserveClear(RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* slot = (int*)keyOnData;
    do {
        if (*slot == (int)track) {
            *slot = 0;
        }
        slot += 2;
    } while (slot < (int*)((int)keyOnData + 0x600));
}

/*
 * --INFO--
 * PAL Address: 0x801C7504
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void KeyOnReserve(RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* slot;
    int* limit;

    if ((((signed char*)track)[0x26] & 5) != 0) {
        slot = (int*)((int)keyOnData + ((signed char*)track)[0x14e] * 8);
        if ((*slot == 0) || (*slot == (int)track)) {
            *slot = (int)track;
            slot[1] = ((int*)track)[9];
            DAT_8032f3f8++;
        }
        return;
    }

    if ((((unsigned char*)track)[0x26] & 8) != 0) {
        slot = (int*)((int)keyOnData + 0x200);
        limit = (int*)((int)keyOnData + 0x400);
    } else {
        slot = (int*)((int)keyOnData + 0x400);
        limit = (int*)((int)keyOnData + 0x600);
    }

    do {
        if (*slot == 0) {
            *slot = (int)track;
            slot[1] = ((int*)track)[9];
            DAT_8032f3f8++;
            break;
        }
        slot += 2;
    } while (slot < limit);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801C75F4
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void KeyOffSet(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    char key;
    int* slot;

    if (((void*)control == (void*)((int)DAT_8032f3f0 + 0x928)) || ((((unsigned int*)track)[0x41] & 0x80000) == 0)) {
        ((int*)track)[0x44] = 0;
        key = ((char*)track)[0x24];
        slot = (int*)keyOnData;
        do {
            if ((*slot == (int)track) && (*(char*)(slot + 1) == key)) {
                *slot = 0;
            }
            slot += 2;
        } while (slot < (int*)((int)keyOnData + 0x600));

        key = ((char*)track)[0x24];
        slot = (int*)DAT_8032f444;
        do {
            if ((*slot == (int)track && (*(char*)(slot + 6) == key))) {
                slot[0x24] &= 0xfffffffe;
                slot[0x24] |= 2;
            }
            slot += 0x30;
        } while (slot < (int*)(DAT_8032f444 + 0xc00));
    }
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801C76D0
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int SineSwing(int phase)
{
    u32 index = (u32)phase & 0x1FF;
    int value = DAT_8021e1d0[index];

    if (((u32)phase & 0x200) != 0) {
        value = -value;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x801C770C
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 4
int TriangleSwing(int phase)
{
    u32 low = (u32)phase & 0xFF;
    int result = low << 8;

    switch (((u32)phase >> 8) & 3) {
    case 1:
        result = 0x10000 - result;
        break;
    case 2:
        result = -result;
        break;
    case 3:
        result -= 0x10000;
        break;
    }

    return (low | result);
}
#pragma optimization_level 0

/*
 * --INFO--
 * PAL Address: 0x801C7768
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int SawSwing(int phase)
{
    signed char value = (signed char)(phase >> 2);
    return (int)value << 8;
}

/*
 * --INFO--
 * PAL Address: 0x801C778C
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int DutySwing(int phase)
{
    int value;
    int result;

    if ((phase & 0x200) != 0) {
        value = -0x10000;
    } else {
        value = 0x10000;
    }
    result = value;
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C77C4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RandomSwing(int phase)
{
    int index = phase >> 8;
    char value;

    index &= 0xFF;
    value = DAT_8021dcce[index];
    return (int)value << 8;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int SineSwingR(int phase)
{
    phase ^= 0x200;
    int value = phase & 0x1FF;
    value = DAT_8021e1d0[value];
    if ((phase & 0x200) != 0) {
        value = -value;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x801C783C
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 4
int TriangleSwingR(int phase)
{
    int mode;
    int result;

    phase ^= 0x200;
    mode = (phase >> 8) & 3;
    result = (phase & 0xFF) << 8;
    if (mode != 2) {
        if (mode >= 2) {
            if (mode < 4) {
                result -= 0x10000;
            }
        } else if (mode != 0) {
            result = 0x10000 - result;
        }
    } else {
        result = -result;
    }
    return (phase & 0xFF) | result;
}
#pragma optimization_level 0

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int DutySwingR(int phase)
{
    int value;
    int result;

    phase ^= 0x200;
    if ((phase & 0x200) != 0) {
        value = -0x10000;
    } else {
        value = 0x10000;
    }

    result = value;
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int SawSwingR(int phase)
{
    signed char value = static_cast<signed char>((~phase) >> 2);
    return static_cast<int>(value) << 8;
}

/*
 * --INFO--
 * PAL Address: 0x801C7904
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RandomSwingR(int phase)
{
    return static_cast<int>(DAT_8021dcce[((phase >> 8) & 0xFF) ^ 0x40]) << 8;
}

/*
 * --INFO--
 * PAL Address: 0x801C7940
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_NoSupport(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
	__MidiCtrl_Stop(control, keyOnData, track);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_Pass(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801C797C
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_Stop(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    unsigned int* seTrack;
    unsigned int* controlData;

    ((int*)track)[0x41] = 0;
    KeyOffSet(control, keyOnData, track);

    seTrack = DAT_8032f444;
    do {
        if ((RedTrackDATA*)*seTrack == track) {
            ((unsigned char*)seTrack)[0x1a] &= (unsigned char)0xfa;
        }
        seTrack += 0x30;
    } while (seTrack < DAT_8032f444 + 0xc00);

    *((int*)track) = 0;
    if ((int*)control < (int*)((int)DAT_8032f3f0 + 0xdbc)) {
        *(short*)((int)control + 0x48e) = *(short*)((int)control + 0x48e) - 1;
        if ((*(short*)((int)control + 0x48e) == 0) &&
            ((DAT_8032f424 == 1) || ((((int*)control)[0x11b] & 1) == 0))) {
            controlData = (unsigned int*)control;
            seTrack = DAT_8032f444;
            do {
                if ((controlData[0] <= seTrack[0]) &&
                    (seTrack[0] < controlData[0] + (unsigned int)((unsigned char*)control)[0x491] * 0x154)) {
                    seTrack[0x25] &= 0xfffffff3;
                    seTrack[0x24] &= 0xfffffffe;
                    seTrack[0x24] |= 2;
                    seTrack[0] = 0;
                }
                seTrack += 0x30;
            } while (seTrack < DAT_8032f444 + 0xc00);

            DAT_8032e154.MusicHistoryManager(0, controlData[0x11c]);
            DAT_8032e154.WaveHistoryManager(0, controlData[0x11f]);
            controlData[0x11c] = 0xffffffff;
            controlData[0x122] = 0;
            RedDelete((int)controlData[0]);
            controlData[0] = 0;
        }
    } else {
        if (((int*)track)[6] != 0) {
            DAT_8032e154.WaveHistoryManager(0, *(short*)(((int*)track)[6] + 2));
        }
        DAT_8032e154.SeSepHistoryManager(0, ((int*)track)[0x3d]);
        ((int*)track)[0x3e] = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7B44
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_Sleep(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA*)
{
    if ((DAT_8032f424 == 1) && ((void*)control == DAT_8032f3f0)) {
        int* track = (int*)*(int*)control;
        do {
            if (*track != 0) {
                __MidiCtrl_Stop(control, keyOnData, (RedTrackDATA*)track);
            }
            track += 0x55;
        } while (track < (int*)(*(int*)control + (unsigned int)*(unsigned char*)((char*)control + 0x491) * 0x154));
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7BCC
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_WholeLoopStart(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* controlData = (int*)control;
    int* trackData = (int*)track;
    int loopBase = controlData[0x121];
    int deltaAdjust = 1 - trackData[0x42];
    int slot = 0;
    int* scan;

    controlData[0x11b] |= 1;
    for (scan = (int*)controlData[0]; scan < trackData; scan += 0x55) {
        controlData[slot + 10] = *scan;
        controlData[slot + 0x4a] = scan[0x42] + deltaAdjust;
        controlData[slot + 0x8a] = scan[0x41];
        controlData[slot + 0xca] = scan[9];
        slot++;
    }

    {
        unsigned char* command = (unsigned char*)*scan;
        int delta = DeltaTimeSumup(&command);
        int* nextTrack = scan + 0x55;

        controlData[slot + 10] = (int)command;
        controlData[slot + 0x4a] = scan[0x42] + delta + deltaAdjust;
        controlData[slot + 0x8a] = scan[0x41];
        controlData[slot + 0xca] = scan[9];

        if (nextTrack < (int*)(controlData[0] + (unsigned int)*(unsigned char*)((char*)control + 0x491) * 0x154)) {
            for (; nextTrack < (int*)(controlData[0] + (unsigned int)*(unsigned char*)((char*)control + 0x491) * 0x154);
                 nextTrack += 0x55) {
                int currentDelta = deltaAdjust + (nextTrack[0x42] - loopBase);

                while ((currentDelta < 1) && (*nextTrack != 0)) {
                    unsigned char* cmd = (unsigned char*)*nextTrack;
                    *nextTrack = (int)(cmd + 1);
                    ((void (*)(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*))gRedCommandHandlerTable[*cmd])(
                        control, keyOnData, (RedTrackDATA*)nextTrack);

                    if (*nextTrack != 0) {
                        int step = DeltaTimeSumup((unsigned char**)nextTrack);
                        currentDelta += step;
                        nextTrack[0x42] += step;
                    }
                }

                controlData[slot + 0xb] = *nextTrack;
                controlData[slot + 0x4b] = currentDelta;
                controlData[slot + 0x8b] = nextTrack[0x41];
                controlData[slot + 0xcb] = nextTrack[9];
                slot++;
            }
        }
    }

    controlData[0x10d] = (int)*(short*)((char*)control + 0x48e);
    memmove(controlData + 0x10e, controlData + 3, 0x10);
    controlData[0x10f] = controlData[0x10f] - deltaAdjust;
    if (controlData[0x10f] < 0) {
        controlData[0x10f] += controlData[0x110];
        controlData[0x10e] = controlData[0x10e] - 1;
    }
    memmove(controlData + 0x10a, controlData + 0x112, 0xc);
}

/*
 * --INFO--
 * PAL Address: 0x801C7E40
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_WholeLoopEnd(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA*)
{
    int* controlData = (int*)control;

    controlData[0x11b] |= 2;
    if ((DAT_8032f424 == 1) && ((void*)control == DAT_8032f3f0)) {
        int* track = (int*)controlData[0];
        do {
            if (*track != 0) {
                __MidiCtrl_Stop(control, keyOnData, (RedTrackDATA*)track);
            }
            track += 0x55;
        } while (track < (int*)(controlData[0] + (unsigned int)*(unsigned char*)((char*)control + 0x491) * 0x154));
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7ED4
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_LoopStart(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    *(short*)((char*)track + 0x13C) = *(short*)((char*)track + 0x13C) + 1;
    *(unsigned short*)((char*)track + 0x13C) &= 3;
    ((int*)track)[*(short*)((char*)track + 0x13C) + 2] = *(int*)track;
    *(unsigned short*)((char*)track + *(short*)((char*)track + 0x13C) * 2 + 0x130) =
        *(unsigned short*)((char*)track + 0x144);
    *(unsigned short*)((char*)track + *(short*)((char*)track + 0x13C) * 2 + 0x128) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C7F2C
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_LoopEnd(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command;
    int* trackData = (int*)track;
    unsigned int loopCount;
    int loopIndexOffset;

    command = (unsigned char*)trackData[0];
    trackData[0] = (int)(command + 1);
    loopCount = command[0];
    if (loopCount == 0) {
        loopCount = 0x100;
    }

    loopIndexOffset = *(short*)(trackData + 0x4f) * 2 + 0x128;
    *(short*)((char*)trackData + loopIndexOffset) = *(short*)((char*)trackData + loopIndexOffset) + 1;
    if (*(unsigned short*)((char*)trackData + *(short*)(trackData + 0x4f) * 2 + 0x128) == loopCount) {
        *(short*)(trackData + 0x4f) = *(short*)(trackData + 0x4f) - 1;
        *(unsigned short*)(trackData + 0x4f) &= 3;
    } else {
        trackData[0] = trackData[*(short*)(trackData + 0x4f) + 2];
        *(short*)(trackData + 0x51) = *(short*)((char*)trackData + *(short*)(trackData + 0x4f) * 2 + 0x130);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7FD0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_LoopRepeat(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    *(int*)track = ((int*)track)[*(short*)((char*)track + 0x13c) + 2];
    *(short*)((char*)track + 0x144) =
        *(short*)((char*)track + *(short*)((char*)track + 0x13c) * 2 + 0x130);
}

/*
 * --INFO--
 * PAL Address: 0x801C7FFC
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TempoDirect(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    u8* command = (u8*)*(u32*)track;

    *(u32*)track = (u32)(command + 1);
    *(u32*)((u8*)control + 0x448) = ((u32)*command) << 0xc;
    *(u32*)((u8*)control + 0x44C) = 0;
    *(u32*)((u8*)control + 0x450) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C8028
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TempoChange(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned int delta[3];
    int* controlData = (int*)control;

    if (*(char*)*(int*)track == '\0') {
        delta[0] = 0x100;
    } else {
        delta[0] = *(unsigned char*)*(int*)track;
    }

    controlData[0x113] = DataAddCompute(controlData + 0x112, *(unsigned char*)(*(int*)track + 1), (int*)delta);
    controlData[0x114] = delta[0];
    *(int*)track += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C80B4
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ReverbDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command = (unsigned char*)((int*)track)[0];
    int* trackData = (int*)track;
    int* reverbDepth = trackData + 0x1a;

    trackData[0] = (int)(command + 1);
    *reverbDepth = (int)*command;

    if (*reverbDepth != 0) {
        *reverbDepth += 1;
        *reverbDepth <<= 8;
        *reverbDepth -= 1;
        *reverbDepth <<= 0xc;
    }

    trackData[0x1b] = 0;
    trackData[0x1c] = 0;
    SetVoiceAccess(track, 8);
}

/*
 * --INFO--
 * PAL Address: 0x801C8158
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ReverbDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned int stepCount[2];
    char* command = (char*)((int*)track)[0];
    int* trackData = (int*)track;
    int value;
    char targetDepth;

    if (*command == '\0') {
        stepCount[0] = 0x100;
    } else {
        stepCount[0] = (unsigned char)*command;
    }

    trackData[0] = (int)(command + 1);
    targetDepth = *command;
    if (targetDepth != '\0') {
        targetDepth = -1;
    }

    value = DataAddCompute(trackData + 0x1a, (int)targetDepth, (int*)stepCount);
    trackData[0x1b] = value;
    trackData[0x1c] = stepCount[0];
    trackData[0] += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C820C
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TimeSignature(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command = (unsigned char*)*(int*)track;

    *(unsigned short*)((int)control + 0x18) = command[0];
    *(unsigned short*)((int)control + 0x1a) = command[1];
    *(int*)((int)control + 0x14) =
        (0xc0 / (int)*(short*)((int)control + 0x1a)) * (int)*(short*)((int)control + 0x18);
    *(int*)track += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C824C
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeySignature(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command = (unsigned char*)((int*)track)[0];
    int* controlData = (int*)control;
    int scale;
    unsigned int voice;

    ((int*)track)[0] = (int)(command + 1);
    scale = command[0] & 0x1f;
    controlData[0x120] = scale;
    controlData[2] = DAT_8021dc20[scale] + (int)DAT_8021dc20;

    if (DAT_8032f414 != 0) {
        voice = (unsigned int)controlData[0];
        do {
            *(int*)(voice + 0x20) = controlData[2];
            voice += 0x154;
        } while (voice < (unsigned int)(controlData[0] + (unsigned int)*(unsigned char*)((char*)control + 0x491) * 0x154));
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C82D8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PhraseSignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    *trackData = *trackData + 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C82F8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOnSame(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8328
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
#pragma dont_inline on
void __MidiCtrl_KeyOnNoteVelocity(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);
    unsigned char* command = reinterpret_cast<unsigned char*>(trackData[0]);

    trackData[0] = reinterpret_cast<int>(command + 1);
    *reinterpret_cast<unsigned char*>(trackData + 9) = *command;
    command = reinterpret_cast<unsigned char*>(trackData[0]);
    trackData[0] = reinterpret_cast<int>(command + 1);
    *reinterpret_cast<unsigned char*>(reinterpret_cast<int>(trackData) + 0x25) = *command;

    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8390
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOnNote(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);
    unsigned char* command = reinterpret_cast<unsigned char*>(trackData[0]);

    trackData[0] = reinterpret_cast<int>(command + 1);
    *reinterpret_cast<unsigned char*>(trackData + 9) = *command;

    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C83E0
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOnVelocity(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);
    unsigned char* command = reinterpret_cast<unsigned char*>(trackData[0]);

    trackData[0] = reinterpret_cast<int>(command + 1);
    *reinterpret_cast<unsigned char*>(reinterpret_cast<int>(trackData) + 0x25) = *command;

    KeyOnReserve(keyOnData, track);
}
#pragma dont_inline reset
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801C8430
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOffSame(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8468
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOffNoteVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);
    unsigned char* command = reinterpret_cast<unsigned char*>(trackData[0]);

    trackData[0] = reinterpret_cast<int>(command + 1);
    *reinterpret_cast<unsigned char*>(trackData + 9) = *command;
    trackData[0] += 1;

    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C84C8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOffNote(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);
    unsigned char* command = reinterpret_cast<unsigned char*>(trackData[0]);

    trackData[0] = reinterpret_cast<int>(command + 1);
    *reinterpret_cast<unsigned char*>(trackData + 9) = *command;

    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C851C
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyOffVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);

    trackData[0] += 1;

    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8564
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_Wave(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command;
    unsigned int waveNo;
    int* trackData = (int*)track;

    trackData[7] = 0;
    trackData[0x47] = 0;
    command = (unsigned char*)*trackData;
    *trackData = (int)(command + 1);
    waveNo = (unsigned int)*command;
    if ((trackData[6] != 0) && ((int)waveNo < *(int*)(trackData[6] + 8))) {
        trackData[7] = trackData[6] + *(int*)(trackData[6] + 0x20 + waveNo * 4);
        trackData[0x47] = *(int*)(trackData[6] + 0x10);
        memset(trackData + 0x35, 0xffffffff, 0xc);
    }
    *(unsigned char*)((int)trackData + 0x14d) = 0x10;
    trackData[0x49] = waveNo;
}

/*
 * --INFO--
 * PAL Address: 0x801C861C
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_WaveWithBank(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u8* command;
	u8 bankNo;
	u32 waveNo;
	int waveBank;
	int* trackData = (int*)track;

	command = (u8*)trackData[0];
	trackData[0] = (int)(command + 1);
	bankNo = *command;
	command = (u8*)trackData[0];
	trackData[0] = (int)(command + 1);
	waveNo = *command;
	trackData[7] = 0;
	trackData[0x47] = 0;
	waveBank = GetWaveBank__9CRedEntryFi(&DAT_8032e154, bankNo);
	if (waveBank != 0) {
		waveBank = *(int*)(waveBank + 8);
		trackData[7] = waveBank + *(int*)(waveBank + 0x20 + waveNo * 4);
		trackData[0x47] = *(int*)(waveBank + 0x10);
		memset(trackData + 0x35, 0xffffffff, 0xc);
	}
	*(u8*)((int)trackData + 0x14d) = bankNo;
	trackData[0x49] = waveNo;
}

/*
 * --INFO--
 * PAL Address: 0x801C86C4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VolumeDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned int volume;
    unsigned char* command;
    int* trackData = (int*)track;

    command = (unsigned char*)trackData[0];
    trackData[0] = (int)(command + 1);
    volume = *command;
    if (volume != 0) {
        volume = (((volume + 1) * 0x100) - 1) << 0xc;
    }

    trackData[10] = volume;
    trackData[0xb] = 0;
    trackData[0xc] = 0;
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C8720
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VolumeChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int delta[4];
    unsigned char* command;
    unsigned int volume;
    int* trackData = (int*)track;

    delta[0] = DeltaTimeSumup((unsigned char**)trackData);
    if (delta[0] == 0) {
        delta[0] = 1;
    }

    command = (unsigned char*)trackData[0];
    trackData[0] = (int)(command + 1);
    volume = *command;
    if (volume != 0) {
        volume = ((volume + 1) * 0x100) - 1;
    }

    trackData[0xb] = DataAddCompute(trackData + 10, volume, delta);
    trackData[0xc] = delta[0];
}

/*
 * --INFO--
 * PAL Address: 0x801C87B4
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ExpressionDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command = (unsigned char*)*(int*)track;
    int* trackData = (int*)track;

    *trackData = (int)(command + 1);
    trackData[0xd] = ((int)(char)*command) << 0xc;
    trackData[0xe] = 0;
    trackData[0xf] = 0;
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C8800
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ExpressionChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int delta[4];
    char* command;
    int* trackData = (int*)track;

    delta[0] = DeltaTimeSumup((unsigned char**)trackData);
    if (delta[0] == 0) {
        delta[0] = 1;
    }

    command = (char*)trackData[0];
    trackData[0] = (int)(command + 1);
    trackData[0xe] = DataAddCompute(trackData + 0xd, *command, delta);
    trackData[0xf] = delta[0];
}

/*
 * --INFO--
 * PAL Address: 0x801C8884
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PanDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    u8* command;
    int* trackData = (int*)track;

    command = (u8*)trackData[0];
    trackData[0] = (int)(command + 1);
    trackData[0x10] = ((u32)*command) << 0xc;
    trackData[0x11] = 0;
    trackData[0x12] = 0;
    if (trackData[0x2d] == 0) {
        trackData[0x33] = 0;
    }
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C88E0
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PanChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[4];
	u8* command;
	int* trackData = (int*)track;

	delta[0] = DeltaTimeSumup((unsigned char**)trackData);
	if (delta[0] == 0) {
		delta[0] = 1;
	}
	if (trackData[0x2d] == 0) {
		trackData[0x10] += trackData[0x33] * 0x1000;
		trackData[0x33] = 0;
	}
	command = (u8*)trackData[0];
	trackData[0] = (int)(command + 1);
	trackData[0x11] = DataAddCompute(trackData + 0x10, *command, delta);
	trackData[0x12] = delta[0];
}

/*
 * --INFO--
 * PAL Address: 0x801C8984
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PortamentOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	((int*)track)[0x46] = DeltaTimeSumup((unsigned char**)track);
}

/*
 * --INFO--
 * PAL Address: 0x801C89B8
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PortamentOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    ((int*)track)[0x46] = 0;
    ((int*)track)[0x48] = -1;
}

/*
 * --INFO--
 * PAL Address: 0x801C89CC
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_SlurOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    ((unsigned int*)track)[0x41] |= 0x80000;
    ((unsigned int*)track)[0x41] &= 0xFFEFFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x801C89E8
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_SlurOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    ((unsigned int*)track)[0x41] &= 0xFFF7FFFF;
}

/*
 * --INFO--
 * PAL Address: 0x801C89F8
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_Sweep(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    int delta = DeltaTimeSumup((unsigned char**)trackData);
    char* command;
    int value = 0;
    int* voiceData;

    if (delta == 0) {
        delta = 1;
    }

    command = (char*)trackData[0];
    trackData[0] = (int)(command + 1);
    DataAddCompute(&value, ((int)*command) << 8, &delta);
    trackData[0x45] = value;
    trackData[0x44] = delta;
    trackData[0x48] &= 0xfffff000;

    voiceData = (int*)DAT_8032f444;
    do {
        if ((int*)voiceData[0] == trackData) {
            voiceData[0x28] &= 0xfffff000;
        }
        voiceData += 0x30;
    } while (voiceData < (int*)(DAT_8032f444 + 0xc00));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TenutoOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    ((unsigned int*)track)[0x41] |= 0x00200000;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TenutoOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    ((unsigned int*)track)[0x41] &= ~0x00200000;
}

/*
 * --INFO--
 * PAL Address: 0x801C8AEC
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_Default(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* voice;
    int* trackData = (int*)track;

    trackData[0x35] = -1;
    trackData[0x36] = -1;
    memset(trackData + 0x35, 0xffffffff, 0xc);

    voice = (int*)DAT_8032f444;
    do {
        if ((voice[0] == (int)trackData) && (voice[1] != 0)) {
            memcpy(voice + 0x14, (void*)(voice[1] + 0x50), 0xc);
            voice[0x24] |= 0x3c0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xc00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8B8C
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_AL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    u8* sequencePos;
    u8 value;
    int* voice;

    sequencePos = *(u8**)track;
    *(u8**)track = sequencePos + 1;
    value = *sequencePos;
    *((u8*)track + 0xDC) = value;

    voice = (int*)DAT_8032f444;
    do {
        if ((RedTrackDATA*)*voice == track) {
            *((u8*)voice + 0x58) = value;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8BF4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_AR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int trackData;
    int* voice;
    int delta;

    trackData = (int)track;
    delta = DeltaTimeSumup((unsigned char**)trackData);
    *(unsigned short*)(trackData + 0xD4) = delta;

    voice = (int*)DAT_8032f444;
    do {
        if (*voice == trackData) {
            *(unsigned short*)(voice + 0x14) = delta;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8C70
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_DL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    u8* sequencePos;
    u8 value;
    int* voice;

    sequencePos = *(u8**)track;
    *(u8**)track = sequencePos + 1;
    value = *sequencePos;
    *((u8*)track + 0xDD) = value;

    voice = (int*)DAT_8032f444;
    do {
        if ((RedTrackDATA*)*voice == track) {
            *((u8*)voice + 0x59) = value;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8CD8
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_DR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int trackData;
    int* voice;
    int delta;

    trackData = (int)track;
    delta = DeltaTimeSumup((unsigned char**)trackData);
    *(unsigned short*)(trackData + 0xD6) = delta;

    voice = (int*)DAT_8032f444;
    do {
        if (*voice == trackData) {
            *(unsigned short*)((int)voice + 0x52) = delta;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8D54
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_SL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    u8* sequencePos;
    u8 value;
    int* voice;

    sequencePos = *(u8**)track;
    *(u8**)track = sequencePos + 1;
    value = *sequencePos;
    *((u8*)track + 0xDE) = value;

    voice = (int*)DAT_8032f444;
    do {
        if ((RedTrackDATA*)*voice == track) {
            *((u8*)voice + 0x5A) = value;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8DBC
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_SR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int trackData;
    int* voice;
    int delta;

    trackData = (int)track;
    delta = DeltaTimeSumup((unsigned char**)trackData);
    *(unsigned short*)(trackData + 0xD8) = delta;

    voice = (int*)DAT_8032f444;
    do {
        if (*voice == trackData) {
            *(unsigned short*)(voice + 0x15) = delta;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8E38
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_RL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    u8* sequencePos;
    u8 value;
    int* voice;

    sequencePos = *(u8**)track;
    *(u8**)track = sequencePos + 1;
    value = *sequencePos;
    *((u8*)track + 0xDF) = value;

    voice = (int*)DAT_8032f444;
    do {
        if ((RedTrackDATA*)*voice == track) {
            *((u8*)voice + 0x5B) = value;
            voice[0x24] |= 0x3C0;
        }
        voice += 0x30;
    } while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8EA0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ADSR_RR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int trackData;
	int* voice;
	int delta;

	trackData = (int)track;
	delta = DeltaTimeSumup((unsigned char**)trackData);
	*(unsigned short*)(trackData + 0xDA) = delta;

	voice = (int*)DAT_8032f444;
	do {
		if (*voice == trackData) {
			*(unsigned short*)((int)voice + 0x56) = delta;
			voice[0x24] |= 0x3C0;
		}
		voice += 0x30;
	} while (voice < (int*)(DAT_8032f444 + 0xC00));
}

/*
 * --INFO--
 * PAL Address: 0x801C8F1C
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_SustainPedal(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned int* voice;
    int* trackData;

    trackData = (int*)track;
    if (*(char*)trackData[0] == '\0') {
        trackData[0x3f] &= 0xFFFFFFFB;
        voice = DAT_8032f444;
        do {
            if ((int*)voice[0] == trackData) {
                voice[0x25] &= 0xFFFFFFFB;
            }
            voice += 0x30;
        } while (voice < DAT_8032f444 + 0xc00);
    } else {
        trackData[0x3f] |= 4;
        voice = DAT_8032f444;
        do {
            if ((int*)voice[0] == trackData) {
                voice[0x25] |= 4;
            }
            voice += 0x30;
        } while (voice < DAT_8032f444 + 0xc00);
    }

    trackData[0] += 1;
    SetVoiceSwitch(track, trackData[0x3f]);
}

/*
 * --INFO--
 * PAL Address: 0x801C8FF0
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ChannelAlloc(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData;
    unsigned char* command;

    trackData = (int*)track;
    command = (unsigned char*)trackData[0];
    trackData[0] = (int)(command + 1);
    *(unsigned char*)((char*)control + 0x490) = *command;
}

/*
 * --INFO--
 * PAL Address: 0x801C9008
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ChannelPriority(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData;
    u8* command;

    trackData = (int*)track;
    command = (u8*)trackData[0];
    trackData[0] = (int)(command + 1);
    if (*command != 0) {
        *(u8*)((char*)trackData + 0x26) |= 8;
    } else {
        *(u8*)((char*)trackData + 0x26) &= 0xF7;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9050
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ChannelFix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData;
    u8* command;

    trackData = (int*)track;
    command = (u8*)trackData[0];
    trackData[0] = (int)(command + 1);
    if (*command != 0) {
        *(u8*)((char*)trackData + 0x26) |= 4;
    } else {
        *(u8*)((char*)trackData + 0x26) &= 0xFB;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c9098
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOn, RedTrackDATA* track)
{
    unsigned int depth;
    int value;
    unsigned int* entry;
    int* trackData = (int*)track;

    trackData[0x20] = (unsigned int)(*(unsigned char*)trackData[0]) << 0xc;
    if (*(char*)(trackData[0] + 1) == '\0') {
        depth = 0x100;
    } else {
        depth = (unsigned int)(*(unsigned char*)(trackData[0] + 1));
    }

    trackData[0x1e] = 0x100000 / depth;
    trackData[0x1d] = PTR_SineSwing__Fi_8021e9d0[*(unsigned char*)(trackData[0] + 2) & 0xf];
    *(short*)((int)trackData + 0x8e) = 0;
    *(short*)(trackData + 0x23) = 0;
    trackData[0] = trackData[0] + 3;

    entry = DAT_8032f444;
    do {
        if ((int*)*entry == trackData) {
            value = 0x100;
            *(short*)(entry + 10) = *(short*)(trackData + 0x24);
            if (trackData[0x1e] >> 0xc != 0) {
                value = 0x100 / (trackData[0x1e] >> 0xc);
            }
            if (*(short*)((int)trackData + 0x92) == 0) {
                value = 0;
            } else {
                value = (int)*(short*)((int)trackData + 0x92) * value * 4;
            }
            entry[8] = value;
            entry[9] = 0;
            entry[7] = 0;
        }
        entry = entry + 0x30;
    } while (entry < DAT_8032f444 + 0xc00);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    *(u32*)((u8*)track + 0x74) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C91C4
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int* trackData = (int*)track;
	u8* command = (u8*)trackData[0];

	trackData[0] = (int)(command + 1);
	trackData[0x20] = (unsigned int)(*command) << 0xc;
	*(short*)((int)trackData + 0x8e) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C91E8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[1];
	int* trackData = (int*)track;

	delta[0] = DeltaTimeSumup((unsigned char**)trackData);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	trackData[0x21] = DataAddCompute(trackData + 0x20, *(u8*)trackData[0], delta);
	*(short*)((int)trackData + 0x8e) = (short)delta[0];
	trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9260
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    unsigned int rateDivisor;

    if (*(char*)trackData[0] == '\0') {
        rateDivisor = 0x100;
    } else {
        rateDivisor = (unsigned int)*(unsigned char*)trackData[0];
    }
    trackData[0x1e] = 0x100000 / rateDivisor;
    *(short*)(trackData + 0x23) = 0;
    trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C92C0
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int trackDelta[1];
    int* trackData = (int*)track;
    unsigned int rate;

    trackDelta[0] = DeltaTimeSumup((unsigned char**)trackData);
    if (trackDelta[0] == 0) {
        trackDelta[0] += 1;
    }

    if (*(char*)trackData[0] == '\0') {
        rate = 0x100;
    } else {
        rate = (unsigned int)*(unsigned char*)trackData[0];
    }

    trackData[0x1f] = DataAddCompute(trackData + 0x1e, 0x100 / rate, trackDelta);
    *(short*)(trackData + 0x23) = (short)trackDelta[0];
    trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9370
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u8* command = (u8*)((int*)track)[0];

	((int*)track)[0] = (int)(command + 1);
	((int*)track)[0x1d] = PTR_SineSwing__Fi_8021e9d0[*command & 0xf];
}

/*
 * --INFO--
 * PAL Address: 0x801C93B0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_VibrateDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int* trackData = (int*)track;

	*(unsigned short*)(trackData + 0x24) = (unsigned short)*(u8*)trackData[0];
	*(unsigned short*)((int)trackData + 0x92) = (unsigned short)*(u8*)(trackData[0] + 1);
	trackData[0] += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801c93d8
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	unsigned int rateDivisor;
	int value;
	int* trackData;
	unsigned int* voice;

	trackData = (int*)track;
	trackData[0x28] = (unsigned int)(*(unsigned char*)trackData[0]) << 0xc;
	if (*(char*)(trackData[0] + 1) == '\0') {
		rateDivisor = 0x100;
	} else {
		rateDivisor = (unsigned int)(*(unsigned char*)(trackData[0] + 1));
	}
	trackData[0x26] = 0x100000 / rateDivisor;
	trackData[0x25] = PTR_SineSwing__Fi_8021e9d0[*(unsigned char*)(trackData[0] + 2) & 0xf];
	*(short*)((int)trackData + 0xae) = 0;
	*(short*)(trackData + 0x2b) = 0;
	trackData[0] += 3;

	voice = DAT_8032f444;
	do {
		if ((int*)*voice == trackData) {
			value = 0x100;
			*(short*)(voice + 0xe) = *(short*)(trackData + 0x2c);
			if (trackData[0x26] >> 0xc != 0) {
				value = 0x100 / (trackData[0x26] >> 0xc);
			}
			if (*(short*)((int)trackData + 0xb2) == 0) {
				value = 0;
			} else {
				value = *(short*)((int)trackData + 0xb2) * value * 4;
			}
			voice[0xc] = value;
			voice[0xd] = 0;
			voice[0xb] = 0;
		}
		voice += 0x30;
	} while (voice < DAT_8032f444 + 0xc00);
}

/*
 * --INFO--
 * PAL Address: 0x801C94F8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	((int*)track)[0x25] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C9504
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int* trackData = (int*)track;
	u8* command = (u8*)trackData[0];

	trackData[0] = (int)(command + 1);
	trackData[0x28] = (u32)*command << 0xc;
	*(u16*)((u8*)trackData + 0xae) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C9528
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[1];
	int* trackData = (int*)track;

	delta[0] = DeltaTimeSumup((unsigned char**)trackData);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	trackData[0x29] = DataAddCompute(trackData + 0x28, *(u8*)trackData[0], delta);
	*(short*)((int)trackData + 0xae) = (short)delta[0];
	trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C95A0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u32 rate;
	int* trackData = (int*)track;

	if (*(char*)trackData[0] == '\0') {
		rate = 0x100;
	} else {
		rate = *(u8*)trackData[0];
	}
	trackData[0x26] = 0x100000 / rate;
	*(short*)(trackData + 0x2b) = 0;
	trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9600
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[1];
	u32 rate;
	int* trackData = (int*)track;

	delta[0] = DeltaTimeSumup((unsigned char**)trackData);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	if (*(char*)trackData[0] == '\0') {
		rate = 0x100;
	} else {
		rate = *(u8*)trackData[0];
	}
	trackData[0x27] = DataAddCompute(trackData + 0x26, 0x100 / rate, delta);
	*(short*)(trackData + 0x2b) = (short)delta[0];
	trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C96B0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u8* command = (u8*)((int*)track)[0];

	((int*)track)[0] = (int)(command + 1);
	((int*)track)[0x25] = PTR_SineSwing__Fi_8021e9d0[*command & 0xf];
}

/*
 * --INFO--
 * PAL Address: 0x801C96F0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_TremoloDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int* trackData = (int*)track;

	*(u16*)(trackData + 0x2c) = (u16)*(u8*)trackData[0];
	*(u16*)((u8*)trackData + 0xb2) = (u16)*(u8*)(trackData[0] + 1);
	trackData[0] += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C9718
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ShakeOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u32 rate;
	int* trackData = (int*)track;

	trackData[0x30] = *(u8*)trackData[0] << 0xc;
	if (*(char*)(trackData[0] + 1) == '\0') {
		rate = 0x100;
	} else {
		rate = *(u8*)(trackData[0] + 1);
	}
	trackData[0x2e] = 0x100000 / rate;
	trackData[0x2d] = PTR_SineSwing__Fi_8021e9d0[*(u8*)(trackData[0] + 2) & 0xf];
	*(u16*)((u8*)trackData + 0xd2) = 0;
	*(u16*)(trackData + 0x34) = 0;
	trackData[0x32] = 0;
	trackData[0x33] = 0;
	trackData[0] += 3;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    *(u32*)((u8*)track + 0xB4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C97C8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ShakeDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char* command = *(unsigned char**)track;
    *(unsigned char**)track = command + 1;
    ((int*)track)[0x30] = ((int)(*command)) << 0xc;
    *(unsigned short*)((unsigned char*)track + 0xd2) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C97EC
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ShakeDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[1];
	int* trackData = (int*)track;

	delta[0] = DeltaTimeSumup((unsigned char**)trackData);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	trackData[0x31] = DataAddCompute(trackData + 0x30, *(u8*)trackData[0], delta);
	*(short*)((int)trackData + 0xd2) = (short)delta[0];
	trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9864
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ShakeRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = reinterpret_cast<int*>(track);
    u32 rate;

    if (*reinterpret_cast<char*>(trackData[0]) == '\0') {
        rate = 0x100;
    } else {
        rate = *reinterpret_cast<unsigned char*>(trackData[0]);
    }

    trackData[0x2e] = 0x100000 / rate;
    *reinterpret_cast<short*>(trackData + 0x34) = 0;
    trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C98C4
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ShakeRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[1];
	u32 rate;
	int* trackData = (int*)track;

	delta[0] = DeltaTimeSumup((unsigned char**)trackData);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	if (*(char*)trackData[0] == '\0') {
		rate = 0x100;
	} else {
		rate = *(u8*)trackData[0];
	}
	trackData[0x2f] = DataAddCompute(trackData + 0x2e, 0x100 / rate, delta);
	*(short*)(trackData + 0x34) = (short)delta[0];
	trackData[0] += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9974
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ShakeType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u8* command = (u8*)((int*)track)[0];

	((int*)track)[0] = (int)(command + 1);
	((int*)track)[0x2d] = PTR_SineSwing__Fi_8021e9d0[*command & 0xf];
}

/*
 * --INFO--
 * PAL Address: 0x801C99B4
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_FineTuneAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u8* command = (u8*)((int*)track)[0];

	((int*)track)[0] = (int)(command + 1);
	((u8*)track)[0x148] = *command;
	DAT_8032f4b4 |= 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C99D8
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_FineTuneRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	s8* command = (s8*)((int*)track)[0];
	register s8 fineTune = ((s8*)track)[0x148];

	((int*)track)[0] = (int)(command + 1);
	register int fineTuneResult = fineTune + *command;
	((s8*)track)[0x148] = fineTuneResult;
	DAT_8032f4b4 |= 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9A04
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyTransposeAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	s8* command = (s8*)((int*)track)[0];

	((int*)track)[0] = (int)(command + 1);
	*(short*)((char*)track + 0x142) = (short)(*command << 8);
	DAT_8032f4b4 |= 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9A30
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_KeyTransposeRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	s8* command = (s8*)((int*)track)[0];
	register short keyTranspose = *(short*)((char*)track + 0x142);

	((int*)track)[0] = (int)(command + 1);
	register int keyTransposeDelta = *command << 8;
	register int keyTransposeResult = keyTranspose + keyTransposeDelta;
	*(short*)((char*)track + 0x142) = keyTransposeResult;
	DAT_8032f4b4 |= 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9A64
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void _PitchBendCompute(RedTrackDATA* track, int bend)
{
    int* voiceData = (int*)DAT_8032f444;
    int* trackData = (int*)track;

    do {
        if (voiceData[0] == (int)trackData) {
            if (voiceData[1] != 0) {
                int pitch;
                if ((((unsigned char*)voiceData)[0x1a] & 3) == 0) {
                    pitch = voiceData[0x28] + *DAT_8032f420;
                } else {
                    pitch = voiceData[0x28] + trackData[0x17];
                }
                voiceData[0x26] = PitchCompute(pitch, *(short*)((char*)trackData + 0x142) + bend, ((int*)voiceData[1])[5],
                                               *(char*)((char*)trackData + 0x148));
                voiceData[0x2e] |= 1;
            }
        }
        voiceData += 0x30;
    } while (voiceData < (int*)(DAT_8032f444 + 0xc00));
}

/*
 * --INFO--
 * PAL Address: 0x801C9B3C
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PitchBend(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    int bend = (unsigned int)*(unsigned char*)trackData[0] + (unsigned int)*(unsigned char*)(trackData[0] + 1) * 0x80 + -0x2000;

    *(short*)(trackData + 0x50) = bend;
    bend = (short)bend;
    bend = (bend * *(char*)((char*)trackData + 0x14b)) >> 5;
    *(short*)((char*)trackData + 0x13e) = bend;
    trackData[0] += 2;
    _PitchBendCompute(track, *(short*)((char*)trackData + 0x13e));
}

/*
 * --INFO--
 * PAL Address: 0x801C9BC0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_PitchBendRange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    unsigned char* command = (unsigned char*)((int*)track)[0];
    signed char range;

    trackData[0] = (int)(command + 1);
    range = *(signed char*)command;
    *(char*)((char*)trackData + 0x14b) = range;
    range = *(char*)((char*)trackData + 0x14b);
    *(short*)((char*)trackData + 0x13e) = (*(short*)(trackData + 0x50) * range) >> 5;
    _PitchBendCompute(track, *(short*)((char*)trackData + 0x13e));
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801C9C30
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ReverbOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;

    trackData[0x3f] |= 0x3c00;
    SetVoiceSwitch(track, trackData[0x3f]);
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C9C7C
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ReverbOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;

    trackData[0x3f] &= 0xffffcfff;
    trackData[0x3f] |= 0xc00;
    SetVoiceSwitch(track, trackData[0x3f]);
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C9CD4
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_ReverbMix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    unsigned char value;

    trackData[0x3f] &= 0xFFFFC3FF;
    value = *(unsigned char*)trackData[0];

    if (value == 2) {
        trackData[0x3f] |= 0x1000;
        trackData[0x3f] |= 0x400;
    } else if ((value < 2) && (value != 0)) {
        trackData[0x3f] |= 0x1000;
    } else {
        trackData[0x3f] |= 0x400;
    }

    value = *(unsigned char*)(trackData[0] + 1);
    if (value == 2) {
        trackData[0x3f] |= 0x2000;
        trackData[0x3f] |= 0x800;
    } else if ((value < 2) && (value != 0)) {
        trackData[0x3f] |= 0x2000;
    } else {
        trackData[0x3f] |= 0x800;
    }
    trackData[0] += 2;
    SetVoiceSwitch(track, trackData[0x3f]);
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C9DBC
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_StepRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    char value;
    short step;
    char* command;
    int* trackData = (int*)track;

    command = (char*)trackData[0];
    trackData[0] = (int)(command + 1);
    value = *command;
    if (value == 0) {
        step = 0;
    } else {
        step = *(short*)(trackData + 0x4e) + (short)value;
    }
    *(short*)(trackData + 0x4e) = step;
    *(short*)((char*)trackData + 0x13a) = 0;

    if (*(short*)(trackData + 0x4e) < -9999) {
        *(short*)(trackData + 0x4e) = -9999;
    } else if (*(short*)(trackData + 0x4e) > 9999) {
        *(short*)(trackData + 0x4e) = 9999;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9E3C
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_StepRelative2(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned char value;
    short step;
    unsigned char* command;
    int* trackData = (int*)track;

    command = (unsigned char*)trackData[0];
    trackData[0] = (int)(command + 1);
    value = *command;
    *(short*)(trackData + 0x4e) = 0;

    if (value == 0) {
        step = 0;
    } else {
        step = *(short*)((char*)trackData + 0x13a) + (unsigned short)value;
    }
    *(short*)((char*)trackData + 0x13a) = step;

    if (*(short*)((char*)trackData + 0x13a) < -9999) {
        *(short*)((char*)trackData + 0x13a) = -9999;
    } else if (*(short*)((char*)trackData + 0x13a) > 9999) {
        *(short*)((char*)trackData + 0x13a) = 9999;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9EBC
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_FuzzyOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int* trackData = (int*)track;
    unsigned char* command = *(unsigned char**)track;
    unsigned int value = command[1];

    *(unsigned char**)track = command + 2;
    if (value == 0) {
        value = 0x100;
    } else {
        value += 1;
    }

    switch (*command) {
    case 3:
        trackData[0x3b] = value;
        trackData[0x3f] |= 0x20000;
        return;
    case 1:
        trackData[0x39] = value;
        trackData[0x3f] |= 0x8000;
        return;
    case 2:
        trackData[0x3a] = value;
        trackData[0x3f] |= 0x10000;
        return;
    case 4:
        trackData[0x3c] = value;
        trackData[0x3f] |= 0x40000;
        return;
    case 0:
    default:
        trackData[0x38] = value;
        trackData[0x3f] |= 0x4000;
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9FA0
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __MidiCtrl_FuzzyOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    char* command = *(char**)track;
    int* trackData = (int*)track;
    char mode;

    *(char**)track = command + 1;
    mode = *command;

    if (mode == 3) {
        trackData[0x3f] &= 0xFFFDFFFF;
    } else if (mode < 3) {
        if (mode == 1) {
            trackData[0x3f] &= 0xFFFF7FFF;
        } else if (mode != 0) {
            trackData[0x3f] &= 0xFFFEFFFF;
        } else {
            trackData[0x3f] &= 0xFFFFBFFF;
        }
    } else if (mode < 5) {
        trackData[0x3f] &= 0xFFFBFFFF;
    } else {
        trackData[0x3f] &= 0xFFFFBFFF;
    }
}
