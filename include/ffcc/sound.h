#ifndef _FFCC_PPP_SOUND_H_
#define _FFCC_PPP_SOUND_H_

#include "ffcc/file.h"
#include "ffcc/line.h"
#include "ffcc/manager.h"
#include "ffcc/memory.h"
#include "ffcc/RedSound/RedSound.h"

struct _pppMngSt;

class CSound : public CManager
{
public:
    class CSe3D {
    public:
        union {
            struct {
                unsigned char m_active : 1;
                unsigned char m_paused : 1;
                unsigned char m_flagsRest : 6;
            } m_bits;
            signed char m_flags;
        };
        unsigned char m_volume;
        unsigned char m_pan;
        signed char m_lineIndex;
        int m_handle;
        int m_playId;
        int m_soundId;
        float m_nearDistance;
        float m_farDistance;
        Vec m_position;
        int m_group;
    };

    CSound();
    ~CSound();

    void Init();
    void Quit();
    void SetStereo(int);
    void SetBgmMasterVolume(int);
    void SetSeMasterVolume(int);
    unsigned int GetSoundMode() { return m_redSound.GetSoundMode(); }
    int DMAEntry(int flags, int direction, int mainMemory, int aramMemory, int size,
                 RedDmaCallback callback, void* callbackData)
    {
        return m_redSound.DMAEntry(flags, direction, mainMemory, aramMemory, size, callback, callbackData);
    }
    int DMACheck(int id) { return m_redSound.DMACheck(id); }
    int GetBgmMasterVolume() const { return m_bgmMasterVolume; }
    int GetSeMasterVolume() const { return m_seMasterVolume; }
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
    int IsLoadWaveASyncCompleted();
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
    int PlaySe(int, int, int, int);
    void StopSe(int);
    void FadeOutSe(int, int);
    void ChangeSeVolume(int, int, int);
    void ChangeSePan(int, int, int);
    void calcVolumePan(CSe3D*, int&, int&);
    CSe3D* searchSe3D(int);
    int PlaySe3D(int, Vec*, float, float, int);
    int PlaySe3DLine(int, int, float, float, int);
    void SetSe3DGroup(int, int);
    void StopSe3DGroup(int);
    void StopSe3D(int);
    void FadeOutSe3D(int, int);
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

private:
    CMemory::CStage* m_stage;
    CRedSound m_redSound;
    unsigned char* m_aramBuffer;
    CFile::CHandle* m_waveFile;
    int m_waveRemain;
    int m_waveOffset;
    int m_waveID;
    int m_waveState;
    int m_waveSyncMode;
    int m_seCount;
    CSe3D m_seWork[128];
    CLine<10> m_lines[8];
    unsigned char* m_streamBuffer;
    CFile::CHandle* m_streamFile;
    int m_streamOffset;
    int m_streamID;
    unsigned int m_streamHalf;
    int m_streamPlaying;
    int m_streamRemain;
    int m_streamState;
    int m_streamWaveID;
    int m_bgmMasterVolume;
    int m_seMasterVolume;
    int m_curMusicVolume;
    int m_seMaxVolume;
    short m_noFreeSeGroups[4];
    short m_noFreeWaves[4];
    int m_pauseAllSe;
    int m_debugPrint;
};

typedef int CSound_CSe3D_size_mismatch[(sizeof(CSound::CSe3D) == 0x28) ? 1 : -1];

extern CSound Sound;

#endif // _FFCC_PPP_SOUND_H_
