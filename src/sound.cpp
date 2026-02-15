#include "ffcc/sound.h"

#include "ffcc/RedSound/RedSound.h"
#include "ffcc/system.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSound::CSound()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSound::~CSound()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800c7f20
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::SetStereo(int stereo)
{
    reinterpret_cast<CRedSound*>(this)->SetSoundMode((u32)__cntlzw(stereo) >> 5);
}

/*
 * --INFO--
 * PAL Address: 0x800c7ef8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::SetBgmMasterVolume(int volume)
{
    *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22B0) = volume;
    reinterpret_cast<CRedSound*>(this)->MusicMasterVolume(volume);
}

/*
 * --INFO--
 * PAL Address: 0x800c7ed0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::SetSeMasterVolume(int volume)
{
    *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22B4) = volume;
    reinterpret_cast<CRedSound*>(this)->SeMasterVolume(volume);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::create(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Realloc(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::GetPerformance()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PauseDiscError(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::CheckDriver(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Frame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::loadWaveFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadWaveASync(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::CancelLoadWaveASync()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::IsLoadWaveASyncCompleted()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadBgm(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PlayBgm(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::CrossPlayBgm(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PlayNextBgm(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::StopBgm()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::FadeOutBgm(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadBlock()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::FreeBlock()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadSe(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadSe(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadWave(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadWave(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::FreeWave(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::StopAndFreeAllSe(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PlaySe(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::StopSe(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::FadeOutSe(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::ChangeSeVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::ChangeSePan(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::calcVolumePan(CSound::CSe3D*, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::searchSe3D(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PlaySe3D(int, Vec*, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PlaySe3DLine(int, int, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::SetSe3DGroup(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::StopSe3DGroup(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::StopSe3D(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
_pppMngSt* CSound::FadeOutSe3D(int, int)
{
	return (_pppMngSt*)nullptr;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::ChangeSe3DPos(int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::ChangeSe3DPitch(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Clear3DLine(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::Add3DLine(int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::SetReverb(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::LoadStream(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PlayStreamASync()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::StopStream()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::SetStreamVolume(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::IsPlayStream()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::IsDebugPrint(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800c50c8
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::PauseAllSe(int pause)
{
    int paused = (-pause | pause) >> 31;
    reinterpret_cast<CRedSound*>(this)->SePause(-1, paused);
    reinterpret_cast<CRedSound*>(this)->StreamPause(-1, paused);
    *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22D0) = pause;
}

/*
 * --INFO--
 * PAL Address: 0x800c5050
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::AddNoFreeSeGroup(int group)
{
    short* noFreeSeGroups = reinterpret_cast<short*>(reinterpret_cast<u8*>(this) + 0x22C0);
    for (int i = 0; i < 4; i++) {
        if (noFreeSeGroups[i] == -1) {
            noFreeSeGroups[i] = group;
            return;
        }
    }

    if (System.m_execParam != 0) {
        System.Printf("%s", (char*)nullptr);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c4fd8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::AddNoFreeWave(int wave)
{
    short* noFreeWaves = reinterpret_cast<short*>(reinterpret_cast<u8*>(this) + 0x22C8);
    for (int i = 0; i < 4; i++) {
        if (noFreeWaves[i] == -1) {
            noFreeWaves[i] = wave;
            return;
        }
    }

    if (System.m_execParam != 0) {
        System.Printf("%s", (char*)nullptr);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::WaitASync()
{
	// TODO
}
