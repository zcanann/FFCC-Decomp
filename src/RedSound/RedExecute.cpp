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
u32 m_TerminateNote[REDSOUND_TERMINATE_NOTE_WORD_COUNT] = { 0 };
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

enum RedReverbDelayChannelIndex {
    REDSOUND_REVERB_DELAY_LEFT = 0,
    REDSOUND_REVERB_DELAY_RIGHT = 1,
    REDSOUND_REVERB_DELAY_SURROUND = 2,
};

enum RedExecuteAxVoiceLayout {
    REDSOUND_AX_VOICE_LOOP_OFFSET = 0x148,
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

enum RedExecuteAdsrStateIndex {
    REDSOUND_ADSR_STATE_STAGE = 0,
    REDSOUND_ADSR_STATE_STEP_FRAMES = 1,
    REDSOUND_ADSR_STATE_STEP_ADD = 2,
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
	signed char* data = t_RandomData + m_RandomIndex;
	m_RandomIndex++;
	return *data;
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
    pitch = (basePitch >> REDSOUND_FIXED_SHIFT) + (pitchOffset + (wavePitch >> 16));
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
    switch (reverb->m_kind) {
    case REDSOUND_REVERB_KIND_STD: {
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)reverb->m_context;
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
        AXFX_REVERBHI* hi = (AXFX_REVERBHI*)reverb->m_context;
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
        AXFX_DELAY* delay = (AXFX_DELAY*)reverb->m_context;
        u32 delayValue = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->delay[REDSOUND_REVERB_DELAY_SURROUND] = delayValue;
        delay->delay[REDSOUND_REVERB_DELAY_RIGHT] = delayValue;
        delay->delay[REDSOUND_REVERB_DELAY_LEFT] = delayValue;
        delayValue = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->feedback[REDSOUND_REVERB_DELAY_SURROUND] = delayValue;
        delay->feedback[REDSOUND_REVERB_DELAY_RIGHT] = delayValue;
        delay->feedback[REDSOUND_REVERB_DELAY_LEFT] = delayValue;
        delayValue = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        delay->output[REDSOUND_REVERB_DELAY_SURROUND] = delayValue;
        delay->output[REDSOUND_REVERB_DELAY_RIGHT] = delayValue;
        delay->output[REDSOUND_REVERB_DELAY_LEFT] = delayValue;
        result = AXFXDelaySettings(delay);
        break;
    }
    case REDSOUND_REVERB_KIND_CHORUS: {
        AXFX_CHORUS* chorus = (AXFX_CHORUS*)reverb->m_context;
        chorus->baseDelay = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_BASE_DELAY];
        chorus->variation = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_VARIATION];
        chorus->period = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_PERIOD];
        result = AXFXChorusSettings(chorus);
        break;
    }
    case REDSOUND_REVERB_KIND_HI_DPL2: {
        AXFX_REVERBHI_DPL2* hiDpl2 = (AXFX_REVERBHI_DPL2*)reverb->m_context;
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
    if (reverb->m_callback == 0) {
        return;
    }

    if (bank == 0) {
        AXRegisterAuxACallback((void (*)(void*, void*))_ReverbNullCallback, 0);
    } else {
        AXRegisterAuxBCallback((void (*)(void*, void*))_ReverbNullCallback, 0);
    }

    switch (reverb->m_kind) {
    case REDSOUND_REVERB_KIND_STD:
        AXFXReverbStdShutdown((AXFX_REVERBSTD*)reverb->m_context);
        break;
    case REDSOUND_REVERB_KIND_HI:
        AXFXReverbHiShutdown((AXFX_REVERBHI*)reverb->m_context);
        break;
    case REDSOUND_REVERB_KIND_DELAY:
        AXFXDelayShutdown((AXFX_DELAY*)reverb->m_context);
        break;
    case REDSOUND_REVERB_KIND_CHORUS:
        AXFXChorusShutdown((AXFX_CHORUS*)reverb->m_context);
        break;
    case REDSOUND_REVERB_KIND_HI_DPL2:
        AXFXReverbHiShutdownDpl2((AXFX_REVERBHI_DPL2*)reverb->m_context);
        break;
    }

    reverb->m_callback = 0;
    RedDelete((int)reverb->m_context);
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
    if ((reverb->m_callback != 0) && (reverb->m_kind == kind)) {
        _SetReverbData(reverb, params);
        return (int*)p_ReverbSize;
    }

    _ClearReverb(bank);
    if (kind == REDSOUND_REVERB_KIND_HI_DPL2) {
        _ClearReverb(1);
    }

    reverb->m_kind = kind;
    switch (kind) {
    case REDSOUND_REVERB_KIND_STD: {
        reverb->m_context = (void*)RedNew(sizeof(AXFX_REVERBSTD));
        reverb->m_callback = (int)AXFXReverbStdCallback;
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)reverb->m_context;
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
        reverb->m_context = (void*)RedNew(sizeof(AXFX_REVERBHI));
        reverb->m_callback = (int)AXFXReverbHiCallback;
        AXFX_REVERBHI* hi = (AXFX_REVERBHI*)reverb->m_context;
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
        reverb->m_context = (void*)RedNew(sizeof(AXFX_DELAY));
        reverb->m_callback = (int)AXFXDelayCallback;
        AXFX_DELAY* delay = (AXFX_DELAY*)reverb->m_context;
        u32 delayValue = (u32)params[REDSOUND_REVERB_PARAM_DELAY];
        delay->delay[REDSOUND_REVERB_DELAY_SURROUND] = delayValue;
        delay->delay[REDSOUND_REVERB_DELAY_RIGHT] = delayValue;
        delay->delay[REDSOUND_REVERB_DELAY_LEFT] = delayValue;
        delayValue = (u32)params[REDSOUND_REVERB_PARAM_FEEDBACK];
        delay->feedback[REDSOUND_REVERB_DELAY_SURROUND] = delayValue;
        delay->feedback[REDSOUND_REVERB_DELAY_RIGHT] = delayValue;
        delay->feedback[REDSOUND_REVERB_DELAY_LEFT] = delayValue;
        delayValue = (u32)params[REDSOUND_REVERB_PARAM_OUTPUT];
        delay->output[REDSOUND_REVERB_DELAY_SURROUND] = delayValue;
        delay->output[REDSOUND_REVERB_DELAY_RIGHT] = delayValue;
        delay->output[REDSOUND_REVERB_DELAY_LEFT] = delayValue;
        result = AXFXDelayInit(delay);
        break;
    }
    case REDSOUND_REVERB_KIND_CHORUS: {
        reverb->m_context = (void*)RedNew(sizeof(AXFX_CHORUS));
        reverb->m_callback = (int)AXFXChorusCallback;
        AXFX_CHORUS* chorus = (AXFX_CHORUS*)reverb->m_context;
        chorus->baseDelay = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_BASE_DELAY];
        chorus->variation = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_VARIATION];
        chorus->period = (u32)params[REDSOUND_REVERB_PARAM_CHORUS_PERIOD];
        result = AXFXChorusInit(chorus);
        break;
    }
    case REDSOUND_REVERB_KIND_HI_DPL2: {
        reverb->m_context = (void*)RedNew(sizeof(AXFX_REVERBHI_DPL2));
        reverb->m_callback = (int)AXFXReverbHiCallbackDpl2;
        AXFX_REVERBHI_DPL2* hiDpl2 = (AXFX_REVERBHI_DPL2*)reverb->m_context;
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
            AXRegisterAuxACallback((void (*)(void*, void*))reverb->m_callback, reverb->m_context);
        }
        else {
            AXRegisterAuxBCallback((void (*)(void*, void*))reverb->m_callback, reverb->m_context);
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
    RedTrackDATA* trackData = voice->m_track;
    s16 leftPan;
    s16 rightPan;
    u16 uVar3;
    int volFactor;
    AXPBMIX* mixData;

    if (trackData == 0) {
        return;
    }

    mixData = &voice->m_axMix;
    memset(mixData, 0, sizeof(*mixData));

    switch (m_SoundPlayMode) {
    case 1:
        volFactor = (int)t_PanningData[REDSOUND_PAN_BYTE_CENTER];
        int monoBase = (volume * volFactor) >> 8;

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_STEREO) != 0) {
            uVar3 = (u16)monoBase;
            mixData->vL = uVar3;
            mixData->vR = uVar3;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_STEREO) != 0) {
            u16 monoMix = (u16)((monoBase * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT);
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData->vAuxAL = monoMix;
                mixData->vAuxAR = monoMix;
            } else {
                mixData->vAuxBL = monoMix;
                mixData->vAuxBR = monoMix;
            }
        }
        break;
    case 2:
        mixData->vL = (u16)((volume * t_PanningData[pan]) >> 8);
        mixData->vAuxBL = (u16)((volume * t_PanningDataR[pan]) >> 8);
        mixData->vR = (u16)((volume * t_PanningData[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8);
        mixData->vAuxBR = (u16)((volume * t_PanningDataR[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8);

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_LEFT) != 0) {
            mixData->vAuxAL =
                (s16)((int)((u32)mixData->vL * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT);
            mixData->vAuxAS =
                (u16)((int)((u32)mixData->vAuxBL *
                             ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >>
                      REDSOUND_AX_MIX_SHIFT);
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_RIGHT) != 0) {
            mixData->vAuxAR =
                (u16)((int)((u32)mixData->vR *
                             ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >>
                      REDSOUND_AX_MIX_SHIFT);
            mixData->vAuxBS =
                (u16)((int)((u32)mixData->vAuxBR *
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
            mixData->vL = (u16)leftMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_RIGHT) != 0) {
            mixData->vR = (u16)rightMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_LEFT) != 0) {
            iVar1 = (leftMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData->vAuxAL = (u16)iVar1;
            } else {
                mixData->vAuxBL = (u16)iVar1;
            }
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_RIGHT) != 0) {
            iVar2 = (rightMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData->vAuxAR = (u16)iVar2;
            } else {
                mixData->vAuxBR = (u16)iVar2;
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

    if (volume != 0) {
        volume = volume + 1;
    }

    voiceMix = volume * ((*voice->m_trackExpression >> REDSOUND_FIXED_SHIFT) + 1) >>
               REDSOUND_VOLUME_MOD_SCALE_SHIFT;

    if (voice->m_velocity != 0) {
        if (voice->m_velocity != 0) {
            envelopeMul = voice->m_velocity + 1;
        } else {
            envelopeMul = 0;
        }
        voiceMix = voiceMix * envelopeMul >> 7;
    }

    envelopeMul = voice->m_track->m_mixVolume >> REDSOUND_FIXED_SHIFT;
    if (envelopeMul != 0) {
        envelopeMul = envelopeMul + 1;
    }

    voiceMix = voiceMix * envelopeMul >> REDSOUND_VOLUME_MOD_SCALE_SHIFT;
    voiceMix = voiceMix * (*voice->m_trackVolume >> REDSOUND_FIXED_SHIFT) >> REDSOUND_VOLUME_TRACK_SCALE_SHIFT;
    pan = voice->m_waveData->m_volume & REDSOUND_PAN_BYTE_MASK;
    if (pan != 0) {
        pan = pan + 1;
    }
    voiceMix = voiceMix * pan >> REDSOUND_VOLUME_MOD_SCALE_SHIFT;

    if (voice->m_track->m_tremoloFunc != 0) {
        if (voice->m_volumeModDelay == 0) {
            envelopeMul = voice->m_track->m_tremoloDepth >> REDSOUND_FIXED_SHIFT;
            if (envelopeMul != 0) {
                envelopeMul = envelopeMul + 1;
            }

            modVolume = voiceMix * envelopeMul >> 8;
            iVar1 = voice->m_track->m_tremoloFunc((unsigned int)voice->m_volumeModPhase >> REDSOUND_FIXED_SHIFT);
            modVolume = modVolume * (iVar1 >> REDSOUND_VOLUME_MOD_WAVE_SHIFT) >> REDSOUND_FIXED_SHIFT;

            if (voice->m_volumeModFrames != 0) {
                iVar1 = voice->m_volumeModFrame;
                voice->m_volumeModFrame = voice->m_volumeModFrame + 1;
                modVolume = (modVolume * iVar1) / voice->m_volumeModFrames;
                if (voice->m_volumeModFrame >= voice->m_volumeModFrames) {
                    voice->m_volumeModFrames = 0;
                }
            }

            voiceMix = voiceMix + modVolume;
            voice->m_volumeModPhase = voice->m_volumeModPhase + voice->m_track->m_tremoloRate;

            if (voiceMix > REDSOUND_AX_MIX_MAX) {
                voiceMix = REDSOUND_AX_MIX_MAX;
            } else if (voiceMix < 0) {
                voiceMix = 0;
            }
        }
    }

    if (m_SoundPlayMode == 1) {
        pan = REDSOUND_PAN_BYTE_CENTER;
    } else if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAIRED_PAN) != 0) {
        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAIRED_LEFT) != 0) {
            pan = 0;
        } else {
            pan = REDSOUND_PAN_BYTE_MASK;
        }
    } else {
        if ((voice->m_waveData->m_pan & REDSOUND_PAN_BYTE_SIGN_BIT) != 0) {
            pan = voice->m_waveData->m_pan & REDSOUND_PAN_BYTE_MASK;
            if (pan == 0) {
                pan = REDSOUND_PAN_BYTE_CENTER;
            }
        } else {
            pan = *voice->m_trackPan >> REDSOUND_FIXED_SHIFT;
        }

        if (voice->m_randomPan != 0) {
            pan = pan + ((int)(pan * voice->m_randomPan) >> REDSOUND_VOLUME_MOD_SCALE_SHIFT);
        }

        pan = pan + voice->m_track->m_shakePan;
        pan &= 0xff;
    }

    if (voice->m_randomVolume != 0) {
        voiceMix =
            voiceMix + (voiceMix * voice->m_randomVolume >> REDSOUND_VOLUME_MOD_SCALE_SHIFT);
        if (voiceMix > REDSOUND_AX_MIX_MAX) {
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
    int targetPitchDelta;

    if ((voice->m_track->m_vibrateFunc != 0) && (voice->m_pitchModDelay == 0)) {
        u32 pitchLfo = voice->m_track->m_vibrateDepth >> REDSOUND_FIXED_SHIFT;
        if (pitchLfo < REDSOUND_PITCH_MOD_DEPTH_SPLIT) {
            pitchDelta = (pitchLfo + 1) * REDSOUND_PITCH_MOD_SHALLOW_SCALE;
        } else {
            pitchDelta = ((pitchLfo & REDSOUND_PAN_BYTE_MASK) + 1) * REDSOUND_PITCH_MOD_DEEP_SCALE;
        }

        int pitchBend = voice->m_track->m_keyTranspose + voice->m_track->m_pitchBend + pitchDelta;
        int basePitch;
        if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0) {
            basePitch = voice->m_basePitch + voice->m_track->m_pitch;
        } else {
            basePitch = voice->m_basePitch + p_MusicPitchControl->m_value;
        }
        pitchDelta = PitchCompute(basePitch, pitchBend, voice->m_waveData->m_pitch, voice->m_track->m_fineTune);

        pitchDelta =
            ((pitchDelta - voice->m_pitch) *
             (voice->m_track->m_vibrateFunc((u32)voice->m_pitchModPhase >> REDSOUND_FIXED_SHIFT) >> REDSOUND_PITCH_MOD_WAVE_SHIFT)) >>
            REDSOUND_FIXED_SHIFT;

        if (voice->m_pitchModFrames != 0) {
            int frame = voice->m_pitchModFrame;
            int rampedPitch = pitchDelta * frame;
            voice->m_pitchModFrame = voice->m_pitchModFrame + 1;
            pitchDelta = rampedPitch / voice->m_pitchModFrames;
            if (voice->m_pitchModFrame >= voice->m_pitchModFrames) {
                voice->m_pitchModFrames = 0;
            }
        }

        targetPitchDelta = pitchDelta;
        if (pitchDelta < 0) {
            targetPitchDelta = pitchDelta >> 1;
        }

        voice->m_pitchModPhase += voice->m_track->m_vibrateRate;
        pitchDelta = targetPitchDelta;
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
static void _VoiceDataAsign(RedTrackDATA* track, RedVoiceDATA* voice, RedNoteDATA* noteData, int* voiceMask)
{
    int iVar1;
    int iVar5;
    int pitchWork[4];

    voice->m_track = track;
    voice->m_active = 1;

    if ((track->m_portamentTime != 0) &&
        (track->m_portamentPitch >= 0)) {
        track->m_portamentPitch &= REDSOUND_FIXED_WHOLE_MASK;
        voice->m_basePitch = track->m_portamentPitch;
        track->m_sweepDelta = track->m_portamentTime;
        pitchWork[0] = 0;
        track->m_sweepAdd =
            DataAddCompute(pitchWork, noteData->m_key * REDSOUND_PITCH_NOTE_UNIT -
                                          (track->m_portamentPitch >> REDSOUND_FIXED_SHIFT),
                           &track->m_sweepDelta);
    } else {
        track->m_portamentPitch = noteData->m_key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
        if (voice->m_waveData != 0) {
            if ((voice->m_waveData->m_flags & REDSOUND_WAVE_FLAG_USE_WAVE_KEY) == 0) {
                voice->m_basePitch = noteData->m_key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
                if (track->m_keySignatureData != 0) {
                    iVar5 = voice->m_basePitch >> REDSOUND_PITCH_BASE_NOTE_SHIFT;
                    iVar1 = iVar5 / REDSOUND_NOTES_PER_OCTAVE + (voice->m_basePitch >> 0x1f);
                    pitchWork[0] =
                        track->m_keySignatureData[iVar5 + (iVar1 - (iVar1 >> 0x1f)) * -REDSOUND_NOTES_PER_OCTAVE];
                    voice->m_basePitch += pitchWork[0] * REDSOUND_PITCH_KEY_SIGNATURE_UNIT;
                }
            } else {
                voice->m_basePitch =
                    voice->m_waveData->m_splitKey << REDSOUND_PITCH_BASE_NOTE_SHIFT;
            }
        }
    }

    *(int*)&voice->m_key = *(int*)noteData;
    voice->m_trackVolume = &track->m_volume;
    voice->m_trackExpression = &track->m_expression;
    voice->m_trackPan = &track->m_pan;

    if (voice->m_waveData == 0) {
        memset(voice->m_adsrTime, 0, REDSOUND_TRACK_ADSR_SIZE);
    } else {
        memcpy(voice->m_adsrTime,
               track->m_waveData->m_adsr,
               REDSOUND_TRACK_ADSR_SIZE);
    }

    voice->m_voiceSwitch = track->m_voiceSwitch;
    if (voice->m_waveData != 0 &&
        voice->m_waveData->m_reverbMix != 0) {
        unsigned int maskBits;
        voice->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_MIX_MASK;
        if (voice->m_waveData->m_reverbMix == 1) {
            maskBits = REDSOUND_VOICE_SWITCH_MIX_ALL;
        } else {
            maskBits = REDSOUND_VOICE_SWITCH_DRY_STEREO;
        }
        voice->m_voiceSwitch |= maskBits;
    }

    pitchWork[0] = track->m_keyTranspose + track->m_pitchBend;
    if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) == 0) {
        iVar5 = voice->m_basePitch + p_MusicPitchControl->m_value;
    } else {
        iVar5 = voice->m_basePitch + track->m_pitch;
    }

    if (voice->m_waveData == 0) {
        iVar5 = 0;
    } else {
        iVar5 = PitchCompute(iVar5, pitchWork[0], voice->m_waveData->m_pitch, track->m_fineTune);
    }
    voice->m_pitch = iVar5;

    if ((track->m_flags & REDSOUND_TRACK_FLAG_SLUR_RELEASE) != 0) {
        if ((((s8)track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) == 0) ||
            ((track->m_flags & (REDSOUND_TRACK_FLAG_SLUR | REDSOUND_TRACK_FLAG_TENUTO)) != 0)) {
            if ((((s8)track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) != 0) ||
                ((track->m_flags & REDSOUND_TRACK_FLAG_SLUR) != 0)) {
                goto skipModSetup;
            }
        }
    }

    if (voice->m_track->m_vibrateFunc != 0) {
        voice->m_pitchModDelay = track->m_vibrateDelay;
        pitchWork[0] = REDSOUND_MOD_DELAY_PHASE_SCALE;
        if ((track->m_vibrateRate >> REDSOUND_FIXED_SHIFT) != 0) {
            pitchWork[0] =
                REDSOUND_MOD_DELAY_PHASE_SCALE / (track->m_vibrateRate >> REDSOUND_FIXED_SHIFT);
        }
        if (track->m_vibrateDelayDepth == 0) {
            iVar5 = 0;
        } else {
            iVar5 = track->m_vibrateDelayDepth * (pitchWork[0] * REDSOUND_MOD_DELAY_FRAME_SCALE);
        }
        voice->m_pitchModFrames = iVar5;
        voice->m_pitchModFrame = 0;
        voice->m_pitchModPhase = 0;
    }

    if (voice->m_track->m_tremoloFunc != 0) {
        voice->m_volumeModDelay = track->m_tremoloDelay;
        pitchWork[0] = REDSOUND_MOD_DELAY_PHASE_SCALE;
        if ((track->m_tremoloRate >> REDSOUND_FIXED_SHIFT) != 0) {
            pitchWork[0] =
                REDSOUND_MOD_DELAY_PHASE_SCALE / (track->m_tremoloRate >> REDSOUND_FIXED_SHIFT);
        }
        if (track->m_tremoloDelayDepth == 0) {
            iVar5 = 0;
        } else {
            iVar5 = track->m_tremoloDelayDepth * (pitchWork[0] * REDSOUND_MOD_DELAY_FRAME_SCALE);
        }
        voice->m_volumeModFrames = iVar5;
        voice->m_volumeModFrame = 0;
        voice->m_volumeModPhase = 0;
    }

skipModSetup:

    if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_PITCH) != 0) {
        unsigned int random = GetRandomData();
        iVar5 = ((int)(random & REDSOUND_RANDOM_BYTE_MASK) + 1) *
                (voice->m_pitch * voice->m_track->m_fuzzyPitchDepth);
        pitchWork[0] = iVar5 >> REDSOUND_RANDOM_FUZZY_PITCH_SHIFT;
        if ((random & REDSOUND_RANDOM_BYTE_SIGN_BIT) == 0) {
            voice->m_randomPitch = pitchWork[0];
        } else {
            voice->m_randomPitch = -(pitchWork[0] >> 1);
        }
    } else {
        voice->m_randomPitch = 0;
    }

    if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_VOLUME) != 0) {
        s8 random = (s8)GetRandomData();
        voice->m_randomVolume =
            (track->m_fuzzyVolumeDepth * random) >> REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT;
    } else {
        voice->m_randomVolume = 0;
    }

    if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_PAN) != 0) {
        s8 random = (s8)GetRandomData();
        voice->m_randomPan =
            (track->m_fuzzyPanDepth * random) >> REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT;
    } else {
        voice->m_randomPan = 0;
    }

    if (voice->m_waveData != 0) {
        memcpy(voice->m_adsrTime,
               voice->m_waveData->m_adsr,
               REDSOUND_TRACK_ADSR_SIZE);
        if ((s8)track->m_adsrAL != -1) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_ATTACK] =
                track->m_adsrAL;
        }
        if ((s16)track->m_adsrAR != -1) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_ATTACK] =
                track->m_adsrAR;
        }
        if ((s8)track->m_adsrDL != -1) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_DECAY] =
                track->m_adsrDL;
        }
        if ((s16)track->m_adsrDR != -1) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_DECAY] =
                track->m_adsrDR;
        }
        if ((s8)track->m_adsrSL != -1) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_SUSTAIN] =
                track->m_adsrSL;
        }
        if ((s16)track->m_adsrSR != -1) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_SUSTAIN] =
                track->m_adsrSR;
        }
        if ((s8)track->m_adsrRL != -1) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_RELEASE] =
                track->m_adsrRL;
        }
        if ((s16)track->m_adsrRR != -1) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_RELEASE] =
                track->m_adsrRR;
        }
        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_ADSR) != 0) {
            u16 random = GetRandomData();
            u16 attack = (u16)(track->m_fuzzyAdsrDepth *
                               (random & REDSOUND_RANDOM_BYTE_MASK));
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_ATTACK] = attack;
        }
    } else {
        memset(voice->m_adsrTime, 0, REDSOUND_TRACK_ADSR_SIZE);
    }

    iVar5 = ((int)voice - (int)p_VoiceData) / REDSOUND_VOICE_SIZE;
    if (REDSOUND_VOICE_INDEX_MASK < iVar5) {
        voiceMask += 1;
    }

    if (((track->m_flags & REDSOUND_TRACK_FLAG_SLUR) == 0) ||
        ((track->m_flags & REDSOUND_TRACK_FLAG_SLUR_RELEASE) == 0)) {
        track->m_flags |= REDSOUND_TRACK_FLAG_SLUR_RELEASE;
        *voiceMask |= (int)(1u << voice->m_voiceIndex);
    }
    voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_ALL;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static RedVoiceDATA* _VoiceDataSelect(RedTrackDATA* track, RedNoteDATA* note, int* voiceMask)
{
    RedVoiceDATA* voiceData;

    if ((track->m_flags & REDSOUND_TRACK_FLAG_SLUR) != 0) {
        voiceData = p_VoiceData;
        do {
            if (voiceData->m_track == track) {
                break;
            }
            voiceData++;
        } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);

        if (!(voiceData < p_VoiceData + REDSOUND_VOICE_COUNT)) {
            voiceData = EntryVoiceSearch(track);
        }
    } else {
        voiceData = EntryVoiceSearch(track);
    }

    if (voiceData != 0) {
        voiceData->m_waveData = _WaveSplitSelect(track->m_waveData, note);
        _VoiceDataAsign(track, voiceData, note, voiceMask);

        if (((voiceData->m_waveData->m_flags & REDSOUND_WAVE_FLAG_PAIRED_ENTRY) != 0) &&
            (((s8)track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) == 0)) {
            RedWaveDATA* wave = voiceData->m_waveData;
            voiceData->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAIRED_LEFT;
            voiceData = EntryVoiceSearch(track);
            if (voiceData != 0) {
                voiceData->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAIRED_RIGHT;
                voiceData->m_waveData = wave + 1;
                _VoiceDataAsign(track, voiceData, note, voiceMask);
            }
        }
    }

    return voiceData;
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
    int* stage = &voice->m_adsrStage;
    u8* adsrData = (u8*)voice->m_adsrTime;
    int prevLevel;
    int nextLevel;
    int stepFrames;

    nextLevel = voice->m_adsrLevel[REDSOUND_VOICE_ADSR_ATTACK];
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

    stage[REDSOUND_ADSR_STATE_STEP_FRAMES] = stepFrames;
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
        stage[REDSOUND_ADSR_STATE_STEP_ADD] = (nextLevel - prevLevel) / stepFrames;
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
    u8* adsrData = (u8*)voice->m_adsrTime;
    int prevValue;
    int stepCount;
    int level;
    int* stage = &voice->m_adsrStage;

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

    stage[REDSOUND_ADSR_STATE_STEP_FRAMES] = stepCount;
    if (stepCount != 0) {
        voice->m_adsrCurrentLevel = prevValue;
        level |= REDSOUND_FIXED_HALF;
        stage[REDSOUND_ADSR_STATE_STEP_ADD] = (level - prevValue) / stepCount;
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

    if (voice->m_adsrStage < REDSOUND_VOICE_ADSR_DONE) {
        if ((voice->m_flags & REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE) != 0 ||
            voice->m_adsrStage < REDSOUND_VOICE_ADSR_RELEASE) {
            changed += 1;
            voice->m_adsrStepFrames -= 1;
            voice->m_adsrCurrentLevel += voice->m_adsrStepAdd;
            if (voice->m_adsrStepFrames == 0 && voice->m_adsrStage < REDSOUND_VOICE_ADSR_RELEASE) {
                voice->m_adsrStage += 1;
                _AdsrDataCompute(voice);
            }
        }
    } else {
        voice->m_adsrCurrentLevel = 0;
    }

    if ((voice->m_adsrCurrentLevel >> REDSOUND_FIXED_SHIFT) < 1) {
        voice->m_adsrStage = REDSOUND_VOICE_ADSR_DONE;
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
        if (voiceData[REDSOUND_VOICE_ACTIVE_WORD] != 0) {
            int voice;

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_START) != 0) {
                voice = voiceData[REDSOUND_VOICE_AX_VOICE_WORD];
                if ((voice != 0) && (((AXVPB*)voice)->priority != 0)) {
                    AXFreeVoice((AXVPB*)voice);
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = 0;
                }

                if ((((u8*)voiceData)[REDSOUND_VOICE_STATE_FLAGS_OFFSET] & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0) {
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] =
                        (int)AXAcquireVoice(REDSOUND_VOICE_INDEX_MASK, _VoiceDropedCallback, 0);
                } else {
                    int prio = ((int)voiceData - (int)p_VoiceData) / REDSOUND_VOICE_SIZE;
                    prio = (REDSOUND_VOICE_COUNT - prio >> 1) - 1;
                    if (prio < 1) {
                        prio = 1;
                    }
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = (int)AXAcquireVoice(prio, _VoiceDropedCallback, 0);
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
                int pitch = voiceData[REDSOUND_VOICE_TARGET_PITCH_WORD];
                voiceFlags = AX_SYNC_FLAG_COPYRATIO;
                ((AXVPB*)voice)->pb.src.ratioHi = (u16)(((u32)pitch >> 0x10) & 3);
                ((AXVPB*)voice)->pb.src.ratioLo = (u16)pitch;
            }

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_ADPCM_DIRTY) != 0) {
                if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_PAUSE) == 0) {
                    memcpy(&((AXVPB*)voice)->pb.mix, &((RedVoiceDATA*)voiceData)->m_axMix, sizeof(((AXVPB*)voice)->pb.mix));
                } else {
                    memset(&((AXVPB*)voice)->pb.mix, 0, sizeof(((AXVPB*)voice)->pb.mix));
                }

                ((AXVPB*)voice)->pb.mixerCtrl = REDSOUND_AX_MIX_CTRL_DRY_STEREO;
                if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_REVERB_STEREO) != 0) {
                    if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                        ((AXVPB*)voice)->pb.mixerCtrl |= REDSOUND_AX_MIX_CTRL_AUX_A_STEREO;
                    } else {
                        ((AXVPB*)voice)->pb.mixerCtrl |= REDSOUND_AX_MIX_CTRL_AUX_B_STEREO;
                    }
                }
                voiceFlags |= AX_SYNC_FLAG_COPYAXPBMIX | AX_SYNC_FLAG_COPYMXRCTRL;
            }

            if (((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_PAUSE) == 0) &&
                ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_ADSR_START) != 0)) {
                _AdsrStart((RedVoiceDATA*)voiceData);
                envChanged = 1;
            }

            if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_START) != 0) {
                voiceData[REDSOUND_VOICE_FLAGS_WORD] &= REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK;
                RedWaveDATA* waveData = (RedWaveDATA*)voiceData[REDSOUND_VOICE_WAVE_DATA_WORD];
                RedTrackDATA* trackData = (RedTrackDATA*)voiceData[REDSOUND_VOICE_TRACK_WORD];
                if ((waveData == 0) || (trackData == 0)) {
                    voiceData[REDSOUND_VOICE_ACTIVE_WORD] = 0;
                } else {
                    envChanged += 1;
                    int key = (trackData->m_waveBase + waveData->m_sampleStart + 1) * 2;
                    int keyBase = key - 2;

                    *(u16*)(voice + REDSOUND_AX_VOICE_LOOP_OFFSET) =
                        (u16)((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_LOOP) != 0);
                    ((AXVPB*)voice)->pb.srcSelect = 1;
                    ((AXVPB*)voice)->pb.state = 1;

                    memcpy(&((AXVPB*)voice)->pb.adpcm, &waveData->m_adpcm.m_data, sizeof(waveData->m_adpcm.m_data));
                    memcpy(&((AXVPB*)voice)->pb.adpcmLoop, &waveData->m_adpcm.m_loop, sizeof(waveData->m_adpcm.m_loop));
                    memset(((AXVPB*)voice)->pb.src.last_samples, 0, sizeof(((AXVPB*)voice)->pb.src.last_samples));
                    ((AXVPB*)voice)->pb.addr.format = 0;
                    *(u32*)&((AXVPB*)voice)->pb.addr.currentAddressHi = key;

                    if (waveData->m_loopStart < 0) {
                        ((AXVPB*)voice)->pb.addr.loopFlag = 0;
                        key = keyBase;
                    } else {
                        ((AXVPB*)voice)->pb.addr.loopFlag = 1;
                        key = keyBase + waveData->m_loopStart;
                    }

                    ((AXVPB*)voice)->pb.addr.loopAddressHi = (u16)((u32)key >> 0x10);
                    ((AXVPB*)voice)->pb.addr.loopAddressLo = (u16)key;
                    *(u32*)&((AXVPB*)voice)->pb.addr.endAddressHi = keyBase + waveData->m_loopEnd;

                    voiceFlags |= AX_SYNC_FLAG_COPYADPCMLOOP | AX_SYNC_FLAG_COPYSRC | AX_SYNC_FLAG_COPYADPCM |
                                  AX_SYNC_FLAG_COPYCURADDR | AX_SYNC_FLAG_COPYADDR | AX_SYNC_FLAG_COPYTYPE |
                                  AX_SYNC_FLAG_COPYSTATE | AX_SYNC_FLAG_COPYSELECT;
                    voiceData[REDSOUND_VOICE_FLAGS_WORD] |= REDSOUND_VOICE_FLAGS_ADSR_START;
                    voiceData[REDSOUND_VOICE_ENVELOPE_WORD] = REDSOUND_ENVELOPE_LEVEL_FULL;
                    voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] = 0;
                }
            } else {
                if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_RELEASED) != 0) {
                    voiceData[REDSOUND_VOICE_FLAGS_WORD] |= REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE;
                    voiceData[REDSOUND_VOICE_ADSR_STAGE_WORD] = REDSOUND_VOICE_ADSR_RELEASE;
                    voiceData[REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD] =
                        (u16)((u8*)voiceData)[REDSOUND_VOICE_ADSR_TIME_RELEASE_BYTE_OFFSET];
                    if (voiceData[REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD] == 0) {
                        voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] = 0;
                    } else {
                        voiceData[REDSOUND_VOICE_ADSR_STEP_ADD_WORD] = -voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD];
                        voiceData[REDSOUND_VOICE_ADSR_STEP_ADD_WORD] =
                            voiceData[REDSOUND_VOICE_ADSR_STEP_ADD_WORD] / voiceData[REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD];
                    }
                    voiceData[REDSOUND_VOICE_ENVELOPE_WORD] =
                        voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT;
                } else {
                    if ((voiceData[REDSOUND_VOICE_SWITCH_WORD] & REDSOUND_VOICE_SWITCH_PAUSE) == 0) {
                        if ((voiceData[REDSOUND_VOICE_FLAGS_WORD] & REDSOUND_VOICE_FLAGS_ADSR_START) == 0) {
                            envChanged |= _AdsrDataExecute((RedVoiceDATA*)voiceData);
                            voiceData[REDSOUND_VOICE_ENVELOPE_WORD] =
                                voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT;
                        }
                        voiceData[REDSOUND_VOICE_FLAGS_WORD] &= ~REDSOUND_VOICE_FLAGS_ADSR_START;
                    }
                }
            }

            if (voiceData[REDSOUND_VOICE_ENVELOPE_WORD] < 1) {
                voiceData[REDSOUND_VOICE_FLAGS_WORD] &= REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK;
                voiceData[REDSOUND_VOICE_ACTIVE_WORD] = 0;
                voiceFlags |= AX_SYNC_FLAG_COPYVOL | AX_SYNC_FLAG_COPYSTATE;
                voiceData[REDSOUND_VOICE_TRACK_WORD] = 0;
                ((AXVPB*)voice)->pb.state = 0;
                voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] = 0;
                voiceData[REDSOUND_VOICE_ENVELOPE_WORD] = 0;
                ((AXVPB*)voice)->pb.ve.currentVolume = 0;
                ((AXVPB*)voice)->pb.ve.currentDelta = 0;
            } else if ((envChanged != 0) &&
                       ((u32)((AXVPB*)voice)->pb.ve.currentVolume !=
                        ((voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT) & 0xFFFFU))) {
                voiceFlags |= AX_SYNC_FLAG_COPYVOL;
                ((AXVPB*)voice)->pb.ve.currentDelta = 0;
                ((AXVPB*)voice)->pb.ve.currentVolume =
                    (u16)(voiceData[REDSOUND_VOICE_ADSR_CURRENT_WORD] >> REDSOUND_FIXED_SHIFT);
            }

            ((AXVPB*)voice)->sync |= voiceFlags;
        } else {
            voiceData[REDSOUND_VOICE_ENVELOPE_WORD] = 0;
            voiceData[REDSOUND_VOICE_WAVE_DATA_WORD] = 0;
            int voice = voiceData[REDSOUND_VOICE_AX_VOICE_WORD];
            if (voice != 0) {
                if (((AXVPB*)voice)->pb.state != 0) {
                    ((AXVPB*)voice)->pb.state = 0;
                    ((AXVPB*)voice)->pb.ve.currentVolume = 0;
                    ((AXVPB*)voice)->sync |= AX_SYNC_FLAG_COPYVOL | AX_SYNC_FLAG_COPYSTATE;
                } else {
                    if (((AXVPB*)voice)->priority != 0) {
                        AXFreeVoice((AXVPB*)voice);
                    }
                    voiceData[REDSOUND_VOICE_AX_VOICE_WORD] = 0;
                    voiceData[REDSOUND_VOICE_TRACK_WORD] = 0;
                }
            }
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
    u32 voiceStartMask[2];
    int* reserve;
    RedVoiceDATA* voiceData;
    int (*waveFunc)(int);

    _VoiceEnvelopeCheck();
    voiceStartMask[0] = 0;
    voiceStartMask[1] = 0;

    if (m_KeyOnEntry != 0) {
        reserve = (int*)p_KeyOnData;
        voiceData = p_VoiceData;
        do {
            if (((u32)*reserve != 0) && (((RedTrackDATA*)*reserve)->m_waveData != 0)) {
                voiceData = _VoiceDataSelect((RedTrackDATA*)*reserve, (RedNoteDATA*)(reserve + 1), (int*)voiceStartMask);
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
                int shakeDepth = (track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1;
                int shakeValue = waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT);
                track->m_shakePan = (shakeDepth * shakeValue) >> 0x10;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track <
                 p_SoundControlBuffer->m_tracks + p_SoundControlBuffer->m_trackCount);
    }

    if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount != 0) &&
        ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_flags &
          REDSOUND_CONTROL_FLAG_PAUSE) == 0)) {
        RedTrackDATA* track = p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks;
        RedTrackDATA* trackBase = p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                int shakeDepth = (track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1;
                int shakeValue = waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT);
                track->m_shakePan = (shakeDepth * shakeValue) >> 0x10;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track < trackBase + p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_trackCount);
    }

    {
        RedTrackDATA* track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                int shakeDepth = (track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1;
                int shakeValue = waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT);
                track->m_shakePan = (shakeDepth * shakeValue) >> 0x10;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);
    }

    {
        RedVoiceDATA* voice = p_VoiceData;
        do {
            if ((voice->m_active != 0) && (voice->m_track != 0) &&
                ((voice->m_track->m_voiceSwitch & 9) == 0)) {
                if ((voice->m_updateFlags & REDSOUND_VOICE_UPDATE_VOLUME) != 0 ||
                    (voice->m_track->m_tremoloFunc != 0) ||
                    (voice->m_track->m_shakeFunc != 0)) {
                    int volume;
                    RedSoundCONTROL* soundControl = p_SoundControlBuffer;
                    RedTrackDATA* trackData = voice->m_track;
                    if ((soundControl->m_tracks <= trackData) &&
                        (trackData < soundControl->m_tracks + soundControl->m_trackCount)) {
                        int idx = trackData->m_trackNo;
                        if (((1U << (idx % REDSOUND_MUTE_BITS_PER_WORD)) &
                             m_Mute[idx / REDSOUND_MUTE_BITS_PER_WORD]) == 0) {
                            volume = ((soundControl->m_volumeScale + 1) *
                                      (soundControl->m_volume >> REDSOUND_FIXED_SHIFT)) >>
                                     7;
                            if (soundControl->m_masterVolumeDelta != 0) {
                                volume = (volume * (soundControl->m_masterVolume >> REDSOUND_FIXED_SHIFT)) >> 9;
                            }
                            volume = (volume * m_MasterMusicVolume) >> 9;
                        } else {
                            volume = 0;
                        }
                    } else {
                        volume = m_MasterSEVolume;
                        if ((soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks <= trackData) &&
                            (trackData <
                             soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks +
                                 soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_trackCount)) {
                            int idx = trackData->m_trackNo;

                            if (((1U << (idx % REDSOUND_MUTE_BITS_PER_WORD)) &
                                 m_Mute[idx / REDSOUND_MUTE_BITS_PER_WORD]) == 0) {
                                volume = ((soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_volumeScale + 1) *
                                          (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_volume >>
                                           REDSOUND_FIXED_SHIFT)) >>
                                         7;
                                if (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_masterVolumeDelta != 0) {
                                    volume = (volume *
                                              (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_masterVolume >>
                                               REDSOUND_FIXED_SHIFT)) >>
                                             9;
                                }
                                volume = (volume * m_MasterMusicVolume) >> 9;
                            } else {
                                volume = 0;
                            }
                        }
                    }
                    _VolumeExecute(voice, volume);
                }

                if ((voice->m_updateFlags & REDSOUND_VOICE_UPDATE_PITCH) != 0 ||
                    (voice->m_track->m_vibrateFunc != 0)) {
                    _PitchExecute(voice);
                }
                voice->m_updateFlags = 0;
            }
            voice++;
        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
    }

    {
        u32 bit = 1;
        RedVoiceDATA* voice = p_VoiceData;
        do {
            if ((voiceStartMask[0] & bit) != 0) {
                voiceStartMask[0] &= ~bit;
                voice->m_flags |= REDSOUND_VOICE_FLAGS_START;
            }
            bit <<= 1;
            voice++;
        } while (voiceStartMask[0] != 0);
    }

    {
        u32 bit = 1;
        RedVoiceDATA* voice = p_VoiceData + REDSOUND_MUTE_BITS_PER_WORD;
        do {
            if ((voiceStartMask[1] & bit) != 0) {
                voiceStartMask[1] &= ~bit;
                voice->m_flags |= REDSOUND_VOICE_FLAGS_START;
            }
            bit <<= 1;
            voice++;
        } while (voiceStartMask[1] != 0);
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
                voice->m_pitch = PitchCompute(
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
            if ((soundControl->m_flags & REDSOUND_CONTROL_FLAG_STOP_ON_VOLUME_ZERO) != 0) {
                if ((soundControl->m_volumeDelta == 0) && (soundControl->m_musicId >= 0)) {
                    MusicStop(soundControl->m_musicId);
                }
            } else {
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
    RedVoiceDATA* voiceData;

    track->m_playTime += frames;

    if (track->m_volumeDelta != 0) {
        int step;
        if (frames < track->m_volumeDelta) {
            step = frames;
        } else {
            step = track->m_volumeDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_volumeDelta -= step;
        track->m_volume += track->m_volumeAdd * step;
    }

    if (track->m_expressionDelta != 0) {
        int step;
        if (frames < track->m_expressionDelta) {
            step = frames;
        } else {
            step = track->m_expressionDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_expressionDelta -= step;
        track->m_expression += track->m_expressionAdd * step;
    }

    if (track->m_panDelta != 0) {
        int step;
        if (frames < track->m_panDelta) {
            step = frames;
        } else {
            step = track->m_panDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_panDelta -= step;
        track->m_pan += track->m_panAdd * step;
    }

    if (track->m_reverbDepthDelta != 0) {
        int step;
        if (frames < track->m_reverbDepthDelta) {
            step = frames;
        } else {
            step = track->m_reverbDepthDelta;
        }
        updateFlags = REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_reverbDepthDelta -= step;
        track->m_reverbDepth += track->m_reverbDepthAdd * step;
    }

    if (track->m_sweepDelta != 0) {
        int step;
        int addPitch;

        if (frames < track->m_sweepDelta) {
            step = frames;
        } else {
            step = track->m_sweepDelta;
        }
        updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
        track->m_sweepDelta -= step;
        addPitch = step * track->m_sweepAdd;
        track->m_portamentPitch += addPitch;

        voiceData = p_VoiceData;
        do {
            if (voiceData->m_track == track) {
                voiceData->m_basePitch += addPitch;
                if (voiceData->m_waveData != 0) {
                    voiceData->m_pitch =
                        PitchCompute(voiceData->m_basePitch + p_MusicPitchControl->m_value,
                                     (int)(s16)track->m_keyTranspose + (int)(s16)track->m_pitchBend,
                                     voiceData->m_waveData->m_pitch, (s8)track->m_fineTune);
                }
            }
            voiceData++;
        } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
    }

    if (track->m_vibrateFunc != 0) {
        if (track->m_vibrateRateDelta != 0) {
            int step;
            if (frames < track->m_vibrateRateDelta) {
                step = frames;
            } else {
                step = track->m_vibrateRateDelta;
            }
            track->m_vibrateRateDelta -= (s16)step;
            track->m_vibrateRate += track->m_vibrateRateAdd * step;
        }
        if (track->m_vibrateDepthDelta != 0) {
            int step;
            if (frames < track->m_vibrateDepthDelta) {
                step = frames;
            } else {
                step = track->m_vibrateDepthDelta;
            }
            track->m_vibrateDepthDelta -= (s16)step;
            track->m_vibrateDepth += track->m_vibrateDepthAdd * step;
        }
    }

    if (track->m_tremoloFunc != 0) {
        if (track->m_tremoloRateDelta != 0) {
            int step;
            if (frames < track->m_tremoloRateDelta) {
                step = frames;
            } else {
                step = track->m_tremoloRateDelta;
            }
            track->m_tremoloRateDelta -= (s16)step;
            track->m_tremoloRate += track->m_tremoloRateAdd * step;
        }
        if (track->m_tremoloDepthDelta != 0) {
            int step;
            if (frames < track->m_tremoloDepthDelta) {
                step = frames;
            } else {
                step = track->m_tremoloDepthDelta;
            }
            track->m_tremoloDepthDelta -= (s16)step;
            track->m_tremoloDepth += track->m_tremoloDepthAdd * step;
        }
    }

    voiceData = p_VoiceData;
    if (track->m_shakeFunc != 0) {
        if (track->m_shakeRateDelta != 0) {
            int step;
            if (frames < track->m_shakeRateDelta) {
                step = frames;
            } else {
                step = track->m_shakeRateDelta;
            }
            track->m_shakeRateDelta -= (s16)step;
            track->m_shakeRate += track->m_shakeRateAdd * step;
        }
        if (track->m_shakeDepthDelta != 0) {
            int step;
            if (frames < track->m_shakeDepthDelta) {
                step = frames;
            } else {
                step = track->m_shakeDepthDelta;
            }
            track->m_shakeDepthDelta -= (s16)step;
            track->m_shakeDepth += track->m_shakeDepthAdd * step;
        }
    }

    do {
        if (voiceData->m_track == track) {
            if (voiceData->m_pitchModDelay != 0) {
                int step;
                if (frames < voiceData->m_pitchModDelay) {
                    step = frames;
                } else {
                    step = voiceData->m_pitchModDelay;
                }
                voiceData->m_pitchModDelay -= (s16)step;
            }
            if (voiceData->m_volumeModDelay != 0) {
                int step;
                if (frames < voiceData->m_volumeModDelay) {
                    step = frames;
                } else {
                    step = voiceData->m_volumeModDelay;
                }
                voiceData->m_volumeModDelay -= (s16)step;
            }
            voiceData->m_updateFlags |= updateFlags;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
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
                RedVoiceDATA* voice = p_VoiceData;
                do {
                    if (voice->m_track == track) {
                        voice->m_updateFlags = m_ChangeStatus;
                    }
                    voice++;
                } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
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
    int iVar5;
    int trackIndex;
    int trackCount;
    RedSoundCONTROL* control;
    RedTrackDATA* track;

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
        track = control->m_tracks;
        trackCount = control->m_trackCount;
        trackIndex = 0;
        do {
            track->m_command = control->m_savedCommand[trackIndex];
            track->m_deltaTime = control->m_savedDelta[trackIndex];
            track->m_flags = control->m_savedFlags[trackIndex];
            track->m_note = control->m_savedNote[trackIndex];
            trackCount -= 1;
            trackIndex += 1;
            track += 1;
        } while (trackCount != 0);
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
		if (frames < track->m_volumeDelta) {
			step = frames;
		} else {
			step = track->m_volumeDelta;
		}
		track->m_volumeDelta -= step;
		track->m_volume += track->m_volumeAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_expressionDelta != 0) {
		if (frames < track->m_expressionDelta) {
			step = frames;
		} else {
			step = track->m_expressionDelta;
		}
		track->m_expressionDelta -= step;
		track->m_expression += track->m_expressionAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_panDelta != 0) {
		if (frames < track->m_panDelta) {
			step = frames;
		} else {
			step = track->m_panDelta;
		}
		track->m_panDelta -= step;
		track->m_pan += track->m_panAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_reverbDepthDelta != 0) {
		if (frames < track->m_reverbDepthDelta) {
			step = frames;
		} else {
			step = track->m_reverbDepthDelta;
		}
		track->m_reverbDepthDelta -= step;
		track->m_reverbDepth += track->m_reverbDepthAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_mixVolumeDelta != 0) {
		if (frames < track->m_mixVolumeDelta) {
			step = frames;
		} else {
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
		if (frames < track->m_pitchDelta) {
			step = frames;
		} else {
			step = track->m_pitchDelta;
		}
		track->m_pitchDelta -= step;
		track->m_pitch += track->m_pitchAdd * step;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
	}

	if (track->m_sweepDelta != 0) {
		if (frames < track->m_sweepDelta) {
			step = frames;
		} else {
			step = track->m_sweepDelta;
		}
		track->m_sweepDelta -= step;
		track->m_portamentPitch += step * track->m_sweepAdd;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
		voice->m_basePitch += step * track->m_sweepAdd;
	}

	if (((voice->m_updateFlags & REDSOUND_VOICE_UPDATE_PITCH) != 0) && (voice->m_waveData != 0)) {
		voice->m_pitch =
			PitchCompute(voice->m_basePitch + track->m_pitch,
			             (int)(s16)track->m_keyTranspose + (int)(s16)track->m_pitchBend,
			             voice->m_waveData->m_pitch, (int)(s8)track->m_fineTune);
	}

	if (track->m_vibrateFunc != 0) {
		if (track->m_vibrateRateDelta != 0) {
			if (frames < track->m_vibrateRateDelta) {
				step = frames;
			} else {
				step = track->m_vibrateRateDelta;
			}
			track->m_vibrateRateDelta = track->m_vibrateRateDelta - (short)step;
			track->m_vibrateRate += track->m_vibrateRateAdd * step;
		}
		if (track->m_vibrateDepthDelta != 0) {
			if (frames < track->m_vibrateDepthDelta) {
				step = frames;
			} else {
				step = track->m_vibrateDepthDelta;
			}
			track->m_vibrateDepthDelta = track->m_vibrateDepthDelta - (short)step;
			track->m_vibrateDepth += track->m_vibrateDepthAdd * step;
		}
	}

	if (track->m_tremoloFunc != 0) {
		if (track->m_tremoloRateDelta != 0) {
			if (frames < track->m_tremoloRateDelta) {
				step = frames;
			} else {
				step = track->m_tremoloRateDelta;
			}
			track->m_tremoloRateDelta = track->m_tremoloRateDelta - (short)step;
			track->m_tremoloRate += track->m_tremoloRateAdd * step;
		}
		if (track->m_tremoloDepthDelta != 0) {
			if (frames < track->m_tremoloDepthDelta) {
				step = frames;
			} else {
				step = track->m_tremoloDepthDelta;
			}
			track->m_tremoloDepthDelta = track->m_tremoloDepthDelta - (short)step;
			track->m_tremoloDepth += track->m_tremoloDepthAdd * step;
		}
	}

	if (track->m_shakeFunc != 0) {
		if (track->m_shakeRateDelta != 0) {
			if (frames < track->m_shakeRateDelta) {
				step = frames;
			} else {
				step = track->m_shakeRateDelta;
			}
			track->m_shakeRateDelta = track->m_shakeRateDelta - (short)step;
			track->m_shakeRate += track->m_shakeRateAdd * step;
		}
		if (track->m_shakeDepthDelta != 0) {
			if (frames < track->m_shakeDepthDelta) {
				step = frames;
			} else {
				step = track->m_shakeDepthDelta;
			}
			track->m_shakeDepthDelta = track->m_shakeDepthDelta - (short)step;
			track->m_shakeDepth += track->m_shakeDepthAdd * step;
		}
	}

	if (voice->m_pitchModDelay != 0) {
		if (frames < voice->m_pitchModDelay) {
			step = frames;
		} else {
			step = voice->m_pitchModDelay;
		}
		voice->m_pitchModDelay = voice->m_pitchModDelay - (short)step;
	}

	if (voice->m_volumeModDelay != 0) {
		if (frames < voice->m_volumeModDelay) {
			step = frames;
		} else {
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
