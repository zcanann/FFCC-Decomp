#include "ffcc/RedSound/RedExecute.h"
#include "types.h"
#include <string.h>

/*
 * --INFO--
 * PAL Address: 0x801c2fc4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
u8 GetRandomData()
{
    extern u8 DAT_8032f4a8;
    extern u8 DAT_8021dcce[];
    
    u8 uVar1 = (u8)DAT_8032f4a8;
    DAT_8032f4a8 = DAT_8032f4a8 + 1;
    return DAT_8021dcce[uVar1];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void PitchCompute(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c30fc
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _ReverbNullCallback(AXFX_BUFFERUPDATE* param_1, void*)
{
    u32* data = (u32*)param_1;
    memset((void*)data[0], 0, 0x280);
    memset((void*)data[1], 0, 0x280);
    memset((void*)data[2], 0, 0x280);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ReverbAreaAlloc(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c31ac
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ReverbAreaFree(void* param_1)
{
    extern void RedDelete(void*);
    RedDelete(param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitReverb()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetReverbData(RedReverbDATA*, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearReverb(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetReverb(int, int, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void EntryVoiceSearch(RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _VoiceEnvelopeCheck()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetVoiceVolumeMix(RedVoiceDATA*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _VolumeExecute(RedVoiceDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _PitchExecute(RedVoiceDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _WaveSplitSelect(RedWaveDATA*, RedNoteDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _VoiceDataAsign(RedTrackDATA*, RedVoiceDATA*, RedNoteDATA*, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _VoiceDataSelect(RedTrackDATA*, RedNoteDATA*, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetVoiceAccess(RedTrackDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetVoiceSwitch(RedTrackDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _AdsrStart(RedVoiceDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _AdsrDataCompute(RedVoiceDATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _AdsrDataExecute(RedVoiceDATA*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c4fd4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _VoiceDropedCallback(void* param_1)
{
    extern u32* DAT_8032f444;
    
    u32* puVar1;
    int iParam1 = (int)param_1;
    
    puVar1 = DAT_8032f444;
    do {
        if ((puVar1[5] != 0) && ((int)puVar1[5] == iParam1)) {
            puVar1[0x23] = 0;
            *puVar1 = 0;
            puVar1[5] = 0;
        }
        puVar1 = puVar1 + 0x30;
    } while (puVar1 < DAT_8032f444 + 0xc00);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void EnvelopeKeyExecute()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _KeyOnControl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ExecuteExtraData()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicTrackDataExecute(RedTrackDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MidiTrackExecute(RedSoundCONTROL*, RedKeyOnDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicNoteExecute()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicMidiNoteSkipExecute(RedSoundCONTROL*, RedKeyOnDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SkipMusicEntry()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MusicSkipFunction()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeTrackDataExecute(RedTrackDATA*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MainControl(int)
{
	// TODO
}
