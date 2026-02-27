#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"

extern unsigned int* DAT_8032f444;
extern unsigned int DAT_8032f4b4;
extern int DAT_8032f3f8;
extern void* DAT_8032f3f0;
extern int* DAT_8032f420;
extern int DAT_8032f424;
extern CRedEntry DAT_8032e154;
extern int lbl_8021EA10[];

extern "C" {
void* memmove(void*, const void*, unsigned long);
void* memset(void*, int, unsigned long);
}

/*
 * --INFO--
 * PAL Address: 0x801C7478
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int DataAddCompute(int* current, int target, int* delta)
{
    if (target == (*current >> 0xc)) {
        *delta = 0;
        return 0;
    }

    return ((target << 0xc) + 0x800 - *current) / *delta;
}

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
 * Address:	TODO
 * Size:	TODO
 */
void SineSwing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void TriangleSwing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SawSwing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DutySwing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RandomSwing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SineSwingR(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void TriangleSwingR(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DutySwingR(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SawSwingR(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RandomSwingR(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_NoSupport(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
                    ((void (*)(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*))lbl_8021EA10[*cmd])(
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
    int* trackData = (int*)track;

    *(short*)(trackData + 0x4f) = *(short*)(trackData + 0x4f) + 1;
    *(unsigned short*)(trackData + 0x4f) &= 3;

    trackData[*(short*)(trackData + 0x4f) + 2] = trackData[0];
    *(short*)((char*)trackData + *(short*)(trackData + 0x4f) * 2 + 0x130) = *(short*)(trackData + 0x51);
    *(short*)((char*)trackData + *(short*)(trackData + 0x4f) * 2 + 0x128) = 0;
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
    int* trackData = (int*)track;

    trackData[0] = trackData[*(short*)(trackData + 0x4f) + 2];
    *(short*)(trackData + 0x51) = *(short*)((char*)trackData + *(short*)(trackData + 0x4f) * 2 + 0x130);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TempoDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TempoChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
    unsigned int delta[2];
    int* trackData = (int*)track;
    char* command = (char*)trackData[0];
    char mode;

    if (*command == 0) {
        delta[0] = 0x100;
    } else {
        delta[0] = (unsigned char)*command;
    }

    trackData[0] = (int)(command + 1);
    mode = *command;
    if (mode != 0) {
        mode = -1;
    }
    trackData[0x1b] = DataAddCompute(trackData + 0x1a, mode, (int*)delta);
    trackData[0x1c] = delta[0];
    trackData[0] += 2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TimeSignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeySignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PhraseSignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOnSame(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOnNoteVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOnNote(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOnVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOffSame(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOffNoteVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOffNote(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyOffVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_WaveWithBank(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VolumeDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VolumeChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ExpressionDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ExpressionChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PanDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PanChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PortamentOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PortamentOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_SlurOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_SlurOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
void __MidiCtrl_TenutoOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TenutoOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_Default(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_AL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_AR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_DL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_DR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_SL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_SR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_RL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ADSR_RR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ChannelAlloc(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ChannelPriority(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ChannelFix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
	int rate;
	void* entry;
	
	// Set vibrato depth from first parameter byte (12-bit shift)
	((int*)track)[0x20] = (unsigned int)(*(unsigned char*)((int*)track)[0]) << 0xc;
	
	// Set vibrato rate from second parameter byte
	if (*(char*)(((int*)track)[0] + 1) == '\0') {
		depth = 0x100;
	} else {
		depth = (unsigned int)(*(unsigned char*)(((int*)track)[0] + 1));
	}
	((int*)track)[0x1e] = 0x100000 / depth;
	
	// Set vibrato type from third parameter byte (lower 4 bits) 
	// Note: This should reference a function pointer table, using placeholder for now
	((int*)track)[0x1d] = (int)SineSwing; // Simplified for compilation
	
	// Initialize vibrato state
	*(short*)((int)track + 0x8e) = 0;
	*(short*)(((int*)track) + 0x23) = 0;
	
	// Advance parameter pointer by 3 bytes
	((int*)track)[0] = ((int*)track)[0] + 3;
	
	// Apply to active sound entries
	entry = (void*)0x8032f444; // DAT_8032f444
	do {
		if ((RedTrackDATA*)*(int*)entry == track) {
			rate = 0x100;
			*(short*)((int)entry + 0x28) = *(short*)(((int*)track) + 0x24);
			
			if (((int*)track)[0x1e] >> 0xc != 0) {
				rate = 0x100 / (((int*)track)[0x1e] >> 0xc);
			}
			
			if (*(short*)((int)track + 0x92) == 0) {
				rate = 0;
			} else {
				rate = (int)*(short*)((int)track + 0x92) * rate * 4;
			}
			
			((int*)entry)[8] = rate;
			((int*)entry)[9] = 0;
			((int*)entry)[7] = 0;
		}
		entry = (void*)((int)entry + 0xc0);
	} while (entry < (void*)(0x8032f444 + 0xc00));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
    int trackDelta[3];
    int* trackData = (int*)track;
    unsigned int rate;

    trackDelta[0] = DeltaTimeSumup((unsigned char**)trackData);
    if (trackDelta[0] == 0) {
        trackDelta[0] = 1;
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
	trackData[0x25] = (int)SineSwing;
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_TremoloDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ShakeType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_FineTuneAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_FineTuneRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyTransposeAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_KeyTransposeRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
    unsigned char* command = (unsigned char*)((int*)track)[0];
    int* trackData = (int*)track;
    int bend = (unsigned int)command[0] + (unsigned int)command[1] * 0x80 - 0x2000;

    *(short*)(trackData + 0x50) = bend;
    *(short*)((char*)trackData + 0x13e) = (bend * *(char*)((char*)trackData + 0x14b)) >> 5;
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
    unsigned char* command = (unsigned char*)((int*)track)[0];
    int* trackData = (int*)track;

    trackData[0] = (int)(command + 1);
    *(char*)((char*)trackData + 0x14b) = *(char*)command;
    *(short*)((char*)trackData + 0x13e) = (*(short*)(trackData + 0x50) * *(char*)((char*)trackData + 0x14b)) >> 5;
    _PitchBendCompute(track, *(short*)((char*)trackData + 0x13e));
}

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
    unsigned char* command = (unsigned char*)((int*)track)[0];
    int* trackData = (int*)track;

    trackData[0x3f] &= 0xFFFFC3FF;

    if (command[0] == 1 || command[0] == 2) {
        trackData[0x3f] |= 0x1000;
    }
    if (command[0] == 0 || command[0] >= 2) {
        trackData[0x3f] |= 0x400;
    }

    if (command[1] == 1 || command[1] == 2) {
        trackData[0x3f] |= 0x2000;
    }
    if (command[1] == 0 || command[1] >= 2) {
        trackData[0x3f] |= 0x800;
    }

    trackData[0] += 2;
    SetVoiceSwitch(track, trackData[0x3f]);
    DAT_8032f4b4 |= 2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_StepRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_StepRelative2(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
    unsigned char* command = (unsigned char*)((int*)track)[0];
    int* trackData = (int*)track;
    int value;

    trackData[0] = (int)(command + 2);
    value = command[1] + 1;
    if (command[1] == 0) {
        value = 0x100;
    }

    if (command[0] == 1) {
        trackData[0x39] = value;
        trackData[0x3f] |= 0x8000;
    } else if (command[0] == 2) {
        trackData[0x3a] = value;
        trackData[0x3f] |= 0x10000;
    } else if (command[0] == 3) {
        trackData[0x3b] = value;
        trackData[0x3f] |= 0x20000;
    } else if (command[0] == 4) {
        trackData[0x3c] = value;
        trackData[0x3f] |= 0x40000;
    } else {
        trackData[0x38] = value;
        trackData[0x3f] |= 0x4000;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_FuzzyOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}
