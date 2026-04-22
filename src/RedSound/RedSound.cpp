#include "ffcc/RedSound/RedSound.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedGlobals.h"

#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "string.h"
#include "dolphin/os.h"
#include "dolphin/ai.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
#include "dolphin/axart.h"

extern "C" {
	void __dl__FPv(void*);
	void* RedNew__Fi(int);
}

// RedSound global linkage that is shared across Red* units.
CRedDriver c_Driver;
int m_StandbyStatus[0x40];
volatile unsigned int m_AutoID;
volatile int DAT_8032f4c8;
static const char s_redSoundMemorySettingErrorFmt[] = "%s%s  Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n";
static const char sRedSoundLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char s_redSoundAMemorySettingErrorFmt[] = "%s%sA-Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n";
static const char sRedSoundLogErrorColor[] = "\x1B[7;31m";
static const char sRedSoundLogReset[] = "\x1B[0m";
static const char sRedSoundLogInfoColor[] = "\x1B[4;34m";
static const char s_redSoundArNotInitializedFmt[] = "%s\"AR\" was not initialized.%s\n";
static const char s_redSoundInitOkFmt[] = "%s%sSound Driver Initialize OK.%s\n";
static const char s_redSoundInitErrorFmt[] = "%s%sSound Driver Initialize ERROR !!%s\n";
static const char s_redSoundInvalidStreamDataFmt[] = "%s%sSTREAM : This data was not 'STREAM-DATA'.%s\n";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
extern "C" CRedSound* __dt__9CRedSoundFv(CRedSound* redSound, short shouldDelete)
{
    if ((redSound != 0) && (0 < shouldDelete)) {
        __dl__FPv(redSound);
    }
    return redSound;
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
		m_AutoID = (m_AutoID + 1) & 0x7FFFFFFF;
	} while (m_AutoID == 0);

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
	} while (slot < (m_StandbyStatus + 0x40));

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
int CRedSound::Init(void* param_2, int param_3, int param_4, int param_5)
{
	memset(m_StandbyStatus, 0, 0x100);

	if (param_3 > 0 && param_5 > 0) {
		if ((((u32)param_2 & 0x1F) != 0) || (((u32)param_3 & 0x1F) != 0)) {
			if (m_ReportPrint != 0) {
				OSReport("%s%s  Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n", "\x1B[7;34mSound\x1B[0m:",
				         sRedSoundLogErrorColor, (u32)param_2,
				         param_3, sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if ((((u32)param_4 & 0x1F) != 0) || (((u32)param_5 & 0x1F) != 0)) {
			if (m_ReportPrint != 0) {
				OSReport("%s%sA-Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n", "\x1B[7;34mSound\x1B[0m:",
				         sRedSoundLogErrorColor, param_4, param_5,
				         sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if (ARCheckInit() == 0) {
			if (m_ReportPrint != 0) {
				OSReport("%s\"AR\" was not initialized.%s\n", "\x1B[7;34mSound\x1B[0m:", sRedSoundLogErrorColor,
				         sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		AIReset();
		AIInit(0);
		AXInit();
		AXARTInit();
        c_RedMemory.Init((int)param_2, param_3, param_4, param_5);
		c_RedEntry.Init();
		Start();
		c_Driver.Init();

		if (m_ReportPrint != 0) {
			OSReport("%s%sSound Driver Initialize OK.%s\n", "\x1B[7;34mSound\x1B[0m:", sRedSoundLogInfoColor,
			         sRedSoundLogReset);
			fflush(__files + 1);
		}
	} else {
		param_3 = 0;

		if (m_ReportPrint != 0) {
			OSReport("%s%sSound Driver Initialize ERROR !!%s\n", "\x1B[7;34mSound\x1B[0m:", sRedSoundLogErrorColor,
			         sRedSoundLogReset);
			fflush(__files + 1);
		}
	}

	return param_3;
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
#define redSoundReverbSize (*(u32* volatile*)&p_ReverbSize)
	redSoundReverbSize = (u32*)RedNew__Fi(0x100);
	memset((void*)redSoundReverbSize, 0, 0x100);
#undef redSoundReverbSize
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
void CRedSound::GetProgramTime()
{
	c_Driver.GetProgramTime();
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

	if (id == 0) {
		i = 0;
		do {
			if (m_StandbyStatus[i] != 0) {
				return 1;
			}
			i++;
		} while (i < 0x40);
	} else {
		i = 0;
		do {
			if (id == m_StandbyStatus[i]) {
				return 1;
			}
			i++;
		} while (i < 0x40);
	}

	return 0;
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
void CRedSound::DMAEntry(int type, int src, int dst, int length, int flags, void (*callback)(void*), void* userData)
{
	RedDmaEntry(type, src, dst, length, flags, callback, userData);
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
void CRedSound::DMACheck(int id)
{
	RedDmaSearchID(id);
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
void CRedSound::GetSoundMode()
{
	c_Driver.GetSoundMode();
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
void CRedSound::ReentryMusicData(int bank)
{
	c_Driver.ReentryMusicData(bank);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicStop(int id)
{
	c_Driver.MusicStop(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicPlay(int id, int vol, int fadeTime)
{
	c_Driver.MusicPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicCrossPlay(int id, int vol, int fadeTime)
{
	c_Driver.MusicCrossPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicNextPlay(int id, int vol, int fadeTime)
{
	c_Driver.MusicNextPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicMasterVolume(int volume)
{
	c_Driver.MusicMasterVolume(volume);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicFadeOut(int id, int fadeTime)
{
	c_Driver.MusicFadeOut(id, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicVolume(int id, int volume, int fadeTime)
{
	c_Driver.MusicVolume(id, volume, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentrySeSepData(int id)
{
	c_Driver.ReentrySeSepData(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePlayState(int id)
{
	c_Driver.SePlayState(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
int CRedSound::SePlay(int seID, int sepID, int unk, int volume, int pitch)
{
	unsigned int autoID = GetAutoID();
	c_Driver.SePlay(seID, sepID, autoID, unk, volume, pitch);
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
void CRedSound::GetSeVolume(int seID, int outVolume)
{
	c_Driver.GetSeVolume(seID, outVolume);
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
void CRedSound::ReportSeLoop(int mode)
{
	c_Driver.ReportSeLoop(mode);
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
void CRedSound::StreamPlayState(int streamID)
{
	c_Driver.StreamPlayState(streamID);
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
int CRedSound::StreamPlay(void* data, int param_3, int param_4, int param_5)
{
	int id = 0;
	char* streamData = (char*)data;

	if (streamData[0] == 'S' && streamData[1] == 'T' && streamData[2] == 'R') {
		id = GetAutoID();
		c_Driver.StreamPlay(id, data, param_3, param_4, param_5);
	} else if (m_ReportPrint != 0) {
		OSReport(s_redSoundInvalidStreamDataFmt, sRedSoundLogPrefix, sRedSoundLogErrorColor, sRedSoundLogReset);
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
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearWaveBank(int id)
{
	c_Driver.ClearWaveBank(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentryWaveData(int id)
{
	c_Driver.ReentryWaveData(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DisplayWaveInfo()
{
	c_Driver.DisplayWaveInfo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::TestProcess(int mode)
{
	c_Driver.TestProcess(mode);
}
