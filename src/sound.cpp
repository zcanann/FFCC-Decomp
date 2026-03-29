#include "ffcc/sound.h"

#include "ffcc/RedSound/RedSound.h"
#include "ffcc/color.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/system.h"
#include "ffcc/line_constants.h"
#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"
#include <Runtime.PPCEABI.H/NMWException.h>
#include "dolphin/ar.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include <math.h>
#include <string.h>

CSound Sound;

extern const float kLineSegmentMinT;
extern const float kLineSegmentMaxT;
extern const float kLineBoundsInitMin;
extern const float kLineBoundsInitMax;

static char s_soundStageName[] = "CSound";
static char s_soundSourceName[] = "sound.cpp";
static char s_soundErrorFmt[] = "Sound\n";
static char s_soundLineOutOfRangeFmt[] = "CSound(%d)\n";
static char s_soundLineTableFullFmt[] = "CSound(%d+)\n";

extern float FLOAT_80330ce8;
extern float FLOAT_80330cf4;
extern float FLOAT_80330cf8;
extern float FLOAT_80330cfc;
extern float FLOAT_80330d00;
extern double DOUBLE_80330d08;
extern double DOUBLE_80330d18;
extern double DOUBLE_80330d20;
extern double DOUBLE_80330d28;
extern "C" void* __vt__6CSound[];
extern "C" void __ct__9CRedSoundFv(void*);
extern "C" void __dt__9CRedSoundFv(void*, short);
extern "C" void __dt__6CSoundFv(void*);
extern "C" unsigned int GetSoundMode__9CRedSoundFv(CRedSound*);
extern "C" void SetSoundMode__9CRedSoundFi(CRedSound*, int);
extern "C" int Init__9CRedSoundFPviii(CRedSound*, void*, int, int, int);
extern "C" void End__9CRedSoundFv(CRedSound*);
extern "C" int StreamPlayState__9CRedSoundFi(CRedSound*, int);
extern "C" void StreamStop__9CRedSoundFi(CRedSound*, int);
extern "C" int StreamPlay__9CRedSoundFPviii(CRedSound*, void*, int, int, int);
extern "C" void StreamVolume__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" int ReentryWaveData__9CRedSoundFi(CRedSound*, int);
extern "C" int ReentrySeSepData__9CRedSoundFi(CRedSound*, int);
extern "C" void SetSeSepData__9CRedSoundFPv(CRedSound*, void*);
extern "C" int SePlayState__9CRedSoundFi(CRedSound*, int);
extern "C" int ReportSeLoop__9CRedSoundFi(CRedSound*, int);
extern "C" int GetSeVolume__9CRedSoundFii(CRedSound*, int, int);
extern "C" unsigned int GetProgramTime__9CRedSoundFv(CRedSound*);
extern "C" void GetStreamPlayPoint__9CRedSoundFiPiPi(CRedSound*, int, int*, int*);
extern "C" unsigned int SetWaveData__9CRedSoundFiPvi(CRedSound*, int, void*, int);
extern "C" int ReportStandby__9CRedSoundFi(CRedSound*, int);
extern "C" void SePause__9CRedSoundFii(CRedSound*, int, int);
extern "C" void StreamPause__9CRedSoundFii(CRedSound*, int, int);
extern "C" void ReportPrint__9CRedSoundFi(CRedSound*, int);
extern "C" void TestProcess__9CRedSoundFi(CRedSound*, int);
extern "C" void DisplayWaveInfo__9CRedSoundFv(CRedSound*);
extern "C" void DisplaySePlayInfo__9CRedSoundFv(CRedSound*);
extern "C" void SeStop__9CRedSoundFi(CRedSound*, int);
extern "C" void SeStopMG__9CRedSoundFiiii(CRedSound*, int, int, int, int);
extern "C" void SeFadeOut__9CRedSoundFii(CRedSound*, int, int);
extern "C" void SePan__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void SePitch__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void SeVolume__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" int SePlay__9CRedSoundFiiiii(CRedSound*, int, int, int, int, int);
extern "C" void ClearSeSepData__9CRedSoundFi(CRedSound*, int);
extern "C" void ClearSeSepDataMG__9CRedSoundFiiii(CRedSound*, int, int, int, int);
extern "C" void ClearWaveData__9CRedSoundFi(CRedSound*, int);
extern "C" void ClearWaveDataM__9CRedSoundFiiii(CRedSound*, int, int, int, int);
extern "C" void MusicVolume__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void MusicMasterVolume__9CRedSoundFi(CRedSound*, int);
extern "C" void SeMasterVolume__9CRedSoundFi(CRedSound*, int);
extern "C" int ReentryMusicData__9CRedSoundFi(CRedSound*, int);
extern "C" void SetMusicData__9CRedSoundFPv(CRedSound*, void*);
extern "C" void MusicStop__9CRedSoundFi(CRedSound*, int);
extern "C" void MusicPlay__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void MusicCrossPlay__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void MusicNextPlay__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void MusicFadeOut__9CRedSoundFii(CRedSound*, int, int);
extern "C" void SetMusicPhraseStop__9CRedSoundFi(CRedSound*, int);
extern "C" void SetReverb__9CRedSoundFii(CRedSound*, int, int);
extern "C" void SetReverbDepth__9CRedSoundFiii(CRedSound*, int, int, int);
extern "C" void ClearWaveBank__9CRedSoundFi(CRedSound*, int);
extern "C" void SetSeBlockData__9CRedSoundFiPv(CRedSound*, int, void*);
extern "C" void Printf__7CSystemFPce(CSystem*, char*, ...);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
u8 ARRAY_802f26c8[0xC];
extern char DAT_801db190[];
extern char DAT_801db1d8[];
extern char DAT_801db29c[];
extern char DAT_801db2b8[];
extern char s_soundNoFreeWaveWarn_801DB0BC[];
extern char s_soundNoFreeSeGroupWarn_801DB0E4[];

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

struct CSoundLayout {
    u32 m_redSoundWord0;
    void* m_stage;
    CFile::CHandle* m_waveFile;
    void* m_aramBuffer;
    int m_waveLoadMode;
    int m_waveRemain;
    int m_waveOffset;
    int m_waveID;
    int m_waveState;
    int m_waveSyncMode;
    int m_seCount;
    u8 m_seWork[0x1400];
    u8 m_lineWork[0xE60];
    void* m_streamBuffer;
    CFile::CHandle* m_streamFile;
    int m_streamOffset;
    int m_streamID;
    u32 m_streamHalf;
    int m_streamPlaying;
    int m_streamRemain;
    int m_streamState;
    int m_streamWaveID;
    int m_bgmMasterVolume;
    int m_seMasterVolume;
    int m_curMusicVolume;
    int m_seMaxVolume;
    s16 m_noFreeSeGroups[4];
    s16 m_noFreeWaves[4];
    int m_pauseAllSe;
    int m_debugPrint;
};

static inline CSoundLayout& SoundData(CSound* self)
{
    return *reinterpret_cast<CSoundLayout*>(self);
}

static inline const CSoundLayout& SoundData(const CSound* self)
{
    return *reinterpret_cast<const CSoundLayout*>(self);
}

static inline CRedSound* RedSound(CSound* self)
{
    return reinterpret_cast<CRedSound*>(reinterpret_cast<u8*>(self) + 8);
}

extern "C" void __ct__9CLine(CLine* line)
{
    line->pointCount = 0;
}

extern "C" int Calc__9CLine(double maxDistance, CLine* line, Vec* outPos, float* outDistance, u32* outIndex,
                             float* outT, const Vec* queryPos)
{
    const bool infiniteRange = ((float)maxDistance == kLineSegmentMinT);
    float bestDistance = infiniteRange ? kLineBoundsInitMin : (float)maxDistance;
    const float maxDistanceSq = (float)(maxDistance * maxDistance);
    int found = 0;
    u32 bestIndex = 0;
    float bestT = kLineSegmentMinT;
    Vec bestPos;

    for (u32 i = 0; i + 1 < line->pointCount; i++) {
        Vec candidate = line->points[i];
        float distanceSq = PSVECSquareDistance(&candidate, queryPos);
        if (distanceSq < maxDistanceSq || infiniteRange) {
            float distance = distanceSq;
            if (distanceSq <= kLineSegmentMinT) {
                distance = NAN;
            } else {
                distance = (float)sqrt(distanceSq);
            }
            if (distance < bestDistance) {
                bestDistance = distance;
                bestPos = candidate;
                bestIndex = i;
                bestT = kLineSegmentMinT;
                found = 1;
            }
        }

        if (i + 1 == line->pointCount - 1) {
            candidate = line->points[i + 1];
            distanceSq = PSVECSquareDistance(&candidate, queryPos);
            if (distanceSq < maxDistanceSq || infiniteRange) {
                float distance = distanceSq;
                if (distanceSq <= kLineSegmentMinT) {
                    distance = NAN;
                } else {
                    distance = (float)sqrt(distanceSq);
                }
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPos = candidate;
                    bestIndex = i;
                    bestT = kLineSegmentMaxT;
                    found = 1;
                }
            }
        }

        const CLineSegment& segment = line->segments[i];
        const float dotQuery = PSVECDotProduct(queryPos, &segment.delta);
        const float dotStart = PSVECDotProduct(&line->points[i], &segment.delta);
        const float t = (dotQuery - dotStart) / (segment.length * segment.length);
        if (((kLineSegmentMinT <= t) && (t <= kLineSegmentMaxT)) || infiniteRange) {
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
    line->min.x = kLineBoundsInitMin;
    line->min.y = kLineBoundsInitMin;
    line->min.z = kLineBoundsInitMin;
    line->max.x = kLineBoundsInitMax;
    line->max.y = kLineBoundsInitMax;
    line->max.z = kLineBoundsInitMax;
    line->totalLength = kLineSegmentMinT;

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
            if (segment.length != kLineSegmentMinT) {
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
    // NOTE: This __sinit is compiler-generated. To match, move the vtable setup
    // (and any sub-construction) into the class constructor, then delete this
    // function. The compiler will auto-generate __sinit from the global object.

    unsigned char* sound = reinterpret_cast<unsigned char*>(&Sound);

    *reinterpret_cast<void**>(sound) = __vt__6CSound;
    __ct__9CRedSoundFv(sound + 8);
    __construct_array(sound + 0x142C, (ConstructorDestructor)__ct__9CLine, 0, 0x1cc, 8);
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
    *reinterpret_cast<void**>(this) = __vt__6CSound;
    __dt__9CRedSoundFv(RedSound(this), -1);
}

/*
 * --INFO--
 * PAL Address: 0x800c810c
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Init()
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    CSoundLayout& sound = SoundData(this);

    CMemory::CStage* stage = Memory.CreateStage(0xA4000, s_soundStageName, 0);
    sound.m_stage = stage;

    sound.m_aramBuffer = new (stage, s_soundSourceName, 0x2E) u8[0x80000];
    sound.m_streamBuffer = new (stage, s_soundSourceName, 0x2F) u8[0x20000];

    sound.m_bgmMasterVolume = 0x7F;
    sound.m_seMasterVolume = 0x7F;
    sound.m_seMaxVolume = 0x7F;
    sound.m_curMusicVolume = 0x7F;
    sound.m_debugPrint = 0;

    ARInit(0, 0);
    ARQInit();

    Init__9CRedSoundFPviii(redSound, sound.m_aramBuffer, 0x80000, 0x800000, 0x800000);
    {
        u32 debugPrint = sound.m_debugPrint;
        ReportPrint__9CRedSoundFi(redSound, (-debugPrint | debugPrint) >> 31);
    }

    {
        u32 soundMode = GetSoundMode__9CRedSoundFv(redSound);
        SetSoundMode__9CRedSoundFi(redSound, (u32)__cntlzw((u32)__cntlzw(soundMode) >> 5) >> 5);
    }

    MusicMasterVolume__9CRedSoundFi(redSound, sound.m_bgmMasterVolume);
    SeMasterVolume__9CRedSoundFi(redSound, sound.m_seMasterVolume);
    SetReverb__9CRedSoundFii(redSound, 1, 4);
    SetReverbDepth__9CRedSoundFiii(redSound, 1, 0x40, 0xF);

    sound.m_waveLoadMode = 0;
    sound.m_streamFile = 0;
    sound.m_streamPlaying = 0;
    memset(sound.m_noFreeSeGroups, 0xFF, sizeof(sound.m_noFreeSeGroups));
    memset(sound.m_noFreeWaves, 0xFF, sizeof(sound.m_noFreeWaves));
    sound.m_pauseAllSe = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800c7f4c
 * PAL Size: 448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Quit()
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    CSoundLayout& sound = SoundData(this);

    CFile::CHandle*& waveFile = sound.m_waveFile;
    if (waveFile != 0) {
        File.Close(waveFile);
        waveFile = 0;
        Printf__7CSystemFPce(&System, DAT_801db190);
    }

    SetWaveData__9CRedSoundFiPvi(redSound, -1, nullptr, 0);

    int shouldStopStream = 0;
    if (sound.m_streamPlaying != 0 && StreamPlayState__9CRedSoundFi(redSound, sound.m_streamID) != 0) {
        shouldStopStream = 1;
    }

    if (shouldStopStream != 0) {
        StreamStop__9CRedSoundFi(redSound, sound.m_streamID);
    }

    CFile::CHandle*& streamFile = sound.m_streamFile;
    if (streamFile != 0) {
        File.Close(streamFile);
        streamFile = 0;
    }

    sound.m_streamPlaying = 0;

    SeStop__9CRedSoundFi(redSound, -1);
    ClearSeSepData__9CRedSoundFi(redSound, -1);
    ClearWaveData__9CRedSoundFi(redSound, -3);

    sound.m_seCount = 10000000;
    memset(sound.m_seWork, 0, sizeof(sound.m_seWork));
    memset(sound.m_noFreeSeGroups, 0xFF, sizeof(sound.m_noFreeSeGroups));
    memset(sound.m_noFreeWaves, 0xFF, sizeof(sound.m_noFreeWaves));

    ClearWaveBank__9CRedSoundFi(redSound, 500);
    ClearWaveBank__9CRedSoundFi(redSound, 0);

    for (int i = 0; i < 4; i++) {
        SetSeBlockData__9CRedSoundFiPv(redSound, i, nullptr);
    }

    End__9CRedSoundFv(redSound);

    void*& streamBuffer = sound.m_streamBuffer;
    if (streamBuffer != 0) {
        delete[] reinterpret_cast<u8*>(streamBuffer);
        streamBuffer = 0;
    }

    void*& aramBuffer = sound.m_aramBuffer;
    if (aramBuffer != 0) {
        delete[] reinterpret_cast<u8*>(aramBuffer);
        aramBuffer = 0;
    }

    Memory.DestroyStage(reinterpret_cast<CMemory::CStage*>(sound.m_stage));
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
    RedSound(this)->SetSoundMode((u32)__cntlzw(stereo) >> 5);
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
    SoundData(this).m_bgmMasterVolume = volume;
    RedSound(this)->MusicMasterVolume(volume);
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
    SoundData(this).m_seMasterVolume = volume;
    RedSound(this)->SeMasterVolume(volume);
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
    CSoundLayout& sound = SoundData(this);

    CFile::CHandle*& waveFile = sound.m_waveFile;
    CFile::CHandle*& streamFile = sound.m_streamFile;
    int& streamPlaying = sound.m_streamPlaying;
    int& streamID = sound.m_streamID;

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

    sound.m_seCount = 10000000;
    memset(sound.m_seWork, 0, sizeof(sound.m_seWork));
    memset(sound.m_noFreeSeGroups, 0xFF, sizeof(sound.m_noFreeSeGroups));
    memset(sound.m_noFreeWaves, 0xFF, sizeof(sound.m_noFreeWaves));

    redSound->ClearWaveBank(500);
    redSound->ClearWaveBank(0);

    for (int i = 0; i < 4; i++) {
        redSound->SetSeBlockData(i, 0);
    }

    redSound->End();

    int streamHeapSize = (isMinMemoryMode != 0) ? 0x200000 : 0x800000;
    int waveHeapSize = (isMinMemoryMode != 0) ? 0xE00000 : 0x800000;
    redSound->Init(sound.m_stage, 0x80000, waveHeapSize, streamHeapSize);

    u32 reportFlag = sound.m_debugPrint;
    redSound->ReportPrint(((-reportFlag) | reportFlag) >> 31);

    u32 soundMode = GetSoundMode__9CRedSoundFv(redSound);
    redSound->SetSoundMode((u32)__cntlzw((u32)__cntlzw(soundMode) >> 5) >> 5);

    redSound->MusicMasterVolume(sound.m_bgmMasterVolume);
    redSound->SeMasterVolume(sound.m_seMasterVolume);

    redSound->SetReverb(1, 4);
    redSound->SetReverbDepth(1, 0x40, 0xF);

    waveFile = 0;
    streamFile = 0;
    streamPlaying = 0;
    memset(sound.m_noFreeSeGroups, 0xFF, sizeof(sound.m_noFreeSeGroups));
    memset(sound.m_noFreeWaves, 0xFF, sizeof(sound.m_noFreeWaves));
    sound.m_pauseAllSe = 0;

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
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 0;
            sound.m_waveSyncMode = 1;
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
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 1;
            sound.m_waveSyncMode = 1;
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
float CSound::GetPerformance()
{
    unsigned int programTime = GetProgramTime__9CRedSoundFv(reinterpret_cast<CRedSound*>(this));
    float numer = (float)(programTime / 0xF);
    float denom = (float)(((OS_BUS_CLOCK / 500000) * 0x8235) >> 3);
    return FLOAT_80330d00 * (numer / denom);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::PauseDiscError(int pause)
{
    if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x22D0) == 0) {
        CRedSound* redSound = reinterpret_cast<CRedSound*>(reinterpret_cast<u8*>(this) + 8);
        pause = static_cast<int>((static_cast<u32>(-pause) | static_cast<u32>(pause)) >> 0x1F);
        SePause__9CRedSoundFii(redSound, -1, pause);
        StreamPause__9CRedSoundFii(redSound, -1, pause);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::CheckDriver(int mode)
{
    CSoundLayout& sound = SoundData(this);
    unsigned int oldPrint = sound.m_debugPrint;
    sound.m_debugPrint = 1;
    ReportPrint__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), 1);
    TestProcess__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), mode);
    DisplayWaveInfo__9CRedSoundFv(reinterpret_cast<CRedSound*>(this));
    DisplaySePlayInfo__9CRedSoundFv(reinterpret_cast<CRedSound*>(this));
    sound.m_debugPrint = oldPrint;
    ReportPrint__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), (-oldPrint | oldPrint) >> 0x1F);
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
    loadWaveFrame();
    unsigned char* se = reinterpret_cast<unsigned char*>(this) + 0x2C;
    u32 i = 0;
    do {
        if (static_cast<signed char>(*se) < 0) {
            int pan;
            int volume[3];

            calcVolumePan(reinterpret_cast<CSe3D*>(se), volume[0], pan);

            if (((*se >> 6) & 1) == 0) {
                if (SePlayState__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8)) == 0) {
                    *se &= 0x7F;
                } else {
                    int playing = ReportSeLoop__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8));
                    if ((playing != 0) &&
                        (GetSeVolume__9CRedSoundFii(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8), 0) == 0) &&
                        (GetSeVolume__9CRedSoundFii(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8), 1) == 0)) {
                        if ((*reinterpret_cast<unsigned int*>(CFlat + 0x129C) & 0x400000) != 0) {
                            Printf__7CSystemFPce(&System, DAT_801db2b8, *reinterpret_cast<int*>(se + 0xC));
                        }
                        SeStop__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8));
                        *se = (*se & 0xBF) | 0x40;
                        goto next;
                    }

                    if (static_cast<signed char>(se[2]) != pan) {
                        if (*reinterpret_cast<int*>(se + 8) < 0) {
                            Printf__7CSystemFPce(&System, s_soundErrorFmt);
                        } else {
                            SePan__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8), pan, 0x1E);
                        }
                        se[2] = static_cast<unsigned char>(pan);
                    }

                    if (static_cast<signed char>(se[1]) != volume[0]) {
                        if (*reinterpret_cast<int*>(se + 8) < 0) {
                            Printf__7CSystemFPce(&System, s_soundErrorFmt);
                        } else {
                            SeVolume__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(se + 8), volume[0], 0x1E);
                        }
                        se[1] = static_cast<unsigned char>(volume[0]);
                    }
                }
            } else if (volume[0] != 0) {
                if ((*reinterpret_cast<unsigned int*>(CFlat + 0x129C) & 0x400000) != 0) {
                    Printf__7CSystemFPce(&System, DAT_801db29c, *reinterpret_cast<int*>(se + 0xC));
                }

                int vol = volume[0];
                int seNo = *reinterpret_cast<int*>(se + 0xC);
                if (seNo < 0) {
                    Printf__7CSystemFPce(&System, s_soundErrorFmt);
                    seNo = -1;
                } else if (seNo < 4000) {
                    int bank = seNo / 1000;
                    seNo = SePlay__9CRedSoundFiiiii(reinterpret_cast<CRedSound*>(this), bank, seNo - (bank * 1000), pan, 0, 0);
                    SeVolume__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), seNo, vol, 0x1E);
                } else {
                    seNo = SePlay__9CRedSoundFiiiii(reinterpret_cast<CRedSound*>(this), -1, seNo, pan, 0, 0);
                    SeVolume__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), seNo, vol, 0x1E);
                }
                *reinterpret_cast<int*>(se + 8) = seNo;
                *se &= 0xBF;
            }
        }
next:
        i++;
        se += 0x28;
    } while (i < 0x80);

    CSoundLayout& sound = SoundData(this);
    int currentMusicVolume = sound.m_curMusicVolume;
    if (currentMusicVolume != sound.m_seMaxVolume) {
        if (currentMusicVolume < sound.m_seMaxVolume) {
            sound.m_curMusicVolume = currentMusicVolume + 1;
        } else {
            sound.m_curMusicVolume = currentMusicVolume - 1;
        }
    }

    MusicVolume__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), -1, sound.m_curMusicVolume, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800c7380
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Draw()
{
    Mtx cameraMatrix;
    PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4), cameraMatrix);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    GXSetZCompLoc((u8)0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
    GXSetZMode((u8)1, (_GXCompare)3, (u8)1);
    GXSetCullMode((_GXCullMode)1);
    GXSetNumTevStages((u8)1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
    GXSetNumChans((u8)1);
    GXSetChanCtrl((GXChannelID)0, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)1);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    CSoundLayout& sound = SoundData(this);
    unsigned char* se = sound.m_seWork;
    for (u32 i = 0; i < 0x80; i++, se += 0x28) {
        if (static_cast<signed char>(*se) < 0) {
            u32 innerColor;
            u32 outerColor;
            Graphic.DrawSphere(cameraMatrix, reinterpret_cast<Vec*>(se + 0x18), *reinterpret_cast<float*>(se + 0x10),
                               static_cast<_GXColor*>(__ct__6CColorFUcUcUcUc(&innerColor, 0xC0, 0xC0, 0xC0, 0x80)));
            Graphic.DrawSphere(cameraMatrix, reinterpret_cast<Vec*>(se + 0x18), *reinterpret_cast<float*>(se + 0x14),
                               static_cast<_GXColor*>(__ct__6CColorFUcUcUcUc(&outerColor, 0x80, 0x80, 0x80, 0x80)));
        }
    }

    u32 lineColorRaw = 0xFF8000FF;
    GXColor lineColor = *reinterpret_cast<GXColor*>(&lineColorRaw);
    GXSetChanMatColor((GXChannelID)4, lineColor);
    GXLoadPosMtxImm(cameraMatrix, 0);

    CLine* line = reinterpret_cast<CLine*>(sound.m_lineWork);
    for (u32 i = 0; i < 8; i++) {
        Draw__9CLine(line);
        line = reinterpret_cast<CLine*>(reinterpret_cast<unsigned char*>(line) + 0x1CC);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c70e4
 * PAL Size: 668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::loadWaveFrame()
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    CSoundLayout& sound = SoundData(this);
    CFile::CHandle*& waveFile = sound.m_waveFile;
    int& waveRemain = sound.m_waveRemain;
    int& waveOffset = sound.m_waveOffset;
    int& waveID = sound.m_waveID;
    int& waveState = sound.m_waveState;
    int& waveSyncMode = sound.m_waveSyncMode;

    if (waveFile != 0) {
        if (waveState == 0) {
            unsigned int readSize = 0x100000;
            if ((unsigned int)waveRemain < readSize) {
                readSize = (unsigned int)waveRemain;
            }

            waveFile->m_chunkSize = readSize;
            waveFile->m_currentOffset = (unsigned int)waveOffset;
            File.ReadASync(waveFile);

            if (waveSyncMode != 0) {
                File.SyncCompleted(waveFile);
            }

            waveRemain -= (int)readSize;
            waveOffset += (int)readSize;
            waveState = 1;
        } else if (waveState == 1 && File.IsCompleted(waveFile)) {
            SetWaveData__9CRedSoundFiPvi(redSound, waveID, File.m_readBuffer, (int)waveFile->m_chunkSize);

            while (ReportStandby__9CRedSoundFi(reinterpret_cast<CRedSound*>(&Sound), 0) != 0) {
            }

            waveState = 0;
            if (waveRemain == 0) {
                File.Close(waveFile);
                waveFile = 0;
            } else {
                waveFile->Reset();
            }
        }
    }

    bool streamPlaying = false;
    int& isStreamEnabled = sound.m_streamPlaying;
    int& streamID = sound.m_streamID;
    if (isStreamEnabled != 0 && StreamPlayState__9CRedSoundFi(redSound, streamID) != 0) {
        streamPlaying = true;
    }

    CFile::CHandle*& streamFile = sound.m_streamFile;
    if (streamPlaying && streamFile != 0) {
        int& streamState = sound.m_streamState;
        int& streamRemain = sound.m_streamRemain;
        int& streamOffset = sound.m_streamOffset;
        u32& streamHalf = sound.m_streamHalf;
        u8* streamBuffer = reinterpret_cast<u8*>(sound.m_streamBuffer);

        if (streamState == 0) {
            int playPoint[2];
            GetStreamPlayPoint__9CRedSoundFiPiPi(redSound, streamID, &playPoint[0], &playPoint[1]);
            unsigned int curHalf = (unsigned int)(playPoint[0] >> 16);

            if (streamHalf != curHalf) {
                int readSize = 0x10000;
                if (streamRemain < readSize) {
                    readSize = streamRemain;
                }

                if (readSize != 0) {
                    streamFile->m_chunkSize = (unsigned int)readSize;
                    streamFile->m_currentOffset = (unsigned int)streamOffset;
                    File.ReadASync(streamFile);

                    streamOffset += readSize;
                    streamRemain -= readSize;
                    streamHalf = curHalf;
                    streamState = 1;
                }
            }
        } else if (File.IsCompleted(streamFile)) {
            memcpy(streamBuffer + (1 - streamHalf) * 0x10000, File.m_readBuffer, 0x10000);
            streamState = 0;

            if (streamRemain == 0) {
                File.Close(streamFile);
                streamFile = 0;
            } else {
                streamFile->Reset();
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6fb0
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadWaveASync(int waveNo, int waveId, int syncMode)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (waveNo < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else if (ReentryWaveData__9CRedSoundFi(redSound, waveNo) == -1) {
        CSoundLayout& sound = SoundData(this);
        CFile::CHandle*& waveFile = sound.m_waveFile;
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, DAT_801db190);
        }

        SetWaveData__9CRedSoundFiPvi(redSound, -1, nullptr, 0);

        char wavePath[260];
        sprintf(wavePath, "dvd/sound/wave/wave_%04d.wd", waveNo);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = waveId;
            sound.m_waveSyncMode = syncMode;

            if (syncMode != 0) {
                while (((u32)__cntlzw((u32)waveFile) >> 5) == 0) {
                    loadWaveFrame();
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6f3c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::CancelLoadWaveASync()
{
    u8* self = reinterpret_cast<u8*>(this);
    CFile::CHandle* handle = *reinterpret_cast<CFile::CHandle**>(self + 0x10);
    if (handle != 0) {
        File.Close(handle);
        *reinterpret_cast<CFile::CHandle**>(self + 0x10) = 0;
        Printf__7CSystemFPce(&System, DAT_801db190);
    }
    SetWaveData__9CRedSoundFiPvi(reinterpret_cast<CRedSound*>(self + 8), -1, nullptr, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800c6f2c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSound::IsLoadWaveASyncCompleted()
{
    CFile::CHandle* waveFile = (*reinterpret_cast<CSoundLayout*>(reinterpret_cast<u8*>(this) + 8)).m_waveFile;
    return (u32)__cntlzw((u32)waveFile) >> 5;
}

/*
 * --INFO--
 * PAL Address: 0x800c6e4c
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadBgm(int bgmId)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else if (ReentryMusicData__9CRedSoundFi(redSound, bgmId) == -1) {
        char musicPath[256];
        sprintf(musicPath, "dvd/sound/music/music_%03d.bgm", bgmId);

        CFile::CHandle* handle = File.Open(musicPath, 0, CFile::PRI_LOW);
        if (handle != 0) {
            File.Read(handle);
            File.SyncCompleted(handle);
            SetMusicData__9CRedSoundFPv(redSound, File.m_readBuffer);
            File.Close(handle);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6dcc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::PlayBgm(int bgmId)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        MusicStop__9CRedSoundFi(redSound, -1);
        SetMusicPhraseStop__9CRedSoundFi(redSound, 0);
        MusicPlay__9CRedSoundFiii(redSound, bgmId, 0x7F, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6d4c
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::CrossPlayBgm(int bgmId, int crossFrames)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        SetMusicPhraseStop__9CRedSoundFi(redSound, 0);
        MusicCrossPlay__9CRedSoundFiii(redSound, bgmId, 0x7F, crossFrames);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6ce4
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::PlayNextBgm(int bgmId)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        MusicNextPlay__9CRedSoundFiii(redSound, bgmId, 0x7F, 0);
        SetMusicPhraseStop__9CRedSoundFi(redSound, 1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6cbc
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::StopBgm()
{
    MusicStop__9CRedSoundFi(RedSound(this), -1);
}

/*
 * --INFO--
 * PAL Address: 0x800c6c90
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::FadeOutBgm(int fadeFrames)
{
    MusicFadeOut__9CRedSoundFii(RedSound(this), -1, fadeFrames);
}

/*
 * --INFO--
 * PAL Address: 0x800c6a20
 * PAL Size: 624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadBlock()
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    CSoundLayout& sound = SoundData(this);
    CFile::CHandle*& waveFile = sound.m_waveFile;

    if (ReentryWaveData__9CRedSoundFi(redSound, 0) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, DAT_801db190);
        }

        redSound->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, "dvd/sound/wave/wave_%04d.wd", 0);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 0;
            sound.m_waveSyncMode = 1;
            while (waveFile != 0) {
                loadWaveFrame();
            }
        }
    }

    if (ReentryWaveData__9CRedSoundFi(redSound, 500) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, DAT_801db190);
        }

        redSound->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, "dvd/sound/wave/wave_%04d.wd", 500);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 1;
            sound.m_waveSyncMode = 1;
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
 * PAL Address: 0x800c69b8
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::FreeBlock()
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    redSound->ClearWaveBank(500);
    redSound->ClearWaveBank(0);
    for (int i = 0; i < 4; i++) {
        redSound->SetSeBlockData(i, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c68a4
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadSe(int seId)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (seId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else if (ReentrySeSepData__9CRedSoundFi(redSound, seId) == -1) {
        char sePath[264];
        sprintf(sePath, "dvd/sound/se_sep/se_%06d.sep", seId);
        CFile::CHandle* handle = File.Open(sePath, 0, CFile::PRI_LOW);
        if (handle != 0) {
            File.Read(handle);
            File.SyncCompleted(handle);
            SetSeSepData__9CRedSoundFPv(redSound, File.m_readBuffer);
            File.Close(handle);
            if (System.m_execParam != 0) {
                Printf__7CSystemFPce(&System, "CSound::LoadSe[%d]\n", seId);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6850
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadSe(void* seData)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    if (ReentrySeSepData__9CRedSoundFi(redSound, *reinterpret_cast<s32*>((u8*)seData + 8)) == -1) {
        SetSeSepData__9CRedSoundFPv(redSound, seData);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c66bc
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadWave(int waveId)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    CSoundLayout& sound = SoundData(this);
    CFile::CHandle*& waveFile = sound.m_waveFile;

    if (waveId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        if (ReentryWaveData__9CRedSoundFi(redSound, waveId) == -1) {
            if (waveId < 0) {
                Printf__7CSystemFPce(&System, s_soundErrorFmt);
            } else if (ReentryWaveData__9CRedSoundFi(redSound, waveId) == -1) {
                if (waveFile != 0) {
                    File.Close(waveFile);
                    waveFile = 0;
                    Printf__7CSystemFPce(&System, DAT_801db190);
                }

                SetWaveData__9CRedSoundFiPvi(redSound, -1, nullptr, 0);

                char wavePath[260];
                sprintf(wavePath, "dvd/sound/wave/wave_%04d.wd", waveId);
                waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);

                if (waveFile != 0) {
                    sound.m_waveRemain = File.GetLength(waveFile);
                    sound.m_waveOffset = 0;
                    sound.m_waveState = 0;
                    sound.m_waveID = -1;
                    sound.m_waveSyncMode = 1;
                    while (waveFile != 0) {
                        loadWaveFrame();
                    }
                }
            }

            if (System.m_execParam != 0) {
                Printf__7CSystemFPce(&System, DAT_801db1d8, waveId);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6614
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadWave(void* waveData)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    CFile::CHandle*& waveFile = SoundData(this).m_waveFile;

    if (ReentryWaveData__9CRedSoundFi(redSound, reinterpret_cast<s16*>(waveData)[1]) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, DAT_801db190);
        }
        SetWaveData__9CRedSoundFiPvi(redSound, -1, nullptr, 0);
        SetWaveData__9CRedSoundFiPvi(redSound, -1, waveData, -1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c65cc
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::FreeWave(int waveId)
{
    if (waveId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        ClearWaveData__9CRedSoundFi(RedSound(this), waveId);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c64f0
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::StopAndFreeAllSe(int clearMode)
{
    CSoundLayout& sound = SoundData(this);
    if (clearMode != 0) {
        SeStop__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), -1);
        ClearSeSepData__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), -1);
        ClearWaveData__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), -3);
    } else {
        SeStopMG__9CRedSoundFiiii(reinterpret_cast<CRedSound*>(this),
                                  sound.m_noFreeSeGroups[0],
                                  sound.m_noFreeSeGroups[1],
                                  sound.m_noFreeSeGroups[2],
                                  sound.m_noFreeSeGroups[3]);
        ClearSeSepDataMG__9CRedSoundFiiii(reinterpret_cast<CRedSound*>(this),
                                          sound.m_noFreeSeGroups[0],
                                          sound.m_noFreeSeGroups[1],
                                          sound.m_noFreeSeGroups[2],
                                          sound.m_noFreeSeGroups[3]);
        ClearWaveDataM__9CRedSoundFiiii(reinterpret_cast<CRedSound*>(this),
                                        sound.m_noFreeWaves[0],
                                        sound.m_noFreeWaves[1],
                                        sound.m_noFreeWaves[2],
                                        sound.m_noFreeWaves[3]);
    }

    sound.m_seCount = 10000000;
    memset(sound.m_seWork, 0, sizeof(sound.m_seWork));
    memset(sound.m_noFreeSeGroups, 0xFF, sizeof(sound.m_noFreeSeGroups));
    memset(sound.m_noFreeWaves, 0xFF, sizeof(sound.m_noFreeWaves));
}

/*
 * --INFO--
 * PAL Address: 0x800c63b8
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSound::PlaySe(int seNo, int pan, int volume, int fadeFrames)
{
    int seId;
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);

    if (seNo < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
        seId = -1;
    } else if (seNo < 4000) {
        const int seBank = seNo / 1000;
        seId = SePlay__9CRedSoundFiiiii(redSound, seBank, seNo - seBank * 1000, pan,
                                        volume & ~((-fadeFrames | fadeFrames) >> 0x1F), 0);
        if (fadeFrames != 0) {
            SeVolume__9CRedSoundFiii(redSound, seId, volume, fadeFrames);
        }
    } else {
        seId = SePlay__9CRedSoundFiiiii(redSound, -1, seNo, pan, volume & ~((-fadeFrames | fadeFrames) >> 0x1F), 0);
        if (fadeFrames != 0) {
            SeVolume__9CRedSoundFiii(redSound, seId, volume, fadeFrames);
        }
    }

    return seId;
}

/*
 * --INFO--
 * PAL Address: 0x800c6370
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::StopSe(int seId)
{
    if (seId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        SeStop__9CRedSoundFi(RedSound(this), seId);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c6328
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::FadeOutSe(int seId, int fadeFrames)
{
    if (seId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        SeFadeOut__9CRedSoundFii(RedSound(this), seId, fadeFrames);
    }
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
 * PAL Address: 0x800c601c
 * PAL Size: 780b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::calcVolumePan(CSound::CSe3D* se3D, int& outVolume, int& outPan)
{
    u8* se = reinterpret_cast<u8*>(se3D);
    float fVar1;
    float fVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    float nearestDistance;
    float nearestT;
    Vec nearestPoint;

    if (static_cast<s8>(se[3]) >= 0) {
        iVar4 = Calc__9CLine((double)*reinterpret_cast<float*>(se + 0x14),
                             reinterpret_cast<CLine*>(SoundData(this).m_lineWork + ((int)static_cast<s8>(se[3]) * 0x1CC)),
                             &nearestPoint, &nearestDistance, (u32*)0, &nearestT,
                             reinterpret_cast<const Vec*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE0));
        if (iVar4 == 0) {
            outVolume = 0;
            outPan = 0x40;
        } else {
            PSMTXMultVec(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4), &nearestPoint,
                         &nearestPoint);
            fVar3 = *reinterpret_cast<float*>(se + 0x10);
            if (fVar3 <= nearestDistance) {
                outVolume = 0x7F - (int)(FLOAT_80330ce8 * ((nearestDistance - fVar3) / (*reinterpret_cast<float*>(se + 0x14) - fVar3)));
            } else {
                outVolume = 0x7F;
            }

            iVar4 = (int)nearestPoint.x;
            if (iVar4 < -0x38) {
                iVar5 = -0x38;
            } else {
                iVar5 = 0x38;
                if (iVar4 < 0x39) {
                    iVar5 = iVar4;
                }
            }
            outPan = iVar5 + 0x40;
        }
    } else if ((kLineSegmentMinT == *reinterpret_cast<float*>(se + 0x10)) &&
               (kLineSegmentMinT == *reinterpret_cast<float*>(se + 0x14))) {
        outVolume = 0x7F;
        outPan = 0x40;
    } else {
        fVar1 = kLineSegmentMaxT;
        if (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(&Game) + 0x13E4) != '\0') {
            const short stageId = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(&Game) + 0x13E0);
            if (stageId == 0xE) {
                fVar1 = FLOAT_80330cf4;
            } else if (stageId == 8) {
                fVar1 = FLOAT_80330cf4;
            } else {
                fVar1 = FLOAT_80330cf8;
            }
        }

        PSMTXMultVec(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4),
                     reinterpret_cast<Vec*>(se + 0x18), &nearestPoint);
        fVar3 = fVar1 * PSVECSquareDistance(reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xD4),
                                            reinterpret_cast<Vec*>(se + 0x18));
        fVar2 = *reinterpret_cast<float*>(se + 0x14) * fVar1;
        fVar2 = *reinterpret_cast<float*>(se + 0x14) * fVar2;
        fVar2 = fVar1 * fVar2;
        if (fVar2 <= fVar3) {
            outVolume = 0;
        } else {
            float nearScaled = *reinterpret_cast<float*>(se + 0x10) * fVar1;
            nearScaled = *reinterpret_cast<float*>(se + 0x10) * nearScaled;
            if (nearScaled <= fVar3) {
                outVolume = 0x7F - (int)(FLOAT_80330ce8 * ((fVar3 - nearScaled) / (fVar2 - nearScaled)));
            } else {
                outVolume = 0x7F;
            }
        }

        if (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&Game) + 0xC7F4) == 0x21) {
            iVar4 = (int)(nearestPoint.x / FLOAT_80330cfc);
        } else {
            iVar4 = (int)nearestPoint.x;
        }
        if (iVar4 < -0x38) {
            iVar5 = -0x38;
        } else {
            iVar5 = 0x38;
            if (iVar4 < 0x39) {
                iVar5 = iVar4;
            }
        }
        outPan = iVar5 + 0x40;
    }

    if (SoundData(this).m_curMusicVolume < outVolume) {
        outVolume = SoundData(this).m_curMusicVolume;
    }
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
 * PAL Address: 0x800c5e2c
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSound::PlaySe3D(int soundId, Vec* pos, float nearDistance, float farDistance, int fadeFrames)
{
    u8* se;
    int slot;
    int pan;
    int volume[4];
    CRedSound* redSound;

    if (soundId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        CSoundLayout& sound = SoundData(this);
        redSound = RedSound(this);
        se = sound.m_seWork;
        slot = 0x80;
        do {
            if (static_cast<s8>(*se) >= 0) {
                *se = (*se & 0x7F) | 0x80;
                *se &= 0xBF;
                *reinterpret_cast<int*>(se + 0xC) = soundId;
                slot = sound.m_seCount;
                sound.m_seCount = slot + 1;
                *reinterpret_cast<int*>(se + 4) = slot;

                *reinterpret_cast<float*>(se + 0x10) = nearDistance;
                *reinterpret_cast<float*>(se + 0x14) = farDistance;
                *reinterpret_cast<Vec*>(se + 0x18) = *pos;
                se[3] = 0xFF;

                calcVolumePan(reinterpret_cast<CSe3D*>(se), volume[0], pan);
                se[1] = static_cast<u8>(volume[0]);
                se[2] = static_cast<u8>(pan);
                se[0x24] = 0xFF;
                se[0x25] = 0xFF;
                se[0x26] = 0xFF;
                se[0x27] = 0xFF;

                if (soundId < 0) {
                    Printf__7CSystemFPce(&System, s_soundErrorFmt);
                    slot = -1;
                } else if (soundId < 4000) {
                    slot = soundId / 1000 + (soundId >> 31);
                    slot = SePlay__9CRedSoundFiiiii(redSound, slot - (slot >> 31),
                                                    soundId + (slot - (slot >> 31)) * -1000, pan,
                                                    volume[0] & ~((int)(-fadeFrames | fadeFrames) >> 0x1F), 0);
                    if (fadeFrames != 0) {
                        SeVolume__9CRedSoundFiii(redSound, slot, volume[0], fadeFrames);
                    }
                } else {
                    slot = SePlay__9CRedSoundFiiiii(redSound, -1, soundId, pan,
                                                    volume[0] & ~((int)(-fadeFrames | fadeFrames) >> 0x1F), 0);
                    if (fadeFrames != 0) {
                        SeVolume__9CRedSoundFiii(redSound, slot, volume[0], fadeFrames);
                    }
                }

                *reinterpret_cast<int*>(se + 8) = slot;
                return *reinterpret_cast<int*>(se + 4);
            }
            se += 0x28;
            slot--;
        }
        while (slot != 0);
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800c5c58
 * PAL Size: 468b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSound::PlaySe3DLine(int soundId, int lineIndex, float nearDistance, float farDistance, int fadeFrames)
{
    if (soundId < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        CSoundLayout& sound = SoundData(this);
        u8* se = sound.m_seWork;
        for (int i = 0; i < 0x80; i++, se += 0x28) {
            if (static_cast<s8>(*se) >= 0) {
                int volume;
                int pan;

                *se = (*se & 0x7F) | 0x80;
                *se &= 0xBF;
                *reinterpret_cast<int*>(se + 0xC) = soundId;

                int& seCount = sound.m_seCount;
                const int seIndex = seCount;
                seCount = seIndex + 1;
                *reinterpret_cast<int*>(se + 4) = seIndex;

                *reinterpret_cast<float*>(se + 0x10) = nearDistance;
                *reinterpret_cast<float*>(se + 0x14) = farDistance;
                se[3] = static_cast<u8>(lineIndex);

                calcVolumePan(reinterpret_cast<CSe3D*>(se), volume, pan);
                se[1] = static_cast<u8>(volume);
                se[2] = static_cast<u8>(pan);
                se[0x24] = 0xFF;
                se[0x25] = 0xFF;
                se[0x26] = 0xFF;
                se[0x27] = 0xFF;

                int sePlayId;
                if (soundId < 0) {
                    Printf__7CSystemFPce(&System, s_soundErrorFmt);
                    sePlayId = -1;
                } else if (soundId < 4000) {
                    int bank = soundId / 1000 + (soundId >> 31);
                    bank -= (bank >> 31);

                    const u32 fade = static_cast<u32>(fadeFrames);
                    const int firstVolume = volume & ~((int)((-fade) | fade) >> 0x1F);
                    sePlayId = SePlay__9CRedSoundFiiiii(reinterpret_cast<CRedSound*>(this), bank,
                                                        soundId + bank * -1000, pan, firstVolume, 0);
                    if (fade != 0) {
                        SeVolume__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), sePlayId, volume, fade);
                    }
                } else {
                    const u32 fade = static_cast<u32>(fadeFrames);
                    const int firstVolume = volume & ~((int)((-fade) | fade) >> 0x1F);
                    sePlayId = SePlay__9CRedSoundFiiiii(reinterpret_cast<CRedSound*>(this), -1, soundId, pan, firstVolume, 0);
                    if (fade != 0) {
                        SeVolume__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), sePlayId, volume, fade);
                    }
                }

                *reinterpret_cast<int*>(se + 8) = sePlayId;
                return *reinterpret_cast<int*>(se + 4);
            }
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800c5b7c
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSound::SetSe3DGroup(int se3dHandle, int group)
{
    if (se3dHandle < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        char* se = reinterpret_cast<char*>(this) + 0x2C;
        char* found;
        int count = 0x20;
        do {
            if ((*se < 0 &&
                  (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
                 (se[0x28] < 0 &&
                  (found = se + 0x28, *reinterpret_cast<int*>(se + 0x2C) == se3dHandle)) ||
                 (se[0x50] < 0 &&
                  (found = se + 0x50, *reinterpret_cast<int*>(se + 0x54) == se3dHandle)) ||
                 (se[0x78] < 0 &&
                  (found = se + 0x78, *reinterpret_cast<int*>(se + 0x7C) == se3dHandle))) {
                goto found_se;
            }
            se += 0xA0;
            count--;
        } while (count != 0);
        found = 0;
found_se:
        if (found != 0) {
            *reinterpret_cast<int*>(found + 0x24) = group;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c5a08
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::StopSe3DGroup(int group)
{
    u8* se = reinterpret_cast<u8*>(this) + 0x2C;
    u32 i = 0;

    do {
        if ((static_cast<s8>(*se) < 0) && (-1 < *reinterpret_cast<int*>(se + 0x24)) &&
            (*reinterpret_cast<int*>(se + 0x24) == group)) {
            int se3dHandle = *reinterpret_cast<int*>(se + 4);
            if (se3dHandle < 0) {
                Printf__7CSystemFPce(&System, s_soundErrorFmt);
            } else {
                u8* search = reinterpret_cast<u8*>(this) + 0x2C;
                int count = 0x20;
                u8* found;
                do {
                    if (((static_cast<s8>(search[0]) < 0 &&
                          (found = search, *reinterpret_cast<int*>(search + 4) == se3dHandle)) ||
                         (found = search + 0x28, static_cast<s8>(*found) < 0 &&
                          (*reinterpret_cast<int*>(search + 0x2C) == se3dHandle)) ||
                         (found = search + 0x50, static_cast<s8>(*found) < 0 &&
                          (*reinterpret_cast<int*>(search + 0x54) == se3dHandle)) ||
                         (static_cast<s8>(search[0x78]) < 0 &&
                          (found = search + 0x78, *reinterpret_cast<int*>(search + 0x7C) == se3dHandle)))) {
                        goto found_se;
                    }
                    search += 0xA0;
                    count--;
                } while (count != 0);
                found = 0;
found_se:

                if (found != 0) {
                    int playId = *reinterpret_cast<int*>(found + 8);
                    if (playId < 0) {
                        Printf__7CSystemFPce(&System, s_soundErrorFmt);
                    } else {
                        SeStop__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), playId);
                    }
                    *found &= 0x7F;
                }
            }
            *se &= 0x7F;
        }
        i++;
        se += 0x28;
        if (0x7F < i) {
            return;
        }
    } while (true);
}

/*
 * --INFO--
 * PAL Address: 0x800c58e8
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::StopSe3D(int se3dHandle)
{
    if (se3dHandle < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        u8* se = reinterpret_cast<u8*>(this) + 0x2C;
        u8* found;
        int idx = 0;
        int count = 0x20;
        do {
            if (((((static_cast<s8>(*se) < 0) && (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
                  ((found = se + 0x28), static_cast<s8>(*found) < 0 && *reinterpret_cast<int*>(se + 0x2C) == se3dHandle)) ||
                 ((found = se + 0x50), static_cast<s8>(*found) < 0 && *reinterpret_cast<int*>(se + 0x54) == se3dHandle)) ||
                (static_cast<s8>(se[0x78]) < 0 && (found = se + 0x78, *reinterpret_cast<int*>(se + 0x7C) == se3dHandle))) {
                goto found_entry;
            }
            idx += 3;
            se += 0xA0;
            count--;
        } while (count != 0);
        found = 0;

found_entry:
        if (found != 0) {
            const int playId = *reinterpret_cast<int*>(found + 8);
            if (playId < 0) {
                Printf__7CSystemFPce(&System, s_soundErrorFmt, idx);
            } else {
                SeStop__9CRedSoundFi(reinterpret_cast<CRedSound*>(this), playId);
            }
            *found &= 0x7F;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c57c8
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
_pppMngSt* CSound::FadeOutSe3D(int se3dHandle, int fadeFrames)
{
    if (se3dHandle < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
        return 0;
    }

    u8* se = reinterpret_cast<u8*>(this) + 0x2C;
    u8* found;
    int ret = 0;
    int count = 0x20;
    do {
        if (((((static_cast<s8>(*se) < 0) && (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
              ((found = se + 0x28), static_cast<s8>(*found) < 0 && *reinterpret_cast<int*>(se + 0x2C) == se3dHandle)) ||
             ((found = se + 0x50), static_cast<s8>(*found) < 0 && *reinterpret_cast<int*>(se + 0x54) == se3dHandle)) ||
            (static_cast<s8>(se[0x78]) < 0 && (found = se + 0x78, *reinterpret_cast<int*>(se + 0x7C) == se3dHandle))) {
            goto found_entry;
        }
        ret += 3;
        se += 0xA0;
        count--;
    } while (count != 0);
    found = 0;

found_entry:
    if (found != 0) {
        const int playId = *reinterpret_cast<int*>(found + 8);
        if (playId < 0) {
            Printf__7CSystemFPce(&System, s_soundErrorFmt, fadeFrames, ret);
        } else {
            SeFadeOut__9CRedSoundFii(reinterpret_cast<CRedSound*>(this), playId, fadeFrames);
        }
        *found &= 0x7F;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800c56d8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CSound::ChangeSe3DPos(int se3dHandle, Vec* position)
{
    int ret;

    if (se3dHandle < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
        ret = 0;
    } else {
        char* se = reinterpret_cast<char*>(this) + 0x2C;
        char* found;
        ret = 0;
        int count = 0x20;
        do {
            if ((((*se < 0) && (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
                 ((found = se + 0x28), found[0] < 0 && (*reinterpret_cast<int*>(se + 0x2C) == se3dHandle))) ||
                ((found = se + 0x50), found[0] < 0 && (*reinterpret_cast<int*>(se + 0x54) == se3dHandle)) ||
                (se[0x78] < 0 && (found = se + 0x78, *reinterpret_cast<int*>(se + 0x7C) == se3dHandle))) {
                goto found_entry;
            }
            ret += 3;
            se += 0xA0;
            count--;
        } while (count != 0);
        found = 0;
found_entry:
        if (found != 0) {
            *reinterpret_cast<float*>(found + 0x18) = position->x;
            *reinterpret_cast<float*>(found + 0x1C) = position->y;
            *reinterpret_cast<float*>(found + 0x20) = position->z;
        }
    }
    return ret;
}

/*
 * --INFO--
 * PAL Address: 0x800c55f0
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::ChangeSe3DPitch(int se3dHandle, int pitch, int frames)
{
    if (se3dHandle < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
        return;
    }

    s8* se = reinterpret_cast<s8*>(this) + 0x2C;
    s8* found = 0;
    int remaining = 0x20;
    while (remaining != 0) {
        found = se;
        if ((se[0] < 0) && (*reinterpret_cast<int*>(se + 4) == se3dHandle)) {
            break;
        }

        found = se + 0x28;
        u8 secondMatched = 0;
        if ((se[0x28] < 0) && (*reinterpret_cast<int*>(se + 0x2C) == se3dHandle)) {
            secondMatched = 1;
        }
        if (secondMatched != 0) {
            break;
        }

        found = se + 0x50;
        u8 thirdMatched = 0;
        if ((se[0x50] < 0) && (*reinterpret_cast<int*>(se + 0x54) == se3dHandle)) {
            thirdMatched = 1;
        }
        if (thirdMatched != 0) {
            break;
        }

        if ((se[0x78] < 0) && (*reinterpret_cast<int*>(se + 0x7C) == se3dHandle)) {
            found = se + 0x78;
            break;
        }

        remaining--;
        se += 0xA0;
        found = 0;
    }

    if (found != 0) {
        SePitch__9CRedSoundFiii(reinterpret_cast<CRedSound*>(this), *reinterpret_cast<int*>(found + 8), pitch << 8, frames);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c558c
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Clear3DLine(int lineIndex)
{
    if ((u32)lineIndex >= 8) {
        Printf__7CSystemFPce(&System, s_soundLineOutOfRangeFmt);
    }

    reinterpret_cast<CLine*>(reinterpret_cast<u8*>(this) + 0x142C)[lineIndex].pointCount = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800c5508
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::Add3DLine(int lineIndex, Vec* position)
{
    CLine* line = reinterpret_cast<CLine*>(SoundData(this).m_lineWork + lineIndex * sizeof(CLine));
    const u32 pointCount = line->pointCount;

    if (pointCount < 10) {
        line->pointCount = pointCount + 1;
        line->points[pointCount] = *position;
        CalcBound__9CLine2(line);
    } else {
        Printf__7CSystemFPce(&System, s_soundLineTableFullFmt);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c54ac
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::SetReverb(int reverb, int depth)
{
    CRedSound* redSound = reinterpret_cast<CRedSound*>(this);
    redSound->SetReverb(1, reverb);
    redSound->SetReverbDepth(1, depth, 0xF);
}

/*
 * --INFO--
 * PAL Address: 0x800c5318
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::LoadStream(int streamID)
{
    if (streamID < 0) {
        Printf__7CSystemFPce(&System, s_soundErrorFmt);
    } else {
        CSoundLayout& sound = SoundData(this);
        bool isPlaying = false;

        if (sound.m_streamPlaying != 0) {
            if (StreamPlayState__9CRedSoundFi(RedSound(this), sound.m_streamID) != 0) {
                isPlaying = true;
            }
        }

        if (isPlaying) {
            StreamStop__9CRedSoundFi(RedSound(this), sound.m_streamID);
        }

        CFile::CHandle*& streamFile = sound.m_streamFile;
        if (streamFile != 0) {
            File.Close(streamFile);
            streamFile = 0;
        }

        sound.m_streamPlaying = 0;

        char streamPath[268];
        sprintf(streamPath, "dvd/sound/stream/str_%04d.str", streamID);
        streamFile = File.Open(streamPath, 0, CFile::PRI_LOW);
        if (streamFile != 0) {
            streamFile->m_chunkSize = 0x20000;
            streamFile->m_currentOffset = 0;
            File.Read(streamFile);
            File.SyncCompleted(streamFile);
            memcpy(sound.m_streamBuffer, File.m_readBuffer, 0x20000);
            sound.m_streamOffset = 0x20000;
            sound.m_streamHalf = 0;
            sound.m_streamRemain = File.GetLength(streamFile) - 0x20000;
            sound.m_streamState = 0;
            sound.m_streamWaveID = streamID;
            File.Close(streamFile);
            streamFile = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c51f8
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::PlayStreamASync()
{
    char streamPath[268];
    CSoundLayout& sound = SoundData(this);
    sprintf(streamPath, "dvd/sound/stream/str_%04d.str", sound.m_streamWaveID);

    sound.m_streamFile = File.Open(streamPath, 0, CFile::PRI_LOW);
    if (sound.m_streamFile == 0) {
        return;
    }

    int streamId = sound.m_streamWaveID;
    int volume;
    if (streamId == 5 || streamId == 1) {
        volume = sound.m_bgmMasterVolume;
        if (streamId == 1) {
            volume -= (volume * 0x19) / 0x7f;
        }
    } else if (streamId > 0 && streamId < 7) {
        volume = 0x7f;
        if (streamId == 6) {
            volume = 0x70;
        }
    } else {
        volume = sound.m_seMasterVolume;
    }
    int clampedVolume;
    if (volume < 0) {
        clampedVolume = 0;
    } else if (volume > 0x7f) {
        clampedVolume = 0x7f;
    } else {
        clampedVolume = volume;
    }

    int streamNo = StreamPlay__9CRedSoundFPviii(
        reinterpret_cast<CRedSound*>(this), sound.m_streamBuffer, 0x20000, 0x40, clampedVolume);
    sound.m_streamID = streamNo;
    sound.m_streamPlaying = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800c5164
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::StopStream()
{
    CSoundLayout& sound = SoundData(this);
    bool shouldStop = false;

    if (sound.m_streamPlaying != 0) {
        int state = StreamPlayState__9CRedSoundFi(RedSound(this), sound.m_streamID);
        if (state != 0) {
            shouldStop = true;
        }
    }

    if (shouldStop) {
        StreamStop__9CRedSoundFi(RedSound(this), sound.m_streamID);
    }

    CFile::CHandle* handle = sound.m_streamFile;
    if (handle != 0) {
        File.Close(handle);
        sound.m_streamFile = 0;
    }
    sound.m_streamPlaying = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800c5130
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::SetStreamVolume(int volume, int frames)
{
    StreamVolume__9CRedSoundFiii(RedSound(this), -1, volume, frames);
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
    int pauseFlag = (pause != 0);
    CRedSound* redSound = RedSound(this);
    SePause__9CRedSoundFii(redSound, -1, pauseFlag);
    StreamPause__9CRedSoundFii(redSound, -1, pauseFlag);
    SoundData(this).m_pauseAllSe = pause;
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
    for (int i = 0; i < 4; i++) {
        if (SoundData(this).m_noFreeSeGroups[i] == -1) {
            SoundData(this).m_noFreeSeGroups[i] = static_cast<s16>(group);
            return;
        }
    }

    if ((unsigned int)System.m_execParam < 1) {
        return;
    }

    Printf__7CSystemFPce(&System, s_soundNoFreeSeGroupWarn_801DB0E4);
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
    for (int i = 0; i < 4; i++) {
        if (SoundData(this).m_noFreeWaves[i] == -1) {
            SoundData(this).m_noFreeWaves[i] = static_cast<s16>(wave);
            return;
        }
    }

    if ((unsigned int)System.m_execParam < 1) {
        return;
    }

    Printf__7CSystemFPce(&System, s_soundNoFreeWaveWarn_801DB0BC);
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
