#ifndef _FFCC_REDSOUND_REDMIDICTRL_H
#define _FFCC_REDSOUND_REDMIDICTRL_H

struct RedKeyOnDATA;
struct RedTrackDATA;
struct RedSoundCONTROL;

void DataAddCompute(int*, int, int*);
void KeyOnReserveClear(RedKeyOnDATA*, RedTrackDATA*);
void KeyOnReserve(RedKeyOnDATA*, RedTrackDATA*);
void KeyOffSet(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void SineSwing(int);
void TriangleSwing(int);
void SawSwing(int);
void DutySwing(int);
void RandomSwing(int);
void SineSwingR(int);
void TriangleSwingR(int);
void DutySwingR(int);
void SawSwingR(int);
void RandomSwingR(int);

void __MidiCtrl_NoSupport(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_Pass(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_Stop(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_Sleep(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_WholeLoopStart(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_WholeLoopEnd(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_LoopStart(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_LoopEnd(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_LoopRepeat(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TempoDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TempoChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ReverbDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ReverbDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TimeSignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeySignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_PhraseSignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_KeyOnSame(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyOnNoteVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyOnNote(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyOnVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_KeyOffSame(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyOffNoteVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyOffNote(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyOffVelocity(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_Wave(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_WaveWithBank(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_VolumeDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VolumeChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ExpressionDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ExpressionChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_PanDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_PanChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_PortamentOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_PortamentOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_SlurOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_SlurOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_Sweep(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TenutoOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TenutoOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_ADSR_Default(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_AL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_AR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_DL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_DR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_SL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_SR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_RL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ADSR_RR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_SustainPedal(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ChannelAlloc(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ChannelPriority(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ChannelFix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_VibrateOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_VibrateDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_TremoloOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_TremoloDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_ShakeOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ShakeOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ShakeDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ShakeDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ShakeRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ShakeRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ShakeType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_FineTuneAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_FineTuneRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyTransposeAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_KeyTransposeRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void _PitchBendCompute(RedTrackDATA*, int);
void __MidiCtrl_PitchBend(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_PitchBendRange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_ReverbOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ReverbOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_ReverbMix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_StepRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_StepRelative2(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

void __MidiCtrl_FuzzyOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
void __MidiCtrl_FuzzyOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);

#endif // _FFCC_REDSOUND_REDMIDICTRL_H
