#ifndef _FFCC_REDSOUND_REDEXECUTE_H
#define _FFCC_REDSOUND_REDEXECUTE_H

#include "types.h"

class AXFX_BUFFERUPDATE;
struct RedReverbDATA;
struct RedTrackDATA;
struct RedVoiceDATA;
struct RedWaveDATA;
struct RedNoteDATA;
struct RedSoundCONTROL;
struct RedKeyOnDATA;

u8 GetRandomData();
int PitchCompute(int, int, int, int);
void _ReverbNullCallback(AXFX_BUFFERUPDATE*, void*);
void ReverbAreaAlloc(unsigned long);
void ReverbAreaFree(void*);
void InitReverb();
void _SetReverbData(RedReverbDATA*, int*);
void _ClearReverb(int);
int* SetReverb(int, int, int*);

void EntryVoiceSearch(RedTrackDATA*);
void _VoiceEnvelopeCheck();
void SetVoiceVolumeMix(RedVoiceDATA*, int, int);
void _VolumeExecute(RedVoiceDATA*, int);
void _PitchExecute(RedVoiceDATA*);
void _WaveSplitSelect(RedWaveDATA*, RedNoteDATA*);
void _VoiceDataAsign(RedTrackDATA*, RedVoiceDATA*, RedNoteDATA*, int*);
void _VoiceDataSelect(RedTrackDATA*, RedNoteDATA*, int*);
void SetVoiceAccess(RedTrackDATA*, int);
void SetVoiceSwitch(RedTrackDATA*, int);

void _AdsrStart(RedVoiceDATA*);
void _AdsrDataCompute(RedVoiceDATA*);
void _AdsrDataExecute(RedVoiceDATA*);
void _VoiceDropedCallback(void*);
void EnvelopeKeyExecute();
void _KeyOnControl();
void _ExecuteExtraData();

void _MusicTrackDataExecute(RedTrackDATA*, int);
void _MidiTrackExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _MusicMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _MusicNoteExecute();
void _MusicMidiNoteSkipExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _SkipMusicEntry();
void MusicSkipFunction();

void _SeTrackDataExecute(RedTrackDATA*, int);
void _SeMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*, int, int);

void MainControl(int);

#endif // _FFCC_REDSOUND_REDEXECUTE_H
