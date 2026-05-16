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
    REDSOUND_WAVE_SETTING_SLOT_OFFSET = (unsigned int)&(((RedWaveSettingState*)0)->m_slot),
    REDSOUND_WAVE_SETTING_WAVE_ID_OFFSET = (unsigned int)&(((RedWaveSettingState*)0)->m_waveId),
    REDSOUND_WAVE_SETTING_WAVE_DATA_OFFSET = (unsigned int)&(((RedWaveSettingState*)0)->m_waveData),
    REDSOUND_WAVE_SETTING_WAVE_SIZE_OFFSET = (unsigned int)&(((RedWaveSettingState*)0)->m_waveSize),
    REDSOUND_WAVE_SETTING_SIZE = sizeof(RedWaveSettingState),
};

enum RedDriverSyncLayoutSize {
    REDSOUND_DRIVER_SYNC_THREAD_SIZE = sizeof(OSThread),
    REDSOUND_DRIVER_SYNC_SEMAPHORE_SIZE = sizeof(OSSemaphore),
    REDSOUND_DRIVER_SYNC_WAVE_DATA_SIZE = sizeof(RedWaveSettingState),
    REDSOUND_DRIVER_SYNC_DMA_REQUEST_SIZE = sizeof(ARQRequest),
    REDSOUND_DRIVER_SYNC_THREAD_ALIGN_PAD_SIZE = sizeof(u32),
};

struct RedDriverSyncState {
    RedDmaRequest m_dmaQueue[REDSOUND_DMA_QUEUE_ENTRY_COUNT];
    RedDmaRequest m_streamDmaQueue[REDSOUND_DMA_QUEUE_ENTRY_COUNT];
    OSThread m_mainThread;
    OSSemaphore m_mainSemaphore;
    u8 m_mainThreadAlignPadding[REDSOUND_DRIVER_SYNC_THREAD_ALIGN_PAD_SIZE];
    OSThread m_waveThread;
    OSSemaphore m_waveSemaphore;
    RedWaveSettingState m_waveSettingData;
    u8 m_waveThreadAlignPadding[REDSOUND_DRIVER_SYNC_THREAD_ALIGN_PAD_SIZE];
    OSThread m_dmaThread;
    OSSemaphore m_dmaSemaphore;
    ARQRequest m_dmaRequest;
    u8 m_dmaThreadAlignPadding[REDSOUND_DRIVER_SYNC_THREAD_ALIGN_PAD_SIZE];
    OSThread m_musicThread;
    OSSemaphore m_musicSemaphore;
};

enum RedDriverSyncLayoutOffset {
    REDSOUND_DRIVER_SYNC_DMA_QUEUE_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_dmaQueue),
    REDSOUND_DRIVER_SYNC_STREAM_DMA_QUEUE_OFFSET =
        (unsigned int)&(((RedDriverSyncState*)0)->m_streamDmaQueue),
    REDSOUND_DRIVER_SYNC_MAIN_THREAD_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_mainThread),
    REDSOUND_DRIVER_SYNC_MAIN_SEMAPHORE_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_mainSemaphore),
    REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET =
        (unsigned int)&(((RedDriverSyncState*)0)->m_mainThreadAlignPadding),
    REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_waveThread),
    REDSOUND_DRIVER_SYNC_WAVE_SEMAPHORE_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_waveSemaphore),
    REDSOUND_DRIVER_SYNC_WAVE_DATA_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_waveSettingData),
    REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET =
        (unsigned int)&(((RedDriverSyncState*)0)->m_waveThreadAlignPadding),
    REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_dmaThread),
    REDSOUND_DRIVER_SYNC_DMA_SEMAPHORE_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_dmaSemaphore),
    REDSOUND_DRIVER_SYNC_DMA_REQUEST_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_dmaRequest),
    REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET =
        (unsigned int)&(((RedDriverSyncState*)0)->m_dmaThreadAlignPadding),
    REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_musicThread),
    REDSOUND_DRIVER_SYNC_MUSIC_SEMAPHORE_OFFSET = (unsigned int)&(((RedDriverSyncState*)0)->m_musicSemaphore),
    REDSOUND_DRIVER_SYNC_SIZE = sizeof(RedDriverSyncState),
    REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET = REDSOUND_DRIVER_SYNC_SIZE,
    REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET =
        REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET + REDSOUND_SE_BLOCK_BANK_COUNT * sizeof(RedSeBlockHEAD*),
    REDSOUND_DRIVER_BSS_ENTRY_WORK_WORD_COUNT = 3,
    REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE = REDSOUND_DRIVER_BSS_ENTRY_WORK_WORD_COUNT * sizeof(int),
    REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET =
        REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET + REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE,
    REDSOUND_DRIVER_BSS_ENTRY_OFFSET = REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET + REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE,
    REDSOUND_DRIVER_BSS_SIZE = REDSOUND_DRIVER_BSS_ENTRY_OFFSET + sizeof(CRedEntry),
};

enum RedDriverGlobalObjectSize {
    REDSOUND_SE_BLOCK_DATA_TABLE_SIZE = REDSOUND_SE_BLOCK_BANK_COUNT * sizeof(RedSeBlockHEAD*),
    REDSOUND_RED_MEMORY_SIZE = sizeof(CRedMemory),
    REDSOUND_RED_ENTRY_SIZE = sizeof(CRedEntry),
};

struct RedExecCommand;
struct RedMusicPlayCommand;
struct RedTickHistory;

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

enum RedDriverSmallDataLayout {
    REDSOUND_DRIVER_SBSS_MASTER_TIME_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_redMasterTime),
    REDSOUND_DRIVER_SBSS_SEQUENCIAL_ID_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_sequencialID),
    REDSOUND_DRIVER_SBSS_THREAD_CONTROL_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_threadControl),
    REDSOUND_DRIVER_SBSS_THREAD_EXECUTE_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_threadExecute),
    REDSOUND_DRIVER_SBSS_SOUND_MODE_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_soundMode),
    REDSOUND_DRIVER_SBSS_TICK_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_tick),
    REDSOUND_DRIVER_SBSS_ZERO_DATA_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_zeroData),
    REDSOUND_DRIVER_SBSS_EXEC_COMMAND_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_execCommand),
    REDSOUND_DRIVER_SBSS_EXEC_COMMAND_NOW_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_execCommandNow),
    REDSOUND_DRIVER_SBSS_EXEC_COMMAND_OLD_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_execCommandOld),
    REDSOUND_DRIVER_SBSS_DMA_NOW_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_dmaControlNow),
    REDSOUND_DRIVER_SBSS_DMA_OLD_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_dmaControlOld),
    REDSOUND_DRIVER_SBSS_SOUND_CONTROL_BUFFER_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_soundControlBuffer),
    REDSOUND_DRIVER_SBSS_SOUND_CONTROL_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_soundControl),
    REDSOUND_DRIVER_SBSS_KEY_ON_ENTRY_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_keyOnEntry),
    REDSOUND_DRIVER_SBSS_KEY_ON_DATA_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_keyOnData),
    REDSOUND_DRIVER_SBSS_SOUND_PLAY_MODE_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_soundPlayMode),
    REDSOUND_DRIVER_SBSS_SOUND_MASTER_CONTROL_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_soundMasterControl),
    REDSOUND_DRIVER_SBSS_REPORT_PRINT_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_reportPrint),
    REDSOUND_DRIVER_SBSS_MUSIC_FAST_SPEED_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicFastSpeed),
    REDSOUND_DRIVER_SBSS_MUSIC_SKIP_LINE_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicSkipLine),
    REDSOUND_DRIVER_SBSS_MUSIC_KEY_SIGNATURE_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicKeySignature),
    REDSOUND_DRIVER_SBSS_MUSIC_REPLAY_POINT_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicReplayPoint),
    REDSOUND_DRIVER_SBSS_MUSIC_TEMPO_CONTROL_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicTempoControl),
    REDSOUND_DRIVER_SBSS_MUSIC_PITCH_CONTROL_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicPitchControl),
    REDSOUND_DRIVER_SBSS_MUSIC_PHRASE_STOP_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicPhraseStop),
    REDSOUND_DRIVER_SBSS_MUSIC_NEXT_PLAY_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicNextPlay),
    REDSOUND_DRIVER_SBSS_CROSS_TIME_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_crossTime),
    REDSOUND_DRIVER_SBSS_MASTER_MUSIC_VOLUME_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_masterMusicVolume),
    REDSOUND_DRIVER_SBSS_MASTER_SE_VOLUME_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_masterSEVolume),
    REDSOUND_DRIVER_SBSS_STREAM_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_stream),
    REDSOUND_DRIVER_SBSS_DMA_MODE_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_dmaMode),
    REDSOUND_DRIVER_SBSS_SE_SKIP_STEP_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_seSkipStep),
    REDSOUND_DRIVER_SBSS_VOICE_DATA_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_voiceData),
    REDSOUND_DRIVER_SBSS_EDITOR_VOICE_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_editorVoice),
    REDSOUND_DRIVER_SBSS_EDITOR_TRACK_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_editorTrack),
    REDSOUND_DRIVER_SBSS_MAIN_THREAD_STACK_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_mainThreadStack),
    REDSOUND_DRIVER_SBSS_MAIN_THREAD_TIME_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_mainThreadTime),
    REDSOUND_DRIVER_SBSS_WAVE_THREAD_STACK_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_waveSettingThreadStack),
    REDSOUND_DRIVER_SBSS_WAVE_SETTING_STATUS_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_waveSettingStatus),
    REDSOUND_DRIVER_SBSS_DMA_THREAD_STACK_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_dmaExecuteThreadStack),
    REDSOUND_DRIVER_SBSS_DMA_STATUS_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_dmaStatus),
    REDSOUND_DRIVER_SBSS_MUSIC_THREAD_STACK_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicSkipThreadStack),
    REDSOUND_DRIVER_SBSS_MUSIC_SKIP_COMPLETE_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_musicSkipComplete),
    REDSOUND_DRIVER_SBSS_REVERB_DEPTH_OFFSET =
        (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_reverbDepth),
    REDSOUND_DRIVER_SBSS_MUTE_OFFSET = (unsigned int)&(((RedDriverSmallDataPrefixState*)0)->m_mute),
    REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE = sizeof(RedDriverSmallDataPrefixState),
    REDSOUND_DRIVER_SBSS_RED_MEMORY_OFFSET = REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE,
    REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_OFFSET = REDSOUND_DRIVER_SBSS_RED_MEMORY_OFFSET + REDSOUND_RED_MEMORY_SIZE,
    REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE = sizeof(u32) - REDSOUND_RED_MEMORY_SIZE,
    REDSOUND_DRIVER_SBSS_DMA_EXECUTE_OFFSET =
        REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_OFFSET + REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE,
    REDSOUND_DRIVER_SBSS_DMA_IN_THREAD_OFFSET = REDSOUND_DRIVER_SBSS_DMA_EXECUTE_OFFSET + sizeof(int),
    REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_OFFSET = REDSOUND_DRIVER_SBSS_DMA_IN_THREAD_OFFSET + sizeof(int),
    REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_SIZE = sizeof(int),
    REDSOUND_DRIVER_SBSS_SIZE =
        REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_OFFSET + REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_SIZE,
    REDSOUND_DRIVER_SOURCE_SBSS_SILENT_WAVE_OFFSET = REDSOUND_DRIVER_SBSS_BEFORE_RED_MEMORY_SIZE,
    REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_OFFSET =
        REDSOUND_DRIVER_SOURCE_SBSS_SILENT_WAVE_OFFSET + sizeof(int),
    REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_OFFSET =
        REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_OFFSET + REDSOUND_RED_MEMORY_SIZE,
    REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_SIZE = REDSOUND_DRIVER_SBSS_RED_MEMORY_PAD_SIZE,
    REDSOUND_DRIVER_SOURCE_SBSS_DMA_EXECUTE_OFFSET =
        REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_OFFSET + REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_SIZE,
    REDSOUND_DRIVER_SOURCE_SBSS_DMA_IN_THREAD_OFFSET =
        REDSOUND_DRIVER_SOURCE_SBSS_DMA_EXECUTE_OFFSET + sizeof(int),
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

enum RedDriverThreadControlState {
    REDSOUND_THREAD_CONTROL_STOP = 0,
    REDSOUND_THREAD_CONTROL_RUN = 1,
};

enum RedDriverDmaStatus {
    REDSOUND_DMA_STATUS_IDLE = 0,
    REDSOUND_DMA_STATUS_BUSY = 1,
};

enum RedDriverDmaMode {
    REDSOUND_DMA_MODE_NORMAL = 0,
};

enum RedDriverWorkerState {
    REDSOUND_WORKER_IDLE = 0,
    REDSOUND_WORKER_BUSY = 1,
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
    int m_unusedSilentWave;
};

struct RedDriverSourceSmallDataTailState {
    u8 m_beforeSilentWave[REDSOUND_DRIVER_SOURCE_SBSS_SILENT_WAVE_OFFSET];
    int m_silentWave;
    CRedMemory m_redMemory;
    u8 m_redMemoryAlignPadding[REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_SIZE];
    volatile int m_dmaExecute;
    volatile int m_dmaInThread;
};

STATIC_ASSERT(offsetof(RedDmaRequest, m_id) == REDSOUND_DMA_REQUEST_ID_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_direction) == REDSOUND_DMA_REQUEST_DIRECTION_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_mainMemory) == REDSOUND_DMA_REQUEST_MAIN_MEMORY_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_aramMemory) == REDSOUND_DMA_REQUEST_ARAM_MEMORY_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_size) == REDSOUND_DMA_REQUEST_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_callback) == REDSOUND_DMA_REQUEST_CALLBACK_OFFSET);
STATIC_ASSERT(offsetof(RedDmaRequest, m_callbackData) == REDSOUND_DMA_REQUEST_CALLBACK_DATA_OFFSET);
STATIC_ASSERT(sizeof(RedDmaRequest) == REDSOUND_DMA_REQUEST_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaQueue) == REDSOUND_DRIVER_SYNC_DMA_QUEUE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_streamDmaQueue) == REDSOUND_DRIVER_SYNC_STREAM_DMA_QUEUE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaQueue) == REDSOUND_DMA_QUEUE_SIZE);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_streamDmaQueue) == REDSOUND_DMA_QUEUE_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_SYNC_STREAM_DMA_QUEUE_OFFSET == REDSOUND_DRIVER_SYNC_DMA_QUEUE_OFFSET +
                                                            REDSOUND_DMA_QUEUE_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_SYNC_MAIN_THREAD_OFFSET == REDSOUND_DRIVER_SYNC_STREAM_DMA_QUEUE_OFFSET +
                                                       REDSOUND_DMA_QUEUE_SIZE);
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
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_mainThread) == REDSOUND_DRIVER_SYNC_THREAD_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_mainSemaphore) == REDSOUND_DRIVER_SYNC_MAIN_SEMAPHORE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_mainSemaphore) == REDSOUND_DRIVER_SYNC_SEMAPHORE_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_mainThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_mainThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET - REDSOUND_DRIVER_SYNC_MAIN_THREAD_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveThread) == REDSOUND_DRIVER_SYNC_WAVE_THREAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_waveThread) == REDSOUND_DRIVER_SYNC_THREAD_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveSemaphore) == REDSOUND_DRIVER_SYNC_WAVE_SEMAPHORE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_waveSemaphore) == REDSOUND_DRIVER_SYNC_SEMAPHORE_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveSettingData) == REDSOUND_DRIVER_SYNC_WAVE_DATA_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_waveSettingData) == REDSOUND_DRIVER_SYNC_WAVE_DATA_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_waveThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_waveThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET - REDSOUND_DRIVER_SYNC_WAVE_THREAD_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaThread) == REDSOUND_DRIVER_SYNC_DMA_THREAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaThread) == REDSOUND_DRIVER_SYNC_THREAD_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaSemaphore) == REDSOUND_DRIVER_SYNC_DMA_SEMAPHORE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaSemaphore) == REDSOUND_DRIVER_SYNC_SEMAPHORE_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaRequest) == REDSOUND_DRIVER_SYNC_DMA_REQUEST_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaRequest) == REDSOUND_DRIVER_SYNC_DMA_REQUEST_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_dmaThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_dmaThreadAlignPadding) ==
              REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET - REDSOUND_DRIVER_SYNC_DMA_THREAD_PAD_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_musicThread) == REDSOUND_DRIVER_SYNC_MUSIC_THREAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_musicThread) == REDSOUND_DRIVER_SYNC_THREAD_SIZE);
STATIC_ASSERT(offsetof(RedDriverSyncState, m_musicSemaphore) == REDSOUND_DRIVER_SYNC_MUSIC_SEMAPHORE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSyncState*)0)->m_musicSemaphore) == REDSOUND_DRIVER_SYNC_SEMAPHORE_SIZE);
STATIC_ASSERT(sizeof(RedDriverSyncState) == REDSOUND_DRIVER_SYNC_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_SYNC_SIZE == REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_seBlockData) == REDSOUND_SE_BLOCK_DATA_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_SE_BLOCK_DATA_OFFSET + REDSOUND_SE_BLOCK_DATA_TABLE_SIZE ==
              REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_entryWork0) ==
              REDSOUND_DRIVER_BSS_ENTRY_WORK_WORD_COUNT * sizeof(int));
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_entryWork0) == REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_ENTRY_WORK0_OFFSET + REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE ==
              REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverBssState*)0)->m_entryWork1) == REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_ENTRY_WORK1_OFFSET + REDSOUND_DRIVER_BSS_ENTRY_WORK_SIZE ==
              REDSOUND_DRIVER_BSS_ENTRY_OFFSET);
STATIC_ASSERT(REDSOUND_DRIVER_BSS_ENTRY_OFFSET + sizeof(CRedEntry) == REDSOUND_DRIVER_BSS_SIZE);

enum RedExecCommandArgIndex {
    REDSOUND_EXEC_COMMAND_ARG0 = 0,
    REDSOUND_EXEC_COMMAND_ARG1 = 1,
    REDSOUND_EXEC_COMMAND_ARG2 = 2,
    REDSOUND_EXEC_COMMAND_ARG3 = 3,
    REDSOUND_EXEC_COMMAND_ARG4 = 4,
    REDSOUND_EXEC_COMMAND_ARG5 = 5,
    REDSOUND_EXEC_COMMAND_ARG6 = 6,
    REDSOUND_EXEC_COMMAND_ARG_COUNT = REDSOUND_EXEC_COMMAND_ARG6 + 1,
};

typedef void (*RedExecCommandFunc)(int* command);

struct RedExecCommand {
    RedExecCommandFunc m_func;
    int m_args[REDSOUND_EXEC_COMMAND_ARG_COUNT];
};

#define RedExecCommandGetArg(command, index) ((command)->m_args[(index)])

enum RedExecCommandLayout {
    REDSOUND_EXEC_COMMAND_FUNC_OFFSET = (unsigned int)&(((RedExecCommand*)0)->m_func),
    REDSOUND_EXEC_COMMAND_ARGS_OFFSET = (unsigned int)&(((RedExecCommand*)0)->m_args),
    REDSOUND_EXEC_COMMAND_SIZE = sizeof(RedExecCommand),
};

struct RedMusicPlayCommand {
    int m_musicId;
    int m_volume;
    int m_mode;
    int m_reserved;
};

enum RedMusicPlayCommandLayout {
    REDSOUND_MUSIC_PLAY_COMMAND_ID_OFFSET = (unsigned int)&(((RedMusicPlayCommand*)0)->m_musicId),
    REDSOUND_MUSIC_PLAY_COMMAND_VOLUME_OFFSET = (unsigned int)&(((RedMusicPlayCommand*)0)->m_volume),
    REDSOUND_MUSIC_PLAY_COMMAND_MODE_OFFSET = (unsigned int)&(((RedMusicPlayCommand*)0)->m_mode),
    REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_OFFSET = (unsigned int)&(((RedMusicPlayCommand*)0)->m_reserved),
    REDSOUND_MUSIC_PLAY_COMMAND_SIZE = sizeof(RedMusicPlayCommand),
    REDSOUND_MUSIC_PLAY_COMMAND_RESERVED_SIZE = sizeof(((RedMusicPlayCommand*)0)->m_reserved),
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
STATIC_ASSERT(offsetof(RedDriverSmallDataTailState, m_unusedSilentWave) ==
              REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSmallDataTailState*)0)->m_unusedSilentWave) ==
              REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_SIZE);
STATIC_ASSERT(sizeof(RedDriverSmallDataTailState) == REDSOUND_DRIVER_SBSS_SIZE);
STATIC_ASSERT(offsetof(RedDriverSourceSmallDataTailState, m_silentWave) ==
              REDSOUND_DRIVER_SOURCE_SBSS_SILENT_WAVE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSourceSmallDataTailState, m_redMemory) ==
              REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSourceSmallDataTailState, m_redMemoryAlignPadding) ==
              REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedDriverSourceSmallDataTailState*)0)->m_redMemoryAlignPadding) ==
              REDSOUND_DRIVER_SOURCE_SBSS_RED_MEMORY_PAD_SIZE);
STATIC_ASSERT(offsetof(RedDriverSourceSmallDataTailState, m_dmaExecute) ==
              REDSOUND_DRIVER_SOURCE_SBSS_DMA_EXECUTE_OFFSET);
STATIC_ASSERT(offsetof(RedDriverSourceSmallDataTailState, m_dmaInThread) ==
              REDSOUND_DRIVER_SOURCE_SBSS_DMA_IN_THREAD_OFFSET);
STATIC_ASSERT(sizeof(RedDriverSourceSmallDataTailState) == REDSOUND_DRIVER_SBSS_SIZE);

enum RedDriverBufferSize {
    REDSOUND_ZERO_BUFFER_SIZE = 0x1000,
    REDSOUND_THREAD_STACK_SIZE = 0x1000,
    REDSOUND_WAVE_SETTING_TABLE_ALIGN = 0x40,
    REDSOUND_WAVE_SETTING_TABLE_ALIGN_MASK = ~(REDSOUND_WAVE_SETTING_TABLE_ALIGN - 1),
    REDSOUND_MUSIC_REPLAY_POINT_COUNT = 0x100,
    REDSOUND_MUSIC_REPLAY_POINT_SIZE = sizeof(int) * REDSOUND_MUSIC_REPLAY_POINT_COUNT,
    REDSOUND_MUSIC_REPLAY_POINT_ALLOC_SIZE = REDSOUND_MUSIC_REPLAY_POINT_SIZE,
    REDSOUND_EXEC_COMMAND_COUNT = 0x100,
    REDSOUND_EXEC_COMMAND_BUFFER_SIZE = sizeof(RedExecCommand) * REDSOUND_EXEC_COMMAND_COUNT,
    REDSOUND_EXEC_COMMAND_ALLOC_SIZE = REDSOUND_EXEC_COMMAND_BUFFER_SIZE,
    REDSOUND_EXEC_COMMAND_WORD_COUNT = REDSOUND_EXEC_COMMAND_BUFFER_SIZE / sizeof(int),
    REDSOUND_MUSIC_NEXT_PLAY_BUFFER_SIZE = sizeof(RedMusicPlayCommand),
    REDSOUND_SOUND_CONTROL_ALLOC_SIZE = REDSOUND_CONTROL_BUFFER_SIZE,
    REDSOUND_KEY_ON_ALLOC_SIZE = REDSOUND_KEY_ON_BUFFER_SIZE,
    REDSOUND_VOICE_ALLOC_SIZE = REDSOUND_VOICE_BUFFER_SIZE,
    REDSOUND_SE_TRACK_ARENA_ALLOC_SIZE = REDSOUND_SE_TRACK_ARENA_SIZE,
    REDSOUND_REVERB_DEPTH_ALLOC_SIZE = REDSOUND_REVERB_DEPTH_BUFFER_SIZE,
    REDSOUND_MUSIC_NEXT_PLAY_ALLOC_SIZE = REDSOUND_MUSIC_NEXT_PLAY_BUFFER_SIZE,
    REDSOUND_STREAM_ALLOC_SIZE = REDSOUND_STREAM_BUFFER_SIZE,
};

enum RedDriverReverbScale {
    REDSOUND_REVERB_DEPTH_INPUT_SCALE_SHIFT = 8,
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
    REDSOUND_THREAD_FLAG_NONE = 0,
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

enum RedDriverTestProcess {
    REDSOUND_TEST_PROCESS_DMA_CHECK = 1,
};

enum RedAxCompressorState {
    REDSOUND_AX_COMPRESSOR_OFF = 0,
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
#define RedTickHistoryGet() (p_Tick)
#define RedTickHistoryGetTicks() (RedTickHistoryGet()->m_ticks)
u8* volatile p_ZeroData;
static RedExecCommand* volatile p_ExecCommand;
static RedExecCommand* volatile p_ExecCommandNow;
static RedExecCommand* volatile p_ExecCommandOld;
#define RedExecCommandGetBegin() (p_ExecCommand)
#define RedExecCommandGetEnd() (p_ExecCommand + REDSOUND_EXEC_COMMAND_COUNT)
#define RedExecCommandGetNow() (p_ExecCommandNow)
#define RedExecCommandSetNow(command) (p_ExecCommandNow = (command))
#define RedExecCommandGetOld() (p_ExecCommandOld)
#define RedExecCommandSetOld(command) (p_ExecCommandOld = (command))
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
#define RedMusicNextPlayGet() (p_MusicNextPlay)
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
#define RedMainThreadStackGet() (p_MainThreadStack)
static int m_MainThreadTime;
static u8* volatile p_WaveSettingThreadStack;
#define RedWaveSettingThreadStackGet() (p_WaveSettingThreadStack)
static int m_WaveSettingStatus;
static u8* volatile p_DmaExecuteThreadStack;
#define RedDmaExecuteThreadStackGet() (p_DmaExecuteThreadStack)
static volatile int m_DMAStatus;
u8* volatile p_MusicSkipThreadStack;
#define RedMusicSkipThreadStackGet() (p_MusicSkipThreadStack)
volatile int m_MusicSkipComplete;
RedReverbDepth* volatile p_ReverbDepth;
unsigned int m_Mute[REDSOUND_MUTE_WORD_COUNT];
static int m_SilentWave;
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
                  sizeof(m_DMAInThread) + REDSOUND_DRIVER_SBSS_UNUSED_SILENT_WAVE_SIZE ==
              REDSOUND_DRIVER_SBSS_SIZE);
STATIC_ASSERT(sizeof(m_SilentWave) == sizeof(int));

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
 * EN Address: 0x801fee30
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetSoundMode(int* command)
{
    m_SoundMode = command[REDSOUND_SOUND_MODE_COMMAND_MODE];
    if (command[REDSOUND_SOUND_MODE_COMMAND_MODE] == REDSOUND_SOUND_MODE_MONO) {
        OSGetSoundMode(OS_SOUND_MODE_MONO);
    } else {
        OSGetSoundMode(OS_SOUND_MODE_STEREO);
    }
    m_SoundPlayMode = m_SoundMode;
    switch (m_SoundPlayMode) {
    case REDSOUND_SOUND_MODE_SURROUND:
        AXSetMode(REDSOUND_SOUND_MODE_SURROUND);
        break;
    default:
        AXSetMode(REDSOUND_SOUND_MODE_STEREO);
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bcf88
 * PAL Size: 192b
 * EN Address: 0x801feeac
 * EN Size: 192b
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

    reverbBank = command[REDSOUND_REVERB_COMMAND_BANK] & REDSOUND_REVERB_BANK_MASK;
    reverbDepth = command[REDSOUND_REVERB_COMMAND_DEPTH] & REDSOUND_COMMAND_VALUE_MASK;
    fadeStep = command[REDSOUND_REVERB_COMMAND_FADE_TIME];
    if (reverbDepth != 0) {
        reverbDepth += 1;
        reverbDepth <<= REDSOUND_REVERB_DEPTH_INPUT_SCALE_SHIFT;
        reverbDepth -= 1;
        reverbDepth <<= REDSOUND_FIXED_SHIFT;
    }
    RedReverbDepthGet(reverbBank)->m_depth = reverbDepth;
    if (reverbBank != 0) {
        fadeStep = fadeStep * REDSOUND_SE_FADE_TICKS_PER_SECOND;
        fadeStep = fadeStep / REDSOUND_FRAMES_PER_SECOND;
        if (fadeStep == 0) {
            fadeStep++;
        }
        reverbDepth |= REDSOUND_FIXED_HALF;
        track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
        do {
            if ((u32)track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
                fadeDepth = track->m_reverbDepth & REDSOUND_FIXED_WHOLE_MASK;
                fadeDepth = reverbDepth - fadeDepth;
                track->m_reverbDepthAdd = fadeDepth / fadeStep;
                track->m_reverbDepthDelta = fadeStep;
            }
            track++;
        } while (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE)));
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd048
 * PAL Size: 56b
 * EN Address: 0x801fef6c
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetMusicData(int* command)
{
    c_RedEntry.SetMusicData((RedMusicHEAD*)command[REDSOUND_DATA_COMMAND_BUFFER]);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: UNUSED
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ClearMusicData(int* command)
{
    c_RedEntry.ClearMusicData(command[REDSOUND_MUSIC_COMMAND_ID]);
}

static void _MusicPlaySequence(int* command);
static void _MusicCrossPlaySequence(int* command);
static void _MusicNextPlaySequence(int* command);

/*
 * --INFO--
 * PAL Address: 0x801bd080
 * PAL Size: 116b
 * EN Address: 0x801fefa4
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicStop(int* command)
{
    MusicStop(command[REDSOUND_MUSIC_COMMAND_ID]);
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == REDSOUND_MUSIC_ID_NONE) ||
        (RedMusicNextPlayGet()->m_musicId == command[REDSOUND_MUSIC_COMMAND_ID])) {
        RedMusicNextPlayGet()->m_musicId = REDSOUND_MUSIC_ID_NONE;
    }
    if (RedMusicNextPlayGet()->m_musicId < REDSOUND_MUSIC_ID_MIN) {
        m_MusicPhraseStop = REDSOUND_MUSIC_PHRASE_STOP_OFF;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd0f4
 * PAL Size: 264b
 * EN Address: 0x801ff018
 * EN Size: 264b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicPlaySequence(int* command)
{
    int replayPoint;
    RedSoundCONTROL* soundControl;

    soundControl = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
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
                replayPoint = *RedMusicReplayPointGet(command[REDSOUND_MUSIC_COMMAND_ID]);
                *RedMusicReplayPointGet(command[REDSOUND_MUSIC_COMMAND_ID]) = 0;
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
 * EN Address: 0x801ff120
 * EN Size: 520b
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
    control = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == control[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId)) {
        return;
    }

    if (command[REDSOUND_MUSIC_COMMAND_ID] == control[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId) {
        control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolumeAdd =
            -control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolume / command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        control[REDSOUND_CONTROL_MUSIC_PRIMARY].m_masterVolumeDelta = command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        control = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY);
        control->m_masterVolumeAdd =
            (REDSOUND_MASTER_VOLUME_FULL_FIXED_HALF -
             control->m_masterVolume) /
            command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        control->m_masterVolumeDelta = command[REDSOUND_MUSIC_COMMAND_FADE_TIME];
        swapControl = (RedSoundCONTROL*)RedNew(REDSOUND_CONTROL_SIZE);
        memcpy(swapControl, RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY), REDSOUND_CONTROL_SIZE);
        memcpy(RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY),
               RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY),
               REDSOUND_CONTROL_SIZE);
        memcpy(RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY), swapControl, REDSOUND_CONTROL_SIZE);
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
                replayPoint = *RedMusicReplayPointGet(command[REDSOUND_MUSIC_COMMAND_ID]);
                *RedMusicReplayPointGet(command[REDSOUND_MUSIC_COMMAND_ID]) = 0;
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
 * EN Address: 0x801ff328
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicNextPlaySequence(int* command)
{
    RedSoundCONTROL* soundControl;

    soundControl = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
    if ((command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId) ||
        (command[REDSOUND_MUSIC_COMMAND_ID] == soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId)) {
        return;
    }
    if (c_RedEntry.SearchMusicSequence(command[REDSOUND_MUSIC_COMMAND_ID]) >= 0) {
        RedMusicNextPlayGet()->m_musicId = command[REDSOUND_MUSIC_COMMAND_ID];
        RedMusicNextPlayGet()->m_volume = command[REDSOUND_MUSIC_COMMAND_VOLUME];
        RedMusicNextPlayGet()->m_mode = command[REDSOUND_MUSIC_COMMAND_MODE];
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd4a8
 * PAL Size: 116b
 * EN Address: 0x801ff3cc
 * EN Size: 116b
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
    voice = RedVoiceDataGetBegin();
    do {
        voice->m_updateFlags = voice->m_updateFlags | REDSOUND_VOICE_UPDATE_VOLUME;
        voice++;
    } while (voice < RedVoiceDataGetEnd());
}

/*
 * --INFO--
 * PAL Address: 0x801bd51c
 * PAL Size: 92b
 * EN Address: 0x801ff440
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _MusicVolume(int* command)
{
    if (command[REDSOUND_MUSIC_COMMAND_STOP_NEXT] == REDSOUND_MUSIC_VOLUME_MODE_FADE_OUT) {
        RedMusicNextPlayGet()->m_musicId = REDSOUND_MUSIC_ID_NONE;
        m_MusicPhraseStop = REDSOUND_MUSIC_PHRASE_STOP_OFF;
    }
    SetMusicVolume(command[REDSOUND_MUSIC_COMMAND_ID], command[REDSOUND_MUSIC_COMMAND_VOLUME],
                   command[REDSOUND_MUSIC_COMMAND_FADE_TIME], command[REDSOUND_MUSIC_COMMAND_STOP_NEXT]);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 */
static void _MusicTempo(int* command)
{
    SetMusicTempo(command[REDSOUND_MUSIC_COMMAND_VOLUME], command[REDSOUND_MUSIC_COMMAND_FADE_TIME]);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 */
static void _MusicPitch(int* command)
{
    SetMusicPitch(command[REDSOUND_MUSIC_COMMAND_VOLUME], command[REDSOUND_MUSIC_COMMAND_FADE_TIME]);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 */
static void _MusicPause(int* command)
{
    MusicPause(command[REDSOUND_MUSIC_COMMAND_ID], command[REDSOUND_MUSIC_COMMAND_VOLUME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd578
 * PAL Size: 12b
 * EN Address: 0x801ff49c
 * EN Size: 12b
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
 * EN Address: 0x801ff4a8
 * EN Size: 300b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SetSeBlockData(int* command)
{
    u32 index = (u32)command[REDSOUND_SE_BLOCK_DATA_COMMAND_BANK] & REDSOUND_SE_BLOCK_BANK_MASK;
    RedSeBlockHEAD* seBlockData;

    if (RedSeBlockDataGet(index) != REDSOUND_SE_BLOCK_DATA_NONE) {
        RedDelete(RedSeBlockDataGet(index));
        RedSeBlockDataGet(index) = REDSOUND_SE_BLOCK_DATA_NONE;
    }

    if (command[REDSOUND_SE_BLOCK_DATA_COMMAND_BUFFER] != 0) {
        seBlockData = (RedSeBlockHEAD*)command[REDSOUND_SE_BLOCK_DATA_COMMAND_BUFFER];
        if ((seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_0_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_0) &&
            (seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_1_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_1) &&
            (seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_2_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_2) &&
            (seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_3_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_3) &&
            (seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_4_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_4) &&
            (seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_5_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_5) &&
            (seBlockData->m_signature[REDSOUND_SE_BLOCK_SIGNATURE_6_INDEX] = REDSOUND_SE_BLOCK_SIGNATURE_6)) {
            RedSeBlockDataGet(index) = seBlockData;
        } else {
            RedDelete(seBlockData);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd6b0
 * PAL Size: 56b
 * EN Address: 0x801ff5d4
 * EN Size: 56b
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
 * EN Address: 0x801ff60c
 * EN Size: 56b
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
 * EN Address: 0x801ff644
 * EN Size: 68b
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
 * EN Address: 0x801ff688
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _SeStop(int* command)
{
    SeStopID(command[REDSOUND_SE_COMMAND_ID]);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 */
static void _SeStopG(int* command)
{
    SeStopG(command[REDSOUND_SE_COMMAND_ID]);
}

/*
 * --INFO--
 * PAL Address: 0x801bd794
 * PAL Size: 60b
 * EN Address: 0x801ff6b8
 * EN Size: 60b
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
 * EN Address: 0x801ff6f4
 * EN Size: 72b
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
 * EN Address: 0x801ff73c
 * EN Size: 108b
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
 * EN Address: 0x801ff7a8
 * EN Size: 92b
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
 * EN Address: 0x801ff804
 * EN Size: 116b
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
    voice = RedVoiceDataGetBegin();
    do {
        voice->m_updateFlags = voice->m_updateFlags | REDSOUND_VOICE_UPDATE_VOLUME;
        voice++;
    } while (voice < RedVoiceDataGetEnd());
}

/*
 * --INFO--
 * PAL Address: 0x801bd954
 * PAL Size: 60b
 * EN Address: 0x801ff878
 * EN Size: 60b
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
 * EN Address: 0x801ff8b4
 * EN Size: 56b
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
 * EN Address: 0x801ff8ec
 * EN Size: 56b
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
 * EN Address: 0x801ff924
 * EN Size: 52b
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
 * EN Address: 0x801ff958
 * EN Size: 48b
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
 * EN Address: 0x801ff988
 * EN Size: 64b
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
 * EN Address: 0x801ff9c8
 * EN Size: 56b
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
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: UNUSED
 * EN Size: 56b
 * JP Address: TODO
 */
static void _StreamPan(int* command)
{
	SetStreamPan(command[REDSOUND_STREAM_COMMAND_ID], command[REDSOUND_STREAM_COMMAND_PAN],
	             command[REDSOUND_STREAM_COMMAND_FADE_TIME]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdadc
 * PAL Size: 52b
 * EN Address: 0x801ffa00
 * EN Size: 52b
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
 * EN Address: 0x801ffa34
 * EN Size: 192b
 * JP Address: TODO
 * JP Size: TODO
 */
static RedExecCommand* _EntryExecCommand(RedExecCommandFunc func, int arg1, int arg2, int arg3, int arg4,
                                         int arg5, int arg6, int arg7)
{
    unsigned int interruptLevel;
    RedExecCommand* writePos;

    interruptLevel = OSDisableInterrupts();
    writePos = RedExecCommandGetNow();
    writePos->m_func = func;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG0) = arg1;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG1) = arg2;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG2) = arg3;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG3) = arg4;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG4) = arg5;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG5) = arg6;
    RedExecCommandGetArg(writePos, REDSOUND_EXEC_COMMAND_ARG6) = arg7;
    writePos++;
    if (writePos == RedExecCommandGetEnd()) {
        writePos = RedExecCommandGetBegin();
    }
    RedExecCommandSetNow(writePos);
    OSRestoreInterrupts(interruptLevel);
    return writePos;
}

/*
 * --INFO--
 * PAL Address: 0x801bdbd0
 * PAL Size: 120b
 * EN Address: 0x801ffaf4
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _ExecuteCommand()
{
	volatile RedExecCommand* readPos;
	volatile RedExecCommand* executePos;

	executePos = RedExecCommandGetNow();
	readPos = RedExecCommandGetOld();

	while (executePos != readPos) {
		if (readPos->m_func != 0) {
			readPos->m_func((int*)readPos->m_args);
		}
		readPos++;
		if (readPos == RedExecCommandGetEnd()) {
			readPos = RedExecCommandGetBegin();
		}
	}

	RedExecCommandSetOld((RedExecCommand*)readPos);
}

/*
 * --INFO--
 * PAL Address: 0x801bdc48
 * PAL Size: 112b
 * EN Address: 0x801ffb6c
 * EN Size: 112b
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
 * EN Address: 0x801ffbdc
 * EN Size: 56b
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
 * EN Address: 0x801ffc14
 * EN Size: 44b
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
 * EN Address: 0x801ffc40
 * EN Size: 160b
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
 * EN Address: 0x801ffce0
 * EN Size: 300b
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
    while (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
        OSWaitSemaphore(&m_MainSemaphore);
        if (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
            startTick = OSGetTick();
            control = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
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
            if ((RedMusicNextPlayGet()->m_musicId >= REDSOUND_MUSIC_ID_MIN) &&
                (control->m_musicId < REDSOUND_MUSIC_ID_MIN)) {
                _MusicPlaySequence((int*)RedMusicNextPlayGet());
                RedMusicNextPlayGet()->m_musicId = REDSOUND_MUSIC_ID_NONE;
                m_MusicPhraseStop = REDSOUND_MUSIC_PHRASE_STOP_OFF;
            }
            while (OSTryWaitSemaphore(&m_MainSemaphore) > 0) {
            }
            memmove(RedTickHistoryGetTicks() + 1, RedTickHistoryGetTicks(), REDSOUND_TICK_HISTORY_SHIFT_SIZE);
            endTick = OSGetTick();
            RedTickHistoryGetTicks()[REDSOUND_TICK_HISTORY_LATEST] = endTick - startTick;
        }
    }
    m_ThreadExecute = m_ThreadExecute & ~REDSOUND_THREAD_FLAG_MAIN;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bdee8
 * PAL Size: 196b
 * EN Address: 0x801ffe0c
 * EN Size: 196b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _WaveSettingThread(void* threadArg)
{
    m_ThreadExecute = m_ThreadExecute | REDSOUND_THREAD_FLAG_WAVE_SETTING;
    m_WaveSettingStatus = REDSOUND_WORKER_IDLE;
    while (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
        OSWaitSemaphore(&m_WaveSettingSemaphore);
        if (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
            RedWaveSettingState* waveSetting = (RedWaveSettingState*)threadArg;
            m_WaveSettingStatus = m_WaveSettingStatus + 1;
            c_RedEntry.SetWaveData(waveSetting->m_waveId, waveSetting->m_waveData, waveSetting->m_waveSize);
            *waveSetting->m_slot = 0;
            do {
            } while (OSTryWaitSemaphore(&m_WaveSettingSemaphore) > 0);
            m_WaveSettingStatus = REDSOUND_WORKER_IDLE;
        }
    }
    m_ThreadExecute = m_ThreadExecute & ~REDSOUND_THREAD_FLAG_WAVE_SETTING;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bdfac
 * PAL Size: 280b
 * EN Address: 0x801ffed0
 * EN Size: 280b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _DMACheckProcess()
{
    RedDmaRequest* dmaInfo;

    if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
        OSReport(s_redDriverDmaCheckHeaderFmt, sRedDriverLogPrefix);
        fflush(__files + 1);

        OSReport(sRedDriverDmaStatusFmt, sRedDriverLogPrefix, m_DMAStatus,
                 OSGetSemaphoreCount(&m_DmaExecuteSemaphore), m_DMAExecute, m_DMAInThread);
        fflush(__files + 1);
    }

    dmaInfo = RedDriverMainDmaQueue();
    do {
        if ((dmaInfo->m_id != REDSOUND_DMA_ID_NONE) && (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF)) {
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
 * EN Address: 0x801fffe8
 * EN Size: 12b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _DmaCallback(unsigned long)
{
    m_DMAStatus = REDSOUND_DMA_STATUS_IDLE;
}

/*
 * --INFO--
 * PAL Address: 0x801be0d0
 * PAL Size: 356b
 * EN Address: 0x801ffff4
 * EN Size: 356b
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
    if ((m_DMAMode != REDSOUND_DMA_MODE_NORMAL) || ((flags & REDSOUND_DMA_FLAG_CHUNKED_TRANSFER) != 0)) {
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
                queueEntry->m_callback = REDSOUND_DMA_CALLBACK_NONE;
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
 * EN Address: 0x80200158
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
int RedDmaSearchID(int id)
{
    unsigned int interruptLevel;
    int found;
    RedDmaRequest* queueEntry;

    found = REDSOUND_DMA_SEARCH_NOT_FOUND;
    interruptLevel = OSDisableInterrupts();
    if (id != REDSOUND_DMA_ID_NONE) {
        queueEntry = RedDriverMainDmaQueue();
        do {
            if ((queueEntry->m_id != REDSOUND_DMA_ID_NONE) &&
                ((id == REDSOUND_DMA_ID_NONE) || (queueEntry->m_id == id))) {
                found = REDSOUND_DMA_SEARCH_FOUND;
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
 * PAL Size: 96b
 * EN Address: UNUSED
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
void RedDmaClearID(int id)
{
    unsigned int interruptLevel;
    RedDmaRequest* queueEntry;

    interruptLevel = OSDisableInterrupts();
    queueEntry = RedDriverMainDmaQueue();
    do {
        if ((id == REDSOUND_DMA_ID_NONE) || (queueEntry->m_id == id)) {
            queueEntry->m_id = REDSOUND_DMA_ID_NONE;
        }
        queueEntry++;
    } while (queueEntry < RedDriverStreamDmaQueueEnd());
    OSRestoreInterrupts(interruptLevel);
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
inline void RedSetDMAMode(int mode)
{
    m_DMAMode = mode;
}

/*
 * --INFO--
 * PAL Address: 0x801be2dc
 * PAL Size: 496b
 * EN Address: 0x80200200
 * EN Size: 496b
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
        if (queueEntry->m_id != REDSOUND_DMA_ID_NONE) {
            m_DMAStatus = REDSOUND_DMA_STATUS_BUSY;
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
            if (m_DMAStatus == REDSOUND_DMA_STATUS_IDLE) {
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
                activeRequest->m_id = REDSOUND_DMA_ID_NONE;
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
 * EN Address: 0x802003f0
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _DmaExecuteThread(void*)
{
    m_ThreadExecute |= REDSOUND_THREAD_FLAG_DMA;
    m_DMAExecute = REDSOUND_WORKER_IDLE;
    m_DMAInThread = REDSOUND_DMA_THREAD_IDLE;
    while (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
        OSWaitSemaphore(&m_DmaExecuteSemaphore);
        m_DMAExecute = REDSOUND_WORKER_BUSY;
        if (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
            _DmaExecute();
        }
        m_DMAExecute = REDSOUND_WORKER_IDLE;
    }
    m_ThreadExecute &= ~REDSOUND_THREAD_FLAG_DMA;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be550
 * PAL Size: 128b
 * EN Address: 0x80200474
 * EN Size: 128b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _MusicSkipThread(void*)
{
    m_ThreadExecute |= REDSOUND_THREAD_FLAG_MUSIC_SKIP;
    m_MusicSkipComplete = REDSOUND_MUSIC_SKIP_NOT_COMPLETE;
    while (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
        OSWaitSemaphore(&m_MusicSkipSemaphore);
        if (m_ThreadControl != REDSOUND_THREAD_CONTROL_STOP) {
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
 * EN Address: 0x802004f4
 * EN Size: 56b
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
 * EN Address: 0x8020052c
 * EN Size: 4b
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
 * EN Address: 0x80200530
 * EN Size: 72b
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
 * EN Address: 0x80200578
 * EN Size: 1316b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::Init()
{
    RedDriverSyncState& sync = RedDriverSync();
    RedSeBlockHEAD* volatile* seBlockData = RedSeBlockDataGetBegin();
    RedTrackDATA* seTrackArena;
    RedDmaRequest* dmaControl;
    unsigned int* mute;
    int* editorVoice;
    int allocSize;
    int nextIndex;
    int index;
    int fullVolume;
    int noMusicId;

    m_ThreadExecute = REDSOUND_THREAD_FLAG_NONE;
    m_ThreadControl = REDSOUND_THREAD_CONTROL_RUN;
    m_ReportPrint = REDSOUND_REPORT_PRINT_ON;
    m_SoundMode = REDSOUND_SOUND_MODE_STEREO;
    GetSoundMode();
    switch (m_SoundPlayMode) {
    case REDSOUND_SOUND_MODE_SURROUND:
        AXSetMode(REDSOUND_SOUND_MODE_SURROUND);
        break;
    default:
        AXSetMode(REDSOUND_SOUND_MODE_STEREO);
        break;
    }
    p_Tick = (RedTickHistory*)RedNew(REDSOUND_TICK_HISTORY_SIZE);
    memset(RedTickHistoryGet(), 0, REDSOUND_TICK_HISTORY_SIZE);
    AXSetCompressor(REDSOUND_AX_COMPRESSOR_OFF);
    m_MusicKeySignature = 0;
    m_SoundMasterControl = 0;
    m_MusicSkipLine = 0;
    m_MusicFastSpeed = 0;
    m_DMAStatus = REDSOUND_DMA_STATUS_IDLE;
    m_CrossTime = 0;
    m_MasterSEVolume = REDSOUND_MASTER_VOLUME_FULL;
    m_MasterMusicVolume = REDSOUND_MASTER_VOLUME_FULL;
    index = 0;
    do {
        nextIndex = index + 1;
        seBlockData[index] = REDSOUND_SE_BLOCK_DATA_NONE;
        index = nextIndex;
    } while (nextIndex < REDSOUND_SE_BLOCK_BANK_COUNT);
    p_ZeroData = (u8*)RedNew(REDSOUND_ZERO_BUFFER_SIZE);
    memset(RedZeroDataGet(), 0, REDSOUND_ZERO_BUFFER_SIZE);
    p_MusicReplayPoint = (int*)RedNew(REDSOUND_MUSIC_REPLAY_POINT_SIZE);
    memset(RedMusicReplayPointGetBegin(), 0, REDSOUND_MUSIC_REPLAY_POINT_SIZE);
    p_MusicTempoControl = (RedControlRamp*)RedNew(REDSOUND_CONTROL_RAMP_SIZE);
    memset(RedMusicTempoControlGet(), 0, REDSOUND_CONTROL_RAMP_SIZE);
    p_MusicPitchControl = (RedControlRamp*)RedNew(REDSOUND_CONTROL_RAMP_SIZE);
    memset(RedMusicPitchControlGet(), 0, REDSOUND_CONTROL_RAMP_SIZE);
    allocSize = REDSOUND_EXEC_COMMAND_BUFFER_SIZE;
    p_ExecCommand = (RedExecCommand*)RedNew(allocSize);
    RedExecCommandSetNow(RedExecCommandGetBegin());
    RedExecCommandSetOld(RedExecCommandGetBegin());
    memset(RedExecCommandGetBegin(), 0, allocSize);
    allocSize = REDSOUND_CONTROL_BUFFER_SIZE;
    p_SoundControlBuffer = (RedSoundCONTROL*)RedNew(allocSize);
    RedCurrentSoundControlSet(RedSoundControlGetBegin());
    memset(RedSoundControlGetBegin(), 0, allocSize);
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
    memset(RedKeyOnDataGet(), 0, REDSOUND_KEY_ON_BUFFER_SIZE);
    p_VoiceData = (RedVoiceDATA*)RedNew(REDSOUND_VOICE_BUFFER_SIZE);
    memset(RedVoiceDataGetBegin(), 0, REDSOUND_VOICE_BUFFER_SIZE);
    index = 0;
    do {
        nextIndex = index % REDSOUND_SE_VOICE_BASE_INDEX;
        RedVoiceDataGet(index)->m_voiceIndex = nextIndex;
        index = index + 1;
    } while (index < REDSOUND_VOICE_COUNT);
    editorVoice = RedEditorVoiceGetBegin();
    editorVoice[REDSOUND_EDITOR_VOICE_RIGHT] = 0;
    editorVoice[REDSOUND_EDITOR_VOICE_LEFT] = 0;
    RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks = (RedTrackDATA*)RedNew(REDSOUND_SE_TRACK_ARENA_SIZE);
    memset(RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks, 0, REDSOUND_SE_TRACK_ARENA_SIZE);
    seTrackArena = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
    nextIndex = 0;
    do {
        seTrackArena[nextIndex].m_trackNo = (char)(nextIndex + REDSOUND_SE_VOICE_BASE_INDEX);
        nextIndex = nextIndex + 1;
    } while (nextIndex < REDSOUND_SE_TRACK_COUNT);
    p_EditorTrack = (RedTrackDATA*)RedNew(REDSOUND_TRACK_SIZE);
    memset(RedEditorTrackGet(), 0, REDSOUND_TRACK_SIZE);
    p_ReverbDepth = (RedReverbDepth*)RedNew(REDSOUND_REVERB_DEPTH_BUFFER_SIZE);
    memset(RedReverbDepthGetBegin(), 0, REDSOUND_REVERB_DEPTH_BUFFER_SIZE);
    mute = m_Mute;
    mute[REDSOUND_MUTE_HIGH_WORD] = 0;
    mute[REDSOUND_MUTE_LOW_WORD] = 0;
    p_MusicNextPlay = (RedMusicPlayCommand*)RedNew(REDSOUND_MUSIC_NEXT_PLAY_BUFFER_SIZE);
    RedMusicNextPlayGet()->m_musicId = REDSOUND_MUSIC_ID_NONE;
    m_MusicPhraseStop = REDSOUND_MUSIC_PHRASE_STOP_OFF;
    p_Stream = (RedStreamDATA*)RedNew(REDSOUND_STREAM_BUFFER_SIZE);
    memset(RedStreamDataGetBegin(), 0, REDSOUND_STREAM_BUFFER_SIZE);
    m_DMAMode = REDSOUND_DMA_MODE_NORMAL;
    dmaControl = sync.m_dmaQueue;
    memset(dmaControl, 0, REDSOUND_DMA_CONTROL_SIZE);
    p_DmaControlNow[REDSOUND_DMA_MAIN_QUEUE_INDEX] = dmaControl;
    p_DmaControlOld[REDSOUND_DMA_MAIN_QUEUE_INDEX] = dmaControl;
    p_DmaControlNow[REDSOUND_DMA_STREAM_QUEUE_INDEX] = dmaControl + REDSOUND_DMA_QUEUE_ENTRY_COUNT;
    p_DmaControlOld[REDSOUND_DMA_STREAM_QUEUE_INDEX] = dmaControl + REDSOUND_DMA_QUEUE_ENTRY_COUNT;
    m_RedMasterTime = 0;
    AXRegisterCallback(_RedAXCallback);
    AXFXSetHooks(ReverbAreaAlloc, ReverbAreaFree);
    InitReverb();
    OSInitSemaphore(&sync.m_dmaSemaphore, 0);
    p_DmaExecuteThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&sync.m_dmaThread, (void* (*)(void*))_DmaExecuteThread, 0,
                   RedDmaExecuteThreadStackGet() + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_DMA_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&sync.m_dmaThread);
    OSInitSemaphore(&sync.m_waveSemaphore, 0);
    p_WaveSettingThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&sync.m_waveThread, (void* (*)(void*))_WaveSettingThread, &sync.m_waveSettingData,
                   RedWaveSettingThreadStackGet() + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_WORKER_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&sync.m_waveThread);
    OSInitSemaphore(&sync.m_musicSemaphore, 0);
    p_MusicSkipThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&sync.m_musicThread, (void* (*)(void*))_MusicSkipThread, 0,
                   RedMusicSkipThreadStackGet() + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_WORKER_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&sync.m_musicThread);
    OSInitSemaphore(&sync.m_mainSemaphore, 0);
    m_MainThreadTime = 0;
    p_MainThreadStack = (u8*)RedNew(REDSOUND_THREAD_STACK_SIZE);
    OSCreateThread(&sync.m_mainThread, (void* (*)(void*))_MainThread, 0,
                   RedMainThreadStackGet() + REDSOUND_THREAD_STACK_SIZE, REDSOUND_THREAD_STACK_SIZE,
                   REDSOUND_WORKER_THREAD_PRIORITY, REDSOUND_THREAD_DETACHED);
    OSResumeThread(&sync.m_mainThread);
}

/*
 * --INFO--
 * PAL Address: 0x801beb78
 * PAL Size: 140b
 * EN Address: 0x80200a9c
 * EN Size: 140b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::End()
{
    RedDriverSyncState& sync = RedDriverSync();

    AXRegisterCallback(0);
    m_ThreadControl = REDSOUND_THREAD_CONTROL_STOP;
    OSSignalSemaphore(&sync.m_mainSemaphore);
    OSSignalSemaphore(&sync.m_waveSemaphore);
    OSSignalSemaphore(&sync.m_dmaSemaphore);
    OSSignalSemaphore(&sync.m_musicSemaphore);
    while (m_ThreadExecute != REDSOUND_THREAD_FLAG_NONE) {
        RedSleep(REDSOUND_THREAD_YIELD_SLEEP_US);
    }
    AXRegisterAuxACallback(0, 0);
    AXRegisterAuxBCallback(0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bec04
 * PAL Size: 68b
 * EN Address: 0x80200b28
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetProgramTime()
{
    int sum = 0;
    int* p = RedTickHistoryGetTicks();

    do {
        sum += *p;
        p++;
    } while (p < RedTickHistoryGetTicks() + REDSOUND_TICK_HISTORY_COUNT);
    return sum;
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
inline int CRedDriver::GetMasterTime()
{
    return m_RedMasterTime;
}

/*
 * --INFO--
 * PAL Address: 0x801bec48
 * PAL Size: 72b
 * EN Address: 0x80200b6c
 * EN Size: 72b
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
 * EN Address: 0x80200bb4
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetSoundMode()
{
    int soundMode = __OSReadROM();

    if (soundMode == 0) {
        m_SoundPlayMode = REDSOUND_SOUND_MODE_MONO;
    } else {
        m_SoundPlayMode = m_SoundMode;
    }
    return m_SoundPlayMode;
}

/*
 * --INFO--
 * PAL Address: 0x801becd8
 * PAL Size: 276b
 * EN Address: 0x80200bfc
 * EN Size: 276b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SetMusicData(void* musicData)
{
    int headerSize;
    int result;
    RedMusicHEAD* header = (RedMusicHEAD*)musicData;
    RedMusicHEAD localHeader;

    result = REDSOUND_MUSIC_ID_NONE;
    if (((header->m_signature[REDSOUND_MUSIC_SIGNATURE_0_INDEX] == REDSOUND_MUSIC_SIGNATURE_0) &&
         (header->m_signature[REDSOUND_MUSIC_SIGNATURE_1_INDEX] == REDSOUND_MUSIC_SIGNATURE_1)) &&
        (header->m_signature[REDSOUND_MUSIC_SIGNATURE_2_INDEX] == REDSOUND_MUSIC_SIGNATURE_2)) {
        memcpy(&localHeader, musicData, REDSOUND_MUSIC_HEADER_SIZE);
        headerSize = localHeader.m_size;
        header = (RedMusicHEAD*)RedNew(headerSize);
        if (header != 0) {
            memcpy(header, musicData, headerSize);
            result = localHeader.m_musicNo;
            _EntryExecCommand(_SetMusicData, (int)header, 0, 0, 0, 0, 0, 0);
        }
    } else if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
        OSReport(sRedDriverMusicHeaderErrorFmt, sRedDriverLogPrefix, sRedDriverLogWarnColor, sRedDriverLogReset);
        fflush(__files + 1);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: UNUSED
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::ClearMusicData(int musicID)
{
    _EntryExecCommand(_ClearMusicData, musicID, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bedec
 * PAL Size: 92b
 * EN Address: 0x80200d10
 * EN Size: 92b
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
 * PAL Address: UNUSED
 * PAL Size: 372b
 * EN Address: UNUSED
 * EN Size: 372b
 * JP Address: TODO
 */
inline int CRedDriver::MusicPlayState(int musicID)
{
    RedExecCommand* commandNow;
    unsigned int interruptLevel;
    RedSoundCONTROL* soundControl;
    int result;
    RedExecCommand* command;

    interruptLevel = OSDisableInterrupts();
    result = 0;
    soundControl = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
    if (((musicID == REDSOUND_MUSIC_ID_NONE) ||
         (soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId == musicID)) &&
        (soundControl[REDSOUND_CONTROL_MUSIC_PRIMARY].m_activeTrackCount != 0)) {
        result = 1;
    } else if (((musicID == REDSOUND_MUSIC_ID_NONE) ||
                (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId == musicID)) &&
               (soundControl[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount != 0)) {
        result = 1;
    } else if ((musicID == REDSOUND_MUSIC_ID_NONE) ||
               (soundControl[REDSOUND_CONTROL_MUSIC_SKIP].m_musicId == musicID)) {
        result = 1;
    } else if ((RedMusicNextPlayGet()->m_musicId >= REDSOUND_MUSIC_ID_MIN) &&
               ((musicID == REDSOUND_MUSIC_ID_NONE) || (RedMusicNextPlayGet()->m_musicId == musicID))) {
        result = 1;
    }

    if (result == 0) {
        commandNow = RedExecCommandGetNow();
        command = RedExecCommandGetOld();
        while (commandNow != command) {
            if ((command->m_func != 0) &&
                ((command->m_func == _MusicPlaySequence) ||
                 (command->m_func == _MusicCrossPlaySequence) ||
                 (command->m_func == _MusicNextPlaySequence)) &&
                ((musicID == REDSOUND_MUSIC_ID_NONE) ||
                 (musicID == RedExecCommandGetArg(command, REDSOUND_EXEC_COMMAND_ARG0)))) {
                result = 1;
                break;
            }
            command++;
            if (command == RedExecCommandGetEnd()) {
                command = RedExecCommandGetBegin();
            }
        }
    }

    OSRestoreInterrupts(interruptLevel);
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bee48
 * PAL Size: 72b
 * EN Address: 0x80200d6c
 * EN Size: 72b
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
 * EN Address: 0x80200db4
 * EN Size: 88b
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
 * PAL Address: UNUSED
 * PAL Size: 272b
 * EN Address: UNUSED
 * EN Size: 272b
 * JP Address: TODO
 */
inline int CRedDriver::MusicPlay(void* musicData, int volume, int mode)
{
    int result;
    RedMusicHEAD localHeader;
    RedMusicHEAD* const header = (RedMusicHEAD*)musicData;
    RedMusicHEAD* copiedHeader;
    int headerSize;

    result = REDSOUND_MUSIC_ID_NONE;
    if (((header->m_signature[REDSOUND_MUSIC_SIGNATURE_0_INDEX] == REDSOUND_MUSIC_SIGNATURE_0) &&
         (header->m_signature[REDSOUND_MUSIC_SIGNATURE_1_INDEX] == REDSOUND_MUSIC_SIGNATURE_1)) &&
        (header->m_signature[REDSOUND_MUSIC_SIGNATURE_2_INDEX] == REDSOUND_MUSIC_SIGNATURE_2)) {
        memcpy(&localHeader, header, REDSOUND_MUSIC_HEADER_SIZE);
        headerSize = localHeader.m_size;
        copiedHeader = (RedMusicHEAD*)RedNew(headerSize);
        if (copiedHeader == 0) {
            return result;
        }
        memcpy(copiedHeader, header, headerSize);
        result = copiedHeader->m_musicNo;
        _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        _EntryExecCommand(_MusicPlaySequence, result, volume, mode, 0, 0, 0, 0);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801beee8
 * PAL Size: 88b
 * EN Address: 0x80200e0c
 * EN Size: 88b
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
 * PAL Address: UNUSED
 * PAL Size: 272b
 * EN Address: UNUSED
 * EN Size: 272b
 * JP Address: TODO
 */
inline int CRedDriver::MusicCrossPlay(void* musicData, int volume, int mode)
{
    int result;
    RedMusicHEAD localHeader;
    RedMusicHEAD* const header = (RedMusicHEAD*)musicData;
    RedMusicHEAD* copiedHeader;
    int headerSize;

    result = REDSOUND_MUSIC_ID_NONE;
    if (((header->m_signature[REDSOUND_MUSIC_SIGNATURE_0_INDEX] == REDSOUND_MUSIC_SIGNATURE_0) &&
         (header->m_signature[REDSOUND_MUSIC_SIGNATURE_1_INDEX] == REDSOUND_MUSIC_SIGNATURE_1)) &&
        (header->m_signature[REDSOUND_MUSIC_SIGNATURE_2_INDEX] == REDSOUND_MUSIC_SIGNATURE_2)) {
        memcpy(&localHeader, header, REDSOUND_MUSIC_HEADER_SIZE);
        headerSize = localHeader.m_size;
        copiedHeader = (RedMusicHEAD*)RedNew(headerSize);
        if (copiedHeader == 0) {
            return result;
        }
        memcpy(copiedHeader, header, headerSize);
        result = copiedHeader->m_musicNo;
        _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        _EntryExecCommand(_MusicCrossPlaySequence, result, volume, mode, 0, 0, 0, 0);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bef40
 * PAL Size: 88b
 * EN Address: 0x80200e64
 * EN Size: 88b
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
 * PAL Address: UNUSED
 * PAL Size: 272b
 * EN Address: UNUSED
 * EN Size: 272b
 * JP Address: TODO
 */
inline int CRedDriver::MusicNextPlay(void* musicData, int volume, int mode)
{
    int result;
    RedMusicHEAD localHeader;
    RedMusicHEAD* const header = (RedMusicHEAD*)musicData;
    RedMusicHEAD* copiedHeader;
    int headerSize;

    result = REDSOUND_MUSIC_ID_NONE;
    if (((header->m_signature[REDSOUND_MUSIC_SIGNATURE_0_INDEX] == REDSOUND_MUSIC_SIGNATURE_0) &&
         (header->m_signature[REDSOUND_MUSIC_SIGNATURE_1_INDEX] == REDSOUND_MUSIC_SIGNATURE_1)) &&
        (header->m_signature[REDSOUND_MUSIC_SIGNATURE_2_INDEX] == REDSOUND_MUSIC_SIGNATURE_2)) {
        memcpy(&localHeader, header, REDSOUND_MUSIC_HEADER_SIZE);
        headerSize = localHeader.m_size;
        copiedHeader = (RedMusicHEAD*)RedNew(headerSize);
        if (copiedHeader == 0) {
            return result;
        }
        memcpy(copiedHeader, header, headerSize);
        result = copiedHeader->m_musicNo;
        _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        _EntryExecCommand(_MusicNextPlaySequence, result, volume, mode, 0, 0, 0, 0);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bef98
 * PAL Size: 72b
 * EN Address: 0x80200ebc
 * EN Size: 72b
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
 * EN Address: 0x80200f04
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicFadeOut(int musicID, int fadeTime)
{
    _EntryExecCommand(_MusicVolume, musicID, 0, fadeTime, REDSOUND_MUSIC_VOLUME_MODE_FADE_OUT, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf02c
 * PAL Size: 80b
 * EN Address: 0x80200f50
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicVolume(int musicID, int volume, int frameCount)
{
    _EntryExecCommand(_MusicVolume, musicID, volume, frameCount, REDSOUND_MUSIC_VOLUME_MODE_NORMAL, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: UNUSED
 * EN Size: 76b
 * JP Address: TODO
 */
inline void CRedDriver::MusicTempo(int tempo, int frameCount)
{
    _EntryExecCommand(_MusicTempo, 0, tempo, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: UNUSED
 * EN Size: 76b
 * JP Address: TODO
 */
inline void CRedDriver::MusicPitch(int pitch, int frameCount)
{
    _EntryExecCommand(_MusicPitch, 0, pitch, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: UNUSED
 * EN Size: 76b
 * JP Address: TODO
 */
inline void CRedDriver::MusicPause(int musicID, int pause)
{
    _EntryExecCommand(_MusicPause, musicID, pause, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf07c
 * PAL Size: 72b
 * EN Address: 0x80200fa0
 * EN Size: 72b
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
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedDriver::CheckMusicEntry(int musicID)
{
    return c_RedEntry.SearchMusicSequence(musicID);
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
inline void CRedDriver::SetMusicFastSpeed(int speed)
{
    m_MusicFastSpeed = speed;
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
inline int CRedDriver::CheckMusicPhraseStop()
{
    return m_MusicPhraseStop;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: UNUSED
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::DisplayMusicInfo()
{
    c_RedEntry.DisplayMusicInfo();
}

/*
 * --INFO--
 * PAL Address: 0x801bf0c4
 * PAL Size: 168b
 * EN Address: 0x80200fe8
 * EN Size: 168b
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
 * EN Address: 0x80201090
 * EN Size: 288b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SetSeSepData(void* seSepData)
{
    int headerSize;
    int result = REDSOUND_SESEP_ID_NONE;
    RedSeSepHEAD* header = (RedSeSepHEAD*)seSepData;

    if (((((header->m_signature[REDSOUND_SESEP_SIGNATURE_0_INDEX] == REDSOUND_SESEP_SIGNATURE_0) &&
           (header->m_signature[REDSOUND_SESEP_SIGNATURE_1_INDEX] == REDSOUND_SESEP_SIGNATURE_1)) &&
          (header->m_signature[REDSOUND_SESEP_SIGNATURE_2_INDEX] == REDSOUND_SESEP_SIGNATURE_2)) &&
         ((header->m_signature[REDSOUND_SESEP_SIGNATURE_3_INDEX] == REDSOUND_SESEP_SIGNATURE_3 &&
           (header->m_signature[REDSOUND_SESEP_SIGNATURE_4_INDEX] == REDSOUND_SESEP_SIGNATURE_4))))) {
        headerSize = ((RedSeSepHEAD*)seSepData)->m_sizeAndFlags;
        headerSize &= REDSOUND_SESEP_SIZE_MASK;
        header = (RedSeSepHEAD*)RedNew(headerSize);
        if (header != 0) {
            memcpy(header, seSepData, headerSize);
            result = header->m_seNo;
            _EntryExecCommand(_SetSeSepData, (int)header, 0, 0, 0, 0, 0, 0);
        }
    } else if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
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
 * EN Address: 0x802011b0
 * EN Size: 72b
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
 * EN Address: 0x802011f8
 * EN Size: 84b
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
 * EN Address: 0x8020124c
 * EN Size: 92b
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
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedDriver::CheckSeSepEntry(int id)
{
    return c_RedEntry.SearchSeSepSequence(id);
}

/*
 * --INFO--
 * PAL Address: 0x801bf384
 * PAL Size: 288b
 * EN Address: 0x802012a8
 * EN Size: 288b
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
    seInfoBase = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
    seInfo = *seInfoBase;
    do {
        if (((u32)seInfo->m_command != REDSOUND_TRACK_COMMAND_NONE) && ((seID == REDSOUND_SE_ID_ALL || (seInfo->m_seId == seID)))) {
            result = (int)seInfo;
            break;
        }
        seInfo++;
    } while (seInfo < RedSeTrackGetEnd(*seInfoBase));
    if (result == 0) {
        commandNow = RedExecCommandGetNow();
        command = RedExecCommandGetOld();
        while (commandNow != command) {
            if (((command->m_func != 0) &&
                (((command->m_func == _SeBlockPlay) ||
                  (command->m_func == _SeSepPlay)) ||
                 (command->m_func == _SeSepPlaySequence))) &&
                ((seID == REDSOUND_SE_ID_ALL || (seID == RedExecCommandGetArg(command, REDSOUND_EXEC_COMMAND_ARG0))))) {
                result = 1;
                break;
            }
            command++;
            if (command == RedExecCommandGetEnd()) {
                command = RedExecCommandGetBegin();
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
 * EN Address: 0x802013c8
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeStop(int id)
{
    _EntryExecCommand(_SeStop, id, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: UNUSED
 * EN Size: 72b
 * JP Address: TODO
 */
inline void CRedDriver::SeStopG(int group)
{
    _EntryExecCommand(_SeStopG, group, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf4ec
 * PAL Size: 84b
 * EN Address: 0x80201410
 * EN Size: 84b
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
 * EN Address: 0x80201464
 * EN Size: 196b
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
 * PAL Address: UNUSED
 * PAL Size: 312b
 * EN Address: UNUSED
 * EN Size: 312b
 * JP Address: TODO
 */
inline int CRedDriver::SePlay(void* seSepData, int autoID, int pan, int volume, int pitch)
{
    int result = REDSOUND_SESEP_ID_NONE;
    RedSeSepHEAD* const header = (RedSeSepHEAD*)seSepData;
    RedSeSepHEAD* copiedHeader;
    int headerSize;

    if (((((header->m_signature[REDSOUND_SESEP_SIGNATURE_0_INDEX] == REDSOUND_SESEP_SIGNATURE_0) &&
           (header->m_signature[REDSOUND_SESEP_SIGNATURE_1_INDEX] == REDSOUND_SESEP_SIGNATURE_1)) &&
          (header->m_signature[REDSOUND_SESEP_SIGNATURE_2_INDEX] == REDSOUND_SESEP_SIGNATURE_2)) &&
         ((header->m_signature[REDSOUND_SESEP_SIGNATURE_3_INDEX] == REDSOUND_SESEP_SIGNATURE_3 &&
           (header->m_signature[REDSOUND_SESEP_SIGNATURE_4_INDEX] == REDSOUND_SESEP_SIGNATURE_4))))) {
        headerSize = header->m_sizeAndFlags & REDSOUND_SESEP_SIZE_MASK;
        copiedHeader = (RedSeSepHEAD*)RedNew(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, header, headerSize);
            result = copiedHeader->m_seNo;
            _EntryExecCommand(_SetSeSepData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
            _EntryExecCommand(_SeSepPlaySequence, autoID, result, pan, volume, pitch, 0, 0);
        } else {
            result = REDSOUND_SESEP_ID_NONE;
        }
    } else if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
        OSReport(sRedDriverSeSepHeaderErrorFmt, sRedDriverLogPrefix,
                 sRedDriverLogWarnColor, sRedDriverLogReset);
    }
    return autoID;
}

/*
 * --INFO--
 * PAL Address: 0x801bf604
 * PAL Size: 72b
 * EN Address: 0x80201528
 * EN Size: 72b
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
 * EN Address: 0x80201570
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeFadeOut(int seID, int fadeTime)
{
    _EntryExecCommand(_SeVolume, seID, 0, fadeTime, REDSOUND_SE_VOLUME_MODE_FADE_OUT, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf698
 * PAL Size: 80b
 * EN Address: 0x802015bc
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeVolume(int seID, int volume, int frameCount)
{
    _EntryExecCommand(_SeVolume, seID, volume, frameCount, REDSOUND_SE_VOLUME_MODE_NORMAL, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf6e8
 * PAL Size: 80b
 * EN Address: 0x8020160c
 * EN Size: 80b
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
 * EN Address: 0x8020165c
 * EN Size: 80b
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
 * EN Address: 0x802016ac
 * EN Size: 76b
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
 * EN Address: 0x802016f8
 * EN Size: 128b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetSeVolume(int seID, int mode)
{
    RedTrackDATA* track;

    track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
    while (1) {
        if (((u32)track->m_command != REDSOUND_TRACK_COMMAND_NONE) && ((seID == REDSOUND_SE_ID_ALL) || (seID == track->m_seId))) {
            if ((u32)track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
                if (mode == REDSOUND_SE_VOLUME_QUERY_DELTA) {
                    return track->m_mixVolumeDelta;
                }
                return track->m_mixVolume >> REDSOUND_FIXED_SHIFT;
            }
        }
        track++;
        if (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE))) {
            continue;
        }
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bf854
 * PAL Size: 108b
 * EN Address: 0x80201778
 * EN Size: 108b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReportSeLoop(int seID)
{
    RedTrackDATA* track;

    track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
    while (1) {
        if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
            (((seID == REDSOUND_SE_ID_ALL) || (seID == track->m_seId)) &&
             ((track->m_loopReport & REDSOUND_TRACK_LOOP_REPORT_ACTIVE) != 0))) {
            return 1;
        }
        track++;
        if (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE))) {
            continue;
        }
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bf8c0
 * PAL Size: 40b
 * EN Address: 0x802017e4
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::DisplaySePlayInfo()
{
	c_RedEntry.DisplaySePlayInfo();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: UNUSED
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::ClearSePlayLine()
{
	RedSoundCONTROL* control = RedSoundControlGet(REDSOUND_CONTROL_SE);
	RedTrackDATA* track = control->m_tracks;

	do {
		track->m_command = REDSOUND_TRACK_COMMAND_NONE;
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(control));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 80b
 * EN Address: UNUSED
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedTrackDATA* CRedDriver::GetSePlayTrack()
{
	RedTrackDATA* track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
	RedTrackDATA* trackEnd = RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE));

	do {
		if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
			return track;
		}
		track++;
	} while (track < trackEnd);
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bf8e8
 * PAL Size: 240b
 * EN Address: 0x8020180c
 * EN Size: 240b
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
	streamData = RedStreamDataGetBegin();
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamData->m_streamId == streamID))) {
			result = 1;
			break;
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());

	if (result == 0) {
		commandNow = RedExecCommandGetNow();
		command = RedExecCommandGetOld();
		while (commandNow != command) {
			if ((command->m_func != 0) && (command->m_func == _StreamPlay) &&
			    ((streamID == REDSOUND_STREAM_ID_ALL) ||
			     (streamID == RedExecCommandGetArg(command, REDSOUND_EXEC_COMMAND_ARG0)))) {
				result = 1;
				break;
			}
			command++;
			if (command == RedExecCommandGetEnd()) {
				command = RedExecCommandGetBegin();
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
 * EN Address: 0x802018fc
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetStreamPlayPoint(int streamID, int* playPoint, int* readPoint)
{
	RedStreamDATA* streamData;
	int found;

	found = 0;
	if (playPoint != 0) {
		*playPoint = 0;
	}
	if (readPoint != 0) {
		*readPoint = 0;
	}
	streamData = RedStreamDataGetBegin();
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) && (streamData->m_streamId == streamID)) {
			if (playPoint != 0) {
				*playPoint = streamData->m_fileCursor;
			}
			if (readPoint != 0) {
				*readPoint = streamData->m_readOffset;
			}
			found = 1;
			break;
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());
	return found;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 80b
 * EN Address: UNUSED
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedStreamDATA* CRedDriver::GetStreamPlayBlock(int streamID)
{
	RedStreamDATA* streamData = RedStreamDataGetBegin();

	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) && (streamData->m_streamId == streamID)) {
			return streamData;
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bfa74
 * PAL Size: 72b
 * EN Address: 0x80201998
 * EN Size: 72b
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
 * EN Address: 0x802019e0
 * EN Size: 96b
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
 * EN Address: 0x80201a40
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamVolume(int streamID, int volume, int frameCount)
{
    _EntryExecCommand(_StreamVolume, streamID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 80b
 * EN Address: UNUSED
 * EN Size: 80b
 * JP Address: TODO
 */
inline void CRedDriver::StreamPan(int streamID, int pan, int frameCount)
{
    _EntryExecCommand(_StreamPan, streamID, pan, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfb6c
 * PAL Size: 76b
 * EN Address: 0x80201a90
 * EN Size: 76b
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
 * EN Address: 0x80201adc
 * EN Size: 48b
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
 * EN Address: 0x80201b0c
 * EN Size: 72b
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
 * EN Address: 0x80201b54
 * EN Size: 48b
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
 * EN Address: 0x80201b84
 * EN Size: 276b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWaveData(int slot, int waveID, void* waveData, int waveSize)
{
    while (true) {
        if (m_WaveSettingStatus == REDSOUND_WORKER_IDLE) {
            break;
        }

        RedSleep(REDSOUND_THREAD_YIELD_SLEEP_US);
    }

    m_WaveSettingData.m_slot = reinterpret_cast<int*>(slot);
    m_WaveSettingData.m_waveId = waveID;
    m_WaveSettingData.m_waveData = waveData;

    if (waveSize == REDSOUND_WAVE_SIZE_AUTO) {
        RedWaveHeadWD* const waveHeader = (RedWaveHeadWD*)waveData;

        if ((waveHeader->m_signature[REDSOUND_WAVE_SIGNATURE_MAGIC0_INDEX] == REDSOUND_WAVE_SIGNATURE_MAGIC0) &&
            (waveHeader->m_signature[REDSOUND_WAVE_SIGNATURE_MAGIC1_INDEX] == REDSOUND_WAVE_SIGNATURE_MAGIC1)) {
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
 * EN Address: 0x80201c98
 * EN Size: 92b
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
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedWaveHeadWD* CRedDriver::GetWaveInfo(int waveID)
{
    return c_RedEntry.SearchWaveBase(waveID);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedDriver::CheckWaveEntry(int waveID)
{
    return c_RedEntry.SearchWaveSequence(waveID);
}

/*
 * --INFO--
 * PAL Address: 0x801bfdd0
 * PAL Size: 40b
 * EN Address: 0x80201cf4
 * EN Size: 40b
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
 * EN Address: UNUSED
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::DisplayMMemoryInfo()
{
    c_RedEntry.DisplayMMemoryInfo();
}

/*
 * --INFO--
 * PAL Address: 0x801BFDF8
 * PAL Size: 92b
 * EN Address: 0x80201d1c
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetReverb(int bank, int kind)
{
    ::SetReverb(bank, RedReverbModeDataGet(kind)->m_kind, RedReverbModeDataGet(kind)->m_params);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: UNUSED
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::SetReverb(int bank, int kind, int* params)
{
    ::SetReverb(bank, kind, params);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: UNUSED
 * EN Size: 32b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedReverbSize* CRedDriver::GetReverbInfo()
{
    return ::GetReverbInfo();
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
inline RedReverbDepth* CRedDriver::GetReverbDepth()
{
    return p_ReverbDepth;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: UNUSED
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::SetMute(unsigned int voiceNo, unsigned int mute)
{
    if (mute != 0) {
        RedMuteGetWord(voiceNo) |= RedMuteGetMask(voiceNo);
    } else {
        RedMuteGetWord(voiceNo) &= ~RedMuteGetMask(voiceNo);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 624b
 * EN Address: UNUSED
 * EN Size: 624b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::PlayWaveItem(int waveNo, int itemNo, int key, int pan, int volume)
{
    RedVoiceDATA* voice;
    RedWaveDATA* wave;
    RedWaveHeadWD* waveHead;
    int voiceIndex;

    waveHead = c_RedEntry.SearchWaveBase(waveNo);
    if ((waveHead == 0) || (itemNo < 0) || (itemNo >= waveHead->m_toneCount)) {
        return 0;
    }

    wave = RedWaveHeadGetWaveData(waveHead, itemNo);
    RedEditorTrackGet()->m_waveBankData = waveHead;
    RedEditorTrackGet()->m_waveData = wave;
    RedEditorTrackGet()->m_waveBase = waveHead->m_aramAddress;
    RedEditorTrackGet()->m_note.m_key = key;
    RedEditorTrackGet()->m_note.m_velocity = REDSOUND_VOLUME_MAX;
    RedEditorTrackGet()->m_note.m_allocFlags = REDSOUND_NOTE_ALLOC_DIRECT_MASK;
    RedEditorTrackGet()->m_trackNo = REDSOUND_EDITOR_VOICE_LEFT + 1;
    RedEditorTrackGet()->m_volume = REDSOUND_VOLUME_FULL;
    RedEditorTrackGet()->m_expression = REDSOUND_VOLUME_DEFAULT;
    RedEditorTrackGet()->m_mixVolume = volume << REDSOUND_FIXED_SHIFT;
    RedEditorTrackGet()->m_pan = pan << REDSOUND_FIXED_SHIFT;
    RedEditorTrackGet()->m_reverbDepth = RedReverbDepthGet(REDSOUND_REVERB_DEPTH_SE)->m_depth;
    RedEditorTrackGet()->m_portamentPitch = key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
    RedEditorTrackGet()->m_pitchBendRange = REDSOUND_SE_DEFAULT_PITCH_BEND_RANGE;
    RedEditorTrackGet()->m_voiceSwitch = REDSOUND_VOICE_SWITCH_DRY_STEREO;

    voice = EntryVoiceSearch(RedEditorTrackGet());
    if (voice == 0) {
        return 0;
    }

    voiceIndex = RedVoiceDataGetIndex(voice);
    *RedEditorVoiceGet(REDSOUND_EDITOR_VOICE_LEFT) = voiceIndex;
    *RedEditorVoiceGet(REDSOUND_EDITOR_VOICE_RIGHT) = 0;
    voice->m_track = RedEditorTrackGet();
    voice->m_waveData = wave;
    voice->m_trackVolume = &RedEditorTrackGet()->m_volume;
    voice->m_trackExpression = &RedEditorTrackGet()->m_expression;
    voice->m_trackPan = &RedEditorTrackGet()->m_pan;
    voice->m_stateFlags = REDSOUND_VOICE_STATE_PLAYING;
    voice->m_voiceSwitch = RedEditorTrackGet()->m_voiceSwitch;
    if ((wave->m_reverbMix != 0) && (wave->m_reverbMix != 1)) {
        voice->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_STEREO;
    }
    memcpy(&voice->m_adsr, wave->m_adsr, REDSOUND_ADSR_DATA_SIZE);
    voice->m_basePitch = key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
    if ((wave->m_flags & REDSOUND_WAVE_FLAG_USE_WAVE_KEY) != 0) {
        voice->m_basePitch = wave->m_splitKey << REDSOUND_PITCH_BASE_NOTE_SHIFT;
    }
    voice->m_pitch = WavePitchCompute(key, 0);
    voice->m_targetPitch = voice->m_pitch;
    voice->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
    voice->m_flags = REDSOUND_VOICE_FLAGS_START | REDSOUND_VOICE_FLAGS_ADPCM_DIRTY |
                     REDSOUND_VOICE_FLAGS_PITCH_DIRTY | REDSOUND_VOICE_FLAGS_ADSR_START;
    voice->m_active = REDSOUND_VOICE_ACTIVE_ON;
    voice->m_updateFlags = REDSOUND_VOICE_UPDATE_ALL;
    SetVoiceVolumeMix(voice, pan, volume);

    return voiceIndex;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 96b
 * EN Address: UNUSED
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedDriver::StopWaveItem()
{
    RedVoiceDATA* voice = RedVoiceDataGetBegin();

    do {
        if (voice->m_track == RedEditorTrackGet()) {
            voice->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
            voice->m_active = REDSOUND_VOICE_ACTIVE_OFF;
            voice->m_track = REDSOUND_VOICE_TRACK_NONE;
        }
        voice++;
    } while (voice < RedVoiceDataGetEnd());

    *RedEditorVoiceGet(REDSOUND_EDITOR_VOICE_LEFT) = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 96b
 * EN Address: UNUSED
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWavePitch(int pitch)
{
    int* voiceNo;

    RedEditorTrackGet()->m_pitch = pitch;
    voiceNo = RedEditorVoiceGetBegin();
    do {
        int voiceIndex = *voiceNo;
        if (voiceIndex != 0) {
            RedVoiceDataGet(voiceIndex)->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
        }
        voiceNo++;
    } while (voiceNo <= RedEditorVoiceGet(REDSOUND_EDITOR_VOICE_RIGHT));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 152b
 * EN Address: UNUSED
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWaveTune(int key, int fineTune)
{
    int* voiceNo;

    RedEditorTrackGet()->m_keyTranspose = key;
    RedEditorTrackGet()->m_note.m_key = key;
    RedEditorTrackGet()->m_fineTune = fineTune;
    RedEditorTrackGet()->m_portamentPitch = key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
    voiceNo = RedEditorVoiceGetBegin();
    do {
        int voiceIndex = *voiceNo;
        if (voiceIndex != 0) {
            RedVoiceDATA* voice = RedVoiceDataGet(voiceIndex);
            voice->m_basePitch = key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
            voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_PITCH;
        }
        voiceNo++;
    } while (voiceNo < RedEditorVoiceGetEnd());
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 160b
 * EN Address: UNUSED
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWaveAdsr(int attack, RedAdsrDATA* adsr)
{
    int* voiceNo;

    memcpy(&RedEditorTrackGet()->m_adsr, adsr, REDSOUND_TRACK_ADSR_SIZE);
    voiceNo = RedEditorVoiceGetBegin();
    do {
        int voiceIndex = *voiceNo;
        if (voiceIndex != 0) {
            RedVoiceDATA* voice = RedVoiceDataGet(voiceIndex);
            memcpy(&voice->m_adsr, adsr, REDSOUND_ADSR_DATA_SIZE);
            voice->m_flags |= REDSOUND_VOICE_FLAGS_ADSR_START;
        }
        voiceNo++;
    } while (voiceNo < RedEditorVoiceGetEnd());
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: UNUSED
 * EN Size: 176b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedDriver::WavePitchCompute(int key, int pitch)
{
    int basePitch = key << REDSOUND_PITCH_BASE_NOTE_SHIFT;
    int pitchOffset;
    RedWaveDATA* wave = RedEditorTrackGet()->m_waveData;

    if (wave != 0) {
        if ((wave->m_flags & REDSOUND_WAVE_FLAG_USE_WAVE_KEY) != 0) {
            basePitch = wave->m_splitKey << REDSOUND_PITCH_BASE_NOTE_SHIFT;
        }
        pitchOffset = RedEditorTrackGet()->m_keyTranspose + pitch;
        basePitch += RedEditorTrackGet()->m_pitch;
        return PitchCompute(basePitch, pitchOffset, wave->m_pitch, RedEditorTrackGet()->m_fineTune);
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 24b
 * EN Address: UNUSED
 * EN Size: 24b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedReverbModeData* CRedDriver::GetReverbModeTable(int mode)
{
    mode &= REDSOUND_REVERB_MODE_INDEX_MASK;
    return RedReverbModeDataGet(mode);
}

/*
 * --INFO--
 * PAL Address: 0x801bfe54
 * PAL Size: 80b
 * EN Address: 0x80201d78
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetReverbDepth(int bank, int depth, int frameCount)
{
    _EntryExecCommand(_SetReverbDepth, bank, depth, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfea4
 * PAL Size: 52b
 * EN Address: 0x80201dc8
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::TestProcess(int processType)
{
    switch (processType) {
    case REDSOUND_TEST_PROCESS_DMA_CHECK:
        _DMACheckProcess();
        break;
    }
}
