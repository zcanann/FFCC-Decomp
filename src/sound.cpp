#include "ffcc/sound.h"

#include "ffcc/RedSound/RedSound.h"
#include "ffcc/system.h"
#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"
#include <Runtime.PPCEABI.H/NMWException.h>
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include <math.h>
#include <string.h>

extern float FLOAT_80330ce8;
extern float FLOAT_80330cec;
extern float FLOAT_80330cf0;
extern float FLOAT_80330cf4;
extern float FLOAT_80330d10;
extern float FLOAT_80330d30;
extern double DOUBLE_80330d18;
extern double DOUBLE_80330d20;
extern double DOUBLE_80330d28;
extern float DAT_8032ec20;
extern "C" void* PTR_PTR_s_CSound_8021056c;
extern "C" void __ct__9CRedSoundFv(void*);
extern "C" void __dt__6CSoundFv(void*);
extern "C" unsigned int GetSoundMode__9CRedSoundFv(CRedSound*);
extern "C" int StreamPlayState__9CRedSoundFi(CRedSound*, int);
extern "C" int ReentryWaveData__9CRedSoundFi(CRedSound*, int);
extern "C" int SePlayState__9CRedSoundFi(CRedSound*, int);
extern "C" int ReportSeLoop__9CRedSoundFi(CRedSound*, int);
extern "C" int GetSeVolume__9CRedSoundFii(CRedSound*, int, int);
extern "C" void SeStop__9CRedSoundFi(CRedSound*, int);
extern "C" void SePan__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void SeVolume__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" int SePlay__9CRedSoundFiiiii(CRedSound*, int, int, int, int, int);
extern "C" void MusicVolume__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void Printf__7CSystemFPce(CSystem*, char*, ...);
extern "C" int sprintf(char*, const char*, ...);
extern void* ARRAY_802f26c8;
extern char DAT_801db29c[];
extern char DAT_801db2b8[];
extern char s_Sound___1_n_B_801db130[];
extern unsigned char CFlat[];

struct CLineSegment {
    Vec delta;
    Vec normal;
    float length;
    float startLength;
};

struct CLine {
    Vec min;
    Vec max;
    u32 pointCount;
    u32 unused;
    float unk20[4];
    Vec points[10];
    CLineSegment segments[9];
    float totalLength;
};

extern "C" void __ct__9CLine(CLine* line)
{
    line->pointCount = 0;
}

extern "C" int Calc__9CLine(double maxDistance, CLine* line, Vec* outPos, float* outDistance, u32* outIndex,
                             float* outT, const Vec* queryPos)
{
    const bool infiniteRange = ((float)maxDistance == FLOAT_80330cec);
    float bestDistance = infiniteRange ? FLOAT_80330d10 : (float)maxDistance;
    const float maxDistanceSq = (float)(maxDistance * maxDistance);
    int found = 0;
    u32 bestIndex = 0;
    float bestT = FLOAT_80330cec;
    Vec bestPos;

    for (u32 i = 0; i + 1 < line->pointCount; i++) {
        Vec candidate = line->points[i];
        float distanceSq = PSVECSquareDistance(&candidate, queryPos);
        if (distanceSq < maxDistanceSq || infiniteRange) {
            float distance = distanceSq;
            if (distanceSq <= FLOAT_80330cec) {
                distance = DAT_8032ec20;
            } else {
                distance = (float)sqrt(distanceSq);
            }
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPos = candidate;
                bestIndex = i;
                bestT = FLOAT_80330cec;
                found = 1;
            }
        }

        if (i + 1 == line->pointCount - 1) {
            candidate = line->points[i + 1];
            distanceSq = PSVECSquareDistance(&candidate, queryPos);
            if (distanceSq < maxDistanceSq || infiniteRange) {
                float distance = distanceSq;
                if (distanceSq <= FLOAT_80330cec) {
                    distance = DAT_8032ec20;
                } else {
                    distance = (float)sqrt(distanceSq);
                }
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPos = candidate;
                    bestIndex = i;
                    bestT = FLOAT_80330cf0;
                    found = 1;
                }
            }
        }

        const CLineSegment& segment = line->segments[i];
        const float dotQuery = PSVECDotProduct(queryPos, &segment.delta);
        const float dotStart = PSVECDotProduct(&line->points[i], &segment.delta);
        const float t = (dotQuery - dotStart) / (segment.length * segment.length);
        if (((FLOAT_80330cec <= t) && (t <= FLOAT_80330cf0)) || infiniteRange) {
            Vec scaled;
            Vec projected;
            PSVECScale(&segment.delta, &scaled, t);
            PSVECAdd(&line->points[i], &scaled, &projected);
            const float distance = PSVECDistance(queryPos, &projected);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPos = projected;
                bestIndex = i;
                bestT = t;
                found = 1;
            }
        }
    }

    if (found != 0) {
        if (outPos != nullptr) {
            *outPos = bestPos;
        }
        if (outDistance != nullptr) {
            *outDistance = bestDistance;
        }
        if (outIndex != nullptr) {
            *outIndex = bestIndex;
        }
        if (outT != nullptr) {
            *outT = bestT;
        }
    }

    return found;
}

extern "C" void Draw__9CLine(CLine* line)
{
    if (line->pointCount == 0) {
        return;
    }

    GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(line->pointCount & 0xFFFF));
    u32 i = 0;
    u32* coord = reinterpret_cast<u32*>(&line->points[0]);
    while (i < line->pointCount) {
        GXWGFifo.u32 = coord[0];
        GXWGFifo.u32 = coord[1];
        GXWGFifo.u32 = coord[2];
        coord += 3;
        i++;
    }

    GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(line->pointCount & 0xFFFF));
    i = 0;
    coord = reinterpret_cast<u32*>(&line->points[0]);
    while (i < line->pointCount) {
        GXWGFifo.u32 = coord[0];
        GXWGFifo.f32 = FLOAT_80330cf4 + reinterpret_cast<float*>(coord)[1];
        GXWGFifo.u32 = coord[2];
        coord += 3;
        i++;
    }

    GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, (u16)((line->pointCount & 0x7FFF) << 1));
    i = 0;
    coord = reinterpret_cast<u32*>(&line->points[0]);
    while (i < line->pointCount) {
        GXWGFifo.u32 = coord[0];
        GXWGFifo.u32 = coord[1];
        GXWGFifo.u32 = coord[2];
        GXWGFifo.u32 = coord[0];
        GXWGFifo.f32 = FLOAT_80330cf4 + reinterpret_cast<float*>(coord)[1];
        GXWGFifo.u32 = coord[2];
        coord += 3;
        i++;
    }
}

extern "C" void CalcBound__9CLine2(CLine* line)
{
    line->min.x = FLOAT_80330d10;
    line->min.y = FLOAT_80330d10;
    line->min.z = FLOAT_80330d10;
    line->max.x = FLOAT_80330d30;
    line->max.y = FLOAT_80330d30;
    line->max.z = FLOAT_80330d30;
    line->totalLength = FLOAT_80330cec;

    for (u32 i = 0; i < line->pointCount; i++) {
        const Vec& point = line->points[i];

        if (point.x < line->min.x) {
            line->min.x = point.x;
        }
        if (point.y < line->min.y) {
            line->min.y = point.y;
        }
        if (point.z < line->min.z) {
            line->min.z = point.z;
        }

        if (line->max.x < point.x) {
            line->max.x = point.x;
        }
        if (line->max.y < point.y) {
            line->max.y = point.y;
        }
        if (line->max.z < point.z) {
            line->max.z = point.z;
        }

        if (i != 0) {
            CLineSegment& segment = line->segments[i - 1];
            PSVECSubtract(&line->points[i], &line->points[i - 1], &segment.delta);
            segment.length = PSVECMag(&segment.delta);
            segment.startLength = line->totalLength;
            line->totalLength += segment.length;
            if (segment.length != FLOAT_80330cec) {
                PSVECNormalize(&segment.delta, &segment.normal);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c8998
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_sound_cpp(void)
{
    *reinterpret_cast<void**>(&Sound) = &PTR_PTR_s_CSound_8021056c;
    __ct__9CRedSoundFv(&Sound);
    __construct_array(reinterpret_cast<unsigned char*>(&Sound) + 0x142c, (ConstructorDestructor)__ct__9CLine, 0, 0x1cc,
                      8);
    __register_global_object(&Sound, __dt__6CSoundFv, &ARRAY_802f26c8);
}

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
 * PAL Address: 0x800c7a28
 * PAL Size: 1192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Realloc(int isMinMemoryMode)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    CFile::CHandle*& waveFile = *reinterpret_cast<CFile::CHandle**>(reinterpret_cast<u8*>(this) + 0x8);
    CFile::CHandle*& streamFile = *reinterpret_cast<CFile::CHandle**>(reinterpret_cast<u8*>(this) + 0x2290);
    int& streamPlaying = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22A0);
    int& streamID = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x2298);

    if (waveFile != 0) {
        File.Close(waveFile);
        waveFile = 0;
    }

    redSound->SetWaveData(-1, 0, 0);

    bool wasStreaming = false;
    if (streamPlaying != 0) {
        if (StreamPlayState__9CRedSoundFi(redSound, streamID) != 0) {
            wasStreaming = true;
        }
    }
    if (wasStreaming) {
        redSound->StreamStop(streamID);
    }

    if (streamFile != 0) {
        File.Close(streamFile);
        streamFile = 0;
    }

    streamPlaying = 0;

    redSound->SeStop(-1);
    redSound->ClearSeSepData(-1);
    redSound->ClearWaveData(-3);

    *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x28) = 10000000;
    memset(reinterpret_cast<u8*>(this) + 0x2C, 0, 0x1400);
    memset(reinterpret_cast<u8*>(this) + 0x22C0, 0xFF, 8);
    memset(reinterpret_cast<u8*>(this) + 0x22C8, 0xFF, 8);

    redSound->ClearWaveBank(500);
    redSound->ClearWaveBank(0);

    for (int i = 0; i < 4; i++) {
        redSound->SetSeBlockData(i, 0);
    }

    redSound->End();

    int streamHeapSize = (isMinMemoryMode != 0) ? 0x200000 : 0x800000;
    int waveHeapSize = (isMinMemoryMode != 0) ? 0xE00000 : 0x800000;
    redSound->Init(*reinterpret_cast<void**>(reinterpret_cast<u8*>(this) + 0x4), 0x80000, waveHeapSize, streamHeapSize);

    u32 reportFlag = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x22D4);
    redSound->ReportPrint(((-reportFlag) | reportFlag) >> 31);

    u32 soundMode = GetSoundMode__9CRedSoundFv(redSound);
    redSound->SetSoundMode((u32)__cntlzw((u32)__cntlzw(soundMode) >> 5) >> 5);

    redSound->MusicMasterVolume(*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22B0));
    redSound->SeMasterVolume(*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22B4));

    redSound->SetReverb(1, 4);
    redSound->SetReverbDepth(1, 0x40, 0xF);

    waveFile = 0;
    streamFile = 0;
    streamPlaying = 0;
    memset(reinterpret_cast<u8*>(this) + 0x22C0, 0xFF, 8);
    memset(reinterpret_cast<u8*>(this) + 0x22C8, 0xFF, 8);
    *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22D0) = 0;

    if (isMinMemoryMode != 0) {
        return;
    }

    if (ReentryWaveData__9CRedSoundFi(redSound, 0) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
        }

        redSound->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, "dvd/sound/wave/wave_%04d.wd", 0);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x14) = File.GetLength(waveFile);
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x18) = 0;
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x20) = 0;
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x1C) = 0;
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x24) = 1;
            while (waveFile != 0) {
                loadWaveFrame();
            }
        }
    }

    if (ReentryWaveData__9CRedSoundFi(redSound, 500) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
        }

        redSound->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, "dvd/sound/wave/wave_%04d.wd", 500);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x14) = File.GetLength(waveFile);
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x18) = 0;
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x20) = 0;
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x1C) = 1;
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x24) = 1;
            while (waveFile != 0) {
                loadWaveFrame();
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        char sePath[260];
        sprintf(sePath, "dvd/sound/se/block/se_%03d.seb", i);
        CFile::CHandle* handle = File.Open(sePath, 0, CFile::PRI_LOW);
        if (handle != 0) {
            File.Read(handle);
            File.SyncCompleted(handle);
            redSound->SetSeBlockData(i, File.m_readBuffer);
            File.Close(handle);
        }
    }
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
 * PAL Address: 0x800c7594
 * PAL Size: 776b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Frame()
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    unsigned char* se = reinterpret_cast<unsigned char*>(this) + 0x2C;

    loadWaveFrame();

    for (u32 i = 0; i < 0x80; i++, se += 0x28) {
        if (static_cast<signed char>(*se) < 0) {
            int volumePan[3];
            int pan;

            calcVolumePan(reinterpret_cast<CSe3D*>(se), volumePan[0], pan);

            if (((*se >> 6) & 1) == 0) {
                int& seId = *reinterpret_cast<int*>(se + 8);
                if (SePlayState__9CRedSoundFi(redSound, seId) == 0) {
                    *se &= 0x7F;
                } else {
                    if (ReportSeLoop__9CRedSoundFi(redSound, seId) != 0 &&
                        GetSeVolume__9CRedSoundFii(redSound, seId, 0) == 0 &&
                        GetSeVolume__9CRedSoundFii(redSound, seId, 1) == 0) {
                        if ((*reinterpret_cast<unsigned int*>(CFlat + 0x129C) & 0x400000) != 0) {
                            Printf__7CSystemFPce(&System, DAT_801db2b8, *reinterpret_cast<int*>(se + 0xC));
                        }
                        SeStop__9CRedSoundFi(redSound, seId);
                        *se = (*se & 0xBF) | 0x40;
                        continue;
                    }

                    if (static_cast<signed char>(se[2]) != pan) {
                        if (seId < 0) {
                            Printf__7CSystemFPce(&System, s_Sound___1_n_B_801db130);
                        } else {
                            SePan__9CRedSoundFiii(redSound, seId, pan, 0x1E);
                        }
                        se[2] = static_cast<unsigned char>(pan);
                    }

                    if (static_cast<signed char>(se[1]) != volumePan[0]) {
                        if (seId < 0) {
                            Printf__7CSystemFPce(&System, s_Sound___1_n_B_801db130);
                        } else {
                            SeVolume__9CRedSoundFiii(redSound, seId, volumePan[0], 0x1E);
                        }
                        se[1] = static_cast<unsigned char>(volumePan[0]);
                    }
                }
            } else if (volumePan[0] != 0) {
                if ((*reinterpret_cast<unsigned int*>(CFlat + 0x129C) & 0x400000) != 0) {
                    Printf__7CSystemFPce(&System, DAT_801db29c, *reinterpret_cast<int*>(se + 0xC));
                }

                int soundId = *reinterpret_cast<int*>(se + 0xC);
                int newSeId;
                if (soundId < 0) {
                    Printf__7CSystemFPce(&System, s_Sound___1_n_B_801db130);
                    newSeId = -1;
                } else if (soundId < 4000) {
                    int bank = soundId / 1000;
                    newSeId = SePlay__9CRedSoundFiiiii(redSound, bank, soundId - bank * 1000, pan, 0, 0);
                    SeVolume__9CRedSoundFiii(redSound, newSeId, volumePan[0], 0x1E);
                } else {
                    newSeId = SePlay__9CRedSoundFiiiii(redSound, -1, soundId, pan, 0, 0);
                    SeVolume__9CRedSoundFiii(redSound, newSeId, volumePan[0], 0x1E);
                }

                *reinterpret_cast<int*>(se + 8) = newSeId;
                *se &= 0xBF;
            }
        }
    }

    int& currentMusicVolume = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x22B8);
    const int targetMusicVolume = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x22BC);
    if (currentMusicVolume != targetMusicVolume) {
        if (currentMusicVolume < targetMusicVolume) {
            currentMusicVolume++;
        } else {
            currentMusicVolume--;
        }
    }

    MusicVolume__9CRedSoundFiii(redSound, -1, currentMusicVolume, 0);
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
    CSound* sound = this;
    int i = 0;
    int count = 4;

    do {
        if (*reinterpret_cast<s16*>(reinterpret_cast<u8*>(sound) + 0x22C0) == -1) {
            *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x22C0 + i * 2) = group;
            return;
        }
        sound = reinterpret_cast<CSound*>(reinterpret_cast<u8*>(sound) + 2);
        i++;
        count--;
    } while (count != 0);

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
    CSound* sound = this;
    int i = 0;
    int count = 4;

    do {
        if (*reinterpret_cast<s16*>(reinterpret_cast<u8*>(sound) + 0x22C8) == -1) {
            *reinterpret_cast<s16*>(reinterpret_cast<u8*>(this) + 0x22C8 + i * 2) = wave;
            return;
        }
        sound = reinterpret_cast<CSound*>(reinterpret_cast<u8*>(sound) + 2);
        i++;
        count--;
    } while (count != 0);

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
