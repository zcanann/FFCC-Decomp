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
CRedDriver gRedDriver;
int DAT_8032e17c[0x40];
int DAT_8032f3f8;
u8 DAT_8032f4a8;
int DAT_8032f4ac;
u32* DAT_8032f4b0;
u32 DAT_8032f4b4;
int* DAT_8032f4b8;
volatile unsigned int DAT_8032f4c4;
volatile int DAT_8032f4c8;
static const char s_redSoundMemorySettingErrorFmt[] = "%s%s  Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n";
static const char sRedSoundLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char s_redSoundAMemorySettingErrorFmt[] = "%s%sA-Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n";
static const char sRedSoundLogErrorColor[] = "\x1B[7;31m";
static const char sRedSoundLogReset[] = "\x1B[0m";
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
 * Address:	TODO
 * Size:	TODO
 */
CRedSound::~CRedSound()
{
	End();
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
#pragma dont_inline on
unsigned int CRedSound::GetAutoID()
{
	do {
		DAT_8032f4c4 = DAT_8032f4c4 + 1;
		DAT_8032f4c4 = DAT_8032f4c4 & 0x7FFFFFFF;
	} while ((int)DAT_8032f4c4 == 0);

	return DAT_8032f4c4;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x801ccaac
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int* CRedSound::EntryStandbyID(int id)
{
	int* slot = DAT_8032e17c;
	do {
		if (*slot == 0) {
			*slot = id;
			return slot;
		}
		slot++;
	} while (slot < (DAT_8032e17c + 0x40));

	return 0;
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801ccafc
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int CRedSound::Init(void* param_2, int param_3, int param_4, int param_5)
{
	memset(DAT_8032e17c, 0, 0x100);

	if (param_3 > 0 && param_5 > 0) {
		if ((((u32)param_2 & 0x1F) != 0) || (((u32)param_3 & 0x1F) != 0)) {
			if (gRedMemoryDebugEnabled != 0) {
				OSReport("%s%s  Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n", "\x1B[7;34mSound\x1B[0m:",
				         sRedSoundLogErrorColor, (u32)param_2,
				         param_3, sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if ((((u32)param_4 & 0x1F) != 0) || (((u32)param_5 & 0x1F) != 0)) {
			if (gRedMemoryDebugEnabled != 0) {
				OSReport("%s%sA-Memory Setting Error !! (0x%8.8X:0x%8.8X)%s\n", "\x1B[7;34mSound\x1B[0m:",
				         sRedSoundLogErrorColor, param_4, param_5,
				         sRedSoundLogReset);
				fflush(__files + 1);
			}
			return 0;
		}

		if (ARCheckInit() == 0) {
			if (gRedMemoryDebugEnabled != 0) {
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
		DAT_8032f480.Init((int)param_2, param_3, param_4, param_5);
		DAT_8032e154.Init();
		Start();
		gRedDriver.Init();

		if (gRedMemoryDebugEnabled != 0) {
			OSReport("%s%sSound Driver Initialize OK.%s\n", "\x1B[7;34mSound\x1B[0m:", "\x1B[4;34m",
			         sRedSoundLogReset);
			fflush(__files + 1);
		}
	} else {
		param_3 = 0;

		if (gRedMemoryDebugEnabled != 0) {
			OSReport("%s%sSound Driver Initialize ERROR !!%s\n", "\x1B[7;34mSound\x1B[0m:", sRedSoundLogErrorColor,
			         sRedSoundLogReset);
			fflush(__files + 1);
		}
	}

	return param_3;
}
#pragma optimization_level 4

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
	DAT_8032f4c8 = (int)RedNew__Fi(0x100);
	memset((void*)DAT_8032f4c8, 0, 0x100);
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
	gRedDriver.End();
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
	gRedDriver.GetProgramTime();
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
	gRedMemoryDebugEnabled = debugFlag;
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
#pragma optimization_level 0
int CRedSound::ReportStandby(int id)
{
	int result = 0;
	int i;

	if (id == 0) {
		i = 0;
		do {
			if (DAT_8032e17c[i] != 0) {
				result++;
				break;
			}
			i++;
		} while (i < 0x40);
	} else {
		i = 0;
		do {
			if (id == DAT_8032e17c[i]) {
				result++;
				break;
			}
			i++;
		} while (i < 0x40);
	}

	return result;
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cce34
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::DMAEntry(int type, int src, int dst, int length, int flags, void (*callback)(void*), void* userData)
{
	RedDmaEntry(type, src, dst, length, flags, callback, userData);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cce8c
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::DMACheck(int id)
{
	RedDmaSearchID(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cceb4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SetSoundMode(int mode)
{
	gRedDriver.SetSoundMode(mode);
}
#pragma optimization_level 4

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
	gRedDriver.GetSoundMode();
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
#pragma optimization_level 0
void CRedSound::SetReverb(int bank, int kind)
{
	gRedDriver.SetReverb(bank, kind);
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
	gRedDriver.SetReverbDepth(bank, sep, depth);
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
	gRedDriver.SetMusicData(musicData);
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
	gRedDriver.ReentryMusicData(bank);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicStop(int id)
{
	gRedDriver.MusicStop(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicPlay(int id, int vol, int fadeTime)
{
	gRedDriver.MusicPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicCrossPlay(int id, int vol, int fadeTime)
{
	gRedDriver.MusicCrossPlay(id, vol, fadeTime);
}
#pragma optimization_level 0

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicNextPlay(int id, int vol, int fadeTime)
{
	gRedDriver.MusicNextPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicMasterVolume(int volume)
{
	gRedDriver.MusicMasterVolume(volume);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicFadeOut(int id, int fadeTime)
{
	gRedDriver.MusicFadeOut(id, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicVolume(int id, int volume, int fadeTime)
{
	gRedDriver.MusicVolume(id, volume, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetMusicPhraseStop(int id)
{
	gRedDriver.SetMusicPhraseStop(id);
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
	gRedDriver.SetSeBlockData(bank, blockData);
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
	gRedDriver.SetSeSepData(seSepData);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearSeSepData(int id)
{
	gRedDriver.ClearSeSepData(id);
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
#pragma optimization_level 0
void CRedSound::ClearSeSepDataMG(int bank, int sep, int group, int kind)
{
	gRedDriver.ClearSeSepDataMG(bank, sep, group, kind);
}
#pragma optimization_level 4

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::ReentrySeSepData(int id)
{
	gRedDriver.ReentrySeSepData(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::SePlayState(int id)
{
	gRedDriver.SePlayState(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::SeStop(int id)
{
	gRedDriver.SeStop(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd2c8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SeStopMG(int bank, int sep, int group, int kind)
{
	gRedDriver.SeStopMG(bank, sep, group, kind);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd30c
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int CRedSound::SePlay(int seID, int sepID, int unk, int volume, int pitch)
{
	unsigned int autoID = GetAutoID();
	gRedDriver.SePlay(seID, sepID, autoID, unk, volume, pitch);
	return autoID;
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd378
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SeMasterVolume(int volume)
{
	gRedDriver.SeMasterVolume(volume);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd3a4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SeFadeOut(int seID, int frameCount)
{
	gRedDriver.SeFadeOut(seID, frameCount);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd3d8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SeVolume(int seID, int volume, int frameCount)
{
	gRedDriver.SeVolume(seID, volume, frameCount);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd414
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SePan(int seID, int pan, int frameCount)
{
	gRedDriver.SePan(seID, pan, frameCount);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd450
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SePitch(int seID, int pitch, int frameCount)
{
	gRedDriver.SePitch(seID, pitch, frameCount);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd48c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::SePause(int seID, int pause)
{
	gRedDriver.SePause(seID, pause);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd4c0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int CRedSound::GetSeVolume(int seID, int outVolume)
{
	return gRedDriver.GetSeVolume(seID, outVolume);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd4f4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::ReportSeLoop(int mode)
{
	gRedDriver.ReportSeLoop(mode);
}
#pragma optimization_level 4

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
	gRedDriver.DisplaySePlayInfo();
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
#pragma optimization_level 0
void CRedSound::StreamPlayState(int streamID)
{
	gRedDriver.StreamPlayState(streamID);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd570
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::GetStreamPlayPoint(int streamID, int* point1, int* point2)
{
	gRedDriver.GetStreamPlayPoint(streamID, point1, point2);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd5ac
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::StreamStop(int streamID)
{
	gRedDriver.StreamStop(streamID);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd5d8
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
int CRedSound::StreamPlay(void* data, int param_3, int param_4, int param_5)
{
	int id = 0;
	char* streamData = (char*)data;

	if (streamData[0] == 'S' && streamData[1] == 'T' && streamData[2] == 'R') {
		id = GetAutoID();
		gRedDriver.StreamPlay(id, data, param_3, param_4, param_5);
	} else if (gRedMemoryDebugEnabled != 0) {
		OSReport(s_redSoundInvalidStreamDataFmt, sRedSoundLogPrefix, sRedSoundLogErrorColor, sRedSoundLogReset);
		fflush(__files + 1);
	}

	return id;
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd6b8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::StreamVolume(int streamID, int volume, int frameCount)
{
	gRedDriver.StreamVolume(streamID, volume, frameCount);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd6f4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::StreamPause(int streamID, int pause)
{
	gRedDriver.StreamPause(streamID, pause);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd728
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
#pragma optimization_level 0
unsigned int CRedSound::SetWaveData(int waveID, void* waveData, int waveSize)
{
	unsigned int id = GetAutoID();
	int* slot = EntryStandbyID(id);
	if (slot != 0) {
		gRedDriver.SetWaveData((int)slot, waveID, waveData, waveSize);
	}
	return id;
}
#pragma optimization_level 4
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::ClearWaveData(int id)
{
	gRedDriver.ClearWaveData(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * PAL Address: 0x801cd7d0
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma optimization_level 0
void CRedSound::ClearWaveDataM(int bank, int sep, int group, int kind)
{
	gRedDriver.ClearWaveDataM(bank, sep, group, kind);
}
#pragma optimization_level 4

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::ClearWaveBank(int id)
{
	gRedDriver.ClearWaveBank(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::ReentryWaveData(int id)
{
	gRedDriver.ReentryWaveData(id);
}
#pragma optimization_level 4

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DisplayWaveInfo()
{
	gRedDriver.DisplayWaveInfo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 0
void CRedSound::TestProcess(int mode)
{
	gRedDriver.TestProcess(mode);
}
