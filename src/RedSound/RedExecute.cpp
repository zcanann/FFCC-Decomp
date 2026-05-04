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

u32 t_TonePitch[] = {
    131072, 138865, 147123, 155871, 165140, 174960,
    185363, 196386, 208063, 220435, 233543, 247430,
};

int t_FinePitch[] = {
    65536, 65550, 65565, 65580, 65595, 65609, 65624, 65639,
    65654, 65669, 65684, 65698, 65713, 65728, 65743, 65758,
    65773, 65787, 65802, 65817, 65832, 65847, 65862, 65876,
    65891, 65906, 65921, 65936, 65951, 65966, 65981, 65996,
    66010, 66025, 66040, 66055, 66070, 66085, 66100, 66115,
    66130, 66145, 66160, 66174, 66189, 66204, 66219, 66234,
    66249, 66264, 66279, 66294, 66309, 66324, 66339, 66354,
    66369, 66384, 66399, 66414, 66429, 66444, 66459, 66474,
    66489, 66504, 66519, 66534, 66549, 66564, 66579, 66594,
    66609, 66624, 66639, 66654, 66669, 66684, 66699, 66714,
    66729, 66744, 66759, 66774, 66789, 66805, 66820, 66835,
    66850, 66865, 66880, 66895, 66910, 66925, 66940, 66955,
    66971, 66986, 67001, 67016, 67031, 67046, 67061, 67076,
    67092, 67107, 67122, 67137, 67152, 67167, 67182, 67198,
    67213, 67228, 67243, 67258, 67273, 67289, 67304, 67319,
    67334, 67349, 67365, 67380, 67395, 67410, 67425, 67441,
    67456, 67471, 67486, 67502, 67517, 67532, 67547, 67562,
    67578, 67593, 67608, 67623, 67639, 67654, 67669, 67685,
    67700, 67715, 67730, 67746, 67761, 67776, 67792, 67807,
    67822, 67837, 67853, 67868, 67883, 67899, 67914, 67929,
    67945, 67960, 67975, 67991, 68006, 68021, 68037, 68052,
    68067, 68083, 68098, 68114, 68129, 68144, 68160, 68175,
    68190, 68206, 68221, 68237, 68252, 68267, 68283, 68298,
    68314, 68329, 68344, 68360, 68375, 68391, 68406, 68422,
    68437, 68452, 68468, 68483, 68499, 68514, 68530, 68545,
    68561, 68576, 68592, 68607, 68623, 68638, 68654, 68669,
    68685, 68700, 68716, 68731, 68747, 68762, 68778, 68793,
    68809, 68824, 68840, 68855, 68871, 68886, 68902, 68917,
    68933, 68949, 68964, 68980, 68995, 69011, 69026, 69042,
    69057, 69073, 69089, 69104, 69120, 69135, 69151, 69167,
    69182, 69198, 69213, 69229, 69245, 69260, 69276, 69292,
    69307, 69323, 69339, 69354, 69370, 69385, 69401, 69417,
};

int t_KeySignatureIndex[] = {
    11, 4, 9, 2, 7, 0, 5, 10,
    11, 0, 5, 10, 3, 8, 1, 6,
    25, 30, 23, 28, 33, 26, 31, 24,
    34, 26, 31, 24, 29, 34, 27, 32,
};

signed char t_KeySignatureData[] = {
    0, 0, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1,
    0, 0, 0, 0, -1, 0, -1, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
};

signed char t_RandomData[] = {
    -115, 0, -26, 99, -116, -94, 94, 31, 49, 108, 21, -3, -52, 62, -7, -123,
    -43, 127, 98, 1, 101, 69, -33, -113, 112, -86, 88, 111, 56, 96, 79, 126,
    105, -17, 124, -85, 12, -50, -55, 66, 8, -42, -4, 5, -24, -9, -105, -34,
    42, -107, -90, -13, 87, -77, 53, -11, 64, -16, -20, 3, -69, 61, 57, 51,
    41, -122, -31, -22, 44, 68, -103, 47, 93, -12, -8, 6, 120, 102, 9, -118,
    -67, 35, -101, -35, -48, 65, -10, -120, -51, -1, 83, -53, -27, -49, -25, -112,
    80, -70, 43, -68, 7, 85, 121, -5, -18, -84, -98, 118, 37, 86, 33, 25,
    -38, -114, -61, -87, 67, -111, -28, 14, 34, 109, -104, 50, 2, -23, -93, -46,
    28, -19, -127, 13, -97, 45, 84, 36, 23, 110, 39, 104, 95, 123, 117, -74,
    114, -126, 74, -82, 125, 71, -95, -63, 77, -30, -60, 52, 27, 113, -102, 116,
    15, -92, -99, 97, -37, 46, 30, 48, -56, -108, 76, -73, -41, 29, -100, 81,
    54, 16, 4, 70, -71, 26, 22, 20, 115, 122, 11, 78, -109, -128, 90, 73,
    -81, 18, -2, 60, -117, -58, 38, -106, -89, -44, 119, 106, -83, -45, 89, 103,
    -110, 10, 91, 72, -29, 100, -80, 107, -15, -40, -21, -125, -124, -88, 17, -14,
    -64, -66, 63, 82, -47, 40, -72, -6, 24, -57, -79, 32, 58, -78, 19, -59,
    -76, -32, -121, -75, -96, -36, -54, -65, 92, -91, -62, 55, 59, 75, -39, -119,
};

s16 t_PanningData[] = {
    256, 254, 253, 252, 251, 250, 248, 247,
    246, 245, 244, 243, 241, 240, 239, 238,
    237, 236, 234, 233, 232, 231, 230, 229,
    227, 226, 225, 224, 223, 222, 220, 219,
    218, 217, 216, 214, 213, 212, 211, 210,
    209, 207, 206, 205, 204, 203, 202, 200,
    199, 198, 197, 196, 195, 193, 192, 191,
    190, 189, 188, 186, 185, 184, 183, 182,
    182, 176, 173, 170, 167, 164, 162, 159,
    156, 153, 150, 147, 145, 142, 139, 136,
    133, 130, 127, 125, 122, 119, 116, 113,
    110, 108, 105, 102, 99, 96, 93, 91,
    88, 85, 82, 79, 76, 73, 71, 68,
    65, 62, 59, 56, 54, 51, 48, 45,
    42, 39, 36, 34, 31, 28, 25, 22,
    19, 17, 14, 11, 8, 5, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 6,
    12, 18, 24, 30, 36, 42, 48, 54,
    60, 67, 73, 79, 85, 91, 97, 103,
    109, 115, 121, 128, 134, 140, 146, 152,
    158, 164, 170, 176, 182, 188, 195, 201,
    207, 213, 219, 225, 231, 237, 243, 249,
};

s16 t_PanningDataR[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 5, 11, 17, 23, 29,
    34, 40, 46, 52, 58, 64, 69, 75,
    81, 87, 93, 98, 104, 110, 116, 122,
    128, 133, 139, 145, 151, 157, 162, 168,
    174, 180, 186, 192, 197, 203, 209, 215,
    221, 226, 232, 238, 244, 250, 256, 249,
    243, 237, 231, 225, 219, 213, 207, 201,
    195, 188, 182, 176, 170, 164, 158, 152,
    146, 140, 134, 128, 121, 115, 109, 103,
    97, 91, 85, 79, 73, 67, 60, 54,
    48, 42, 36, 30, 24, 18, 12, 6,
};

static volatile u8 m_RandomIndex;
static RedReverbDATA* volatile p_ReverbData;
static RedReverbSize* p_ReverbSize;
volatile u32 m_ChangeStatus;
u32 m_TerminateNote[1] = { 0 };
static RedKeyOnDATA* volatile p_SkipKeyOn;
static const float s_ReverbTimeScale = 1000.0f;
static const float s_ReverbEffectScale = 100.0f;

enum RedExecuteLayoutSize {
    REDSOUND_REVERB_DATA_COUNT = 2,
    REDSOUND_REVERB_DATA_BUFFER_SIZE = sizeof(RedReverbDATA) * REDSOUND_REVERB_DATA_COUNT,
    REDSOUND_REVERB_AUX_BUFFER_SIZE = 0x280,
    REDSOUND_REVERB_ALLOC_ALIGN = 0x20,
    REDSOUND_REVERB_ALLOC_ALIGN_MASK = REDSOUND_REVERB_ALLOC_ALIGN - 1,
};

enum RedExecuteAxVoiceLayout {
    REDSOUND_AX_VOICE_PRIORITY_OFFSET = 0x0C,
    REDSOUND_AX_VOICE_SYNC_FLAGS_OFFSET = 0x1C,
    REDSOUND_AX_VOICE_SRC_SELECT_OFFSET = 0x140,
    REDSOUND_AX_VOICE_MIX_CTRL_OFFSET = 0x144,
    REDSOUND_AX_VOICE_RUNNING_OFFSET = 0x146,
    REDSOUND_AX_VOICE_LOOP_OFFSET = 0x148,
    REDSOUND_AX_VOICE_MIX_OFFSET = 0x14A,
    REDSOUND_AX_VOICE_VOLUME_OFFSET = 0x19C,
    REDSOUND_AX_VOICE_VOLUME_DELTA_OFFSET = 0x19E,
    REDSOUND_AX_VOICE_ADDR_LOOP_FLAG_OFFSET = 0x1A6,
    REDSOUND_AX_VOICE_ADDR_FORMAT_OFFSET = 0x1A8,
    REDSOUND_AX_VOICE_ADDR_LOOP_HI_OFFSET = 0x1AA,
    REDSOUND_AX_VOICE_ADDR_LOOP_LO_OFFSET = 0x1AC,
    REDSOUND_AX_VOICE_ADDR_END_OFFSET = 0x1AE,
    REDSOUND_AX_VOICE_ADDR_CURRENT_OFFSET = 0x1B2,
    REDSOUND_AX_VOICE_ADPCM_DATA_OFFSET = 0x1B6,
    REDSOUND_AX_VOICE_RATIO_HIGH_OFFSET = 0x1DE,
    REDSOUND_AX_VOICE_RATIO_LOW_OFFSET = 0x1E0,
    REDSOUND_AX_VOICE_SRC_LAST_SAMPLES_OFFSET = 0x1E4,
    REDSOUND_AX_VOICE_ADPCM_LOOP_OFFSET = 0x1EC,
    REDSOUND_AX_MIX_CTRL_DRY_STEREO = 0x3,
    REDSOUND_AX_MIX_CTRL_AUX_A_STEREO = 0x30,
    REDSOUND_AX_MIX_CTRL_AUX_B_STEREO = 0x600,
};

enum RedExecutePitchModConst {
    REDSOUND_PITCH_MOD_DEPTH_SPLIT = 0x80,
    REDSOUND_MOD_DELAY_PHASE_SCALE = 0x100,
    REDSOUND_MOD_DELAY_FRAME_SCALE = 4,
    REDSOUND_PITCH_MOD_SHALLOW_SCALE = 2,
    REDSOUND_PITCH_MOD_DEEP_SCALE = 0x18,
    REDSOUND_PITCH_MOD_WAVE_SHIFT = 4,
};

enum RedExecuteVolumeModConst {
    REDSOUND_VOLUME_MOD_SCALE_SHIFT = 7,
    REDSOUND_VOLUME_TRACK_SCALE_SHIFT = 9,
    REDSOUND_VOLUME_MOD_WAVE_SHIFT = 4,
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
	signed char* data = &t_RandomData[m_RandomIndex];
	m_RandomIndex++;
	return (u8)*data;
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
int PitchCompute(int basePitch, int pitchOffset, int wavePitch, int fineTune)
{
    int value;
    int pitch;
    int octaveAdjust;
    int noteBand;

    octaveAdjust = 0;
    pitch = pitchOffset + (wavePitch >> 16) + (basePitch >> REDSOUND_FIXED_SHIFT);
    while (pitch < 0) {
        pitch += REDSOUND_PITCH_OCTAVE_UNITS;
        octaveAdjust -= 1;
    }

    noteBand = (pitch >> REDSOUND_PITCH_NOTE_SHIFT) & REDSOUND_PITCH_NOTE_MASK;
    octaveAdjust += noteBand / REDSOUND_NOTES_PER_OCTAVE;
    value = (int)((t_TonePitch[noteBand % REDSOUND_NOTES_PER_OCTAVE] >> (REDSOUND_PITCH_TONE_SHIFT - octaveAdjust)) *
                  t_FinePitch[pitch & REDSOUND_PITCH_FINE_MASK]) >>
        REDSOUND_FIXED_SHIFT;

    if (fineTune != 0) {
        if (fineTune > 0) {
            value = value + ((int)(value * (fineTune + 1)) >> REDSOUND_PITCH_FINE_TUNE_POSITIVE_SHIFT);
        } else {
            value = (int)(value * (fineTune & REDSOUND_PITCH_FINE_MASK)) >> REDSOUND_PITCH_FINE_TUNE_NEGATIVE_SHIFT;
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
static void _ReverbNullCallback(AXFX_BUFFERUPDATE* update, void*)
{
    memset(update->left, 0, REDSOUND_REVERB_AUX_BUFFER_SIZE);
    memset(update->right, 0, REDSOUND_REVERB_AUX_BUFFER_SIZE);
    memset(update->surround, 0, REDSOUND_REVERB_AUX_BUFFER_SIZE);
}

/*
 * --INFO--
 * PAL Address: 0x801C3154
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* ReverbAreaAlloc(unsigned long size)
{
    p_ReverbSize->m_requested += (u32)size;
    p_ReverbSize->m_aligned += ((u32)size + REDSOUND_REVERB_ALLOC_ALIGN_MASK) & ~REDSOUND_REVERB_ALLOC_ALIGN_MASK;
    return (void*)RedNew((int)size);
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
void ReverbAreaFree(void* area)
{
    RedDelete(area);
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
    p_ReverbData = (RedReverbDATA*)RedNew(REDSOUND_REVERB_DATA_BUFFER_SIZE);
    memset(p_ReverbData, 0, REDSOUND_REVERB_DATA_BUFFER_SIZE);
    p_ReverbSize = (RedReverbSize*)RedNew(4);
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
static void _SetReverbData(RedReverbDATA* reverb, int* params)
{
    int result = 0;
    switch (reverb->kind) {
    case REDSOUND_REVERB_KIND_STD: {
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)reverb->context;
        std->tempDisableFX = 0;
        std->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        std->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        std->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        std->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        std->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        result = AXFXReverbStdSettings(std);
        break;
    }
    case REDSOUND_REVERB_KIND_HI: {
        AXFX_REVERBHI* hi = (AXFX_REVERBHI*)reverb->context;
        hi->tempDisableFX = 0;
        hi->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        hi->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        hi->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        hi->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        hi->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        hi->crosstalk = (float)params[REDSOUND_REVERB_PARAM_CROSSTALK] / s_ReverbEffectScale;
        result = AXFXReverbHiSettings(hi);
        break;
    }
    case REDSOUND_REVERB_KIND_DELAY: {
        AXFX_DELAY* delay = (AXFX_DELAY*)reverb->context;
        delay->delay[2] = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->delay[1] = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->delay[0] = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->feedback[2] = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->feedback[1] = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->feedback[0] = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->output[2] = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        delay->output[1] = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        delay->output[0] = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        result = AXFXDelaySettings(delay);
        break;
    }
    case REDSOUND_REVERB_KIND_CHORUS: {
        AXFX_CHORUS* chorus = (AXFX_CHORUS*)reverb->context;
        chorus->baseDelay = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_BASE_DELAY];
        chorus->variation = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_VARIATION];
        chorus->period = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_PERIOD];
        result = AXFXChorusSettings(chorus);
        break;
    }
    case REDSOUND_REVERB_KIND_HI_DPL2: {
        AXFX_REVERBHI_DPL2* hiDpl2 = (AXFX_REVERBHI_DPL2*)reverb->context;
        hiDpl2->tempDisableFX = 0;
        hiDpl2->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        hiDpl2->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        hiDpl2->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        hiDpl2->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        hiDpl2->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        result = AXFXReverbHiSettingsDpl2(hiDpl2);
        break;
    }
    }

    if (result != 1) {
        p_ReverbSize->m_aligned = 0;
        p_ReverbSize->m_requested = 0;
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
static void _ClearReverb(int bank)
{
    RedReverbDATA* reverb = p_ReverbData + (bank & 1);
    if (reverb->callback == 0) {
        return;
    }

    if (bank == 0) {
        AXRegisterAuxACallback((void (*)(void*, void*))_ReverbNullCallback, 0);
    } else {
        AXRegisterAuxBCallback((void (*)(void*, void*))_ReverbNullCallback, 0);
    }

    switch (reverb->kind) {
    case REDSOUND_REVERB_KIND_STD:
        AXFXReverbStdShutdown((AXFX_REVERBSTD*)reverb->context);
        break;
    case REDSOUND_REVERB_KIND_HI:
        AXFXReverbHiShutdown((AXFX_REVERBHI*)reverb->context);
        break;
    case REDSOUND_REVERB_KIND_DELAY:
        AXFXDelayShutdown((AXFX_DELAY*)reverb->context);
        break;
    case REDSOUND_REVERB_KIND_CHORUS:
        AXFXChorusShutdown((AXFX_CHORUS*)reverb->context);
        break;
    case REDSOUND_REVERB_KIND_HI_DPL2:
        AXFXReverbHiShutdownDpl2((AXFX_REVERBHI_DPL2*)reverb->context);
        break;
    }

    reverb->callback = 0;
    RedDelete((int)reverb->context);
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

    p_ReverbSize->m_aligned = 0;
    p_ReverbSize->m_requested = 0;

    if (kind == REDSOUND_REVERB_KIND_NONE) {
        _ClearReverb(bank);
        return (int*)p_ReverbSize;
    }

    if (kind == REDSOUND_REVERB_KIND_HI_DPL2) {
        return 0;
    }

    reverb = p_ReverbData + (bank & 1);
    if ((reverb->callback != 0) && (reverb->kind == kind)) {
        _SetReverbData(reverb, params);
        return (int*)p_ReverbSize;
    }

    _ClearReverb(bank);
    if (kind == REDSOUND_REVERB_KIND_HI_DPL2) {
        _ClearReverb(1);
    }

    reverb->kind = kind;
    result = 0;
    switch (kind) {
    case REDSOUND_REVERB_KIND_STD: {
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)RedNew(sizeof(AXFX_REVERBSTD));
        reverb->context = std;
        reverb->callback = (int)AXFXReverbStdCallback;
        std->tempDisableFX = 0;
        std->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        std->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        std->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        std->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        std->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        result = AXFXReverbStdInit(std);
        break;
    }
    case REDSOUND_REVERB_KIND_HI: {
        AXFX_REVERBHI* hi = (AXFX_REVERBHI*)RedNew(sizeof(AXFX_REVERBHI));
        reverb->context = hi;
        reverb->callback = (int)AXFXReverbHiCallback;
        hi->tempDisableFX = 0;
        hi->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        hi->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        hi->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        hi->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        hi->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        hi->crosstalk = (float)params[REDSOUND_REVERB_PARAM_CROSSTALK] / s_ReverbEffectScale;
        result = AXFXReverbHiInit(hi);
        break;
    }
    case REDSOUND_REVERB_KIND_DELAY: {
        AXFX_DELAY* delay = (AXFX_DELAY*)RedNew(sizeof(AXFX_DELAY));
        reverb->context = delay;
        reverb->callback = (int)AXFXDelayCallback;
        delay->delay[2] = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->delay[1] = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->delay[0] = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->feedback[2] = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->feedback[1] = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->feedback[0] = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->output[2] = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        delay->output[1] = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        delay->output[0] = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        result = AXFXDelayInit(delay);
        break;
    }
    case REDSOUND_REVERB_KIND_CHORUS: {
        AXFX_CHORUS* chorus = (AXFX_CHORUS*)RedNew(sizeof(AXFX_CHORUS));
        reverb->context = chorus;
        reverb->callback = (int)AXFXChorusCallback;
        chorus->baseDelay = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_BASE_DELAY];
        chorus->variation = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_VARIATION];
        chorus->period = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_PERIOD];
        result = AXFXChorusInit(chorus);
        break;
    }
    case REDSOUND_REVERB_KIND_HI_DPL2: {
        AXFX_REVERBHI_DPL2* hiDpl2 = (AXFX_REVERBHI_DPL2*)RedNew(sizeof(AXFX_REVERBHI_DPL2));
        reverb->context = hiDpl2;
        reverb->callback = (int)AXFXReverbHiCallbackDpl2;
        hiDpl2->tempDisableFX = 0;
        hiDpl2->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        hiDpl2->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        hiDpl2->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        hiDpl2->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        hiDpl2->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        result = AXFXReverbHiInitDpl2(hiDpl2);
        break;
    }
    }

    if (result == 1) {
        if (bank == 0) {
            AXRegisterAuxACallback((void (*)(void*, void*))reverb->callback, reverb->context);
        }
        else {
            AXRegisterAuxBCallback((void (*)(void*, void*))reverb->callback, reverb->context);
        }
    }
    else {
        p_ReverbSize->m_aligned = 0;
        p_ReverbSize->m_requested = 0;
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
    RedVoiceDATA* bestVoice = 0;
    RedVoiceDATA* voice;
    int bestEnvelope;
    RedVoiceDATA* voiceEnd;

    if ((static_cast<s8>(track->m_note.m_allocFlags) & REDSOUND_NOTE_ALLOC_DIRECT_MASK) != 0) {
        if (((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT) == 0) &&
            ((p_VoiceData + track->m_trackNo)->m_track != 0) &&
            ((p_VoiceData + track->m_trackNo)->m_track != track)) {
            voice = 0;
        }
        else {
            voice = p_VoiceData + track->m_trackNo;
        }
    } else {
        if ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_PRIORITY) != 0) {
            voice = (RedVoiceDATA*)p_VoiceData;
        } else {
            voice = p_VoiceData + (s8)p_SoundControl->m_channelAlloc;
        }

        bestEnvelope = REDSOUND_ENVELOPE_LEVEL_FULL;
        voiceEnd = p_VoiceData + REDSOUND_VOICE_COUNT;
        do {
            if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) == 0) {
                if (voice->m_envelopeLevel < 1) {
                    if (voice->m_track != 0) {
                        voice->m_track = 0;
                    }
                    break;
                }

                if (voice->m_envelopeLevel < bestEnvelope) {
                    bestEnvelope = voice->m_envelopeLevel;
                    bestVoice = voice;
                }
            }
            voice++;
        } while (voice < voiceEnd);

        if (voice == voiceEnd) {
            RedVoiceDATA* selectedVoice;
            RedSoundCONTROL* soundControl = (RedSoundCONTROL*)p_SoundControl;
            soundControl->m_updateFlags = soundControl->m_updateFlags | 2;
            if (bestEnvelope == REDSOUND_ENVELOPE_LEVEL_FULL) {
                selectedVoice = 0;
            } else {
                selectedVoice = bestVoice;
            }
            voice = selectedVoice;
        }
    }

    if (voice != 0) {
        voice->m_flags &= ~REDSOUND_VOICE_FLAGS_RELEASED;
        voice->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
    }

    return voice;
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
static void _VoiceEnvelopeCheck()
{
    RedVoiceDATA* voiceData = (RedVoiceDATA*)p_VoiceData;
    do {
        if ((voiceData->m_stateFlags & REDSOUND_VOICE_STATE_ANY_MASK) != 0) {
            voiceData->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
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
    RedTrackDATA* trackData;
    s16 leftPan;
    s16 rightPan;
    u16 uVar3;
    int volFactor;
    u16* mixData;
    int* voiceData = (int*)voice;

    trackData = voice->m_track;
    if (trackData == 0) {
        return;
    }

    mixData = voice->m_axMix;
    memset(mixData, 0, REDSOUND_VOICE_AX_MIX_SIZE);

    switch (m_SoundPlayMode) {
    case 1:
        volFactor = (int)t_PanningData[REDSOUND_PAN_BYTE_CENTER];
        int monoBase = (volume * volFactor) >> 8;

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_STEREO) != 0) {
            uVar3 = (u16)monoBase;
            *mixData = uVar3;
            mixData[REDSOUND_VOICE_AX_MIX_VR_INDEX] = uVar3;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_STEREO) != 0) {
            u16 monoMix = (u16)((monoBase * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT);
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData[REDSOUND_VOICE_AX_MIX_AUX_A_L_INDEX] = monoMix;
                mixData[REDSOUND_VOICE_AX_MIX_AUX_A_R_INDEX] = monoMix;
            } else {
                mixData[REDSOUND_VOICE_AX_MIX_AUX_B_L_INDEX] = monoMix;
                mixData[REDSOUND_VOICE_AX_MIX_AUX_B_R_INDEX] = monoMix;
            }
        }
        break;
    case 2:
        *mixData = (u16)((volume * t_PanningData[pan]) >> 8);
        *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_L_WORD) = (s16)((volume * t_PanningDataR[pan]) >> 8);
        *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_VR_WORD) = (s16)((volume * t_PanningData[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8);
        *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_R_WORD) = (s16)((volume * t_PanningDataR[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8);

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_LEFT) != 0) {
            *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_A_L_WORD) =
                (s16)((int)((u32)*mixData * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT);
            *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_A_S_WORD) =
                (s16)((int)((u32)*(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_L_WORD) *
                             ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >>
                      REDSOUND_AX_MIX_SHIFT);
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_RIGHT) != 0) {
            *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_A_R_WORD) =
                (s16)((int)((u32)*(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_VR_WORD) *
                             ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >>
                      REDSOUND_AX_MIX_SHIFT);
            *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_S_WORD) =
                (s16)((int)((u32)*(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_R_WORD) *
                             ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >>
                      REDSOUND_AX_MIX_SHIFT);
        }
        break;
    default:
        if (REDSOUND_PAN_BYTE_SIGN_BIT < pan) {
            pan = REDSOUND_PAN_BYTE_WRAP - pan;
        }

        leftPan = t_PanningData[pan];
        rightPan = t_PanningData[pan ^ REDSOUND_PAN_BYTE_MASK];
        int leftMix = (volume * leftPan) >> 8;
        int rightMix = (volume * rightPan) >> 8;

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_LEFT) != 0) {
            *mixData = (u16)leftMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_RIGHT) != 0) {
            *(s16*)(voiceData + REDSOUND_VOICE_AX_MIX_VR_WORD) = (s16)rightMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_LEFT) != 0) {
            iVar1 = (leftMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                *(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_A_L_WORD) = (u16)iVar1;
            } else {
                *(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_L_WORD) = (u16)iVar1;
            }
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_RIGHT) != 0) {
            iVar2 = (rightMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                *(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_A_R_WORD) = (u16)iVar2;
            } else {
                *(u16*)(voiceData + REDSOUND_VOICE_AX_MIX_AUX_B_R_WORD) = (u16)iVar2;
            }
        }
        break;
    }

    voice->m_flags |= REDSOUND_VOICE_FLAGS_ADPCM_DIRTY;
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
static void _VolumeExecute(RedVoiceDATA* voice, int volume)
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

    voiceMix = volume * ((*voice->m_trackExpression >> REDSOUND_FIXED_SHIFT) + 1) >>
               REDSOUND_VOLUME_MOD_SCALE_SHIFT;

    if (voice->m_velocity != 0) {
        if (voice->m_velocity == 0) {
            envelopeMul = 0;
        } else {
            envelopeMul = voice->m_velocity + 1;
        }
        voiceMix = voiceMix * envelopeMul >> 7;
    }

    envelopeMul = voice->m_track->m_mixVolume >> REDSOUND_FIXED_SHIFT;
    if (envelopeMul != 0) {
        envelopeMul = envelopeMul + 1;
    }

    pan = voice->m_waveData->m_volume & REDSOUND_PAN_BYTE_MASK;
    if (pan != 0) {
        pan = pan + 1;
    }

    voiceMix = (int)(((voiceMix * envelopeMul >> REDSOUND_VOLUME_MOD_SCALE_SHIFT) *
                      (*voice->m_trackVolume >> REDSOUND_FIXED_SHIFT) >>
                      REDSOUND_VOLUME_TRACK_SCALE_SHIFT) *
                     pan) >>
               REDSOUND_VOLUME_MOD_SCALE_SHIFT;

    if (voice->m_track->m_tremoloFunc != 0) {
        if (voice->m_volumeModDelay == 0) {
            envelopeMul = voice->m_track->m_tremoloDepth >> REDSOUND_FIXED_SHIFT;
            if (envelopeMul != 0) {
                envelopeMul = envelopeMul + 1;
            }

            iVar1 = voice->m_track->m_tremoloFunc((unsigned int)voice->m_volumeModPhase >> REDSOUND_FIXED_SHIFT);
            modVolume = (voiceMix * envelopeMul >> 8) * (iVar1 >> REDSOUND_VOLUME_MOD_WAVE_SHIFT) >>
                        REDSOUND_FIXED_SHIFT;

            if (voice->m_volumeModFrames != 0) {
                iVar1 = voice->m_volumeModFrame;
                voice->m_volumeModFrame = voice->m_volumeModFrame + 1;
                modVolume = (modVolume * iVar1) / voice->m_volumeModFrames;
                if (voice->m_volumeModFrames <= voice->m_volumeModFrame) {
                    voice->m_volumeModFrames = 0;
                }
            }

            voiceMix = voiceMix + modVolume;
            voice->m_volumeModPhase = voice->m_volumeModPhase + voice->m_track->m_tremoloRate;

            if (voiceMix >= REDSOUND_ENVELOPE_LEVEL_FULL) {
                voiceMix = REDSOUND_AX_MIX_MAX;
            } else if (voiceMix < 0) {
                voiceMix = 0;
            }
        }
    }

    if (m_SoundPlayMode == 1) {
        pan = REDSOUND_PAN_BYTE_CENTER;
    } else if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAIRED_PAN) == 0) {
        if ((voice->m_waveData->m_pan & REDSOUND_PAN_BYTE_SIGN_BIT) == 0) {
            pan = *voice->m_trackPan >> REDSOUND_FIXED_SHIFT;
        } else {
            pan = voice->m_waveData->m_pan & REDSOUND_PAN_BYTE_MASK;
            if (pan == 0) {
                pan = REDSOUND_PAN_BYTE_CENTER;
            }
        }

        if (voice->m_randomPan != 0) {
            pan = pan + ((int)(pan * voice->m_randomPan) >> REDSOUND_VOLUME_MOD_SCALE_SHIFT);
        }

        pan = (pan + voice->m_track->m_shakePan) & 0xff;
    } else if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAIRED_LEFT) == 0) {
        pan = REDSOUND_PAN_BYTE_MASK;
    } else {
        pan = 0;
    }

    if (voice->m_randomVolume != 0) {
        voiceMix =
            voiceMix + (voiceMix * voice->m_randomVolume >> REDSOUND_VOLUME_MOD_SCALE_SHIFT);
        if (voiceMix >= REDSOUND_ENVELOPE_LEVEL_FULL) {
            voiceMix = REDSOUND_AX_MIX_MAX;
        } else if (voiceMix < 0) {
            voiceMix = 0;
        }
    }

    SetVoiceVolumeMix(voice, pan, voiceMix);
    voice->m_flags |= REDSOUND_VOICE_FLAGS_ADPCM_DIRTY;
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
static void _PitchExecute(RedVoiceDATA* voice)
{
    int pitchDelta = 0;
    int* voiceData = (int*)voice;

    if ((voice->m_track->m_vibrateFunc != 0) && (voice->m_pitchModDelay == 0)) {
        int pitchLfo = voice->m_track->m_vibrateDepth >> REDSOUND_FIXED_SHIFT;
        if (pitchLfo < REDSOUND_PITCH_MOD_DEPTH_SPLIT) {
            pitchDelta = (pitchLfo + 1) * REDSOUND_PITCH_MOD_SHALLOW_SCALE;
        } else {
            pitchDelta = ((pitchLfo & REDSOUND_PAN_BYTE_MASK) + 1) * REDSOUND_PITCH_MOD_DEEP_SCALE;
        }

        int pitchBend = voice->m_track->m_pitchBend + voice->m_track->m_keyTranspose + pitchDelta;
        int basePitch;
        if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0) {
            basePitch = voice->m_basePitch + voice->m_track->m_pitch;
        } else {
            basePitch = voice->m_basePitch + p_MusicPitchControl->m_value;
        }
        pitchDelta = PitchCompute(basePitch, pitchBend, voice->m_waveData->m_pitch, voice->m_track->m_fineTune);

        {
            int currentPitch = voice->m_pitch;
            RedSwingFunc pitchWaveFunc = voice->m_track->m_vibrateFunc;
            int pitchWave = pitchWaveFunc((u32)voice->m_pitchModPhase >> REDSOUND_FIXED_SHIFT);
            pitchDelta = ((pitchDelta - currentPitch) * (pitchWave >> REDSOUND_PITCH_MOD_WAVE_SHIFT)) >>
                         REDSOUND_FIXED_SHIFT;
        }

        if (voice->m_pitchModFrames != 0) {
            int frame = voice->m_pitchModFrame;
            int rampedPitch = pitchDelta * frame;
            voice->m_pitchModFrame = voice->m_pitchModFrame + 1;
            pitchDelta = rampedPitch / voice->m_pitchModFrames;
            if (voice->m_pitchModFrames <= voice->m_pitchModFrame) {
                voice->m_pitchModFrames = 0;
            }
        }

        if (pitchDelta < 0) {
            pitchDelta >>= 1;
        }

        voice->m_pitchModPhase += voice->m_track->m_vibrateRate;
    }

    voice->m_targetPitch = pitchDelta + voice->m_pitch + voice->m_randomPitch;
    voice->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static RedWaveDATA* _WaveSplitSelect(RedWaveDATA* wave, RedNoteDATA* note)
{
    if ((wave != 0) && ((wave->m_flags & REDSOUND_WAVE_FLAG_SPLIT_TABLE) != 0)) {
        for (;;) {
            if ((wave->m_flags & REDSOUND_WAVE_FLAG_SPLIT_END) != 0) {
                break;
            }
            if (note->m_key <= wave->m_splitKey) {
                break;
            }
            if ((wave->m_flags & REDSOUND_WAVE_FLAG_PAIRED_ENTRY) != 0) {
                wave++;
            }
            wave++;
        }

        int splitKey = wave->m_splitKey;
        for (;;) {
            if ((wave->m_flags & REDSOUND_WAVE_FLAG_SPLIT_END) != 0) {
                break;
            }
            if (note->m_velocity <= wave->m_splitVelocity) {
                break;
            }
            if (splitKey == wave->m_splitKey) {
                if ((wave->m_flags & REDSOUND_WAVE_FLAG_PAIRED_ENTRY) != 0) {
                    wave++;
                }
                wave++;
            } else {
                return wave;
            }
        }
    }

    return wave;
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
static void _VoiceDataAsign(RedTrackDATA* param_1, RedVoiceDATA* param_2, RedNoteDATA* param_3, int* param_4)
{
    int iVar1;
    int iVar5;
    int local_38[4];
    int* voiceData = (int*)param_2;
    s8 note = param_3->m_key;
    unsigned int* voiceMask = (unsigned int*)param_4;

    param_2->m_track = param_1;
    param_2->m_active = 1;

    if ((param_1->m_portamentTime == 0) ||
        (param_1->m_portamentPitch < 0)) {
        param_1->m_portamentPitch = note << REDSOUND_PITCH_BASE_NOTE_SHIFT;
        if (param_2->m_waveData != 0) {
            if ((param_2->m_waveData->m_flags & REDSOUND_WAVE_FLAG_USE_WAVE_KEY) == 0) {
                param_2->m_basePitch = note << REDSOUND_PITCH_BASE_NOTE_SHIFT;
                if (param_1->m_keySignatureData != 0) {
                    iVar5 = param_2->m_basePitch >> REDSOUND_PITCH_BASE_NOTE_SHIFT;
                    iVar1 = iVar5 / REDSOUND_NOTES_PER_OCTAVE + (param_2->m_basePitch >> 0x1f);
                    local_38[0] =
                        param_1->m_keySignatureData[iVar5 + (iVar1 - (iVar1 >> 0x1f)) * -REDSOUND_NOTES_PER_OCTAVE];
                    param_2->m_basePitch += local_38[0] * REDSOUND_PITCH_KEY_SIGNATURE_UNIT;
                }
            } else {
                param_2->m_basePitch =
                    param_2->m_waveData->m_splitKey << REDSOUND_PITCH_BASE_NOTE_SHIFT;
            }
        }
    } else {
        param_1->m_portamentPitch &= REDSOUND_FIXED_WHOLE_MASK;
        param_2->m_basePitch = param_1->m_portamentPitch;
        param_1->m_sweepDelta = param_1->m_portamentTime;
        local_38[0] = 0;
        DataAddCompute(local_38, note * REDSOUND_PITCH_NOTE_UNIT -
                                     (param_1->m_portamentPitch >> REDSOUND_FIXED_SHIFT),
                       &param_1->m_sweepDelta);
    }

    voiceData[REDSOUND_VOICE_NOTE_WORD] = *(int*)param_3;
    param_2->m_trackVolume = &param_1->m_volume;
    param_2->m_trackExpression = &param_1->m_expression;
    param_2->m_trackPan = &param_1->m_pan;

    if (param_2->m_waveData == 0) {
        memset(param_2->m_adsrTime, 0, REDSOUND_TRACK_ADSR_SIZE);
    } else {
        memcpy(param_2->m_adsrTime,
               ((RedWaveDATA*)param_1->m_waveData)->m_adsr,
               REDSOUND_TRACK_ADSR_SIZE);
    }

    param_2->m_voiceSwitch = param_1->m_voiceSwitch;
    if (param_2->m_waveData != 0 &&
        param_2->m_waveData->m_reverbMix != 0) {
        unsigned int maskBits;
        param_2->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_MIX_MASK;
        if (param_2->m_waveData->m_reverbMix == 1) {
            maskBits = REDSOUND_VOICE_SWITCH_MIX_ALL;
        } else {
            maskBits = REDSOUND_VOICE_SWITCH_DRY_STEREO;
        }
        param_2->m_voiceSwitch |= maskBits;
    }

    local_38[0] = param_1->m_keyTranspose + param_1->m_pitchBend;
    if ((param_2->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) == 0) {
        iVar5 = param_2->m_basePitch + p_MusicPitchControl->m_value;
    } else {
        iVar5 = param_2->m_basePitch + param_1->m_pitch;
    }

    if (param_2->m_waveData == 0) {
        iVar5 = 0;
    } else {
        iVar5 = PitchCompute(iVar5, local_38[0], param_2->m_waveData->m_pitch, param_1->m_fineTune);
    }
    param_2->m_targetPitch = iVar5;

    if (((param_1->m_flags & REDSOUND_TRACK_FLAG_SLUR_RELEASE) == 0) ||
        ((((s8)param_1->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) == 0) &&
          ((param_1->m_flags & (REDSOUND_TRACK_FLAG_SLUR | REDSOUND_TRACK_FLAG_TENUTO)) == 0)) ||
         ((((s8)param_1->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) != 0) &&
          ((param_1->m_flags & REDSOUND_TRACK_FLAG_SLUR) == 0))) {
        if (param_1->m_vibrateFunc != 0) {
            param_2->m_pitchModDelay = param_1->m_vibrateDelay;
            local_38[0] = REDSOUND_MOD_DELAY_PHASE_SCALE;
            if ((param_1->m_vibrateRate >> REDSOUND_FIXED_SHIFT) != 0) {
                local_38[0] =
                    REDSOUND_MOD_DELAY_PHASE_SCALE / (param_1->m_vibrateRate >> REDSOUND_FIXED_SHIFT);
            }
            if (param_1->m_vibrateDelayDepth == 0) {
                iVar5 = 0;
            } else {
                iVar5 = param_1->m_vibrateDelayDepth * local_38[0] * REDSOUND_MOD_DELAY_FRAME_SCALE;
            }
            param_2->m_pitchModFrames = iVar5;
            param_2->m_pitchModFrame = 0;
            param_2->m_pitchModPhase = 0;
        }

        if (param_1->m_tremoloFunc != 0) {
            param_2->m_volumeModDelay = param_1->m_tremoloDelay;
            local_38[0] = REDSOUND_MOD_DELAY_PHASE_SCALE;
            if ((param_1->m_tremoloRate >> REDSOUND_FIXED_SHIFT) != 0) {
                local_38[0] =
                    REDSOUND_MOD_DELAY_PHASE_SCALE / (param_1->m_tremoloRate >> REDSOUND_FIXED_SHIFT);
            }
            if (param_1->m_tremoloDelayDepth == 0) {
                iVar5 = 0;
            } else {
                iVar5 = param_1->m_tremoloDelayDepth * local_38[0] * REDSOUND_MOD_DELAY_FRAME_SCALE;
            }
            param_2->m_volumeModFrames = iVar5;
            param_2->m_volumeModFrame = 0;
            param_2->m_volumeModPhase = 0;
        }
    }

    if ((param_2->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_PITCH) == 0) {
        param_2->m_randomPitch = 0;
    } else {
        unsigned int random = GetRandomData();
        iVar5 = ((int)(random & REDSOUND_RANDOM_BYTE_MASK) + 1) *
                param_2->m_targetPitch *
                param_1->m_fuzzyPitchDepth;
        local_38[0] = iVar5 >> REDSOUND_RANDOM_FUZZY_PITCH_SHIFT;
        if ((random & REDSOUND_RANDOM_BYTE_SIGN_BIT) == 0) {
            param_2->m_randomPitch = local_38[0];
        } else {
            param_2->m_randomPitch = -(iVar5 >> REDSOUND_RANDOM_FUZZY_PITCH_NEGATIVE_SHIFT);
        }
    }

    if ((param_2->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_VOLUME) == 0) {
        param_2->m_randomVolume = 0;
    } else {
        s8 random = (s8)GetRandomData();
        param_2->m_randomVolume =
            (param_1->m_fuzzyVolumeDepth * random) >> REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT;
    }

    if ((param_2->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_PAN) == 0) {
        param_2->m_randomPan = 0;
    } else {
        s8 random = (s8)GetRandomData();
        param_2->m_randomPan =
            (param_1->m_fuzzyPanDepth * random) >> REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT;
    }

    if (param_2->m_waveData == 0) {
        memset(param_2->m_adsrTime, 0, REDSOUND_TRACK_ADSR_SIZE);
    } else {
        memcpy(param_2->m_adsrTime,
               param_2->m_waveData->m_adsr,
               REDSOUND_TRACK_ADSR_SIZE);
        if ((s8)param_1->m_adsrAL != -1) {
            param_2->m_adsrLevel[0] =
                param_1->m_adsrAL;
        }
        if ((s16)param_1->m_adsrAR != -1) {
            param_2->m_adsrTime[0] =
                param_1->m_adsrAR;
        }
        if ((s8)param_1->m_adsrDL != -1) {
            param_2->m_adsrLevel[1] =
                param_1->m_adsrDL;
        }
        if ((s16)param_1->m_adsrDR != -1) {
            param_2->m_adsrTime[1] =
                param_1->m_adsrDR;
        }
        if ((s8)param_1->m_adsrSL != -1) {
            param_2->m_adsrLevel[2] =
                param_1->m_adsrSL;
        }
        if ((s16)param_1->m_adsrSR != -1) {
            param_2->m_adsrTime[2] =
                param_1->m_adsrSR;
        }
        if ((s8)param_1->m_adsrRL != -1) {
            param_2->m_adsrLevel[3] =
                param_1->m_adsrRL;
        }
        if ((s16)param_1->m_adsrRR != -1) {
            param_2->m_adsrTime[3] =
                param_1->m_adsrRR;
        }
        if ((param_2->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_ADSR) != 0) {
            u16 random = GetRandomData();
            param_2->m_adsrTime[0] =
                (u16)(param_1->m_fuzzyAdsrDepth *
                      (random & REDSOUND_RANDOM_BYTE_MASK));
        }
    }

    iVar5 = ((int)param_2 - (int)p_VoiceData) / REDSOUND_VOICE_SIZE + (((int)param_2 - (int)p_VoiceData) >> 0x1f);
    if (REDSOUND_VOICE_INDEX_MASK < iVar5 - (iVar5 >> 0x1f)) {
        voiceMask += 1;
    }

    if (((param_1->m_flags & REDSOUND_TRACK_FLAG_SLUR) == 0) ||
        ((param_1->m_flags & REDSOUND_TRACK_FLAG_SLUR_RELEASE) == 0)) {
        param_1->m_flags |= REDSOUND_TRACK_FLAG_SLUR_RELEASE;
        *voiceMask |= 1u << param_2->m_voiceIndex;
    }
    param_2->m_updateFlags |= REDSOUND_VOICE_UPDATE_ALL;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static RedVoiceDATA* _VoiceDataSelect(RedTrackDATA* track, RedNoteDATA* note, int* voiceMask)
{
    int* voiceData;

    if ((track->m_flags & REDSOUND_TRACK_FLAG_SLUR) != 0) {
        voiceData = (int*)p_VoiceData;
        do {
            if ((RedTrackDATA*)*voiceData == track) {
                break;
            }
            voiceData += REDSOUND_VOICE_SIZE / sizeof(*voiceData);
        } while (voiceData < (int*)(p_VoiceData + REDSOUND_VOICE_COUNT));

        if (!(voiceData < (int*)(p_VoiceData + REDSOUND_VOICE_COUNT))) {
            voiceData = (int*)EntryVoiceSearch(track);
        }
    } else {
        voiceData = (int*)EntryVoiceSearch(track);
    }

    if (voiceData != 0) {
        ((RedVoiceDATA*)voiceData)->m_waveData = _WaveSplitSelect((RedWaveDATA*)track->m_waveData, note);
        _VoiceDataAsign(track, (RedVoiceDATA*)voiceData, note, voiceMask);

        if (((((RedVoiceDATA*)voiceData)->m_waveData->m_flags & REDSOUND_WAVE_FLAG_PAIRED_ENTRY) != 0) &&
            (((s8)track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) == 0)) {
            RedWaveDATA* wave = ((RedVoiceDATA*)voiceData)->m_waveData;
            ((RedVoiceDATA*)voiceData)->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAIRED_LEFT;
            voiceData = (int*)EntryVoiceSearch(track);
            if (voiceData != 0) {
                ((RedVoiceDATA*)voiceData)->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAIRED_RIGHT;
                ((RedVoiceDATA*)voiceData)->m_waveData = wave + 1;
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
    RedVoiceDATA* voiceData = (RedVoiceDATA*)p_VoiceData;
    do {
        if ((voiceData->m_track != 0) && (voiceData->m_track == track)) {
            voiceData->m_flags |= mask;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
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
    RedVoiceDATA* voiceData = (RedVoiceDATA*)p_VoiceData;
    do {
        if ((voiceData->m_track != 0) && (voiceData->m_track == track)) {
            voiceData->m_voiceSwitch = voiceSwitch;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
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
static void _AdsrStart(RedVoiceDATA* voice)
{
    u8* adsrData = (u8*)voice + REDSOUND_VOICE_ADSR_TIME_OFFSET;
    int* stage = (int*)((u8*)voice + REDSOUND_VOICE_ADSR_STAGE_OFFSET);
    int prevLevel;
    int nextLevel;
    int stepFrames;

    nextLevel = *(u8*)((u8*)voice + REDSOUND_VOICE_ADSR_LEVEL_OFFSET);
    *stage    = 0;
    do {
        prevLevel = nextLevel;
        stepFrames = *(u16*)(adsrData + *stage * 2);
        nextLevel = *(u8*)(adsrData + *stage + REDSOUND_VOICE_ADSR_LEVEL_BASE);
        if (stepFrames != 0) {
            break;
        }
        *stage = *stage + 1;
    } while (*stage < REDSOUND_VOICE_ADSR_STAGE_COUNT);

    stage[1] = stepFrames;
    if (nextLevel != 0) {
        nextLevel += 1;
        nextLevel <<= 8;
        nextLevel -= 1;
        nextLevel <<= REDSOUND_FIXED_SHIFT;
    }

    if (stepFrames != 0) {
        if (prevLevel != 0) {
            prevLevel += 1;
            prevLevel <<= 8;
            prevLevel -= 1;
            prevLevel <<= REDSOUND_FIXED_SHIFT;
        }
        voice->m_adsrCurrentLevel = prevLevel;
        nextLevel |= REDSOUND_FIXED_HALF;
        stage[2] = (nextLevel - prevLevel) / stepFrames;
    } else {
        voice->m_adsrCurrentLevel = nextLevel;
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
static void _AdsrDataCompute(RedVoiceDATA* voice)
{
    u8* adsrData = (u8*)voice + REDSOUND_VOICE_ADSR_TIME_OFFSET;
    int prevValue;
    int stepCount;
    int level;
    int* stage = (int*)((u8*)voice + REDSOUND_VOICE_ADSR_STAGE_OFFSET);

    level = voice->m_adsrCurrentLevel;
    stepCount = 0;
    while (*stage < REDSOUND_VOICE_ADSR_STAGE_COUNT) {
        prevValue = level;
        level = (u32)*(u8*)(adsrData + *stage + REDSOUND_VOICE_ADSR_LEVEL_BASE);
        stepCount = (u32)*(u16*)(adsrData + *stage * 2);
        if (level != 0) {
            level += 1;
            level <<= 8;
            level -= 1;
            level <<= REDSOUND_FIXED_SHIFT;
        }
        if (stepCount != 0) {
            break;
        }
        *stage = *stage + 1;
    }

    stage[1] = stepCount;
    if (stepCount != 0) {
        voice->m_adsrCurrentLevel = prevValue;
        level |= REDSOUND_FIXED_HALF;
        stage[2] = (level - prevValue) / stepCount;
    } else {
        voice->m_adsrCurrentLevel = level;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C4F00
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static u32 _AdsrDataExecute(RedVoiceDATA* voice)
{
    u32 changed = 0;

    if (voice->m_adsrStage < 4) {
        if ((voice->m_flags & REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE) != 0 || voice->m_adsrStage < 3) {
            changed += 1;
            voice->m_adsrStepFrames -= 1;
            voice->m_adsrCurrentLevel += voice->m_adsrStepAdd;
            if (voice->m_adsrStepFrames == 0 && voice->m_adsrStage < 3) {
                voice->m_adsrStage += 1;
                _AdsrDataCompute(voice);
            }
        }
    } else {
        voice->m_adsrCurrentLevel = 0;
    }

    if ((voice->m_adsrCurrentLevel >> REDSOUND_FIXED_SHIFT) < 1) {
        voice->m_adsrStage = 4;
        voice->m_adsrCurrentLevel = 0;
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
static void _VoiceDropedCallback(void* dropped)
{
    RedVoiceDATA* voiceData;
    
    voiceData = (RedVoiceDATA*)p_VoiceData;
    do {
        if ((voiceData->m_axVoice != 0) && (voiceData->m_axVoice == dropped)) {
            voiceData->m_active = 0;
            voiceData->m_track = 0;
            voiceData->m_axVoice = 0;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void EnvelopeKeyExecute()
{
    int* voiceData = (int*)p_VoiceData;

    while (true) {
        if (voiceData[REDSOUND_VOICE_ACTIVE_WORD] == 0) {
            voiceData[REDSOUND_VOICE_ENVELOPE_WORD] = 0;
            voiceData[1] = 0;
            int voice = voiceData[REDSOUND_VOICE_AX_VOICE_WORD];
            if (voice != 0) {
                if (*(s16*)(voice + REDSOUND_AX_VOICE_RUNNING_OFFSET) == 0) {
                    if (*(int*)(voice + REDSOUND_AX_VOICE_PRIORITY_OFFSET) != 0) {
                        AXFreeVoice((AXVPB*)voice);
                    }
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = 0;
                    *voiceData = 0;
                } else {
                    *(u16*)(voice + REDSOUND_AX_VOICE_RUNNING_OFFSET) = 0;
                    *(u16*)(voice + REDSOUND_AX_VOICE_VOLUME_OFFSET) = 0;
                    *(u32*)(voice + REDSOUND_AX_VOICE_SYNC_FLAGS_OFFSET) |= AX_SYNC_FLAG_COPYVOL | AX_SYNC_FLAG_COPYSTATE;
                }
            }
        } else {
            int voice;

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_START) != 0) {
                voice = voiceData[REDSOUND_VOICE_AX_VOICE_WORD];
                if ((voice != 0) && (*(int*)(voice + REDSOUND_AX_VOICE_PRIORITY_OFFSET) != 0)) {
                    AXFreeVoice((AXVPB*)voice);
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = 0;
                }

                if ((((u8*)voiceData)[0x1A] & REDSOUND_VOICE_STATE_PLAYING_MASK) == 0) {
                    int prio = ((int)voiceData - (int)p_VoiceData) / REDSOUND_VOICE_SIZE +
                               (((int)voiceData - (int)p_VoiceData) >> 0x1F);
                    prio = (0x40 - (prio - (prio >> 0x1F)) >> 1) - 1;
                    if (prio < 1) {
                        prio = 1;
                    }
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = (int)AXAcquireVoice(prio, _VoiceDropedCallback, 0);
                } else {
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = (int)AXAcquireVoice(0x1F, _VoiceDropedCallback, 0);
                }
            }

            voice = voiceData[REDSOUND_VOICE_AX_VOICE_WORD];
            if (voice == 0) {
                voiceData[REDSOUND_VOICE_FLAGS_WORD] = 0;
                voiceData[REDSOUND_VOICE_ACTIVE_WORD] = 0;
                return;
            }

            u32 voiceFlags = 0;
            u32 envChanged = 0;

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_PITCH_DIRTY) != 0) {
                int pitch = voiceData[0x27];
                voiceFlags = AX_SYNC_FLAG_COPYRATIO;
                *(u16*)(voice + REDSOUND_AX_VOICE_RATIO_HIGH_OFFSET) = (u16)(((u32)pitch >> 0x10) & 3);
                *(s16*)(voice + REDSOUND_AX_VOICE_RATIO_LOW_OFFSET) = (s16)pitch;
            }

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_ADPCM_DIRTY) != 0) {
                if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_PAUSE) == 0) {
                    memcpy((void*)(voice + REDSOUND_AX_VOICE_MIX_OFFSET), voiceData + REDSOUND_VOICE_AX_MIX_WORD,
                           REDSOUND_VOICE_AX_MIX_SIZE);
                } else {
                    memset((void*)(voice + REDSOUND_AX_VOICE_MIX_OFFSET), 0, REDSOUND_VOICE_AX_MIX_SIZE);
                }

                *(u16*)(voice + REDSOUND_AX_VOICE_MIX_CTRL_OFFSET) = REDSOUND_AX_MIX_CTRL_DRY_STEREO;
                if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_REVERB_STEREO) != 0) {
                    if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) == 0) {
                        *(u16*)(voice + REDSOUND_AX_VOICE_MIX_CTRL_OFFSET) |= REDSOUND_AX_MIX_CTRL_AUX_B_STEREO;
                    } else {
                        *(u16*)(voice + REDSOUND_AX_VOICE_MIX_CTRL_OFFSET) |= REDSOUND_AX_MIX_CTRL_AUX_A_STEREO;
                    }
                }
                voiceFlags |= AX_SYNC_FLAG_COPYAXPBMIX | AX_SYNC_FLAG_COPYMXRCTRL;
            }

            if (((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_PAUSE) == 0) &&
                ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_ADSR_START) != 0)) {
                _AdsrStart((RedVoiceDATA*)voiceData);
                envChanged = 1;
            }

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_START) == 0) {
                if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_RELEASED) == 0) {
                    if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_PAUSE) == 0) {
                        if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_ADSR_START) == 0) {
                            envChanged |= _AdsrDataExecute((RedVoiceDATA*)voiceData);
                            voiceData[REDSOUND_VOICE_ENVELOPE_WORD] =
                                voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT;
                        }
                        voiceData[REDSOUND_VOICE_FLAGS_WORD] &= ~REDSOUND_VOICE_FLAGS_ADSR_START;
                    }
                } else {
                    voiceData[REDSOUND_VOICE_FLAGS_WORD] |= REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE;
                    voiceData[REDSOUND_VOICE_ADSR_STAGE_WORD] = 3;
                    voiceData[REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD] = (u16)((u8*)voiceData)[0x56];
                    if (voiceData[REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD] == 0) {
                        voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] = 0;
                    } else {
                        voiceData[REDSOUND_VOICE_ADSR_STEP_ADD_WORD] = -voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD];
                        voiceData[REDSOUND_VOICE_ADSR_STEP_ADD_WORD] =
                            voiceData[REDSOUND_VOICE_ADSR_STEP_ADD_WORD] / voiceData[REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD];
                    }
                    voiceData[REDSOUND_VOICE_ENVELOPE_WORD] =
                        voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT;
                }
            } else {
                voiceData[REDSOUND_VOICE_FLAGS_WORD] &= REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK;
                int waveData = voiceData[1];
                int trackData = voiceData[0];
                if ((waveData == 0) || (trackData == 0)) {
                    voiceData[REDSOUND_VOICE_ACTIVE_WORD] = 0;
                } else {
                    envChanged += 1;
                    int key = (*(int*)(trackData + 0x11C) + *(int*)(waveData + REDSOUND_WAVE_SAMPLE_START_OFFSET) + 1) * 2;
                    int keyBase = key - 2;

                    *(u16*)(voice + REDSOUND_AX_VOICE_LOOP_OFFSET) =
                        (u16)((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_LOOP) != 0);
                    *(u16*)(voice + REDSOUND_AX_VOICE_SRC_SELECT_OFFSET) = 1;
                    *(u16*)(voice + REDSOUND_AX_VOICE_RUNNING_OFFSET) = 1;

                    memcpy((void*)(voice + REDSOUND_AX_VOICE_ADPCM_DATA_OFFSET),
                           (void*)(waveData + REDSOUND_WAVE_ADPCM_DATA_OFFSET), 0x28);
                    memcpy((void*)(voice + REDSOUND_AX_VOICE_ADPCM_LOOP_OFFSET),
                           (void*)(waveData + REDSOUND_WAVE_ADPCM_LOOP_OFFSET), 6);
                    memset((void*)(voice + REDSOUND_AX_VOICE_SRC_LAST_SAMPLES_OFFSET), 0, 8);
                    *(u16*)(voice + REDSOUND_AX_VOICE_ADDR_FORMAT_OFFSET) = 0;
                    *(int*)(voice + REDSOUND_AX_VOICE_ADDR_CURRENT_OFFSET) = key;

                    if (*(int*)(waveData + REDSOUND_WAVE_LOOP_START_OFFSET) < 0) {
                        *(u16*)(voice + REDSOUND_AX_VOICE_ADDR_LOOP_FLAG_OFFSET) = 0;
                        key = keyBase;
                    } else {
                        *(u16*)(voice + REDSOUND_AX_VOICE_ADDR_LOOP_FLAG_OFFSET) = 1;
                        key = keyBase + *(int*)(waveData + REDSOUND_WAVE_LOOP_START_OFFSET);
                    }

                    *(s16*)(voice + REDSOUND_AX_VOICE_ADDR_LOOP_HI_OFFSET) = (s16)((u32)key >> 0x10);
                    *(s16*)(voice + REDSOUND_AX_VOICE_ADDR_LOOP_LO_OFFSET) = (s16)key;
                    *(int*)(voice + REDSOUND_AX_VOICE_ADDR_END_OFFSET) =
                        keyBase + *(int*)(waveData + REDSOUND_WAVE_LOOP_END_OFFSET);

                    voiceFlags |= AX_SYNC_FLAG_COPYADPCMLOOP | AX_SYNC_FLAG_COPYSRC | AX_SYNC_FLAG_COPYADPCM |
                                  AX_SYNC_FLAG_COPYCURADDR | AX_SYNC_FLAG_COPYADDR | AX_SYNC_FLAG_COPYTYPE |
                                  AX_SYNC_FLAG_COPYSTATE | AX_SYNC_FLAG_COPYSELECT;
                    voiceData[REDSOUND_VOICE_FLAGS_WORD] |= REDSOUND_VOICE_FLAGS_ADSR_START;
                    voiceData[REDSOUND_VOICE_ENVELOPE_WORD] = REDSOUND_ENVELOPE_LEVEL_FULL;
                    voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] = 0;
                }
            }

            if (voiceData[REDSOUND_VOICE_ENVELOPE_WORD] < 1) {
                voiceData[REDSOUND_VOICE_FLAGS_WORD] &= REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK;
                voiceData[REDSOUND_VOICE_ACTIVE_WORD] = 0;
                voiceFlags |= AX_SYNC_FLAG_COPYVOL | AX_SYNC_FLAG_COPYSTATE;
                *voiceData = 0;
                *(u16*)(voice + REDSOUND_AX_VOICE_RUNNING_OFFSET) = 0;
                voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] = 0;
                voiceData[REDSOUND_VOICE_ENVELOPE_WORD] = 0;
                *(u16*)(voice + REDSOUND_AX_VOICE_VOLUME_OFFSET) = 0;
                *(u16*)(voice + REDSOUND_AX_VOICE_VOLUME_DELTA_OFFSET) = 0;
            } else if ((envChanged != 0) &&
                       ((u32)*(u16*)(voice + REDSOUND_AX_VOICE_VOLUME_OFFSET) !=
                        ((voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT) & 0xFFFFU))) {
                voiceFlags |= AX_SYNC_FLAG_COPYVOL;
                *(u16*)(voice + REDSOUND_AX_VOICE_VOLUME_DELTA_OFFSET) = 0;
                *(s16*)(voice + REDSOUND_AX_VOICE_VOLUME_OFFSET) =
                    (s16)(voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT);
            }

            *(u32*)(voice + REDSOUND_AX_VOICE_SYNC_FLAGS_OFFSET) |= voiceFlags;
        }

        voiceData[REDSOUND_VOICE_FLAGS_WORD] &= REDSOUND_VOICE_FLAGS_EXECUTE_KEEP_MASK;
        voiceData += REDSOUND_VOICE_SIZE / sizeof(*voiceData);
        if ((int*)(p_VoiceData + REDSOUND_VOICE_COUNT) <= voiceData) {
            return;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static void _KeyOnControl()
{
    u32 local_24 = 0;
    u32 local_28 = 0;
    int* reserve = (int*)p_KeyOnData;
    unsigned int* voiceData = (unsigned int*)p_VoiceData;
    int (*waveFunc)(int);

    _VoiceEnvelopeCheck();

    if (m_KeyOnEntry != 0) {
        do {
            if (((u32)*reserve != 0) && (((RedTrackDATA*)*reserve)->m_waveData != 0)) {
                voiceData = (unsigned int*)_VoiceDataSelect((RedTrackDATA*)*reserve, (RedNoteDATA*)(reserve + 1), (int*)&local_28);
            }
            reserve += 2;
        } while ((voiceData != 0) && (reserve < (int*)p_KeyOnData + REDSOUND_KEY_ON_TOTAL_WORD_COUNT));
    }

    if ((p_SoundControlBuffer->m_activeTrackCount != 0) &&
        ((p_SoundControlBuffer->m_flags & REDSOUND_CONTROL_FLAG_PAUSE) == 0)) {
        RedTrackDATA* track = p_SoundControlBuffer->m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                track->m_shakePan =
                    (((track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1) *
                     waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT)) >>
                    0x10;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track <
                 p_SoundControlBuffer->m_tracks + p_SoundControlBuffer->m_trackCount);
    }

    if ((*(s16*)((u8*)p_SoundControlBuffer + REDSOUND_CONTROL_SECONDARY_ACTIVE_TRACK_COUNT_OFFSET) != 0) &&
        ((((u32*)p_SoundControlBuffer)[REDSOUND_CONTROL_SECONDARY_FLAGS_WORD_OFFSET] &
          REDSOUND_CONTROL_FLAG_PAUSE) == 0)) {
        int* track = (int*)((u32*)p_SoundControlBuffer)[REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET];
        u32* trackBase = (u32*)p_SoundControlBuffer + REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET;
        do {
            if (((u32)*track != 0) && (track[REDSOUND_TRACK_SHAKE_FUNC_WORD_OFFSET] != 0)) {
                waveFunc = (int (*)(int))track[REDSOUND_TRACK_SHAKE_FUNC_WORD_OFFSET];
                track[REDSOUND_TRACK_SHAKE_PAN_WORD_OFFSET] =
                    (((track[REDSOUND_TRACK_SHAKE_DEPTH_WORD_OFFSET] >> REDSOUND_FIXED_SHIFT) + 1) *
                     waveFunc((u32)track[REDSOUND_TRACK_SHAKE_OUTPUT_WORD_OFFSET] >> REDSOUND_FIXED_SHIFT)) >>
                    0x10;
                track[REDSOUND_TRACK_SHAKE_OUTPUT_WORD_OFFSET] += track[REDSOUND_TRACK_SHAKE_RATE_WORD_OFFSET];
            }
            track += REDSOUND_TRACK_SIZE / sizeof(*track);
        } while (track < (int*)(*trackBase + (u32) *
                                             ((u8*)p_SoundControlBuffer +
                                              REDSOUND_CONTROL_SECONDARY_TRACK_COUNT_OFFSET) *
                                             REDSOUND_TRACK_SIZE));
    }

    {
        RedTrackDATA* track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                track->m_shakePan =
                    (((track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1) *
                     waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT)) >>
                    0x10;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);
    }

    {
        unsigned int* voice = (unsigned int*)p_VoiceData;
        do {
            if ((voice[REDSOUND_VOICE_ACTIVE_WORD] != 0) && (voice[REDSOUND_VOICE_TRACK_WORD] != 0) &&
                ((((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])->m_voiceSwitch & 9) == 0)) {
                if ((((RedVoiceDATA*)voice)->m_updateFlags & REDSOUND_VOICE_UPDATE_VOLUME) != 0 ||
                    (((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])->m_tremoloFunc != 0) ||
                    (((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])->m_shakeFunc != 0)) {
                    int volume;
                    if (((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD] < p_SoundControlBuffer->m_tracks) ||
                        (p_SoundControlBuffer->m_tracks + p_SoundControlBuffer->m_trackCount <=
                         (RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])) {
                        volume = m_MasterSEVolume;
                        if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks <=
                             (RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD]) &&
                            ((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD] <
                             p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks +
                                 p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_trackCount)) {
                            u32 idx = (u32)((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])->m_trackNo;

                            if (((1U << (idx & REDSOUND_VOICE_INDEX_MASK)) &
                                 m_Mute[((int)idx >> 5) + (u32)((int)idx < 0 && (idx & 0x1F) != 0)]) == 0) {
                                volume = ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_volumeScale + 1) *
                                          (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_volume >>
                                           REDSOUND_FIXED_SHIFT)) >>
                                         7;
                                if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_masterVolumeDelta != 0) {
                                    volume = (volume *
                                              (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_masterVolume >>
                                               REDSOUND_FIXED_SHIFT)) >>
                                             9;
                                }
                                volume = (volume * m_MasterMusicVolume) >> 9;
                            } else {
                                volume = 0;
                            }
                        }
                    } else {
                        u32 idx = (u32)((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])->m_trackNo;
                        if (((1U << (idx & REDSOUND_VOICE_INDEX_MASK)) &
                             m_Mute[((int)idx >> 5) + (u32)((int)idx < 0 && (idx & 0x1F) != 0)]) == 0) {
                            volume = ((p_SoundControlBuffer->m_volumeScale + 1) *
                                      (p_SoundControlBuffer->m_volume >> REDSOUND_FIXED_SHIFT)) >>
                                     7;
                            if (p_SoundControlBuffer->m_masterVolumeDelta != 0) {
                                volume = (volume * (p_SoundControlBuffer->m_masterVolume >> REDSOUND_FIXED_SHIFT)) >> 9;
                            }
                            volume = (volume * m_MasterMusicVolume) >> 9;
                        } else {
                            volume = 0;
                        }
                    }
                    _VolumeExecute((RedVoiceDATA*)voice, volume);
                }

                if ((((RedVoiceDATA*)voice)->m_updateFlags & REDSOUND_VOICE_UPDATE_PITCH) != 0 ||
                    (((RedTrackDATA*)voice[REDSOUND_VOICE_TRACK_WORD])->m_vibrateFunc != 0)) {
                    _PitchExecute((RedVoiceDATA*)voice);
                }
                ((RedVoiceDATA*)voice)->m_updateFlags = 0;
            }
            voice += REDSOUND_VOICE_SIZE / sizeof(*voice);
        } while (voice < (unsigned int*)(p_VoiceData + REDSOUND_VOICE_COUNT));
    }

    {
        u32 bit = 1;
        unsigned int* voice = (unsigned int*)p_VoiceData;
        do {
            if ((local_28 & bit) != 0) {
                local_28 &= ~bit;
                voice[REDSOUND_VOICE_FLAGS_WORD] |= REDSOUND_VOICE_FLAGS_START;
            }
            bit <<= 1;
            voice += REDSOUND_VOICE_SIZE / sizeof(*voice);
        } while (local_28 != 0);
    }

    {
        u32 bit = 1;
        unsigned int* voice = (unsigned int*)p_VoiceData + REDSOUND_VOICE_SECOND_MASK_WORD_OFFSET;
        do {
            if ((local_24 & bit) != 0) {
                local_24 &= ~bit;
                voice[REDSOUND_VOICE_FLAGS_WORD] |= REDSOUND_VOICE_FLAGS_START;
            }
            bit <<= 1;
            voice += REDSOUND_VOICE_SIZE / sizeof(*voice);
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
static void _ExecuteExtraData()
{
    u32* sound = (u32*)p_SoundControlBuffer;
    u32* soundBase;
    RedSoundCONTROL* soundControl;
    RedVoiceDATA* voice;
    RedTrackDATA* track;
    RedTrackDATA* musicBase;

    do {
        soundControl = (RedSoundCONTROL*)sound;
        if ((soundControl->m_masterVolumeDelta != 0) && (*sound != 0)) {
            soundControl->m_masterVolumeDelta--;
            soundControl->m_masterVolume += soundControl->m_masterVolumeAdd;
            if ((soundControl->m_masterVolumeDelta == 0) && (soundControl->m_masterVolumeAdd < 0)) {
                MusicStop(soundControl->m_musicId);
            }

            if (*sound != 0) {
                musicBase = (RedTrackDATA*)*sound;
                voice = p_VoiceData;
                do {
                    if ((musicBase <= voice->m_track) &&
                        (voice->m_track < musicBase + soundControl->m_trackCount)) {
                        voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
                    }
                    voice++;
                } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
            }
        }
        soundBase = (u32*)p_SoundControlBuffer;
        sound += REDSOUND_CONTROL_WORD_COUNT;
    } while (sound < (u32*)p_SoundControlBuffer + REDSOUND_CONTROL_SECONDARY_END_WORD_OFFSET);

    if (p_MusicTempoControl->m_count != 0) {
        p_MusicTempoControl->m_count--;
        p_MusicTempoControl->m_value += p_MusicTempoControl->m_step;
    }

    if (p_MusicPitchControl->m_count != 0) {
        p_MusicPitchControl->m_count--;
        p_MusicPitchControl->m_value += p_MusicPitchControl->m_step;
        voice = p_VoiceData;
        do {
            if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) == 0) {
                voice->m_targetPitch = PitchCompute(
                    voice->m_basePitch + p_MusicPitchControl->m_value,
                    (int)voice->m_track->m_keyTranspose + (int)voice->m_track->m_pitchBend,
                    voice->m_waveData->m_pitch,
                    voice->m_track->m_fineTune);
                voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
            }
            voice++;
        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
    }

    do {
        soundControl = (RedSoundCONTROL*)soundBase;
        if ((soundControl->m_tickCounter != 0) && (soundControl->m_volumeDelta != 0)) {
            soundControl->m_volumeDelta--;
            soundControl->m_volume += soundControl->m_volumeAdd;
            if ((soundControl->m_flags & REDSOUND_CONTROL_FLAG_STOP_ON_VOLUME_ZERO) == 0) {
                track = soundControl->m_tracks;
                do {
                    voice = p_VoiceData;
                    if (track->m_command != 0) {
                        do {
                            if (voice->m_track == track) {
                                voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
                            }
                            voice++;
                        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
                    }
                    track++;
                } while (track < soundControl->m_tracks + soundControl->m_trackCount);
            } else if ((soundControl->m_volumeDelta == 0) && (-1 < soundControl->m_musicId)) {
                MusicStop(soundControl->m_musicId);
            }
        }
        soundBase += REDSOUND_CONTROL_WORD_COUNT;
    } while (soundBase < (u32*)p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_END_WORD_OFFSET);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static void _MusicTrackDataExecute(RedTrackDATA* track, int frames)
{
    u32 updateFlags = 0;
    int* trackData = (int*)track;
    int* voiceData;

    track->m_playTime += frames;

    if (track->m_volumeDelta != 0) {
        int step = frames;
        if (track->m_volumeDelta <= frames) {
            step = track->m_volumeDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_volumeDelta -= step;
        track->m_volume += track->m_volumeAdd * step;
    }

    if (track->m_expressionDelta != 0) {
        int step = frames;
        if (track->m_expressionDelta <= frames) {
            step = track->m_expressionDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_expressionDelta -= step;
        track->m_expression += track->m_expressionAdd * step;
    }

    if (track->m_panDelta != 0) {
        int step = frames;
        if (track->m_panDelta <= frames) {
            step = track->m_panDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_panDelta -= step;
        track->m_pan += track->m_panAdd * step;
    }

    if (track->m_reverbDepthDelta != 0) {
        int step = frames;
        if (track->m_reverbDepthDelta <= frames) {
            step = track->m_reverbDepthDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_reverbDepthDelta -= step;
        track->m_reverbDepth += track->m_reverbDepthAdd * step;
    }

    if (track->m_sweepDelta != 0) {
        int step = frames;
        int addPitch;

        if (track->m_sweepDelta <= frames) {
            step = track->m_sweepDelta;
        }
        updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
        track->m_sweepDelta -= step;
        addPitch = step * track->m_sweepAdd;
        track->m_portamentPitch += addPitch;

        voiceData = (int*)p_VoiceData;
        do {
            if ((RedTrackDATA*)voiceData[REDSOUND_VOICE_TRACK_WORD] == track) {
                voiceData[REDSOUND_VOICE_BASE_PITCH_WORD] += addPitch;
                if (voiceData[REDSOUND_VOICE_WAVE_DATA_WORD] != 0) {
                    voiceData[REDSOUND_VOICE_TARGET_PITCH_WORD] =
                        PitchCompute(voiceData[REDSOUND_VOICE_BASE_PITCH_WORD] + p_MusicPitchControl->m_value,
                                     (int)(s16)track->m_keyTranspose + (int)(s16)track->m_pitchBend,
                                     ((RedWaveDATA*)voiceData[REDSOUND_VOICE_WAVE_DATA_WORD])->m_pitch,
                                     (s8)track->m_fineTune);
                }
            }
            voiceData += REDSOUND_VOICE_SIZE / sizeof(*voiceData);
        } while (voiceData < (int*)(p_VoiceData + REDSOUND_VOICE_COUNT));
    }

    if (track->m_vibrateFunc != 0) {
        if (track->m_vibrateRateDelta != 0) {
            int step = frames;
            if (track->m_vibrateRateDelta <= frames) {
                step = track->m_vibrateRateDelta;
            }
            track->m_vibrateRateDelta -= (s16)step;
            track->m_vibrateRate += track->m_vibrateRateAdd * step;
        }
        if (track->m_vibrateDepthDelta != 0) {
            int step = frames;
            if (track->m_vibrateDepthDelta <= frames) {
                step = track->m_vibrateDepthDelta;
            }
            track->m_vibrateDepthDelta -= (s16)step;
            track->m_vibrateDepth += track->m_vibrateDepthAdd * step;
        }
    }

    if (track->m_tremoloFunc != 0) {
        if (track->m_tremoloRateDelta != 0) {
            int step = frames;
            if (track->m_tremoloRateDelta <= frames) {
                step = track->m_tremoloRateDelta;
            }
            track->m_tremoloRateDelta -= (s16)step;
            track->m_tremoloRate += track->m_tremoloRateAdd * step;
        }
        if (track->m_tremoloDepthDelta != 0) {
            int step = frames;
            if (track->m_tremoloDepthDelta <= frames) {
                step = track->m_tremoloDepthDelta;
            }
            track->m_tremoloDepthDelta -= (s16)step;
            track->m_tremoloDepth += track->m_tremoloDepthAdd * step;
        }
    }

    voiceData = (int*)p_VoiceData;
    if (track->m_shakeFunc != 0) {
        if (track->m_shakeRateDelta != 0) {
            int step = frames;
            if (track->m_shakeRateDelta <= frames) {
                step = track->m_shakeRateDelta;
            }
            track->m_shakeRateDelta -= (s16)step;
            track->m_shakeRate += track->m_shakeRateAdd * step;
        }
        if (track->m_shakeDepthDelta != 0) {
            int step = frames;
            if (track->m_shakeDepthDelta <= frames) {
                step = track->m_shakeDepthDelta;
            }
            track->m_shakeDepthDelta -= (s16)step;
            track->m_shakeDepth += track->m_shakeDepthAdd * step;
        }
    }

    do {
        if (*voiceData == (int)track) {
            if (((RedVoiceDATA*)voiceData)->m_pitchModDelay != 0) {
                int step = frames;
                if (((RedVoiceDATA*)voiceData)->m_pitchModDelay <= frames) {
                    step = ((RedVoiceDATA*)voiceData)->m_pitchModDelay;
                }
                ((RedVoiceDATA*)voiceData)->m_pitchModDelay -= (s16)step;
            }
            if (((RedVoiceDATA*)voiceData)->m_volumeModDelay != 0) {
                int step = frames;
                if (((RedVoiceDATA*)voiceData)->m_volumeModDelay <= frames) {
                    step = ((RedVoiceDATA*)voiceData)->m_volumeModDelay;
                }
                ((RedVoiceDATA*)voiceData)->m_volumeModDelay -= (s16)step;
            }
            ((RedVoiceDATA*)voiceData)->m_updateFlags |= updateFlags;
        }
        voiceData += REDSOUND_VOICE_SIZE / sizeof(*voiceData);
    } while (voiceData < (int*)(p_VoiceData + REDSOUND_VOICE_COUNT));
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
static void _MidiTrackExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    RedTrackDATA* track = control->m_tracks;
    do {
        if (track->m_command != 0) {
            int step = frames;
            m_ChangeStatus = 0;
            if (track->m_deltaTime < frames) {
                step = track->m_deltaTime;
            }
            track->m_deltaTime -= frames;
            _MusicTrackDataExecute(track, step);
            if (((track->m_flags & REDSOUND_TRACK_FLAG_TENUTO) == 0) && (track->m_deltaTime == 1)) {
                KeyOffSet(control, keyOnData, track);
            }
            while ((track->m_command != 0) && (track->m_deltaTime < 1)) {
                unsigned char* cmd = track->m_command;
                int delta;
                track->m_command = cmd + 1;
                p_MidiControl_Function[*cmd](control, keyOnData, track);
                if (track->m_command != 0) {
                    if (track->m_deltaTime < 1) {
                        delta = DeltaTimeSumup((unsigned char**)&track->m_command);
                    } else {
                        delta = track->m_deltaTime;
                        track->m_deltaTime = 0;
                    }

                    if (delta != 0) {
                        delta += track->m_step;
                        if (delta < 1) {
                            delta = 1;
                        } else if ((track->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME) != 0) {
                            delta += ((delta * track->m_fuzzyDeltaTimeDepth >> 8) * (int)GetRandomData()) >> 7;
                            if (delta < 1) {
                                delta = 1;
                            }
                        }
                    }

                    if (track->m_deltaTime < -1) {
                        int execStep = delta;
                        if (track->m_deltaTime + delta > 0) {
                            execStep = -track->m_deltaTime;
                        }
                        _MusicTrackDataExecute(track, execStep);
                    }
                    track->m_deltaTime += delta;
                }
            }

            if (m_ChangeStatus != 0) {
                int* voice = (int*)p_VoiceData;
                do {
                    if ((RedTrackDATA*)*voice == track) {
                        ((RedVoiceDATA*)voice)->m_updateFlags = m_ChangeStatus;
                    }
                    voice += REDSOUND_VOICE_SIZE / sizeof(*voice);
                } while (voice < (int*)(p_VoiceData + REDSOUND_VOICE_COUNT));
            }
        }
        track++;
    } while ((control->m_activeTrackCount != 0) && (track < control->m_tracks + control->m_trackCount));
}


/*
 * --INFO--
 * PAL Address: 0x801c63c4
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MusicMidiNoteExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* tick = &control->m_measure;

    frames <<= m_MusicFastSpeed;
    control->m_loopBase = frames;

    tick[1] += frames;

    while (tick[1] >= tick[2]) {
        tick[0] += 1;
        tick[1] -= tick[2];
    }

    if (control->m_activeTrackCount != 0) {
        _MidiTrackExecute(control, keyOnData, frames);
    }

    control->m_skipFrames = 1;
    if (m_MusicPhraseStop == 0) {
        if ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END) != 0) {
            control->m_flags &= ~REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END;
            if ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) != 0) {
                control->m_activeTrackCount = 0;
            }
        }
    }

    return control->m_activeTrackCount;
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
static void _MusicNoteExecute()
{
    int i;
    u32 trackCount;
    u32* soundControl;
    RedTrackDATA* track;
    int status = _MusicMidiNoteExecute(p_SoundControl, (RedKeyOnDATA*)p_KeyOnData, 1);

    while ((status == 0) && (m_MusicPhraseStop == 0) &&
           ((p_SoundControl->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) != 0)) {
        p_SoundControl->m_activeTrackCount = p_SoundControl->m_savedActiveTrackCount;
        memcpy(&p_SoundControl->m_measure, &p_SoundControl->m_savedMeasure, REDSOUND_CONTROL_SAVED_POSITION_SIZE);
        memcpy(&p_SoundControl->m_tempo, &p_SoundControl->m_savedTempo, REDSOUND_CONTROL_SAVED_TEMPO_SIZE);

        soundControl = (u32*)p_SoundControl;
        track = p_SoundControl->m_tracks;
        trackCount = p_SoundControl->m_trackCount;
        i = 0;
        do {
            track->m_command = (u8*)soundControl[i + REDSOUND_CONTROL_SAVED_COMMAND_WORD_OFFSET];
            track->m_deltaTime = soundControl[i + REDSOUND_CONTROL_SAVED_DELTA_WORD_OFFSET];
            track->m_flags = soundControl[i + REDSOUND_CONTROL_SAVED_FLAGS_WORD_OFFSET];
            *(int*)&track->m_note = soundControl[i + REDSOUND_CONTROL_SAVED_NOTE_WORD_OFFSET];
            track++;
            i++;
        } while (--trackCount != 0);

        status = _MusicMidiNoteExecute(p_SoundControl, (RedKeyOnDATA*)p_KeyOnData, 1);
    }

    if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId < 0) &&
        (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId < 0) &&
        (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId < 0)) {
        m_MusicPhraseStop = 0;
    }
}


/*
 * --INFO--
 * PAL Address: 0x801c6604
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MusicMidiNoteSkipExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* tick = &control->m_measure;
    do {
        control->m_skipFrames = frames;
        control->m_loopBase = frames;
        tick[1] += frames;

        while (tick[1] >= tick[2]) {
            tick[0] += 1;
            tick[1] -= tick[2];
        }

        if (control->m_activeTrackCount != 0) {
            _MidiTrackExecute(control, keyOnData, frames);
        }

        if (m_MusicSkipLine != 0) {
            if ((control->m_activeTrackCount != 0) && ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END) == 0)) {
                m_MusicSkipLine--;
                frames = tick[2];
                RedSleep(1000);
            }
        }

        if (m_MusicSkipLine <= 0) {
            break;
        }
    } while (control->m_activeTrackCount != 0);

    control->m_skipFrames = 1;
    if ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END) != 0) {
        control->m_flags &= ~REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END;
        if ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) != 0) {
            control->m_activeTrackCount = 0;
        }
    }

    return control->m_activeTrackCount;
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
static void _SkipMusicEntry()
{
    int* src;
    int* dst;
    RedSoundCONTROL* soundControl;
    RedControlRamp volume;

    if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId >= 0) {
        src = (int*)p_SkipKeyOn;
        dst = (int*)p_KeyOnData;
        do {
            if ((*src != 0) && (*dst == 0)) {
                *dst = *src;
                dst[1] = src[1];
                m_KeyOnEntry++;
            }
            src += 2;
            dst += 2;
        } while (src < (int*)p_SkipKeyOn + REDSOUND_KEY_ON_PRIORITY_WORD_OFFSET);

        src = (int*)p_SkipKeyOn + REDSOUND_KEY_ON_PRIORITY_WORD_OFFSET;
        for (dst = (int*)p_KeyOnData + REDSOUND_KEY_ON_PRIORITY_WORD_OFFSET;
             (dst < (int*)p_KeyOnData + REDSOUND_KEY_ON_NORMAL_WORD_OFFSET) && (*dst != 0); dst += 2) {
        }
        while ((dst < (int*)p_KeyOnData + REDSOUND_KEY_ON_NORMAL_WORD_OFFSET) &&
               (src < (int*)p_SkipKeyOn + REDSOUND_KEY_ON_NORMAL_WORD_OFFSET)) {
            if (*src != 0) {
                *dst = *src;
                dst[1] = src[1];
                dst += 2;
                m_KeyOnEntry++;
            }
            src += 2;
        }

        src = (int*)p_SkipKeyOn + REDSOUND_KEY_ON_NORMAL_WORD_OFFSET;
        for (dst = (int*)p_KeyOnData + REDSOUND_KEY_ON_NORMAL_WORD_OFFSET;
             (dst < (int*)p_KeyOnData + REDSOUND_KEY_ON_TOTAL_WORD_COUNT) && (*dst != 0); dst += 2) {
        }
        while ((dst < (int*)p_KeyOnData + REDSOUND_KEY_ON_TOTAL_WORD_COUNT) &&
               (src < (int*)p_SkipKeyOn + REDSOUND_KEY_ON_TOTAL_WORD_COUNT)) {
            if (*src != 0) {
                *dst = *src;
                dst[1] = src[1];
                dst += 2;
                m_KeyOnEntry++;
            }
            src += 2;
        }

        soundControl = p_SoundControlBuffer;
        if (soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId != -1) {
            if (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId != -1) {
                MusicStop(soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId);
            }
            memcpy(&soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY], soundControl, REDSOUND_CONTROL_SIZE);
        }

        memcpy(soundControl, &soundControl[REDSOUND_CONTROL_MUSIC_SKIP], REDSOUND_CONTROL_SIZE);
        memcpy(&volume, &soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_volume, sizeof(volume));
        memset(&soundControl[REDSOUND_CONTROL_MUSIC_SKIP], 0, REDSOUND_CONTROL_SIZE);
        memcpy(&soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_volume, &volume, sizeof(volume));
        soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId = -1;
    }

    RedDelete(p_SkipKeyOn);
    m_MusicSkipComplete = 0;
}


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
    int iVar5;
    u32 uVar6;
    int iVar7;
    u32* puVar8;
    RedSoundCONTROL* control;

    do {
        p_SkipKeyOn = (RedKeyOnDATA*)RedNew(REDSOUND_KEY_ON_BUFFER_SIZE);
        if (p_SkipKeyOn == 0) {
            RedSleep(10000);
        }
    } while (p_SkipKeyOn == 0);

    control = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SKIP;
    memset(p_SkipKeyOn, 0, REDSOUND_KEY_ON_BUFFER_SIZE);
    iVar5 = _MusicMidiNoteSkipExecute(control, p_SkipKeyOn, 1);
    while ((iVar5 == 0) && ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) != 0)) {
        control->m_activeTrackCount = control->m_savedActiveTrackCount;
        memcpy(&control->m_measure, &control->m_savedMeasure, REDSOUND_CONTROL_SAVED_POSITION_SIZE);
        memcpy(&control->m_tempo, &control->m_savedTempo, REDSOUND_CONTROL_SAVED_TEMPO_SIZE);
        puVar8 = (u32*)control->m_tracks;
        iVar7 = (int)control + 0x28;
        uVar6 = control->m_trackCount;
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
            puVar8 += REDSOUND_TRACK_SIZE / sizeof(*puVar8);
        } while (uVar6 != 0);
        iVar5 = _MusicMidiNoteSkipExecute(control, p_SkipKeyOn, 1);
    }
    m_MusicSkipComplete = 1;
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
static void _SeTrackDataExecute(RedTrackDATA* track, int frames)
{
	RedVoiceDATA* voice;
	int step;

	if ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_STREAM) != 0) {
		return;
	}

	voice = p_VoiceData + track->m_trackNo;
	if (0 < frames) {
		track->m_playTime += frames;
	}

	if (track->m_volumeDelta != 0) {
		step = frames;
		if (track->m_volumeDelta <= frames) {
			step = track->m_volumeDelta;
		}
		track->m_volumeDelta -= step;
		track->m_volume += track->m_volumeAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_expressionDelta != 0) {
		step = frames;
		if (track->m_expressionDelta <= frames) {
			step = track->m_expressionDelta;
		}
		track->m_expressionDelta -= step;
		track->m_expression += track->m_expressionAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_panDelta != 0) {
		step = frames;
		if (track->m_panDelta <= frames) {
			step = track->m_panDelta;
		}
		track->m_panDelta -= step;
		track->m_pan += track->m_panAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_reverbDepthDelta != 0) {
		step = frames;
		if (track->m_reverbDepthDelta <= frames) {
			step = track->m_reverbDepthDelta;
		}
		track->m_reverbDepthDelta -= step;
		track->m_reverbDepth += track->m_reverbDepthAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_mixVolumeDelta != 0) {
		step = frames;
		if (track->m_mixVolumeDelta <= frames) {
			step = track->m_mixVolumeDelta;
		}
		track->m_mixVolumeDelta -= step;
		if ((track->m_mixVolumeDelta == 0) && (track->m_mixVolumeMode == 1)) {
			track->m_command = (u8*)m_TerminateNote;
			track->m_deltaTime = 1;
		}
		track->m_mixVolume += track->m_mixVolumeAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_pitchDelta != 0) {
		step = frames;
		if (track->m_pitchDelta <= frames) {
			step = track->m_pitchDelta;
		}
		track->m_pitchDelta -= step;
		track->m_pitch += track->m_pitchAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
	}

	if (track->m_sweepDelta != 0) {
		step = frames;
		if (track->m_sweepDelta <= frames) {
			step = track->m_sweepDelta;
		}
		track->m_sweepDelta -= step;
		track->m_portamentPitch += step * track->m_sweepAdd;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
		voice->m_basePitch += step * track->m_sweepAdd;
	}

	if (((voice->m_updateFlags & REDSOUND_VOICE_UPDATE_PITCH) != 0) && (voice->m_waveData != 0)) {
		voice->m_targetPitch =
			PitchCompute(voice->m_basePitch + track->m_pitch,
			             (int)(s16)track->m_keyTranspose + (int)(s16)track->m_pitchBend,
			             voice->m_waveData->m_pitch, (int)(s8)track->m_fineTune);
	}

	if (track->m_vibrateFunc != 0) {
		if (track->m_vibrateRateDelta != 0) {
			step = frames;
			if (track->m_vibrateRateDelta <= frames) {
				step = track->m_vibrateRateDelta;
			}
			track->m_vibrateRateDelta = track->m_vibrateRateDelta - (short)step;
			track->m_vibrateRate += track->m_vibrateRateAdd * step;
		}
		if (track->m_vibrateDepthDelta != 0) {
			step = frames;
			if (track->m_vibrateDepthDelta <= frames) {
				step = track->m_vibrateDepthDelta;
			}
			track->m_vibrateDepthDelta = track->m_vibrateDepthDelta - (short)step;
			track->m_vibrateDepth += track->m_vibrateDepthAdd * step;
		}
	}

	if (track->m_tremoloFunc != 0) {
		if (track->m_tremoloRateDelta != 0) {
			step = frames;
			if (track->m_tremoloRateDelta <= frames) {
				step = track->m_tremoloRateDelta;
			}
			track->m_tremoloRateDelta = track->m_tremoloRateDelta - (short)step;
			track->m_tremoloRate += track->m_tremoloRateAdd * step;
		}
		if (track->m_tremoloDepthDelta != 0) {
			step = frames;
			if (track->m_tremoloDepthDelta <= frames) {
				step = track->m_tremoloDepthDelta;
			}
			track->m_tremoloDepthDelta = track->m_tremoloDepthDelta - (short)step;
			track->m_tremoloDepth += track->m_tremoloDepthAdd * step;
		}
	}

	if (track->m_shakeFunc != 0) {
		if (track->m_shakeRateDelta != 0) {
			step = frames;
			if (track->m_shakeRateDelta <= frames) {
				step = track->m_shakeRateDelta;
			}
			track->m_shakeRateDelta = track->m_shakeRateDelta - (short)step;
			track->m_shakeRate += track->m_shakeRateAdd * step;
		}
		if (track->m_shakeDepthDelta != 0) {
			step = frames;
			if (track->m_shakeDepthDelta <= frames) {
				step = track->m_shakeDepthDelta;
			}
			track->m_shakeDepthDelta = track->m_shakeDepthDelta - (short)step;
			track->m_shakeDepth += track->m_shakeDepthAdd * step;
		}
	}

	if (voice->m_pitchModDelay != 0) {
		step = frames;
		if (voice->m_pitchModDelay <= frames) {
			step = voice->m_pitchModDelay;
		}
		voice->m_pitchModDelay = voice->m_pitchModDelay - (short)step;
	}

	if (voice->m_volumeModDelay != 0) {
		step = frames;
		if (voice->m_volumeModDelay <= frames) {
			step = voice->m_volumeModDelay;
		}
		voice->m_volumeModDelay = voice->m_volumeModDelay - (short)step;
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
static int _SeMidiNoteExecute(
    RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* trackData, int frames, int tickStep)
{
    RedTrackDATA* track = trackData;
    do {
        if ((track->m_command != 0) && ((track->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAUSE) == 0)) {
            track->m_seTickCounter += (s16)(tickStep * -REDSOUND_SE_TICK_STEP);
            while (track->m_seTickCounter < 1) {
                int step = frames;
                track->m_seTickCounter += REDSOUND_CONTROL_TICK_PERIOD;
                if (track->m_deltaTime < frames) {
                    step = track->m_deltaTime;
                }
                track->m_deltaTime -= frames;
                _SeTrackDataExecute(track, step);
                if (((track->m_flags & REDSOUND_TRACK_FLAG_TENUTO) == 0) && (track->m_deltaTime == 1)) {
                    KeyOffSet(control, keyOnData, track);
                }

                m_ChangeStatus = 0;
                while ((track->m_command != 0) && (track->m_deltaTime < 1)) {
                    int delta;
                    unsigned char* cmd;
                    track->m_loopStepCurrent += 1;
                    cmd = track->m_command;
                    track->m_command = cmd + 1;
                    p_MidiControl_Function[*cmd](control, keyOnData, track);
                    if (track->m_command != 0) {
                        delta = DeltaTimeSumup((unsigned char**)&track->m_command);
                        if (delta != 0) {
                            delta += track->m_step;
                            if (delta < 1) {
                                delta = 1;
                            } else if ((track->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME) != 0) {
                                delta += ((delta * track->m_fuzzyDeltaTimeDepth >> 8) * (int)GetRandomData()) >>
                                    7;
                                if (delta < 1) {
                                    delta = 1;
                                }
                            }
                        }

                        if (track->m_deltaTime < -1) {
                            int execStep = delta;
                            if (track->m_deltaTime + delta > 0) {
                                execStep = -track->m_deltaTime;
                            }
                            _SeTrackDataExecute(track, execStep);
                        }
                        track->m_deltaTime += delta;
                    }
                }

                if (m_ChangeStatus != 0) {
                    (p_VoiceData + track->m_trackNo)->m_updateFlags = m_ChangeStatus;
                }
            }
        }
        track++;
    } while (track < control->m_tracks + REDSOUND_SE_TRACK_COUNT);
    control->m_updateFlags = 1;
    return control->m_tickCounter;
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
    m_KeyOnEntry = 0;
    memset(p_KeyOnData, 0, REDSOUND_KEY_ON_BUFFER_SIZE);

    p_SoundControl = p_SoundControlBuffer + REDSOUND_CONTROL_SE;
    _SeMidiNoteExecute((RedSoundCONTROL*)p_SoundControl, (RedKeyOnDATA*)p_KeyOnData,
                       p_SoundControl->m_tracks, p_SoundControl->m_skipFrames, frames);
    p_SoundControl = p_SoundControlBuffer;

    if (p_SoundControl->m_activeTrackCount != 0) {
        if ((p_SoundControl->m_flags & REDSOUND_CONTROL_FLAG_PAUSE) == 0) {
            mul = ((u32)p_MusicTempoControl->m_value >> REDSOUND_FIXED_SHIFT) & REDSOUND_TEMPO_SCALE_MASK;
            step = p_SoundControl->m_tempo >> REDSOUND_FIXED_SHIFT;
            if (mul != 0) {
                if (p_MusicTempoControl->m_value < 0) {
                    step *= (int)mul;
                    step >>= 0x10;
                } else {
                    step *= (int)mul + 1;
                    step >>= 0xF;
                    step += p_SoundControl->m_tempo >> REDSOUND_FIXED_SHIFT;
                }
            }
            ((RedSoundCONTROL*)p_SoundControl)->m_tickCounter -= step * frames;
            while (((RedSoundCONTROL*)p_SoundControl)->m_tickCounter < 1) {
                ((RedSoundCONTROL*)p_SoundControl)->m_tickCounter += REDSOUND_CONTROL_TICK_PERIOD;
                _MusicNoteExecute();
            }
        }
    }

    if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount != 0) {
        p_SoundControl = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY;
        step = p_SoundControl->m_tempo >> REDSOUND_FIXED_SHIFT;
        ((RedSoundCONTROL*)p_SoundControl)->m_tickCounter -= step * frames;
        while (((RedSoundCONTROL*)p_SoundControl)->m_tickCounter < 1) {
            ((RedSoundCONTROL*)p_SoundControl)->m_tickCounter += REDSOUND_CONTROL_TICK_PERIOD;
            _MusicNoteExecute();
        }
        if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_activeTrackCount == 0) {
            memcpy(p_SoundControlBuffer, p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY, REDSOUND_CONTROL_SIZE);
            p_SoundControl->m_activeTrackCount = 0;
            p_SoundControl->m_trackCount = 0;
            p_SoundControl->m_musicId = -1;
        }
        p_SoundControl = p_SoundControlBuffer;
    }

    _ExecuteExtraData();
    if (m_MusicSkipComplete != 0) {
        _SkipMusicEntry();
    }
}
