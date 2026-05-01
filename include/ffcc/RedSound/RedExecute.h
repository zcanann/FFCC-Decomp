#ifndef _FFCC_REDSOUND_REDEXECUTE_H
#define _FFCC_REDSOUND_REDEXECUTE_H

#include "types.h"

class AXFX_BUFFERUPDATE;
struct RedReverbDATA;
struct RedTrackDATA;
struct RedWaveDATA;
struct RedNoteDATA;
struct RedSoundCONTROL;
struct RedKeyOnDATA;

struct RedVoiceDATA {
	RedTrackDATA* m_track;
	RedNoteDATA* m_note;
	RedWaveDATA* m_waveData;
	void* m_axVoice;
	unsigned char m_pad10[0x1A - 0x10];
	unsigned char m_stateFlags;
	unsigned char m_pad1B[0x8C - 0x1B];
	int m_active;
	unsigned int m_flags;
	unsigned int m_voiceSwitch;
	int m_pitch;
	int m_targetPitch;
	int m_basePitch;
	unsigned char m_padA4[0xB0 - 0xA4];
	int m_envelopeLevel;
	unsigned char m_padB4[0xB8 - 0xB4];
	unsigned int m_updateFlags;
	unsigned char m_padBC[0xC0 - 0xBC];
};

u8 GetRandomData();
int PitchCompute(int, int, int, int);
void _ReverbNullCallback(AXFX_BUFFERUPDATE*, void*);
void* ReverbAreaAlloc(unsigned long);
void ReverbAreaFree(void*);
void InitReverb();
void _SetReverbData(RedReverbDATA*, int*);
void _ClearReverb(int);
int* SetReverb(int, int, int*);

RedVoiceDATA* EntryVoiceSearch(RedTrackDATA*);
void _VoiceEnvelopeCheck();
void SetVoiceVolumeMix(RedVoiceDATA*, int, int);
void _VolumeExecute(RedVoiceDATA*, int);
void _PitchExecute(RedVoiceDATA*);
RedWaveDATA* _WaveSplitSelect(RedWaveDATA*, RedNoteDATA*);
void _VoiceDataAsign(RedTrackDATA*, RedVoiceDATA*, RedNoteDATA*, int*);
RedVoiceDATA* _VoiceDataSelect(RedTrackDATA*, RedNoteDATA*, int*);
void SetVoiceAccess(RedTrackDATA*, int);
void SetVoiceSwitch(RedTrackDATA*, int);

void _AdsrStart(RedVoiceDATA*);
void _AdsrDataCompute(RedVoiceDATA*);
u32 _AdsrDataExecute(RedVoiceDATA*);
void _VoiceDropedCallback(void*);
void EnvelopeKeyExecute();
void _KeyOnControl();
void _ExecuteExtraData();

void _MusicTrackDataExecute(RedTrackDATA*, int);
void _MidiTrackExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
int _MusicMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _MusicNoteExecute();
int _MusicMidiNoteSkipExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _SkipMusicEntry();
void MusicSkipFunction();

void _SeTrackDataExecute(RedTrackDATA*, int);
int _SeMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*, int, int);

void MainControl(int);

#endif // _FFCC_REDSOUND_REDEXECUTE_H
