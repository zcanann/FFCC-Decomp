#ifndef _FFCC_REDSOUND_REDMIDICTRL_H
#define _FFCC_REDSOUND_REDMIDICTRL_H

struct RedKeyOnDATA;
struct RedSoundCONTROL;

struct RedTrackDATA {
	unsigned char* m_command;
	unsigned char m_pad04[0x18 - 0x04];
	int m_waveBankData;
	int m_waveData;
	unsigned char m_pad20[0x28 - 0x20];
	int m_volume;
	int m_volumeAdd;
	int m_volumeDelta;
	int m_expression;
	int m_expressionAdd;
	int m_expressionDelta;
	int m_pan;
	int m_panAdd;
	int m_panDelta;
	unsigned char m_pad4C[0x74 - 0x4C];
	int m_vibrateFunc;
	int m_vibrateRate;
	int m_vibrateRateAdd;
	int m_vibrateDepth;
	int m_vibrateDepthAdd;
	unsigned char m_pad88[0x8C - 0x88];
	unsigned short m_vibrateRateDelta;
	unsigned short m_vibrateDepthDelta;
	unsigned short m_vibrateDelay;
	unsigned short m_vibrateDelayDepth;
	int m_tremoloFunc;
	int m_tremoloRate;
	int m_tremoloRateAdd;
	int m_tremoloDepth;
	int m_tremoloDepthAdd;
	unsigned char m_padA8[0xAC - 0xA8];
	unsigned short m_tremoloRateDelta;
	unsigned short m_tremoloDepthDelta;
	unsigned short m_tremoloDelay;
	unsigned short m_tremoloDelayDepth;
	int m_shakeFunc;
	int m_shakeRate;
	int m_shakeRateAdd;
	int m_shakeDepth;
	int m_shakeDepthAdd;
	int m_shakeOutput;
	int m_shakePan;
	unsigned short m_shakeRateDelta;
	unsigned short m_shakeDepthDelta;
	unsigned short m_adsrAR;
	unsigned short m_adsrDR;
	unsigned short m_adsrSR;
	unsigned short m_adsrRR;
	unsigned char m_adsrAL;
	unsigned char m_adsrDL;
	unsigned char m_adsrSL;
	unsigned char m_adsrRL;
	unsigned char m_padE0[0xFC - 0xE0];
	int m_voiceSwitch;
	unsigned char m_pad100[0x104 - 0x100];
	unsigned int m_flags;
	unsigned char m_pad108[0x110 - 0x108];
	int m_sweepDelta;
	int m_sweepAdd;
	int m_portamentTime;
	int m_waveBase;
	int m_portamentPitch;
	int m_waveNo;
	unsigned char m_pad128[0x138 - 0x128];
	short m_step;
	short m_step2;
	unsigned char m_pad13C[0x13E - 0x13C];
	short m_pitchBend;
	short m_pitchBendRaw;
	short m_keyTranspose;
	unsigned char m_pad144[0x148 - 0x144];
	signed char m_fineTune;
	unsigned char m_pad149[0x14B - 0x149];
	signed char m_pitchBendRange;
	unsigned char m_pad14C[0x14D - 0x14C];
	unsigned char m_waveBankNo;
	unsigned char m_pad14E[0x154 - 0x14E];
};

typedef void (*RedMidiControlFunc)(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
typedef int (*RedSwingFunc)(int);

int DataAddCompute(int*, int, int*);
void KeyOnReserveClear(RedKeyOnDATA*, RedTrackDATA*);
void KeyOnReserve(RedKeyOnDATA*, RedTrackDATA*);
void KeyOffSet(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*);
int SineSwing(int);
int TriangleSwing(int);
int SawSwing(int);
int DutySwing(int);
int RandomSwing(int);
int SineSwingR(int);
int TriangleSwingR(int);
int DutySwingR(int);
int SawSwingR(int);
int RandomSwingR(int);

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

extern RedMidiControlFunc p_MidiControl_Function[];
extern RedSwingFunc SwingEntryFunction[];

#endif // _FFCC_REDSOUND_REDMIDICTRL_H
