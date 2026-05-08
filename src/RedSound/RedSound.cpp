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
	REDSOUND_SOUND_OBJECT_SIZE = 0x01,
	REDSOUND_STANDBY_STATUS_COUNT = 0x40,
	REDSOUND_STANDBY_STATUS_SIZE = REDSOUND_STANDBY_STATUS_COUNT * sizeof(int),
	REDSOUND_STANDBY_STATUS_OFFSET = 0x0C,
	REDSOUND_STANDBY_STATUS_ALLOC_SIZE = 0x100,
	REDSOUND_BSS_SIZE = 0x10C,
	REDSOUND_STREAM_BANK_SIZE = 0x100,
};

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
	REDSOUND_SOUND_SBSS_DRIVER_OFFSET = 0x00,
	REDSOUND_DRIVER_OBJECT_SIZE = 0x01,
	REDSOUND_AUTO_ID_SIZE = 0x04,
	REDSOUND_SOUND_SBSS_AUTO_ID_OFFSET = 0x04,
	REDSOUND_STREAM_BANK_PTR_SIZE = 0x04,
	REDSOUND_SOUND_SBSS_STREAM_BANK_OFFSET = 0x08,
	REDSOUND_SBSS_PADDING_SIZE = 0x03,
	REDSOUND_SBSS_SIZE = 0x0c,
};

struct RedSoundBssState {
	u8 m_initPadding[REDSOUND_STANDBY_STATUS_OFFSET];
	int m_standbyStatus[REDSOUND_STANDBY_STATUS_COUNT];
};

struct RedSoundSmallDataState {
	CRedDriver m_driver;
	u8 m_driverPadding[REDSOUND_SBSS_PADDING_SIZE];
	volatile unsigned int m_autoId;
	void* m_streamBank;
};

// RedSound global linkage that is shared across Red* units.
CRedDriver c_Driver;
static int m_StandbyStatus[REDSOUND_STANDBY_STATUS_COUNT];
volatile unsigned int m_AutoID;
static void* p_StreamBank;
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
STATIC_ASSERT(offsetof(RedSoundBssState, m_standbyStatus) == REDSOUND_STANDBY_STATUS_OFFSET);
STATIC_ASSERT(sizeof(RedSoundBssState) == REDSOUND_BSS_SIZE);
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
 * PAL Address: 0x801cca34
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CRedSound::GetAutoID()
{
	do {
		m_AutoID++;
		m_AutoID &= 0x7FFFFFFF;
	} while ((int)m_AutoID == 0);

	return m_AutoID;
}

/*
 * --INFO--
 * PAL Address: 0x801ccaac
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int* CRedSound::EntryStandbyID(int id)
{
	int* slot = m_StandbyStatus;
	do {
		if (*slot == 0) {
			*slot = id;
			return slot;
		}
		slot++;
	} while (slot < (m_StandbyStatus + REDSOUND_STANDBY_STATUS_COUNT));

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801ccafc
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::Init(void* mainBuffer, int mainBufferSize, int aramBuffer, int aramBufferSize)
{
	memset(m_StandbyStatus, 0, REDSOUND_STANDBY_STATUS_SIZE);

	if (mainBufferSize > 0 && aramBufferSize > 0) {
		if ((((u32)mainBuffer & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0) ||
		    (((u32)mainBufferSize & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0)) {
			if (m_ReportPrint != 0) {
				OSReport(sRedSoundMemorySettingError, sRedSoundLogPrefix, sRedSoundLogErrorColor, (u32)mainBuffer,
				         mainBufferSize, sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if ((((u32)aramBuffer & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0) ||
		    (((u32)aramBufferSize & REDSOUND_MEMORY_BANK_ALIGN_MASK) != 0)) {
			if (m_ReportPrint != 0) {
				OSReport(sRedSoundAMemorySettingError,
				         sRedSoundLogPrefix, sRedSoundLogErrorColor, aramBuffer,
				         aramBufferSize, sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if (ARCheckInit() == 0) {
			if (m_ReportPrint != 0) {
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

		if (m_ReportPrint != 0) {
			OSReport(sRedSoundInitOk,
			         sRedSoundLogPrefix, sRedSoundLogInfoColor, sRedSoundLogReset);
			fflush(__files + 1);
		}
	} else {
		mainBufferSize = 0;

		if (m_ReportPrint != 0) {
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::Start()
{
#define redSoundStreamBank (*(void* volatile*)&p_StreamBank)
	redSoundStreamBank = (void*)RedNew(REDSOUND_STREAM_BANK_SIZE);
	memset((void*)redSoundStreamBank, 0, REDSOUND_STREAM_BANK_SIZE);
#undef redSoundStreamBank
}

/*
 * --INFO--
 * PAL Address: 0x801ccd44
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::ReportPrint(int debugFlag)
{
	m_ReportPrint = debugFlag;
}

/*
 * --INFO--
 * PAL Address: 0x801ccd9c
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::ReportStandby(int id)
{
	int i;
	int result = 0;

	if (id == 0) {
		i = 0;
		do {
			if (m_StandbyStatus[i] != 0) {
				result++;
				break;
			}
			i++;
	} while (i < REDSOUND_STANDBY_STATUS_COUNT);
	} else {
		i = 0;
		do {
			if (id == m_StandbyStatus[i]) {
				result++;
				break;
			}
			i++;
		} while (i < REDSOUND_STANDBY_STATUS_COUNT);
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801cce34
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::SetReverbDepth(int bank, int sep, int depth)
{
	c_Driver.SetReverbDepth(bank, sep, depth);
}

/*
 * --INFO--
 * PAL Address: 0x801ccf74
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::GetStreamPlayPoint(int streamID, int* point1, int* point2)
{
	c_Driver.GetStreamPlayPoint(streamID, point1, point2);
}

/*
 * --INFO--
 * PAL Address: 0x801cd5ac
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedSound::StreamPlay(void* data, int fileSize, int pan, int volume)
{
	int id = 0;
	RedStreamHEAD* streamHeader = (RedStreamHEAD*)data;

	if (streamHeader->m_signature[0] == REDSOUND_STREAM_SIGNATURE_0 &&
	    streamHeader->m_signature[1] == REDSOUND_STREAM_SIGNATURE_1 &&
	    streamHeader->m_signature[2] == REDSOUND_STREAM_SIGNATURE_2) {
		id = GetAutoID();
		c_Driver.StreamPlay(id, data, fileSize, pan, volume);
	} else if (m_ReportPrint != 0) {
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedSound::TestProcess(int mode)
{
	c_Driver.TestProcess(mode);
}
