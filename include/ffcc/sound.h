#ifndef _FFCC_PPP_SOUND_H_
#define _FFCC_PPP_SOUND_H_

#include "ffcc/file.h"

struct _pppMngSt;
struct Vec;

class CSound
{
public:
    class CSe3D;

    CSound();
    ~CSound();

    void Init();
    void Quit();
    void SetStereo(int);
    void SetBgmMasterVolume(int);
    void SetSeMasterVolume(int);
    void SeMaxVolume(int);
    void create(int);
    void destroy();
    void Realloc(int);
    float GetPerformance();
    void PauseDiscError(int);
    void CheckDriver(int);
    void Frame();
    void Draw();
    void loadWaveFrame();
    void LoadWaveASync(int, int, int);
    void CancelLoadWaveASync();
    void IsLoadWaveASyncCompleted();
    void LoadBgm(int);
    void PlayBgm(int);
    void CrossPlayBgm(int, int);
    void PlayNextBgm(int);
    void StopBgm();
    void FadeOutBgm(int);
    void LoadBlock();
    void FreeBlock();
    void LoadSe(int);
    void LoadSe(void*);
    void LoadWave(int);
    void LoadWave(void*);
    void FreeWave(int);
    void StopAndFreeAllSe(int);
    void PlaySe(int, int, int, int);
    void StopSe(int);
    void FadeOutSe(int, int);
    void ChangeSeVolume(int, int, int);
    void ChangeSePan(int, int, int);
    void calcVolumePan(CSe3D*, int&, int&);
    void searchSe3D(int);
    void PlaySe3D(int, Vec*, float, float, int);
    void PlaySe3DLine(int, int, float, float, int);
    void SetSe3DGroup(int, int);
    void StopSe3DGroup(int);
    void StopSe3D(int);
    _pppMngSt* FadeOutSe3D(int, int);
    void ChangeSe3DPos(int, Vec*);
    void ChangeSe3DPitch(int, int, int);
    void Clear3DLine(int);
    void Add3DLine(int, Vec*);
    void SetReverb(int, int);
    void LoadStream(int);
    void PlayStreamASync();
    void StopStream();
    void SetStreamVolume(int, int);
    void IsPlayStream();
    void IsDebugPrint(int);
    void PauseAllSe(int);
    void AddNoFreeSeGroup(int);
    void AddNoFreeWave(int);
    void WaitASync();
};

extern CSound Sound;

#endif // _FFCC_PPP_SOUND_H_
