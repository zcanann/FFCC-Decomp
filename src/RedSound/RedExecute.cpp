#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "global.h"
#include "types.h"
#include "dolphin/ax.h"
#include "dolphin/axfx.h"
#include <string.h>

u32 t_TonePitch[REDSOUND_NOTES_PER_OCTAVE] = {
    131072, 138865, 147123, 155871, 165140, 174960,
    185363, 196386, 208063, 220435, 233543, 247430,
};

int t_FinePitch[REDSOUND_PITCH_FINE_COUNT] = {
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

int t_KeySignatureIndex[REDSOUND_KEY_SIGNATURE_INDEX_COUNT] = {
    11, 4, 9, 2, 7, 0, 5, 10,
    11, 0, 5, 10, 3, 8, 1, 6,
    25, 30, 23, 28, 33, 26, 31, 24,
    34, 26, 31, 24, 29, 34, 27, 32,
};

signed char t_KeySignatureData[REDSOUND_KEY_SIGNATURE_DATA_COUNT] = {
    0, 0, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1,
    0, 0, 0, 0, -1, 0, -1, 0, 0, 1, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
};

signed char t_RandomData[REDSOUND_RANDOM_DATA_COUNT] = {
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

s16 t_PanningData[REDSOUND_PAN_TABLE_COUNT] = {
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

s16 t_PanningDataR[REDSOUND_PAN_TABLE_COUNT] = {
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
    REDSOUND_REVERB_DATA_COUNT = REDSOUND_REVERB_DEPTH_COUNT,
    REDSOUND_REVERB_DATA_BUFFER_SIZE = sizeof(RedReverbDATA) * REDSOUND_REVERB_DATA_COUNT,
    REDSOUND_REVERB_DATA_ALLOC_SIZE = 0x18,
    REDSOUND_REVERB_SIZE_ALLOC_SIZE = sizeof(u32),
    REDSOUND_REVERB_AUX_BUFFER_SIZE = 0x280,
    REDSOUND_REVERB_ALLOC_ALIGN = 0x20,
    REDSOUND_REVERB_ALLOC_ALIGN_MASK = REDSOUND_REVERB_ALLOC_ALIGN - 1,
};

enum RedReverbControlConstant {
    REDSOUND_REVERB_AUX_A = 0,
    REDSOUND_REVERB_AUX_B = 1,
    REDSOUND_REVERB_FX_ENABLE = 0,
    REDSOUND_REVERB_INIT_SUCCESS = 1,
};

enum RedExecuteSmallDataLayout {
    REDSOUND_EXECUTE_SDATA_SIZE = 0x04,
    REDSOUND_EXECUTE_SBSS_RANDOM_INDEX_OFFSET = 0x00,
    REDSOUND_EXECUTE_SBSS_RANDOM_PAD_OFFSET = 0x01,
    REDSOUND_EXECUTE_SBSS_RANDOM_PAD_SIZE = 3,
    REDSOUND_EXECUTE_SBSS_REVERB_DATA_OFFSET = 0x04,
    REDSOUND_EXECUTE_SBSS_REVERB_SIZE_OFFSET = 0x08,
    REDSOUND_EXECUTE_SBSS_CHANGE_STATUS_OFFSET = 0x0C,
    REDSOUND_EXECUTE_SBSS_SKIP_KEY_ON_OFFSET = 0x10,
    REDSOUND_EXECUTE_SBSS_SIZE = 0x14,
};

struct RedExecuteSmallDataState {
    volatile u8 m_randomIndex;
    u8 m_randomIndexAlignPadding[REDSOUND_EXECUTE_SBSS_RANDOM_PAD_SIZE];
    RedReverbDATA* volatile m_reverbData;
    RedReverbSize* m_reverbSize;
    volatile u32 m_changeStatus;
    RedKeyOnDATA* volatile m_skipKeyOn;
};

enum RedReverbDelayChannelIndex {
    REDSOUND_REVERB_DELAY_LEFT = 0,
    REDSOUND_REVERB_DELAY_RIGHT = 1,
    REDSOUND_REVERB_DELAY_SURROUND = 2,
};

enum RedExecuteAxfxReverbLayout {
    REDSOUND_AXFX_REVERB_STD_TEMP_DISABLE_OFFSET = 0x13C,
    REDSOUND_AXFX_REVERB_STD_COLORATION_OFFSET = 0x140,
    REDSOUND_AXFX_REVERB_STD_MIX_OFFSET = 0x144,
    REDSOUND_AXFX_REVERB_STD_TIME_OFFSET = 0x148,
    REDSOUND_AXFX_REVERB_STD_DAMPING_OFFSET = 0x14C,
    REDSOUND_AXFX_REVERB_STD_PRE_DELAY_OFFSET = 0x150,
    REDSOUND_AXFX_REVERB_STD_SIZE = 0x154,

    REDSOUND_AXFX_REVERB_HI_TEMP_DISABLE_OFFSET = 0x1C4,
    REDSOUND_AXFX_REVERB_HI_COLORATION_OFFSET = 0x1C8,
    REDSOUND_AXFX_REVERB_HI_MIX_OFFSET = 0x1CC,
    REDSOUND_AXFX_REVERB_HI_TIME_OFFSET = 0x1D0,
    REDSOUND_AXFX_REVERB_HI_DAMPING_OFFSET = 0x1D4,
    REDSOUND_AXFX_REVERB_HI_PRE_DELAY_OFFSET = 0x1D8,
    REDSOUND_AXFX_REVERB_HI_CROSSTALK_OFFSET = 0x1DC,
    REDSOUND_AXFX_REVERB_HI_SIZE = 0x1E0,

    REDSOUND_AXFX_REVERB_HI_DPL2_TEMP_DISABLE_OFFSET = 0x254,
    REDSOUND_AXFX_REVERB_HI_DPL2_COLORATION_OFFSET = 0x258,
    REDSOUND_AXFX_REVERB_HI_DPL2_MIX_OFFSET = 0x25C,
    REDSOUND_AXFX_REVERB_HI_DPL2_TIME_OFFSET = 0x260,
    REDSOUND_AXFX_REVERB_HI_DPL2_DAMPING_OFFSET = 0x264,
    REDSOUND_AXFX_REVERB_HI_DPL2_PRE_DELAY_OFFSET = 0x268,
    REDSOUND_AXFX_REVERB_HI_DPL2_SIZE = 0x26C,

    REDSOUND_AXFX_DELAY_CHANNEL_COUNT = 3,
    REDSOUND_AXFX_DELAY_CHANNEL_SIZE = sizeof(u32) * REDSOUND_AXFX_DELAY_CHANNEL_COUNT,
    REDSOUND_AXFX_DELAY_DELAY_OFFSET = 0x3C,
    REDSOUND_AXFX_DELAY_FEEDBACK_OFFSET = 0x48,
    REDSOUND_AXFX_DELAY_OUTPUT_OFFSET = 0x54,
    REDSOUND_AXFX_DELAY_SIZE = 0x60,

    REDSOUND_AXFX_CHORUS_BASE_DELAY_OFFSET = 0x90,
    REDSOUND_AXFX_CHORUS_VARIATION_OFFSET = 0x94,
    REDSOUND_AXFX_CHORUS_PERIOD_OFFSET = 0x98,
    REDSOUND_AXFX_CHORUS_SIZE = 0x9C,
};

enum RedExecuteAxVoiceLayout {
    REDSOUND_AX_VOICE_TYPE_OFFSET = 0x148,
    REDSOUND_AX_MIX_CTRL_DRY_STEREO = 0x3,
    REDSOUND_AX_MIX_CTRL_AUX_A_STEREO = 0x30,
    REDSOUND_AX_MIX_CTRL_AUX_B_STEREO = 0x600,
    REDSOUND_AX_SAMPLE_ADDR_SCALE = 2,
    REDSOUND_AX_SAMPLE_START_BIAS = 1,
    REDSOUND_AX_HIGH_WORD_SHIFT = 0x10,
    REDSOUND_AX_SRC_RATIO_HI_MASK = 3,
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
    REDSOUND_SHAKE_PAN_SCALE_SHIFT = 0x10,
};

enum RedControlTickWord {
    REDSOUND_CONTROL_TICK_MEASURE = 0,
    REDSOUND_CONTROL_TICK_CURRENT = 1,
    REDSOUND_CONTROL_TICK_PER_MEASURE = 2,
};

enum RedMusicSkipTiming {
    REDSOUND_MUSIC_SKIP_RETRY_SLEEP_US = 10000,
    REDSOUND_MUSIC_SKIP_LOOP_SLEEP_US = 1000,
};

enum RedExecuteAdsrStateIndex {
    REDSOUND_ADSR_STATE_STAGE = 0,
    REDSOUND_ADSR_STATE_STEP_FRAMES = 1,
    REDSOUND_ADSR_STATE_STEP_ADD = 2,
};

enum RedVoiceStartMaskIndex {
    REDSOUND_VOICE_START_MASK_LOW = 0,
    REDSOUND_VOICE_START_MASK_HIGH = 1,
    REDSOUND_VOICE_START_MASK_COUNT = 2,
};

STATIC_ASSERT(sizeof(t_TonePitch) == REDSOUND_TONE_PITCH_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_TONE_PITCH_TABLE_SIZE == REDSOUND_TONE_PITCH_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_FinePitch) == REDSOUND_FINE_PITCH_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_FINE_PITCH_TABLE_SIZE == REDSOUND_FINE_PITCH_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_KeySignatureIndex) == REDSOUND_KEY_SIGNATURE_INDEX_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_KEY_SIGNATURE_INDEX_TABLE_SIZE == REDSOUND_KEY_SIGNATURE_INDEX_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_KeySignatureData) == REDSOUND_KEY_SIGNATURE_DATA_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_KEY_SIGNATURE_DATA_TABLE_SIZE == REDSOUND_KEY_SIGNATURE_DATA_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_RandomData) == REDSOUND_RANDOM_DATA_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_RANDOM_DATA_TABLE_SIZE == REDSOUND_RANDOM_DATA_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_PanningData) == REDSOUND_PAN_TABLE_SIZE);
STATIC_ASSERT(sizeof(t_PanningDataR) == REDSOUND_PAN_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_PAN_TABLE_SIZE == REDSOUND_PAN_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_PAN_TABLE_PAIR_SIZE == REDSOUND_PAN_TABLE_PAIR_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_FINE_PITCH_TABLE_OFFSET == REDSOUND_TONE_PITCH_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_KEY_SIGNATURE_INDEX_TABLE_OFFSET ==
              REDSOUND_FINE_PITCH_TABLE_OFFSET + REDSOUND_FINE_PITCH_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_KEY_SIGNATURE_DATA_TABLE_OFFSET ==
              REDSOUND_KEY_SIGNATURE_INDEX_TABLE_OFFSET + REDSOUND_KEY_SIGNATURE_INDEX_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_RANDOM_DATA_TABLE_OFFSET ==
              REDSOUND_KEY_SIGNATURE_DATA_TABLE_OFFSET + REDSOUND_KEY_SIGNATURE_DATA_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_PAN_TABLE_OFFSET == REDSOUND_RANDOM_DATA_TABLE_OFFSET + REDSOUND_RANDOM_DATA_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_PAN_TABLE_R_OFFSET == REDSOUND_PAN_TABLE_OFFSET + REDSOUND_PAN_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_EXECUTE_DATA_TABLE_END_OFFSET ==
              REDSOUND_PAN_TABLE_R_OFFSET + REDSOUND_PAN_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_TonePitch) + sizeof(t_FinePitch) + sizeof(t_KeySignatureIndex) +
                  sizeof(t_KeySignatureData) + sizeof(t_RandomData) + sizeof(t_PanningData) +
                  sizeof(t_PanningDataR) ==
              REDSOUND_EXECUTE_DATA_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_EXECUTE_DATA_TABLE_SIZE == REDSOUND_EXECUTE_DATA_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_REVERB_DATA_BUFFER_SIZE == REDSOUND_REVERB_DATA_ALLOC_SIZE);
STATIC_ASSERT(sizeof(m_TerminateNote) == REDSOUND_EXECUTE_SDATA_SIZE);
STATIC_ASSERT(offsetof(RedExecuteSmallDataState, m_randomIndex) == REDSOUND_EXECUTE_SBSS_RANDOM_INDEX_OFFSET);
STATIC_ASSERT(offsetof(RedExecuteSmallDataState, m_randomIndexAlignPadding) ==
              REDSOUND_EXECUTE_SBSS_RANDOM_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedExecuteSmallDataState, m_reverbData) == REDSOUND_EXECUTE_SBSS_REVERB_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedExecuteSmallDataState, m_reverbSize) == REDSOUND_EXECUTE_SBSS_REVERB_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedExecuteSmallDataState, m_changeStatus) == REDSOUND_EXECUTE_SBSS_CHANGE_STATUS_OFFSET);
STATIC_ASSERT(offsetof(RedExecuteSmallDataState, m_skipKeyOn) == REDSOUND_EXECUTE_SBSS_SKIP_KEY_ON_OFFSET);
STATIC_ASSERT(sizeof(RedExecuteSmallDataState) == REDSOUND_EXECUTE_SBSS_SIZE);
STATIC_ASSERT(sizeof(m_RandomIndex) + REDSOUND_EXECUTE_SBSS_RANDOM_PAD_SIZE + sizeof(p_ReverbData) +
                  sizeof(p_ReverbSize) + sizeof(m_ChangeStatus) + sizeof(p_SkipKeyOn) ==
              REDSOUND_EXECUTE_SBSS_SIZE);
STATIC_ASSERT(offsetof(RedReverbDATA, m_callback) == REDSOUND_REVERB_CALLBACK_OFFSET);
STATIC_ASSERT(offsetof(RedReverbDATA, m_context) == REDSOUND_REVERB_CONTEXT_OFFSET);
STATIC_ASSERT(offsetof(RedReverbDATA, m_kind) == REDSOUND_REVERB_KIND_OFFSET);
STATIC_ASSERT(sizeof(RedReverbDATA) == REDSOUND_REVERB_SIZE);
STATIC_ASSERT(offsetof(RedReverbSize, m_requested) == REDSOUND_REVERB_SIZE_REQUESTED_OFFSET);
STATIC_ASSERT(offsetof(RedReverbSize, m_aligned) == REDSOUND_REVERB_SIZE_ALIGNED_OFFSET);
STATIC_ASSERT(sizeof(RedReverbSize) == REDSOUND_REVERB_SIZE_SIZE);
STATIC_ASSERT(offsetof(RedSavedTrackDATA, m_delta) == REDSOUND_MUSIC_TRACK_SAVE_COUNT * sizeof(int));
STATIC_ASSERT(offsetof(RedSavedTrackDATA, m_flags) == REDSOUND_MUSIC_TRACK_SAVE_COUNT * 2 * sizeof(int));
STATIC_ASSERT(offsetof(RedSavedTrackDATA, m_note) == REDSOUND_MUSIC_TRACK_SAVE_COUNT * 3 * sizeof(int));
STATIC_ASSERT(sizeof(RedSavedTrackDATA) == REDSOUND_MUSIC_TRACK_SAVE_COUNT * 4 * sizeof(int));
STATIC_ASSERT(offsetof(AXFX_REVERBSTD, tempDisableFX) == REDSOUND_AXFX_REVERB_STD_TEMP_DISABLE_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBSTD, coloration) == REDSOUND_AXFX_REVERB_STD_COLORATION_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBSTD, mix) == REDSOUND_AXFX_REVERB_STD_MIX_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBSTD, time) == REDSOUND_AXFX_REVERB_STD_TIME_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBSTD, damping) == REDSOUND_AXFX_REVERB_STD_DAMPING_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBSTD, preDelay) == REDSOUND_AXFX_REVERB_STD_PRE_DELAY_OFFSET);
STATIC_ASSERT(sizeof(AXFX_REVERBSTD) == REDSOUND_AXFX_REVERB_STD_SIZE);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, tempDisableFX) == REDSOUND_AXFX_REVERB_HI_TEMP_DISABLE_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, coloration) == REDSOUND_AXFX_REVERB_HI_COLORATION_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, mix) == REDSOUND_AXFX_REVERB_HI_MIX_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, time) == REDSOUND_AXFX_REVERB_HI_TIME_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, damping) == REDSOUND_AXFX_REVERB_HI_DAMPING_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, preDelay) == REDSOUND_AXFX_REVERB_HI_PRE_DELAY_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI, crosstalk) == REDSOUND_AXFX_REVERB_HI_CROSSTALK_OFFSET);
STATIC_ASSERT(sizeof(AXFX_REVERBHI) == REDSOUND_AXFX_REVERB_HI_SIZE);
STATIC_ASSERT(offsetof(AXFX_REVERBHI_DPL2, tempDisableFX) == REDSOUND_AXFX_REVERB_HI_DPL2_TEMP_DISABLE_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI_DPL2, coloration) == REDSOUND_AXFX_REVERB_HI_DPL2_COLORATION_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI_DPL2, mix) == REDSOUND_AXFX_REVERB_HI_DPL2_MIX_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI_DPL2, time) == REDSOUND_AXFX_REVERB_HI_DPL2_TIME_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI_DPL2, damping) == REDSOUND_AXFX_REVERB_HI_DPL2_DAMPING_OFFSET);
STATIC_ASSERT(offsetof(AXFX_REVERBHI_DPL2, preDelay) == REDSOUND_AXFX_REVERB_HI_DPL2_PRE_DELAY_OFFSET);
STATIC_ASSERT(sizeof(AXFX_REVERBHI_DPL2) == REDSOUND_AXFX_REVERB_HI_DPL2_SIZE);
STATIC_ASSERT(offsetof(AXFX_DELAY, delay) == REDSOUND_AXFX_DELAY_DELAY_OFFSET);
STATIC_ASSERT(sizeof(((AXFX_DELAY*)0)->delay) == REDSOUND_AXFX_DELAY_CHANNEL_SIZE);
STATIC_ASSERT(offsetof(AXFX_DELAY, feedback) == REDSOUND_AXFX_DELAY_FEEDBACK_OFFSET);
STATIC_ASSERT(sizeof(((AXFX_DELAY*)0)->feedback) == REDSOUND_AXFX_DELAY_CHANNEL_SIZE);
STATIC_ASSERT(offsetof(AXFX_DELAY, output) == REDSOUND_AXFX_DELAY_OUTPUT_OFFSET);
STATIC_ASSERT(sizeof(((AXFX_DELAY*)0)->output) == REDSOUND_AXFX_DELAY_CHANNEL_SIZE);
STATIC_ASSERT(REDSOUND_AXFX_DELAY_FEEDBACK_OFFSET ==
              REDSOUND_AXFX_DELAY_DELAY_OFFSET + REDSOUND_AXFX_DELAY_CHANNEL_SIZE);
STATIC_ASSERT(REDSOUND_AXFX_DELAY_OUTPUT_OFFSET ==
              REDSOUND_AXFX_DELAY_FEEDBACK_OFFSET + REDSOUND_AXFX_DELAY_CHANNEL_SIZE);
STATIC_ASSERT(REDSOUND_AXFX_DELAY_OUTPUT_OFFSET + REDSOUND_AXFX_DELAY_CHANNEL_SIZE == REDSOUND_AXFX_DELAY_SIZE);
STATIC_ASSERT(sizeof(AXFX_DELAY) == REDSOUND_AXFX_DELAY_SIZE);
STATIC_ASSERT(offsetof(AXFX_CHORUS, baseDelay) == REDSOUND_AXFX_CHORUS_BASE_DELAY_OFFSET);
STATIC_ASSERT(offsetof(AXFX_CHORUS, variation) == REDSOUND_AXFX_CHORUS_VARIATION_OFFSET);
STATIC_ASSERT(offsetof(AXFX_CHORUS, period) == REDSOUND_AXFX_CHORUS_PERIOD_OFFSET);
STATIC_ASSERT(sizeof(AXFX_CHORUS) == REDSOUND_AXFX_CHORUS_SIZE);
STATIC_ASSERT(offsetof(RedWaveADPCMInfo, m_data) == REDSOUND_WAVE_ADPCM_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedWaveADPCMInfo, m_loop) == REDSOUND_WAVE_ADPCM_LOOP_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveADPCMInfo*)0)->m_data) == REDSOUND_WAVE_ADPCM_DATA_SIZE);
STATIC_ASSERT(sizeof(((RedWaveADPCMInfo*)0)->m_loop) == REDSOUND_WAVE_ADPCM_LOOP_SIZE);
STATIC_ASSERT(sizeof(RedWaveADPCMInfo) == REDSOUND_WAVE_ADPCM_INFO_SIZE);
STATIC_ASSERT(offsetof(RedWaveDATA, m_flags) == REDSOUND_WAVE_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_sampleStart) == REDSOUND_WAVE_SAMPLE_START_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_loopStart) == REDSOUND_WAVE_LOOP_START_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_loopEnd) == REDSOUND_WAVE_LOOP_END_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_reserved10) == REDSOUND_WAVE_RESERVED10_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveDATA*)0)->m_reserved10) == REDSOUND_WAVE_RESERVED10_SIZE);
STATIC_ASSERT(offsetof(RedWaveDATA, m_pitch) == REDSOUND_WAVE_PITCH_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_splitKey) == REDSOUND_WAVE_SPLIT_KEY_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_splitVelocity) == REDSOUND_WAVE_SPLIT_VELOCITY_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_volume) == REDSOUND_WAVE_VOLUME_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_pan) == REDSOUND_WAVE_PAN_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_reverbMix) == REDSOUND_WAVE_REVERB_MIX_OFFSET);
STATIC_ASSERT(offsetof(RedWaveDATA, m_reserved1D) == REDSOUND_WAVE_RESERVED1D_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveDATA*)0)->m_reserved1D) == REDSOUND_WAVE_RESERVED1D_SIZE);
STATIC_ASSERT(offsetof(RedWaveDATA, m_adpcm) == REDSOUND_WAVE_ADPCM_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveDATA*)0)->m_adpcm) == REDSOUND_WAVE_ADPCM_INFO_SIZE);
STATIC_ASSERT(offsetof(RedWaveDATA, m_adsr) == REDSOUND_WAVE_ADSR_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveDATA*)0)->m_adsr) == REDSOUND_WAVE_ADSR_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_ADSR_SIZE == REDSOUND_ADSR_DATA_SIZE);
STATIC_ASSERT(offsetof(RedWaveDATA, m_reserved5C) == REDSOUND_WAVE_RESERVED5C_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveDATA*)0)->m_reserved5C) == REDSOUND_WAVE_RESERVED5C_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_RESERVED10_OFFSET + REDSOUND_WAVE_RESERVED10_SIZE == REDSOUND_WAVE_PITCH_OFFSET);
STATIC_ASSERT(REDSOUND_WAVE_RESERVED1D_OFFSET + REDSOUND_WAVE_RESERVED1D_SIZE == REDSOUND_WAVE_ADPCM_OFFSET);
STATIC_ASSERT(REDSOUND_WAVE_ADSR_OFFSET + REDSOUND_WAVE_ADSR_SIZE == REDSOUND_WAVE_RESERVED5C_OFFSET);
STATIC_ASSERT(REDSOUND_WAVE_RESERVED5C_OFFSET + REDSOUND_WAVE_RESERVED5C_SIZE == REDSOUND_WAVE_DATA_SIZE);
STATIC_ASSERT(sizeof(RedWaveDATA) == REDSOUND_WAVE_DATA_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_track) == REDSOUND_VOICE_TRACK_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_waveData) == REDSOUND_VOICE_WAVE_DATA_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_trackVolume) == REDSOUND_VOICE_TRACK_VOLUME_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_trackExpression) == REDSOUND_VOICE_TRACK_EXPRESSION_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_trackPan) == REDSOUND_VOICE_TRACK_PAN_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_axVoice) == REDSOUND_VOICE_AX_VOICE_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_key) == REDSOUND_VOICE_KEY_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_velocity) == REDSOUND_VOICE_VELOCITY_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_stateFlags) == REDSOUND_VOICE_STATE_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reserved1B) == REDSOUND_VOICE_RESERVED1B_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reserved1B) == REDSOUND_VOICE_RESERVED1B_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_pitchModPhase) == REDSOUND_VOICE_PITCH_MOD_PHASE_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_pitchModFrames) == REDSOUND_VOICE_PITCH_MOD_FRAMES_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_pitchModFrame) == REDSOUND_VOICE_PITCH_MOD_FRAME_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_pitchModDelay) ==
              REDSOUND_VOICE_PITCH_MOD_DELAY_HALFWORD * sizeof(unsigned short));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reserved2A) == REDSOUND_VOICE_RESERVED2A_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reserved2A) == REDSOUND_VOICE_RESERVED2A_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_volumeModPhase) == REDSOUND_VOICE_VOLUME_MOD_PHASE_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_volumeModFrames) == REDSOUND_VOICE_VOLUME_MOD_FRAMES_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_volumeModFrame) == REDSOUND_VOICE_VOLUME_MOD_FRAME_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_volumeModDelay) ==
              REDSOUND_VOICE_VOLUME_MOD_DELAY_HALFWORD * sizeof(unsigned short));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reserved3A) == REDSOUND_VOICE_RESERVED3A_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reserved3A) == REDSOUND_VOICE_RESERVED3A_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_randomPitch) == REDSOUND_VOICE_RANDOM_PITCH_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_randomVolume) == REDSOUND_VOICE_RANDOM_VOLUME_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_randomPan) == REDSOUND_VOICE_RANDOM_PAN_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reserved48) == REDSOUND_VOICE_RESERVED48_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reserved48) == REDSOUND_VOICE_RESERVED48_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_adsr) == REDSOUND_VOICE_ADSR_TIME_OFFSET);
STATIC_ASSERT(offsetof(RedAdsrDATA, m_time) == REDSOUND_ADSR_TIME_OFFSET);
STATIC_ASSERT(sizeof(((RedAdsrDATA*)0)->m_time) ==
              REDSOUND_VOICE_ADSR_TIME_COUNT * sizeof(unsigned short));
STATIC_ASSERT(offsetof(RedAdsrDATA, m_level) == REDSOUND_ADSR_LEVEL_OFFSET);
STATIC_ASSERT(REDSOUND_ADSR_LEVEL_OFFSET == REDSOUND_VOICE_ADSR_LEVEL_OFFSET - REDSOUND_VOICE_ADSR_TIME_OFFSET);
STATIC_ASSERT(sizeof(((RedAdsrDATA*)0)->m_level) == REDSOUND_VOICE_ADSR_LEVEL_COUNT * sizeof(unsigned char));
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_adsr) == REDSOUND_TRACK_ADSR_SIZE);
STATIC_ASSERT(sizeof(RedAdsrDATA) == REDSOUND_ADSR_DATA_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_adsrStage) == REDSOUND_VOICE_ADSR_STAGE_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_adsrStepFrames) == REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_adsrStepAdd) == REDSOUND_VOICE_ADSR_STEP_ADD_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_active) == REDSOUND_VOICE_ACTIVE_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_flags) == REDSOUND_VOICE_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_voiceSwitch) == REDSOUND_VOICE_SWITCH_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_pitch) == REDSOUND_VOICE_PITCH_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_targetPitch) == REDSOUND_VOICE_TARGET_PITCH_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_basePitch) == REDSOUND_VOICE_BASE_PITCH_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reservedA4) == REDSOUND_VOICE_RESERVEDA4_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reservedA4) == REDSOUND_VOICE_RESERVEDA4_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_voiceIndex) == REDSOUND_VOICE_INDEX_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_adsrCurrentLevel) == REDSOUND_VOICE_ADSR_CURRENT_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_envelopeLevel) == REDSOUND_VOICE_ENVELOPE_WORD * sizeof(int));
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reservedB4) == REDSOUND_VOICE_RESERVEDB4_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reservedB4) == REDSOUND_VOICE_RESERVEDB4_SIZE);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_updateFlags) == REDSOUND_VOICE_UPDATE_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedVoiceDATA, m_reservedBC) == REDSOUND_VOICE_RESERVEDBC_OFFSET);
STATIC_ASSERT(sizeof(((RedVoiceDATA*)0)->m_reservedBC) == REDSOUND_VOICE_RESERVEDBC_SIZE);
STATIC_ASSERT(REDSOUND_VOICE_RESERVED1B_OFFSET + REDSOUND_VOICE_RESERVED1B_SIZE ==
              REDSOUND_VOICE_PITCH_MOD_PHASE_WORD * sizeof(int));
STATIC_ASSERT(REDSOUND_VOICE_RESERVED2A_OFFSET + REDSOUND_VOICE_RESERVED2A_SIZE ==
              REDSOUND_VOICE_VOLUME_MOD_PHASE_WORD * sizeof(int));
STATIC_ASSERT(REDSOUND_VOICE_RESERVED3A_OFFSET + REDSOUND_VOICE_RESERVED3A_SIZE ==
              REDSOUND_VOICE_RANDOM_PITCH_WORD * sizeof(int));
STATIC_ASSERT(REDSOUND_VOICE_RESERVED48_OFFSET + REDSOUND_VOICE_RESERVED48_SIZE ==
              REDSOUND_VOICE_ADSR_TIME_OFFSET);
STATIC_ASSERT(REDSOUND_VOICE_RESERVEDA4_OFFSET + REDSOUND_VOICE_RESERVEDA4_SIZE == REDSOUND_VOICE_INDEX_OFFSET);
STATIC_ASSERT(REDSOUND_VOICE_RESERVEDB4_OFFSET + REDSOUND_VOICE_RESERVEDB4_SIZE == REDSOUND_VOICE_UPDATE_FLAGS_OFFSET);
STATIC_ASSERT(REDSOUND_VOICE_RESERVEDBC_OFFSET + REDSOUND_VOICE_RESERVEDBC_SIZE == REDSOUND_VOICE_SIZE);
STATIC_ASSERT(sizeof(RedVoiceDATA) == REDSOUND_VOICE_SIZE);
STATIC_ASSERT(offsetof(AXVPB, pb) + offsetof(AXPB, type) == REDSOUND_AX_VOICE_TYPE_OFFSET);

/*
 * --INFO--
 * PAL Address: 0x801c2fc4
 * PAL Size: 56b
 * EN Address: 0x80204ee8
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
u8 GetRandomData()
{
	s8* random = &t_RandomData[m_RandomIndex];
	m_RandomIndex++;
	return *random;
}

/*
 * --INFO--
 * PAL Address: 0x801C2FFC
 * PAL Size: 256b
 * EN Address: 0x80204f20
 * EN Size: 256b
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
    basePitch >>= REDSOUND_FIXED_SHIFT;
    pitch = pitchOffset + (wavePitch >> REDSOUND_PITCH_WAVE_SHIFT);
    pitch = basePitch + pitch;
    while (pitch < 0) {
        pitch += REDSOUND_PITCH_OCTAVE_UNITS;
        octaveAdjust -= 1;
    }

    noteBand = (pitch >> REDSOUND_PITCH_NOTE_SHIFT) & REDSOUND_PITCH_NOTE_MASK;
    octaveAdjust += noteBand / REDSOUND_NOTES_PER_OCTAVE;
    noteBand %= REDSOUND_NOTES_PER_OCTAVE;
    value = t_TonePitch[noteBand] >> (REDSOUND_PITCH_TONE_SHIFT - octaveAdjust);
    value *= t_FinePitch[pitch & REDSOUND_PITCH_FINE_MASK];
    value >>= REDSOUND_FIXED_SHIFT;

    if (fineTune != 0) {
        if ((int)fineTune > 0) {
            value = value + ((int)(value * (fineTune + 1)) >> REDSOUND_PITCH_FINE_TUNE_POSITIVE_SHIFT);
        } else {
            value *= fineTune & REDSOUND_PITCH_FINE_MASK;
            value >>= REDSOUND_PITCH_FINE_TUNE_NEGATIVE_SHIFT;
        }
    }

    return value;
}

/*
 * --INFO--
 * PAL Address: 0x801c30fc
 * PAL Size: 88b
 * EN Address: 0x80205020
 * EN Size: 88b
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
 * EN Address: 0x80205078
 * EN Size: 88b
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
 * EN Address: 0x802050d0
 * EN Size: 40b
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
 * EN Address: 0x802050f8
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
void InitReverb()
{
    p_ReverbData = (RedReverbDATA*)RedNew(sizeof(*p_ReverbData) * REDSOUND_REVERB_DATA_COUNT);
    memset(p_ReverbData, 0, sizeof(*p_ReverbData) * REDSOUND_REVERB_DATA_COUNT);
    p_ReverbSize = (RedReverbSize*)RedNew(REDSOUND_REVERB_SIZE_ALLOC_SIZE);
}

/*
 * --INFO--
 * PAL Address: 0x801c3218
 * PAL Size: 1040b
 * EN Address: 0x8020513c
 * EN Size: 1040b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetReverbData(RedReverbDATA* reverb, int* params)
{
    int result = 0;

    switch (reverb->m_kind) {
    case REDSOUND_REVERB_KIND_STD: {
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)reverb->m_context;
        std->tempDisableFX = REDSOUND_REVERB_FX_ENABLE;
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
        hi->tempDisableFX = REDSOUND_REVERB_FX_ENABLE;
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
        hiDpl2->tempDisableFX = REDSOUND_REVERB_FX_ENABLE;
        hiDpl2->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        hiDpl2->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        hiDpl2->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        hiDpl2->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        hiDpl2->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        result = AXFXReverbHiSettingsDpl2(hiDpl2);
        break;
    }
    }

    if (result != REDSOUND_REVERB_INIT_SUCCESS) {
        p_ReverbSize->m_aligned = 0;
        p_ReverbSize->m_requested = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c3628
 * PAL Size: 240b
 * EN Address: 0x8020554c
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ClearReverb(int bank)
{
    RedReverbDATA* reverb = p_ReverbData + (bank & REDSOUND_REVERB_BANK_MASK);
    if (reverb->m_callback == REDSOUND_REVERB_CALLBACK_NONE) {
        return;
    }

    if (bank == REDSOUND_REVERB_AUX_A) {
        AXRegisterAuxACallback((void (*)(void*, void*))_ReverbNullCallback, REDSOUND_REVERB_CONTEXT_NONE);
    } else {
        AXRegisterAuxBCallback((void (*)(void*, void*))_ReverbNullCallback, REDSOUND_REVERB_CONTEXT_NONE);
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

    reverb->m_callback = REDSOUND_REVERB_CALLBACK_NONE;
    RedDelete((int)reverb->m_context);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: UNUSED
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _CompFX(float a, float b)
{
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x801c3718
 * PAL Size: 1324b
 * EN Address: 0x8020563c
 * EN Size: 1324b
 * JP Address: TODO
 * JP Size: TODO
 */
RedReverbSize* SetReverb(int bank, int kind, int* params)
{
    RedReverbDATA* reverb;
    int result;

    p_ReverbSize->m_requested = p_ReverbSize->m_aligned = 0;

    if (kind == REDSOUND_REVERB_KIND_NONE) {
        _ClearReverb(bank);
        return p_ReverbSize;
    }

    if (kind == REDSOUND_REVERB_KIND_HI_DPL2) {
        return 0;
    }

    reverb = p_ReverbData + (bank & REDSOUND_REVERB_BANK_MASK);
    if ((reverb->m_callback != REDSOUND_REVERB_CALLBACK_NONE) && (reverb->m_kind == kind)) {
        _SetReverbData(reverb, params);
        return p_ReverbSize;
    }

    _ClearReverb(bank);
    if (kind == REDSOUND_REVERB_KIND_HI_DPL2) {
        _ClearReverb(REDSOUND_REVERB_AUX_B);
    }

    reverb->m_kind = (RedReverbKind)kind;
    switch (kind) {
    case REDSOUND_REVERB_KIND_STD: {
        reverb->m_context = (void*)RedNew(sizeof(AXFX_REVERBSTD));
        reverb->m_callback = (int)AXFXReverbStdCallback;
        AXFX_REVERBSTD* std = (AXFX_REVERBSTD*)reverb->m_context;
        std->tempDisableFX = REDSOUND_REVERB_FX_ENABLE;
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
        hi->tempDisableFX = REDSOUND_REVERB_FX_ENABLE;
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
        hiDpl2->tempDisableFX = REDSOUND_REVERB_FX_ENABLE;
        hiDpl2->preDelay = (float)params[REDSOUND_REVERB_PARAM_PRE_DELAY] / s_ReverbTimeScale;
        hiDpl2->time = (float)params[REDSOUND_REVERB_PARAM_TIME] / s_ReverbTimeScale;
        hiDpl2->coloration = (float)params[REDSOUND_REVERB_PARAM_COLORATION] / s_ReverbEffectScale;
        hiDpl2->damping = (float)params[REDSOUND_REVERB_PARAM_DAMPING] / s_ReverbEffectScale;
        hiDpl2->mix = (float)params[REDSOUND_REVERB_PARAM_MIX] / s_ReverbEffectScale;
        result = AXFXReverbHiInitDpl2(hiDpl2);
        break;
    }
    }

    if (result == REDSOUND_REVERB_INIT_SUCCESS) {
        if (bank == REDSOUND_REVERB_AUX_A) {
            AXRegisterAuxACallback((void (*)(void*, void*))reverb->m_callback, reverb->m_context);
        }
        else {
            AXRegisterAuxBCallback((void (*)(void*, void*))reverb->m_callback, reverb->m_context);
        }
    }
    else {
        p_ReverbSize->m_requested = p_ReverbSize->m_aligned = 0;
    }

    return p_ReverbSize;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: UNUSED
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
RedReverbSize* GetReverbInfo()
{
    return p_ReverbSize;
}

/*
 * --INFO--
 * PAL Address: 0x801c3c44
 * PAL Size: 368b
 * EN Address: 0x80205b68
 * EN Size: 368b
 * JP Address: TODO
 * JP Size: TODO
 */
RedVoiceDATA* EntryVoiceSearch(RedTrackDATA* track)
{
    RedVoiceDATA* voice;
    int bestEnvelope;
    RedVoiceDATA* voiceEnd;
    RedVoiceDATA* bestVoice = REDSOUND_VOICE_DATA_NONE;

    if ((static_cast<s8>(track->m_note.m_allocFlags) & REDSOUND_NOTE_ALLOC_DIRECT_MASK) != 0) {
        if (((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT) != 0) ||
            ((p_VoiceData + track->m_trackNo)->m_track == REDSOUND_VOICE_TRACK_NONE) ||
            ((p_VoiceData + track->m_trackNo)->m_track == track)) {
            voice = p_VoiceData + track->m_trackNo;
        } else {
            voice = REDSOUND_VOICE_DATA_NONE;
        }
    } else {
        if ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_PRIORITY) != 0) {
            voice = p_VoiceData;
        } else {
            voice = p_VoiceData + (s8)p_SoundControl->m_channelAlloc;
        }

        bestEnvelope = REDSOUND_ENVELOPE_LEVEL_FULL;
        voiceEnd = p_VoiceData + REDSOUND_VOICE_COUNT;
        do {
            if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) == 0) {
                if (voice->m_envelopeLevel < 1) {
                    if (voice->m_track != REDSOUND_VOICE_TRACK_NONE) {
                        voice->m_track = REDSOUND_VOICE_TRACK_NONE;
                    }
                    break;
                }

                if (voice->m_envelopeLevel < bestEnvelope) {
                    bestVoice = voice;
                    bestEnvelope = voice->m_envelopeLevel;
                }
            }
            voice++;
        } while (voice < voiceEnd);

        if (voice == voiceEnd) {
            RedVoiceDATA* selectedVoice;
            p_SoundControl->m_updateFlags |= REDSOUND_CONTROL_UPDATE_VOICE_STEAL;
            if (bestEnvelope == REDSOUND_ENVELOPE_LEVEL_FULL) {
                selectedVoice = REDSOUND_VOICE_DATA_NONE;
            } else {
                selectedVoice = bestVoice;
            }
            voice = selectedVoice;
        }
    }

    if (voice != REDSOUND_VOICE_DATA_NONE) {
        voice->m_flags &= ~REDSOUND_VOICE_FLAGS_RELEASED;
        voice->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
    }

    return voice;
}

/*
 * --INFO--
 * PAL Address: 0x801c3db4
 * PAL Size: 68b
 * EN Address: 0x80205cd8
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _VoiceEnvelopeCheck()
{
    RedVoiceDATA* voiceData = p_VoiceData;
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
 * EN Address: 0x80205d1c
 * EN Size: 720b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetVoiceVolumeMix(RedVoiceDATA* voice, int pan, int volume)
{
    int auxLeftMix;
    int auxRightMix;
    RedTrackDATA* trackData = voice->m_track;
    AXPBMIX* mixData;

    if (trackData == 0) {
        return;
    }

    mixData = &voice->m_axMix;
    memset(mixData, 0, sizeof(*mixData));

    switch (m_SoundPlayMode) {
    case REDSOUND_SOUND_MODE_MONO:
        auxLeftMix = (volume * t_PanningData[REDSOUND_PAN_BYTE_CENTER]) >> 8;

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_STEREO) != 0) {
            mixData->vL = (u16)auxLeftMix;
            mixData->vR = (u16)auxLeftMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_STEREO) != 0) {
            auxLeftMix =
                (auxLeftMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData->vAuxAL = (u16)auxLeftMix;
                mixData->vAuxAR = (u16)auxLeftMix;
            } else {
                mixData->vAuxBL = (u16)auxLeftMix;
                mixData->vAuxBR = (u16)auxLeftMix;
            }
        }
        break;
    case REDSOUND_SOUND_MODE_SURROUND:
        mixData->vL = (u16)((volume * t_PanningData[pan]) >> 8);
        mixData->vAuxBL = (u16)((volume * t_PanningDataR[pan]) >> 8);
        mixData->vR = (u16)((volume * t_PanningData[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8);
        mixData->vAuxBR = (u16)((volume * t_PanningDataR[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8);

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_LEFT) != 0) {
            mixData->vAuxAL =
                (u16)((int)((u32)mixData->vL * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT);
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

        auxLeftMix = (volume * t_PanningData[pan]) >> 8;
        auxRightMix = (volume * t_PanningData[pan ^ REDSOUND_PAN_BYTE_MASK]) >> 8;

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_LEFT) != 0) {
            mixData->vL = (u16)auxLeftMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_DRY_RIGHT) != 0) {
            mixData->vR = (u16)auxRightMix;
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_LEFT) != 0) {
            auxLeftMix = (auxLeftMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData->vAuxAL = (u16)auxLeftMix;
            } else {
                mixData->vAuxBL = (u16)auxLeftMix;
            }
        }

        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_RIGHT) != 0) {
            auxRightMix = (auxRightMix * ((trackData->m_reverbDepth >> REDSOUND_FIXED_SHIFT) + 1)) >> REDSOUND_AX_MIX_SHIFT;
            if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                mixData->vAuxAR = (u16)auxRightMix;
            } else {
                mixData->vAuxBR = (u16)auxRightMix;
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
 * EN Address: 0x80205fec
 * EN Size: 664b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _VolumeExecute(RedVoiceDATA* voice, int volume)
{
    int modVolume;
    int tremoloValue;
    int pan;
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
            tremoloValue = voice->m_volumeModFrames;
            envelopeMul = voice->m_track->m_tremoloFunc((unsigned int)voice->m_volumeModPhase >> REDSOUND_FIXED_SHIFT);
            modVolume = modVolume * (envelopeMul >> REDSOUND_VOLUME_MOD_WAVE_SHIFT) >> REDSOUND_FIXED_SHIFT;

            if (tremoloValue != 0) {
                envelopeMul = voice->m_volumeModFrame;
                voice->m_volumeModFrame = voice->m_volumeModFrame + 1;
                modVolume = (modVolume * envelopeMul) / tremoloValue;
                if (voice->m_volumeModFrame >= tremoloValue) {
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

    if (m_SoundPlayMode == REDSOUND_SOUND_MODE_MONO) {
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
        pan &= REDSOUND_PAN_BYTE_WRAP - 1;
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
 * EN Address: 0x80206284
 * EN Size: 428b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _PitchExecute(RedVoiceDATA* voice)
{
    int pitchDelta = 0;
    int targetPitchDelta = 0;

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

        if (pitchDelta < 0) {
            targetPitchDelta = pitchDelta >> 1;
        } else {
            targetPitchDelta = pitchDelta;
        }

        voice->m_pitchModPhase += voice->m_track->m_vibrateRate;
        pitchDelta = targetPitchDelta;
    }

    voice->m_targetPitch = pitchDelta + voice->m_pitch + voice->m_randomPitch;
    voice->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
}

/*
 * --INFO--
 * PAL Address: 0x801c450c
 * PAL Size: 180b
 * EN Address: 0x80206430
 * EN Size: 180b
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: 0x802064e4
 * EN Size: 1568b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _VoiceDataAsign(RedTrackDATA* track, RedVoiceDATA* voice, RedNoteDATA* noteData, int* voiceMask)
{
    int workValue;
    int pitchWork;

    workValue = 0;
    voice->m_track = track;
    voice->m_active = REDSOUND_VOICE_ACTIVE_ON;

    if ((track->m_portamentTime != 0) &&
        (track->m_portamentPitch >= 0)) {
        track->m_portamentPitch &= REDSOUND_FIXED_WHOLE_MASK;
        voice->m_basePitch = track->m_portamentPitch;
        track->m_sweepDelta = track->m_portamentTime;
        pitchWork = 0;
        workValue = noteData->m_key * REDSOUND_PITCH_NOTE_UNIT -
                    (track->m_portamentPitch >> REDSOUND_FIXED_SHIFT);
        track->m_sweepAdd = DataAddCompute(&pitchWork, workValue, &track->m_sweepDelta);
    } else {
        track->m_portamentPitch = noteData->m_key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
        if (voice->m_waveData != 0) {
            if ((voice->m_waveData->m_flags & REDSOUND_WAVE_FLAG_USE_WAVE_KEY) != 0) {
                voice->m_basePitch =
                    voice->m_waveData->m_splitKey << REDSOUND_PITCH_BASE_NOTE_SHIFT;
            } else {
                voice->m_basePitch = noteData->m_key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
                if (voice->m_track->m_keySignatureData != 0) {
                    pitchWork = voice->m_basePitch >> REDSOUND_PITCH_BASE_NOTE_SHIFT;
                    pitchWork =
                        voice->m_track->m_keySignatureData[pitchWork % REDSOUND_NOTES_PER_OCTAVE];
                    voice->m_basePitch += pitchWork * REDSOUND_PITCH_KEY_SIGNATURE_UNIT;
                }
            }
        }
    }

    *(int*)&voice->m_key = *(int*)noteData;
    voice->m_trackVolume = &track->m_volume;
    voice->m_trackExpression = &track->m_expression;
    voice->m_trackPan = &track->m_pan;

    if (voice->m_waveData != 0) {
        memcpy(&voice->m_adsr,
               track->m_waveData->m_adsr,
               sizeof(voice->m_adsr));
    } else {
        memset(&voice->m_adsr, 0, sizeof(voice->m_adsr));
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

    pitchWork = track->m_keyTranspose + track->m_pitchBend;
    if ((voice->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0) {
        workValue = voice->m_basePitch + track->m_pitch;
    } else {
        workValue = voice->m_basePitch + p_MusicPitchControl->m_value;
    }

    if (voice->m_waveData != 0) {
        workValue = PitchCompute(workValue, pitchWork, voice->m_waveData->m_pitch, track->m_fineTune);
    } else {
        workValue = 0;
    }
    voice->m_pitch = workValue;

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
        pitchWork = REDSOUND_MOD_DELAY_PHASE_SCALE;
        if ((track->m_vibrateRate >> REDSOUND_FIXED_SHIFT) != 0) {
            pitchWork =
                pitchWork / (track->m_vibrateRate >> REDSOUND_FIXED_SHIFT);
        }
        if (track->m_vibrateDelayDepth != 0) {
            workValue = track->m_vibrateDelayDepth * (pitchWork * REDSOUND_MOD_DELAY_FRAME_SCALE);
        } else {
            workValue = 0;
        }
        voice->m_pitchModFrames = workValue;
        voice->m_pitchModFrame = 0;
        voice->m_pitchModPhase = 0;
    }

    if (voice->m_track->m_tremoloFunc != 0) {
        voice->m_volumeModDelay = track->m_tremoloDelay;
        pitchWork = REDSOUND_MOD_DELAY_PHASE_SCALE;
        if ((track->m_tremoloRate >> REDSOUND_FIXED_SHIFT) != 0) {
            pitchWork =
                pitchWork / (track->m_tremoloRate >> REDSOUND_FIXED_SHIFT);
        }
        if (track->m_tremoloDelayDepth != 0) {
            workValue = track->m_tremoloDelayDepth * (pitchWork * REDSOUND_MOD_DELAY_FRAME_SCALE);
        } else {
            workValue = 0;
        }
        voice->m_volumeModFrames = workValue;
        voice->m_volumeModFrame = 0;
        voice->m_volumeModPhase = 0;
    }

skipModSetup:

    if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_PITCH) != 0) {
        unsigned int random = GetRandomData();
        unsigned int randomSign = random & REDSOUND_RANDOM_BYTE_SIGN_BIT;
        int randomScale = (int)(random & REDSOUND_RANDOM_BYTE_MASK) + 1;
        pitchWork = voice->m_track->m_fuzzyPitchDepth;
        workValue = voice->m_pitch * pitchWork;
        workValue *= randomScale;
        pitchWork = workValue >> REDSOUND_RANDOM_FUZZY_PITCH_SHIFT;
        if (randomSign != 0) {
            voice->m_randomPitch = -(pitchWork >> 1);
        } else {
            voice->m_randomPitch = pitchWork;
        }
    } else {
        voice->m_randomPitch = 0;
    }

    if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_VOLUME) != 0) {
        voice->m_randomVolume =
            (track->m_fuzzyVolumeDepth * (s8)GetRandomData()) >> REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT;
    } else {
        voice->m_randomVolume = 0;
    }

    if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_PAN) != 0) {
        voice->m_randomPan =
            (track->m_fuzzyPanDepth * (s8)GetRandomData()) >> REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT;
    } else {
        voice->m_randomPan = 0;
    }

    if (voice->m_waveData != 0) {
        memcpy(&voice->m_adsr,
               voice->m_waveData->m_adsr,
               sizeof(voice->m_adsr));
        if ((s8)track->m_adsr.m_level[REDSOUND_VOICE_ADSR_ATTACK] != (s8)REDSOUND_TRACK_ADSR_DEFAULT_BYTE) {
            voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_ATTACK] =
                track->m_adsr.m_level[REDSOUND_VOICE_ADSR_ATTACK];
        }
        if ((s16)track->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK] != REDSOUND_TRACK_ADSR_DEFAULT_WORD) {
            voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK] =
                track->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK];
        }
        if ((s8)track->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY] != (s8)REDSOUND_TRACK_ADSR_DEFAULT_BYTE) {
            voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY] =
                track->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY];
        }
        if ((s16)track->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY] != REDSOUND_TRACK_ADSR_DEFAULT_WORD) {
            voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY] =
                track->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY];
        }
        if ((s8)track->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN] != (s8)REDSOUND_TRACK_ADSR_DEFAULT_BYTE) {
            voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN] =
                track->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN];
        }
        if ((s16)track->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN] != REDSOUND_TRACK_ADSR_DEFAULT_WORD) {
            voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN] =
                track->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN];
        }
        if ((s8)track->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE] != (s8)REDSOUND_TRACK_ADSR_DEFAULT_BYTE) {
            voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE] =
                track->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE];
        }
        if ((s16)track->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE] != REDSOUND_TRACK_ADSR_DEFAULT_WORD) {
            voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE] =
                track->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE];
        }
        if ((voice->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_ADSR) != 0) {
            pitchWork = track->m_fuzzyAdsrDepth * (GetRandomData() & REDSOUND_RANDOM_BYTE_MASK);
            voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK] = (u16)pitchWork;
        }
    } else {
        memset(&voice->m_adsr, 0, sizeof(voice->m_adsr));
    }

    workValue = voice - p_VoiceData;
    if (REDSOUND_VOICE_INDEX_MASK < workValue) {
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
 * PAL Address: 0x801c4be0
 * PAL Size: 296b
 * EN Address: 0x80206b04
 * EN Size: 296b
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: UNUSED
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetAllVoiceAccess(RedSoundCONTROL* control, int mask)
{
    RedTrackDATA* track = control->m_tracks;
    RedTrackDATA* trackEnd = track + control->m_trackCount;
    do {
        if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
            SetVoiceAccess(track, mask);
        }
        track++;
    } while (track < trackEnd);
}

/*
 * --INFO--
 * PAL Address: 0x801c4d08
 * PAL Size: 80b
 * EN Address: 0x80206c2c
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetVoiceAccess(RedTrackDATA* track, int mask)
{
    RedVoiceDATA* voiceData = p_VoiceData;
    do {
        if ((voiceData->m_track != REDSOUND_VOICE_TRACK_NONE) && (voiceData->m_track == track)) {
            voiceData->m_flags |= mask;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801c4d58
 * PAL Size: 72b
 * EN Address: 0x80206c7c
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetVoiceSwitch(RedTrackDATA* track, int voiceSwitch)
{
    RedVoiceDATA* voiceData = p_VoiceData;
    do {
        if ((voiceData->m_track != REDSOUND_VOICE_TRACK_NONE) && (voiceData->m_track == track)) {
            voiceData->m_voiceSwitch = voiceSwitch;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801c4da0
 * PAL Size: 188b
 * EN Address: 0x80206cc4
 * EN Size: 188b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _AdsrStart(RedVoiceDATA* voice)
{
    int* stage = &voice->m_adsrStage;
    RedAdsrDATA* adsrData = &voice->m_adsr;
    int prevLevel;
    int nextLevel;
    int stepFrames;

    nextLevel = adsrData->m_level[REDSOUND_VOICE_ADSR_ATTACK];
    *stage    = 0;
    do {
        prevLevel = nextLevel;
        stepFrames = adsrData->m_time[*stage];
        nextLevel = RedAdsrGetStageLevel(adsrData, *stage);
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
        voice->m_adsrStepAdd = (nextLevel - prevLevel) / stepFrames;
    } else {
        voice->m_adsrCurrentLevel = nextLevel;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c4e5c
 * PAL Size: 164b
 * EN Address: 0x80206d80
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _AdsrDataCompute(RedVoiceDATA* voice)
{
    RedAdsrDATA* adsrData = &voice->m_adsr;
    int prevValue;
    int stepCount;
    int level;
    int* stage = &voice->m_adsrStage;

    level = voice->m_adsrCurrentLevel;
    stepCount = 0;
    while (*stage < REDSOUND_VOICE_ADSR_STAGE_COUNT) {
        prevValue = level;
        level = RedAdsrGetStageLevel(adsrData, *stage);
        stepCount = adsrData->m_time[*stage];
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
 * EN Address: 0x80206e24
 * EN Size: 212b
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
 * EN Address: 0x80206ef8
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _VoiceDropedCallback(void* dropped)
{
    RedVoiceDATA* voiceData;
    
    voiceData = p_VoiceData;
    do {
        if ((voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE) && (voiceData->m_axVoice == dropped)) {
            voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
            voiceData->m_track = REDSOUND_VOICE_TRACK_NONE;
            voiceData->m_axVoice = REDSOUND_AX_VOICE_NONE;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801c5030
 * PAL Size: 1268b
 * EN Address: 0x80206f54
 * EN Size: 1268b
 * JP Address: TODO
 * JP Size: TODO
 */
void EnvelopeKeyExecute()
{
    RedVoiceDATA* voiceData = p_VoiceData;
    int voiceIndex = 0;

    do {
        if (voiceData->m_active != REDSOUND_VOICE_ACTIVE_OFF) {
            AXVPB* voice;

            if ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_START) != 0) {
                voice = voiceData->m_axVoice;
                if ((voice != REDSOUND_AX_VOICE_NONE) && (voice->priority != 0)) {
                    AXFreeVoice(voice);
                    voiceData->m_axVoice = REDSOUND_AX_VOICE_NONE;
                }

                if ((voiceData->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0) {
                    voiceData->m_axVoice = AXAcquireVoice(REDSOUND_VOICE_INDEX_MASK, _VoiceDropedCallback, 0);
                } else {
                    int prio = voiceData - p_VoiceData;
                    prio = (REDSOUND_VOICE_COUNT - prio >> 1) - 1;
                    if (prio < 1) {
                        prio = 1;
                    }
                    voiceData->m_axVoice = AXAcquireVoice(prio, _VoiceDropedCallback, 0);
                }
            }

            voice = voiceData->m_axVoice;
            if (voice == REDSOUND_AX_VOICE_NONE) {
                voiceData->m_flags = 0;
                voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
                return;
            }

            u32 voiceFlags = 0;
            u32 envChanged = 0;

            if ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_PITCH_DIRTY) != 0) {
                int pitch = voiceData->m_targetPitch;
                voiceFlags = AX_SYNC_FLAG_COPYRATIO;
                voice->pb.src.ratioHi = (u16)(((u32)pitch >> REDSOUND_AX_HIGH_WORD_SHIFT) & REDSOUND_AX_SRC_RATIO_HI_MASK);
                voice->pb.src.ratioLo = (u16)pitch;
            }

            if ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_ADPCM_DIRTY) != 0) {
                if ((voiceData->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAUSE) == 0) {
                    memcpy(&voice->pb.mix, &voiceData->m_axMix, sizeof(voice->pb.mix));
                } else {
                    memset(&voice->pb.mix, 0, sizeof(voice->pb.mix));
                }

                voice->pb.mixerCtrl = REDSOUND_AX_MIX_CTRL_DRY_STEREO;
                if ((voiceData->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_STEREO) != 0) {
                    if ((voiceData->m_voiceSwitch & REDSOUND_VOICE_SWITCH_REVERB_AUX_A) != 0) {
                        voice->pb.mixerCtrl |= REDSOUND_AX_MIX_CTRL_AUX_A_STEREO;
                    } else {
                        voice->pb.mixerCtrl |= REDSOUND_AX_MIX_CTRL_AUX_B_STEREO;
                    }
                }
                voiceFlags |= AX_SYNC_FLAG_COPYAXPBMIX | AX_SYNC_FLAG_COPYMXRCTRL;
            }

            if (((voiceData->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAUSE) == 0) &&
                ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_ADSR_START) != 0)) {
                _AdsrStart(voiceData);
                envChanged = 1;
            }

            if ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_START) != 0) {
                voiceData->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK;
                RedWaveDATA* waveData = voiceData->m_waveData;
                RedTrackDATA* trackData = voiceData->m_track;
                if ((waveData != 0) && (trackData != 0)) {
                    envChanged += 1;
                    u16 loopFlag;
                    if ((voiceData->m_voiceSwitch & REDSOUND_VOICE_SWITCH_LOOP) != 0) {
                        loopFlag = REDSOUND_AX_VOICE_TYPE_LOOP;
                    } else {
                        loopFlag = REDSOUND_AX_VOICE_TYPE_ONE_SHOT;
                    }
                    voice->pb.type = loopFlag;
                    voice->pb.srcSelect = REDSOUND_AX_SRC_SELECT_ADPCM;
                    voice->pb.state = REDSOUND_AX_VOICE_PLAY;

                    memcpy(&voice->pb.adpcm, &waveData->m_adpcm.m_data, sizeof(voice->pb.adpcm));
                    memcpy(&voice->pb.adpcmLoop, &waveData->m_adpcm.m_loop, sizeof(voice->pb.adpcmLoop));
                    memset(voice->pb.src.last_samples, 0, sizeof(voice->pb.src.last_samples));
                    voice->pb.addr.format = REDSOUND_AX_ADDR_FORMAT_ADPCM;
                    int key = trackData->m_waveBase + waveData->m_sampleStart;
                    key += REDSOUND_AX_SAMPLE_START_BIAS;
                    key *= REDSOUND_AX_SAMPLE_ADDR_SCALE;
                    voice->pb.addr.currentAddressHi = (u16)(key >> REDSOUND_AX_HIGH_WORD_SHIFT);
                    voice->pb.addr.currentAddressLo = (u16)key;
                    int keyBase = key - REDSOUND_AX_SAMPLE_ADDR_SCALE;

                    if (waveData->m_loopStart < 0) {
                        voice->pb.addr.loopFlag = REDSOUND_AX_VOICE_LOOP_OFF;
                        key = keyBase;
                    } else {
                        voice->pb.addr.loopFlag = REDSOUND_AX_VOICE_LOOP_ON;
                        key = keyBase + waveData->m_loopStart;
                    }

                    voice->pb.addr.loopAddressHi = (u16)(key >> REDSOUND_AX_HIGH_WORD_SHIFT);
                    voice->pb.addr.loopAddressLo = (u16)key;
                    key = keyBase + waveData->m_loopEnd;
                    voice->pb.addr.endAddressHi = (u16)(key >> REDSOUND_AX_HIGH_WORD_SHIFT);
                    voice->pb.addr.endAddressLo = (u16)key;

                    voiceFlags |= AX_SYNC_FLAG_COPYADPCMLOOP | AX_SYNC_FLAG_COPYSRC | AX_SYNC_FLAG_COPYADPCM |
                                  AX_SYNC_FLAG_COPYCURADDR | AX_SYNC_FLAG_COPYADDR | AX_SYNC_FLAG_COPYTYPE |
                                  AX_SYNC_FLAG_COPYSTATE | AX_SYNC_FLAG_COPYSELECT;
                    voiceData->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_START;
                    voiceData->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
                    voiceData->m_adsrCurrentLevel = 0;
                } else {
                    voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
                }
            } else {
                if ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_RELEASED) != 0) {
                    voiceData->m_flags |= REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE;
                    voiceData->m_adsrStage = REDSOUND_VOICE_ADSR_RELEASE;
                    voiceData->m_adsrStepFrames = voiceData->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE];
                    if (voiceData->m_adsrStepFrames != 0) {
                        voiceData->m_adsrStepAdd = -voiceData->m_adsrCurrentLevel;
                        voiceData->m_adsrStepAdd = voiceData->m_adsrStepAdd / voiceData->m_adsrStepFrames;
                    } else {
                        voiceData->m_adsrCurrentLevel = 0;
                    }
                    voiceData->m_envelopeLevel = voiceData->m_adsrCurrentLevel >> REDSOUND_FIXED_SHIFT;
                } else {
                    if ((voiceData->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAUSE) == 0) {
                        if ((voiceData->m_flags & REDSOUND_VOICE_FLAGS_ADSR_START) == 0) {
                            envChanged |= _AdsrDataExecute(voiceData);
                            voiceData->m_envelopeLevel = voiceData->m_adsrCurrentLevel >> REDSOUND_FIXED_SHIFT;
                        }
                        voiceData->m_flags &= ~REDSOUND_VOICE_FLAGS_ADSR_START;
                    }
                }
            }

            if (voiceData->m_envelopeLevel < 1) {
                voiceData->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK;
                voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
                voiceFlags |= AX_SYNC_FLAG_COPYVOL;
                voiceData->m_track = REDSOUND_VOICE_TRACK_NONE;
                voice->pb.state = REDSOUND_AX_VOICE_STOP;
                voiceData->m_adsrCurrentLevel = 0;
                voiceData->m_envelopeLevel = 0;
                voice->pb.ve.currentVolume = 0;
                voice->pb.ve.currentDelta = 0;
                voiceFlags |= AX_SYNC_FLAG_COPYSTATE;
            } else if ((envChanged != 0) &&
                       ((u32)voice->pb.ve.currentVolume !=
                        ((voiceData->m_adsrCurrentLevel >> REDSOUND_FIXED_SHIFT) & 0xFFFFU))) {
                voiceFlags |= AX_SYNC_FLAG_COPYVOL;
                voice->pb.ve.currentDelta = 0;
                voice->pb.ve.currentVolume = (u16)(voiceData->m_adsrCurrentLevel >> REDSOUND_FIXED_SHIFT);
            }

            voice->sync |= voiceFlags;
        } else {
            voiceData->m_envelopeLevel = 0;
            voiceData->m_waveData = REDSOUND_WAVE_DATA_NONE;
            AXVPB* voice = voiceData->m_axVoice;
            if (voice != REDSOUND_AX_VOICE_NONE) {
                if (voice->pb.state != REDSOUND_AX_VOICE_STOP) {
                    voice->pb.state = REDSOUND_AX_VOICE_STOP;
                    voice->pb.ve.currentVolume = 0;
                    voice->sync |= AX_SYNC_FLAG_COPYVOL | AX_SYNC_FLAG_COPYSTATE;
                } else {
                    if (voice->priority != 0) {
                        AXFreeVoice(voice);
                    }
                    voiceData->m_axVoice = REDSOUND_AX_VOICE_NONE;
                    voiceData->m_track = REDSOUND_VOICE_TRACK_NONE;
                }
            }
        }

        voiceData->m_flags &= REDSOUND_VOICE_FLAGS_EXECUTE_KEEP_MASK;
        voiceIndex++;
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801c5524
 * PAL Size: 1304b
 * EN Address: 0x80207448
 * EN Size: 1304b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _KeyOnControl()
{
    int voiceStartMask[REDSOUND_VOICE_START_MASK_COUNT];
    RedKeyOnSlot* reserve;
    RedVoiceDATA* voiceData;
    RedSwingFunc waveFunc;
    int shakeDepth;
    RedSoundCONTROL* soundControl;
    RedTrackDATA* track;
    RedTrackDATA* trackData;
    RedVoiceDATA* voice;
    int volume;
    int idx;
    int bit;

    _VoiceEnvelopeCheck();
    voiceStartMask[REDSOUND_VOICE_START_MASK_HIGH] = 0;
    voiceStartMask[REDSOUND_VOICE_START_MASK_LOW] = 0;

    if (m_KeyOnEntry != 0) {
        reserve = p_KeyOnData->m_fixed;
        voiceData = p_VoiceData;
        do {
            if ((reserve->m_track != 0) && (reserve->m_track->m_waveData != 0)) {
                voiceData = _VoiceDataSelect(reserve->m_track, &reserve->m_note, voiceStartMask);
            }
            reserve++;
        } while ((voiceData != 0) && (reserve < p_KeyOnData->m_normal + REDSOUND_KEY_ON_SLOT_COUNT));
    }

    soundControl = p_SoundControlBuffer;
    if ((soundControl->m_activeTrackCount != 0) &&
        ((soundControl->m_flags & REDSOUND_CONTROL_FLAG_PAUSE) == 0)) {
        track = soundControl->m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                shakeDepth = (track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1;
                track->m_shakePan =
                    (shakeDepth * waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT)) >>
                    REDSOUND_SHAKE_PAN_SCALE_SHIFT;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track < soundControl->m_tracks + soundControl->m_trackCount);
    }

    soundControl = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY;
    if ((soundControl->m_activeTrackCount != 0) &&
        ((soundControl->m_flags & REDSOUND_CONTROL_FLAG_PAUSE) == 0)) {
        track = soundControl->m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                shakeDepth = (track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1;
                track->m_shakePan =
                    (shakeDepth * waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT)) >>
                    REDSOUND_SHAKE_PAN_SCALE_SHIFT;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track < soundControl->m_tracks + soundControl->m_trackCount);
    }

    {
        soundControl = p_SoundControlBuffer + REDSOUND_CONTROL_SE;
        track = soundControl->m_tracks;
        do {
            if ((track->m_command != 0) && (track->m_shakeFunc != 0)) {
                waveFunc = track->m_shakeFunc;
                shakeDepth = (track->m_shakeDepth >> REDSOUND_FIXED_SHIFT) + 1;
                track->m_shakePan =
                    (shakeDepth * waveFunc((u32)track->m_shakeOutput >> REDSOUND_FIXED_SHIFT)) >>
                    REDSOUND_SHAKE_PAN_SCALE_SHIFT;
                track->m_shakeOutput += track->m_shakeRate;
            }
            track++;
        } while (track < soundControl->m_tracks + REDSOUND_SE_TRACK_COUNT);
    }

    {
        voice = p_VoiceData;
        do {
            if ((voice->m_active != REDSOUND_VOICE_ACTIVE_OFF) && (voice->m_track != 0) &&
                ((voice->m_track->m_voiceSwitch & REDSOUND_VOICE_SWITCH_SKIP_UPDATE) == 0)) {
                if ((voice->m_updateFlags & REDSOUND_VOICE_UPDATE_VOLUME) != 0 ||
                    (voice->m_track->m_tremoloFunc != 0) ||
                    (voice->m_track->m_shakeFunc != 0)) {
                    soundControl = p_SoundControlBuffer;
                    trackData = voice->m_track;
                    if ((soundControl->m_tracks <= trackData) &&
                        (trackData < soundControl->m_tracks + soundControl->m_trackCount)) {
                        idx = trackData->m_trackNo;
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
                            idx = trackData->m_trackNo;

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
        bit = 1;
        voice = p_VoiceData;
        do {
            if ((voiceStartMask[REDSOUND_VOICE_START_MASK_LOW] & bit) != 0) {
                voiceStartMask[REDSOUND_VOICE_START_MASK_LOW] &= ~bit;
                voice->m_flags |= REDSOUND_VOICE_FLAGS_START;
            }
            bit <<= 1;
            voice++;
        } while (voiceStartMask[REDSOUND_VOICE_START_MASK_LOW] != 0);
    }

    {
        bit = 1;
        voice = p_VoiceData + REDSOUND_MUTE_BITS_PER_WORD;
        do {
            if ((voiceStartMask[REDSOUND_VOICE_START_MASK_HIGH] & bit) != 0) {
                voiceStartMask[REDSOUND_VOICE_START_MASK_HIGH] &= ~bit;
                voice->m_flags |= REDSOUND_VOICE_FLAGS_START;
            }
            bit <<= 1;
            voice++;
        } while (voiceStartMask[REDSOUND_VOICE_START_MASK_HIGH] != 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c5a3c
 * PAL Size: 688b
 * EN Address: 0x80207960
 * EN Size: 688b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ExecuteExtraData()
{
    RedSoundCONTROL* soundControl;
    RedVoiceDATA* voice;
    RedTrackDATA* track;
    RedTrackDATA* musicBase;

    soundControl = p_SoundControlBuffer;
    do {
        if ((soundControl->m_masterVolumeDelta != 0) && (soundControl->m_tracks != 0)) {
            soundControl->m_masterVolumeDelta--;
            soundControl->m_masterVolume += soundControl->m_masterVolumeAdd;
            if ((soundControl->m_masterVolumeDelta == 0) && (soundControl->m_masterVolumeAdd < 0)) {
                MusicStop(soundControl->m_musicId);
            }

            if (soundControl->m_tracks != 0) {
                musicBase = soundControl->m_tracks;
                voice = p_VoiceData;
                do {
                    if ((voice->m_track >= musicBase) &&
                        (voice->m_track < musicBase + soundControl->m_trackCount)) {
                        voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
                    }
                    voice++;
                } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
            }
        }
        soundControl++;
    } while (soundControl < p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SKIP);

    soundControl = p_SoundControlBuffer;

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
                int pitchOffset = (int)voice->m_track->m_keyTranspose + (int)voice->m_track->m_pitchBend;
                voice->m_pitch = PitchCompute(voice->m_basePitch + p_MusicPitchControl->m_value, pitchOffset,
                                               voice->m_waveData->m_pitch,
                                               voice->m_track->m_fineTune);
                voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
            }
            voice++;
        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
    }

    do {
        if ((soundControl->m_activeTrackCount != 0) && (soundControl->m_volumeDelta != 0)) {
            soundControl->m_volumeDelta--;
            soundControl->m_volume += soundControl->m_volumeAdd;
            if ((soundControl->m_flags & REDSOUND_CONTROL_FLAG_STOP_ON_VOLUME_ZERO) != 0) {
                if ((soundControl->m_volumeDelta == 0) &&
                    (soundControl->m_musicId >= REDSOUND_MUSIC_ID_MIN)) {
                    MusicStop(soundControl->m_musicId);
                }
            } else {
                track = soundControl->m_tracks;
                do {
                    if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
                        voice = p_VoiceData;
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
        soundControl++;
    } while (soundControl < p_SoundControlBuffer + REDSOUND_CONTROL_SE);
}

/*
 * --INFO--
 * PAL Address: 0x801c5cec
 * PAL Size: 1200b
 * EN Address: 0x80207c10
 * EN Size: 1200b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicTrackDataExecute(RedTrackDATA* track, int frames)
{
    u32 updateFlags = 0;
    RedVoiceDATA* voiceData;

    track->m_playTime += frames;

    if (track->m_volumeDelta != 0) {
        int step;
        if (track->m_volumeDelta > frames) {
            step = frames;
        } else {
            step = track->m_volumeDelta;
        }
        updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_volumeDelta -= step;
        track->m_volume += track->m_volumeAdd * step;
    }

    if (track->m_expressionDelta != 0) {
        int step;
        if (track->m_expressionDelta > frames) {
            step = frames;
        } else {
            step = track->m_expressionDelta;
        }
        updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_expressionDelta -= step;
        track->m_expression += track->m_expressionAdd * step;
    }

    if (track->m_panDelta != 0) {
        int step;
        if (track->m_panDelta > frames) {
            step = frames;
        } else {
            step = track->m_panDelta;
        }
        updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_panDelta -= step;
        track->m_pan += track->m_panAdd * step;
    }

    if (track->m_reverbDepthDelta != 0) {
        int step;
        if (track->m_reverbDepthDelta > frames) {
            step = frames;
        } else {
            step = track->m_reverbDepthDelta;
        }
        updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
        track->m_reverbDepthDelta -= step;
        track->m_reverbDepth += track->m_reverbDepthAdd * step;
    }

    if (track->m_sweepDelta != 0) {
        int step;
        int addPitch;

        if (track->m_sweepDelta > frames) {
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
            if (track->m_vibrateRateDelta > frames) {
                step = frames;
            } else {
                step = track->m_vibrateRateDelta;
            }
            track->m_vibrateRateDelta -= (s16)step;
            track->m_vibrateRate += track->m_vibrateRateAdd * step;
        }
        if (track->m_vibrateDepthDelta != 0) {
            int step;
            if (track->m_vibrateDepthDelta > frames) {
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
            if (track->m_tremoloRateDelta > frames) {
                step = frames;
            } else {
                step = track->m_tremoloRateDelta;
            }
            track->m_tremoloRateDelta -= (s16)step;
            track->m_tremoloRate += track->m_tremoloRateAdd * step;
        }
        if (track->m_tremoloDepthDelta != 0) {
            int step;
            if (track->m_tremoloDepthDelta > frames) {
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
            if (track->m_shakeRateDelta > frames) {
                step = frames;
            } else {
                step = track->m_shakeRateDelta;
            }
            track->m_shakeRateDelta -= (s16)step;
            track->m_shakeRate += track->m_shakeRateAdd * step;
        }
        if (track->m_shakeDepthDelta != 0) {
            int step;
            if (track->m_shakeDepthDelta > frames) {
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
                if (voiceData->m_pitchModDelay > frames) {
                    step = frames;
                } else {
                    step = voiceData->m_pitchModDelay;
                }
                voiceData->m_pitchModDelay -= (s16)step;
            }
            if (voiceData->m_volumeModDelay != 0) {
                int step;
                if (voiceData->m_volumeModDelay > frames) {
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
 * EN Address: 0x802080c0
 * EN Size: 552b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MidiTrackExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    RedTrackDATA* track = control->m_tracks;
    do {
        if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
            int step;
            m_ChangeStatus = 0;
            if (track->m_deltaTime < frames) {
                step = track->m_deltaTime;
            } else {
                step = frames;
            }
            int execStep = step;
            track->m_deltaTime -= frames;
            _MusicTrackDataExecute(track, execStep);
            if (((track->m_flags & REDSOUND_TRACK_FLAG_TENUTO) == 0) && (track->m_deltaTime == 1)) {
                KeyOffSet(control, keyOnData, track);
            }
            while ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_deltaTime < 1)) {
                unsigned char* cmd = track->m_command;
                int delta;
                track->m_command = cmd + 1;
                RedMidiControlFunc func = p_MidiControl_Function[*cmd];
                func(control, keyOnData, track);
                if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
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
                            int fuzzyDelta = delta * track->m_fuzzyDeltaTimeDepth >> 8;
                            s8 random = (s8)GetRandomData();
                            delta += fuzzyDelta * random >> 7;
                            if (delta < 1) {
                                delta = 1;
                            }
                        }
                    }

                    if (track->m_deltaTime < -1) {
                        int clampedStep;
                        if (track->m_deltaTime + delta > 0) {
                            clampedStep = -track->m_deltaTime;
                        } else {
                            clampedStep = delta;
                        }
                        int execStep = clampedStep;
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
 * EN Address: 0x802082e8
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MusicMidiNoteExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* tick = &control->m_measure;

    frames <<= m_MusicFastSpeed;
    control->m_loopBase = frames;

    tick[REDSOUND_CONTROL_TICK_CURRENT] += frames;

    while (tick[REDSOUND_CONTROL_TICK_CURRENT] >= tick[REDSOUND_CONTROL_TICK_PER_MEASURE]) {
        tick[REDSOUND_CONTROL_TICK_MEASURE] += 1;
        tick[REDSOUND_CONTROL_TICK_CURRENT] -= tick[REDSOUND_CONTROL_TICK_PER_MEASURE];
    }

    if (control->m_activeTrackCount != 0) {
        _MidiTrackExecute(control, keyOnData, frames);
    }

    control->m_skipFrames = 1;
    if (m_MusicPhraseStop == REDSOUND_MUSIC_PHRASE_STOP_OFF) {
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
 * EN Address: 0x802083d4
 * EN Size: 340b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicNoteExecute()
{
    int i;
    u32 trackCount;
    RedTrackDATA* track;
    RedSavedTrackDATA* savedTrackData;
    int status = _MusicMidiNoteExecute(p_SoundControl, p_KeyOnData, 1);

    while ((status == 0) && (m_MusicPhraseStop == REDSOUND_MUSIC_PHRASE_STOP_OFF) &&
           ((p_SoundControl->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) != 0)) {
        p_SoundControl->m_activeTrackCount = p_SoundControl->m_savedActiveTrackCount;
        memcpy(&p_SoundControl->m_measure, &p_SoundControl->m_savedPosition, sizeof(RedSoundControlPosition));
        memcpy(&p_SoundControl->m_tempo, &p_SoundControl->m_savedTempo, sizeof(RedSoundControlTempo));

        track = p_SoundControl->m_tracks;
        trackCount = p_SoundControl->m_trackCount;
        savedTrackData = &p_SoundControl->m_savedTracks;
        i = 0;
        do {
            track->m_command = savedTrackData->m_command[i];
            track->m_deltaTime = savedTrackData->m_delta[i];
            track->m_flags = savedTrackData->m_flags[i];
            *(int*)&track->m_note = *(int*)&savedTrackData->m_note[i];
            track++;
            i++;
        } while (--trackCount != 0);

        status = _MusicMidiNoteExecute(p_SoundControl, p_KeyOnData, 1);
    }

    if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId < REDSOUND_MUSIC_ID_MIN) &&
        (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId < REDSOUND_MUSIC_ID_MIN) &&
        (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId < REDSOUND_MUSIC_ID_MIN)) {
        m_MusicPhraseStop = REDSOUND_MUSIC_PHRASE_STOP_OFF;
    }
}


/*
 * --INFO--
 * PAL Address: 0x801c6604
 * PAL Size: 304b
 * EN Address: 0x80208528
 * EN Size: 304b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MusicMidiNoteSkipExecute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, int frames)
{
    int* tick = &control->m_measure;
    do {
        control->m_skipFrames = frames;
        control->m_loopBase = frames;
        tick[REDSOUND_CONTROL_TICK_CURRENT] += frames;

        while (tick[REDSOUND_CONTROL_TICK_CURRENT] >= tick[REDSOUND_CONTROL_TICK_PER_MEASURE]) {
            tick[REDSOUND_CONTROL_TICK_MEASURE] += 1;
            tick[REDSOUND_CONTROL_TICK_CURRENT] -= tick[REDSOUND_CONTROL_TICK_PER_MEASURE];
        }

        if (control->m_activeTrackCount != 0) {
            _MidiTrackExecute(control, keyOnData, frames);
        }

        if (m_MusicSkipLine != 0) {
            if ((control->m_activeTrackCount != 0) && ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END) == 0)) {
                m_MusicSkipLine--;
                frames = tick[REDSOUND_CONTROL_TICK_PER_MEASURE];
                RedSleep(REDSOUND_MUSIC_SKIP_LOOP_SLEEP_US);
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
 * EN Address: 0x80208658
 * EN Size: 588b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SkipMusicEntry()
{
    RedKeyOnSlot* src;
    RedKeyOnSlot* dst;
    RedSoundCONTROL* soundControl;
    RedControlRamp volume;
    int keyOnEntryCount = 0;

    if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId >= REDSOUND_MUSIC_ID_MIN) {
        src = p_SkipKeyOn->m_fixed;
        dst = p_KeyOnData->m_fixed;
        do {
            if ((src->m_track != REDSOUND_TRACK_NONE) && (dst->m_track == REDSOUND_TRACK_NONE)) {
                dst->m_track = src->m_track;
                *(int*)&dst->m_note = *(int*)&src->m_note;
                keyOnEntryCount++;
                m_KeyOnEntry++;
            }
            src++;
            dst++;
        } while (src < p_SkipKeyOn->m_priority);

        src = p_SkipKeyOn->m_priority;
        dst = p_KeyOnData->m_priority;
        while (dst < p_KeyOnData->m_normal) {
            if (dst->m_track == REDSOUND_TRACK_NONE) {
                break;
            }
            dst++;
        }
        while ((dst < p_KeyOnData->m_normal) && (src < p_SkipKeyOn->m_normal)) {
            if (src->m_track != REDSOUND_TRACK_NONE) {
                dst->m_track = src->m_track;
                *(int*)&dst->m_note = *(int*)&src->m_note;
                dst++;
                keyOnEntryCount++;
                m_KeyOnEntry++;
            }
            src++;
        }

        src = p_SkipKeyOn->m_normal;
        dst = p_KeyOnData->m_normal;
        while (dst < p_KeyOnData->m_normal + REDSOUND_KEY_ON_SLOT_COUNT) {
            if (dst->m_track == REDSOUND_TRACK_NONE) {
                break;
            }
            dst++;
        }
        while ((dst < p_KeyOnData->m_normal + REDSOUND_KEY_ON_SLOT_COUNT) &&
               (src < p_SkipKeyOn->m_normal + REDSOUND_KEY_ON_SLOT_COUNT)) {
            if (src->m_track != REDSOUND_TRACK_NONE) {
                dst->m_track = src->m_track;
                *(int*)&dst->m_note = *(int*)&src->m_note;
                dst++;
                keyOnEntryCount++;
                m_KeyOnEntry++;
            }
            src++;
        }

        soundControl = p_SoundControlBuffer;
        if (soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId != REDSOUND_MUSIC_ID_NONE) {
            if (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId != REDSOUND_MUSIC_ID_NONE) {
                MusicStop(soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId);
            }
            memcpy(&soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY], soundControl, sizeof(*soundControl));
        }

        memcpy(soundControl, &soundControl[REDSOUND_CONTROL_MUSIC_SKIP], sizeof(*soundControl));
        memcpy(&volume, &soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_volume, sizeof(volume));
        memset(&soundControl[REDSOUND_CONTROL_MUSIC_SKIP], 0, sizeof(*soundControl));
        memcpy(&soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_volume, &volume, sizeof(volume));
        soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId = REDSOUND_MUSIC_ID_NONE;
    }

    RedDelete(p_SkipKeyOn);
    m_MusicSkipComplete = REDSOUND_MUSIC_SKIP_NOT_COMPLETE;
}


/*
 * --INFO--
 * PAL Address: 0x801c6980
 * PAL Size: 308b
 * EN Address: 0x802088a4
 * EN Size: 308b
 * JP Address: TODO
 * JP Size: TODO
 */
void MusicSkipFunction()
{
    int activeTrackCount;
    int trackIndex;
    unsigned int trackCount;
    RedSavedTrackDATA* savedTrackData;
    RedSoundCONTROL* control;
    RedTrackDATA* track;

    do {
        p_SkipKeyOn = (RedKeyOnDATA*)RedNew(sizeof(*p_SkipKeyOn));
        if (p_SkipKeyOn == 0) {
            RedSleep(REDSOUND_MUSIC_SKIP_RETRY_SLEEP_US);
        }
    } while (p_SkipKeyOn == 0);

    control = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SKIP;
    memset(p_SkipKeyOn, 0, sizeof(*p_SkipKeyOn));
    activeTrackCount = _MusicMidiNoteSkipExecute(control, p_SkipKeyOn, 1);
    while ((activeTrackCount == 0) && ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) != 0)) {
        control->m_activeTrackCount = control->m_savedActiveTrackCount;
        memcpy(&control->m_measure, &control->m_savedPosition, sizeof(RedSoundControlPosition));
        memcpy(&control->m_tempo, &control->m_savedTempo, sizeof(RedSoundControlTempo));
        savedTrackData = &control->m_savedTracks;
        track = control->m_tracks;
        trackCount = control->m_trackCount;
        trackIndex = 0;
        do {
            track->m_command = savedTrackData->m_command[trackIndex];
            track->m_deltaTime = savedTrackData->m_delta[trackIndex];
            track->m_flags = savedTrackData->m_flags[trackIndex];
            *(int*)&track->m_note = *(int*)&savedTrackData->m_note[trackIndex];
            trackCount -= 1;
            trackIndex += 1;
            track += 1;
        } while (trackCount != 0);
        activeTrackCount = _MusicMidiNoteSkipExecute(control, p_SkipKeyOn, 1);
    }
    m_MusicSkipComplete = REDSOUND_MUSIC_SKIP_COMPLETE;
}


/*
 * --INFO--
 * PAL Address: 0x801c6ab4
 * PAL Size: 1416b
 * EN Address: 0x802089d8
 * EN Size: 1416b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeTrackDataExecute(RedTrackDATA* track, int frames)
{
	RedVoiceDATA* voice;
	int volumeStep;
	int expressionStep;
	int panStep;
	int reverbStep;
	int mixStep;
	int pitchStep;
	int sweepStep;
	int vibrateRateStep;
	int vibrateDepthStep;
	int tremoloRateStep;
	int tremoloDepthStep;
	int shakeRateStep;
	int shakeDepthStep;
	int pitchModDelayStep;
	int volumeModDelayStep;

	if ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_STREAM) != 0) {
		return;
	}

	voice = p_VoiceData + track->m_trackNo;
	if (0 < frames) {
		track->m_playTime += frames;
	}

	if (track->m_volumeDelta != 0) {
		if (track->m_volumeDelta > frames) {
			volumeStep = frames;
		} else {
			volumeStep = track->m_volumeDelta;
		}
		track->m_volumeDelta -= volumeStep;
		track->m_volume += track->m_volumeAdd * volumeStep;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_expressionDelta != 0) {
		if (track->m_expressionDelta > frames) {
			expressionStep = frames;
		} else {
			expressionStep = track->m_expressionDelta;
		}
		track->m_expressionDelta -= expressionStep;
		track->m_expression += track->m_expressionAdd * expressionStep;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_panDelta != 0) {
		if (track->m_panDelta > frames) {
			panStep = frames;
		} else {
			panStep = track->m_panDelta;
		}
		track->m_panDelta -= panStep;
		track->m_pan += track->m_panAdd * panStep;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_reverbDepthDelta != 0) {
		if (track->m_reverbDepthDelta > frames) {
			reverbStep = frames;
		} else {
			reverbStep = track->m_reverbDepthDelta;
		}
		track->m_reverbDepthDelta -= reverbStep;
		track->m_reverbDepth += track->m_reverbDepthAdd * reverbStep;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_mixVolumeDelta != 0) {
		if (track->m_mixVolumeDelta > frames) {
			mixStep = frames;
		} else {
			mixStep = track->m_mixVolumeDelta;
		}
		track->m_mixVolumeDelta -= mixStep;
		if ((track->m_mixVolumeDelta == 0) && (track->m_mixVolumeMode == REDSOUND_SE_VOLUME_MODE_FADE_OUT)) {
			track->m_command = (u8*)m_TerminateNote;
			track->m_deltaTime = 1;
		}
		track->m_mixVolume += track->m_mixVolumeAdd * mixStep;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_VOLUME;
	}

	if (track->m_pitchDelta != 0) {
		if (track->m_pitchDelta > frames) {
			pitchStep = frames;
		} else {
			pitchStep = track->m_pitchDelta;
		}
		track->m_pitchDelta -= pitchStep;
		track->m_pitch += track->m_pitchAdd * pitchStep;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
	}

	if (track->m_sweepDelta != 0) {
		if (track->m_sweepDelta > frames) {
			sweepStep = frames;
		} else {
			sweepStep = track->m_sweepDelta;
		}
		track->m_sweepDelta -= sweepStep;
		track->m_portamentPitch += sweepStep * track->m_sweepAdd;
		voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
		voice->m_basePitch += sweepStep * track->m_sweepAdd;
	}

	if (((voice->m_updateFlags & REDSOUND_VOICE_UPDATE_PITCH) != 0) && (voice->m_waveData != 0)) {
		voice->m_pitch =
			PitchCompute(voice->m_basePitch + track->m_pitch,
			             (int)(s16)track->m_keyTranspose + (int)(s16)track->m_pitchBend,
			             voice->m_waveData->m_pitch, track->m_fineTune);
	}

	if (track->m_vibrateFunc != 0) {
		if (track->m_vibrateRateDelta != 0) {
			if (track->m_vibrateRateDelta > frames) {
				vibrateRateStep = frames;
			} else {
				vibrateRateStep = track->m_vibrateRateDelta;
			}
			track->m_vibrateRateDelta = track->m_vibrateRateDelta - (short)vibrateRateStep;
			track->m_vibrateRate += track->m_vibrateRateAdd * vibrateRateStep;
		}
		if (track->m_vibrateDepthDelta != 0) {
			if (track->m_vibrateDepthDelta > frames) {
				vibrateDepthStep = frames;
			} else {
				vibrateDepthStep = track->m_vibrateDepthDelta;
			}
			track->m_vibrateDepthDelta = track->m_vibrateDepthDelta - (short)vibrateDepthStep;
			track->m_vibrateDepth += track->m_vibrateDepthAdd * vibrateDepthStep;
		}
	}

	if (track->m_tremoloFunc != 0) {
		if (track->m_tremoloRateDelta != 0) {
			if (track->m_tremoloRateDelta > frames) {
				tremoloRateStep = frames;
			} else {
				tremoloRateStep = track->m_tremoloRateDelta;
			}
			track->m_tremoloRateDelta = track->m_tremoloRateDelta - (short)tremoloRateStep;
			track->m_tremoloRate += track->m_tremoloRateAdd * tremoloRateStep;
		}
		if (track->m_tremoloDepthDelta != 0) {
			if (track->m_tremoloDepthDelta > frames) {
				tremoloDepthStep = frames;
			} else {
				tremoloDepthStep = track->m_tremoloDepthDelta;
			}
			track->m_tremoloDepthDelta = track->m_tremoloDepthDelta - (short)tremoloDepthStep;
			track->m_tremoloDepth += track->m_tremoloDepthAdd * tremoloDepthStep;
		}
	}

	if (track->m_shakeFunc != 0) {
		if (track->m_shakeRateDelta != 0) {
			if (track->m_shakeRateDelta > frames) {
				shakeRateStep = frames;
			} else {
				shakeRateStep = track->m_shakeRateDelta;
			}
			track->m_shakeRateDelta = track->m_shakeRateDelta - (short)shakeRateStep;
			track->m_shakeRate += track->m_shakeRateAdd * shakeRateStep;
		}
		if (track->m_shakeDepthDelta != 0) {
			if (track->m_shakeDepthDelta > frames) {
				shakeDepthStep = frames;
			} else {
				shakeDepthStep = track->m_shakeDepthDelta;
			}
			track->m_shakeDepthDelta = track->m_shakeDepthDelta - (short)shakeDepthStep;
			track->m_shakeDepth += track->m_shakeDepthAdd * shakeDepthStep;
		}
	}

	if (voice->m_pitchModDelay != 0) {
		if (voice->m_pitchModDelay > frames) {
			pitchModDelayStep = frames;
		} else {
			pitchModDelayStep = voice->m_pitchModDelay;
		}
		voice->m_pitchModDelay = voice->m_pitchModDelay - (short)pitchModDelayStep;
	}

	if (voice->m_volumeModDelay != 0) {
		if (voice->m_volumeModDelay > frames) {
			volumeModDelayStep = frames;
		} else {
			volumeModDelayStep = voice->m_volumeModDelay;
		}
		voice->m_volumeModDelay = voice->m_volumeModDelay - (short)volumeModDelayStep;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c703c
 * PAL Size: 572b
 * EN Address: 0x80208f60
 * EN Size: 572b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _SeMidiNoteExecute(
    RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track, int frames, int tickStep)
{
    do {
        if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && ((track->m_voiceSwitch & REDSOUND_VOICE_SWITCH_PAUSE) == 0)) {
            track->m_seTickCounter -= tickStep * REDSOUND_SE_TICK_STEP;
            while (track->m_seTickCounter < 1) {
                int step;
                track->m_seTickCounter += REDSOUND_CONTROL_TICK_PERIOD;
                if (track->m_deltaTime < frames) {
                    step = track->m_deltaTime;
                } else {
                    step = frames;
                }
                int execStep = step;
                track->m_deltaTime -= frames;
                _SeTrackDataExecute(track, execStep);
                if (((track->m_flags & REDSOUND_TRACK_FLAG_TENUTO) == 0) && (track->m_deltaTime == 1)) {
                    KeyOffSet(control, keyOnData, track);
                }

                m_ChangeStatus = 0;
                while ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_deltaTime < 1)) {
                    int delta;
                    unsigned char* cmd;
                    track->m_loopStepCurrent += 1;
                    cmd = track->m_command;
                    track->m_command = cmd + 1;
                    RedMidiControlFunc func = p_MidiControl_Function[*cmd];
                    func(control, keyOnData, track);
                    if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
                        delta = DeltaTimeSumup((unsigned char**)&track->m_command);
                        if (delta != 0) {
                            delta += track->m_step;
                            if (delta < 1) {
                                delta = 1;
                            } else if ((track->m_voiceSwitch & REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME) != 0) {
                                int fuzzyDelta = delta * track->m_fuzzyDeltaTimeDepth >> 8;
                                s8 random = (s8)GetRandomData();
                                delta += fuzzyDelta * random >> 7;
                                if (delta < 1) {
                                    delta = 1;
                                }
                            }
                        }

                        if (track->m_deltaTime < -1) {
                            int clampedStep;
                            if (track->m_deltaTime + delta > 0) {
                                clampedStep = -track->m_deltaTime;
                            } else {
                                clampedStep = delta;
                            }
                            int execStep = clampedStep;
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
    control->m_skipFrames = 1;
    return control->m_activeTrackCount;
}

/*
 * --INFO--
 * PAL Address: 0x801c7278
 * PAL Size: 512b
 * EN Address: 0x8020919c
 * EN Size: 512b
 * JP Address: TODO
 * JP Size: TODO
 */
void MainControl(int frames)
{
    u32 mul;
    int step;

    _KeyOnControl();
    m_KeyOnEntry = 0;
    memset(p_KeyOnData, 0, sizeof(*p_KeyOnData));

    p_SoundControl = p_SoundControlBuffer + REDSOUND_CONTROL_SE;
    _SeMidiNoteExecute(p_SoundControl, p_KeyOnData,
                       p_SoundControl->m_tracks, p_SoundControl->m_skipFrames, frames);
    p_SoundControl = p_SoundControlBuffer;

    if (p_SoundControl->m_activeTrackCount != 0) {
        if ((p_SoundControl->m_flags & REDSOUND_CONTROL_FLAG_PAUSE) == 0) {
            mul = ((u32)p_MusicTempoControl->m_value >> REDSOUND_FIXED_SHIFT) & REDSOUND_TEMPO_SCALE_MASK;
            step = p_SoundControl->m_tempo >> REDSOUND_FIXED_SHIFT;
            if (mul != 0) {
                if (p_MusicTempoControl->m_value < 0) {
                    step *= (int)mul;
                    step >>= REDSOUND_TEMPO_SCALE_SHIFT;
                } else {
                    step *= (int)mul + 1;
                    step >>= REDSOUND_TEMPO_SCALE_POSITIVE_SHIFT;
                    step += p_SoundControl->m_tempo >> REDSOUND_FIXED_SHIFT;
                }
            }
            p_SoundControl->m_tickCounter -= step * frames;
            while (p_SoundControl->m_tickCounter < 1) {
                p_SoundControl->m_tickCounter += REDSOUND_CONTROL_TICK_PERIOD;
                _MusicNoteExecute();
            }
        }
    }

    if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount != 0) {
        p_SoundControl = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY;
        step = p_SoundControl->m_tempo >> REDSOUND_FIXED_SHIFT;
        p_SoundControl->m_tickCounter -= step * frames;
        while (p_SoundControl->m_tickCounter < 1) {
            p_SoundControl->m_tickCounter += REDSOUND_CONTROL_TICK_PERIOD;
            _MusicNoteExecute();
        }
        if (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_activeTrackCount == 0) {
            memcpy(p_SoundControlBuffer, p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY,
                   sizeof(*p_SoundControlBuffer));
            p_SoundControl->m_activeTrackCount = 0;
            p_SoundControl->m_trackCount = 0;
            p_SoundControl->m_musicId = REDSOUND_MUSIC_ID_NONE;
        }
        p_SoundControl = p_SoundControlBuffer;
    }

    _ExecuteExtraData();
    if (m_MusicSkipComplete != 0) {
        _SkipMusicEntry();
    }
}
