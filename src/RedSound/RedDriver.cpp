#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "global.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
#include "dolphin/axfx.h"
#include "dolphin/os.h"

// Global objects that need initialization

extern "C" {
    int __OSReadROM();
}

struct RedWaveSettingState {
    int* m_slot;
    int m_waveId;
    void* m_waveData;
    int m_waveSize;
};

enum RedWaveSettingLayoutOffset {
    REDSOUND_WAVE_SETTING_SLOT_OFFSET = 0x00,
    REDSOUND_WAVE_SETTING_WAVE_ID_OFFSET = 0x04,
    REDSOUND_WAVE_SETTING_WAVE_DATA_OFFSET = 0x08,
    REDSOUND_WAVE_SETTING_WAVE_SIZE_OFFSET = 0x0C,
    REDSOUND_WAVE_SETTING_SIZE = 0x10,
};

enum RedDriverDmaLayoutSize {
    REDSOUND_DMA_REQUEST_ID_OFFSET = 0x00,
    REDSOUND_DMA_REQUEST_DIRECTION_OFFSET = 0x04,
    REDSOUND_DMA_REQUEST_MAIN_MEMORY_OFFSET = 0x08,
    REDSOUND_DMA_REQUEST_ARAM_MEMORY_OFFSET = 0x0C,
    REDSOUND_DMA_REQUEST_SIZE_OFFSET = 0x10,
    REDSOUND_DMA_REQUEST_CALLBACK_OFFSET = 0x14,
    REDSOUND_DMA_REQUEST_CALLBACK_DATA_OFFSET = 0x18,
    REDSOUND_DMA_MAIN_QUEUE_INDEX = 0,
    REDSOUND_DMA_STREAM_QUEUE_INDEX = 1,
    REDSOUND_DMA_QUEUE_COUNT = 2,
    REDSOUND_DMA_REQUEST_SIZE = 0x1C,
    REDSOUND_DMA_QUEUE_WORD_COUNT = 0x380,
    REDSOUND_DMA_CONTROL_WORD_COUNT = REDSOUND_DMA_QUEUE_WORD_COUNT * 2,
    REDSOUND_DMA_QUEUE_ENTRY_COUNT = 0x80,
    REDSOUND_DMA_CONTROL_ENTRY_COUNT = REDSOUND_DMA_QUEUE_ENTRY_COUNT * 2,
    REDSOUND_DMA_QUEUE_SIZE = REDSOUND_DMA_REQUEST_SIZE * REDSOUND_DMA_QUEUE_ENTRY_COUNT,
    REDSOUND_DMA_CONTROL_SIZE = REDSOUND_DMA_QUEUE_SIZE * REDSOUND_DMA_QUEUE_COUNT,
    REDSOUND_DMA_TRANSFER_ALIGN = 0x20,
    REDSOUND_DMA_TRANSFER_ALIGN_MASK = ~(REDSOUND_DMA_TRANSFER_ALIGN - 1),
    REDSOUND_DMA_MAX_CHUNK_SIZE = 0x40000,
    REDSOUND_DMA_DIRECTION_TO_ARAM = 0,
    REDSOUND_DMA_DIRECTION_FROM_ARAM = 1,
    REDSOUND_DMA_ARQ_OWNER_ID = 0x469,
    REDSOUND_DMA_ARQ_PRIORITY = 1,
};

enum RedDriverSyncLayoutOffset {
    REDSOUND_DRIVER_SYNC_MAIN_THREAD_OFFSET = 0x1C00,
    REDSOUND_DRIVER_SYNC_MAIN_SEMAPHORE_OFFSET = 0x1F18,
    REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET = 0x1F24,
    REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET = 0x1F28,
    REDSOUND_DRIVER_SYNC_WAVE_SEMAPHORE_OFFSET = 0x2240,
    REDSOUND_DRIVER_SYNC_WAVE_DATA_OFFSET = 0x224C,
    REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET = 0x225C,
    REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET = 0x2260,
    REDSOUND_DRIVER_SYNC_DMA_SEMAPHORE_OFFSET = 0x2578,
    REDSOUND_DRIVER_SYNC_DMA_REQUEST_OFFSET = 0x2584,
    REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET = 0x25A4,
    REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET = 0x25A8,
    REDSOUND_DRIVER_SYNC_MUSIC_SEMAPHORE_OFFSET = 0x28C0,
    REDSOUND_DRIVER_SYNC_SIZE = 0x28CC,
    REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET = 0x28CC,
    REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET = 0x28DC,
    REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET = 0x28E8,
    REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE = 0x0C,
    REDSOUND_DRIVER_BSS_ENTRY_OFFSET = 0x28F4,
    REDSOUND_DRIVER_BSS_SIZE = 0x290C,
};

enum RedDriverGlobalObjectSize {
    REDSOUND_SE_BLOCK_DATA_TABLE_SIZE = 0x10,
    REDSOUND_RED_MEMORY_SIZE = 0x01,
    REDSOUND_RED_ENTRY_SIZE = 0x18,
};

enum RedDriverSmallDataLayout {
    REDSOUND_DRIVER_SBSS_SIZE = 0xD8,
    REDSOUND_DRIVER_SBSS_MASTER_TIME_OFFSET = 0x00,
    REDSOUND_DRIVER_SBSS_DMA_NOW_OFFSET = 0x28,
    REDSOUND_DRIVER_SBSS_SOUND_CONTROL_BUFFER_OFFSET = 0x38,
    REDSOUND_DRIVER_SBSS_MUSIC_REPLAY_POINT_OFFSET = 0x60,
    REDSOUND_DRIVER_SBSS_STREAM_OFFSET = 0x80,
    REDSOUND_DRIVER_SBSS_VOICE_DATA_OFFSET = 0x8C,
    REDSOUND_DRIVER_SBSS_EDITOR_VOICE_OFFSET = 0x90,
    REDSOUND_DRIVER_SBSS_MUTE_OFFSET = 0xC0,
    REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE = 0xC8,
    REDSOUND_DRIVER_SBSS_RED_MEMORY_OFFSET = 0xC8,
    REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_OFFSET = 0xC9,
    REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE = 0x03,
    REDSOUND_DRIVER_SBSS_DMA_EXECUTE_OFFSET = 0xCC,
    REDSOUND_DRIVER_SBSS_DMA_IN_THREAD_OFFSET = 0xD0,
    REDSOUND_DRIVER_SBSS_TRAILING_PAD_SIZE = 0x04,
};

enum RedDriverStringLayout {
    REDSOUND_DRIVER_DMA_CHECK_HEADER_SIZE = 0x20,
    REDSOUND_DRIVER_LOG_PREFIX_SIZE = 0x12,
    REDSOUND_DRIVER_DMA_STATUS_FMT_SIZE = 0x3E,
    REDSOUND_DRIVER_DMA_ENTRY_FMT_SIZE = 0x48,
    REDSOUND_DRIVER_MUSIC_HEADER_ERROR_FMT_SIZE = 0x22,
    REDSOUND_DRIVER_SE_SEP_HEADER_ERROR_FMT_SIZE = 0x23,
    REDSOUND_DRIVER_LOG_WARN_COLOR_SIZE = 0x08,
    REDSOUND_DRIVER_LOG_RESET_SIZE = 0x05,
    REDSOUND_DRIVER_RODATA_SIZE = 0xFD,
    REDSOUND_DRIVER_SDATA2_SIZE = 0x0D,
};

enum RedDriverDmaThreadStage {
    REDSOUND_DMA_THREAD_IDLE = 0,
    REDSOUND_DMA_THREAD_SELECT_QUEUE = 1,
    REDSOUND_DMA_THREAD_LOAD_ENTRY = 2,
    REDSOUND_DMA_THREAD_POST_REQUEST = 3,
    REDSOUND_DMA_THREAD_WAIT_REQUEST = 4,
    REDSOUND_DMA_THREAD_ADVANCE_QUEUE = 5,
    REDSOUND_DMA_THREAD_STORE_QUEUE = 6,
    REDSOUND_DMA_THREAD_POLL_STATUS = 7,
    REDSOUND_DMA_THREAD_RUN_CALLBACK = 8,
    REDSOUND_DMA_THREAD_FINISH_ENTRY = 9,
};

struct RedDmaRequest {
    int m_id;
    int m_direction;
    int m_mainMemory;
    int m_aramMemory;
    int m_size;
    RedDmaCallback m_callback;
    void* m_callbackData;
};

struct RedDriverSyncState {
    RedDmaRequest m_dmaQueue[REDSOUND_DMA_QUEUE_ENTRY_COUNT];
    RedDmaRequest m_streamDmaQueue[REDSOUND_DMA_QUEUE_ENTRY_COUNT];
    OSThread m_mainThread;
    OSSemaphore m_mainSemaphore;
    u8 m_mainThreadAlignPadding[REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET -
                                 REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET];
    OSThread m_waveThread;
    OSSemaphore m_waveSemaphore;
    RedWaveSettingState m_waveSettingData;
    u8 m_waveThreadAlignPadding[REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET -
                                 REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET];
    OSThread m_dmaThread;
    OSSemaphore m_dmaSemaphore;
    ARQRequest m_dmaRequest;
    u8 m_dmaThreadAlignPadding[REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET -
                                REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET];
    OSThread m_musicThread;
    OSSemaphore m_musicSemaphore;
};

struct RedDriverBssState {
    RedDriverSyncState m_sync;
    RedSeBlockHEAD* volatile m_seBlockData[REDSOUND_SE_BLOCK_BANK_COUNT];
    u8 m_entryWork0[REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE];
    u8 m_entryWork1[REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE];
    CRedEntry m_entry;
};

struct RedDriverSmallDataTailState {
    u8 m_beforeRedMemory[REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE];
    CRedMemory m_redMemory;
    u8 m_redMemoryAlignPadding[REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE];
    volatile int m_dmaExecute;
    volatile int m_dmaInThread;
    u8 m_trailingPadding[REDSOUND_DRIVER_SBSS_TRAILING_PAD_SIZE];
};

STATIC_ASSERT(offsetof(RedDmaRequest, m_id) == REDSOUND_DMA_REQUEST_ID_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_direction) == REDSOUND_DMA_REQUEST_DIRECTION_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_mainMemory) == REDSOUND_DMA_REQUEST_MAIN_MEMORY_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_aramMemory) == REDSOUND_DMA_REQUEST_ARAM_MEMORY_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_size) == REDSOUND_DMA_REQUEST_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_callback) == REDSOUND_DMA_REQUEST_CALLBACK_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_callbackData) == REDSOUND_DMA_REQUEST_CALLBACK_DATA_OFFSET);
STATIC_ASSERT(sizeof(RedDmaRequest) == REDSOUND_DMA_REQUEST_SIZE);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaQueue) == REDSOUND_DMA_QUEUE_SIZE);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_streamDmaQueue) == REDSOUND_DMA_QUEUE_SIZE);
STATIC_ASSERT(REDSOUND_DMA_QUEUE_SIZE == REDSOUND_DMA_QUEUE_WORD_COUNT * sizeof(int));
STATIC_ASSERT(REDSOUND_DMA_CONTROL_SIZE == REDSOUND_DMA_CONTROL_WORD_COUNT * sizeof(int));
STATIC_ASSERT(sizeof(RedDmaRequest) * REDSOUND_DMA_CONTROL_ENTRY_COUNT == REDSOUND_DMA_CONTROL_SIZE);
STATIC_ASSERT(REDSOUND_DMA_CONTROL_SIZE == REDSOUND_DRIVER_SYNC_MAIN_THREAD_OFFSET);
STATIC_ASSERT(offsetof(RedWaveSettingState, m_slot) == REDSOUND_WAVE_SETTING_SLOT_OFFSET);
STATIC_ASSERT(offsetof(RedWaveSettingState, m_waveId) == REDSOUND_WAVE_SETTING_WAVE_ID_OFFSET);
STATIC_ASSERT(offsetof(RedWaveSettingState, m_waveData) == REDSOUND_WAVE_SETTING_WAVE_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedWaveSettingState, m_waveSize) == REDSOUND_WAVE_SETTING_WAVE_SIZE_OFFSET);
STATIC_ASSERT(sizeof(RedWaveSettingState) == REDSOUND_WAVE_SETTING_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_mainThread) == REDSOUND_DRIVER_SYNC_MAIN_THREAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_mainSemaphore) == REDSOUND_DRIVER_SYNC_MAIN_SEMAPHORE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_mainThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_mainThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET - REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveThread) == REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveSemaphore) == REDSOUND_DRIVER_SYNC_WAVE_SEMAPHORE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveSettingData) == REDSOUND_DRIVER_SYNC_WAVE_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_waveThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET - REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaThread) == REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaSemaphore) == REDSOUND_DRIVER_SYNC_DMA_SEMAPHORE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaRequest) == REDSOUND_DRIVER_SYNC_DMA_REQUEST_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET - REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_musicThread) == REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_musicSemaphore) == REDSOUND_DRIVER_SYNC_MUSIC_SEMAPHORE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_musicSemaphore) + sizeof(OSSemaphore) == REDSOUND_DRIVER_SYNC_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_SYNC_SIZE == REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_seBlockData) == REDSOUND_SE_BLOCK_DATA_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET + REDSOUND_SE_BLOCK_DATA_TABLE_SIZE ==
              REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_entryWork0) == REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET + REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE ==
              REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_entryWork1) == REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET + REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE ==
              REDSOUND_DRIVER_BSS_ENTRY_OFFSET);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_ENTRY_OFFSET + sizeof(CRedEntry) == REDSOUND_DRIVER_BSS_SIZE);

enum RedExecCommandLayout {
    REDSOUND_EXEC_COMMAND_FUNC_OFFSET = 0x00,
    REDSOUND_EXEC_COMMAND_ARGS_OFFSET = 0x04,
    REDSOUND_EXEC_COMMAND_ARG_COUNT = 7,
    REDSOUND_EXEC_COMMAND_SIZE = 0x20,
};

enum RedExecCommandArgIndex {
    REDSOUND_EXEC_COMMAND_ARG0 = 0,
    REDSOUND_EXEC_COMMAND_ARG1 = 1,
    REDSOUND_EXEC_COMMAND_ARG2 = 2,
    REDSOUND_EXEC_COMMAND_ARG3 = 3,
    REDSOUND_EXEC_COMMAND_ARG4 = 4,
    REDSOUND_EXEC_COMMAND_ARG5 = 5,
    REDSOUND_EXEC_COMMAND_ARG6 = 6,
};

typedef void (*RedExecCommandFunc)(int* command);

struct RedExecCommand {
    RedExecCommandFunc m_func;
    int m_args[REDSOUND_EXEC_COMMAND_ARG_COUNT];
};

enum RedMusicPlayCommandLayout {
    REDSOUND_MUSIC_PLAY_COMMAND_ID_OFFSET = 0x00,
    REDSOUND_MUSIC_PLAY_COMMAND_VOLUME_OFFSET = 0x04,
    REDSOUND_MUSIC_PLAY_COMMAND_MODE_OFFSET = 0x08,
    REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_OFFSET = 0x0C,
    REDSOUND_MUSIC_PLAY_COMMAND_SIZE = 0x10,
    REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_SIZE =
        REDSOUND_MUSIC_PLAY_COMMAND_SIZE - REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_OFFSET,
};

struct RedMusicPlayCommand {
    int m_musicId;
    int m_volume;
    int m_mode;
    int m_reserved;
};

enum RedMusicCommandWord {
    REDSOUND_MUSIC_COMMAND_ID = 0,
    REDSOUND_MUSIC_COMMAND_VOLUME = 1,
    REDSOUND_MUSIC_COMMAND_MODE = 2,
    REDSOUND_MUSIC_COMMAND_FADE_TIME = 2,
    REDSOUND_MUSIC_COMMAND_STOP_NEXT = 3,
};

enum RedSoundModeCommandWord {
    REDSOUND_SOUND_MODE_COMMAND_MODE = 0,
};

enum RedReverbCommandWord {
    REDSOUND_REVERB_COMMAND_BANK = 0,
    REDSOUND_REVERB_COMMAND_DEPTH = 1,
    REDSOUND_REVERB_COMMAND_FADE_TIME = 2,
};

enum RedMasterVolumeCommandWord {
    REDSOUND_MASTER_VOLUME_COMMAND_VOLUME = 0,
};

enum RedDataCommandWord {
    REDSOUND_DATA_COMMAND_BUFFER = 0,
};

enum RedStreamCommandWord {
    REDSOUND_STREAM_COMMAND_ID = 0,
    REDSOUND_STREAM_COMMAND_DATA = 1,
    REDSOUND_STREAM_COMMAND_FILE_SIZE = 2,
    REDSOUND_STREAM_COMMAND_PAN = 3,
    REDSOUND_STREAM_COMMAND_PLAY_VOLUME = 4,
    REDSOUND_STREAM_COMMAND_VOLUME = 1,
    REDSOUND_STREAM_COMMAND_FADE_TIME = 2,
    REDSOUND_STREAM_COMMAND_PAUSE = 1,
};

enum RedSeCommandWord {
    REDSOUND_SE_COMMAND_ID = 0,
    REDSOUND_SE_COMMAND_VALUE = 1,
    REDSOUND_SE_COMMAND_FADE_TIME = 2,
    REDSOUND_SE_COMMAND_MODE = 3,
    REDSOUND_SE_BLOCK_COMMAND_BANK = 1,
    REDSOUND_SE_BLOCK_COMMAND_NO = 2,
    REDSOUND_SE_BLOCK_COMMAND_PAN = 3,
    REDSOUND_SE_BLOCK_COMMAND_VOLUME = 4,
    REDSOUND_SE_BLOCK_COMMAND_PITCH = 5,
    REDSOUND_SE_SEP_COMMAND_DATA = 1,
    REDSOUND_SE_SEP_COMMAND_ID = 1,
    REDSOUND_SE_SEP_COMMAND_PAN = 2,
    REDSOUND_SE_SEP_COMMAND_VOLUME = 3,
    REDSOUND_SE_SEP_COMMAND_PITCH = 4,
    REDSOUND_SE_MG_COMMAND_BANK = 0,
    REDSOUND_SE_MG_COMMAND_SEP = 1,
    REDSOUND_SE_MG_COMMAND_GROUP = 2,
    REDSOUND_SE_MG_COMMAND_KIND = 3,
    REDSOUND_SE_COMMAND_PAUSE = 1,
};

enum RedSeBlockDataCommandWord {
    REDSOUND_SE_BLOCK_DATA_COMMAND_BANK = 0,
    REDSOUND_SE_BLOCK_DATA_COMMAND_BUFFER = 1,
};

enum RedDriverTickHistoryLayout {
    REDSOUND_TICK_HISTORY_LATEST = 0,
    REDSOUND_TICK_HISTORY_COUNT = 100,
    REDSOUND_TICK_HISTORY_SIZE = sizeof(int) * REDSOUND_TICK_HISTORY_COUNT,
    REDSOUND_TICK_HISTORY_SHIFT_SIZE = sizeof(int) * (REDSOUND_TICK_HISTORY_COUNT - 1),
};

struct RedTickHistory {
    int m_ticks[REDSOUND_TICK_HISTORY_COUNT];
};

struct RedDriverSmallDataPrefixState {
    int m_redMasterTime;
    volatile int m_sequencialID;
    volatile int m_threadControl;
    volatile int m_threadExecute;
    int m_soundMode;
    RedTickHistory* volatile m_tick;
    u8* volatile m_zeroData;
    RedExecCommand* volatile m_execCommand;
    RedExecCommand* volatile m_execCommandNow;
    RedExecCommand* volatile m_execCommandOld;
    RedDmaRequest* volatile m_dmaControlNow[REDSOUND_DMA_QUEUE_COUNT];
    RedDmaRequest* volatile m_dmaControlOld[REDSOUND_DMA_QUEUE_COUNT];
    RedSoundCONTROL* volatile m_soundControlBuffer;
    RedSoundCONTROL* volatile m_soundControl;
    volatile int m_keyOnEntry;
    RedKeyOnDATA* volatile m_keyOnData;
    int m_soundPlayMode;
    int m_soundMasterControl;
    volatile int m_reportPrint;
    int m_musicFastSpeed;
    volatile int m_musicSkipLine;
    int m_musicKeySignature;
    int* volatile m_musicReplayPoint;
    RedControlRamp* volatile m_musicTempoControl;
    RedControlRamp* volatile m_musicPitchControl;
    int m_musicPhraseStop;
    RedMusicPlayCommand* volatile m_musicNextPlay;
    int m_crossTime;
    volatile int m_masterMusicVolume;
    volatile int m_masterSEVolume;
    RedStreamDATA* volatile m_stream;
    int m_dmaMode;
    volatile int m_seSkipStep;
    RedVoiceDATA* volatile m_voiceData;
    int m_editorVoice[REDSOUND_EDITOR_VOICE_COUNT];
    RedTrackDATA* m_editorTrack;
    u8* volatile m_mainThreadStack;
    int m_mainThreadTime;
    u8* volatile m_waveSettingThreadStack;
    int m_waveSettingStatus;
    u8* volatile m_dmaExecuteThreadStack;
    volatile int m_dmaStatus;
    u8* volatile m_musicSkipThreadStack;
    volatile int m_musicSkipComplete;
    RedReverbDepth* volatile m_reverbDepth;
    int m_mute[REDSOUND_MUTE_WORD_COUNT];
};

STATIC_ASSERT(offsetof(RedExecCommand, m_func) == REDSOUND_EXEC_COMMAND_FUNC_OFFSET);
STATIC_ASSERT(offsetof(RedExecCommand, m_args) == REDSOUND_EXEC_COMMAND_ARGS_OFFSET);
STATIC_ASSERT(sizeof(((RedExecCommand*)0)->m_args) == sizeof(int) * REDSOUND_EXEC_COMMAND_ARG_COUNT);
STATIC_ASSERT(sizeof(RedExecCommand) == REDSOUND_EXEC_COMMAND_SIZE);
STATIC_ASSERT(offsetof(RedMusicPlayCommand, m_musicId) == REDSOUND_MUSIC_PLAY_COMMAND_ID_OFFSET);
STATIC_ASSERT(offsetof(RedMusicPlayCommand, m_volume) == REDSOUND_MUSIC_PLAY_COMMAND_VOLUME_OFFSET);
STATIC_ASSERT(offsetof(RedMusicPlayCommand, m_mode) == REDSOUND_MUSIC_PLAY_COMMAND_MODE_OFFSET);
STATIC_ASSERT(offsetof(RedMusicPlayCommand, m_reserved) == REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_OFFSET);
STATIC_ASSERT(sizeof(((RedMusicPlayCommand*)0)->m_reserved) == REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_SIZE);
STATIC_ASSERT(sizeof(RedMusicPlayCommand) == REDSOUND_MUSIC_PLAY_COMMAND_SIZE);
STATIC_ASSERT(sizeof(RedTickHistory) == REDSOUND_TICK_HISTORY_SIZE);
STATIC_ASSERT(sizeof(((RedTickHistory*)0)->m_ticks) == REDSOUND_TICK_HISTORY_SIZE);
STATIC_ASSERT(offsetof(RedControlRamp, m_value) == REDSOUND_CONTROL_RAMP_VALUE_OFFSET);
STATIC_ASSERT(offsetof(RedControlRamp, m_step) == REDSOUND_CONTROL_RAMP_STEP_OFFSET);
STATIC_ASSERT(offsetof(RedControlRamp, m_count) == REDSOUND_CONTROL_RAMP_COUNT_OFFSET);
STATIC_ASSERT(sizeof(RedControlRamp) == REDSOUND_CONTROL_RAMP_SIZE);
STATIC_ASSERT(offsetof(RedReverbDepth, m_depth) == REDSOUND_REVERB_DEPTH_DEPTH_OFFSET);
STATIC_ASSERT(offsetof(RedReverbDepth, m_step) == REDSOUND_REVERB_DEPTH_STEP_OFFSET);
STATIC_ASSERT(offsetof(RedReverbDepth, m_count) == REDSOUND_REVERB_DEPTH_COUNT_OFFSET);
STATIC_ASSERT(sizeof(RedReverbDepth) == REDSOUND_REVERB_DEPTH_SIZE);
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_redMasterTime) == REDSOUND_DRIVER_SBSS_MASTER_TIME_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_dmaControlNow) == REDSOUND_DRIVER_SBSS_DMA_NOW_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSmallDataPrefixState*)0)->m_dmaControlNow) ==
              REDSOUND_DMA_QUEUE_COUNT * sizeof(RedDmaRequest*));
STATIC_ASSERT(sizeof(((RedDriverSmallDataPrefixState*)0)->m_dmaControlOld) ==
              REDSOUND_DMA_QUEUE_COUNT * sizeof(RedDmaRequest*));
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_soundControlBuffer) ==
              REDSOUND_DRIVER_SBSS_SOUND_CONTROL_BUFFER_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_musicReplayPoint) ==
              REDSOUND_DRIVER_SBSS_MUSIC_REPLAY_POINT_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_stream) == REDSOUND_DRIVER_SBSS_STREAM_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_voiceData) == REDSOUND_DRIVER_SBSS_VOICE_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_editorVoice) == REDSOUND_DRIVER_SBSS_EDITOR_VOICE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSmallDataPrefixState*)0)->m_editorVoice) ==
              REDSOUND_EDITOR_VOICE_COUNT * sizeof(int));
STATIC_ASSERT(offsetof(RedDriverSmallDataPrefixState, m_mute) == REDSOUND_DRIVER_SBSS_MUTE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSmallDataPrefixState*)0)->m_mute) == REDSOUND_MUTE_WORD_COUNT * sizeof(int));
STATIC_ASSERT(sizeof(RedDriverSmallDataPrefixState) == REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE);
STATIC_ASSERT(sizeof(CRedMemory) == REDSOUND_RED_MEMORY_SIZE);
STATIC_ASSERT(sizeof(CRedEntry) == REDSOUND_RED_ENTRY_SIZE);
STATIC_ASSERT(sizeof(p_SeBlockData) == REDSOUND_SE_BLOCK_DATA_TABLE_SIZE);
STATIC_ASSERT(offsetof(RedDriverSmallDataTailState, m_redMemory) == REDSOUND_DRIVER_SBSS_RED_MEMORY_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataTailState, m_redMemoryAlignPadding) ==
              REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSmallDataTailState*)0)->m_redMemoryAlignPadding) ==
              REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE);
STATIC_ASSERT(offsetof(RedDriverSmallDataTailState, m_dmaExecute) == REDSOUND_DRIVER_SBSS_DMA_EXECUTE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSmallDataTailState, m_dmaInThread) == REDSOUND_DRIVER_SBSS_DMA_IN_THREAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSmallDataTailState*)0)->m_trailingPadding) ==
              REDSOUND_DRIVER_SBSS_TRAILING_PAD_SIZE);
STATIC_ASSERT(sizeof(RedDriverSmallDataTailState) == REDSOUND_DRIVER_SBSS_SIZE);

enum RedDriverBufferSize {
    REDSOUND_ZERO_BUFFER_SIZE = 0x1000,
    REDSOUND_THREAD_STACK_SIZE = 0x1000,
    REDSOUND_WAVE_SETTING_TABLE_ALIGN = 0x40,
    REDSOUND_WAVE_SETTING_TABLE_ALIGN_MASK = ~(REDSOUND_WAVE_SETTING_TABLE_ALIGN - 1),
    REDSOUND_MUSIC_REPLAY_POINT_COUNT = 0x100,
    REDSOUND_MUSIC_REPLAY_POINT_SIZE = sizeof(int) * REDSOUND_MUSIC_REPLAY_POINT_COUNT,
    REDSOUND_MUSIC_REPLAY_POINT_ALLOC_SIZE = 0x400,
    REDSOUND_EXEC_COMMAND_COUNT = 0x100,
    REDSOUND_EXEC_COMMAND_BUFFER_SIZE = sizeof(RedExecCommand) * REDSOUND_EXEC_COMMAND_COUNT,
    REDSOUND_EXEC_COMMAND_ALLOC_SIZE = 0x2000,
    REDSOUND_EXEC_COMMAND_WORD_COUNT = REDSOUND_EXEC_COMMAND_BUFFER_SIZE / sizeof(int),
    REDSOUND_MUSIC_NEXT_PLAY_BUFFER_SIZE = sizeof(RedMusicPlayCommand),
    REDSOUND_SOUND_CONTROL_ALLOC_SIZE = 0x1250,
    REDSOUND_KEY_ON_ALLOC_SIZE = 0x600,
    REDSOUND_VOICE_ALLOC_SIZE = 0x3000,
    REDSOUND_SE_TRACK_ARENA_ALLOC_SIZE = 0x2A80,
    REDSOUND_REVERB_DEPTH_ALLOC_SIZE = 0x18,
    REDSOUND_MUSIC_NEXT_PLAY_ALLOC_SIZE = 0x10,
    REDSOUND_STREAM_ALLOC_SIZE = 0x4C0,
};

STATIC_ASSERT(sizeof(int) * REDSOUND_MUSIC_REPLAY_POINT_COUNT == REDSOUND_MUSIC_REPLAY_POINT_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedExecCommand) * REDSOUND_EXEC_COMMAND_COUNT == REDSOUND_EXEC_COMMAND_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedSoundCONTROL) * REDSOUND_CONTROL_COUNT == REDSOUND_SOUND_CONTROL_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedKeyOnDATA) == REDSOUND_KEY_ON_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedVoiceDATA) * REDSOUND_VOICE_COUNT == REDSOUND_VOICE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedTrackDATA) * REDSOUND_SE_TRACK_COUNT == REDSOUND_SE_TRACK_ARENA_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedReverbDepth) * REDSOUND_REVERB_DEPTH_COUNT == REDSOUND_REVERB_DEPTH_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedMusicPlayCommand) == REDSOUND_MUSIC_NEXT_PLAY_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedStreamDATA) * REDSOUND_STREAM_COUNT == REDSOUND_STREAM_ALLOC_SIZE);

enum RedDriverEditorVoiceIndex {
    REDSOUND_EDITOR_VOICE_LEFT = 0,
    REDSOUND_EDITOR_VOICE_RIGHT = 1,
};

enum RedDriverThreadFlag {
    REDSOUND_THREAD_FLAG_MAIN = 1,
    REDSOUND_THREAD_FLAG_DMA = 2,
    REDSOUND_THREAD_FLAG_WAVE_SETTING = 4,
    REDSOUND_THREAD_FLAG_MUSIC_SKIP = 8,
};

enum RedDriverThreadConfig {
    REDSOUND_DMA_THREAD_PRIORITY = 3,
    REDSOUND_WORKER_THREAD_PRIORITY = 4,
    REDSOUND_THREAD_DETACHED = 1,
    REDSOUND_THREAD_YIELD_SLEEP_US = 0,
};

enum RedDriverSleepTimer {
    REDSOUND_SLEEP_TIMER_DIVISOR = 125000,
    REDSOUND_SLEEP_TIMER_SHIFT = 3,
};

enum RedDriverCommandParse {
    REDSOUND_DELTA_TIME_VALUE_MASK = 0x7F,
    REDSOUND_DELTA_TIME_CONTINUE_FLAG = 0x80,
    REDSOUND_DELTA_TIME_SHIFT = 7,
    REDSOUND_ENTRY_ID_MASK = 0x7fffffff,
};

// RedDriver-owned linkage (sbss/sdata tracked symbols)
static int m_RedMasterTime;
static volatile int m_SequencialID;
static volatile int m_ThreadControl;
static volatile int m_ThreadExecute;
static int m_SoundMode;
static RedTickHistory* volatile p_Tick;
u8* volatile p_ZeroData;
static RedExecCommand* volatile p_ExecCommand;
static RedExecCommand* volatile p_ExecCommandNow;
static RedExecCommand* volatile p_ExecCommandOld;
static RedDmaRequest* volatile p_DmaControlNow[REDSOUND_DMA_QUEUE_COUNT];
static RedDmaRequest* volatile p_DmaControlOld[REDSOUND_DMA_QUEUE_COUNT];
RedSoundCONTROL* volatile p_SoundControlBuffer;
RedSoundCONTROL* volatile p_SoundControl;
volatile int m_KeyOnEntry;
RedKeyOnDATA* volatile p_KeyOnData;
int m_SoundPlayMode;
int m_SoundMasterControl;
volatile int m_ReportPrint;
int m_MusicFastSpeed;
volatile int m_MusicSkipLine;
int m_MusicKeySignature;
int* volatile p_MusicReplayPoint;
RedControlRamp* volatile p_MusicTempoControl;
RedControlRamp* volatile p_MusicPitchControl;
int m_MusicPhraseStop;
static RedMusicPlayCommand* volatile p_MusicNextPlay;
int m_CrossTime;
volatile int m_MasterMusicVolume;
volatile int m_MasterSEVolume;
RedStreamDATA* volatile p_Stream;
static int m_DMAMode;
volatile int m_SeSkipStep;
RedVoiceDATA* volatile p_VoiceData;
int p_EditorVoice[REDSOUND_EDITOR_VOICE_COUNT];
RedTrackDATA* p_EditorTrack;
static u8* volatile p_MainThreadStack;
static int m_MainThreadTime;
static u8* volatile p_WaveSettingThreadStack;
static int m_WaveSettingStatus;
static u8* volatile p_DmaExecuteThreadStack;
static volatile int m_DMAStatus;
u8* volatile p_MusicSkipThreadStack;
volatile int m_MusicSkipComplete;
RedReverbDepth* volatile p_ReverbDepth;
unsigned int m_Mute[REDSOUND_MUTE_WORD_COUNT];
static RedDmaRequest m_DmaControl[REDSOUND_DMA_CONTROL_ENTRY_COUNT];
static OSThread m_MainThread;
static OSSemaphore m_MainSemaphore;
static OSThread m_WaveSettingThread;
static OSSemaphore m_WaveSettingSemaphore;
static RedWaveSettingState m_WaveSettingData;
static OSThread m_DmaExecuteThread;
static OSSemaphore m_DmaExecuteSemaphore;
static ARQRequest m_DMARequest;
OSThread m_MusicSkipThread;
OSSemaphore m_MusicSkipSemaphore;
RedSeBlockHEAD* volatile p_SeBlockData[REDSOUND_SE_BLOCK_BANK_COUNT];
CRedMemory c_RedMemory;
static volatile int m_DMAExecute;
static volatile int m_DMAInThread;
CRedEntry c_RedEntry;

STATIC_ASSERT(sizeof(m_RedMasterTime) + sizeof(m_SequencialID) + sizeof(m_ThreadControl) +
                  sizeof(m_ThreadExecute) + sizeof(m_SoundMode) + sizeof(p_Tick) +
                  sizeof(p_ZeroData) + sizeof(p_ExecCommand) + sizeof(p_ExecCommandNow) +
                  sizeof(p_ExecCommandOld) + sizeof(p_DmaControlNow) + sizeof(p_DmaControlOld) +
                  sizeof(p_SoundControlBuffer) + sizeof(p_SoundControl) + sizeof(m_KeyOnEntry) +
                  sizeof(p_KeyOnData) + sizeof(m_SoundPlayMode) + sizeof(m_SoundMasterControl) +
                  sizeof(m_ReportPrint) + sizeof(m_MusicFastSpeed) + sizeof(m_MusicSkipLine) +
                  sizeof(m_MusicKeySignature) + sizeof(p_MusicReplayPoint) +
                  sizeof(p_MusicTempoControl) + sizeof(p_MusicPitchControl) +
                  sizeof(m_MusicPhraseStop) + sizeof(p_MusicNextPlay) + sizeof(m_CrossTime) +
                  sizeof(m_MasterMusicVolume) + sizeof(m_MasterSEVolume) + sizeof(p_Stream) +
                  sizeof(m_DMAMode) + sizeof(m_SeSkipStep) + sizeof(p_VoiceData) +
                  sizeof(p_EditorVoice) + sizeof(p_EditorTrack) + sizeof(p_MainThreadStack) +
                  sizeof(m_MainThreadTime) + sizeof(p_WaveSettingThreadStack) +
                  sizeof(m_WaveSettingStatus) + sizeof(p_DmaExecuteThreadStack) +
                  sizeof(m_DMAStatus) + sizeof(p_MusicSkipThreadStack) +
                  sizeof(m_MusicSkipComplete) + sizeof(p_ReverbDepth) + sizeof(m_Mute) ==
              REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE + sizeof(c_RedMemory) +
                  REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE + sizeof(m_DMAExecute) +
                  sizeof(m_DMAInThread) + REDSOUND_DRIVER_SBSS_TRAILING_PAD_SIZE ==
              REDSOUND_DRIVER_SBSS_SIZE);

static inline RedDriverSyncState& RedDriverSync()
{
    return *reinterpret_cast<RedDriverSyncState*>(m_DmaControl);
}

static inline RedDmaRequest* RedDriverMainDmaQueue()
{
    return m_DmaControl;
}

static inline RedDmaRequest* RedDriverStreamDmaQueue()
{
    return m_DmaControl + REDSOUND_DMA_QUEUE_ENTRY_COUNT;
}

static inline RedDmaRequest* RedDriverStreamDmaQueueEnd()
{
    return m_DmaControl + REDSOUND_DMA_CONTROL_ENTRY_COUNT;
}

static inline OSThread& RedDriverMainThread()
{
    return m_MainThread;
}

static const char s_redDriverDmaCheckHeaderFmt[] = "%s **** DMA CHECK PROCESS ****\n";
static const char sRedDriverLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char sRedDriverDmaStatusFmt[] = "%s Status = %d, Semaphore = %d, Execute = %d, In Thread = %d\n";
static const char sRedDriverDmaEntryFmt[] = "%s ID = %d, MMem = %8.8X, AMem = %8.8X, Size = %8.8X, Callback = %8.8X\n";
static const char sRedDriverMusicHeaderErrorFmt[] = "%s%sMusic-Header was broken !!%s\n";
static const char sRedDriverSeSepHeaderErrorFmt[] = "%s%sSE-Sep-Header was broken !!%s\n";
static const char sRedDriverLogWarnColor[] = "\x1B[4;31m";
static const char sRedDriverLogReset[] = "\x1B[0m";

STATIC_ASSERT(sizeof(s_redDriverDmaCheckHeaderFmt) == REDSOUND_DRIVER_DMA_CHECK_HEADER_SIZE);
STATIC_ASSERT(sizeof(sRedDriverLogPrefix) == REDSOUND_DRIVER_LOG_PREFIX_SIZE);
STATIC_ASSERT(sizeof(sRedDriverDmaStatusFmt) == REDSOUND_DRIVER_DMA_STATUS_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedDriverDmaEntryFmt) == REDSOUND_DRIVER_DMA_ENTRY_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedDriverMusicHeaderErrorFmt) == REDSOUND_DRIVER_MUSIC_HEADER_ERROR_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedDriverSeSepHeaderErrorFmt) == REDSOUND_DRIVER_SE_SEP_HEADER_ERROR_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedDriverLogWarnColor) == REDSOUND_DRIVER_LOG_WARN_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedDriverLogReset) == REDSOUND_DRIVER_LOG_RESET_SIZE);
STATIC_ASSERT(sizeof(s_redDriverDmaCheckHeaderFmt) + sizeof(sRedDriverLogPrefix) +
                  sizeof(sRedDriverDmaStatusFmt) + sizeof(sRedDriverDmaEntryFmt) +
                  sizeof(sRedDriverMusicHeaderErrorFmt) + sizeof(sRedDriverSeSepHeaderErrorFmt) ==
              REDSOUND_DRIVER_RODATA_SIZE);
STATIC_ASSERT(sizeof(sRedDriverLogWarnColor) + sizeof(sRedDriverLogReset) == REDSOUND_DRIVER_SDATA2_SIZE);

/*
 * --INFO--
 * PAL Address: 0x801bcf0c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetSoundMode(int* command)
{
    m_SoundMode = command[REDSOUND_SOUND_MODE_COMMAND_MODE];
    if (command[REDSOUND_SOUND_MODE_COMMAND_MODE] == 1) {
        OSGetSoundMode(0);
    } else {
        OSGetSoundMode(1);
    }
    m_SoundPlayMode = m_SoundMode;
    switch (m_SoundPlayMode) {
    case 2:
        AXSetMode(2);
        break;
    default:
        AXSetMode(0);
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bcf88
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetReverbDepth(int* command)
{
    int fadeDepth;
    int reverbBank;
    int reverbDepth;
    int fadeStep;
    RedTrackDATA* track;

    reverbBank = command[REDSOUND_REVERB_COMMAND_BANK] & 1;
    reverbDepth = command[REDSOUND_REVERB_COMMAND_DEPTH] & REDSOUND_COMMAND_VALUE_MASK;
    fadeStep = command[REDSOUND_REVERB_COMMAND_FADE_TIME];
    if (reverbDepth != 0) {
        reverbDepth += 1;
        reverbDepth <<= 8;
        reverbDepth -= 1;
        reverbDepth <<= 12;
    }
    p_ReverbDepth[reverbBank].m_depth = reverbDepth;
    if (reverbBank != 0) {
        fadeStep = fadeStep * REDSOUND_SE_FADE_TICKS_PER_SECOND;
        fadeStep = fadeStep / REDSOUND_FRAMES_PER_SECOND;
        if (fadeStep == 0) {
            fadeStep++;
        }
        reverbDepth |= REDSOUND_FIXED_HALF;
        track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
        do {
            if ((u32)track->m_command != 0) {
                fadeDepth = track->m_reverbDepth & REDSOUND_FIXED_WHOLE_MASK;
                fadeDepth = reverbDepth - fadeDepth;
                track->m_reverbDepthAdd = fadeDepth / fadeStep;
                track->m_reverbDepthDelta = fadeStep;
            }
            track++;
        } while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd048
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetMusicData(int* command)
{
    c_RedEntry.SetMusicData((RedMusicHEAD*)command[REDSOUND_DATA_COMMAND_BUFFER]);
}

static void _MusicPlaySequence(int* command);
static void _MusicCrossPlaySequence(int* command);
static void _MusicNextPlaySequence(int* command);

/*
 * --INFO--
 * PAL Address: 0x801bd080
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicStop(int* command)
{
    MusicStop(command[REDSOUND_MUSIC_COMMAND_ID]);
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == REDSOUND_MUSIC_ID_NONE) ||
        (p_MusicNextPlay->m_musicId == command[REDSOUND_MUSIC_COMMAND_ID])) {
        p_MusicNextPlay->m_musicId = REDSOUND_MUSIC_ID_NONE;
    }
    if (p_MusicNextPlay->m_musicId < 0) {
        m_MusicPhraseStop = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd0f4
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicPlaySequence(int* command)
{
    int replayPoint;
    RedSoundCONTROL* soundControl;

    soundControl = p_SoundControlBuffer;
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId)) {
        return;
    }
    if (c_RedEntry.SearchMusicSequence(command[REDSOUND_MUSIC_COMMAND_ID]) >= 0) {
        replayPoint = command[REDSOUND_MUSIC_COMMAND_MODE];
        if (soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId != REDSOUND_MUSIC_ID_NONE) {
            if (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId != REDSOUND_MUSIC_ID_NONE) {
                MusicStop(soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId);
            }
            if (replayPoint == 0) {
                replayPoint = p_MusicReplayPoint[command[REDSOUND_MUSIC_COMMAND_ID]];
                p_MusicReplayPoint[command[REDSOUND_MUSIC_COMMAND_ID]] = 0;
            }
            if (replayPoint == 0) {
                memcpy(&soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY], soundControl, REDSOUND_CONTROL_SIZE);
                soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId = REDSOUND_MUSIC_ID_NONE;
            }
        }
        MusicPlay(command[REDSOUND_MUSIC_COMMAND_ID], command[REDSOUND_MUSIC_COMMAND_VOLUME], replayPoint);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd1fc
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicCrossPlaySequence(int* command)
{
    RedSoundCONTROL* control;
    RedSoundCONTROL* swapControl;
    int replayPoint;
    
    command[REDSOUND_MUSIC_COMMAND_FADE_TIME] =
        command[REDSOUND_MUSIC_COMMAND_FADE_TIME] * REDSOUND_MUSIC_FADE_TICKS_PER_SECOND;
    command[REDSOUND_MUSIC_COMMAND_FADE_TIME] =
        command[REDSOUND_MUSIC_COMMAND_FADE_TIME] / REDSOUND_FRAMES_PER_SECOND;
    if (command[REDSOUND_MUSIC_COMMAND_FADE_TIME] == 0) {
        command[REDSOUND_MUSIC_COMMAND_FADE_TIME] = command[REDSOUND_MUSIC_COMMAND_FADE_TIME] + 1;
    }
    control = p_SoundControlBuffer;
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == control[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId)) {
        return;
    }

    if (command[REDSOUND_MUSIC_COMMAND_ID] == control[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId) {
        control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolumeAdd =
            -control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolume / command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolumeDelta = command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        control = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY;
        control->m_masterVolumeAdd =
            (REDSOUND_MASTER_VOLUME_FULL_FIXED_HALF -
             control->m_masterVolume) /
            command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        control->m_masterVolumeDelta = command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        swapControl = (RedSoundCONTROL*)RedNew(REDSOUND_CONTROL_SIZE);
        memcpy(swapControl, &p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY], REDSOUND_CONTROL_SIZE);
        memcpy(&p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY], p_SoundControlBuffer,
               REDSOUND_CONTROL_SIZE);
        memcpy(p_SoundControlBuffer, swapControl, REDSOUND_CONTROL_SIZE);
        RedDelete(swapControl);
    } else {
        if (c_RedEntry.SearchMusicSequence(command[REDSOUND_MUSIC_COMMAND_ID]) >= 0) {
            m_CrossTime = command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
            replayPoint = 0;
            if (control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId != REDSOUND_MUSIC_ID_NONE) {
                if (control[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId != REDSOUND_MUSIC_ID_NONE) {
                    MusicStop(control[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId);
                }
                control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolumeAdd =
                    -control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolume /
                    command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
                control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolumeDelta = command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
                replayPoint = p_MusicReplayPoint[command[REDSOUND_MUSIC_COMMAND_ID]];
                p_MusicReplayPoint[command[REDSOUND_MUSIC_COMMAND_ID]] = 0;
                if (replayPoint == 0) {
                    memcpy(&control[REDSOUND_CONTROL_MUSIC_SECONDARY], control, REDSOUND_CONTROL_SIZE);
                    control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId = REDSOUND_MUSIC_ID_NONE;
                }
            }
            MusicPlay(command[REDSOUND_MUSIC_COMMAND_ID], command[REDSOUND_MUSIC_COMMAND_VOLUME], replayPoint);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd404
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicNextPlaySequence(int* command)
{
    RedSoundCONTROL* soundControl;

    soundControl = p_SoundControlBuffer;
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId)) {
        return;
    }
    if (c_RedEntry.SearchMusicSequence(command[REDSOUND_MUSIC_COMMAND_ID]) >= 0) {
        p_MusicNextPlay->m_musicId = command[REDSOUND_MUSIC_COMMAND_ID];
        p_MusicNextPlay->m_volume = command[REDSOUND_MUSIC_COMMAND_VOLUME];
        p_MusicNextPlay->m_mode = command[REDSOUND_MUSIC_COMMAND_MODE];
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd4a8
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicMasterVolume(int* command)
{
    RedVoiceDATA* voice;

    m_MasterMusicVolume = command[REDSOUND_MASTER_VOLUME_COMMAND_VOLUME] & REDSOUND_COMMAND_VALUE_MASK;
    if (m_MasterMusicVolume != 0) {
        m_MasterMusicVolume = m_MasterMusicVolume + 1;
        m_MasterMusicVolume = m_MasterMusicVolume * REDSOUND_MASTER_VOLUME_SCALE;
        m_MasterMusicVolume = m_MasterMusicVolume - 1;
    }
    voice = p_VoiceData;
    do {
        voice->m_updateFlags = voice->m_updateFlags | REDSOUND_VOICE_UPDATE_VOLUME;
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801bd51c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicVolume(int* command)
{
    if (command[REDSOUND_MUSIC_COMMAND_STOP_NEXT] == 1) {
        p_MusicNextPlay->m_musicId = REDSOUND_MUSIC_ID_NONE;
        m_MusicPhraseStop = 0;
    }
    SetMusicVolume(command[REDSOUND_MUSIC_COMMAND_ID], command[REDSOUND_MUSIC_COMMAND_VOLUME],
                   command[REDSOUND_MUSIC_COMMAND_FADE_TIME], command[REDSOUND_MUSIC_COMMAND_STOP_NEXT]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd578
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetMusicPhraseStop(int* command)
{
    m_MusicPhraseStop = command[REDSOUND_MUSIC_COMMAND_ID];
}

/*
 * --INFO--
 * PAL Address: 0x801bd584
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetSeBlockData(int* command)
{
    u32 index = (u32)command[REDSOUND_SE_BLOCK_DATA_COMMAND_BANK] & REDSOUND_SE_BLOCK_BANK_MASK;
    char* seBlockData;

    if (p_SeBlockData[index] != 0) {
        RedDelete(p_SeBlockData[index]);
        p_SeBlockData[index] = 0;
    }

    if (command[REDSOUND_SE_BLOCK_DATA_COMMAND_BUFFER] != 0) {
        seBlockData = (char*)command[REDSOUND_SE_BLOCK_DATA_COMMAND_BUFFER];
        if ((*seBlockData = REDSOUND_SE_BLOCK_SIGNATURE_0) && (seBlockData[1] = REDSOUND_SE_BLOCK_SIGNATURE_1) &&
            (seBlockData[2] = REDSOUND_SE_BLOCK_SIGNATURE_2) && (seBlockData[3] = REDSOUND_SE_BLOCK_SIGNATURE_3) &&
            (seBlockData[4] = REDSOUND_SE_BLOCK_SIGNATURE_4) && (seBlockData[5] = REDSOUND_SE_BLOCK_SIGNATURE_5) &&
            (seBlockData[6] = REDSOUND_SE_BLOCK_SIGNATURE_6)) {
            p_SeBlockData[index] = (RedSeBlockHEAD*)seBlockData;
        } else {
            RedDelete(seBlockData);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd6b0
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetSeSepData(int* command)
{
    c_RedEntry.SetSeSepData((RedSeSepHEAD*)command[REDSOUND_DATA_COMMAND_BUFFER]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd6e8
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ClearSeSepData(int* command)
{
    c_RedEntry.ClearSeSepData(command[REDSOUND_SE_COMMAND_ID]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd720
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ClearSeSepDataMG(int* command)
{
    c_RedEntry.ClearSeSepDataMG(command[REDSOUND_SE_MG_COMMAND_BANK], command[REDSOUND_SE_MG_COMMAND_SEP],
                                command[REDSOUND_SE_MG_COMMAND_GROUP], command[REDSOUND_SE_MG_COMMAND_KIND]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd764
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeStop(int* command)
{
    SeStopID(command[REDSOUND_SE_COMMAND_ID]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd794
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeStopMG(int* command)
{
    SeStopMG(command[REDSOUND_SE_MG_COMMAND_BANK], command[REDSOUND_SE_MG_COMMAND_SEP],
             command[REDSOUND_SE_MG_COMMAND_GROUP], command[REDSOUND_SE_MG_COMMAND_KIND]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd7d0
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeBlockPlay(int* command)
{
    m_SeSkipStep = command[REDSOUND_SE_BLOCK_COMMAND_PITCH];
    SeBlockPlay(command[REDSOUND_SE_COMMAND_ID], command[REDSOUND_SE_BLOCK_COMMAND_BANK],
                command[REDSOUND_SE_BLOCK_COMMAND_NO], command[REDSOUND_SE_BLOCK_COMMAND_PAN],
                command[REDSOUND_SE_BLOCK_COMMAND_VOLUME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd818
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeSepPlay(int* command)
{
    RedSeSepHEAD* seSepHead;

    seSepHead = c_RedEntry.SetSeSepData((RedSeSepHEAD*)command[REDSOUND_SE_SEP_COMMAND_DATA]);
    if (seSepHead != 0) {
        m_SeSkipStep = command[REDSOUND_SE_SEP_COMMAND_PITCH];
        int seID = command[REDSOUND_SE_COMMAND_ID];
        SeSepPlay(seID, seSepHead->m_seNo, command[REDSOUND_SE_SEP_COMMAND_PAN],
                  command[REDSOUND_SE_SEP_COMMAND_VOLUME]);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd884
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeSepPlaySequence(int* command)
{
    if (c_RedEntry.SearchSeSepSequence(command[REDSOUND_SE_SEP_COMMAND_ID]) >= 0) {
        m_SeSkipStep = command[REDSOUND_SE_SEP_COMMAND_PITCH];
        SeSepPlay(command[REDSOUND_SE_COMMAND_ID], command[REDSOUND_SE_SEP_COMMAND_ID],
                  command[REDSOUND_SE_SEP_COMMAND_PAN], command[REDSOUND_SE_SEP_COMMAND_VOLUME]);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd8e0
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeMasterVolume(int* command)
{
    RedVoiceDATA* voice;

    m_MasterSEVolume = command[REDSOUND_MASTER_VOLUME_COMMAND_VOLUME] & REDSOUND_COMMAND_VALUE_MASK;
    if (m_MasterSEVolume != 0) {
        m_MasterSEVolume = m_MasterSEVolume + 1;
        m_MasterSEVolume = m_MasterSEVolume * REDSOUND_MASTER_VOLUME_SCALE;
        m_MasterSEVolume = m_MasterSEVolume - 1;
    }
    voice = p_VoiceData;
    do {
        voice->m_updateFlags = voice->m_updateFlags | REDSOUND_VOICE_UPDATE_VOLUME;
        voice++;
    } while (voice < p_VoiceData + REDSOUND_VOICE_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801bd954
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeVolume(int* command)
{
    SetSeVolume(command[REDSOUND_SE_COMMAND_ID], command[REDSOUND_SE_COMMAND_VALUE],
                command[REDSOUND_SE_COMMAND_FADE_TIME], command[REDSOUND_SE_COMMAND_MODE]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd990
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SePan(int* command)
{
    SetSePan(command[REDSOUND_SE_COMMAND_ID], command[REDSOUND_SE_COMMAND_VALUE],
             command[REDSOUND_SE_COMMAND_FADE_TIME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd9c8
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SePitch(int* command)
{
    SetSePitch(command[REDSOUND_SE_COMMAND_ID], command[REDSOUND_SE_COMMAND_VALUE],
               command[REDSOUND_SE_COMMAND_FADE_TIME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bda00
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SePause(int* command)
{
    SePause(command[REDSOUND_SE_COMMAND_ID], command[REDSOUND_SE_COMMAND_PAUSE]);
}

/*
 * --INFO--
 * PAL Address: 0x801bda34
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _StreamStop(int* command)
{
	StreamStop(command[REDSOUND_STREAM_COMMAND_ID]);
}

/*
 * --INFO--
 * PAL Address: 0x801bda64
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _StreamPlay(int* command)
{
	StreamPlay(command[REDSOUND_STREAM_COMMAND_ID], (void*)command[REDSOUND_STREAM_COMMAND_DATA],
	           command[REDSOUND_STREAM_COMMAND_FILE_SIZE], command[REDSOUND_STREAM_COMMAND_PAN],
	           command[REDSOUND_STREAM_COMMAND_PLAY_VOLUME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdaa4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _StreamVolume(int* command)
{
	SetStreamVolume(command[REDSOUND_STREAM_COMMAND_ID], command[REDSOUND_STREAM_COMMAND_VOLUME],
	                command[REDSOUND_STREAM_COMMAND_FADE_TIME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdadc
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _StreamPause(int* command)
{
	StreamPause(command[REDSOUND_STREAM_COMMAND_ID], command[REDSOUND_STREAM_COMMAND_PAUSE]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdb10
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static RedExecCommand* _EntryExecCommand(RedExecCommandFunc func, int arg1, int arg2, int arg3, int arg4,
                                         int arg5, int arg6, int arg7)
{
    unsigned int interruptLevel;
    RedExecCommand* writePos;

    interruptLevel = OSDisableInterrupts();
    writePos = p_ExecCommandNow;
    writePos->m_func = func;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG0] = arg1;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG1] = arg2;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG2] = arg3;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG3] = arg4;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG4] = arg5;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG5] = arg6;
    writePos->m_args[REDSOUND_EXEC_COMMAND_ARG6] = arg7;
    writePos++;
    if (writePos == p_ExecCommand + REDSOUND_EXEC_COMMAND_COUNT) {
        writePos = p_ExecCommand;
    }
    p_ExecCommandNow = writePos;
    OSRestoreInterrupts(interruptLevel);
    return writePos;
}

/*
 * --INFO--
 * PAL Address: 0x801bdbd0
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ExecuteCommand()
{
	volatile RedExecCommand* readPos;
	volatile RedExecCommand* executePos;

	executePos = p_ExecCommandNow;
	readPos = p_ExecCommandOld;

	while (executePos != readPos) {
		if (readPos->m_func != 0) {
			readPos->m_func((int*)readPos->m_args);
		}
		readPos++;
		if (readPos == p_ExecCommand + REDSOUND_EXEC_COMMAND_COUNT) {
			readPos = p_ExecCommand;
		}
	}

	p_ExecCommandOld = (RedExecCommand*)readPos;
}

/*
 * --INFO--
 * PAL Address: 0x801bdc48
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int DeltaTimeSumup(unsigned char** buffer)
{
	unsigned int deltaTime = 0;

	if (buffer != 0) {
		deltaTime = **buffer & REDSOUND_DELTA_TIME_VALUE_MASK;
		while ((**buffer & REDSOUND_DELTA_TIME_CONTINUE_FLAG) != 0) {
			*buffer += 1;
			deltaTime <<= REDSOUND_DELTA_TIME_SHIFT;
			deltaTime |= **buffer & REDSOUND_DELTA_TIME_VALUE_MASK;
		}
		*buffer += 1;
	}

	return deltaTime;
}

/*
 * --INFO--
 * PAL Address: 0x801bdcb8
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int GetMyEntryID()
{
    m_SequencialID++;
    m_SequencialID &= REDSOUND_ENTRY_ID_MASK;
    if (m_SequencialID == 0) {
        m_SequencialID++;
    }
    return m_SequencialID;
}

struct RedSleepAlarm {
    OSAlarm m_alarm;
    OSThread* m_thread;
};

/*
 * --INFO--
 * PAL Address: 0x801bdcf0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MyAlarmHandler(OSAlarm* alarm, OSContext*)
{
    OSResumeThread(((RedSleepAlarm*)alarm)->m_thread);
}

/*
 * --INFO--
 * PAL Address: 0x801bdd1c
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedSleep(int microseconds)
{
    unsigned int interruptLevel;
    RedSleepAlarm alarm;

    if (microseconds < REDSOUND_CONTROL_TICK_PERIOD) {
        microseconds = REDSOUND_CONTROL_TICK_PERIOD;
    }
    interruptLevel = OSDisableInterrupts();
    alarm.m_thread = OSGetCurrentThread();
    OSCreateAlarm(&alarm.m_alarm);
    OSSetAlarm(&alarm.m_alarm,
               (microseconds * (OS_TIMER_CLOCK / REDSOUND_SLEEP_TIMER_DIVISOR)) >> REDSOUND_SLEEP_TIMER_SHIFT,
               _MyAlarmHandler);
    OSSuspendThread(alarm.m_thread);
    OSRestoreInterrupts(interruptLevel);
}

/*
 * --INFO--
 * PAL Address: 0x801bddbc
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MainThread(void*)
{
    RedSoundCONTROL* control;
    int startTick;
    int endTick;
    int masterTime;
    unsigned int elapsed;

    m_ThreadExecute = m_ThreadExecute | REDSOUND_THREAD_FLAG_MAIN;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_MainSemaphore);
        if (m_ThreadControl != 0) {
            startTick = OSGetTick();
            control = p_SoundControlBuffer;
            masterTime = m_RedMasterTime;
            elapsed = (unsigned int)(masterTime - m_MainThreadTime);
            if (control->m_activeTrackCount != 0) {
                control->m_elapsedTime += elapsed;
            }
            m_MainThreadTime = masterTime;
            if (4 < elapsed) {
                elapsed = 4;
            }
            MainControl(elapsed);
            StreamControl();
            _ExecuteCommand();
            if ((p_MusicNextPlay->m_musicId >= 0) && (control->m_musicId < 0)) {
                _MusicPlaySequence((int*)p_MusicNextPlay);
                p_MusicNextPlay->m_musicId = REDSOUND_MUSIC_ID_NONE;
                m_MusicPhraseStop = 0;
            }
            while (OSTryWaitSemaphore(&m_MainSemaphore) > 0) {
            }
            memmove(p_Tick->m_ticks + 1, p_Tick->m_ticks, REDSOUND_TICK_HISTORY_SHIFT_SIZE);
            endTick = OSGetTick();
            p_Tick->m_ticks[REDSOUND_TICK_HISTORY_LATEST] = endTick - startTick;
        }
    }
    m_ThreadExecute = m_ThreadExecute & ~REDSOUND_THREAD_FLAG_MAIN;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bdee8
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _WaveSettingThread(void* threadArg)
{
    m_ThreadExecute = m_ThreadExecute | REDSOUND_THREAD_FLAG_WAVE_SETTING;
    m_WaveSettingStatus = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_WaveSettingSemaphore);
        if (m_ThreadControl != 0) {
            RedWaveSettingState* waveSetting = (RedWaveSettingState*)threadArg;
            m_WaveSettingStatus = m_WaveSettingStatus + 1;
            c_RedEntry.SetWaveData(waveSetting->m_waveId, waveSetting->m_waveData, waveSetting->m_waveSize);
            *waveSetting->m_slot = 0;
            do {
            } while (OSTryWaitSemaphore(&m_WaveSettingSemaphore) > 0);
            m_WaveSettingStatus = 0;
        }
    }
    m_ThreadExecute = m_ThreadExecute & ~REDSOUND_THREAD_FLAG_WAVE_SETTING;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bdfac
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _DMACheckProcess()
{
    RedDmaRequest* dmaInfo;

    if (m_ReportPrint != 0) {
        OSReport(s_redDriverDmaCheckHeaderFmt, sRedDriverLogPrefix);
        fflush(__files + 1);

        OSReport(sRedDriverDmaStatusFmt, sRedDriverLogPrefix, m_DMAStatus,
                 OSGetSemaphoreCount(&m_DmaExecuteSemaphore), m_DMAExecute, m_DMAInThread);
        fflush(__files + 1);
    }

    dmaInfo = RedDriverMainDmaQueue();
    do {
        if ((dmaInfo->m_id != 0) && (m_ReportPrint != 0)) {
            OSReport(sRedDriverDmaEntryFmt, sRedDriverLogPrefix,
                     dmaInfo->m_id, dmaInfo->m_mainMemory, dmaInfo->m_aramMemory,
                     dmaInfo->m_size, dmaInfo->m_callback);
            fflush(__files + 1);
        }
        dmaInfo++;
    } while (dmaInfo < RedDriverStreamDmaQueueEnd());

    fflush(__files + 1);
}

/*
 * --INFO--
 * PAL Address: 0x801be0c4
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _DmaCallback(unsigned long)
{
    m_DMAStatus = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be0d0
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedDmaEntry(int flags, int direction, int mainMemory, int aramMemory, int sizeBytes, RedDmaCallback callback,
                void* callbackData)
{
    unsigned int interrupt;
    RedDmaRequest* queueBase;
    RedDmaRequest* volatile* queuePtr;
    unsigned int entryID;
    int chunkSize;
    int transferSize;
    RedDmaRequest* queueEntry;

    interrupt = OSDisableInterrupts();
    if ((flags & REDSOUND_DMA_FLAG_QUEUE_MASK) != 0) {
        queuePtr = &p_DmaControlNow[REDSOUND_DMA_MAIN_QUEUE_INDEX];
        queueBase = RedDriverMainDmaQueue();
    } else {
        queueBase = RedDriverStreamDmaQueue();
        queuePtr = &p_DmaControlNow[REDSOUND_DMA_STREAM_QUEUE_INDEX];
    }
    queueEntry = *queuePtr;
    entryID = GetMyEntryID();
    sizeBytes += REDSOUND_DMA_TRANSFER_ALIGN - 1;
    sizeBytes &= REDSOUND_DMA_TRANSFER_ALIGN_MASK;
    if ((m_DMAMode != 0) || ((flags & REDSOUND_DMA_FLAG_CHUNKED_TRANSFER) != 0)) {
        do {
            if (sizeBytes > REDSOUND_DMA_MAX_CHUNK_SIZE) {
                chunkSize = REDSOUND_DMA_MAX_CHUNK_SIZE;
            } else {
                chunkSize = sizeBytes;
            }
            queueEntry->m_id = entryID;
            transferSize = chunkSize;
            sizeBytes -= transferSize;
            queueEntry->m_direction = direction;
            queueEntry->m_mainMemory = mainMemory;
            mainMemory += transferSize;
            queueEntry->m_aramMemory = aramMemory;
            aramMemory += transferSize;
            queueEntry->m_size = transferSize;
            queueEntry->m_callbackData = callbackData;
            if (sizeBytes < 1) {
                queueEntry->m_callback = callback;
            } else {
                queueEntry->m_callback = 0;
            }
            queueEntry++;
            if (!(queueEntry < queueBase + REDSOUND_DMA_QUEUE_ENTRY_COUNT)) {
                queueEntry = queueBase;
            }
        } while (sizeBytes > 0);
        *queuePtr = queueEntry;
    } else {
        queueEntry->m_id = entryID;
        queueEntry->m_direction = direction;
        queueEntry->m_mainMemory = mainMemory;
        queueEntry->m_aramMemory = aramMemory;
        queueEntry->m_size = sizeBytes;
        queueEntry->m_callback = callback;
        queueEntry->m_callbackData = callbackData;
        queueEntry++;
        if (!(queueEntry < queueBase + REDSOUND_DMA_QUEUE_ENTRY_COUNT)) {
            queueEntry = queueBase;
        }
        *queuePtr = queueEntry;
    }
    OSSignalSemaphore(&m_DmaExecuteSemaphore);
    OSRestoreInterrupts(interrupt);
    return entryID;
}

/*
 * --INFO--
 * PAL Address: 0x801be234
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedDmaSearchID(int id)
{
    unsigned int interruptLevel;
    int found;
    RedDmaRequest* queueEntry;

    found = 0;
    interruptLevel = OSDisableInterrupts();
    if (id != 0) {
        queueEntry = RedDriverMainDmaQueue();
        do {
            if ((queueEntry->m_id != 0) && ((id == 0) || (queueEntry->m_id == id))) {
                found = 1;
                break;
            }
            queueEntry++;
        } while (queueEntry < RedDriverStreamDmaQueueEnd());
    }
    OSRestoreInterrupts(interruptLevel);
    return found;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedSetDMAMode(int mode)
{
    m_DMAMode = mode;
}

/*
 * --INFO--
 * PAL Address: 0x801be2dc
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _DmaExecute()
{
    unsigned int interrupt;
    int srcAddress;
    int dstAddress;
    RedDmaRequest* queueBase;
    RedDmaRequest* volatile* oldQueuePtr;
    RedDmaRequest* activeRequest;
    RedDmaRequest* queueEntry;

    while ((p_DmaControlNow[REDSOUND_DMA_MAIN_QUEUE_INDEX] != p_DmaControlOld[REDSOUND_DMA_MAIN_QUEUE_INDEX]) ||
           (p_DmaControlNow[REDSOUND_DMA_STREAM_QUEUE_INDEX] != p_DmaControlOld[REDSOUND_DMA_STREAM_QUEUE_INDEX])) {
        activeRequest = 0;
        m_DMAInThread = REDSOUND_DMA_THREAD_SELECT_QUEUE;
        if (p_DmaControlNow[REDSOUND_DMA_MAIN_QUEUE_INDEX] != p_DmaControlOld[REDSOUND_DMA_MAIN_QUEUE_INDEX]) {
            oldQueuePtr = &p_DmaControlOld[REDSOUND_DMA_MAIN_QUEUE_INDEX];
            queueBase = RedDriverMainDmaQueue();
        } else {
            oldQueuePtr = &p_DmaControlOld[REDSOUND_DMA_STREAM_QUEUE_INDEX];
            queueBase = RedDriverStreamDmaQueue();
        }
        queueEntry = *oldQueuePtr;
        m_DMAInThread = REDSOUND_DMA_THREAD_LOAD_ENTRY;
        if (queueEntry->m_id != 0) {
            m_DMAStatus = 1;
            if (queueEntry->m_direction == REDSOUND_DMA_DIRECTION_TO_ARAM) {
                DCFlushRange((void*)queueEntry->m_mainMemory, (u32)queueEntry->m_size);
                srcAddress = queueEntry->m_mainMemory;
                dstAddress = queueEntry->m_aramMemory;
            } else {
                DCInvalidateRange((void*)queueEntry->m_mainMemory, (u32)queueEntry->m_size);
                srcAddress = queueEntry->m_aramMemory;
                dstAddress = queueEntry->m_mainMemory;
            }
            m_DMAInThread = REDSOUND_DMA_THREAD_POST_REQUEST;
            ARQSetChunkSize((u32)queueEntry->m_size);
            ARQPostRequest(&m_DMARequest, REDSOUND_DMA_ARQ_OWNER_ID, (u32)queueEntry->m_direction, REDSOUND_DMA_ARQ_PRIORITY, (u32)srcAddress, (u32)dstAddress,
                           (u32)queueEntry->m_size, _DmaCallback);
            m_DMAInThread = REDSOUND_DMA_THREAD_WAIT_REQUEST;
            activeRequest = queueEntry;
        }
        queueEntry++;
        m_DMAInThread = REDSOUND_DMA_THREAD_ADVANCE_QUEUE;
        if (!(queueEntry < queueBase + REDSOUND_DMA_QUEUE_ENTRY_COUNT)) {
            queueEntry = queueBase;
        }
        *oldQueuePtr = queueEntry;
        m_DMAInThread = REDSOUND_DMA_THREAD_STORE_QUEUE;

        if (activeRequest == 0) {
            continue;
        }

        while (activeRequest != 0) {
            m_DMAInThread = REDSOUND_DMA_THREAD_POLL_STATUS;
            if (m_DMAStatus == 0) {
                m_DMAInThread = REDSOUND_DMA_THREAD_RUN_CALLBACK;
                if ((u32)activeRequest->m_callback != 0) {
                    interrupt = OSDisableInterrupts();
                    activeRequest->m_callback(activeRequest->m_callbackData);
                    OSRestoreInterrupts(interrupt);
                }
                m_DMAInThread = REDSOUND_DMA_THREAD_FINISH_ENTRY;
                if (activeRequest->m_direction == REDSOUND_DMA_DIRECTION_FROM_ARAM) {
                    DCFlushRange((void*)activeRequest->m_mainMemory, (u32)activeRequest->m_size);
                }
                activeRequest->m_id = 0;
                break;
            }
            RedSleep(REDSOUND_THREAD_YIELD_SLEEP_US);
        }
    }
    m_DMAInThread = REDSOUND_DMA_THREAD_IDLE;
}

/*
 * --INFO--
 * PAL Address: 0x801be4cc
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _DmaExecuteThread(void*)
{
    m_ThreadExecute |= REDSOUND_THREAD_FLAG_DMA;
    m_DMAExecute = 0;
    m_DMAInThread = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_DmaExecuteSemaphore);
        m_DMAExecute = 1;
        if (m_ThreadControl != 0) {
            _DmaExecute();
        }
        m_DMAExecute = 0;
    }
    m_ThreadExecute &= ~REDSOUND_THREAD_FLAG_DMA;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be550
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MusicSkipThread(void*)
{
    m_ThreadExecute |= REDSOUND_THREAD_FLAG_MUSIC_SKIP;
    m_MusicSkipComplete = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_MusicSkipSemaphore);
        if (m_ThreadControl != 0) {
            MusicSkipFunction();
        }
        while (OSTryWaitSemaphore(&m_MusicSkipSemaphore) > 0) {
        }
    }
    m_ThreadExecute &= ~REDSOUND_THREAD_FLAG_MUSIC_SKIP;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be5d0
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _RedAXCallback()
{
    m_RedMasterTime = m_RedMasterTime + 1;
    EnvelopeKeyExecute();
    OSSignalSemaphore(&m_MainSemaphore);
}

/*
 * --INFO--
 * PAL Address: 0x801be608
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRedDriver::CRedDriver()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801be60c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRedDriver::~CRedDriver()
{
}

/*
 * --INFO--
 * PAL Address: 0x801be654
 * PAL Size: 1316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::Init()
{
    RedTrackDATA* seTrackArena;
    int nextIndex;
    int index;
    int fullVolume;
    int noMusicId;

    m_ThreadExecute = 0;
    m_ThreadControl = 1;
    m_ReportPrint = 1;
    m_SoundMode = 0;
    GetSoundMode();
    if (m_SoundPlayMode == 2) {
        AXSetMode(2);
    } else {
        AXSetMode(0);
    }
    p_Tick = (RedTickHistory*)RedNew(REDSOUND_TICK_HISTORY_SIZE);
    memset(p_Tick, 0, REDSOUND_TICK_HISTORY_SIZE);
    AXSetCompressor(0);
    m_MusicKeySignature = 0;
    m_SoundMasterControl = 0;
    m_MusicSkipLine = 0;
    m_MusicFastSpeed = 0;
    m_DMAStatus = 0;
    m_CrossTime = 0;
    m_MasterSEVolume = REDSOUND_MASTER_VOLUME_FULL;
    m_MasterMusicVolume = REDSOUND_MASTER_VOLUME_FULL;
    index = 0;
    do {
        nextIndex = index + 1;
        p_SeBlockData[index] = 0;
        index = nextIndex;
    } while (nextIndex < REDSOUND_SE_BLOCK_BANK_COUNT);
    p_ZeroData = (u8*)RedNew(REDSOUND_ZERO_BUFFER_SIZE);
    memset(p_ZeroData, 0, REDSOUND_ZERO_BUFFER_SIZE);
    p_MusicReplayPoint = (int*)RedNew(REDSOUND_MUSIC_REPLAY_POINT_SIZE);
    memset(p_MusicReplayPoint, 0, REDSOUND_MUSIC_REPLAY_POINT_SIZE);
    p_MusicTempoControl = (RedControlRamp*)RedNew(REDSOUND_CONTROL_RAMP_SIZE);
    memset(p_MusicTempoControl, 0, REDSOUND_CONTROL_RAMP_SIZE);
    p_MusicPitchControl = (RedControlRamp*)RedNew(REDSOUND_CONTROL_RAMP_SIZE);
    memset(p_MusicPitchControl, 0, REDSOUND_CONTROL_RAMP_SIZE);
    p_ExecCommand = (RedExecCommand*)RedNew(REDSOUND_EXEC_COMMAND_BUFFER_SIZE);
    p_ExecCommandNow = p_ExecCommand;
    p_ExecCommandOld = p_ExecCommand;
    memset(p_ExecCommand, 0, REDSOUND_EXEC_COMMAND_BUFFER_SIZE);
    p_SoundControlBuffer = (RedSoundCONTROL*)RedNew(REDSOUND_SOUND_CONTROL_ALLOC_SIZE);
    p_SoundControl = p_SoundControlBuffer;
    memset(p_SoundControlBuffer, 0, REDSOUND_SOUND_CONTROL_ALLOC_SIZE);
    fullVolume = REDSOUND_MASTER_VOLUME_FULL_FIXED;
    noMusicId = REDSOUND_MUSIC_ID_NONE;
    p_SoundControl[REDSOUND_CONTROL_SE].m_volume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_volume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_volume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_volume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_SE].m_masterVolume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_masterVolume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_masterVolume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolume = fullVolume;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId = noMusicId;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId = noMusicId;
    p_SoundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId = noMusicId;
    p_KeyOnData = (RedKeyOnDATA*)RedNew(REDSOUND_KEY_ON_BUFFER_SIZE);
    memset(p_KeyOnData, 0, REDSOUND_KEY_ON_BUFFER_SIZE);
    p_VoiceData = (RedVoiceDATA*)RedNew(REDSOUND_VOICE_BUFFER_SIZE);
    memset(p_VoiceData, 0, REDSOUND_VOICE_BUFFER_SIZE);
    index = 0;
    do {
        nextIndex = index % REDSOUND_SE_VOICE_BASE_INDEX;
        p_VoiceData[index].m_voiceIndex = nextIndex;
        index = index + 1;
    } while (index < REDSOUND_VOICE_COUNT);
    p_EditorVoice[REDSOUND_EDITOR_VOICE_RIGHT] = 0;
    p_EditorVoice[REDSOUND_EDITOR_VOICE_LEFT] = 0;
    seTrackArena = (RedTrackDATA*)RedNew(REDSOUND_SE_TRACK_ARENA_SIZE);
    p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks = seTrackArena;
    memset(seTrackArena, 0, REDSOUND_SE_TRACK_ARENA_SIZE);
    nextIndex = 0;
    do {
        seTrackArena[nextIndex].m_trackNo = (char)(nextIndex + REDSOUND_SE_VOICE_BASE_INDEX);
        nextIndex = nextIndex + 1;
    } while (nextIndex < REDSOUND_SE_TRACK_COUNT);
    p_EditorTrack = (RedTrackDATA*)RedNew(REDSOUND_TRACK_SIZE);
    memset(p_EditorTrack, 0, REDSOUND_TRACK_SIZE);
    p_ReverbDepth = (RedReverbDepth*)RedNew(REDSOUND_REVERB_DEPTH_BUFFER_SIZE);
    memset(p_ReverbDepth, 0, REDSOUND_REVERB_DEPTH_BUFFER_SIZE);
    m_Mute[REDSOUND_MUTE_HIGH_WORD] = 0;
    m_Mute[REDSOUND_MUTE_LOW_WORD] = 0;
    p_MusicNextPlay = (RedMusicPlayCommand*)RedNew(REDSOUND_MUSIC_NEXT_PLAY_BUFFER_SIZE);
    p_MusicNextPlay->m_musicId = REDSOUND_MUSIC_ID_NONE;
    m_MusicPhraseStop = 0;
    p_Stream = (RedStreamDATA*)RedNew(REDSOUND_STREAM_BUFFER_SIZE);
    memset(p_Stream, 0, REDSOUND_STREAM_BUFFER_SIZE);
    m_DMAMode = 0;
    memset(m_DmaControl, 0, REDSOUND_DMA_CONTROL_SIZE);
    p_DmaControlNow[REDSOUND_DMA_MAIN_QUEUE_INDEX] = RedDriverMainDmaQueue();
    p_DmaControlOld[REDSOUND_DMA_MAIN_QUEUE_INDEX] = RedDriverMainDmaQueue();
    p_DmaControlNow[REDSOUND_DMA_STREAM_QUEUE_INDEX] = RedDriverStreamDmaQueue();
    p_DmaControlOld[REDSOUND_DMA_STREAM_QUEUE_INDEX] = RedDriverStreamDmaQueue();
    m_RedMasterTime = 0;
    AXRegisterCallback(_RedAXCallback);
    AXFXSetHooks(ReverbAreaAlloc, ReverbAreaFree);
    InitReverb();
    OSInitSemaphore(&m_DmaExecuteSemaphore, 0);
    p_DmaExecuteThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&m_DmaExecuteThread, (void* (*)(void*))_DmaExecuteThread, 0,
                   p_DmaExecuteThreadStack + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_DMA_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&m_DmaExecuteThread);
    OSInitSemaphore(&m_WaveSettingSemaphore, 0);
    p_WaveSettingThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&m_WaveSettingThread, (void* (*)(void*))_WaveSettingThread, &m_WaveSettingData,
                   p_WaveSettingThreadStack + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_WORKER_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&m_WaveSettingThread);
    OSInitSemaphore(&m_MusicSkipSemaphore, 0);
    p_MusicSkipThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&m_MusicSkipThread, (void* (*)(void*))_MusicSkipThread, 0,
                   p_MusicSkipThreadStack + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_WORKER_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&m_MusicSkipThread);
    OSInitSemaphore(&m_MainSemaphore, 0);
    m_MainThreadTime = 0;
    p_MainThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&RedDriverMainThread(), (void* (*)(void*))_MainThread, 0,
                   p_MainThreadStack + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_WORKER_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&RedDriverMainThread());
}

/*
 * --INFO--
 * PAL Address: 0x801beb78
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::End()
{
    RedDriverSyncState& sync = RedDriverSync();

    AXRegisterCallback(0);
    m_ThreadControl = 0;
    OSSignalSemaphore(&sync.m_mainSemaphore);
    OSSignalSemaphore(&sync.m_waveSemaphore);
    OSSignalSemaphore(&sync.m_dmaSemaphore);
    OSSignalSemaphore(&sync.m_musicSemaphore);
    while (m_ThreadExecute != 0) {
        RedSleep(REDSOUND_THREAD_YIELD_SLEEP_US);
    }
    AXRegisterAuxACallback(0, 0);
    AXRegisterAuxBCallback(0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bec04
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetProgramTime()
{
    int sum = 0;
    int* p = p_Tick->m_ticks;

    do {
        sum += *p;
        p++;
    } while (p < p_Tick->m_ticks + REDSOUND_TICK_HISTORY_COUNT);
    return sum;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetMasterTime()
{
    return m_RedMasterTime;
}

/*
 * --INFO--
 * PAL Address: 0x801bec48
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetSoundMode(int soundMode)
{
    _EntryExecCommand(_SetSoundMode, soundMode, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bec90
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetSoundMode()
{
    int soundMode = __OSReadROM();

    if (soundMode == 0) {
        m_SoundPlayMode = 1;
    } else {
        m_SoundPlayMode = m_SoundMode;
    }
    return m_SoundPlayMode;
}

/*
 * --INFO--
 * PAL Address: 0x801becd8
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SetMusicData(void* musicData)
{
    int result;
    RedMusicHEAD localHeader;
    RedMusicHEAD* const header = (RedMusicHEAD*)musicData;
    RedMusicHEAD* copiedHeader;
    int headerSize;

    result = REDSOUND_MUSIC_ID_NONE;
    if (((header->m_signature[0] == REDSOUND_MUSIC_SIGNATURE_0) &&
         (header->m_signature[1] == REDSOUND_MUSIC_SIGNATURE_1)) &&
        (header->m_signature[2] == REDSOUND_MUSIC_SIGNATURE_2)) {
        memcpy(&localHeader, header, REDSOUND_MUSIC_HEADER_SIZE);
        headerSize = localHeader.m_size;
        copiedHeader = (RedMusicHEAD*)RedNew(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, header, headerSize);
            result = localHeader.m_musicNo;
            _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        }
    } else if (m_ReportPrint != 0) {
        OSReport(sRedDriverMusicHeaderErrorFmt, sRedDriverLogPrefix, sRedDriverLogWarnColor, sRedDriverLogReset);
        fflush(__files + 1);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bedec
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReentryMusicData(int musicID)
{
    unsigned int interrupt;

    interrupt = OSDisableInterrupts();
    musicID   = c_RedEntry.ReentryMusicData(musicID);
    OSRestoreInterrupts(interrupt);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801bee48
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicStop(int musicID)
{
    _EntryExecCommand(_MusicStop, musicID, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801BEE90
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::MusicPlay(int musicID, int volume, int mode)
{
    _EntryExecCommand(_MusicPlaySequence, musicID, volume, mode, 0, 0, 0, 0);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801beee8
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::MusicCrossPlay(int musicID, int volume, int mode)
{
    _EntryExecCommand(_MusicCrossPlaySequence, musicID, volume, mode, 0, 0, 0, 0);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801bef40
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::MusicNextPlay(int musicID, int volume, int mode)
{
    _EntryExecCommand(_MusicNextPlaySequence, musicID, volume, mode, 0, 0, 0, 0);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801bef98
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicMasterVolume(int volume)
{
    _EntryExecCommand(_MusicMasterVolume, volume, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801befe0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicFadeOut(int musicID, int fadeTime)
{
    _EntryExecCommand(_MusicVolume, musicID, 0, fadeTime, 1, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf02c
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicVolume(int musicID, int volume, int frameCount)
{
    _EntryExecCommand(_MusicVolume, musicID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf07c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetMusicPhraseStop(int stop)
{
    _EntryExecCommand(_SetMusicPhraseStop, stop, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::CheckMusicEntry(int musicID)
{
    return c_RedEntry.SearchMusicSequence(musicID);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetMusicFastSpeed(int speed)
{
    m_MusicFastSpeed = speed;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::CheckMusicPhraseStop()
{
    return m_MusicPhraseStop;
}

/*
 * --INFO--
 * PAL Address: 0x801bf0c4
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CRedDriver::SetSeBlockData(int blockIndex, void* seBlockData)
{
    void* copiedBuffer;
    int copySize;

    if (seBlockData != 0) {
        copySize = reinterpret_cast<RedSeBlockHEAD*>(seBlockData)->m_size;
        if (copySize > 0) {
            copiedBuffer = (void*)RedNew(copySize);
            if (copiedBuffer != 0) {
                memcpy(copiedBuffer, seBlockData, copySize);
            }
        } else {
            copiedBuffer = 0;
        }
    } else {
        copiedBuffer = 0;
    }
    _EntryExecCommand(_SetSeBlockData, blockIndex, (int)copiedBuffer, 0, 0, 0, 0, 0);
    return copiedBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x801bf16c
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SetSeSepData(void* seSepData)
{
    int result = REDSOUND_SESEP_ID_NONE;
    RedSeSepHEAD* const header = (RedSeSepHEAD*)seSepData;
    RedSeSepHEAD* copiedHeader;
    int headerSize;

    if (((((header->m_signature[0] == REDSOUND_SESEP_SIGNATURE_0) &&
           (header->m_signature[1] == REDSOUND_SESEP_SIGNATURE_1)) &&
          (header->m_signature[2] == REDSOUND_SESEP_SIGNATURE_2)) &&
         ((header->m_signature[3] == REDSOUND_SESEP_SIGNATURE_3 &&
           (header->m_signature[4] == REDSOUND_SESEP_SIGNATURE_4))))) {
        headerSize = header->m_sizeAndFlags & REDSOUND_SESEP_SIZE_MASK;
        copiedHeader = (RedSeSepHEAD*)RedNew(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, header, headerSize);
            result = copiedHeader->m_seNo;
            _EntryExecCommand(_SetSeSepData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        }
    } else if (m_ReportPrint != 0) {
        OSReport(sRedDriverSeSepHeaderErrorFmt, sRedDriverLogPrefix,
                 sRedDriverLogWarnColor, sRedDriverLogReset);
        fflush(__files + 1);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bf28c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearSeSepData(int id)
{
    _EntryExecCommand(_ClearSeSepData, id, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf2d4
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearSeSepDataMG(int id1, int id2, int id3, int id4)
{
    _EntryExecCommand(_ClearSeSepDataMG, id1, id2, id3, id4, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf328
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReentrySeSepData(int id)
{
    unsigned int interrupts;

    interrupts = OSDisableInterrupts();
    id         = c_RedEntry.ReentrySeSepData(id);
    OSRestoreInterrupts(interrupts);
    return id;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::CheckSeSepEntry(int id)
{
    return c_RedEntry.SearchSeSepSequence(id);
}

/*
 * --INFO--
 * PAL Address: 0x801bf384
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SePlayState(int seID)
{
    RedExecCommand* commandNow;
    unsigned int interruptLevel;
    RedTrackDATA* seInfo;
    RedTrackDATA** seInfoBase;
    int result;
    RedExecCommand* command;

    interruptLevel = OSDisableInterrupts();
    result = 0;
    seInfoBase = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
    seInfo = *seInfoBase;
    do {
        if (((u32)seInfo->m_command != 0) && ((seID == REDSOUND_SE_ID_ALL || (seInfo->m_seId == seID)))) {
            result = (int)seInfo;
            break;
        }
        seInfo++;
    } while (seInfo < *seInfoBase + REDSOUND_SE_TRACK_COUNT);
    if (result == 0) {
        commandNow = p_ExecCommandNow;
        command = p_ExecCommandOld;
        while (commandNow != command) {
            if (((command->m_func != 0) &&
                (((command->m_func == _SeBlockPlay) ||
                  (command->m_func == _SeSepPlay)) ||
                 (command->m_func == _SeSepPlaySequence))) &&
                ((seID == REDSOUND_SE_ID_ALL || (seID == command->m_args[REDSOUND_EXEC_COMMAND_ARG0])))) {
                result = 1;
                break;
            }
            command++;
            if (command == p_ExecCommand + REDSOUND_EXEC_COMMAND_COUNT) {
                command = p_ExecCommand;
            }
        }
    }
    OSRestoreInterrupts(interruptLevel);
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bf4a4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeStop(int id)
{
    _EntryExecCommand(_SeStop, id, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf4ec
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeStopMG(int id1, int id2, int id3, int id4)
{
    _EntryExecCommand(_SeStopMG, id1, id2, id3, id4, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf540
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SePlay(int bank, int sep, int autoID, int pan, int volume, int pitch)
{
	if (bank == REDSOUND_SE_BANK_SESEP) {
		if (sep >= 0) {
			_EntryExecCommand(_SeSepPlaySequence, autoID, sep, pan, volume, pitch, 0, 0);
		}
	} else if ((bank >= 0) && (bank < REDSOUND_SE_BLOCK_BANK_COUNT) && (sep >= 0) &&
	           (sep < REDSOUND_SE_BLOCK_SEQUENCE_COUNT)) {
		_EntryExecCommand(_SeBlockPlay, autoID, bank, sep, pan, volume, pitch, 0);
	}
    return autoID;
}

/*
 * --INFO--
 * PAL Address: 0x801bf604
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeMasterVolume(int volume)
{
    _EntryExecCommand(_SeMasterVolume, volume, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf64c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeFadeOut(int seID, int fadeTime)
{
    _EntryExecCommand(_SeVolume, seID, 0, fadeTime, 1, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf698
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeVolume(int seID, int volume, int frameCount)
{
    _EntryExecCommand(_SeVolume, seID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf6e8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePan(int seID, int pan, int frameCount)
{
    _EntryExecCommand(_SePan, seID, pan, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf738
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePitch(int seID, int pitch, int frameCount)
{
    _EntryExecCommand(_SePitch, seID, pitch, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf788
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePause(int seID, int pause)
{
    _EntryExecCommand(_SePause, seID, pause, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf7d4
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetSeVolume(int seID, int mode)
{
    RedTrackDATA* track;

    track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
    while (1) {
        if (((u32)track->m_command != 0) && ((seID == REDSOUND_SE_ID_ALL) || (seID == track->m_seId))) {
            if ((u32)track->m_command != 0) {
                if (mode == 1) {
                    return track->m_mixVolumeDelta;
                }
                return track->m_mixVolume >> REDSOUND_FIXED_SHIFT;
            }
        }
        track++;
        if (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT) {
            continue;
        }
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bf854
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReportSeLoop(int seID)
{
    RedTrackDATA* track;

    track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
    while (1) {
        if ((track->m_command != 0) &&
            (((seID == REDSOUND_SE_ID_ALL) || (seID == track->m_seId)) &&
             ((track->m_loopReport & REDSOUND_TRACK_LOOP_REPORT_ACTIVE) != 0))) {
            return 1;
        }
        track++;
        if (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT) {
            continue;
        }
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bf8c0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::DisplaySePlayInfo()
{
	c_RedEntry.DisplaySePlayInfo();
}

/*
 * --INFO--
 * PAL Address: 0x801bf8e8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::StreamPlayState(int streamID)
{
	RedExecCommand* commandNow;
	unsigned int interrupts;
	RedStreamDATA* streamData;
	int result;
	RedExecCommand* command;

	interrupts = OSDisableInterrupts();
	result = 0;
	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != 0) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamData->m_streamId == streamID))) {
			result = 1;
			break;
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);

	if (result == 0) {
		commandNow = p_ExecCommandNow;
		command = p_ExecCommandOld;
		while (commandNow != command) {
			if ((command->m_func != 0) && (command->m_func == _StreamPlay) &&
			    ((streamID == REDSOUND_STREAM_ID_ALL) ||
			     (streamID == command->m_args[REDSOUND_EXEC_COMMAND_ARG0]))) {
				result = 1;
				break;
			}
			command++;
			if (command == p_ExecCommand + REDSOUND_EXEC_COMMAND_COUNT) {
				command = p_ExecCommand;
			}
		}
	}
	OSRestoreInterrupts(interrupts);
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bf9d8
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetStreamPlayPoint(int streamID, int* outPoint1, int* outPoint2)
{
	RedStreamDATA* streamData;
	int found;

	found = 0;
	if (outPoint1 != 0) {
		*outPoint1 = 0;
	}
	if (outPoint2 != 0) {
		*outPoint2 = 0;
	}
	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != 0) && (streamData->m_streamId == streamID)) {
			if (outPoint1 != 0) {
				*outPoint1 = streamData->m_fileCursor;
			}
			if (outPoint2 != 0) {
				*outPoint2 = streamData->m_readOffset;
			}
			found = 1;
			break;
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
	return found;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedStreamDATA* CRedDriver::GetStreamPlayBlock(int streamID)
{
	RedStreamDATA* streamData = p_Stream;

	do {
		if ((streamData->m_streamId != 0) && (streamData->m_streamId == streamID)) {
			return streamData;
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bfa74
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamStop(int streamID)
{
    _EntryExecCommand(_StreamStop, streamID, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfabc
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::StreamPlay(int streamID, void* streamData, int fileSize, int pan, int volume)
{
	_EntryExecCommand(_StreamPlay, streamID, (int)streamData, fileSize, pan, volume, 0, 0);
	return streamID;
}

/*
 * --INFO--
 * PAL Address: 0x801bfb1c
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamVolume(int streamID, int volume, int frameCount)
{
    _EntryExecCommand(_StreamVolume, streamID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfb6c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamPause(int streamID, int pause)
{
    _EntryExecCommand(_StreamPause, streamID, pause, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfbb8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearWaveData(int waveID)
{
    c_RedEntry.ClearWaveData(waveID);
}

/*
 * --INFO--
 * PAL Address: 0x801bfbe8
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearWaveDataM(int waveNo0, int waveNo1, int waveNo2, int waveNo3)
{
    c_RedEntry.ClearWaveDataM(waveNo0, waveNo1, waveNo2, waveNo3);
}

/*
 * --INFO--
 * PAL Address: 0x801bfc30
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearWaveBank(int waveBank)
{
    c_RedEntry.ClearWaveBank(waveBank);
}

/*
 * --INFO--
 * PAL Address: 0x801bfc60
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWaveData(int slot, int waveID, void* waveData, int waveSize)
{
    while (true) {
        if (m_WaveSettingStatus == 0) {
            break;
        }

        RedSleep(REDSOUND_THREAD_YIELD_SLEEP_US);
    }

    m_WaveSettingData.m_slot = reinterpret_cast<int*>(slot);
    m_WaveSettingData.m_waveId = waveID;
    m_WaveSettingData.m_waveData = waveData;

    if (waveSize == REDSOUND_WAVE_SIZE_AUTO) {
        RedWaveHeadWD* const waveHeader = (RedWaveHeadWD*)waveData;

        if ((waveHeader->m_signature[0] == REDSOUND_WAVE_SIGNATURE_MAGIC0) &&
            (waveHeader->m_signature[1] == REDSOUND_WAVE_SIGNATURE_MAGIC1)) {
            int dataSize = waveHeader->m_tableCount * REDSOUND_WAVE_TABLE_ENTRY_SIZE;
            dataSize = (dataSize += REDSOUND_WAVE_SETTING_TABLE_ALIGN - 1) & REDSOUND_WAVE_SETTING_TABLE_ALIGN_MASK;
            dataSize += waveHeader->m_toneCount * REDSOUND_WAVE_TONE_ENTRY_SIZE;
            dataSize = waveHeader->m_waveSize + dataSize;
            dataSize += REDSOUND_WAVE_HEADER_COPY_BASE_SIZE;
            m_WaveSettingData.m_waveSize = dataSize;
        } else {
            m_WaveSettingData.m_waveSize = 0;
        }
    } else {
        m_WaveSettingData.m_waveSize = waveSize;
    }
    OSSignalSemaphore(&m_WaveSettingSemaphore);
}

/*
 * --INFO--
 * PAL Address: 0x801bfd74
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReentryWaveData(int id)
{
    unsigned int interrupts;

    interrupts = OSDisableInterrupts();
    id         = c_RedEntry.ReentryWaveData(id);
    OSRestoreInterrupts(interrupts);
    return id;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedWaveHeadWD* CRedDriver::GetWaveInfo(int waveID)
{
    return c_RedEntry.SearchWaveBase(waveID);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::CheckWaveEntry(int waveID)
{
    return c_RedEntry.SearchWaveSequence(waveID);
}

/*
 * --INFO--
 * PAL Address: 0x801bfdd0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::DisplayWaveInfo()
{
    c_RedEntry.DisplayWaveInfo();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::DisplayMMemoryInfo()
{
    c_RedEntry.DisplayMMemoryInfo();
}

/*
 * --INFO--
 * PAL Address: 0x801BFDF8
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetReverb(int bank, int kind)
{
    ::SetReverb(bank, t_ReverbModeData[kind].m_kind, t_ReverbModeData[kind].m_params);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedReverbSize* CRedDriver::GetReverbInfo()
{
    return ::GetReverbInfo();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedReverbDepth* CRedDriver::GetReverbDepth()
{
    return p_ReverbDepth;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedReverbModeData* CRedDriver::GetReverbModeTable(int mode)
{
    return t_ReverbModeData + mode;
}

/*
 * --INFO--
 * PAL Address: 0x801bfe54
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetReverbDepth(int bank, int mode, int depth)
{
    _EntryExecCommand(_SetReverbDepth, bank, mode, depth, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfea4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::TestProcess(int processType)
{
    switch (processType) {
    case 1:
        _DMACheckProcess();
        break;
    }
}
