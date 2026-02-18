#include "ffcc/RedSound/RedMidiCtrl.h"

extern unsigned int* DAT_8032f444;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DataAddCompute(int*, int, int*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void KeyOnReserve(RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void KeyOffSet(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_Stop(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_Sleep(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_WholeLoopStart(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_WholeLoopEnd(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_LoopStart(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_LoopEnd(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_LoopRepeat(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ReverbDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ReverbDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_Wave(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_Sweep(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_SustainPedal(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_VibrateRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void _PitchBendCompute(RedTrackDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PitchBend(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_PitchBendRange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ReverbOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ReverbOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_ReverbMix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void __MidiCtrl_FuzzyOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
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
