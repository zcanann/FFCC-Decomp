#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"

enum RedMidiSignTableSize {
    REDSOUND_SIGN_DATA_TABLE_COUNT = 0x200,
};

static int m_SignDataTable[REDSOUND_SIGN_DATA_TABLE_COUNT] = {
    0, 402, 804, 1206, 1608, 2010, 2412, 2814,
    3216, 3617, 4019, 4420, 4821, 5222, 5623, 6023,
    6424, 6824, 7224, 7623, 8022, 8421, 8820, 9218,
    9616, 10014, 10411, 10808, 11204, 11600, 11996, 12391,
    12785, 13180, 13573, 13966, 14359, 14751, 15143, 15534,
    15924, 16314, 16703, 17091, 17479, 17867, 18253, 18639,
    19024, 19409, 19792, 20175, 20557, 20939, 21320, 21699,
    22078, 22457, 22834, 23210, 23586, 23961, 24335, 24708,
    25080, 25451, 25821, 26190, 26558, 26925, 27291, 27656,
    28020, 28383, 28745, 29106, 29466, 29824, 30182, 30538,
    30893, 31248, 31600, 31952, 32303, 32652, 33000, 33347,
    33692, 34037, 34380, 34721, 35062, 35401, 35738, 36075,
    36410, 36744, 37076, 37407, 37736, 38064, 38391, 38716,
    39040, 39362, 39683, 40002, 40320, 40636, 40951, 41264,
    41576, 41886, 42194, 42501, 42806, 43110, 43412, 43713,
    44011, 44308, 44604, 44898, 45190, 45480, 45769, 46056,
    46341, 46624, 46906, 47186, 47464, 47741, 48015, 48288,
    48559, 48828, 49095, 49361, 49624, 49886, 50146, 50404,
    50660, 50914, 51166, 51417, 51665, 51911, 52156, 52398,
    52639, 52878, 53114, 53349, 53581, 53812, 54040, 54267,
    54491, 54714, 54934, 55152, 55368, 55582, 55794, 56004,
    56212, 56418, 56621, 56823, 57022, 57219, 57414, 57607,
    57798, 57986, 58172, 58356, 58538, 58718, 58896, 59071,
    59244, 59415, 59583, 59750, 59914, 60075, 60235, 60392,
    60547, 60700, 60851, 60999, 61145, 61288, 61429, 61568,
    61705, 61839, 61971, 62101, 62228, 62353, 62476, 62596,
    62714, 62830, 62943, 63054, 63162, 63268, 63372, 63473,
    63572, 63668, 63763, 63854, 63944, 64031, 64115, 64197,
    64277, 64354, 64429, 64501, 64571, 64639, 64704, 64766,
    64827, 64884, 64940, 64993, 65043, 65091, 65137, 65180,
    65220, 65259, 65294, 65328, 65358, 65387, 65413, 65436,
    65457, 65476, 65492, 65505, 65516, 65525, 65531, 65535,
    65536, 65535, 65531, 65525, 65516, 65505, 65492, 65476,
    65457, 65436, 65413, 65387, 65358, 65328, 65294, 65259,
    65220, 65180, 65137, 65091, 65043, 64993, 64940, 64884,
    64827, 64766, 64704, 64639, 64571, 64501, 64429, 64354,
    64277, 64197, 64115, 64031, 63944, 63854, 63763, 63668,
    63572, 63473, 63372, 63268, 63162, 63054, 62943, 62830,
    62714, 62596, 62476, 62353, 62228, 62101, 61971, 61839,
    61705, 61568, 61429, 61288, 61145, 60999, 60851, 60700,
    60547, 60392, 60235, 60075, 59914, 59750, 59583, 59415,
    59244, 59071, 58896, 58718, 58538, 58356, 58172, 57986,
    57798, 57607, 57414, 57219, 57022, 56823, 56621, 56418,
    56212, 56004, 55794, 55582, 55368, 55152, 54934, 54714,
    54491, 54267, 54040, 53812, 53581, 53349, 53114, 52878,
    52639, 52398, 52156, 51911, 51665, 51417, 51166, 50914,
    50660, 50404, 50146, 49886, 49624, 49361, 49095, 48828,
    48559, 48288, 48015, 47741, 47464, 47186, 46906, 46624,
    46341, 46056, 45769, 45480, 45190, 44898, 44604, 44308,
    44011, 43713, 43412, 43110, 42806, 42501, 42194, 41886,
    41576, 41264, 40951, 40636, 40320, 40002, 39683, 39362,
    39040, 38716, 38391, 38064, 37736, 37407, 37076, 36744,
    36410, 36075, 35738, 35401, 35062, 34721, 34380, 34037,
    33692, 33347, 33000, 32652, 32303, 31952, 31600, 31248,
    30893, 30538, 30182, 29824, 29466, 29106, 28745, 28383,
    28020, 27656, 27291, 26925, 26558, 26190, 25821, 25451,
    25080, 24708, 24335, 23961, 23586, 23210, 22834, 22457,
    22078, 21699, 21320, 20939, 20557, 20175, 19792, 19409,
    19024, 18639, 18253, 17867, 17479, 17091, 16703, 16314,
    15924, 15534, 15143, 14751, 14359, 13966, 13573, 13180,
    12785, 12391, 11996, 11600, 11204, 10808, 10411, 10014,
    9616, 9218, 8820, 8421, 8022, 7623, 7224, 6824,
    6424, 6023, 5623, 5222, 4821, 4420, 4019, 3617,
    3216, 2814, 2412, 2010, 1608, 1206, 804, 402,
};

static int SineSwing(int phase);
static int TriangleSwing(int phase);
static int SawSwing(int phase);
static int DutySwing(int phase);
static int RandomSwing(int phase);
static int SineSwingR(int phase);
static int TriangleSwingR(int phase);
static int DutySwingR(int phase);
static int SawSwingR(int phase);
static int RandomSwingR(int phase);

RedSwingFunc SwingEntryFunction[REDSOUND_SWING_FUNCTION_COUNT] = {
    SineSwing, TriangleSwing, SawSwing, DutySwing,
    RandomSwing, DutySwing,   DutySwing, DutySwing,
    SineSwingR, TriangleSwingR, SawSwingR, DutySwingR,
    RandomSwingR, DutySwingR, DutySwingR, DutySwingR,
};

enum RedMidiSwingConst {
    REDSOUND_SWING_SINE_MASK = REDSOUND_SIGN_DATA_TABLE_COUNT - 1,
    REDSOUND_SWING_PHASE_SIGN = 0x200,
    REDSOUND_SWING_PHASE_SHIFT = 8,
    REDSOUND_SWING_PHASE_MASK = 0xFF,
    REDSOUND_SWING_QUADRANT_MASK = 3,
    REDSOUND_SWING_LEVEL_FULL = 0x10000,
    REDSOUND_SWING_RANDOM_REVERSE_PHASE = 0x40,
};

enum RedMidiCommandConst {
    REDSOUND_MIDI_DEFAULT_STEP_COUNT = 0x100,
    REDSOUND_MIDI_DEFAULT_RATE_DIVISOR = 0x100,
    REDSOUND_MIDI_RATE_FIXED_NUMERATOR = 0x100000,
    REDSOUND_MIDI_TICKS_PER_WHOLE_NOTE = 0xC0,
    REDSOUND_MIDI_MOD_DELAY_SCALE = 4,
    REDSOUND_MIDI_SWING_FUNC_MASK = 0xF,
    REDSOUND_MIDI_FUZZY_DEFAULT_DEPTH = 0x100,
    REDSOUND_MIDI_PITCH_BEND_HIGH_SCALE = 0x80,
    REDSOUND_MIDI_PITCH_BEND_CENTER = 0x2000,
    REDSOUND_MIDI_DELTA_BUFFER_WORD_COUNT = 4,
    REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT = 1,
    REDSOUND_MIDI_WAVE_BANK_DIRECT = 0x10,
};

enum RedMidiModCommandByte {
    REDSOUND_MIDI_MOD_DEPTH = 0,
    REDSOUND_MIDI_MOD_RATE = 1,
    REDSOUND_MIDI_MOD_FUNCTION = 2,
    REDSOUND_MIDI_MOD_DELAY_FRAMES = 0,
    REDSOUND_MIDI_MOD_DELAY_DEPTH = 1,
};

enum RedMidiPitchBendCommandByte {
    REDSOUND_MIDI_PITCH_BEND_LOW = 0,
    REDSOUND_MIDI_PITCH_BEND_HIGH = 1,
};

enum RedMidiReverbMixCommandByte {
    REDSOUND_MIDI_REVERB_MIX_LEFT = 0,
    REDSOUND_MIDI_REVERB_MIX_RIGHT = 1,
};

enum RedMidiTempoChangeCommandByte {
    REDSOUND_MIDI_TEMPO_CHANGE_STEP = 0,
    REDSOUND_MIDI_TEMPO_CHANGE_TARGET = 1,
};

enum RedMidiTimeSignatureCommandByte {
    REDSOUND_MIDI_TIME_SIGNATURE_NUMERATOR = 0,
    REDSOUND_MIDI_TIME_SIGNATURE_DENOMINATOR = 1,
};

static void __MidiCtrl_NoSupport(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_Pass(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_Stop(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_Sleep(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_WholeLoopStart(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_WholeLoopEnd(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_LoopStart(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_LoopEnd(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_LoopRepeat(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TempoDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TempoChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ReverbDepthDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ReverbDepthChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TimeSignature(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeySignature(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_PhraseSignature(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOnSame(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOnNoteVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOnNote(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOnVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOffSame(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOffNoteVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOffNote(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyOffVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_Wave(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_WaveWithBank(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VolumeDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VolumeChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ExpressionDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ExpressionChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_PanDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_PanChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_PortamentOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_PortamentOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_SlurOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_SlurOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_Sweep(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TenutoOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TenutoOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_Default(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_AL(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_AR(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_DL(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_DR(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_SL(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_SR(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_RL(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ADSR_RR(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_SustainPedal(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ChannelAlloc(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ChannelPriority(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ChannelFix(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateDepthDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateDepthChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateRateDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateRateChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateType(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_VibrateDelay(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloDepthDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloDepthChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloRateDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloRateChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloType(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_TremoloDelay(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeDepthDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeDepthChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeRateDirect(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeRateChange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ShakeType(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_FineTuneAbsolute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_FineTuneRelative(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyTransposeAbsolute(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_KeyTransposeRelative(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void _PitchBendCompute(RedTrackDATA* track, int pitchBend);
static void __MidiCtrl_PitchBend(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_PitchBendRange(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ReverbOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ReverbOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_ReverbMix(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_StepRelative(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_StepRelative2(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_FuzzyOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);
static void __MidiCtrl_FuzzyOff(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);

RedMidiControlFunc p_MidiControl_Function[REDSOUND_MIDI_CONTROL_FUNCTION_COUNT] = {
    __MidiCtrl_Stop,             __MidiCtrl_Sleep,           __MidiCtrl_WholeLoopStart,
    __MidiCtrl_WholeLoopEnd,     __MidiCtrl_LoopStart,       __MidiCtrl_LoopEnd,
    __MidiCtrl_LoopRepeat,       __MidiCtrl_NoSupport,       __MidiCtrl_TempoDirect,
    __MidiCtrl_TempoChange,      __MidiCtrl_ReverbDepthDirect, __MidiCtrl_ReverbDepthChange,
    __MidiCtrl_TimeSignature,    __MidiCtrl_KeySignature,    __MidiCtrl_PhraseSignature,
    __MidiCtrl_NoSupport,        __MidiCtrl_KeyOnSame,       __MidiCtrl_KeyOnNoteVelocity,
    __MidiCtrl_KeyOnNote,        __MidiCtrl_KeyOnVelocity,   __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_KeyOffSame,       __MidiCtrl_KeyOffNoteVelocity, __MidiCtrl_KeyOffNote,
    __MidiCtrl_KeyOffVelocity,   __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_Wave,
    __MidiCtrl_WaveWithBank,     __MidiCtrl_VolumeDirect,    __MidiCtrl_VolumeChange,
    __MidiCtrl_ExpressionDirect, __MidiCtrl_ExpressionChange, __MidiCtrl_PanDirect,
    __MidiCtrl_PanChange,        __MidiCtrl_PortamentOn,     __MidiCtrl_PortamentOff,
    __MidiCtrl_SlurOn,           __MidiCtrl_SlurOff,         __MidiCtrl_Sweep,
    __MidiCtrl_NoSupport,        __MidiCtrl_TenutoOn,        __MidiCtrl_TenutoOff,
    __MidiCtrl_ADSR_AL,          __MidiCtrl_ADSR_AR,         __MidiCtrl_ADSR_DL,
    __MidiCtrl_ADSR_DR,          __MidiCtrl_ADSR_SL,         __MidiCtrl_ADSR_SR,
    __MidiCtrl_ADSR_RL,          __MidiCtrl_ADSR_RR,         __MidiCtrl_ADSR_Default,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_SustainPedal,     __MidiCtrl_ChannelAlloc,    __MidiCtrl_ChannelPriority,
    __MidiCtrl_ChannelFix,       __MidiCtrl_VibrateOn,       __MidiCtrl_VibrateOff,
    __MidiCtrl_VibrateDepthDirect, __MidiCtrl_VibrateDepthChange, __MidiCtrl_VibrateRateDirect,
    __MidiCtrl_VibrateRateChange, __MidiCtrl_VibrateType,    __MidiCtrl_VibrateDelay,
    __MidiCtrl_TremoloOn,        __MidiCtrl_TremoloOff,      __MidiCtrl_TremoloDepthDirect,
    __MidiCtrl_TremoloDepthChange, __MidiCtrl_TremoloRateDirect, __MidiCtrl_TremoloRateChange,
    __MidiCtrl_TremoloType,      __MidiCtrl_TremoloDelay,    __MidiCtrl_ShakeOn,
    __MidiCtrl_ShakeOff,         __MidiCtrl_ShakeDepthDirect, __MidiCtrl_ShakeDepthChange,
    __MidiCtrl_ShakeRateDirect,  __MidiCtrl_ShakeRateChange, __MidiCtrl_ShakeType,
    __MidiCtrl_NoSupport,        __MidiCtrl_FineTuneAbsolute, __MidiCtrl_FineTuneRelative,
    __MidiCtrl_KeyTransposeAbsolute, __MidiCtrl_KeyTransposeRelative, __MidiCtrl_PitchBend,
    __MidiCtrl_PitchBendRange,   __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_ReverbOn,         __MidiCtrl_ReverbOff,       __MidiCtrl_ReverbMix,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_StepRelative,    __MidiCtrl_StepRelative2,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_FuzzyOn,          __MidiCtrl_FuzzyOff,        __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_NoSupport,       __MidiCtrl_NoSupport,
    __MidiCtrl_NoSupport,        __MidiCtrl_Pass,
};

/*
 * --INFO--
 * PAL Address: 0x801C7478
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int DataAddCompute(int* current, int target, int* delta)
{
    int result = 0;

    if (target - (*current >> REDSOUND_FIXED_SHIFT) != 0) {
        result = ((target << REDSOUND_FIXED_SHIFT) | REDSOUND_FIXED_HALF) - *current;
        result /= *delta;
    } else {
        *delta = 0;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C74C8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void KeyOnReserveClear(RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    RedKeyOnSlot* slot = keyOnData->m_fixed;
    do {
        if (slot->m_track == track) {
            slot->m_track = 0;
        }
        slot++;
    } while (slot < keyOnData->m_normal + REDSOUND_KEY_ON_SLOT_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C7504
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void KeyOnReserve(RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    RedKeyOnSlot* slot;

    if (((signed char)track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_DIRECT_MASK) != 0) {
        slot = &keyOnData->m_fixed[track->m_trackNo];
        if ((slot->m_track == 0) || (slot->m_track == track)) {
            slot->m_track = track;
            *(unsigned int*)&slot->m_note = *(unsigned int*)&track->m_note;
            m_KeyOnEntry++;
        }
        return;
    }

    if ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_PRIORITY) != 0) {
        slot = keyOnData->m_priority;
        do {
            if (slot->m_track == 0) {
                slot->m_track = track;
                *(unsigned int*)&slot->m_note = *(unsigned int*)&track->m_note;
                m_KeyOnEntry++;
                break;
            }
            slot++;
        } while (slot < keyOnData->m_normal);
    } else {
        slot = keyOnData->m_normal;
        do {
            if (slot->m_track == 0) {
                slot->m_track = track;
                *(unsigned int*)&slot->m_note = *(unsigned int*)&track->m_note;
                m_KeyOnEntry++;
                break;
            }
            slot++;
        } while (slot < keyOnData->m_normal + REDSOUND_KEY_ON_SLOT_COUNT);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C75F4
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void KeyOffSet(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    char key;
    RedKeyOnSlot* slot;
    RedVoiceDATA* voice;

    if ((control == p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SKIP) || ((track->m_flags & REDSOUND_TRACK_FLAG_SLUR) == 0)) {
        track->m_sweepDelta = 0;
        key = ((char*)track)[REDSOUND_TRACK_NOTE_KEY_OFFSET];
        slot = keyOnData->m_fixed;
        do {
            if ((slot->m_track == track) && (slot->m_note.m_key == key)) {
                slot->m_track = 0;
            }
            slot++;
        } while (slot < keyOnData->m_normal + REDSOUND_KEY_ON_SLOT_COUNT);

        key = ((char*)track)[REDSOUND_TRACK_NOTE_KEY_OFFSET];
        voice = p_VoiceData;
        do {
            if ((voice->m_track == track) && (voice->m_key == key)) {
                voice->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
                voice->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
            }
            voice++;
        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C76D0
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int SineSwing(int phase)
{
    int value = phase & REDSOUND_SWING_SINE_MASK;
    value = m_SignDataTable[value];

    if (((u32)phase & REDSOUND_SWING_PHASE_SIGN) != 0) {
        value = -value;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x801C770C
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int TriangleSwing(int phase)
{
    int result = (phase & REDSOUND_SWING_PHASE_MASK) << REDSOUND_SWING_PHASE_SHIFT;

    switch (((u32)phase >> REDSOUND_SWING_PHASE_SHIFT) & REDSOUND_SWING_QUADRANT_MASK) {
    case 3:
        result -= REDSOUND_SWING_LEVEL_FULL;
        break;
    case 2:
        result = -result;
        break;
    case 1:
        result = REDSOUND_SWING_LEVEL_FULL - result;
        break;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C7768
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int SawSwing(int phase)
{
    int result = (int)(char)(phase >> 2) << REDSOUND_SWING_PHASE_SHIFT;

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C778C
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int DutySwing(int phase)
{
    int value;
    int result;

    if ((phase & REDSOUND_SWING_PHASE_SIGN) != 0) {
        value = -REDSOUND_SWING_LEVEL_FULL;
    } else {
        value = REDSOUND_SWING_LEVEL_FULL;
    }
    result = value;
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C77C4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int RandomSwing(int phase)
{
    phase >>= REDSOUND_SWING_PHASE_SHIFT;
    phase &= REDSOUND_SWING_PHASE_MASK;
    int result = (int)t_RandomData[phase] << REDSOUND_SWING_PHASE_SHIFT;

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C77FC
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int SineSwingR(int phase)
{
    phase ^= REDSOUND_SWING_PHASE_SIGN;
    int value = phase & REDSOUND_SWING_SINE_MASK;
    value = m_SignDataTable[value];
    if ((phase & REDSOUND_SWING_PHASE_SIGN) != 0) {
        value = -value;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x801C783C
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int TriangleSwingR(int phase)
{
    int result;

    phase ^= REDSOUND_SWING_PHASE_SIGN;
    result = (phase & REDSOUND_SWING_PHASE_MASK) << REDSOUND_SWING_PHASE_SHIFT;

    switch (((u32)phase >> REDSOUND_SWING_PHASE_SHIFT) & REDSOUND_SWING_QUADRANT_MASK) {
    case 3:
        result -= REDSOUND_SWING_LEVEL_FULL;
        break;
    case 2:
        result = -result;
        break;
    case 1:
        result = REDSOUND_SWING_LEVEL_FULL - result;
        break;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C789C
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int DutySwingR(int phase)
{
    int value;
    int result;

    phase ^= REDSOUND_SWING_PHASE_SIGN;
    if ((phase & REDSOUND_SWING_PHASE_SIGN) != 0) {
        value = -REDSOUND_SWING_LEVEL_FULL;
    } else {
        value = REDSOUND_SWING_LEVEL_FULL;
    }

    result = value;
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C78D8
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int SawSwingR(int phase)
{
    int result = (int)(char)((int)((u32)phase ^ 0xffffffff) >> 2) << REDSOUND_SWING_PHASE_SHIFT;

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C7904
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int RandomSwingR(int phase)
{
    phase >>= REDSOUND_SWING_PHASE_SHIFT;
    phase &= REDSOUND_SWING_PHASE_MASK;
    phase ^= REDSOUND_SWING_RANDOM_REVERSE_PHASE;
    int result = (int)t_RandomData[phase] << REDSOUND_SWING_PHASE_SHIFT;

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801C7940
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_NoSupport(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
	__MidiCtrl_Stop(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801c7978
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_Pass(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801C797C
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_Stop(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    RedVoiceDATA* voice;

    track->m_flags = 0;
    KeyOffSet(control, keyOnData, track);

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);

    track->m_command = 0;
    if (control < p_SoundControlBuffer + REDSOUND_CONTROL_SE) {
        control->m_activeTrackCount--;
        if ((control->m_activeTrackCount == 0) &&
            ((m_MusicPhraseStop == 1) || ((control->m_flags & REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE) == 0))) {
            voice = p_VoiceData;
            do {
                if ((voice->m_track >= control->m_tracks) &&
                    (voice->m_track < control->m_tracks + control->m_trackCount)) {
                    voice->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SUSTAIN_PAUSE_MASK;
                    voice->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
                    voice->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
                    voice->m_track = 0;
                }
                voice++;
            } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);

            c_RedEntry.MusicHistoryManager(0, control->m_musicId);
            c_RedEntry.WaveHistoryManager(0, control->m_waveNo);
            control->m_musicId = -1;
            control->m_updateFlags = 0;
            RedDelete((int)control->m_tracks);
            control->m_tracks = 0;
        }
    } else {
        if (track->m_waveBankData != 0) {
            c_RedEntry.WaveHistoryManager(0, track->m_waveBankData->m_waveNo);
        }
        c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
        track->m_seId = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7B44
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_Sleep(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA*)
{
    if ((m_MusicPhraseStop == 1) && (control == p_SoundControlBuffer)) {
        RedTrackDATA* track = control->m_tracks;
        do {
            if (track->m_command != 0) {
                __MidiCtrl_Stop(control, keyOnData, track);
            }
            track++;
        } while (track < control->m_tracks + control->m_trackCount);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7BCC
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_WholeLoopStart(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    int* saveWords = (int*)control->m_savedCommand;
    int loopBase = control->m_loopBase;

    control->m_flags |= REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE;

    int deltaAdjust = -track->m_deltaTime + 1;
    int slot = 0;
    RedTrackDATA* scan;

    for (scan = control->m_tracks; scan < track; scan++) {
        saveWords[slot] = (int)scan->m_command;
        saveWords[slot + REDSOUND_MUSIC_TRACK_SAVE_COUNT] = scan->m_deltaTime + deltaAdjust;
        saveWords[slot + REDSOUND_MUSIC_TRACK_SAVE_COUNT * 2] = scan->m_flags;
        saveWords[slot + REDSOUND_MUSIC_TRACK_SAVE_COUNT * 3] = *(int*)&scan->m_note;
        slot++;
    }

    {
        unsigned char* command;
        RedTrackDATA* nextTrack = scan + 1;
        command = scan->m_command;
        int delta = DeltaTimeSumup(&command);

        saveWords[slot] = (int)command;
        saveWords[slot + REDSOUND_MUSIC_TRACK_SAVE_COUNT] = scan->m_deltaTime + delta + deltaAdjust;
        saveWords[slot + REDSOUND_MUSIC_TRACK_SAVE_COUNT * 2] = scan->m_flags;
        saveWords[slot + REDSOUND_MUSIC_TRACK_SAVE_COUNT * 3] = *(int*)&scan->m_note;

        if ((nextTrack - control->m_tracks) < control->m_trackCount) {
            for (; nextTrack < control->m_tracks + control->m_trackCount; nextTrack++) {
                int currentDelta = deltaAdjust + (nextTrack->m_deltaTime - loopBase);

                while ((currentDelta < 1) && (nextTrack->m_command != 0)) {
                    unsigned char* cmd = nextTrack->m_command;
                    nextTrack->m_command = cmd + 1;
                    p_MidiControl_Function[*cmd](control, keyOnData, nextTrack);

                    if (nextTrack->m_command != 0) {
                        int step = DeltaTimeSumup((unsigned char**)&nextTrack->m_command);
                        currentDelta += step;
                        nextTrack->m_deltaTime += step;
                    }
                }

                saveWords[slot + 1] = (int)nextTrack->m_command;
                saveWords[slot + 1 + REDSOUND_MUSIC_TRACK_SAVE_COUNT] = currentDelta;
                saveWords[slot + 1 + REDSOUND_MUSIC_TRACK_SAVE_COUNT * 2] = nextTrack->m_flags;
                saveWords[slot + 1 + REDSOUND_MUSIC_TRACK_SAVE_COUNT * 3] = *(int*)&nextTrack->m_note;
                slot++;
            }
        }
    }

    control->m_savedActiveTrackCount = control->m_activeTrackCount;
    memmove(&control->m_savedMeasure,
            &control->m_measure,
            REDSOUND_CONTROL_SAVED_POSITION_SIZE);
    control->m_savedTick -= deltaAdjust;
    if (control->m_savedTick < 0) {
        control->m_savedTick += control->m_savedTicksPerMeasure;
        control->m_savedMeasure--;
    }
    memmove(&control->m_savedTempo,
            &control->m_tempo,
            REDSOUND_CONTROL_SAVED_TEMPO_SIZE);
}

/*
 * --INFO--
 * PAL Address: 0x801C7E40
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_WholeLoopEnd(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA*)
{
    control->m_flags |= REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END;
    if ((m_MusicPhraseStop == 1) && (control == p_SoundControlBuffer)) {
        RedTrackDATA* track = control->m_tracks;
        do {
            if (track->m_command != 0) {
                __MidiCtrl_Stop(control, keyOnData, track);
            }
            track++;
        } while (track < control->m_tracks + control->m_trackCount);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7ED4
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_LoopStart(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    ++track->m_loopDepth;
    track->m_loopDepth &= REDSOUND_TRACK_LOOP_STACK_COUNT - 1;
    track->m_loopCommand[track->m_loopDepth] = track->m_command;
    track->m_loopStep[track->m_loopDepth] = track->m_loopStepCurrent;
    track->m_loopCount[track->m_loopDepth] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C7F2C
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_LoopEnd(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int loopCount;

    loopCount = *track->m_command++;
    if (loopCount == 0) {
        loopCount = REDSOUND_MIDI_DEFAULT_STEP_COUNT;
    }

    track->m_loopCount[track->m_loopDepth]++;
    if (track->m_loopCount[track->m_loopDepth] != loopCount) {
        track->m_command = track->m_loopCommand[track->m_loopDepth];
        track->m_loopStepCurrent = track->m_loopStep[track->m_loopDepth];
    } else {
        track->m_loopDepth--;
        track->m_loopDepth &= REDSOUND_TRACK_LOOP_STACK_COUNT - 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C7FD0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_LoopRepeat(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_command = track->m_loopCommand[track->m_loopDepth];
    track->m_loopStepCurrent = track->m_loopStep[track->m_loopDepth];
}

/*
 * --INFO--
 * PAL Address: 0x801C7FFC
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TempoDirect(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    control->m_tempo = *track->m_command++ << REDSOUND_FIXED_SHIFT;
    control->m_tempoAdd = 0;
    control->m_tempoDelta = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C8028
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TempoChange(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    unsigned int delta;

    delta = (track->m_command[REDSOUND_MIDI_TEMPO_CHANGE_STEP] != 0)
                ? track->m_command[REDSOUND_MIDI_TEMPO_CHANGE_STEP]
                : REDSOUND_MIDI_DEFAULT_STEP_COUNT;

    control->m_tempoAdd =
        DataAddCompute(&control->m_tempo, track->m_command[REDSOUND_MIDI_TEMPO_CHANGE_TARGET], (int*)&delta);
    control->m_tempoDelta = delta;
    track->m_command += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C80B4
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ReverbDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedControlRamp* reverbDepth = (RedControlRamp*)&track->m_reverbDepth;

    reverbDepth->m_value = *(s8*)track->m_command++;

    if (reverbDepth->m_value != 0) {
        reverbDepth->m_value += 1;
        reverbDepth->m_value <<= 8;
        reverbDepth->m_value -= 1;
        reverbDepth->m_value <<= REDSOUND_FIXED_SHIFT;
    }

    reverbDepth->m_step = 0;
    reverbDepth->m_count = 0;
    SetVoiceAccess(track, 8);
}

/*
 * --INFO--
 * PAL Address: 0x801C8158
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ReverbDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedControlRamp* reverbDepth = (RedControlRamp*)&track->m_reverbDepth;
    int targetDepth;
    unsigned int stepCount;

    stepCount = (*track->m_command != 0) ? *track->m_command : REDSOUND_MIDI_DEFAULT_STEP_COUNT;

    targetDepth = (s8)*track->m_command++;
    if (targetDepth != 0) {
        targetDepth += 1;
        targetDepth <<= 8;
        targetDepth -= 1;
    }

    reverbDepth->m_step = DataAddCompute(&track->m_reverbDepth, (s8)targetDepth, (int*)&stepCount);
    reverbDepth->m_count = stepCount;
    track->m_command += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C820C
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TimeSignature(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    control->m_timeNumerator = track->m_command[REDSOUND_MIDI_TIME_SIGNATURE_NUMERATOR];
    control->m_timeDenominator = track->m_command[REDSOUND_MIDI_TIME_SIGNATURE_DENOMINATOR];
    control->m_ticksPerMeasure =
        (REDSOUND_MIDI_TICKS_PER_WHOLE_NOTE / control->m_timeDenominator) * control->m_timeNumerator;
    track->m_command += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C824C
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeySignature(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedTrackDATA* scan;
    unsigned int value;

    value = *track->m_command++;
    value &= REDSOUND_KEY_SIGNATURE_INDEX_MASK;
    control->m_keySignature = value;
    value = t_KeySignatureIndex[value];
    control->m_keySignatureData = value + t_KeySignatureData;

    if (m_MusicKeySignature != 0) {
        scan = control->m_tracks;
        do {
            scan->m_keySignatureData = control->m_keySignatureData;
            scan++;
        } while (scan < control->m_tracks + control->m_trackCount);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C82D8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PhraseSignature(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int command = *track->m_command++;
}

/*
 * --INFO--
 * PAL Address: 0x801C82F8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOnSame(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8328
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOnNoteVelocity(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    track->m_note.m_key = *track->m_command++;
    track->m_note.m_velocity = *track->m_command++;

    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8390
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOnNote(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    track->m_note.m_key = *track->m_command++;

    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C83E0
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOnVelocity(RedSoundCONTROL*, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    track->m_note.m_velocity = *track->m_command++;

    KeyOnReserve(keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8430
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOffSame(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8468
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOffNoteVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    track->m_note.m_key = *track->m_command++;
    track->m_command++;

    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C84C8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOffNote(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    track->m_note.m_key = *track->m_command++;

    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C851C
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyOffVelocity(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track)
{
    track->m_command++;

    KeyOffSet(control, keyOnData, track);
}

/*
 * --INFO--
 * PAL Address: 0x801C8564
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_Wave(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int waveNo;
    int* waveTable;

    track->m_waveData = 0;
    track->m_waveBase = 0;
    waveNo = *track->m_command++;
    if ((track->m_waveBankData != 0) && (waveNo < track->m_waveBankData->m_tableCount)) {
        waveTable = track->m_waveBankData->m_waveOffsets;
        track->m_waveData = (RedWaveDATA*)((int)track->m_waveBankData + waveTable[waveNo]);
        track->m_waveBase = track->m_waveBankData->m_aramAddress;
        memset(&track->m_adsrAR, REDSOUND_TRACK_ADSR_DEFAULT_WORD, REDSOUND_TRACK_ADSR_SIZE);
    }
    track->m_waveBankNo = REDSOUND_MIDI_WAVE_BANK_DIRECT;
    track->m_waveNo = waveNo;
}

/*
 * --INFO--
 * PAL Address: 0x801C861C
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_WaveWithBank(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	RedHistoryBANK* waveBank;
	int* waveTable;
	int bankNo;
	unsigned int waveNo;
	RedWaveHeadWD* waveBankData;

	bankNo = *track->m_command++;
	waveNo = *track->m_command++;
	track->m_waveData = 0;
	track->m_waveBase = 0;
	waveBank = (RedHistoryBANK*)c_RedEntry.GetWaveBank(bankNo);
	if (waveBank != 0) {
		waveBankData = waveBank->m_waveHead;
		waveTable = waveBankData->m_waveOffsets;
		track->m_waveData = (RedWaveDATA*)((int)waveBankData + waveTable[waveNo]);
		track->m_waveBase = waveBankData->m_aramAddress;
		memset(&track->m_adsrAR, REDSOUND_TRACK_ADSR_DEFAULT_WORD, REDSOUND_TRACK_ADSR_SIZE);
	}
	track->m_waveBankNo = bankNo;
	track->m_waveNo = waveNo;
}

/*
 * --INFO--
 * PAL Address: 0x801C86C4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VolumeDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int volume;

    volume = *track->m_command++;
    if (volume != 0) {
        volume++;
        volume <<= 8;
        volume--;
        volume <<= REDSOUND_FIXED_SHIFT;
    }

    track->m_volume = volume;
    track->m_volumeAdd = 0;
    track->m_volumeDelta = 0;
    m_ChangeStatus |= REDSOUND_VOICE_UPDATE_VOLUME;
}

/*
 * --INFO--
 * PAL Address: 0x801C8720
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VolumeChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int delta[REDSOUND_MIDI_DELTA_BUFFER_WORD_COUNT];
    int volume;

    delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
    if (delta[0] == 0) {
        delta[0]++;
    }

    volume = *track->m_command++;
    if (volume != 0) {
        volume++;
        volume <<= 8;
        volume--;
    }

    track->m_volumeAdd = DataAddCompute(&track->m_volume, volume, delta);
    track->m_volumeDelta = delta[0];
}

/*
 * --INFO--
 * PAL Address: 0x801C87B4
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ExpressionDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value = ((int)(char)*track->m_command++) << REDSOUND_FIXED_SHIFT;

    track->m_expression = value;
    track->m_expressionAdd = 0;
    track->m_expressionDelta = 0;
    m_ChangeStatus |= REDSOUND_VOICE_UPDATE_VOLUME;
}

/*
 * --INFO--
 * PAL Address: 0x801C8800
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ExpressionChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int delta[REDSOUND_MIDI_DELTA_BUFFER_WORD_COUNT];
    int expression;

    delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
    if (delta[0] == 0) {
        delta[0]++;
    }

    expression = (char)*track->m_command++;
    track->m_expressionAdd = DataAddCompute(&track->m_expression, expression, delta);
    track->m_expressionDelta = delta[0];
}

/*
 * --INFO--
 * PAL Address: 0x801C8884
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PanDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    u32 pan;

    pan = *track->m_command++;
    track->m_pan = pan << REDSOUND_FIXED_SHIFT;
    track->m_panAdd = 0;
    track->m_panDelta = 0;
    if (track->m_shakeFunc == 0) {
        track->m_shakePan = 0;
    }
    m_ChangeStatus |= REDSOUND_VOICE_UPDATE_VOLUME;
}

/*
 * --INFO--
 * PAL Address: 0x801C88E0
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PanChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[REDSOUND_MIDI_DELTA_BUFFER_WORD_COUNT];
	u32 pan;

	delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
	if (delta[0] == 0) {
		delta[0]++;
	}
	if (track->m_shakeFunc == 0) {
		track->m_pan += track->m_shakePan * REDSOUND_FIXED_ONE;
		track->m_shakePan = 0;
	}
	pan = *track->m_command++;
	track->m_panAdd = DataAddCompute(&track->m_pan, pan, delta);
	track->m_panDelta = delta[0];
}

/*
 * --INFO--
 * PAL Address: 0x801C8984
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PortamentOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_portamentTime = DeltaTimeSumup((unsigned char**)&track->m_command);
}

/*
 * --INFO--
 * PAL Address: 0x801C89B8
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PortamentOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_portamentTime = 0;
    track->m_portamentPitch = -1;
}

/*
 * --INFO--
 * PAL Address: 0x801C89CC
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_SlurOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_flags |= REDSOUND_TRACK_FLAG_SLUR;
    track->m_flags &= ~REDSOUND_TRACK_FLAG_SLUR_RELEASE;
}

/*
 * --INFO--
 * PAL Address: 0x801C89E8
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_SlurOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_flags &= ~REDSOUND_TRACK_FLAG_SLUR;
}

/*
 * --INFO--
 * PAL Address: 0x801C89F8
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_Sweep(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int delta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];
    int command;
    int value;
    RedVoiceDATA* voiceData;

    delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
    if (delta[0] == 0) {
        delta[0] += 1;
    }

    command = (s8)*track->m_command++;
    command <<= 8;
    value = 0;
    track->m_sweepAdd = DataAddCompute(&value, command, delta);
    track->m_sweepDelta = delta[0];
    track->m_portamentPitch &= REDSOUND_FIXED_WHOLE_MASK;

    voiceData = p_VoiceData;
    do {
        if (voiceData->m_track == track) {
            voiceData->m_basePitch &= REDSOUND_FIXED_WHOLE_MASK;
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801c8acc
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TenutoOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_flags |= REDSOUND_TRACK_FLAG_TENUTO;
}

/*
 * --INFO--
 * PAL Address: 0x801c8adc
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TenutoOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_flags &= ~REDSOUND_TRACK_FLAG_TENUTO;
}

/*
 * --INFO--
 * PAL Address: 0x801C8AEC
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_Default(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedVoiceDATA* voice;

    *(int*)&track->m_adsrAR = REDSOUND_TRACK_ADSR_DEFAULT_WORD;
    *(int*)&track->m_adsrSR = REDSOUND_TRACK_ADSR_DEFAULT_WORD;
    memset(&track->m_adsrAR, REDSOUND_TRACK_ADSR_DEFAULT_WORD, REDSOUND_TRACK_ADSR_SIZE);

    voice = p_VoiceData;
    do {
        if ((voice->m_track == track) && (voice->m_waveData != 0)) {
            memcpy(voice->m_adsrTime, voice->m_waveData->m_adsr, REDSOUND_TRACK_ADSR_SIZE);
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8B8C
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_AL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value;
    RedVoiceDATA* voice;

    value = *track->m_command++;
    track->m_adsrAL = value;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_ATTACK] = value;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8BF4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_AR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedVoiceDATA* voice;
    int delta;

    delta = DeltaTimeSumup((unsigned char**)&track->m_command);
    track->m_adsrAR = delta;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_ATTACK] = delta;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8C70
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_DL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value;
    RedVoiceDATA* voice;

    value = *track->m_command++;
    track->m_adsrDL = value;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_DECAY] = value;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8CD8
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_DR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedVoiceDATA* voice;
    int delta;

    delta = DeltaTimeSumup((unsigned char**)&track->m_command);
    track->m_adsrDR = delta;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_DECAY] = delta;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8D54
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_SL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value;
    RedVoiceDATA* voice;

    value = *track->m_command++;
    track->m_adsrSL = value;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_SUSTAIN] = value;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8DBC
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_SR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedVoiceDATA* voice;
    int delta;

    delta = DeltaTimeSumup((unsigned char**)&track->m_command);
    track->m_adsrSR = delta;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrTime[REDSOUND_VOICE_ADSR_SUSTAIN] = delta;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8E38
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_RL(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value;
    RedVoiceDATA* voice;

    value = *track->m_command++;
    track->m_adsrRL = value;

    voice = p_VoiceData;
    do {
        if (voice->m_track == track) {
            voice->m_adsrLevel[REDSOUND_VOICE_ADSR_RELEASE] = value;
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
        }
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8EA0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ADSR_RR(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	RedVoiceDATA* voice;
	int delta;

	delta = DeltaTimeSumup((unsigned char**)&track->m_command);
	track->m_adsrRR = delta;

	voice = p_VoiceData;
	do {
		if (voice->m_track == track) {
			voice->m_adsrTime[REDSOUND_VOICE_ADSR_RELEASE] = delta;
			voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_DIRTY;
		}
		voice++;
	} while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C8F1C
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_SustainPedal(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    RedVoiceDATA* voice;

    if (*track->m_command != 0) {
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_SUSTAIN;
        voice = p_VoiceData;
        do {
            if (voice->m_track == track) {
                voice->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_SUSTAIN;
            }
            voice++;
        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
    } else {
        track->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_SUSTAIN;
        voice = p_VoiceData;
        do {
            if (voice->m_track == track) {
                voice->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_SUSTAIN;
            }
            voice++;
        } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
    }

    track->m_command += 1;
    SetVoiceSwitch(track, track->m_voiceSwitch);
}

/*
 * --INFO--
 * PAL Address: 0x801C8FF0
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ChannelAlloc(RedSoundCONTROL* control, RedKeyOnDATA*, RedTrackDATA* track)
{
    control->m_channelAlloc = (int)*track->m_command++;
}

/*
 * --INFO--
 * PAL Address: 0x801C9008
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ChannelPriority(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int command;

    command = *track->m_command++;
    if (command != 0) {
        track->m_note.m_allocFlags |= REDSOUND_NOTE_ALLOC_PRIORITY;
    } else {
        track->m_note.m_allocFlags &= ~REDSOUND_NOTE_ALLOC_PRIORITY;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9050
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ChannelFix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int command;

    command = *track->m_command++;
    if (command != 0) {
        track->m_note.m_allocFlags |= REDSOUND_NOTE_ALLOC_RESERVED;
    } else {
        track->m_note.m_allocFlags &= ~REDSOUND_NOTE_ALLOC_RESERVED;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801c9098
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateOn(RedSoundCONTROL* control, RedKeyOnDATA* keyOn, RedTrackDATA* track)
{
    int depth;
    int divisor;
    int output;
    RedVoiceDATA* entry;

    track->m_vibrateDepth = (unsigned int)track->m_command[REDSOUND_MIDI_MOD_DEPTH] << REDSOUND_FIXED_SHIFT;
    if (track->m_command[REDSOUND_MIDI_MOD_RATE] != 0) {
        depth = (unsigned int)track->m_command[REDSOUND_MIDI_MOD_RATE];
    } else {
        depth = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
    }

    divisor = depth;
    track->m_vibrateRate = REDSOUND_MIDI_RATE_FIXED_NUMERATOR / divisor;
    track->m_vibrateFunc = SwingEntryFunction[track->m_command[REDSOUND_MIDI_MOD_FUNCTION] & REDSOUND_MIDI_SWING_FUNC_MASK];
    track->m_vibrateRateDelta = track->m_vibrateDepthDelta = 0;
    track->m_command += 3;

    entry = p_VoiceData;
    do {
        if (entry->m_track == track) {
            divisor = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
            entry->m_pitchModDelay = track->m_vibrateDelay;
            if (track->m_vibrateRate >> REDSOUND_FIXED_SHIFT != 0) {
                divisor /= track->m_vibrateRate >> REDSOUND_FIXED_SHIFT;
            }
            if (track->m_vibrateDelayDepth != 0) {
                output = (int)track->m_vibrateDelayDepth * (divisor * REDSOUND_MIDI_MOD_DELAY_SCALE);
            } else {
                output = 0;
            }
            entry->m_pitchModFrames = output;
            entry->m_pitchModFrame = 0;
            entry->m_pitchModPhase = 0;
        }
        entry++;
    } while (entry < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801c91b8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_vibrateFunc = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C91C4
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_vibrateDepth = (unsigned int)*track->m_command++ << REDSOUND_FIXED_SHIFT;
	track->m_vibrateDepthDelta = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C91E8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];

	delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	track->m_vibrateDepthAdd = DataAddCompute(&track->m_vibrateDepth, *track->m_command, delta);
	track->m_vibrateDepthDelta = (short)delta[0];
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9260
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int rate;

	if (*track->m_command != 0) {
		rate = *track->m_command;
	} else {
		rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	int divisor = rate;
	track->m_vibrateRate = REDSOUND_MIDI_RATE_FIXED_NUMERATOR / divisor;
	track->m_vibrateRateDelta = 0;
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C92C0
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int trackDelta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];
    int rate;
    int divisor;

    trackDelta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
    if (trackDelta[0] == 0) {
        trackDelta[0] += 1;
    }

    if (*track->m_command != 0) {
        divisor = *track->m_command;
    } else {
        divisor = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
    }

    rate = divisor;
    rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR / rate;
    track->m_vibrateRateAdd = DataAddCompute(&track->m_vibrateRate, rate, trackDelta);
    track->m_vibrateRateDelta = (short)trackDelta[0];
    track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9370
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u32 type = *track->m_command++;

	track->m_vibrateFunc = SwingEntryFunction[type & REDSOUND_MIDI_SWING_FUNC_MASK];
}

/*
 * --INFO--
 * PAL Address: 0x801C93B0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_VibrateDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_vibrateDelay = (short)track->m_command[REDSOUND_MIDI_MOD_DELAY_FRAMES];
	track->m_vibrateDelayDepth = (short)track->m_command[REDSOUND_MIDI_MOD_DELAY_DEPTH];
	track->m_command += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801c93d8
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int rateDivisor;
	int divisor;
	int output;
	RedVoiceDATA* voice;

	track->m_tremoloDepth = (unsigned int)track->m_command[REDSOUND_MIDI_MOD_DEPTH] << REDSOUND_FIXED_SHIFT;
	if (track->m_command[REDSOUND_MIDI_MOD_RATE] != 0) {
		rateDivisor = (unsigned int)track->m_command[REDSOUND_MIDI_MOD_RATE];
	} else {
		rateDivisor = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	divisor = rateDivisor;
	track->m_tremoloRate = REDSOUND_MIDI_RATE_FIXED_NUMERATOR / divisor;
	track->m_tremoloFunc = SwingEntryFunction[track->m_command[REDSOUND_MIDI_MOD_FUNCTION] & REDSOUND_MIDI_SWING_FUNC_MASK];
	track->m_tremoloRateDelta = track->m_tremoloDepthDelta = 0;
	track->m_command += 3;

	voice = p_VoiceData;
	do {
		if (voice->m_track == track) {
			divisor = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
			voice->m_volumeModDelay = track->m_tremoloDelay;
			if (track->m_tremoloRate >> REDSOUND_FIXED_SHIFT != 0) {
				divisor /= track->m_tremoloRate >> REDSOUND_FIXED_SHIFT;
			}
			if (track->m_tremoloDelayDepth != 0) {
				output = track->m_tremoloDelayDepth * (divisor * REDSOUND_MIDI_MOD_DELAY_SCALE);
			} else {
				output = 0;
			}
			voice->m_volumeModFrames = output;
			voice->m_volumeModFrame = 0;
			voice->m_volumeModPhase = 0;
		}
		voice++;
	} while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C94F8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_tremoloFunc = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C9504
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_tremoloDepth = *track->m_command++ << REDSOUND_FIXED_SHIFT;
	track->m_tremoloDepthDelta = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C9528
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];

	delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	track->m_tremoloDepthAdd = DataAddCompute(&track->m_tremoloDepth, *track->m_command, delta);
	track->m_tremoloDepthDelta = (short)delta[0];
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C95A0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int rate;

	if (*track->m_command != 0) {
		rate = *track->m_command;
	} else {
		rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	int divisor = rate;
	track->m_tremoloRate = REDSOUND_MIDI_RATE_FIXED_NUMERATOR / divisor;
	track->m_tremoloRateDelta = 0;
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9600
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];
	int rate;
	int divisor;

	delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	if (*track->m_command != 0) {
		divisor = *track->m_command;
	} else {
		divisor = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	rate = divisor;
	rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR / rate;
	track->m_tremoloRateAdd = DataAddCompute(&track->m_tremoloRate, rate, delta);
	track->m_tremoloRateDelta = (short)delta[0];
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C96B0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u32 type = *track->m_command++;

	track->m_tremoloFunc = SwingEntryFunction[type & REDSOUND_MIDI_SWING_FUNC_MASK];
}

/*
 * --INFO--
 * PAL Address: 0x801C96F0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_TremoloDelay(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_tremoloDelay = (s16)track->m_command[REDSOUND_MIDI_MOD_DELAY_FRAMES];
	track->m_tremoloDelayDepth = (s16)track->m_command[REDSOUND_MIDI_MOD_DELAY_DEPTH];
	track->m_command += 2;
}

/*
 * --INFO--
 * PAL Address: 0x801C9718
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int rate;
	int divisor;

	track->m_shakeDepth = (unsigned int)track->m_command[REDSOUND_MIDI_MOD_DEPTH] << REDSOUND_FIXED_SHIFT;
	if (track->m_command[REDSOUND_MIDI_MOD_RATE] != 0) {
		rate = (unsigned int)track->m_command[REDSOUND_MIDI_MOD_RATE];
	} else {
		rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	divisor = rate;
	track->m_shakeRate = REDSOUND_MIDI_RATE_FIXED_NUMERATOR / divisor;
	track->m_shakeFunc = SwingEntryFunction[track->m_command[REDSOUND_MIDI_MOD_FUNCTION] & REDSOUND_MIDI_SWING_FUNC_MASK];
	track->m_shakeRateDelta = track->m_shakeDepthDelta = 0;
	track->m_shakeOutput = 0;
	track->m_shakePan = 0;
	track->m_command += 3;
}

/*
 * --INFO--
 * PAL Address: 0x801c97bc
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_shakeFunc = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C97C8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeDepthDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_shakeDepth = (unsigned int)*track->m_command++ << REDSOUND_FIXED_SHIFT;
    track->m_shakeDepthDelta = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801C97EC
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeDepthChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];

	delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	track->m_shakeDepthAdd = DataAddCompute(&track->m_shakeDepth, *track->m_command, delta);
	track->m_shakeDepthDelta = (short)delta[0];
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9864
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeRateDirect(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int rate;

	if (*track->m_command != 0) {
		rate = *track->m_command;
	} else {
		rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	int divisor = rate;
	track->m_shakeRate = REDSOUND_MIDI_RATE_FIXED_NUMERATOR / divisor;
	track->m_shakeRateDelta = 0;
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C98C4
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeRateChange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	int delta[REDSOUND_MIDI_SINGLE_DELTA_WORD_COUNT];
	int rate;
	int divisor;

	delta[0] = DeltaTimeSumup((unsigned char**)&track->m_command);
	if (delta[0] == 0) {
		delta[0] += 1;
	}
	if (*track->m_command != 0) {
		divisor = *track->m_command;
	} else {
		divisor = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR;
	}
	rate = divisor;
	rate = REDSOUND_MIDI_DEFAULT_RATE_DIVISOR / rate;
	track->m_shakeRateAdd = DataAddCompute(&track->m_shakeRate, rate, delta);
	track->m_shakeRateDelta = (short)delta[0];
	track->m_command += 1;
}

/*
 * --INFO--
 * PAL Address: 0x801C9974
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ShakeType(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	u32 type = *track->m_command++;

	track->m_shakeFunc = SwingEntryFunction[type & REDSOUND_MIDI_SWING_FUNC_MASK];
}

/*
 * --INFO--
 * PAL Address: 0x801C99B4
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_FineTuneAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_fineTune = (int)*track->m_command++;
	m_ChangeStatus |= REDSOUND_VOICE_UPDATE_PITCH;
}

/*
 * --INFO--
 * PAL Address: 0x801C99D8
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_FineTuneRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_fineTune = track->m_fineTune + *(s8*)track->m_command++;
	m_ChangeStatus |= REDSOUND_VOICE_UPDATE_PITCH;
}

/*
 * --INFO--
 * PAL Address: 0x801C9A04
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyTransposeAbsolute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_keyTranspose = (short)(*(s8*)track->m_command++ << 8);
	m_ChangeStatus |= REDSOUND_VOICE_UPDATE_PITCH;
}

/*
 * --INFO--
 * PAL Address: 0x801C9A30
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_KeyTransposeRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
	track->m_keyTranspose += *(s8*)track->m_command++ << 8;
	m_ChangeStatus |= REDSOUND_VOICE_UPDATE_PITCH;
}

/*
 * --INFO--
 * PAL Address: 0x801C9A64
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _PitchBendCompute(RedTrackDATA* track, int bend)
{
    RedVoiceDATA* voiceData = p_VoiceData;

    do {
        if (voiceData->m_track == track) {
            if (voiceData->m_waveData != 0) {
                int pitch;
                int computedPitch;
                if ((voiceData->m_stateFlags & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0) {
                    pitch = voiceData->m_basePitch + track->m_pitch;
                } else {
                    pitch = voiceData->m_basePitch + p_MusicPitchControl->m_value;
                }
                computedPitch = pitch;
                voiceData->m_pitch = PitchCompute(computedPitch, track->m_keyTranspose + bend,
                                                   voiceData->m_waveData->m_pitch, track->m_fineTune);
                voiceData->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
            }
        }
        voiceData++;
    } while (voiceData < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801C9B3C
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PitchBend(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int bend = (unsigned int)track->m_command[REDSOUND_MIDI_PITCH_BEND_HIGH] *
                   REDSOUND_MIDI_PITCH_BEND_HIGH_SCALE +
               ((unsigned int)track->m_command[REDSOUND_MIDI_PITCH_BEND_LOW] - REDSOUND_MIDI_PITCH_BEND_CENTER);

    track->m_pitchBendRaw = bend;
    bend *= track->m_pitchBendRange;
    bend >>= 5;
    track->m_pitchBend = bend;
    track->m_command += 2;
    _PitchBendCompute(track, track->m_pitchBend);
}

/*
 * --INFO--
 * PAL Address: 0x801C9BC0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_PitchBendRange(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int bend;

    track->m_pitchBendRange = *track->m_command++;
    bend = track->m_pitchBendRaw * track->m_pitchBendRange;
    bend >>= 5;
    track->m_pitchBend = bend;
    _PitchBendCompute(track, track->m_pitchBend);
}

/*
 * --INFO--
 * PAL Address: 0x801C9C30
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ReverbOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_MIX_ALL;
    SetVoiceSwitch(track, track->m_voiceSwitch);
    m_ChangeStatus |= REDSOUND_VOICE_UPDATE_VOLUME;
}

/*
 * --INFO--
 * PAL Address: 0x801C9C7C
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ReverbOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_REVERB_MASK;
    track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_DRY_STEREO;
    SetVoiceSwitch(track, track->m_voiceSwitch);
    m_ChangeStatus |= REDSOUND_VOICE_UPDATE_VOLUME;
}

/*
 * --INFO--
 * PAL Address: 0x801C9CD4
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_ReverbMix(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    track->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_MIX_MASK;

    switch (track->m_command[REDSOUND_MIDI_REVERB_MIX_LEFT]) {
    case 1:
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_LEFT;
        break;
    case 2:
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_LEFT;
    default:
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_DRY_LEFT;
        break;
    }

    switch (track->m_command[REDSOUND_MIDI_REVERB_MIX_RIGHT]) {
    case 1:
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_RIGHT;
        break;
    case 2:
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_RIGHT;
    default:
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_DRY_RIGHT;
        break;
    }
    track->m_command += 2;
    SetVoiceSwitch(track, track->m_voiceSwitch);
    m_ChangeStatus |= REDSOUND_VOICE_UPDATE_VOLUME;
}

/*
 * --INFO--
 * PAL Address: 0x801C9DBC
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_StepRelative(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value;
    short step;

    value = (s8)*track->m_command++;
    if (value != 0) {
        step = track->m_step + value;
    } else {
        step = 0;
    }
    track->m_step = step;
    track->m_step2 = 0;

    if (track->m_step < -9999) {
        track->m_step = -9999;
    } else if (track->m_step > 9999) {
        track->m_step = 9999;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9E3C
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_StepRelative2(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int value;
    short step;

    value = *track->m_command++;
    track->m_step = 0;

    if (value != 0) {
        step = track->m_step2 + value;
    } else {
        step = 0;
    }
    track->m_step2 = step;

    if (track->m_step2 < -9999) {
        track->m_step2 = -9999;
    } else if (track->m_step2 > 9999) {
        track->m_step2 = 9999;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9EBC
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_FuzzyOn(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int mode;
    int value;
    int fuzzyValue;

    mode = *track->m_command++;
    value = *track->m_command++;
    if (value != 0) {
        fuzzyValue = value + 1;
    } else {
        fuzzyValue = REDSOUND_MIDI_FUZZY_DEFAULT_DEPTH;
    }
    value = fuzzyValue;

    switch (mode) {
    case 1:
        track->m_fuzzyVolumeDepth = value;
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_FUZZY_VOLUME;
        return;
    case 2:
        track->m_fuzzyPanDepth = value;
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_FUZZY_PAN;
        return;
    case 3:
        track->m_fuzzyDeltaTimeDepth = value;
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME;
        return;
    case 4:
        track->m_fuzzyAdsrDepth = value;
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_FUZZY_ADSR;
        return;
    default:
        track->m_fuzzyPitchDepth = value;
        track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_FUZZY_PITCH;
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801C9FA0
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void __MidiCtrl_FuzzyOff(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA* track)
{
    int mode;

    mode = *track->m_command++;

    switch (mode) {
    case 1:
        track->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_FUZZY_VOLUME;
        return;
    case 2:
        track->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_FUZZY_PAN;
        return;
    case 3:
        track->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME;
        return;
    case 4:
        track->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_FUZZY_ADSR;
        return;
    default:
        track->m_voiceSwitch &= ~REDSOUND_VOICE_SWITCH_FUZZY_PITCH;
        return;
    }
}
