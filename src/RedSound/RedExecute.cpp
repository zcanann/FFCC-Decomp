#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "types.h"
#include "dolphin/ax.h"
#include "dolphin/axfx.h"
#include <string.h>

extern int DAT_8032f400;
struct RedReverbDATA {
    void (*callback)(void*, void*);
    void* context;
    int kind;
};

u8 m_RandomIndex;
int p_ReverbData;
u32* p_ReverbSize;
u32 m_ChangeStatus;
int* p_SkipKeyOn;

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
    u8 value = (u8)DAT_8021dcce[m_RandomIndex];
    m_RandomIndex = m_RandomIndex + 1;
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x801C2FFC
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int PitchCompute(int param_1, int param_2, int param_3, int param_4)
{
    int pitch;
    int octaveAdjust;
    int noteBand;
    int value;

    octaveAdjust = 0;
    pitch = (param_1 >> 12) + param_2 + (param_3 >> 16);
    while (pitch < 0) {
        pitch += 0xC00;
        octaveAdjust -= 1;
    }

    noteBand = (pitch >> 8) & 0x7F;
    octaveAdjust += noteBand / 12;
    value = (int)((DAT_8021d7f0[noteBand % 12] >> (10 - octaveAdjust)) * DAT_8021d820[pitch & 0xFF]) >> 12;

    if (param_4 != 0) {
        if (param_4 > 0) {
            value = value + ((int)(value * (param_4 + 1)) >> 7);
        } else {
            value = (int)(value * (param_4 & 0xFF)) >> 8;
        }
    }

    return value;
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
void ReverbAreaAlloc(unsigned long size)
{
    unsigned long alignedSize = ((u32)size + 0x1F) & ~0x1F;
    p_ReverbSize[0] += (u32)size;
    p_ReverbSize[1] += (u32)alignedSize;
    RedNew((int)size);
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
    p_ReverbData = RedNew(0x18);
    memset((void*)p_ReverbData, 0, 0x18);
    p_ReverbSize = (u32*)RedNew(4);
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
        p_ReverbSize[0] = 0;
        p_ReverbSize[1] = 0;
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
    RedReverbDATA* reverb = (RedReverbDATA*)(p_ReverbData + (bank & 1) * 0xC);
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

    p_ReverbSize[0] = 0;
    p_ReverbSize[1] = 0;

    if (kind == 0) {
        _ClearReverb(bank);
        return (int*)p_ReverbSize;
    }

    if (kind > 5) {
        return 0;
    }

    reverb = (RedReverbDATA*)(p_ReverbData + (bank & 1) * 0xC);
    if ((reverb->callback != nullptr) && (reverb->kind == kind)) {
        _SetReverbData(reverb, params);
        return (int*)p_ReverbSize;
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
        p_ReverbSize[0] = 0;
        p_ReverbSize[1] = 0;
    }

    return (int*)p_ReverbSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedVoiceDATA* EntryVoiceSearch(RedTrackDATA* track)
{
    int* bestVoice = 0;
    int* voice = 0;
    int bestEnvelope;
    int* voiceEnd;

    if ((((u8*)track)[0x26] & 5) == 0) {
        voice = (int*)DAT_8032f444;
        if ((((u8*)track)[0x26] & 8) == 0) {
            voice = (int*)DAT_8032f444 + *(s8*)((u8*)DAT_8032f3f4 + 0x490) * 0x30;
        }

        bestEnvelope = 0x8000;
        voiceEnd = (int*)DAT_8032f444 + 0xC00;
        do {
            if ((((u8*)voice)[0x1A] & 3) == 0) {
                if (voice[0x2C] < 1) {
                    if (*voice != 0) {
                        *voice = 0;
                    }
                    break;
                }

                if (voice[0x2C] < bestEnvelope) {
                    bestEnvelope = voice[0x2C];
                    bestVoice = voice;
                }
            }
            voice += 0x30;
        } while (voice < voiceEnd);

        if (voice == voiceEnd) {
            *(u32*)((u8*)DAT_8032f3f4 + 0x488) = *(u32*)((u8*)DAT_8032f3f4 + 0x488) | 2;
            voice = bestVoice;
            if (bestEnvelope == 0x8000) {
                voice = 0;
            }
        }
    } else {
        s8 voiceIndex = *(s8*)((u8*)track + 0x14E);
        voice = (int*)DAT_8032f444 + voiceIndex * 0x30;

        if (((((u8*)track)[0x26] & 1) == 0) && (*voice != 0) && (*voice != (int)track)) {
            voice = 0;
        }
    }

    if (voice != 0) {
        voice[0x24] = voice[0x24] & 0xFFFFFFFD;
        voice[0x2C] = 0x8000;
    }

    return (RedVoiceDATA*)voice;
}

/*
 * --INFO--
 * PAL Address: 0x801c3db4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _VoiceEnvelopeCheck()
{
    unsigned int* voiceData = DAT_8032f444;
    do {
        if ((((u8*)voiceData)[0x1A] & 7) != 0) {
            voiceData[0x2C] = 0x8000;
        }
        voiceData += 0x30;
    } while (voiceData < DAT_8032f444 + 0xC00);
}

/*
 * --INFO--
 * PAL Address: 0x801c3df8
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetVoiceVolumeMix(RedVoiceDATA* voice, int pan, int volume)
{
    int iVar1;
    int iVar2;
    int waveData;
    s16 leftPan;
    s16 rightPan;
    u16 uVar3;
    int volFactor;
    u16* mixData;
    int* voiceData = (int*)voice;

    waveData = voiceData[0];
    if (waveData == 0) {
        return;
    }

    mixData = (u16*)(voiceData + 0x1a);
    memset(mixData, 0, 0x24);

    if (DAT_8032f400 == 2) {
        *mixData = (u16)((u32)(volume * DAT_8021ddce[pan]) >> 8);
        *(s16*)(voiceData + 0x1e) = (s16)((u32)(volume * DAT_8021dfce[pan]) >> 8);
        *(s16*)(voiceData + 0x1b) = (s16)((u32)(volume * DAT_8021ddce[pan ^ 0x7f]) >> 8);
        *(s16*)(voiceData + 0x1f) = (s16)((u32)(volume * DAT_8021dfce[pan ^ 0x7f]) >> 8);

        if ((voiceData[0x25] & 0x1000U) != 0) {
            *(s16*)(voiceData + 0x1c) = (s16)((int)((u32)*mixData * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf);
            *(s16*)(voiceData + 0x22) = (s16)((int)((u32)*(u16*)(voiceData + 0x1e) * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf);
        }

        if ((voiceData[0x25] & 0x2000U) != 0) {
            *(s16*)(voiceData + 0x1d) = (s16)((int)((u32)*(u16*)(voiceData + 0x1b) * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf);
            *(s16*)(voiceData + 0x20) = (s16)((int)((u32)*(u16*)(voiceData + 0x1f) * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf);
        }
    } else if ((DAT_8032f400 < 2) && (0 < DAT_8032f400)) {
        volFactor = (int)DAT_8021de4e;

        if ((voiceData[0x25] & 0xc00U) != 0) {
            uVar3 = (u16)((u32)(volume * volFactor) >> 8);
            *mixData = uVar3;
            *(u16*)(voiceData + 0x1b) = uVar3;
        }

        if ((voiceData[0x25] & 0x3000U) != 0) {
            u16 monoMix = (u16)(((volume * volFactor >> 8) * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf);
            if ((voiceData[0x25] & 2U) == 0) {
                *(u16*)(voiceData + 0x1e) = monoMix;
                *(u16*)(voiceData + 0x1f) = monoMix;
            } else {
                *(u16*)(voiceData + 0x1c) = monoMix;
                *(u16*)(voiceData + 0x1d) = monoMix;
            }
        }
    } else {
        if (0x80 < pan) {
            pan = 0x100 - pan;
        }

        leftPan = DAT_8021ddce[pan];
        rightPan = DAT_8021ddce[pan ^ 0x7f];

        if ((voiceData[0x25] & 0x400U) != 0) {
            *mixData = (u16)((u32)(volume * leftPan) >> 8);
        }

        if ((voiceData[0x25] & 0x800U) != 0) {
            *(s16*)(voiceData + 0x1b) = (s16)((u32)(volume * rightPan) >> 8);
        }

        if ((voiceData[0x25] & 0x1000U) != 0) {
            iVar1 = ((volume * leftPan >> 8) * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf;
            if ((voiceData[0x25] & 2U) == 0) {
                *(u16*)(voiceData + 0x1e) = (u16)iVar1;
            } else {
                *(u16*)(voiceData + 0x1c) = (u16)iVar1;
            }
        }

        if ((voiceData[0x25] & 0x2000U) != 0) {
            iVar2 = ((volume * rightPan >> 8) * ((*(int*)(waveData + 0x68) >> 0xc) + 1)) >> 0xf;
            if ((voiceData[0x25] & 2U) == 0) {
                *(u16*)(voiceData + 0x1f) = (u16)iVar2;
            } else {
                *(u16*)(voiceData + 0x1d) = (u16)iVar2;
            }
        }
    }

    voiceData[0x24] |= 8;
}

/*
 * --INFO--
 * PAL Address: 0x801c40c8
 * PAL Size: 664b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _VolumeExecute(RedVoiceDATA* voice, int volume)
{
    int modVolume;
    int iVar1;
    unsigned int pan;
    int voiceMix;
    int envelopeMul;
    int* voiceData = (int*)voice;

    if (volume != 0) {
        volume = volume + 1;
    }

    voiceMix = volume * ((*(int*)voiceData[3] >> 0xc) + 1) >> 7;

    if (*(s8*)((int)voiceData + 0x19) != 0) {
        if (*(s8*)((int)voiceData + 0x19) == 0) {
            envelopeMul = 0;
        } else {
            envelopeMul = *(s8*)((int)voiceData + 0x19) + 1;
        }
        voiceMix = voiceMix * envelopeMul >> 7;
    }

    envelopeMul = *(int*)(*voiceData + 0x4c) >> 0xc;
    if (envelopeMul != 0) {
        envelopeMul = envelopeMul + 1;
    }

    pan = *(u8*)(voiceData[1] + 0x1a) & 0x7f;
    if ((*(u8*)(voiceData[1] + 0x1a) & 0x7f) != 0) {
        pan = pan + 1;
    }

    voiceMix = (int)(((voiceMix * envelopeMul >> 7) * (*(int*)voiceData[2] >> 0xc) >> 9) * pan) >> 7;

    if (*(int*)(*voiceData + 0x94) != 0) {
        if (*(s16*)(voiceData + 0xe) == 0) {
            envelopeMul = *(int*)(*voiceData + 0xa0) >> 0xc;
            if (envelopeMul != 0) {
                envelopeMul = envelopeMul + 1;
            }

            iVar1 = (**(int (**)(unsigned int))(*((int*)*voiceData + 0x25)))((unsigned int)voiceData[0xb] >> 0xc);
            modVolume = (voiceMix * envelopeMul >> 8) * (iVar1 >> 4) >> 0xc;

            if (voiceData[0xc] != 0) {
                iVar1 = voiceData[0xd];
                voiceData[0xd] = voiceData[0xd] + 1;
                modVolume = (modVolume * iVar1) / voiceData[0xc];
                if (voiceData[0xc] <= voiceData[0xd]) {
                    voiceData[0xc] = 0;
                }
            }

            voiceMix = voiceMix + modVolume;
            voiceData[0xb] = voiceData[0xb] + *(int*)(*voiceData + 0x98);

            if (voiceMix >= 0x8000) {
                voiceMix = 0x7fff;
            } else if (voiceMix < 0) {
                voiceMix = 0;
            }
        }
    }

    if (DAT_8032f400 == 1) {
        pan = 0x40;
    } else if ((voiceData[0x25] & 0xc0U) == 0) {
        if ((*(u8*)(voiceData[1] + 0x1b) & 0x80) == 0) {
            pan = *(int*)voiceData[4] >> 0xc;
        } else {
            pan = *(u8*)(voiceData[1] + 0x1b) & 0x7f;
            if ((*(u8*)(voiceData[1] + 0x1b) & 0x7f) == 0) {
                pan = 0x40;
            }
        }

        if (voiceData[0x11] != 0) {
            pan = pan + ((int)(pan * voiceData[0x11]) >> 7);
        }

        pan = (pan + *(int*)(*voiceData + 0xcc)) & 0xff;
    } else if ((voiceData[0x25] & 0x40U) == 0) {
        pan = 0x7f;
    } else {
        pan = 0;
    }

    if (voiceData[0x10] != 0) {
        voiceMix = voiceMix + (voiceMix * voiceData[0x10] >> 7);
        if (voiceMix >= 0x8000) {
            voiceMix = 0x7fff;
        } else if (voiceMix < 0) {
            voiceMix = 0;
        }
    }

    SetVoiceVolumeMix(voice, pan, voiceMix);
    voiceData[0x24] |= 8;
}

/*
 * --INFO--
 * PAL Address: 0x801c4360
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void _PitchExecute(RedVoiceDATA* param_1)
{
    int pitchDelta = 0;
    int* voiceData = (int*)param_1;
    int* trackData = (int*)voiceData[0];

    if ((trackData[0x1D] != 0) && (((s16*)voiceData)[10] == 0)) {
        u32 pitchLfo = (u32)trackData[0x20] >> 0xC;
        if ((int)pitchLfo < 0x80) {
            pitchDelta = ((int)pitchLfo + 1) * 2;
        } else {
            pitchDelta = ((int)(pitchLfo & 0x7F) + 1) * 0x18;
        }

        if ((((u8*)voiceData)[0x1A] & 3) == 0) {
            pitchDelta = PitchCompute(
                voiceData[0x28] + *DAT_8032f420,
                ((s16*)trackData)[0xA1] + ((s16*)trackData)[0x9F] + pitchDelta,
                ((int*)voiceData[1])[5],
                ((s8*)trackData)[0x148]);
        } else {
            pitchDelta = PitchCompute(
                voiceData[0x28] + trackData[0x17],
                ((s16*)trackData)[0xA1] + ((s16*)trackData)[0x9F] + pitchDelta,
                ((int*)voiceData[1])[5],
                ((s8*)trackData)[0x148]);
        }

        {
            int currentPitch = voiceData[0x26];
            int (*pitchWaveFunc)(u32) = *(int (**)(u32))((u8*)trackData + 0x74);
            int pitchWave = pitchWaveFunc((u32)voiceData[7] >> 0xC);
            pitchDelta = ((pitchDelta - currentPitch) * (pitchWave >> 4)) >> 0xC;
        }

        if (voiceData[8] != 0) {
            int frame = voiceData[9];
            voiceData[9] = frame + 1;
            pitchDelta = (pitchDelta * frame) / voiceData[8];
            if (voiceData[8] <= voiceData[9]) {
                voiceData[8] = 0;
            }
        }

        if (pitchDelta < 0) {
            pitchDelta >>= 1;
        }

        voiceData[7] += trackData[0x1E];
    }

    voiceData[0x27] = pitchDelta + voiceData[0x26] + voiceData[0xF];
    voiceData[0x24] |= 0x10;
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedWaveDATA* _WaveSplitSelect(RedWaveDATA* param_1, RedNoteDATA* param_2)
{
    u32* waveData = (u32*)param_1;
    char* noteData = (char*)param_2;
    u32 flags;

    if (waveData == nullptr) {
        return (RedWaveDATA*)waveData;
    }

    flags = *waveData;
    if ((flags & 0x30000) == 0) {
        return (RedWaveDATA*)waveData;
    }

    while (true) {
        if ((flags & 0x200) != 0) {
            break;
        }
        if (*(char*)(waveData + 6) >= *noteData) {
            break;
        }
        if ((flags & 1) != 0) {
            waveData += 0x18;
        }
        waveData += 0x18;
        flags = *waveData;
    }

    {
        char* splitKeyPtr = (char*)(waveData + 6);

        while (true) {
            if ((flags & 0x200) != 0) {
                return (RedWaveDATA*)waveData;
            }
            if ((u8)*((char*)waveData + 0x19) >= (u8)noteData[1]) {
                return (RedWaveDATA*)waveData;
            }
            if (*splitKeyPtr != *(char*)(waveData + 6)) {
                return (RedWaveDATA*)waveData;
            }
            if ((flags & 1) != 0) {
                waveData += 0x18;
            }
            waveData += 0x18;
            flags = *waveData;
        }
    }

    return (RedWaveDATA*)waveData;
}

/*
 * --INFO--
 * PAL Address: 0x801c45c0
 * PAL Size: 1568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _VoiceDataAsign(RedTrackDATA* param_1, RedVoiceDATA* param_2, RedNoteDATA* param_3, int* param_4)
{
    int iVar1;
    int iVar5;
    int local_38[4];
    int* trackData = (int*)param_1;
    int* voiceData = (int*)param_2;
    s8* trackS8 = (s8*)param_1;
    s16* trackS16 = (s16*)param_1;
    s8 note = *(s8*)param_3;
    unsigned int* voiceMask = (unsigned int*)param_4;

    voiceData[0] = (int)param_1;
    voiceData[0x23] = 1;

    if ((trackData[0x46] == 0) || (trackData[0x48] < 0)) {
        trackData[0x48] = note << 0x14;
        if (voiceData[1] != 0) {
            if ((((unsigned int*)voiceData[1])[0] & 0x20000) == 0) {
                voiceData[0x28] = note << 0x14;
                if (trackData[8] != 0) {
                    iVar5 = voiceData[0x28] >> 0x14;
                    iVar1 = iVar5 / 0xc + (voiceData[0x28] >> 0x1f);
                    local_38[0] = ((s8*)trackData[8])[iVar5 + (iVar1 - (iVar1 >> 0x1f)) * -0xc];
                    voiceData[0x28] += local_38[0] * 0x100000;
                }
            } else {
                voiceData[0x28] = ((s8*)voiceData[1])[0x18] << 0x14;
            }
        }
    } else {
        trackData[0x48] &= 0xfffff000;
        voiceData[0x28] = trackData[0x48];
        trackData[0x44] = trackData[0x46];
        local_38[0] = 0;
        DataAddCompute(local_38, note * 0x100 - (trackData[0x48] >> 0xc), &trackData[0x44]);
    }

    voiceData[6] = *(int*)param_3;
    voiceData[2] = (int)((u8*)param_1 + 0x28);
    voiceData[3] = (int)((u8*)param_1 + 0x34);
    voiceData[4] = (int)((u8*)param_1 + 0x40);

    if (voiceData[1] == 0) {
        memset(voiceData + 0x14, 0, 0xc);
    } else {
        memcpy(voiceData + 0x14, (void*)(trackData[7] + 0x50), 0xc);
    }

    voiceData[0x25] = trackData[0x3f];
    if (voiceData[1] != 0 && ((s8*)voiceData[1])[0x1c] != 0) {
        unsigned int maskBits;
        voiceData[0x25] &= 0xffffc3ff;
        if (((s8*)voiceData[1])[0x1c] == 1) {
            maskBits = 0x3c00;
        } else {
            maskBits = 0xc00;
        }
        voiceData[0x25] |= maskBits;
    }

    local_38[0] = trackS16[0xa1] + trackS16[0x9f];
    if ((((u8*)voiceData)[0x1a] & 3) == 0) {
        iVar5 = voiceData[0x28] + *DAT_8032f420;
    } else {
        iVar5 = voiceData[0x28] + trackData[0x17];
    }

    if (voiceData[1] == 0) {
        iVar5 = 0;
    } else {
        iVar5 = PitchCompute(iVar5, local_38[0], ((int*)voiceData[1])[5], trackS8[0x148]);
    }
    voiceData[0x26] = iVar5;

    if ((((unsigned int)trackData[0x41] & 0x100000) == 0) ||
        ((((trackS8[0x26] & 5) == 0) && (((unsigned int)trackData[0x41] & 0x280000) == 0)) ||
         (((trackS8[0x26] & 5) != 0) && (((unsigned int)trackData[0x41] & 0x80000) == 0)))) {
        if (trackData[0x1d] != 0) {
            ((s16*)voiceData)[10] = trackS16[0x48];
            local_38[0] = 0x100;
            if ((trackData[0x1e] >> 0xc) != 0) {
                local_38[0] = 0x100 / (trackData[0x1e] >> 0xc);
            }
            if (trackS16[0x49] == 0) {
                iVar5 = 0;
            } else {
                iVar5 = trackS16[0x49] * local_38[0] * 4;
            }
            voiceData[8] = iVar5;
            voiceData[9] = 0;
            voiceData[7] = 0;
        }

        if (trackData[0x25] != 0) {
            ((s16*)voiceData)[0xe] = trackS16[0x58];
            local_38[0] = 0x100;
            if ((trackData[0x26] >> 0xc) != 0) {
                local_38[0] = 0x100 / (trackData[0x26] >> 0xc);
            }
            if (trackS16[0x59] == 0) {
                iVar5 = 0;
            } else {
                iVar5 = trackS16[0x59] * local_38[0] * 4;
            }
            voiceData[0xc] = iVar5;
            voiceData[0xd] = 0;
            voiceData[0xb] = 0;
        }
    }

    if (((unsigned int)voiceData[0x25] & 0x4000U) == 0) {
        voiceData[0xf] = 0;
    } else {
        unsigned int random = GetRandomData();
        iVar5 = ((int)(random & 0xff) + 1) * voiceData[0x26] * trackData[0x38];
        local_38[0] = iVar5 >> 0xf;
        if ((random & 0x80) == 0) {
            voiceData[0xf] = local_38[0];
        } else {
            voiceData[0xf] = -(iVar5 >> 0x10);
        }
    }

    if (((unsigned int)voiceData[0x25] & 0x8000U) == 0) {
        voiceData[0x10] = 0;
    } else {
        s8 random = (s8)GetRandomData();
        voiceData[0x10] = (trackData[0x39] * random) >> 8;
    }

    if (((unsigned int)voiceData[0x25] & 0x10000U) == 0) {
        voiceData[0x11] = 0;
    } else {
        s8 random = (s8)GetRandomData();
        voiceData[0x11] = (trackData[0x3a] * random) >> 8;
    }

    if (voiceData[1] == 0) {
        memset(voiceData + 0x14, 0, 0xc);
    } else {
        memcpy(voiceData + 0x14, (void*)(voiceData[1] + 0x50), 0xc);
        if (trackS8[0xdc] != -1) {
            ((u8*)voiceData)[0x58] = trackS8[0xdc];
        }
        if (trackS16[0x6a] != -1) {
            ((s16*)voiceData)[0x28] = trackS16[0x6a];
        }
        if (trackS8[0xdd] != -1) {
            ((u8*)voiceData)[0x59] = trackS8[0xdd];
        }
        if (trackS16[0x6b] != -1) {
            ((s16*)voiceData)[0x29] = trackS16[0x6b];
        }
        if (trackS8[0xde] != -1) {
            ((u8*)voiceData)[0x5a] = trackS8[0xde];
        }
        if (trackS16[0x6c] != -1) {
            ((s16*)voiceData)[0x2a] = trackS16[0x6c];
        }
        if (trackS8[0xdf] != -1) {
            ((u8*)voiceData)[0x5b] = trackS8[0xdf];
        }
        if (trackS16[0x6d] != -1) {
            ((s16*)voiceData)[0x2b] = trackS16[0x6d];
        }
        if (((unsigned int)voiceData[0x25] & 0x40000U) != 0) {
            u16 random = GetRandomData();
            ((u16*)voiceData)[0x28] = (u16)(trackData[0x3c] * (random & 0xff));
        }
    }

    iVar5 = ((int)voiceData - (int)DAT_8032f444) / 0xc0 + (((int)voiceData - (int)DAT_8032f444) >> 0x1f);
    if (0x1f < iVar5 - (iVar5 >> 0x1f)) {
        voiceMask += 1;
    }

    if ((((unsigned int)trackData[0x41] & 0x80000) == 0) || (((unsigned int)trackData[0x41] & 0x100000) == 0)) {
        trackData[0x41] = (int)((unsigned int)trackData[0x41] | 0x100000);
        *voiceMask |= 1u << voiceData[0x2a];
    }
    voiceData[0x2e] |= 3;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedVoiceDATA* _VoiceDataSelect(RedTrackDATA* track, RedNoteDATA* note, int* voiceMask)
{
    int* voiceData = (int*)DAT_8032f444;
    int* trackData = (int*)track;

    if ((trackData[0x41] & 0x80000U) == 0) {
        voiceData = (int*)EntryVoiceSearch(track);
    } else {
        do {
            if (*voiceData == (int)track) {
                break;
            }
            voiceData += 0x30;
        } while (voiceData < (int*)DAT_8032f444 + 0xC00);

        if ((int*)DAT_8032f444 + 0xC00 <= voiceData) {
            voiceData = (int*)EntryVoiceSearch(track);
        }
    }

    if (voiceData != 0) {
        RedWaveDATA* wave = _WaveSplitSelect((RedWaveDATA*)trackData[7], note);
        voiceData[1] = (int)wave;
        _VoiceDataAsign(track, (RedVoiceDATA*)voiceData, note, voiceMask);

        if (((*(u32*)voiceData[1] & 1) != 0) && ((((u8*)trackData)[0x26] & 5) == 0)) {
            voiceData[0x25] |= 0x40;
            voiceData = (int*)EntryVoiceSearch(track);
            if (voiceData != 0) {
                voiceData[0x25] |= 0x80;
                voiceData[1] = (int)((u8*)wave + 0x60);
                _VoiceDataAsign(track, (RedVoiceDATA*)voiceData, note, voiceMask);
            }
        }
    }

    return (RedVoiceDATA*)voiceData;
}

/*
 * --INFO--
 * PAL Address: 0x801c4d08
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetVoiceAccess(RedTrackDATA* track, int mask)
{
    int* voiceData = (int*)DAT_8032f444;
    do {
        if ((voiceData[0] != 0) && (voiceData[0] == (int)track)) {
            voiceData[0x24] |= mask;
        }
        voiceData += 0x30;
    } while (voiceData < (int*)DAT_8032f444 + 0xC00);
}

/*
 * --INFO--
 * PAL Address: 0x801c4d58
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetVoiceSwitch(RedTrackDATA* track, int voiceSwitch)
{
    int* voiceData = (int*)DAT_8032f444;
    do {
        if ((voiceData[0] != 0) && (voiceData[0] == (int)track)) {
            voiceData[0x25] = voiceSwitch;
        }
        voiceData += 0x30;
    } while (voiceData < (int*)DAT_8032f444 + 0xC00);
}

/*
 * --INFO--
 * PAL Address: 0x801c4da0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _AdsrStart(RedVoiceDATA* voice)
{
    int* voiceData = (int*)voice;
    u32 prevLevel;
    u32 nextLevel;
    u32 stepFrames;

    voiceData[0x17] = 0;
    nextLevel = *(u8*)((u8*)voiceData + 0x58);
    do {
        prevLevel = nextLevel;
        stepFrames = *(u16*)((u8*)voiceData + 0x50 + voiceData[0x17] * 2);
        nextLevel = *(u8*)((u8*)voiceData + 0x50 + voiceData[0x17] + 9);
        if (stepFrames != 0) {
            break;
        }
        voiceData[0x17] += 1;
    } while (voiceData[0x17] < 3);

    voiceData[0x18] = stepFrames;
    if (nextLevel != 0) {
        nextLevel = (((nextLevel + 1) * 0x100) - 1) * 0x1000;
    }

    if (stepFrames == 0) {
        voiceData[0x2B] = nextLevel;
    } else {
        if (prevLevel != 0) {
            prevLevel = (((prevLevel + 1) * 0x100) - 1) * 0x1000;
        }
        voiceData[0x2B] = prevLevel;
        voiceData[0x19] = (int)((nextLevel | 0x800) - prevLevel) / (int)stepFrames;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c4e5c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void _AdsrDataCompute(RedVoiceDATA* voice)
{
    u32 prevValue = 0;
    u32 stepCount;
    int* stage = (int*)((int)voice + 0x5c);
    u32 level;
    u32 current = *(u32*)((int)voice + 0xac);

    while ((level = current, *stage < 3)) {
        level = (u32)*(u8*)((int)voice + 0x50 + *stage + 9);
        stepCount = (u32)*(u16*)((int)voice + 0x50 + *stage * 2);
        if (level != 0) {
            level = ((level + 1) * 0x100 - 1) * 0x1000;
        }
        prevValue = current;
        if (stepCount != 0) {
            break;
        }
        *stage = *stage + 1;
        current = level;
    }

    *(u32*)((int)voice + 0x60) = stepCount;
    if (stepCount == 0) {
        *(u32*)((int)voice + 0xac) = level;
    } else {
        *(u32*)((int)voice + 0xac) = prevValue;
        *(int*)((int)voice + 100) = (int)((level | 0x800) - prevValue) / (int)stepCount;
    }
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
u32 _AdsrDataExecute(RedVoiceDATA* voice)
{
    u32 changed = 0;
    int* voiceData = (int*)voice;

    if (voiceData[0x17] < 4) {
        if (((voiceData[0x24] & 4U) != 0) || (voiceData[0x17] < 3)) {
            changed = 1;
            voiceData[0x18] -= 1;
            voiceData[0x2B] += voiceData[0x19];
            if ((voiceData[0x18] == 0) && (voiceData[0x17] < 3)) {
                voiceData[0x17] += 1;
                _AdsrDataCompute(voice);
            }
        }
    } else {
        voiceData[0x2B] = 0;
    }

    if ((voiceData[0x2B] >> 0xC) < 1) {
        voiceData[0x17] = 4;
        voiceData[0x2B] = 0;
    }

    return changed;
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
    unsigned int* puVar1;
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
    int* voiceData = (int*)DAT_8032f444;

    while (true) {
        if (voiceData[0x23] == 0) {
            int voice = voiceData[5];
            voiceData[0x2C] = 0;
            voiceData[1] = 0;
            if (voice != 0) {
                if (*(s16*)(voice + 0x146) == 0) {
                    if (*(int*)(voice + 0xC) != 0) {
                        AXFreeVoice((AXVPB*)voice);
                    }
                    voiceData[5] = 0;
                    *voiceData = 0;
                } else {
                    *(u16*)(voice + 0x146) = 0;
                    *(u16*)(voice + 0x19C) = 0;
                    *(u32*)(voice + 0x1C) |= 0x204;
                }
            }
        } else {
            int voice = voiceData[5];
            u32 voiceFlags = 0;
            u32 envChanged = 0;

            if ((voiceData[0x24] & 1U) != 0) {
                if ((voice != 0) && (*(int*)(voice + 0xC) != 0)) {
                    AXFreeVoice((AXVPB*)voice);
                    voiceData[5] = 0;
                }

                if ((((u8*)voiceData)[0x1A] & 3) == 0) {
                    int prio = ((int)voiceData - (int)DAT_8032f444) / 0xC0 +
                               (((int)voiceData - (int)DAT_8032f444) >> 0x1F);
                    prio = (0x40 - (prio - (prio >> 0x1F)) >> 1) - 1;
                    if (prio < 1) {
                        prio = 1;
                    }
                    voiceData[5] = (int)AXAcquireVoice(prio, _VoiceDropedCallback, 0);
                } else {
                    voiceData[5] = (int)AXAcquireVoice(0x1F, _VoiceDropedCallback, 0);
                }
            }

            voice = voiceData[5];
            if (voice == 0) {
                voiceData[0x24] = 0;
                voiceData[0x23] = 0;
                return;
            }

            if ((voiceData[0x24] & 0x10U) != 0) {
                int pitch = voiceData[0x27];
                voiceFlags = 0x80000;
                *(u16*)(voice + 0x1DE) = (u16)(((u32)pitch >> 0x10) & 3);
                *(s16*)(voice + 0x1E0) = (s16)pitch;
            }

            if ((voiceData[0x24] & 8U) != 0) {
                if ((voiceData[0x25] & 8U) == 0) {
                    memcpy((void*)(voice + 0x14A), voiceData + 0x1A, 0x24);
                } else {
                    memset((void*)(voice + 0x14A), 0, 0x24);
                }

                *(u16*)(voice + 0x144) = 3;
                if ((voiceData[0x25] & 0x3000U) != 0) {
                    if ((voiceData[0x25] & 2U) == 0) {
                        *(u16*)(voice + 0x144) |= 0x600;
                    } else {
                        *(u16*)(voice + 0x144) |= 0x30;
                    }
                }
                voiceFlags |= 0x12;
            }

            if (((voiceData[0x25] & 8U) == 0) && ((voiceData[0x24] & 0x20U) != 0)) {
                _AdsrStart((RedVoiceDATA*)voiceData);
                envChanged = 1;
            }

            if ((voiceData[0x24] & 1U) == 0) {
                if ((voiceData[0x24] & 2U) == 0) {
                    if ((voiceData[0x25] & 8U) == 0) {
                        if ((voiceData[0x24] & 0x20U) == 0) {
                            envChanged |= _AdsrDataExecute((RedVoiceDATA*)voiceData);
                            voiceData[0x2C] = voiceData[0x2B] >> 0xC;
                        }
                        voiceData[0x24] &= 0xFFFFFFDF;
                    }
                } else {
                    voiceData[0x24] |= 4;
                    voiceData[0x17] = 3;
                    voiceData[0x18] = (u16)((u8*)voiceData)[0x56];
                    if (voiceData[0x18] == 0) {
                        voiceData[0x2B] = 0;
                    } else {
                        voiceData[0x19] = -voiceData[0x2B];
                        voiceData[0x19] = voiceData[0x19] / voiceData[0x18];
                    }
                    voiceData[0x2C] = voiceData[0x2B] >> 0xC;
                }
            } else {
                int waveData = voiceData[1];
                int trackData = voiceData[0];

                voiceData[0x24] &= 0xFFFFFFFB;
                if ((waveData == 0) || (trackData == 0)) {
                    voiceData[0x23] = 0;
                } else {
                    int key = (*(int*)(trackData + 0x11C) + *(int*)(waveData + 4) + 1) * 2;
                    int keyBase = key - 2;

                    envChanged += 1;
                    *(u16*)(voice + 0x148) = (u16)((voiceData[0x25] & 1U) != 0);
                    *(u16*)(voice + 0x140) = 1;
                    *(u16*)(voice + 0x146) = 1;

                    memcpy((void*)(voice + 0x1B6), (void*)(waveData + 0x22), 0x28);
                    memcpy((void*)(voice + 0x1EC), (void*)(waveData + 0x4A), 6);
                    memset((void*)(voice + 0x1E4), 0, 8);
                    *(u16*)(voice + 0x1A8) = 0;
                    *(int*)(voice + 0x1B2) = key;

                    if (*(int*)(waveData + 8) < 0) {
                        *(u16*)(voice + 0x1A6) = 0;
                        key = keyBase;
                    } else {
                        *(u16*)(voice + 0x1A6) = 1;
                        key = keyBase + *(int*)(waveData + 8);
                    }

                    *(s16*)(voice + 0x1AA) = (s16)((u32)key >> 0x10);
                    *(s16*)(voice + 0x1AC) = (s16)key;
                    *(int*)(voice + 0x1AE) = keyBase + *(int*)(waveData + 0xC);

                    voiceFlags |= 0x16100D;
                    voiceData[0x24] |= 0x20;
                    voiceData[0x2C] = 0x8000;
                    voiceData[0x2B] = 0;
                }
            }

            if (voiceData[0x2C] < 1) {
                voiceData[0x24] &= 0xFFFFFFFB;
                voiceData[0x23] = 0;
                voiceFlags |= 0x204;
                *voiceData = 0;
                *(u16*)(voice + 0x146) = 0;
                voiceData[0x2B] = 0;
                voiceData[0x2C] = 0;
                *(u16*)(voice + 0x19C) = 0;
                *(u16*)(voice + 0x19E) = 0;
            } else if ((envChanged != 0) && ((u32)*(u16*)(voice + 0x19C) != ((voiceData[0x2B] >> 0xC) & 0xFFFFU))) {
                voiceFlags |= 0x200;
                *(u16*)(voice + 0x19E) = 0;
                *(s16*)(voice + 0x19C) = (s16)(voiceData[0x2B] >> 0xC);
            }

            *(u32*)(voice + 0x1C) |= voiceFlags;
        }

        voiceData[0x24] &= 0xFFFFFC24;
        voiceData += 0x30;
        if ((int*)DAT_8032f444 + 0xC00 <= voiceData) {
            return;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _KeyOnControl()
{
    u32 local_24 = 0;
    u32 local_28 = 0;
    int* reserve = (int*)DAT_8032f3fc;
    unsigned int* voiceData = DAT_8032f444;
    int (*waveFunc)(int);

    _VoiceEnvelopeCheck();

    if (DAT_8032f3f8 != 0) {
        do {
            if ((*reserve != 0) && (*(int*)(*reserve + 0x1C) != 0)) {
                voiceData = (unsigned int*)_VoiceDataSelect((RedTrackDATA*)*reserve, (RedNoteDATA*)(reserve + 1), (int*)&local_28);
            }
            reserve += 2;
        } while ((voiceData != 0) && (reserve < (int*)DAT_8032f3fc + 0x180));
    }

    if ((*(s16*)((u8*)DAT_8032f3f0 + 0x48E) != 0) && ((((u32*)DAT_8032f3f0)[0x11B] & 0x10) == 0)) {
        int* track = *(int**)DAT_8032f3f0;
        do {
            if ((*track != 0) && (track[0x2D] != 0)) {
                waveFunc = (int (*)(int))track[0x2D];
                track[0x33] = (((track[0x30] >> 0xC) + 1) * waveFunc((u32)track[0x32] >> 0xC)) >> 0x10;
                track[0x32] += track[0x2E];
            }
            track += 0x55;
        } while (track < (int*)(*(int*)DAT_8032f3f0 + (u32)*((u8*)DAT_8032f3f0 + 0x491) * 0x154));
    }

    if ((*(s16*)((u8*)DAT_8032f3f0 + 0x922) != 0) && ((((u32*)DAT_8032f3f0)[0x240] & 0x10) == 0)) {
        int* track = (int*)((u32*)DAT_8032f3f0)[0x125];
        u32* trackBase = (u32*)DAT_8032f3f0 + 0x125;
        do {
            if ((*track != 0) && (track[0x2D] != 0)) {
                waveFunc = (int (*)(int))track[0x2D];
                track[0x33] = (((track[0x30] >> 0xC) + 1) * waveFunc((u32)track[0x32] >> 0xC)) >> 0x10;
                track[0x32] += track[0x2E];
            }
            track += 0x55;
        } while (track < (int*)(*trackBase + (u32)*((u8*)DAT_8032f3f0 + 0x925) * 0x154));
    }

    {
        u32* seTrackBase = (u32*)DAT_8032f3f0 + 0x36F;
        int* track = (int*)((u32*)DAT_8032f3f0)[0x36F];
        do {
            if ((*track != 0) && (track[0x2D] != 0)) {
                waveFunc = (int (*)(int))track[0x2D];
                track[0x33] = (((track[0x30] >> 0xC) + 1) * waveFunc((u32)track[0x32] >> 0xC)) >> 0x10;
                track[0x32] += track[0x2E];
            }
            track += 0x55;
        } while (track < (int*)(*seTrackBase + 0x2A80));
    }

    {
        unsigned int* voice = DAT_8032f444;
        do {
            if ((voice[0x23] != 0) && (*voice != 0) && ((*(u32*)(*voice + 0xFC) & 9) == 0)) {
                if (((voice[0x2E] & 2) != 0) || (*(int*)(*voice + 0x94) != 0) || (*(int*)(*voice + 0xB4) != 0)) {
                    int volume;
                    if ((*voice < *(u32*)DAT_8032f3f0) ||
                        (*(u32*)DAT_8032f3f0 + (u32)*((u8*)DAT_8032f3f0 + 0x491) * 0x154 <= *voice)) {
                        volume = DAT_8032f434;
                        if ((((u32*)DAT_8032f3f0)[0x125] <= *voice) &&
                            (*voice < ((u32*)DAT_8032f3f0)[0x125] + (u32)*((u8*)DAT_8032f3f0 + 0x925) * 0x154)) {
                            u32 idx = (u32)*(s8*)(*voice + 0x14E);
                            int idxSign = (int)*(s8*)(*voice + 0x14E) >> 0x1F;

                            if ((1U << (((idxSign * 0x20 |
                                          (u32)(*(s8*)(*voice + 0x14E) * 0x8000000 + idxSign) >> 0x1B) -
                                         idxSign) &
                                        DAT_8032f478[((int)idx >> 5) + (u32)((int)idx < 0 && (idx & 0x1F) != 0)])) == 0) {
                                volume = ((*(s8*)((u8*)DAT_8032f3f0 + 0x926) + 1) * (((int*)((u32*)DAT_8032f3f0)[300])[0] >> 0xC)) >> 7;
                                if (((u32*)DAT_8032f3f0)[0x23C] != 0) {
                                    volume = (volume * (((int*)((u32*)DAT_8032f3f0)[0x23A])[0] >> 0xC)) >> 9;
                                }
                                volume = (volume * DAT_8032f430) >> 9;
                            } else {
                                volume = 0;
                            }
                        }
                    } else {
                        u32 idx = (u32)*(s8*)(*voice + 0x14E);
                        int idxSign = (int)*(s8*)(*voice + 0x14E) >> 0x1F;
                        if ((1U << (((idxSign * 0x20 |
                                      (u32)(*(s8*)(*voice + 0x14E) * 0x8000000 + idxSign) >> 0x1B) -
                                     idxSign) &
                                    DAT_8032f478[((int)idx >> 5) + (u32)((int)idx < 0 && (idx & 0x1F) != 0)])) == 0) {
                            volume = ((*(s8*)((u8*)DAT_8032f3f0 + 0x492) + 1) * (((int*)((u32*)DAT_8032f3f0)[7])[0] >> 0xC)) >> 7;
                            if (((u32*)DAT_8032f3f0)[0x117] != 0) {
                                volume = (volume * (((int*)((u32*)DAT_8032f3f0)[0x115])[0] >> 0xC)) >> 9;
                            }
                            volume = (volume * DAT_8032f430) >> 9;
                        } else {
                            volume = 0;
                        }
                    }
                    _VolumeExecute((RedVoiceDATA*)voice, volume);
                }

                if (((voice[0x2E] & 1) != 0) || (*(int*)(*voice + 0x74) != 0)) {
                    _PitchExecute((RedVoiceDATA*)voice);
                }
                voice[0x2E] = 0;
            }
            voice += 0x30;
        } while (voice < DAT_8032f444 + 0xC00);
    }

    {
        u32 bit = 1;
        unsigned int* voice = DAT_8032f444;
        do {
            if ((local_28 & bit) != 0) {
                local_28 &= ~bit;
                voice[0x24] |= 1;
            }
            bit <<= 1;
            voice += 0x30;
        } while (local_28 != 0);
    }

    {
        u32 bit = 1;
        unsigned int* voice = DAT_8032f444 + 0x600;
        do {
            if ((local_24 & bit) != 0) {
                local_24 &= ~bit;
                voice[0x24] |= 1;
            }
            bit <<= 1;
            voice += 0x30;
        } while (local_24 != 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c5a3c
 * PAL Size: 688b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _ExecuteExtraData()
{
    u32* sound = (u32*)DAT_8032f3f0;
    u32* soundBase;
    unsigned int* voice;
    int* track;
    u32 musicBase;

    do {
        if ((sound[0x117] != 0) && (*sound != 0)) {
            sound[0x117]--;
            sound[0x115] += sound[0x116];
            if ((sound[0x117] == 0) && ((int)sound[0x116] < 0)) {
                MusicStop(sound[0x11C]);
            }

            if (*sound != 0) {
                musicBase = *sound;
                voice = DAT_8032f444;
                do {
                    if ((musicBase <= *voice) && (*voice < musicBase + (u32)*((u8*)sound + 0x491) * 0x154)) {
                        voice[0x2E] |= 2;
                    }
                    voice += 0x30;
                } while (voice < DAT_8032f444 + 0xC00);
            }
        }
        soundBase = (u32*)DAT_8032f3f0;
        sound += 0x125;
    } while (sound < (u32*)DAT_8032f3f0 + 0x24A);

    if (DAT_8032f41c[2] != 0) {
        DAT_8032f41c[2]--;
        DAT_8032f41c[0] += DAT_8032f41c[1];
    }

    if (DAT_8032f420[2] != 0) {
        DAT_8032f420[2]--;
        DAT_8032f420[0] += DAT_8032f420[1];
        voice = DAT_8032f444;
        do {
            if ((((u8*)voice)[0x1A] & 3) == 0) {
                voice[0x26] = PitchCompute(
                    voice[0x28] + DAT_8032f420[0],
                    (int)*(s16*)(*voice + 0x142) + (int)*(s16*)(*voice + 0x13E),
                    *(int*)(voice[1] + 0x14),
                    (s8)*(u8*)(*voice + 0x148));
                voice[0x2E] |= 1;
            }
            voice += 0x30;
        } while (voice < DAT_8032f444 + 0xC00);
    }

    do {
        if ((*(s16*)((u8*)soundBase + 0x48E) != 0) && (soundBase[9] != 0)) {
            soundBase[9]--;
            soundBase[7] += soundBase[8];
            if ((soundBase[0x11B] & 0x10000) == 0) {
                track = (int*)*soundBase;
                do {
                    voice = DAT_8032f444;
                    if (*track != 0) {
                        do {
                            if ((int*)*voice == track) {
                                voice[0x2E] |= 2;
                            }
                            voice += 0x30;
                        } while (voice < DAT_8032f444 + 0xC00);
                    }
                    track += 0x55;
                } while (track < (int*)(*soundBase + (u32)*((u8*)soundBase + 0x491) * 0x154));
            } else if ((soundBase[9] == 0) && (-1 < (int)soundBase[0x11C])) {
                MusicStop(soundBase[0x11C]);
            }
        }
        soundBase += 0x125;
    } while (soundBase < (u32*)DAT_8032f3f0 + 0x36F);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicTrackDataExecute(RedTrackDATA* track, int frames)
{
    u32 flags = 0;
    int* trackData = (int*)track;
    int* voiceData;

    trackData[0x43] += frames;

    if (trackData[0x0C] != 0) {
        int step = frames;
        if (trackData[0x0C] <= frames) {
            step = trackData[0x0C];
        }
        flags = 2;
        trackData[0x0C] -= step;
        trackData[0x0A] += trackData[0x0B] * step;
    }

    if (trackData[0x0F] != 0) {
        int step = frames;
        if (trackData[0x0F] <= frames) {
            step = trackData[0x0F];
        }
        flags = 2;
        trackData[0x0F] -= step;
        trackData[0x0D] += trackData[0x0E] * step;
    }

    if (trackData[0x12] != 0) {
        int step = frames;
        if (trackData[0x12] <= frames) {
            step = trackData[0x12];
        }
        flags = 2;
        trackData[0x12] -= step;
        trackData[0x10] += trackData[0x11] * step;
    }

    if (trackData[0x1C] != 0) {
        int step = frames;
        if (trackData[0x1C] <= frames) {
            step = trackData[0x1C];
        }
        flags = 2;
        trackData[0x1C] -= step;
        trackData[0x1A] += trackData[0x1B] * step;
    }

    if (trackData[0x44] != 0) {
        int step = frames;
        int addPitch;

        if (trackData[0x44] <= frames) {
            step = trackData[0x44];
        }
        flags |= 1;
        trackData[0x44] -= step;
        addPitch = step * trackData[0x45];
        trackData[0x48] += addPitch;

        voiceData = (int*)DAT_8032f444;
        do {
            if ((*voiceData == (int)track) && ((voiceData[0x28] += addPitch), (voiceData[1] != 0))) {
                voiceData[0x26] = PitchCompute(voiceData[0x28] + *DAT_8032f420,
                                               (int)*(s16*)((u8*)track + 0x142) + (int)*(s16*)((u8*)track + 0x13E),
                                               *(int*)((u8*)voiceData[1] + 0x14), (s8)((u8*)track)[0x148]);
            }
            voiceData += 0x30;
        } while (voiceData < (int*)DAT_8032f444 + 0xC00);
    }

    if (trackData[0x1D] != 0) {
        if (*(s16*)((u8*)track + 0x8C) != 0) {
            int step = frames;
            if (*(s16*)((u8*)track + 0x8C) <= frames) {
                step = *(s16*)((u8*)track + 0x8C);
            }
            *(s16*)((u8*)track + 0x8C) -= (s16)step;
            trackData[0x1E] += trackData[0x1F] * step;
        }
        if (*(s16*)((u8*)track + 0x8E) != 0) {
            int step = frames;
            if (*(s16*)((u8*)track + 0x8E) <= frames) {
                step = *(s16*)((u8*)track + 0x8E);
            }
            *(s16*)((u8*)track + 0x8E) -= (s16)step;
            trackData[0x20] += trackData[0x21] * step;
        }
    }

    if (trackData[0x25] != 0) {
        if (*(s16*)((u8*)track + 0xAC) != 0) {
            int step = frames;
            if (*(s16*)((u8*)track + 0xAC) <= frames) {
                step = *(s16*)((u8*)track + 0xAC);
            }
            *(s16*)((u8*)track + 0xAC) -= (s16)step;
            trackData[0x26] += trackData[0x27] * step;
        }
        if (*(s16*)((u8*)track + 0xAE) != 0) {
            int step = frames;
            if (*(s16*)((u8*)track + 0xAE) <= frames) {
                step = *(s16*)((u8*)track + 0xAE);
            }
            *(s16*)((u8*)track + 0xAE) -= (s16)step;
            trackData[0x28] += trackData[0x29] * step;
        }
    }

    voiceData = (int*)DAT_8032f444;
    if (trackData[0x2D] != 0) {
        if (*(s16*)((u8*)track + 0xD0) != 0) {
            int step = frames;
            if (*(s16*)((u8*)track + 0xD0) <= frames) {
                step = *(s16*)((u8*)track + 0xD0);
            }
            *(s16*)((u8*)track + 0xD0) -= (s16)step;
            trackData[0x2E] += trackData[0x2F] * step;
        }
        if (*(s16*)((u8*)track + 0xD2) != 0) {
            int step = frames;
            if (*(s16*)((u8*)track + 0xD2) <= frames) {
                step = *(s16*)((u8*)track + 0xD2);
            }
            *(s16*)((u8*)track + 0xD2) -= (s16)step;
            trackData[0x30] += trackData[0x31] * step;
        }
    }

    do {
        if (*voiceData == (int)track) {
            if (*(s16*)(voiceData + 0x0A) != 0) {
                int step = frames;
                if (*(s16*)(voiceData + 0x0A) <= frames) {
                    step = *(s16*)(voiceData + 0x0A);
                }
                *(s16*)(voiceData + 0x0A) -= (s16)step;
            }
            if (*(s16*)(voiceData + 0x0E) != 0) {
                int step = frames;
                if (*(s16*)(voiceData + 0x0E) <= frames) {
                    step = *(s16*)(voiceData + 0x0E);
                }
                *(s16*)(voiceData + 0x0E) -= (s16)step;
            }
            voiceData[0x2E] |= flags;
        }
        voiceData += 0x30;
    } while (voiceData < (int*)DAT_8032f444 + 0xC00);
}

/*
 * --INFO--
 * PAL Address: 0x801c619c
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MidiTrackExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* track = *(int**)control;
    do {
        if (*track != 0) {
            int step = frames;
            m_VoiceChangeStatus = 0;
            if (track[0x42] < frames) {
                step = track[0x42];
            }
            track[0x42] -= frames;
            _MusicTrackDataExecute((RedTrackDATA*)track, step);
            if (((track[0x41] & 0x200000) == 0) && (track[0x42] == 1)) {
                KeyOffSet(control, keyOnData, (RedTrackDATA*)track);
            }
            while ((*track != 0) && (track[0x42] < 1)) {
                unsigned char* cmd = (unsigned char*)*track;
                int delta;
                *track = (int)(cmd + 1);
                ((void (*)(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*))gRedCommandHandlerTable[*cmd])(
                    control, keyOnData, (RedTrackDATA*)track);
                if (*track != 0) {
                    if (track[0x42] < 1) {
                        delta = DeltaTimeSumup((unsigned char**)track);
                    } else {
                        delta = track[0x42];
                        track[0x42] = 0;
                    }

                    if (delta != 0) {
                        delta += *(s16*)(track + 0x4E);
                        if (delta < 1) {
                            delta = 1;
                        } else if ((track[0x3F] & 0x20000) != 0) {
                            delta += ((delta * track[0x3B] >> 8) * (int)GetRandomData()) >> 7;
                            if (delta < 1) {
                                delta = 1;
                            }
                        }
                    }

                    if (track[0x42] < -1) {
                        int execStep = delta;
                        if (track[0x42] + delta > 0) {
                            execStep = -track[0x42];
                        }
                        _MusicTrackDataExecute((RedTrackDATA*)track, execStep);
                    }
                    track[0x42] += delta;
                }
            }

            if (m_VoiceChangeStatus != 0) {
                int* voice = (int*)DAT_8032f444;
                do {
                    if ((int*)*voice == track) {
                        voice[0x2E] = m_VoiceChangeStatus;
                    }
                    voice += 0x30;
                } while (voice < (int*)DAT_8032f444 + 0xC00);
            }
        }
        track += 0x55;
    } while ((*(s16*)((u8*)control + 0x48E) != 0) &&
             (track < (int*)(*(int*)control + (u32)*(u8*)((u8*)control + 0x491) * 0x154)));
}

#pragma dont_inline on

/*
 * --INFO--
 * PAL Address: 0x801c63c4
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int _MusicMidiNoteExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* sound = (int*)control;

    frames <<= DAT_8032f40c;
    sound[0x121] = frames;
    sound[4] += frames;

    while (sound[5] <= sound[4]) {
        sound[3]++;
        sound[4] -= sound[5];
    }

    if (*(s16*)((u8*)sound + 0x48E) != 0) {
        _MidiTrackExecute(control, keyOnData, frames);
    }

    sound[0x11D] = 1;
    if ((DAT_8032f424 == 0) && ((sound[0x11B] & 2) != 0)) {
        sound[0x11B] &= ~2;
        if ((sound[0x11B] & 1) != 0) {
            *(s16*)((u8*)sound + 0x48E) = 0;
        }
    }

    return *(s16*)((u8*)sound + 0x48E);
}

/*
 * --INFO--
 * PAL Address: 0x801c64b0
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MusicNoteExecute()
{
    int i;
    u32 trackCount;
    u32* sound;
    u32* track;
    int status = _MusicMidiNoteExecute((RedSoundCONTROL*)DAT_8032f3f4, (RedKeyOnDATA*)DAT_8032f3fc, 1);

    while (status == 0) {
        if ((DAT_8032f424 != 0) || ((((u32*)DAT_8032f3f4)[0x11B] & 1) == 0)) {
            break;
        }

        *(s16*)((u8*)DAT_8032f3f4 + 0x48E) = *(s16*)((u8*)DAT_8032f3f4 + 0x434);
        memcpy((u8*)DAT_8032f3f4 + 0xC, (u8*)DAT_8032f3f4 + 0x438, 0x10);
        memcpy((u8*)DAT_8032f3f4 + 0x448, (u8*)DAT_8032f3f4 + 0x428, 0xC);

        sound = (u32*)DAT_8032f3f4;
        track = (u32*)*(u32*)DAT_8032f3f4;
        trackCount = (u8)*((u8*)DAT_8032f3f4 + 0x491);
        i = 0;
        do {
            track[0] = sound[i + 0xA];
            track[0x42] = sound[i + 0x4A];
            track[0x41] = sound[i + 0x8A];
            track[9] = sound[i + 0xCA];
            track += 0x55;
            i++;
        } while (--trackCount != 0);

        status = _MusicMidiNoteExecute((RedSoundCONTROL*)DAT_8032f3f4, (RedKeyOnDATA*)DAT_8032f3fc, 1);
    }

    if ((*(int*)((u8*)DAT_8032f3f0 + 0x470) < 0) && (*(int*)((u8*)DAT_8032f3f0 + 0x904) < 0) &&
        (*(int*)((u8*)DAT_8032f3f0 + 0xD98) < 0)) {
        DAT_8032f424 = 0;
    }
}

#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801c6604
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int _MusicMidiNoteSkipExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* sound = (int*)control;

    do {
        sound[0x11D] = frames;
        sound[0x121] = frames;
        sound[4] += frames;

        while (sound[5] <= sound[4]) {
            sound[3]++;
            sound[4] -= sound[5];
        }

        if (*(s16*)((u8*)sound + 0x48E) != 0) {
            _MidiTrackExecute(control, keyOnData, frames);
        }

        if (DAT_8032f410 != 0) {
            if ((*(s16*)((u8*)sound + 0x48E) != 0) && ((sound[0x11B] & 2) == 0)) {
                DAT_8032f410--;
                frames = sound[5];
                RedSleep(1000);
            }
        }

        if (DAT_8032f410 < 1) {
            break;
        }
    } while (*(s16*)((u8*)sound + 0x48E) != 0);

    sound[0x11D] = 1;
    if ((sound[0x11B] & 2) != 0) {
        sound[0x11B] &= ~2;
        if ((sound[0x11B] & 1) != 0) {
            *(s16*)((u8*)sound + 0x48E) = 0;
        }
    }

    return *(s16*)((u8*)sound + 0x48E);
}

/*
 * --INFO--
 * PAL Address: 0x801c6734
 * PAL Size: 588b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SkipMusicEntry()
{
    int* src;
    int* dst;
    u8 temp[0xC];

    if (*(int*)((u8*)DAT_8032f3f0 + 0xD98) >= 0) {
        src = p_SkipKeyOn;
        dst = (int*)DAT_8032f3fc;
        do {
            if ((*src != 0) && (*dst == 0)) {
                *dst = *src;
                dst[1] = src[1];
                DAT_8032f3f8++;
            }
            src += 2;
            dst += 2;
        } while (src < p_SkipKeyOn + 0x80);

        src = p_SkipKeyOn + 0x80;
        for (dst = (int*)DAT_8032f3fc + 0x80; (dst < (int*)DAT_8032f3fc + 0x100) && (*dst != 0); dst += 2) {
        }
        while ((dst < (int*)DAT_8032f3fc + 0x100) && (src < p_SkipKeyOn + 0x100)) {
            if (*src != 0) {
                *dst = *src;
                dst[1] = src[1];
                dst += 2;
                DAT_8032f3f8++;
            }
            src += 2;
        }

        src = p_SkipKeyOn + 0x100;
        for (dst = (int*)DAT_8032f3fc + 0x100; (dst < (int*)DAT_8032f3fc + 0x180) && (*dst != 0); dst += 2) {
        }
        while ((dst < (int*)DAT_8032f3fc + 0x180) && (src < p_SkipKeyOn + 0x180)) {
            if (*src != 0) {
                *dst = *src;
                dst[1] = src[1];
                dst += 2;
                DAT_8032f3f8++;
            }
            src += 2;
        }

        if (*(int*)((u8*)DAT_8032f3f0 + 0x470) != -1) {
            if (*(int*)((u8*)DAT_8032f3f0 + 0x904) != -1) {
                MusicStop(*(int*)((u8*)DAT_8032f3f0 + 0x904));
            }
            memcpy((u8*)DAT_8032f3f0 + 0x494, DAT_8032f3f0, 0x494);
        }

        memcpy(DAT_8032f3f0, (u8*)DAT_8032f3f0 + 0x928, 0x494);
        memcpy(temp, (u8*)DAT_8032f3f0 + 0x944, 0xC);
        memset((u8*)DAT_8032f3f0 + 0x928, 0, 0x494);
        memcpy((u8*)DAT_8032f3f0 + 0x944, temp, 0xC);
        *(int*)((u8*)DAT_8032f3f0 + 0xD98) = -1;
    }

    RedDelete(p_SkipKeyOn);
    DAT_8032f470 = 0;
}

#pragma dont_inline on

/*
 * --INFO--
 * PAL Address: 0x801c6980
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MusicSkipFunction()
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    u32 uVar6;
    int iVar7;
    u32* puVar8;
    u32* puVar9;

    do {
        p_SkipKeyOn = (int*)RedNew(0x600);
        if (p_SkipKeyOn == 0) {
            RedSleep(10000);
        }
        iVar4 = (int)DAT_8032f3f0;
    } while (p_SkipKeyOn == 0);

    puVar9 = (u32*)((u8*)DAT_8032f3f0 + 0x928);
    memset(p_SkipKeyOn, 0, 0x600);
    iVar5 = _MusicMidiNoteSkipExecute((RedSoundCONTROL*)puVar9, (RedKeyOnDATA*)p_SkipKeyOn, 1);
    while (true) {
        if ((iVar5 != 0) || ((*(u32*)(iVar4 + 0xd94) & 1) == 0)) {
            break;
        }
        *(s16*)(iVar4 + 0xdb6) = *(s16*)(iVar4 + 0xd5c);
        memcpy((void*)(iVar4 + 0x934), (void*)(iVar4 + 0xd60), 0x10);
        memcpy((void*)(iVar4 + 0xd70), (void*)(iVar4 + 0xd50), 0xc);
        puVar8 = (u32*)*puVar9;
        iVar7 = iVar4 + 0x950;
        uVar6 = (u32)*(u8*)(iVar4 + 0xdb9);
        iVar5 = 0;
        do {
            iVar1 = iVar5 * 4;
            iVar2 = iVar5 * 4;
            iVar3 = iVar5 * 4;
            *puVar8 = *(u32*)(iVar7 + iVar5 * 4);
            uVar6 -= 1;
            iVar5 += 1;
            puVar8[0x42] = *(u32*)(iVar7 + iVar1 + 0x100);
            puVar8[0x41] = *(u32*)(iVar7 + iVar2 + 0x200);
            puVar8[9] = *(u32*)(iVar7 + iVar3 + 0x300);
            puVar8 += 0x55;
        } while (uVar6 != 0);
        iVar5 = _MusicMidiNoteSkipExecute((RedSoundCONTROL*)puVar9, (RedKeyOnDATA*)p_SkipKeyOn, 1);
    }
    DAT_8032f470 = 1;
}

#pragma dont_inline reset

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
 * PAL Address: 0x801c703c
 * PAL Size: 572b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SeMidiNoteExecute(
    RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* trackData, int frames, int tickStep)
{
    int* track = (int*)trackData;
    do {
        if ((*track != 0) && ((track[0x3F] & 8) == 0)) {
            *(s16*)((u8*)track + 0x146) += (s16)(tickStep * -0x78);
            while (*(s16*)((u8*)track + 0x146) < 1) {
                int step = frames;
                *(s16*)((u8*)track + 0x146) += 0xFA;
                if (track[0x42] < frames) {
                    step = track[0x42];
                }
                track[0x42] -= frames;
                _SeTrackDataExecute((RedTrackDATA*)track, step);
                if (((track[0x41] & 0x200000) == 0) && (track[0x42] == 1)) {
                    KeyOffSet(control, keyOnData, (RedTrackDATA*)track);
                }

                m_VoiceChangeStatus = 0;
                while ((*track != 0) && (track[0x42] < 1)) {
                    int delta;
                    unsigned char* cmd;
                    *(s16*)(track + 0x51) += 1;
                    cmd = (unsigned char*)*track;
                    *track = (int)(cmd + 1);
                    ((void (*)(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*))gRedCommandHandlerTable[*cmd])(
                        control, keyOnData, (RedTrackDATA*)track);
                    if (*track != 0) {
                        delta = DeltaTimeSumup((unsigned char**)track);
                        if (delta != 0) {
                            delta += *(s16*)(track + 0x4E);
                            if (delta < 1) {
                                delta = 1;
                            } else if ((track[0x3F] & 0x20000) != 0) {
                                delta += ((delta * track[0x3B] >> 8) * (int)GetRandomData()) >> 7;
                                if (delta < 1) {
                                    delta = 1;
                                }
                            }
                        }

                        if (track[0x42] < -1) {
                            int execStep = delta;
                            if (track[0x42] + delta > 0) {
                                execStep = -track[0x42];
                            }
                            _SeTrackDataExecute((RedTrackDATA*)track, execStep);
                        }
                        track[0x42] += delta;
                    }
                }

                if (m_VoiceChangeStatus != 0) {
                    ((int*)((u8*)DAT_8032f444 + (s8)((u8*)track)[0x14E] * 0xC0))[0x2E] = m_VoiceChangeStatus;
                }
            }
        }
        track += 0x55;
    } while (track < (int*)(*(int*)control + 0x2A80));
    ((int*)control)[0x11D] = 1;
}

/*
 * --INFO--
 * PAL Address: 0x801c7278
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MainControl(int frames)
{
    u32 mul;
    int step;

    _KeyOnControl();
    DAT_8032f3f8 = 0;
    memset(DAT_8032f3fc, 0, 0x600);

    DAT_8032f3f4 = (void*)((u8*)DAT_8032f3f0 + 0xDBC);
    _SeMidiNoteExecute((RedSoundCONTROL*)DAT_8032f3f4, (RedKeyOnDATA*)DAT_8032f3fc,
                       *(RedTrackDATA**)DAT_8032f3f4, *(int*)((u8*)DAT_8032f3f0 + 0x1230), frames);
    DAT_8032f3f4 = DAT_8032f3f0;

    if (*(s16*)((u8*)DAT_8032f3f0 + 0x48E) != 0) {
        if ((((u32*)DAT_8032f3f0)[0x11B] & 0x10) == 0) {
            mul = ((u32)*DAT_8032f41c >> 0xC) & 0xFFFF;
            step = *(int*)((u8*)DAT_8032f3f0 + 0x448) >> 0xC;
            if (mul != 0) {
                if (*DAT_8032f41c < 0) {
                    step = (step * (int)mul) >> 0x10;
                } else {
                    step = ((step * ((int)mul + 1)) >> 0xF) + (*(int*)((u8*)DAT_8032f3f0 + 0x448) >> 0xC);
                }
            }
            *(s16*)((u8*)DAT_8032f3f0 + 0x48C) -= (s16)step * (s16)frames;
            while (*(s16*)((u8*)DAT_8032f3f4 + 0x48C) < 1) {
                *(s16*)((u8*)DAT_8032f3f4 + 0x48C) += 0xFA;
                _MusicNoteExecute();
            }
        }
    }

    if (*(s16*)((u8*)DAT_8032f3f0 + 0x922) != 0) {
        DAT_8032f3f4 = (void*)((u8*)DAT_8032f3f0 + 0x494);
        *(s16*)((u8*)DAT_8032f3f0 + 0x920) -= (s16)(*(int*)((u8*)DAT_8032f3f0 + 0x8DC) >> 0xC) * (s16)frames;
        while (*(s16*)((u8*)DAT_8032f3f4 + 0x48C) < 1) {
            *(s16*)((u8*)DAT_8032f3f4 + 0x48C) += 0xFA;
            _MusicNoteExecute();
        }
        if (*(s16*)((u8*)DAT_8032f3f0 + 0x48E) == 0) {
            memcpy(DAT_8032f3f0, (u8*)DAT_8032f3f0 + 0x494, 0x494);
            *(s16*)((u8*)DAT_8032f3f4 + 0x48E) = 0;
            *(u8*)((u8*)DAT_8032f3f4 + 0x491) = 0;
            *(int*)((u8*)DAT_8032f3f4 + 0x470) = -1;
        }
        DAT_8032f3f4 = DAT_8032f3f0;
    }

    _ExecuteExtraData();
    if (DAT_8032f470 != 0) {
        _SkipMusicEntry();
    }
}
