#include "ffcc/RedSound/RedSound.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"

#include "PowerPC_EABI_Support/Runtime/NMWException.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "string.h"
#include "dolphin/os.h"
#include "dolphin/ai.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
#include "dolphin/axart.h"

// Global variables (external declarations)
extern CRedDriver CRedDriver_8032f4c0;
extern CRedMemory DAT_8032f480;
extern CRedEntry DAT_8032e154;
extern int DAT_8032f408; // Debug flag
extern unsigned int DAT_8032f4c4; // Auto ID counter
extern int DAT_8032e17c[0x40]; // Standby ID table
extern void* DAT_8032e170; // Registration memory
extern void* DAT_8032f4c8; // Internal sound state buffer
extern FILE DAT_8021d1a8; // File handle for fflush
extern "C" {
	void __dl__FPv(void*);
	void* RedNew__Fi(int);
}

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
 * PAL Address: 0x801cca38
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CRedSound* dtor_801CCA38(CRedSound* redSound, short param_2)
{
    if ((redSound != 0) && (0 < param_2)) {
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
		DAT_8032f4c4 = (DAT_8032f4c4 + 1) & 0x7FFFFFFF;
	} while (DAT_8032f4c4 == 0);

	return DAT_8032f4c4;
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

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::Init(void* param_2, int param_3, int param_4, int param_5)
{
	memset(DAT_8032e17c, 0, 0x100);
	
	if (param_3 < 1 || param_5 < 1) {
		if (DAT_8032f408 != 0) {
			OSReport("[%s] Sound Driver Initialize ERROR! %s %s\n", "RedSound", "Invalid parameters", "");
			fflush(&DAT_8021d1a8);
		}
		return;
	}
	
	if (((unsigned)param_2 & 0x1f) != 0 || ((unsigned)param_3 & 0x1f) != 0) {
		if (DAT_8032f408 != 0) {
			OSReport("[%s] %s Memory Setting Error! 0x%x 0x%x %s\n", "RedSound", "", (unsigned)param_2, param_3, "");
			fflush(&DAT_8021d1a8);
		}
		return;
	}
	
	if (((unsigned)param_4 & 0x1f) != 0 || ((unsigned)param_5 & 0x1f) != 0) {
		if (DAT_8032f408 != 0) {
			OSReport("[%s] A Memory Setting Error! 0x%x 0x%x %s\n", "RedSound", "", param_4, param_5, "");
			fflush(&DAT_8021d1a8);
		}
		return;
	}
	
	int initResult = ARCheckInit();
	if (initResult == 0) {
		if (DAT_8032f408 != 0) {
			OSReport("[%s] AR was not initialized %s\n", "RedSound", "");
			fflush(&DAT_8021d1a8);
		}
		return;
	}
	
	AIReset();
	AIInit(0);
	AXInit();
	// AXARTInit(); // Function might not exist yet
	DAT_8032f480.Init((int)param_2, param_3, param_4, param_5);
	DAT_8032e154.Init();
	Start();
	CRedDriver_8032f4c0.Init();
	
	if (DAT_8032f408 != 0) {
		OSReport("[%s] Sound Driver Initialize OK! %s\n", "RedSound", "");
		fflush(&DAT_8021d1a8);
	}
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
	DAT_8032f4c8 = RedNew__Fi(0x100);
	memset(DAT_8032f4c8, 0, 0x100);
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
	CRedDriver_8032f4c0.End();
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
	CRedDriver_8032f4c0.GetProgramTime();
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
	DAT_8032f408 = debugFlag;
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
	int localType = type;
	int localSrc = src;
	int localDst = dst;
	int localLength = length;
	int localFlags = flags;
	void (*localCallback)(void*) = callback;
	void* localUserData = userData;

	RedDmaEntry(localType, localSrc, localDst, localLength, localFlags, localCallback, localUserData);
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
	CRedDriver_8032f4c0.SetSoundMode(mode);
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
	CRedDriver_8032f4c0.GetSoundMode();
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
	CRedDriver_8032f4c0.SetReverb(bank, kind);
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
	CRedDriver_8032f4c0.SetReverbDepth(bank, sep, depth);
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
	CRedDriver_8032f4c0.SetMusicData(musicData);
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
	CRedDriver_8032f4c0.ReentryMusicData(bank);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicStop(int id)
{
	CRedDriver_8032f4c0.MusicStop(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicPlay(int id, int vol, int fadeTime)
{
	CRedDriver_8032f4c0.MusicPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicCrossPlay(int id, int vol, int fadeTime)
{
	CRedDriver_8032f4c0.MusicCrossPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicNextPlay(int id, int vol, int fadeTime)
{
	CRedDriver_8032f4c0.MusicNextPlay(id, vol, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicMasterVolume(int volume)
{
	CRedDriver_8032f4c0.MusicMasterVolume(volume);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicFadeOut(int id, int fadeTime)
{
	CRedDriver_8032f4c0.MusicFadeOut(id, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicVolume(int id, int volume, int fadeTime)
{
	CRedDriver_8032f4c0.MusicVolume(id, volume, fadeTime);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetMusicPhraseStop(int id)
{
	CRedDriver_8032f4c0.SetMusicPhraseStop(id);
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
	CRedDriver_8032f4c0.SetSeBlockData(bank, blockData);
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
	CRedDriver_8032f4c0.SetSeSepData(seSepData);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearSeSepData(int id)
{
	CRedDriver_8032f4c0.ClearSeSepData(id);
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
	CRedDriver_8032f4c0.ClearSeSepDataMG(bank, sep, group, kind);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentrySeSepData(int id)
{
	CRedDriver_8032f4c0.ReentrySeSepData(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePlayState(int id)
{
	CRedDriver_8032f4c0.SePlayState(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SeStop(int id)
{
	CRedDriver_8032f4c0.SeStop(id);
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
	CRedDriver_8032f4c0.SeStopMG(bank, sep, group, kind);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedSound::SePlay(int seID, int sepID, int unk, int volume, int pitch)
{
	int autoID = GetAutoID();
	CRedDriver_8032f4c0.SePlay(seID, sepID, autoID, unk, volume, pitch);
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
	CRedDriver_8032f4c0.SeMasterVolume(volume);
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
	CRedDriver_8032f4c0.SeFadeOut(seID, frameCount);
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
	CRedDriver_8032f4c0.SeVolume(seID, volume, frameCount);
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
	CRedDriver_8032f4c0.SePan(seID, pan, frameCount);
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
	CRedDriver_8032f4c0.SePitch(seID, pitch, frameCount);
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
	CRedDriver_8032f4c0.SePause(seID, pause);
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
	CRedDriver_8032f4c0.GetSeVolume(seID, outVolume);
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
	CRedDriver_8032f4c0.ReportSeLoop(mode);
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
	CRedDriver_8032f4c0.DisplaySePlayInfo();
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
	CRedDriver_8032f4c0.StreamPlayState(streamID);
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
	CRedDriver_8032f4c0.GetStreamPlayPoint(streamID, point1, point2);
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
	CRedDriver_8032f4c0.StreamStop(streamID);
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

	if ((streamData[0] == 'S') && (streamData[1] == 'T') && (streamData[2] == 'R')) {
		id = GetAutoID();
		CRedDriver_8032f4c0.StreamPlay(id, data, param_3, param_4, param_5);
	} else if (DAT_8032f408 != 0) {
		OSReport("[%s] %s STREAM : This data was not stream data. %s\n", "RedSound", "", "");
		fflush(&DAT_8021d1a8);
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
	CRedDriver_8032f4c0.StreamVolume(streamID, volume, frameCount);
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
	CRedDriver_8032f4c0.StreamPause(streamID, pause);
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
#pragma dont_inline on
unsigned int CRedSound::SetWaveData(int waveID, void* waveData, int waveSize)
{
	unsigned int id = GetAutoID();
	int* slot = EntryStandbyID(id);
	if (slot != 0) {
		CRedDriver_8032f4c0.SetWaveData((int)slot, waveID, waveData, waveSize);
	}
	return id;
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearWaveData(int id)
{
	CRedDriver_8032f4c0.ClearWaveData(id);
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
	CRedDriver_8032f4c0.ClearWaveDataM(bank, sep, group, kind);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearWaveBank(int id)
{
	CRedDriver_8032f4c0.ClearWaveBank(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentryWaveData(int id)
{
	CRedDriver_8032f4c0.ReentryWaveData(id);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DisplayWaveInfo()
{
	CRedDriver_8032f4c0.DisplayWaveInfo();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::TestProcess(int mode)
{
	CRedDriver_8032f4c0.TestProcess(mode);
}

/*
 * --INFO--
 * PAL Address: 0x801cd8bc
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
// Forward declaration
extern "C" void* __ct__10CRedDriverFv(void*);
extern "C" void __dt__10CRedDriverFv(void*);

extern "C" void __sinit_RedSound_cpp(void)
{
	__register_global_object(__ct__10CRedDriverFv(&CRedDriver_8032f4c0), __dt__10CRedDriverFv, &DAT_8032e170);
}
