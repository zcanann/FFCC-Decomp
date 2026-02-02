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

// Global variables (external declarations)
extern CRedDriver CRedDriver_8032f4c0;
extern CRedMemory DAT_8032f480;
extern CRedEntry DAT_8032e154;
extern int DAT_8032f408; // Debug flag
extern char DAT_8032e17c[]; // Buffer for memset
extern void* DAT_8032e170; // Registration memory
extern FILE DAT_8021d1a8; // File handle for fflush

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
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::GetAutoID()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::EntryStandbyID(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::Init(void* param_2, int param_3, int param_4, int param_5)
{
	memset(&DAT_8032e17c, 0, 0x100);
	
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::Start()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::End()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::GetProgramTime()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReportPrint(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReportStandby(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DMAEntry(int, int, int, int, int, void (*) (void*), void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DMACheck(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetSoundMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::GetSoundMode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetReverb(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetReverbDepth(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetMusicData(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentryMusicData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicPlay(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicCrossPlay(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicNextPlay(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicMasterVolume(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicFadeOut(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::MusicVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetMusicPhraseStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetSeBlockData(int, void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetSeSepData(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearSeSepData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearSeSepDataMG(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentrySeSepData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePlayState(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SeStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SeStopMG(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePlay(int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SeMasterVolume(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SeFadeOut(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SeVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePan(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePitch(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SePause(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::GetSeVolume(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReportSeLoop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DisplaySePlayInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::StreamPlayState(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::GetStreamPlayPoint(int, int*, int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::StreamStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::StreamPlay(void*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::StreamVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::StreamPause(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::SetWaveData(int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearWaveData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearWaveDataM(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ClearWaveBank(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::ReentryWaveData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::DisplayWaveInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedSound::TestProcess(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
// Forward declaration
extern "C" void __dt__10CRedDriverFv(void*);

void __sinit_RedSound_cpp(void)
{
	// Initialize the global CRedDriver object and register for destruction
	__register_global_object(&CRedDriver_8032f4c0, __dt__10CRedDriverFv, &DAT_8032e170);
}
