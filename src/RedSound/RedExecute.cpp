#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
#include "types.h"
#include "dolphin/ax.h"
#include "dolphin/axfx.h"
#include <string.h>

extern u32* DAT_8032f444;
extern unsigned int DAT_8032ec30;
extern int DAT_8032f4ac;
extern u32* DAT_8032f4b0;

struct RedReverbDATA {
    void (*callback)(void*, void*);
    void* context;
    int kind;
};

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
int PitchCompute(int, int, int, int)
{
	// TODO
	return 0;
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
 * PAL Address: 0x801c31d4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitReverb()
{
    DAT_8032f4ac = RedNew(0x18);
    memset((void*)DAT_8032f4ac, 0, 0x18);
    DAT_8032f4b0 = (u32*)RedNew(4);
}

/*
 * --INFO--
 * PAL Address: 0x801c3218
 * PAL Size: 1040b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SetReverbData(RedReverbDATA* reverb, int* params)
{
    int result = 0;
    switch (reverb->kind) {
    case 1: {
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)reverb->context;
        std->tempDisableFX = 0;
        std->preDelay = (float)params[0] / 100.0f;
        std->time = (float)params[1] / 100.0f;
        std->coloration = (float)params[2] / 10000.0f;
        std->damping = (float)params[3] / 10000.0f;
        std->mix = (float)params[4] / 10000.0f;
        result = AXFXReverbStdSettings(std);
        break;
    }
    case 2: {
        AXFX_REVERBHI* hi = (AXFX_REVERBHI*)reverb->context;
        hi->tempDisableFX = 0;
        hi->preDelay = (float)params[0] / 100.0f;
        hi->time = (float)params[1] / 100.0f;
        hi->coloration = (float)params[2] / 10000.0f;
        hi->damping = (float)params[3] / 10000.0f;
        hi->mix = (float)params[4] / 10000.0f;
        hi->crosstalk = (float)params[5] / 10000.0f;
        result = AXFXReverbHiSettings(hi);
        break;
    }
    case 3: {
        AXFX_DELAY* delay = (AXFX_DELAY*)reverb->context;
        delay->delay[0] = (u32)params[0];
        delay->delay[1] = (u32)params[0];
        delay->delay[2] = (u32)params[0];
        delay->feedback[0] = (u32)params[1];
        delay->feedback[1] = (u32)params[1];
        delay->feedback[2] = (u32)params[1];
        delay->output[0] = (u32)params[2];
        delay->output[1] = (u32)params[2];
        delay->output[2] = (u32)params[2];
        result = AXFXDelaySettings(delay);
        break;
    }
    case 4: {
        AXFX_CHORUS* chorus = (AXFX_CHORUS*)reverb->context;
        chorus->baseDelay = (u32)params[0];
        chorus->variation = (u32)params[1];
        chorus->period = (u32)params[2];
        result = AXFXChorusSettings(chorus);
        break;
    }
    case 5: {
        AXFX_REVERBHI_DPL2* hiDpl2 = (AXFX_REVERBHI_DPL2*)reverb->context;
        hiDpl2->tempDisableFX = 0;
        hiDpl2->preDelay = (float)params[0] / 100.0f;
        hiDpl2->time = (float)params[1] / 100.0f;
        hiDpl2->coloration = (float)params[2] / 10000.0f;
        hiDpl2->damping = (float)params[3] / 10000.0f;
        hiDpl2->mix = (float)params[4] / 10000.0f;
        result = AXFXReverbHiSettingsDpl2(hiDpl2);
        break;
    }
    }

    if (result != 1) {
        DAT_8032f4b0[0] = 0;
        DAT_8032f4b0[1] = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c3628
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _ClearReverb(int bank)
{
    RedReverbDATA* reverb = (RedReverbDATA*)(DAT_8032f4ac + (bank & 1) * 0xC);
    if (reverb->callback == 0) {
        return;
    }

    if (bank == 0) {
        AXRegisterAuxACallback((void (*)(void*, void*))_ReverbNullCallback, 0);
    } else {
        AXRegisterAuxBCallback((void (*)(void*, void*))_ReverbNullCallback, 0);
    }

    switch (reverb->kind) {
    case 1:
        AXFXReverbStdShutdown((AXFX_REVERBSTD*)reverb->context);
        break;
    case 2:
        AXFXReverbHiShutdown((AXFX_REVERBHI*)reverb->context);
        break;
    case 3:
        AXFXDelayShutdown((AXFX_DELAY*)reverb->context);
        break;
    case 4:
        AXFXChorusShutdown((AXFX_CHORUS*)reverb->context);
        break;
    case 5:
        AXFXReverbHiShutdownDpl2((AXFX_REVERBHI_DPL2*)reverb->context);
        break;
    }

    reverb->callback = 0;
    RedDelete(reverb->context);
}

/*
 * --INFO--
 * PAL Address: 0x801c3718
 * PAL Size: 1324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int* SetReverb(int bank, int kind, int* params)
{
    RedReverbDATA* reverb;
    int result;

    DAT_8032f4b0[0] = 0;
    DAT_8032f4b0[1] = 0;

    if (kind == 0) {
        _ClearReverb(bank);
        return (int*)DAT_8032f4b0;
    }

    if (kind > 5) {
        return 0;
    }

    reverb = (RedReverbDATA*)(DAT_8032f4ac + (bank & 1) * 0xC);
    if ((reverb->callback != nullptr) && (reverb->kind == kind)) {
        _SetReverbData(reverb, params);
        return (int*)DAT_8032f4b0;
    }

    _ClearReverb(bank);
    if (kind == 5) {
        _ClearReverb(1);
    }

    reverb->kind = kind;
    result = 0;
    switch (kind) {
    case 1: {
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)RedNew(sizeof(AXFX_REVERBSTD));
        reverb->context = std;
        reverb->callback = (void (*)(void*, void*))AXFXReverbStdCallback;
        std->tempDisableFX = 0;
        std->preDelay = (float)params[0] / 100.0f;
        std->time = (float)params[1] / 100.0f;
        std->coloration = (float)params[2] / 10000.0f;
        std->damping = (float)params[3] / 10000.0f;
        std->mix = (float)params[4] / 10000.0f;
        result = AXFXReverbStdInit(std);
        break;
    }
    case 2: {
        AXFX_REVERBHI* hi = (AXFX_REVERBHI*)RedNew(sizeof(AXFX_REVERBHI));
        reverb->context = hi;
        reverb->callback = (void (*)(void*, void*))AXFXReverbHiCallback;
        hi->tempDisableFX = 0;
        hi->preDelay = (float)params[0] / 100.0f;
        hi->time = (float)params[1] / 100.0f;
        hi->coloration = (float)params[2] / 10000.0f;
        hi->damping = (float)params[3] / 10000.0f;
        hi->mix = (float)params[4] / 10000.0f;
        hi->crosstalk = (float)params[5] / 10000.0f;
        result = AXFXReverbHiInit(hi);
        break;
    }
    case 3: {
        AXFX_DELAY* delay = (AXFX_DELAY*)RedNew(sizeof(AXFX_DELAY));
        reverb->context = delay;
        reverb->callback = (void (*)(void*, void*))AXFXDelayCallback;
        delay->delay[0] = (u32)params[0];
        delay->delay[1] = (u32)params[0];
        delay->delay[2] = (u32)params[0];
        delay->feedback[0] = (u32)params[1];
        delay->feedback[1] = (u32)params[1];
        delay->feedback[2] = (u32)params[1];
        delay->output[0] = (u32)params[2];
        delay->output[1] = (u32)params[2];
        delay->output[2] = (u32)params[2];
        result = AXFXDelayInit(delay);
        break;
    }
    case 4: {
        AXFX_CHORUS* chorus = (AXFX_CHORUS*)RedNew(sizeof(AXFX_CHORUS));
        reverb->context = chorus;
        reverb->callback = (void (*)(void*, void*))AXFXChorusCallback;
        chorus->baseDelay = (u32)params[0];
        chorus->variation = (u32)params[1];
        chorus->period = (u32)params[2];
        result = AXFXChorusInit(chorus);
        break;
    }
    case 5: {
        AXFX_REVERBHI_DPL2* hiDpl2 = (AXFX_REVERBHI_DPL2*)RedNew(sizeof(AXFX_REVERBHI_DPL2));
        reverb->context = hiDpl2;
        reverb->callback = (void (*)(void*, void*))AXFXReverbHiCallbackDpl2;
        hiDpl2->tempDisableFX = 0;
        hiDpl2->preDelay = (float)params[0] / 100.0f;
        hiDpl2->time = (float)params[1] / 100.0f;
        hiDpl2->coloration = (float)params[2] / 10000.0f;
        hiDpl2->damping = (float)params[3] / 10000.0f;
        hiDpl2->mix = (float)params[4] / 10000.0f;
        result = AXFXReverbHiInitDpl2(hiDpl2);
        break;
    }
    }

    if (result == 1) {
        if (bank == 0) {
            AXRegisterAuxACallback(reverb->callback, reverb->context);
        }
        else {
            AXRegisterAuxBCallback(reverb->callback, reverb->context);
        }
    }
    else {
        DAT_8032f4b0[0] = 0;
        DAT_8032f4b0[1] = 0;
    }

    return (int*)DAT_8032f4b0;
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
 * PAL Address: 0x801c6ab4
 * PAL Size: 1416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SeTrackDataExecute(RedTrackDATA* track, int frames)
{
	int* trackData = (int*)track;
	unsigned char* trackBytes = (unsigned char*)trackData;
	int voiceBase;
	int step;
	short* trackShorts = (short*)trackData;

	if ((trackBytes[0x26] & 2) != 0) {
		return;
	}

	voiceBase = (int)((unsigned char*)DAT_8032f444 + (s8)trackBytes[0x14E] * 0xC0);
	if (0 < frames) {
		trackData[0x43] += frames;
	}

	if (trackData[0x0C] != 0) {
		step = frames;
		if (trackData[0x0C] <= frames) {
			step = trackData[0x0C];
		}
		trackData[0x0C] -= step;
		trackData[0x0A] += trackData[0x0B] * step;
		*(unsigned int*)(voiceBase + 0xB8) |= 2;
	}

	if (trackData[0x0F] != 0) {
		step = frames;
		if (trackData[0x0F] <= frames) {
			step = trackData[0x0F];
		}
		trackData[0x0F] -= step;
		trackData[0x0D] += trackData[0x0E] * step;
		*(unsigned int*)(voiceBase + 0xB8) |= 2;
	}

	if (trackData[0x12] != 0) {
		step = frames;
		if (trackData[0x12] <= frames) {
			step = trackData[0x12];
		}
		trackData[0x12] -= step;
		trackData[0x10] += trackData[0x11] * step;
		*(unsigned int*)(voiceBase + 0xB8) |= 2;
	}

	if (trackData[0x1C] != 0) {
		step = frames;
		if (trackData[0x1C] <= frames) {
			step = trackData[0x1C];
		}
		trackData[0x1C] -= step;
		trackData[0x1A] += trackData[0x1B] * step;
		*(unsigned int*)(voiceBase + 0xB8) |= 2;
	}

	if (trackData[0x15] != 0) {
		step = frames;
		if (trackData[0x15] <= frames) {
			step = trackData[0x15];
		}
		trackData[0x15] -= step;
		if ((trackData[0x15] == 0) && (trackData[0x16] == 1)) {
			trackData[0] = (int)&DAT_8032ec30;
			trackData[0x42] = 1;
		}
		trackData[0x13] += trackData[0x14] * step;
		*(unsigned int*)(voiceBase + 0xB8) |= 2;
	}

	if (trackData[0x19] != 0) {
		step = frames;
		if (trackData[0x19] <= frames) {
			step = trackData[0x19];
		}
		trackData[0x19] -= step;
		trackData[0x17] += trackData[0x18] * step;
		*(unsigned int*)(voiceBase + 0xB8) |= 1;
	}

	if (trackData[0x44] != 0) {
		step = frames;
		if (trackData[0x44] <= frames) {
			step = trackData[0x44];
		}
		trackData[0x44] -= step;
		trackData[0x48] += step * trackData[0x45];
		*(unsigned int*)(voiceBase + 0xB8) |= 1;
		*(int*)(voiceBase + 0xA0) += step * trackData[0x45];
	}

	if (((*(unsigned int*)(voiceBase + 0xB8) & 1) != 0) && (*(int*)(voiceBase + 4) != 0)) {
		*(int*)(voiceBase + 0x98) = PitchCompute(
			*(int*)(voiceBase + 0xA0) + trackData[0x17], (int)trackShorts[0xA1] + (int)trackShorts[0x9F],
			*(int*)(*(int*)(voiceBase + 4) + 0x14), (int)(s8)trackBytes[0x148]);
	}

	if (trackData[0x1D] != 0) {
		if (trackShorts[0x46] != 0) {
			step = frames;
			if (trackShorts[0x46] <= frames) {
				step = trackShorts[0x46];
			}
			trackShorts[0x46] = trackShorts[0x46] - (short)step;
			trackData[0x1E] += trackData[0x1F] * step;
		}
		if (*(short*)(trackBytes + 0x8E) != 0) {
			step = frames;
			if (*(short*)(trackBytes + 0x8E) <= frames) {
				step = *(short*)(trackBytes + 0x8E);
			}
			*(short*)(trackBytes + 0x8E) = *(short*)(trackBytes + 0x8E) - (short)step;
			trackData[0x20] += trackData[0x21] * step;
		}
	}

	if (trackData[0x25] != 0) {
		if (trackShorts[0x56] != 0) {
			step = frames;
			if (trackShorts[0x56] <= frames) {
				step = trackShorts[0x56];
			}
			trackShorts[0x56] = trackShorts[0x56] - (short)step;
			trackData[0x26] += trackData[0x27] * step;
		}
		if (*(short*)(trackBytes + 0xAE) != 0) {
			step = frames;
			if (*(short*)(trackBytes + 0xAE) <= frames) {
				step = *(short*)(trackBytes + 0xAE);
			}
			*(short*)(trackBytes + 0xAE) = *(short*)(trackBytes + 0xAE) - (short)step;
			trackData[0x28] += trackData[0x29] * step;
		}
	}

	if (trackData[0x2D] != 0) {
		if (trackShorts[0x68] != 0) {
			step = frames;
			if (trackShorts[0x68] <= frames) {
				step = trackShorts[0x68];
			}
			trackShorts[0x68] = trackShorts[0x68] - (short)step;
			trackData[0x2E] += trackData[0x2F] * step;
		}
		if (*(short*)(trackBytes + 0xD2) != 0) {
			step = frames;
			if (*(short*)(trackBytes + 0xD2) <= frames) {
				step = *(short*)(trackBytes + 0xD2);
			}
			*(short*)(trackBytes + 0xD2) = *(short*)(trackBytes + 0xD2) - (short)step;
			trackData[0x30] += trackData[0x31] * step;
		}
	}

	if (*(short*)(voiceBase + 0x28) != 0) {
		step = frames;
		if (*(short*)(voiceBase + 0x28) <= frames) {
			step = *(short*)(voiceBase + 0x28);
		}
		*(short*)(voiceBase + 0x28) = *(short*)(voiceBase + 0x28) - (short)step;
	}

	if (*(short*)(voiceBase + 0x38) != 0) {
		step = frames;
		if (*(short*)(voiceBase + 0x38) <= frames) {
			step = *(short*)(voiceBase + 0x38);
		}
		*(short*)(voiceBase + 0x38) = *(short*)(voiceBase + 0x38) - (short)step;
	}
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
