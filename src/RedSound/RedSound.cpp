#include "ffcc/RedSound/RedSound.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "global.h"

#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "string.h"
#include "dolphin/os.h"
#include "dolphin/ai.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
#include "dolphin/axart.h"

enum RedSoundLocalSize {
	REDSOUND_SOUND_OBJECT_SIZE = sizeof(CRedSound),
	REDSOUND_GLOBAL_INIT_WORK_SIZE = 3 * sizeof(int),
	REDSOUND_STANDBY_STATUS_COUNT = 0x40,
	REDSOUND_STANDBY_STATUS_SIZE = REDSOUND_STANDBY_STATUS_COUNT * sizeof(int),
	REDSOUND_STANDBY_STATUS_OFFSET = REDSOUND_GLOBAL_INIT_WORK_SIZE,
	REDSOUND_STANDBY_STATUS_ALLOC_SIZE = REDSOUND_STANDBY_STATUS_SIZE,
	REDSOUND_STREAM_BANK_COUNT = 4,
	REDSOUND_BSS_SIZE = REDSOUND_STANDBY_STATUS_OFFSET + REDSOUND_STANDBY_STATUS_ALLOC_SIZE,
	REDSOUND_STREAM_BANK_RESERVED14_SIZE = sizeof(int),
	REDSOUND_STREAM_BANK_ENTRY_SIZE = 0x40,
	REDSOUND_STREAM_BANK_SIZE = REDSOUND_STREAM_BANK_ENTRY_SIZE * REDSOUND_STREAM_BANK_COUNT,
	REDSOUND_STREAM_BANK_RESERVED18_SIZE =
	    REDSOUND_STREAM_BANK_ENTRY_SIZE - (5 * sizeof(int) + REDSOUND_STREAM_BANK_RESERVED14_SIZE),
	REDSOUND_AUTO_ID_MASK = 0x7FFFFFFF,
	REDSOUND_STREAM_BANK_FILE_SIZE_NONE = 0,
	REDSOUND_STREAM_BANK_POINT_NONE = 0,
	REDSOUND_STREAM_BANK_RESERVED_NONE = 0,
};

#define REDSOUND_STREAM_BANK_DATA_NONE ((RedStreamFile*)0)

enum RedSoundStringLayout {
	REDSOUND_MEMORY_SETTING_ERROR_SIZE = 0x33,
	REDSOUND_LOG_PREFIX_SIZE = 0x12,
	REDSOUND_AMEMORY_SETTING_ERROR_SIZE = 0x33,
	REDSOUND_AR_NOT_INITIALIZED_SIZE = 0x1f,
	REDSOUND_INIT_OK_SIZE = 0x23,
	REDSOUND_INIT_ERROR_SIZE = 0x28,
	REDSOUND_INVALID_STREAM_DATA_SIZE = 0x31,
	REDSOUND_DATE_SIZE = 0x0c,
	REDSOUND_TIME_SIZE = 0x09,
	REDSOUND_LOG_ERROR_COLOR_SIZE = 0x08,
	REDSOUND_LOG_RESET_SIZE = 0x05,
	REDSOUND_LOG_INFO_COLOR_SIZE = 0x08,
	REDSOUND_RODATA_STRING_SIZE = 0x128,
	REDSOUND_SDATA2_STRING_SIZE = 0x15,
};

enum RedSoundSmallDataLayout {
	REDSOUND_DRIVER_OBJECT_SIZE = sizeof(CRedDriver),
	REDSOUND_AUTO_ID_SIZE = sizeof(unsigned int),
	REDSOUND_STREAM_BANK_PTR_SIZE = sizeof(void*),
	REDSOUND_SBSS_PADDING_SIZE = sizeof(u32) - REDSOUND_DRIVER_OBJECT_SIZE,
};

enum RedStreamReadPointIndex {
	REDSOUND_STREAM_READ_POINT_READ = 0,
	REDSOUND_STREAM_READ_POINT_PLAY = 1,
};

#define RedStreamReadPointGet(readPoint, index) ((readPoint)[(index)])
#define RedStreamReadPointSet(readPoint, index, point) ((readPoint)[(index)] = (point))

struct RedSoundBssState {
	u8 m_globalInitWork[REDSOUND_GLOBAL_INIT_WORK_SIZE];
	int m_standbyStatus[REDSOUND_STANDBY_STATUS_COUNT];
};

struct RedSoundStreamBank {
	int m_streamId;
	RedStreamFile* m_streamData;
	int m_fileSize;
	int m_readPoint;
	int m_playPoint;
	int m_reserved14;
	u8 m_reserved18[REDSOUND_STREAM_BANK_RESERVED18_SIZE];
};

enum RedSoundStreamBankLayout {
	REDSOUND_STREAM_BANK_ID_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_streamId),
	REDSOUND_STREAM_BANK_DATA_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_streamData),
	REDSOUND_STREAM_BANK_FILE_SIZE_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_fileSize),
	REDSOUND_STREAM_BANK_READ_POINT_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_readPoint),
	REDSOUND_STREAM_BANK_PLAY_POINT_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_playPoint),
	REDSOUND_STREAM_BANK_RESERVED14_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_reserved14),
	REDSOUND_STREAM_BANK_RESERVED18_OFFSET = (unsigned int)&(((RedSoundStreamBank*)0)->m_reserved18),
};

struct RedSoundSmallDataState {
	CRedDriver m_driver;
	u8 m_driverPadding[REDSOUND_SBSS_PADDING_SIZE];
	volatile unsigned int m_autoId;
	RedSoundStreamBank* m_streamBank;
};

enum RedSoundSmallDataOffset {
	REDSOUND_SOUND_SBSS_DRIVER_OFFSET = (unsigned int)&(((RedSoundSmallDataState*)0)->m_driver),
	REDSOUND_SOUND_SBSS_AUTO_ID_OFFSET = (unsigned int)&(((RedSoundSmallDataState*)0)->m_autoId),
	REDSOUND_SOUND_SBSS_STREAM_BANK_OFFSET = (unsigned int)&(((RedSoundSmallDataState*)0)->m_streamBank),
	REDSOUND_SBSS_SIZE = sizeof(RedSoundSmallDataState),
};

// RedSound global linkage that is shared across Red* units.
CRedDriver c_Driver;
static int m_StandbyStatus[REDSOUND_STANDBY_STATUS_COUNT];
#define RedStandbyStatusGetBegin() (m_StandbyStatus)
#define RedStandbyStatusGet(index) (m_StandbyStatus[(index)])
#define RedStandbyStatusSet(slot, id) (*(slot) = (id))
#define RedStandbyStatusGetEnd() (m_StandbyStatus + REDSOUND_STANDBY_STATUS_COUNT)
volatile unsigned int m_AutoID;
#define RedAutoIDGet() (m_AutoID)
#define RedAutoIDInc() (m_AutoID++)
#define RedAutoIDApplyMask() (m_AutoID &= REDSOUND_AUTO_ID_MASK)
static RedSoundStreamBank* p_StreamBank;
#define RedSoundStreamBankGetBegin() (p_StreamBank)
#define RedSoundStreamBankSetBegin(bank) (p_StreamBank = (bank))
#define RedSoundStreamBankGetEnd() (p_StreamBank + REDSOUND_STREAM_BANK_COUNT)
#define RedSoundStreamBankSetId(bank, id) ((bank)->m_streamId = (id))
#define RedSoundStreamBankSetData(bank, data) ((bank)->m_streamData = (data))
#define RedSoundStreamBankSetFileSize(bank, size) ((bank)->m_fileSize = (size))
#define RedSoundStreamBankSetReadPoint(bank, point) ((bank)->m_readPoint = (point))
#define RedSoundStreamBankSetPlayPoint(bank, point) ((bank)->m_playPoint = (point))
#define RedSoundStreamBankSetReserved(bank, value) ((bank)->m_reserved14 = (value))
#define RedSoundStreamBankClear(bank)                                                                 \
	do {                                                                                            \
		RedSoundStreamBankSetId((bank), REDSOUND_STREAM_ID_NONE);                                  \
		RedSoundStreamBankSetData((bank), REDSOUND_STREAM_BANK_DATA_NONE);                         \
		RedSoundStreamBankSetFileSize((bank), REDSOUND_STREAM_BANK_FILE_SIZE_NONE);                 \
		RedSoundStreamBankSetReadPoint((bank), REDSOUND_STREAM_BANK_POINT_NONE);                    \
		RedSoundStreamBankSetPlayPoint((bank), REDSOUND_STREAM_BANK_POINT_NONE);                    \
	} while (0)
static const char sRedSoundMemorySettingError[] = "%s%s  Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n";
static const char sRedSoundLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char sRedSoundAMemorySettingError[] = "%s%sA-Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n";
static const char sRedSoundARNotInitialized[] = "%s\"AR\" was not initialized.%s\n";
static const char sRedSoundInitOk[] = "%s%sSound Driver Initialize OK.%s\n";
static const char sRedSoundInitError[] = "%s%sSound Driver Initialize ERROR !!%s\n";
static const char sRedSoundInvalidStreamData[] = "%s%sSTREAM : This data was not 'STREAM-DATA'.%s\n";
static const char sRedSoundDate[] = "Jun 17 2003";
static const char sRedSoundTime[] = "18:02:37";
static const char sRedSoundLogErrorColor[] = "\x1B[7;31m";
static const char sRedSoundLogReset[] = "\x1B[0m";
static const char sRedSoundLogInfoColor[] = "\x1B[4;34m";

STATIC_ASSERT(sizeof(m_StandbyStatus) == REDSOUND_STANDBY_STATUS_SIZE);
STATIC_ASSERT(sizeof(CRedSound) == REDSOUND_SOUND_OBJECT_SIZE);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_streamId) == REDSOUND_STREAM_BANK_ID_OFFSET);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_streamData) == REDSOUND_STREAM_BANK_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_fileSize) == REDSOUND_STREAM_BANK_FILE_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_readPoint) == REDSOUND_STREAM_BANK_READ_POINT_OFFSET);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_playPoint) == REDSOUND_STREAM_BANK_PLAY_POINT_OFFSET);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_reserved14) == REDSOUND_STREAM_BANK_RESERVED14_OFFSET);
STATIC_ASSERT(sizeof(((RedSoundStreamBank*)0)->m_reserved14) == REDSOUND_STREAM_BANK_RESERVED14_SIZE);
STATIC_ASSERT(offsetof(RedSoundStreamBank, m_reserved18) == REDSOUND_STREAM_BANK_RESERVED18_OFFSET);
STATIC_ASSERT(sizeof(((RedSoundStreamBank*)0)->m_reserved18) == REDSOUND_STREAM_BANK_RESERVED18_SIZE);
STATIC_ASSERT(REDSOUND_STREAM_BANK_RESERVED18_OFFSET + REDSOUND_STREAM_BANK_RESERVED18_SIZE ==
              REDSOUND_STREAM_BANK_ENTRY_SIZE);
STATIC_ASSERT(sizeof(RedSoundStreamBank) == REDSOUND_STREAM_BANK_ENTRY_SIZE);
STATIC_ASSERT(REDSOUND_STREAM_BANK_ENTRY_SIZE * REDSOUND_STREAM_BANK_COUNT == REDSOUND_STREAM_BANK_SIZE);
STATIC_ASSERT(offsetof(RedSoundBssState, m_globalInitWork) == 0);
STATIC_ASSERT(offsetof(RedSoundBssState, m_standbyStatus) == REDSOUND_STANDBY_STATUS_OFFSET);
STATIC_ASSERT(sizeof(RedSoundBssState) == REDSOUND_BSS_SIZE);
STATIC_ASSERT(REDSOUND_GLOBAL_INIT_WORK_SIZE + REDSOUND_STANDBY_STATUS_SIZE == REDSOUND_BSS_SIZE);
STATIC_ASSERT(REDSOUND_STANDBY_STATUS_SIZE == REDSOUND_STANDBY_STATUS_ALLOC_SIZE);
STATIC_ASSERT(sizeof(c_Driver) == REDSOUND_DRIVER_OBJECT_SIZE);
STATIC_ASSERT(sizeof(m_AutoID) == REDSOUND_AUTO_ID_SIZE);
STATIC_ASSERT(sizeof(p_StreamBank) == REDSOUND_STREAM_BANK_PTR_SIZE);
STATIC_ASSERT(offsetof(RedSoundSmallDataState, m_driver) == REDSOUND_SOUND_SBSS_DRIVER_OFFSET);
STATIC_ASSERT(offsetof(RedSoundSmallDataState, m_autoId) == REDSOUND_SOUND_SBSS_AUTO_ID_OFFSET);
STATIC_ASSERT(offsetof(RedSoundSmallDataState, m_streamBank) == REDSOUND_SOUND_SBSS_STREAM_BANK_OFFSET);
STATIC_ASSERT(sizeof(RedSoundSmallDataState) == REDSOUND_SBSS_SIZE);
STATIC_ASSERT(sizeof(c_Driver) + REDSOUND_SBSS_PADDING_SIZE + sizeof(m_AutoID) + sizeof(p_StreamBank) ==
              REDSOUND_SBSS_SIZE);
STATIC_ASSERT(sizeof(sRedSoundMemorySettingError) == REDSOUND_MEMORY_SETTING_ERROR_SIZE);
STATIC_ASSERT(sizeof(sRedSoundLogPrefix) == REDSOUND_LOG_PREFIX_SIZE);
STATIC_ASSERT(sizeof(sRedSoundAMemorySettingError) == REDSOUND_AMEMORY_SETTING_ERROR_SIZE);
STATIC_ASSERT(sizeof(sRedSoundARNotInitialized) == REDSOUND_AR_NOT_INITIALIZED_SIZE);
STATIC_ASSERT(sizeof(sRedSoundInitOk) == REDSOUND_INIT_OK_SIZE);
STATIC_ASSERT(sizeof(sRedSoundInitError) == REDSOUND_INIT_ERROR_SIZE);
STATIC_ASSERT(sizeof(sRedSoundInvalidStreamData) == REDSOUND_INVALID_STREAM_DATA_SIZE);
STATIC_ASSERT(sizeof(sRedSoundDate) == REDSOUND_DATE_SIZE);
STATIC_ASSERT(sizeof(sRedSoundTime) == REDSOUND_TIME_SIZE);
STATIC_ASSERT(sizeof(sRedSoundLogErrorColor) == REDSOUND_LOG_ERROR_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedSoundLogReset) == REDSOUND_LOG_RESET_SIZE);
STATIC_ASSERT(sizeof(sRedSoundLogInfoColor) == REDSOUND_LOG_INFO_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedSoundMemorySettingError) + sizeof(sRedSoundLogPrefix) +
                  sizeof(sRedSoundAMemorySettingError) + sizeof(sRedSoundARNotInitialized) +
                  sizeof(sRedSoundInitOk) + sizeof(sRedSoundInitError) + sizeof(sRedSoundInvalidStreamData) +
                  sizeof(sRedSoundDate) + sizeof(sRedSoundTime) ==
              REDSOUND_RODATA_STRING_SIZE);
STATIC_ASSERT(sizeof(sRedSoundLogErrorColor) + sizeof(sRedSoundLogReset) + sizeof(sRedSoundLogInfoColor) ==
              REDSOUND_SDATA2_STRING_SIZE);

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 160b
 * EN Address: UNUSED
 * EN Size: 160b
 * JP Address: TODO
 */
static RedSoundStreamBank* _SearchEmptyStreamBank()
{
	RedSoundStreamBank* bank = RedSoundStreamBankGetBegin();
	RedSoundStreamBank* bankEnd = RedSoundStreamBankGetEnd();

	do {
		if (bank->m_streamId == REDSOUND_STREAM_ID_NONE) {
			return bank;
		}
		if (c_Driver.StreamPlayState(bank->m_streamId) == REDSOUND_STREAM_ID_NONE) {
			RedSoundStreamBankClear(bank);
			return bank;
		}
		bank++;
	} while (bank < bankEnd);

	return 0;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 88b
 * EN Address: UNUSED
 * EN Size: 88b
 * JP Address: TODO
 */
static RedSoundStreamBank* _SearchStreamBank(int streamId)
{
	RedSoundStreamBank* bank = RedSoundStreamBankGetBegin();
	RedSoundStreamBank* bankEnd = RedSoundStreamBankGetEnd();

	do {
		if ((bank->m_streamId != REDSOUND_STREAM_ID_NONE) && (bank->m_streamId == streamId)) {
			return bank;
		}
		bank++;
	} while (bank < bankEnd);

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801cca34
 * PAL Size: 4b
 * EN Address: 0x8020e958
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
CRedSound::CRedSound()
{
	// TODO
}
/*
 * --INFO--
 * PAL Address: 0x801cca38
 * PAL Size: 72b
 * EN Address: 0x8020e95c
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
CRedSound::~CRedSound()
{
}
/*
 * --INFO--
 * PAL Address: 0x801cca80
 * PAL Size: 44b
 * EN Address: 0x8020e9a4
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CRedSound::GetAutoID()
{
	do {
		RedAutoIDInc();
		RedAutoIDApplyMask();
	} while ((int)RedAutoIDGet() == 0);

	return RedAutoIDGet();
}
/*
 * --INFO--
 * PAL Address: 0x801ccaac
 * PAL Size: 80b
 * EN Address: 0x8020e9d0
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
int* CRedSound::EntryStandbyID(int id)
{
	int* slot = RedStandbyStatusGetBegin();
	do {
		if (*slot == 0) {
			RedStandbyStatusSet(slot, id);
			return slot;
		}
		slot++;
	} while (slot < RedStandbyStatusGetEnd());

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801ccafc
 * PAL Size: 528b
 * EN Address: 0x8020ea20
 * EN Size: 528b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::Init(void* mainBuffer, int mainBufferSize, int aramBuffer, int aramBufferSize)
{
	memset(RedStandbyStatusGetBegin(), 0, REDSOUND_STANDBY_STATUS_SIZE);

	if (mainBufferSize > 0 && aramBufferSize > 0) {
		if ((((u32)mainBuffer & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0) ||
		    (((u32)mainBufferSize & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0)) {
			if (RedReportPrintIsEnabled()) {
				OSReport(sRedSoundMemorySettingError, sRedSoundLogPrefix, sRedSoundLogErrorColor, (u32)mainBuffer,
				         mainBufferSize, sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if ((((u32)aramBuffer & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0) ||
		    (((u32)aramBufferSize & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0)) {
			if (RedReportPrintIsEnabled()) {
				OSReport(sRedSoundAMemorySettingError,
				         sRedSoundLogPrefix, sRedSoundLogErrorColor, aramBuffer,
				         aramBufferSize, sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if (ARCheckInit() == 0) {
			if (RedReportPrintIsEnabled()) {
				OSReport(sRedSoundARNotInitialized,
				         sRedSoundLogPrefix, sRedSoundLogErrorColor,
				         sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		AIReset();
		AIInit(0);
		AXInit();
		AXARTInit();
        c_RedMemory.Init((int)mainBuffer, mainBufferSize, aramBuffer, aramBufferSize);
		c_RedEntry.Init();
		Start();
		c_Driver.Init();

		if (RedReportPrintIsEnabled()) {
			OSReport(sRedSoundInitOk,
			         sRedSoundLogPrefix, sRedSoundLogInfoColor, sRedSoundLogReset);
			fflush(__files + 1);
		}
	} else {
		mainBufferSize = 0;

		if (RedReportPrintIsEnabled()) {
			OSReport(sRedSoundInitError,
			         sRedSoundLogPrefix, sRedSoundLogErrorColor,
			         sRedSoundLogReset);
			fflush(__files + 1);
		}
	}

	return mainBufferSize;
}
/*
 * --INFO--
 * PAL Address: 0x801ccd0c
 * PAL Size: 56b
 * EN Address: 0x8020ec30
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::Start()
{
	RedSoundStreamBankSetBegin((RedSoundStreamBank*)RedNew(REDSOUND_STREAM_BANK_SIZE));
	memset(RedSoundStreamBankGetBegin(), 0, REDSOUND_STREAM_BANK_SIZE);
}
/*
 * --INFO--
 * PAL Address: 0x801ccd44
 * PAL Size: 44b
 * EN Address: 0x8020ec68
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::End()
{
	c_Driver.End();
	AXARTQuit();
	AXQuit();
}
/*
 * --INFO--
 * PAL Address: 0x801ccd70
 * PAL Size: 36b
 * EN Address: 0x8020ec94
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::GetProgramTime()
{
	return c_Driver.GetProgramTime();
}
/*
 * --INFO--
 * PAL Address: 0x801ccd94
 * PAL Size: 8b
 * EN Address: 0x8020ecb8
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ReportPrint(int debugFlag)
{
	RedReportPrintSet(debugFlag);
}
/*
 * --INFO--
 * PAL Address: 0x801ccd9c
 * PAL Size: 152b
 * EN Address: 0x8020ecc0
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::ReportStandby(int id)
{
	int statusIndex;
	int standbyCount = 0;

	if (id == 0) {
		statusIndex = 0;
		do {
			if (RedStandbyStatusGet(statusIndex) != 0) {
				standbyCount++;
				break;
			}
			statusIndex++;
	} while (statusIndex < REDSOUND_STANDBY_STATUS_COUNT);
	} else {
		statusIndex = 0;
		do {
			if (id == RedStandbyStatusGet(statusIndex)) {
				standbyCount++;
				break;
			}
			statusIndex++;
		} while (statusIndex < REDSOUND_STANDBY_STATUS_COUNT);
	}

	return standbyCount;
}
/*
 * --INFO--
 * PAL Address: 0x801cce34
 * PAL Size: 88b
 * EN Address: 0x8020ed58
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::DMAEntry(int type, int src, int dst, int length, int flags, RedDmaCallback callback, void* userData)
{
	return RedDmaEntry(type, src, dst, length, flags, callback, userData);
}
/*
 * --INFO--
 * PAL Address: 0x801cce8c
 * PAL Size: 40b
 * EN Address: 0x8020edb0
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::DMACheck(int id)
{
	return RedDmaSearchID(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cceb4
 * PAL Size: 44b
 * EN Address: 0x8020edd8
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetSoundMode(int mode)
{
	c_Driver.SetSoundMode(mode);
}
/*
 * --INFO--
 * PAL Address: 0x801ccee0
 * PAL Size: 36b
 * EN Address: 0x8020ee04
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::GetSoundMode()
{
	return c_Driver.GetSoundMode();
}
/*
 * --INFO--
 * PAL Address: 0x801ccf04
 * PAL Size: 52b
 * EN Address: 0x8020ee28
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetReverb(int bank, int kind)
{
	c_Driver.SetReverb(bank, kind);
}
/*
 * --INFO--
 * PAL Address: 0x801ccf38
 * PAL Size: 60b
 * EN Address: 0x8020ee5c
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetReverbDepth(int bank, int depth, int frameCount)
{
	c_Driver.SetReverbDepth(bank, depth, frameCount);
}
/*
 * --INFO--
 * PAL Address: 0x801ccf74
 * PAL Size: 44b
 * EN Address: 0x8020ee98
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetMusicData(void* musicData)
{
	c_Driver.SetMusicData(musicData);
}
/*
 * --INFO--
 * PAL Address: 0x801ccfa0
 * PAL Size: 44b
 * EN Address: 0x8020eec4
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::ReentryMusicData(int bank)
{
	return c_Driver.ReentryMusicData(bank);
}
/*
 * --INFO--
 * PAL Address: 0x801ccfcc
 * PAL Size: 44b
 * EN Address: 0x8020eef0
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicStop(int id)
{
	c_Driver.MusicStop(id);
}
/*
 * --INFO--
 * PAL Address: 0x801ccff8
 * PAL Size: 60b
 * EN Address: 0x8020ef1c
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicPlay(int id, int vol, int fadeTime)
{
	c_Driver.MusicPlay(id, vol, fadeTime);
}
/*
 * --INFO--
 * PAL Address: 0x801cd034
 * PAL Size: 60b
 * EN Address: 0x8020ef58
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicCrossPlay(int id, int vol, int fadeTime)
{
	c_Driver.MusicCrossPlay(id, vol, fadeTime);
}
/*
 * --INFO--
 * PAL Address: 0x801cd070
 * PAL Size: 60b
 * EN Address: 0x8020ef94
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicNextPlay(int id, int vol, int fadeTime)
{
	c_Driver.MusicNextPlay(id, vol, fadeTime);
}
/*
 * --INFO--
 * PAL Address: 0x801cd0ac
 * PAL Size: 44b
 * EN Address: 0x8020efd0
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicMasterVolume(int volume)
{
	c_Driver.MusicMasterVolume(volume);
}
/*
 * --INFO--
 * PAL Address: 0x801cd0d8
 * PAL Size: 52b
 * EN Address: 0x8020effc
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicFadeOut(int id, int fadeTime)
{
	c_Driver.MusicFadeOut(id, fadeTime);
}
/*
 * --INFO--
 * PAL Address: 0x801cd10c
 * PAL Size: 60b
 * EN Address: 0x8020f030
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::MusicVolume(int id, int volume, int fadeTime)
{
	c_Driver.MusicVolume(id, volume, fadeTime);
}
/*
 * --INFO--
 * PAL Address: 0x801cd148
 * PAL Size: 44b
 * EN Address: 0x8020f06c
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetMusicPhraseStop(int id)
{
	c_Driver.SetMusicPhraseStop(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd174
 * PAL Size: 52b
 * EN Address: 0x8020f098
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetSeBlockData(int bank, void* blockData)
{
	c_Driver.SetSeBlockData(bank, blockData);
}
/*
 * --INFO--
 * PAL Address: 0x801cd1a8
 * PAL Size: 44b
 * EN Address: 0x8020f0cc
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetSeSepData(void* seSepData)
{
	c_Driver.SetSeSepData(seSepData);
}
/*
 * --INFO--
 * PAL Address: 0x801cd1d4
 * PAL Size: 44b
 * EN Address: 0x8020f0f8
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ClearSeSepData(int id)
{
	c_Driver.ClearSeSepData(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd200
 * PAL Size: 68b
 * EN Address: 0x8020f124
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ClearSeSepDataMG(int bank, int sep, int group, int kind)
{
	c_Driver.ClearSeSepDataMG(bank, sep, group, kind);
}
/*
 * --INFO--
 * PAL Address: 0x801cd244
 * PAL Size: 44b
 * EN Address: 0x8020f168
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::ReentrySeSepData(int id)
{
	return c_Driver.ReentrySeSepData(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd270
 * PAL Size: 44b
 * EN Address: 0x8020f194
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::SePlayState(int id)
{
	return c_Driver.SePlayState(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd29c
 * PAL Size: 44b
 * EN Address: 0x8020f1c0
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SeStop(int id)
{
	c_Driver.SeStop(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd2c8
 * PAL Size: 68b
 * EN Address: 0x8020f1ec
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SeStopMG(int bank, int sep, int group, int kind)
{
	c_Driver.SeStopMG(bank, sep, group, kind);
}
/*
 * --INFO--
 * PAL Address: 0x801cd30c
 * PAL Size: 108b
 * EN Address: 0x8020f230
 * EN Size: 108b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::SePlay(int seID, int sepID, int pan, int volume, int pitch)
{
	int autoID = GetAutoID();
	c_Driver.SePlay(seID, sepID, autoID, pan, volume, pitch);
	return autoID;
}
/*
 * --INFO--
 * PAL Address: 0x801cd378
 * PAL Size: 44b
 * EN Address: 0x8020f29c
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SeMasterVolume(int volume)
{
	c_Driver.SeMasterVolume(volume);
}
/*
 * --INFO--
 * PAL Address: 0x801cd3a4
 * PAL Size: 52b
 * EN Address: 0x8020f2c8
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SeFadeOut(int seID, int frameCount)
{
	c_Driver.SeFadeOut(seID, frameCount);
}
/*
 * --INFO--
 * PAL Address: 0x801cd3d8
 * PAL Size: 60b
 * EN Address: 0x8020f2fc
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SeVolume(int seID, int volume, int frameCount)
{
	c_Driver.SeVolume(seID, volume, frameCount);
}
/*
 * --INFO--
 * PAL Address: 0x801cd414
 * PAL Size: 60b
 * EN Address: 0x8020f338
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SePan(int seID, int pan, int frameCount)
{
	c_Driver.SePan(seID, pan, frameCount);
}
/*
 * --INFO--
 * PAL Address: 0x801cd450
 * PAL Size: 60b
 * EN Address: 0x8020f374
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SePitch(int seID, int pitch, int frameCount)
{
	c_Driver.SePitch(seID, pitch, frameCount);
}
/*
 * --INFO--
 * PAL Address: 0x801cd48c
 * PAL Size: 52b
 * EN Address: 0x8020f3b0
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SePause(int seID, int pause)
{
	c_Driver.SePause(seID, pause);
}
/*
 * --INFO--
 * PAL Address: 0x801cd4c0
 * PAL Size: 52b
 * EN Address: 0x8020f3e4
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::GetSeVolume(int seID, int outVolume)
{
	return c_Driver.GetSeVolume(seID, outVolume);
}
/*
 * --INFO--
 * PAL Address: 0x801cd4f4
 * PAL Size: 44b
 * EN Address: 0x8020f418
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::ReportSeLoop(int mode)
{
	return c_Driver.ReportSeLoop(mode);
}
/*
 * --INFO--
 * PAL Address: 0x801cd520
 * PAL Size: 36b
 * EN Address: 0x8020f444
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::DisplaySePlayInfo()
{
	c_Driver.DisplaySePlayInfo();
}
/*
 * --INFO--
 * PAL Address: 0x801cd544
 * PAL Size: 44b
 * EN Address: 0x8020f468
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::StreamPlayState(int streamID)
{
	return c_Driver.StreamPlayState(streamID);
}
/*
 * --INFO--
 * PAL Address: 0x801cd570
 * PAL Size: 60b
 * EN Address: 0x8020f494
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::GetStreamPlayPoint(int streamID, int* playPoint, int* readPoint)
{
	c_Driver.GetStreamPlayPoint(streamID, playPoint, readPoint);
}
/*
 * --INFO--
 * PAL Address: 0x801cd5ac
 * PAL Size: 44b
 * EN Address: 0x8020f4d0
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::StreamStop(int streamID)
{
	c_Driver.StreamStop(streamID);
}
/*
 * --INFO--
 * PAL Address: 0x801cd5d8
 * PAL Size: 224b
 * EN Address: 0x8020f4fc
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::StreamPlay(void* data, int fileSize, int pan, int volume)
{
	int id = 0;
	RedStreamHEAD* streamHeader = (RedStreamHEAD*)data;

	if (streamHeader->m_signature[REDSOUND_STREAM_SIGNATURE_0_INDEX] == REDSOUND_STREAM_SIGNATURE_0 &&
	    streamHeader->m_signature[REDSOUND_STREAM_SIGNATURE_1_INDEX] == REDSOUND_STREAM_SIGNATURE_1 &&
	    streamHeader->m_signature[REDSOUND_STREAM_SIGNATURE_2_INDEX] == REDSOUND_STREAM_SIGNATURE_2) {
		id = GetAutoID();
		c_Driver.StreamPlay(id, data, fileSize, pan, volume);
	} else if (RedReportPrintIsEnabled()) {
		OSReport(sRedSoundInvalidStreamData,
		         sRedSoundLogPrefix, sRedSoundLogErrorColor,
		         sRedSoundLogReset);
		fflush(__files + 1);
	}

	return id;
}
/*
 * --INFO--
 * PAL Address: 0x801cd6b8
 * PAL Size: 60b
 * EN Address: 0x8020f5dc
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::StreamVolume(int streamID, int volume, int frameCount)
{
	c_Driver.StreamVolume(streamID, volume, frameCount);
}
/*
 * --INFO--
 * PAL Address: 0x801cd6f4
 * PAL Size: 52b
 * EN Address: 0x8020f618
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::StreamPause(int streamID, int pause)
{
	c_Driver.StreamPause(streamID, pause);
}
/*
 * --INFO--
 * PAL Address: 0x801cd728
 * PAL Size: 124b
 * EN Address: 0x8020f64c
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CRedSound::SetWaveData(int waveID, void* waveData, int waveSize)
{
	unsigned int id = GetAutoID();
	int* slot = EntryStandbyID(id);
	if (slot != 0) {
		c_Driver.SetWaveData((int)slot, waveID, waveData, waveSize);
	}
	return id;
}
/*
 * --INFO--
 * PAL Address: 0x801cd7a4
 * PAL Size: 44b
 * EN Address: 0x8020f6c8
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ClearWaveData(int id)
{
	c_Driver.ClearWaveData(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd7d0
 * PAL Size: 68b
 * EN Address: 0x8020f6f4
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ClearWaveDataM(int bank, int sep, int group, int kind)
{
	c_Driver.ClearWaveDataM(bank, sep, group, kind);
}
/*
 * --INFO--
 * PAL Address: 0x801cd814
 * PAL Size: 44b
 * EN Address: 0x8020f738
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ClearWaveBank(int id)
{
	c_Driver.ClearWaveBank(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd840
 * PAL Size: 44b
 * EN Address: 0x8020f764
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::ReentryWaveData(int id)
{
	return c_Driver.ReentryWaveData(id);
}
/*
 * --INFO--
 * PAL Address: 0x801cd86c
 * PAL Size: 36b
 * EN Address: 0x8020f790
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::DisplayWaveInfo()
{
	c_Driver.DisplayWaveInfo();
}
/*
 * --INFO--
 * PAL Address: 0x801cd890
 * PAL Size: 44b
 * EN Address: 0x8020f7b4
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::TestProcess(int mode)
{
	c_Driver.TestProcess(mode);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::ClearMusicData(int musicId)
{
	c_Driver.ClearMusicData(musicId);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 */
inline int CRedSound::MusicPlayState(int id)
{
	return c_Driver.MusicPlayState(id);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: UNUSED
 * EN Size: 60b
 * JP Address: TODO
 */
inline void CRedSound::MusicPlay(void* data, int vol, int fadeTime)
{
	c_Driver.MusicPlay(data, vol, fadeTime);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: UNUSED
 * EN Size: 60b
 * JP Address: TODO
 */
inline void CRedSound::MusicCrossPlay(void* data, int vol, int fadeTime)
{
	c_Driver.MusicCrossPlay(data, vol, fadeTime);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: UNUSED
 * EN Size: 60b
 * JP Address: TODO
 */
inline void CRedSound::MusicNextPlay(void* data, int vol, int fadeTime)
{
	c_Driver.MusicNextPlay(data, vol, fadeTime);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 */
inline void CRedSound::MusicPitch(int pitch, int frameCount)
{
	c_Driver.MusicPitch(pitch, frameCount);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 */
inline void CRedSound::MusicTempo(int tempo, int frameCount)
{
	c_Driver.MusicTempo(tempo, frameCount);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 */
inline void CRedSound::MusicPause(int musicId, int pause)
{
	c_Driver.MusicPause(musicId, pause);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 */
inline void CRedSound::SeStopG(int group)
{
	c_Driver.SeStopG(group);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 100b
 * EN Address: UNUSED
 * EN Size: 100b
 * JP Address: TODO
 */
inline int CRedSound::SePlay(void* data, int pan, int volume, int pitch)
{
	int autoID = GetAutoID();
	c_Driver.SePlay(data, autoID, pan, volume, pitch);
	return autoID;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 180b
 * EN Address: UNUSED
 * EN Size: 180b
 * JP Address: TODO
 */
inline int CRedSound::GetSeUsedWave(int bank, int seNo)
{
	int waveNo = REDSOUND_SESEP_ID_NONE;

	if ((bank >= 0) && (bank < REDSOUND_SE_BLOCK_BANK_COUNT)) {
		RedSeBlockHEAD* block = RedSeBlockDataGet(bank);
		if ((block != 0) && (seNo >= 0) && (seNo < block->m_seCount)) {
			int* entries = block->m_entries;
			if (entries[seNo] != REDSOUND_SE_BLOCK_ENTRY_EMPTY) {
				RedSeINFO* info = RedSeBlockGetInfoFromEntries(block, entries, seNo);
				waveNo = RedSeInfoGetWaveNo(info);
			}
		}
	}

	return waveNo;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 48b
 * EN Address: UNUSED
 * EN Size: 48b
 * JP Address: TODO
 */
inline int CRedSound::GetSeUsedWave(void* seSepData)
{
	RedSeSepHEAD* seSepHead = (RedSeSepHEAD*)seSepData;

	return RedSeSepGetWaveNo(seSepHead);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 244b
 * EN Address: UNUSED
 * EN Size: 244b
 * JP Address: TODO
 */
inline int CRedSound::StreamStandby(void* streamHeader, int fileSize)
{
	int streamId = REDSOUND_STREAM_ID_NONE;
	RedStreamHEAD* header = reinterpret_cast<RedStreamHEAD*>(streamHeader);

	if (header->m_signature[REDSOUND_STREAM_SIGNATURE_0_INDEX] == REDSOUND_STREAM_SIGNATURE_0 &&
	    header->m_signature[REDSOUND_STREAM_SIGNATURE_1_INDEX] == REDSOUND_STREAM_SIGNATURE_1 &&
	    header->m_signature[REDSOUND_STREAM_SIGNATURE_2_INDEX] == REDSOUND_STREAM_SIGNATURE_2) {
		RedSoundStreamBank* bank = _SearchEmptyStreamBank();
		if (bank != 0) {
			streamId = GetAutoID();
			RedSoundStreamBankSetId(bank, streamId);
			RedSoundStreamBankSetData(bank, reinterpret_cast<RedStreamFile*>(streamHeader));
			RedSoundStreamBankSetFileSize(bank, fileSize);
			RedSoundStreamBankSetReadPoint(bank, REDSOUND_STREAM_BANK_POINT_NONE);
			RedSoundStreamBankSetPlayPoint(bank, REDSOUND_STREAM_BANK_POINT_NONE);
			RedSoundStreamBankSetReserved(bank, REDSOUND_STREAM_BANK_RESERVED_NONE);
		}
	} else if (RedReportPrintIsEnabled()) {
		OSReport(sRedSoundInvalidStreamData,
		         sRedSoundLogPrefix, sRedSoundLogErrorColor,
		         sRedSoundLogReset);
		fflush(__files + 1);
	}

	return streamId;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: UNUSED
 * EN Size: 112b
 * JP Address: TODO
 */
inline int CRedSound::StreamPlay(int streamId, int pan, int volume)
{
	RedSoundStreamBank* bank = _SearchStreamBank(streamId);

	if (bank != 0) {
		c_Driver.StreamPlay(streamId, bank->m_streamData, bank->m_fileSize, pan, volume);
		return streamId;
	}

	return REDSOUND_STREAM_ID_NONE;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: UNUSED
 * EN Size: 60b
 * JP Address: TODO
 */
inline void CRedSound::StreamPan(int streamID, int pan, int frameCount)
{
	c_Driver.StreamPan(streamID, pan, frameCount);
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
inline void CRedSound::Sleep(int microseconds)
{
	RedSleep(microseconds);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::GetMasterTime()
{
	return c_Driver.GetMasterTime();
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
inline void CRedSound::SetDMAMode(int mode)
{
	RedSetDMAMode(mode);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedReverbSize* CRedSound::GetReverbInfo()
{
	return c_Driver.GetReverbInfo();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedReverbDepth* CRedSound::GetReverbDepth()
{
	return c_Driver.GetReverbDepth();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: UNUSED
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::SetReverb(int bank, int kind, int* params)
{
	c_Driver.SetReverb(bank, kind, params);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::SetMute(unsigned int voiceNo, unsigned int mute)
{
	c_Driver.SetMute(voiceNo, mute);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::DisplayMMemoryInfo()
{
	c_Driver.DisplayMMemoryInfo();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::CheckMusicEntry(int musicId)
{
	return c_Driver.CheckMusicEntry(musicId);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::SetMusicFastSpeed(int speed)
{
	c_Driver.SetMusicFastSpeed(speed);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::CheckMusicPhraseStop()
{
	return c_Driver.CheckMusicPhraseStop();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::DisplayMusicInfo()
{
	c_Driver.DisplayMusicInfo();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::CheckSeSepEntry(int sepId)
{
	return c_Driver.CheckSeSepEntry(sepId);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::ClearSePlayLine()
{
	c_Driver.ClearSePlayLine();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedStreamDATA* CRedSound::GetStreamPlayBlock(int streamId)
{
	return c_Driver.GetStreamPlayBlock(streamId);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 336b
 * EN Address: UNUSED
 * EN Size: 336b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::GetStreamReadPoint(int streamId, int* readPoint)
{
	RedSoundStreamBank* bank = _SearchStreamBank(streamId);

	if (readPoint != 0) {
		RedStreamReadPointSet(readPoint, REDSOUND_STREAM_READ_POINT_READ, 0);
		RedStreamReadPointSet(readPoint, REDSOUND_STREAM_READ_POINT_PLAY, 0);
	}

	if (bank != 0) {
		int playPoint;
		int currentReadPoint;
		int delta;

		if (c_Driver.GetStreamPlayPoint(streamId, &playPoint, &currentReadPoint) != 0) {
			if (readPoint != 0) {
				if (currentReadPoint >= bank->m_readPoint) {
					delta = currentReadPoint - bank->m_readPoint;
				} else {
					delta = bank->m_fileSize - bank->m_readPoint + currentReadPoint;
				}
				RedStreamReadPointSet(readPoint, REDSOUND_STREAM_READ_POINT_READ, delta);
				if (playPoint >= bank->m_playPoint) {
					RedStreamReadPointSet(readPoint, REDSOUND_STREAM_READ_POINT_PLAY, playPoint - bank->m_playPoint);
				}
			}
			RedSoundStreamBankSetReadPoint(bank, currentReadPoint);
			RedSoundStreamBankSetPlayPoint(bank, playPoint);
		} else {
			if (readPoint != 0) {
				RedStreamReadPointSet(readPoint, REDSOUND_STREAM_READ_POINT_READ, bank->m_fileSize - bank->m_readPoint);
				RedStreamReadPointSet(readPoint, REDSOUND_STREAM_READ_POINT_PLAY, bank->m_fileSize - bank->m_playPoint);
			}
			RedSoundStreamBankClear(bank);
		}
	}
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedTrackDATA* CRedSound::GetSePlayTrack()
{
	return c_Driver.GetSePlayTrack();
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
inline int CRedSound::SearchWaveSequence(int waveNo)
{
	return c_RedEntry.SearchWaveSequence(waveNo);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedWaveHeadWD* CRedSound::GetWaveInfo(int waveNo)
{
	return c_Driver.GetWaveInfo(waveNo);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::CheckWaveEntry(int waveNo)
{
	return c_Driver.CheckWaveEntry(waveNo);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedReverbModeData* CRedSound::GetReverbModeTable(int mode)
{
	return c_Driver.GetReverbModeTable(mode);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 28b
 * EN Address: UNUSED
 * EN Size: 28b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::GetMakeTime(char** date, char** time)
{
	*date = (char*)sRedSoundDate;
	*time = (char*)sRedSoundTime;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::GetMainBufferAddress()
{
	return c_RedMemory.GetMainBufferAddress();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::GetMainBufferSize()
{
	return c_RedMemory.GetMainBufferSize();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedMemoryBlock* CRedSound::GetMainBankAddress()
{
	return c_RedMemory.GetMainBankAddress();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::GetABufferAddress()
{
	return c_RedMemory.GetABufferAddress();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline RedMemoryBlock* CRedSound::GetABankAddress()
{
	return c_RedMemory.GetABankAddress();
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
inline RedSoundCONTROL* CRedSound::GetControlAddress()
{
	return RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
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
inline RedVoiceDATA* CRedSound::GetVoiceAddress()
{
	return RedVoiceDataGetBegin();
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
inline int CRedSound::PlayWaveItem(int waveNo, int itemNo, int key, int pan, int volume)
{
	return c_Driver.PlayWaveItem(waveNo, itemNo, key, pan, volume);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: UNUSED
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::StopWaveItem()
{
	c_Driver.StopWaveItem();
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: UNUSED
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::SetWavePitch(int pitch)
{
	c_Driver.SetWavePitch(pitch);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::SetWaveTune(int key, int fineTune)
{
	c_Driver.SetWaveTune(key, fineTune);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CRedSound::SetWaveAdsr(int attack, RedAdsrDATA* adsr)
{
	c_Driver.SetWaveAdsr(attack, adsr);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 52b
 * EN Address: UNUSED
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CRedSound::WavePitchCompute(int key, int pitch)
{
	return c_Driver.WavePitchCompute(key, pitch);
}
