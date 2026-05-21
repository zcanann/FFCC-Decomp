#include "ffcc/sound.h"

#include "ffcc/RedSound/RedGlobals.h"
#include "ffcc/RedSound/RedSound.h"
#include "ffcc/color.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
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
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern const char s_CSound_80330ce0[] = "CSound";
extern const char s_CManager_801DB0B0[] = "CManager";
extern const float FLOAT_80330ce8 = 127.0f;
extern const float kLineSegmentMinT = 0.0f;
extern const float kLineSegmentMaxT = 1.0f;
extern const float FLOAT_80330cf4 = 5.0f;
extern const float FLOAT_80330cf8 = 3.0f;
extern const float FLOAT_80330cfc = 2.5f;
extern const float FLOAT_80330d00 = 100.0f;
extern const double DOUBLE_80330d08 = 4503599627370496.0;
extern const float kLineBoundsInitMin = 10000000.0f;
extern const double DOUBLE_80330d18 = 0.5;
extern const char s_soundNoFreeWaveWarn_801DB0BC[40] =
    "\x82\xb1\x82\xea\x88\xc8\x8f\xe3noFreeWaev\x82\xf0\x92\xc7\x89\xc1\x82\xc5"
    "\x82\xab\x82\xdc\x82\xb9\x82\xf1\x81\x42\n";
extern const char s_soundNoFreeSeGroupWarn_801DB0E4[44] =
    "\x82\xb1\x82\xea\x88\xc8\x8f\xe3noFreeSeGroup\x82\xf0\x92\xc7\x89\xc1\x82\xc5"
    "\x82\xab\x82\xdc\x82\xb9\x82\xf1\x81\x42\n";
extern const char s_dvd_sound_stream_strpct04d_str_801DB110[] = "dvd/sound/stream/str%04d.str";
extern const char s_soundMinusOneFmt[28] =
    "Sound: -1\x82\xaa\x93\x6E\x82\xb3\x82\xea\x82\xdc\x82\xb5\x82\xbd\x81\x42\n";
extern const char s_soundLineTableFullFmt[] =
    "CSound: \x83\x89\x83\x43\x83\x93\x82\xcc\x92\xb8\x93\x5F\x82\xaa\x91\xbd\x82\xb7"
    "\x82\xac\x82\xdc\x82\xb7\x81\x42\n";
extern const char s_soundLineOutOfRangeFmt[32] =
    "CSound: \x83\x89\x83\x43\x83\x93\x82\xaa\x91\xbd\x82\xb7\x82\xac\x82\xdc\x82\xb7"
    "\x81\x42\n";
static const char s_soundLoadWaveErrorFmt[] =
    "\x94\x67\x8C\x60\x83\x66\x81\x5B\x83\x5E\x82\xCC\x93\x5D\x91\x97\x92\x86\x82\xC9"
    "\x83\x4C\x83\x83\x83\x93\x83\x5A\x83\x8B\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD"
    "\x81\x42\n";
static const char s_soundWavePathFmt[] = "dvd/sound/wave/wave%04d.wd";
static const char s_soundLoadWaveMergeFmt[] =
    "\x1B[31mMerge: \x94\x67\x8C\x60\x82\xF0" "DVD\x82\xA9\x82\xE7\x93\xC7\x82\xDD\x8D\x9E"
    "\x82\xDD\x82\xDC\x82\xB5\x82\xBD\x81\x42%d\n\x1B[0m";
static const char s_soundSeSepPathFmt[] = "dvd/sound/se/sep/se%06d.sep";
static const char s_soundLoadSeMergeFmt[] =
    "\x1B[31mMerge: \x95\x88\x96\xCA\x82\xF0" "DVD\x82\xA9\x82\xE7\x93\xC7\x82\xDD\x8D\x9E"
    "\x82\xDD\x82\xDC\x82\xB5\x82\xBD\x81\x42%d\n\x1B[0m";
static const char s_soundSeBlockPathFmt[] = "dvd/sound/se/block/se%03d.seb";
static const char s_soundMusicPathFmt[] = "dvd/sound/music/music%03d.bgm";
static const char s_soundEnvSePlayFmt[] = "\x1B[32mEnvSePlay: %06d\n\x1B[0m";
static const char s_soundEnvSeStopFmt[] = "\x1B[32mEnvSeStop: %06d\n\x1B[0m";
extern const char s_sound_cpp_801db2d4[] = "sound.cpp";

extern double DOUBLE_80330d20;
extern double DOUBLE_80330d28;
extern "C" void __ct__9CRedSoundFv(void*);
extern "C" void __dt__6CSoundFv(void*);
extern "C" CMemory::CStage* CreateStage__7CMemoryFUlPci(CMemory*, unsigned long, char*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(CMemory*, CMemory::CStage*);
extern "C" int Printf__7CSystemFPce(CSystem*, const char*, ...);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
CSound Sound;

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

class CSound::CSe3D {
public:
    union {
        struct {
            u8 m_active : 1;
            u8 m_paused : 1;
            u8 m_flagsRest : 6;
        } m_bits;
        s8 m_flags;
    };
    u8 m_volume;
    u8 m_pan;
    s8 m_lineIndex;
    int m_handle;
    int m_playId;
    int m_soundId;
    float m_nearDistance;
    float m_farDistance;
    Vec m_position;
    int m_group;
};

struct CSoundLayout {
    u32 m_vtable;
    CMemory::CStage* m_stage;
    u32 m_redSoundWord0;
    u8* m_aramBuffer;
    CFile::CHandle* m_waveFile;
    int m_waveRemain;
    int m_waveOffset;
    int m_waveID;
    int m_waveState;
    int m_waveSyncMode;
    int m_seCount;
    u8 m_seWork[0x1400];
    CLine m_lines[8];
    u8* m_streamBuffer;
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
            float distance = sqrtf(distanceSq);
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
                float distance = sqrtf(distanceSq);
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
    for (u32 i = 0; i < line->pointCount; i++) {
        float x;
        float y;
        float z;
        z = line->points[i].z;
        y = line->points[i].y;
        x = line->points[i].x;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
    }

    GXBegin((GXPrimitive)0xB0, GX_VTXFMT0, (u16)(line->pointCount & 0xFFFF));
    for (u32 i = 0; i < line->pointCount; i++) {
        float x = line->points[i].x;
        float y = FLOAT_80330cf4 + line->points[i].y;
        float z = line->points[i].z;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
    }

    GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, (u16)((line->pointCount & 0x7FFF) << 1));
    for (u32 i = 0; i < line->pointCount; i++) {
        float x;
        float y;
        float z;
        z = line->points[i].z;
        y = line->points[i].y;
        x = line->points[i].x;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
        {
            float raisedY = FLOAT_80330cf4 + line->points[i].y;
            float raisedZ = line->points[i].z;
            float raisedX = line->points[i].x;
            GXWGFifo.f32 = raisedX;
            GXWGFifo.f32 = raisedY;
            GXWGFifo.f32 = raisedZ;
        }
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

    Vec* point = line->points;
    CLineSegment* segment = line->segments;
    for (u32 i = 0; i < line->pointCount; i++, point++, segment++) {

        if (point->x < line->min.x) {
            line->min.x = point->x;
        }
        if (point->y < line->min.y) {
            line->min.y = point->y;
        }
        if (point->z < line->min.z) {
            line->min.z = point->z;
        }

        if (point->x > line->max.x) {
            line->max.x = point->x;
        }
        if (point->y > line->max.y) {
            line->max.y = point->y;
        }
        if (point->z > line->max.z) {
            line->max.z = point->z;
        }

        if (i != 0) {
            CLineSegment* prevSegment = segment - 1;
            PSVECSubtract(point, point - 1, &prevSegment->delta);
            prevSegment->length = PSVECMag(&prevSegment->delta);
            prevSegment->startLength = line->totalLength;
            line->totalLength += prevSegment->length;
            if (prevSegment->length != kLineSegmentMinT) {
                PSVECNormalize(&prevSegment->delta, &prevSegment->normal);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CSound::CSound()
{
    unsigned char* sound = reinterpret_cast<unsigned char*>(this);

    __ct__9CRedSoundFv(sound + 8);
    __construct_array(sound + 0x142C, reinterpret_cast<ConstructorDestructor>(__ct__9CLine), 0, 0x1cc, 8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSound::~CSound()
{
    RedSound(this)->~CRedSound();
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
    SoundData(this).m_stage = CreateStage__7CMemoryFUlPci(&Memory, 0xA4000, const_cast<char*>(s_CSound_80330ce0), 0);

    SoundData(this).m_aramBuffer =
        new (SoundData(this).m_stage, const_cast<char*>(s_sound_cpp_801db2d4), 0x2E) u8[0x80000];
    SoundData(this).m_streamBuffer =
        new (SoundData(this).m_stage, const_cast<char*>(s_sound_cpp_801db2d4), 0x2F) u8[0x20000];

    SoundData(this).m_bgmMasterVolume = 0x7F;
    SoundData(this).m_seMasterVolume = 0x7F;
    SoundData(this).m_seMaxVolume = 0x7F;
    SoundData(this).m_curMusicVolume = 0x7F;
    SoundData(this).m_debugPrint = 0;

    ARInit(0, 0);
    ARQInit();

    RedSound(this)->Init(SoundData(this).m_aramBuffer, 0x80000, 0x800000, 0x800000);
    RedSound(this)->ReportPrint((-SoundData(this).m_debugPrint | SoundData(this).m_debugPrint) >> 31);

    u32 soundMode = RedSound(this)->GetSoundMode();
    RedSound(this)->SetSoundMode((u32)__cntlzw((u32)__cntlzw(soundMode) >> 5) >> 5);

    RedSound(this)->MusicMasterVolume(SoundData(this).m_bgmMasterVolume);
    RedSound(this)->SeMasterVolume(SoundData(this).m_seMasterVolume);
    RedSound(this)->SetReverb(1, 4);
    RedSound(this)->SetReverbDepth(1, 0x40, 0xF);

    SoundData(this).m_waveFile = 0;
    SoundData(this).m_streamFile = 0;
    SoundData(this).m_streamPlaying = 0;
    memset(SoundData(this).m_noFreeSeGroups, 0xFF, sizeof(SoundData(this).m_noFreeSeGroups));
    memset(SoundData(this).m_noFreeWaves, 0xFF, sizeof(SoundData(this).m_noFreeWaves));
    SoundData(this).m_pauseAllSe = 0;
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
    CRedSound* redSound = RedSound(this);
    CSoundLayout& sound = SoundData(this);

    CFile::CHandle*& waveFile = sound.m_waveFile;
    if (waveFile != 0) {
        File.Close(waveFile);
        waveFile = 0;
        Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
    }

    redSound->SetWaveData(-1, nullptr, 0);

    int shouldStopStream = 0;
    if (sound.m_streamPlaying != 0 && redSound->StreamPlayState(sound.m_streamID) != 0) {
        shouldStopStream = 1;
    }

    if (shouldStopStream != 0) {
        redSound->StreamStop(sound.m_streamID);
    }

    CFile::CHandle*& streamFile = sound.m_streamFile;
    if (streamFile != 0) {
        File.Close(streamFile);
        streamFile = 0;
    }

    sound.m_streamPlaying = 0;

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
        redSound->SetSeBlockData(i, nullptr);
    }

    redSound->End();

    u8*& streamBuffer = sound.m_streamBuffer;
    if (streamBuffer != 0) {
        delete[] streamBuffer;
        streamBuffer = 0;
    }

    u8*& aramBuffer = sound.m_aramBuffer;
    if (aramBuffer != 0) {
        delete[] aramBuffer;
        aramBuffer = 0;
    }

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, sound.m_stage);
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
inline void CSound::create(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CSound::destroy()
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
    CRedSound* redSound = RedSound(this);
    CSoundLayout& sound = SoundData(this);

    CFile::CHandle*& waveFile = sound.m_waveFile;
    CFile::CHandle*& streamFile = sound.m_streamFile;
    int& streamPlaying = sound.m_streamPlaying;
    int& streamID = sound.m_streamID;

    if (waveFile != 0) {
        File.Close(waveFile);
        waveFile = 0;
        Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
    }

    redSound->SetWaveData(-1, 0, 0);

    bool wasStreaming = false;
    if (streamPlaying != 0) {
        if (redSound->StreamPlayState(streamID) != 0) {
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

    u32 soundMode = redSound->GetSoundMode();
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

    if (redSound->ReentryWaveData(0) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
        }

        redSound->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, s_soundWavePathFmt, 0);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 0;
            sound.m_waveSyncMode = 1;
            while (((u32)__cntlzw((u32)waveFile) >> 5) == 0) {
                loadWaveFrame();
            }
        }
    }

    if (redSound->ReentryWaveData(500) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
        }

        redSound->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, s_soundWavePathFmt, 500);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 1;
            sound.m_waveSyncMode = 1;
            while (((u32)__cntlzw((u32)waveFile) >> 5) == 0) {
                loadWaveFrame();
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        char sePath[260];
        sprintf(sePath, s_soundSeBlockPathFmt, i);
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
    unsigned int programTime = RedSound(this)->GetProgramTime();
    float numer = (float)(programTime / 0xF);
    float denom = (float)(((OS_TIMER_CLOCK / 125000) * 0x8235) >> 3);
    return 100.0f * (numer / denom);
}

/*
 * --INFO--
 * PAL Address: 0x800c7924
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSound::PauseDiscError(int pause)
{
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);

    if (sound.m_pauseAllSe == 0) {
        reinterpret_cast<CRedSound*>(self + 8)->SePause(-1, static_cast<u32>(-pause | pause) >> 31);
        reinterpret_cast<CRedSound*>(self + 8)->StreamPause(-1, (-static_cast<u32>(pause) | static_cast<u32>(pause)) >> 31);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSound::CheckDriver(int mode)
{
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);
    unsigned int oldPrint = sound.m_debugPrint;
    sound.m_debugPrint = 1;
    reinterpret_cast<CRedSound*>(self + 8)->ReportPrint(1);
    reinterpret_cast<CRedSound*>(self + 8)->TestProcess(mode);
    reinterpret_cast<CRedSound*>(self + 8)->DisplayWaveInfo();
    reinterpret_cast<CRedSound*>(self + 8)->DisplaySePlayInfo();
    sound.m_debugPrint = oldPrint;
    reinterpret_cast<CRedSound*>(self + 8)->ReportPrint((-oldPrint | oldPrint) >> 0x1F);
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
    CRedSound* redSound = RedSound(this);
    unsigned char* se = reinterpret_cast<unsigned char*>(this) + 0x2C;
    u32 i = 0;
    do {
        if (((static_cast<u8>(*se) >> 7) & 1) != 0) {
            int pan;
            int volume;

            calcVolumePan(reinterpret_cast<CSe3D*>(se), volume, pan);

            if (((*se >> 6) & 1) != 0) {
                if (volume != 0) {
                    if ((*reinterpret_cast<unsigned int*>(CFlat + 0x129C) & 0x400000) != 0) {
                        Printf__7CSystemFPce(&System, s_soundEnvSePlayFmt, *reinterpret_cast<int*>(se + 0xC));
                    }

                    int vol = volume;
                    int seNo = *reinterpret_cast<int*>(se + 0xC);
                    if (seNo < 0) {
                        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
                        seNo = -1;
                    } else if (seNo < 4000) {
                        int bank = seNo / 1000;
                        seNo = redSound->SePlay(bank, seNo % 1000, pan, 0, 0);
                        redSound->SeVolume(seNo, vol, 0x1E);
                    } else {
                        seNo = redSound->SePlay(-1, seNo, pan, 0, 0);
                        redSound->SeVolume(seNo, vol, 0x1E);
                    }
                    *reinterpret_cast<int*>(se + 8) = seNo;
                    *se &= 0xBF;
                }
            } else {
                if (redSound->SePlayState(*reinterpret_cast<int*>(se + 8)) == 0) {
                    *se &= 0x7F;
                } else {
                    int playing = redSound->ReportSeLoop(*reinterpret_cast<int*>(se + 8));
                    if ((playing != 0) &&
                        (redSound->GetSeVolume(*reinterpret_cast<int*>(se + 8), REDSOUND_SE_VOLUME_QUERY_VALUE) == 0) &&
                        (redSound->GetSeVolume(*reinterpret_cast<int*>(se + 8), REDSOUND_SE_VOLUME_QUERY_DELTA) == 0)) {
                        if ((*reinterpret_cast<unsigned int*>(CFlat + 0x129C) & 0x400000) != 0) {
                            Printf__7CSystemFPce(&System, s_soundEnvSeStopFmt, *reinterpret_cast<int*>(se + 0xC));
                        }
                        redSound->SeStop(*reinterpret_cast<int*>(se + 8));
                        *se = (*se & 0xBF) | 0x40;
                        goto next;
                    }

                    if (static_cast<signed char>(se[2]) != pan) {
                        if (*reinterpret_cast<int*>(se + 8) < 0) {
                            Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
                        } else {
                            redSound->SePan(*reinterpret_cast<int*>(se + 8), pan, 0x1E);
                        }
                        se[2] = static_cast<unsigned char>(pan);
                    }

                    if (static_cast<signed char>(se[1]) != volume) {
                        if (*reinterpret_cast<int*>(se + 8) < 0) {
                            Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
                        } else {
                            redSound->SeVolume(*reinterpret_cast<int*>(se + 8), volume, 0x1E);
                        }
                        se[1] = static_cast<unsigned char>(volume);
                    }
                }
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

    RedSound(this)->MusicVolume(-1, sound.m_curMusicVolume, 0);
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
        if (((static_cast<u8>(*se) >> 7) & 1) != 0) {
            CColor innerColor(0xC0, 0xC0, 0xC0, 0x80);
            CColor outerColor(0x80, 0x80, 0x80, 0x80);
            Graphic.DrawSphere(cameraMatrix, reinterpret_cast<Vec*>(se + 0x18), *reinterpret_cast<float*>(se + 0x10),
                               &innerColor.color);
            Graphic.DrawSphere(cameraMatrix, reinterpret_cast<Vec*>(se + 0x18), *reinterpret_cast<float*>(se + 0x14),
                               &outerColor.color);
        }
    }

    u32 lineColorRaw = 0xFF8000FF;
    GXColor lineColor = *reinterpret_cast<GXColor*>(&lineColorRaw);
    GXSetChanMatColor((GXChannelID)4, lineColor);
    GXLoadPosMtxImm(cameraMatrix, 0);

    CLine* line = sound.m_lines;
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
    CRedSound* redSound = RedSound(this);
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
            redSound->SetWaveData(waveID, File.m_readBuffer, (int)waveFile->m_chunkSize);

            while (RedSound(&Sound)->ReportStandby(0) != 0) {
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
    if (isStreamEnabled != 0 && redSound->StreamPlayState(streamID) != 0) {
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
            redSound->GetStreamPlayPoint(streamID, &playPoint[0], &playPoint[1]);
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
    if (waveNo < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else if (RedSound(this)->ReentryWaveData(waveNo) == -1) {
        CSoundLayout& sound = SoundData(this);
        CFile::CHandle*& waveFile = sound.m_waveFile;
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
        }

        RedSound(this)->SetWaveData(-1, nullptr, 0);

        char wavePath[244];
        sprintf(wavePath, s_soundWavePathFmt, waveNo);
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
        Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
    }
    reinterpret_cast<CRedSound*>(self + 8)->SetWaveData(-1, nullptr, 0);
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
    CFile::CHandle* waveFile = SoundData(this).m_waveFile;
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
    u8* self = reinterpret_cast<u8*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else if (reinterpret_cast<CRedSound*>(self + 8)->ReentryMusicData(bgmId) == -1) {
        char musicPath[256];
        sprintf(musicPath, s_soundMusicPathFmt, bgmId);

        CFile::CHandle* handle = File.Open(musicPath, 0, CFile::PRI_LOW);
        if (handle != 0) {
            File.Read(handle);
            File.SyncCompleted(handle);
            reinterpret_cast<CRedSound*>(self + 8)->SetMusicData(File.m_readBuffer);
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
    u8* self = reinterpret_cast<u8*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        reinterpret_cast<CRedSound*>(self + 8)->MusicStop(-1);
        reinterpret_cast<CRedSound*>(self + 8)->SetMusicPhraseStop(REDSOUND_MUSIC_PHRASE_STOP_OFF);
        reinterpret_cast<CRedSound*>(self + 8)->MusicPlay(bgmId, 0x7F, 0);
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
    u8* self = reinterpret_cast<u8*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        reinterpret_cast<CRedSound*>(self + 8)->SetMusicPhraseStop(REDSOUND_MUSIC_PHRASE_STOP_OFF);
        reinterpret_cast<CRedSound*>(self + 8)->MusicCrossPlay(bgmId, 0x7F, crossFrames);
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
    u8* self = reinterpret_cast<u8*>(this);

    if (bgmId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        reinterpret_cast<CRedSound*>(self + 8)->MusicNextPlay(bgmId, 0x7F, 0);
        reinterpret_cast<CRedSound*>(self + 8)->SetMusicPhraseStop(REDSOUND_MUSIC_PHRASE_STOP_ON);
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
    RedSound(this)->MusicStop(-1);
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
    RedSound(this)->MusicFadeOut(-1, fadeFrames);
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
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);
    CFile::CHandle*& waveFile = sound.m_waveFile;

    if (reinterpret_cast<CRedSound*>(self + 8)->ReentryWaveData(0) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
        }

        reinterpret_cast<CRedSound*>(self + 8)->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, s_soundWavePathFmt, 0);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 0;
            sound.m_waveSyncMode = 1;
            while (((u32)__cntlzw((u32)waveFile) >> 5) == 0) {
                loadWaveFrame();
            }
        }
    }

    if (reinterpret_cast<CRedSound*>(self + 8)->ReentryWaveData(500) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
        }

        reinterpret_cast<CRedSound*>(self + 8)->SetWaveData(-1, 0, 0);

        char wavePath[256];
        sprintf(wavePath, s_soundWavePathFmt, 500);
        waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);
        if (waveFile != 0) {
            sound.m_waveRemain = File.GetLength(waveFile);
            sound.m_waveOffset = 0;
            sound.m_waveState = 0;
            sound.m_waveID = 1;
            sound.m_waveSyncMode = 1;
            while (((u32)__cntlzw((u32)waveFile) >> 5) == 0) {
                loadWaveFrame();
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        char sePath[260];
        sprintf(sePath, s_soundSeBlockPathFmt, i);
        CFile::CHandle* handle = File.Open(sePath, 0, CFile::PRI_LOW);
        if (handle != 0) {
            File.Read(handle);
            File.SyncCompleted(handle);
            reinterpret_cast<CRedSound*>(self + 8)->SetSeBlockData(i, File.m_readBuffer);
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
    u8* self = reinterpret_cast<u8*>(this);

    reinterpret_cast<CRedSound*>(self + 8)->ClearWaveBank(500);
    reinterpret_cast<CRedSound*>(self + 8)->ClearWaveBank(0);
    for (int i = 0; i < 4; i++) {
        reinterpret_cast<CRedSound*>(self + 8)->SetSeBlockData(i, 0);
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
    u8* self = reinterpret_cast<u8*>(this);

    if (seId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else if (reinterpret_cast<CRedSound*>(self + 8)->ReentrySeSepData(seId) == -1) {
        char sePath[264];
        sprintf(sePath, s_soundSeSepPathFmt, seId);
        CFile::CHandle* handle = File.Open(sePath, 0, CFile::PRI_LOW);
        if (handle != 0) {
            File.Read(handle);
            File.SyncCompleted(handle);
            reinterpret_cast<CRedSound*>(self + 8)->SetSeSepData(File.m_readBuffer);
            File.Close(handle);
            if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
                Printf__7CSystemFPce(&System, s_soundLoadSeMergeFmt, seId);
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
    u8* self = reinterpret_cast<u8*>(this);
    if (reinterpret_cast<CRedSound*>(self + 8)->ReentrySeSepData(*reinterpret_cast<s32*>((u8*)seData + 8)) == -1) {
        reinterpret_cast<CRedSound*>(self + 8)->SetSeSepData(seData);
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
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);
    CFile::CHandle*& waveFile = sound.m_waveFile;

    if (waveId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        if (reinterpret_cast<CRedSound*>(self + 8)->ReentryWaveData(waveId) == -1) {
            if (waveId < 0) {
                Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
            } else if (reinterpret_cast<CRedSound*>(self + 8)->ReentryWaveData(waveId) == -1) {
                if (waveFile != 0) {
                    File.Close(waveFile);
                    waveFile = 0;
                    Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
                }

                reinterpret_cast<CRedSound*>(self + 8)->SetWaveData(-1, nullptr, 0);

                char wavePath[260];
                sprintf(wavePath, s_soundWavePathFmt, waveId);
                waveFile = File.Open(wavePath, 0, CFile::PRI_LOW);

                if (waveFile != 0) {
                    sound.m_waveRemain = File.GetLength(waveFile);
                    sound.m_waveOffset = 0;
                    sound.m_waveState = 0;
                    sound.m_waveID = -1;
                    sound.m_waveSyncMode = 1;
                    while (((u32)__cntlzw((u32)waveFile) >> 5) == 0) {
                        loadWaveFrame();
                    }
                }
            }

            if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
                Printf__7CSystemFPce(&System, s_soundLoadWaveMergeFmt, waveId);
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
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);
    CFile::CHandle*& waveFile = sound.m_waveFile;

    if (reinterpret_cast<CRedSound*>(self + 8)->ReentryWaveData(reinterpret_cast<s16*>(waveData)[1]) == -1) {
        if (waveFile != 0) {
            File.Close(waveFile);
            waveFile = 0;
            Printf__7CSystemFPce(&System, s_soundLoadWaveErrorFmt);
        }
        reinterpret_cast<CRedSound*>(self + 8)->SetWaveData(-1, nullptr, 0);
        reinterpret_cast<CRedSound*>(self + 8)->SetWaveData(-1, waveData, -1);
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        RedSound(this)->ClearWaveData(waveId);
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
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);
    if (clearMode != 0) {
        reinterpret_cast<CRedSound*>(self + 8)->SeStop(-1);
        reinterpret_cast<CRedSound*>(self + 8)->ClearSeSepData(-1);
        reinterpret_cast<CRedSound*>(self + 8)->ClearWaveData(-3);
    } else {
        reinterpret_cast<CRedSound*>(self + 8)->SeStopMG(sound.m_noFreeSeGroups[0], sound.m_noFreeSeGroups[1],
                                                         sound.m_noFreeSeGroups[2], sound.m_noFreeSeGroups[3]);
        reinterpret_cast<CRedSound*>(self + 8)->ClearSeSepDataMG(sound.m_noFreeSeGroups[0], sound.m_noFreeSeGroups[1],
                                                                 sound.m_noFreeSeGroups[2], sound.m_noFreeSeGroups[3]);
        reinterpret_cast<CRedSound*>(self + 8)->ClearWaveDataM(sound.m_noFreeWaves[0], sound.m_noFreeWaves[1],
                                                               sound.m_noFreeWaves[2], sound.m_noFreeWaves[3]);
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
    CRedSound* redSound = RedSound(this);

    if (seNo < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
        return -1;
    } else if (seNo < 4000) {
        seId = redSound->SePlay(seNo / 1000, seNo % 1000, pan, volume & ~((-fadeFrames | fadeFrames) >> 0x1F), 0);
        if (fadeFrames != 0) {
            redSound->SeVolume(seId, volume, fadeFrames);
        }
    } else {
        seId = redSound->SePlay(-1, seNo, pan, volume & ~((-fadeFrames | fadeFrames) >> 0x1F), 0);
        if (fadeFrames != 0) {
            redSound->SeVolume(seId, volume, fadeFrames);
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        RedSound(this)->SeStop(seId);
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        RedSound(this)->SeFadeOut(seId, fadeFrames);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CSound::ChangeSeVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CSound::ChangeSePan(int, int, int)
{
	// TODO
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
    int result;
    if (se3dHandle < 0) {
        result = Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        char* se = reinterpret_cast<char*>(this) + 0x2C;
        char* found;
        result = 0;
        int count = 0x20;
        do {
            if ((((static_cast<u8>(*se) >> 7) & 1) != 0 &&
                  (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
                 (((static_cast<u8>(*(se += 0x28)) >> 7) & 1) != 0 &&
                  (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
                 (((static_cast<u8>(*(se += 0x28)) >> 7) & 1) != 0 &&
                  (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle)) ||
                 (((static_cast<u8>(*(se += 0x28)) >> 7) & 1) != 0 &&
                  (found = se, *reinterpret_cast<int*>(se + 4) == se3dHandle))) {
                goto found_se;
            }
            result += 3;
            se += 0x28;
            count--;
        } while (count != 0);
        found = 0;
found_se:
        if (found != 0) {
            *reinterpret_cast<int*>(found + 0x24) = group;
        }
    }
    return result;
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
    int volumeValue;
    CSe3D* se;
    int loopCount;
    int slot;
    int volume;
    int pan;
    int panValue;

    if (soundId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
        return -1;
    }

    u8* soundObj = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(soundObj);
    se = reinterpret_cast<CSe3D*>(sound.m_seWork);

    for (loopCount = 0x80; loopCount != 0; loopCount--, se++) {
        if (se->m_bits.m_active) {
            continue;
        }

        se->m_bits.m_active = 1;
        se->m_bits.m_paused = 0;
        se->m_soundId = soundId;
        slot = sound.m_seCount;
        sound.m_seCount = slot + 1;
        se->m_handle = slot;

        se->m_nearDistance = nearDistance;
        se->m_farDistance = farDistance;
        se->m_lineIndex = static_cast<s8>(lineIndex);

        calcVolumePan(se, volume, pan);
        se->m_volume = static_cast<u8>(volume);
        se->m_pan = static_cast<u8>(pan);
        se->m_group = -1;
        volumeValue = volume;
        panValue = pan;

        if (soundId < 0) {
            Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
            slot = -1;
        } else if (soundId < 4000) {
            int bank = soundId / 1000;
            slot = reinterpret_cast<CRedSound*>(soundObj + 8)->SePlay(
                bank, soundId % 1000, panValue, volumeValue & ~((int)(-fadeFrames | fadeFrames) >> 0x1F), 0);
            if (fadeFrames != 0) {
                reinterpret_cast<CRedSound*>(soundObj + 8)->SeVolume(slot, volumeValue, fadeFrames);
            }
        } else {
            slot = reinterpret_cast<CRedSound*>(soundObj + 8)->SePlay(
                -1, soundId, panValue, volumeValue & ~((int)(-fadeFrames | fadeFrames) >> 0x1F), 0);
            if (fadeFrames != 0) {
                reinterpret_cast<CRedSound*>(soundObj + 8)->SeVolume(slot, volumeValue, fadeFrames);
            }
        }

        se->m_playId = slot;
        return se->m_handle;
    }

    return -1;
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
    int volumeValue;
    CSe3D* se;
    int loopCount;
    int slot;
    int volume;
    int pan;
    int panValue;

    if (soundId < 0) {
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
        return -1;
    }

    u8* soundObj = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(soundObj);
    se = reinterpret_cast<CSe3D*>(sound.m_seWork);

    for (loopCount = 0x80; loopCount != 0; loopCount--, se++) {
        if (se->m_bits.m_active) {
            continue;
        }

        se->m_bits.m_active = 1;
        se->m_bits.m_paused = 0;
        se->m_soundId = soundId;
        slot = sound.m_seCount;
        sound.m_seCount = slot + 1;
        se->m_handle = slot;

        se->m_nearDistance = nearDistance;
        se->m_farDistance = farDistance;
        se->m_position = *pos;
        se->m_lineIndex = -1;

        calcVolumePan(se, volume, pan);
        se->m_volume = static_cast<u8>(volume);
        se->m_pan = static_cast<u8>(pan);
        se->m_group = -1;
        volumeValue = volume;
        panValue = pan;

        if (soundId < 0) {
            Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
            slot = -1;
        } else if (soundId < 4000) {
            int bank = soundId / 1000;
            slot = reinterpret_cast<CRedSound*>(soundObj + 8)->SePlay(
                bank, soundId % 1000, panValue, volumeValue & ~((int)(-fadeFrames | fadeFrames) >> 0x1F), 0);
            if (fadeFrames != 0) {
                reinterpret_cast<CRedSound*>(soundObj + 8)->SeVolume(slot, volumeValue, fadeFrames);
            }
        } else {
            slot = reinterpret_cast<CRedSound*>(soundObj + 8)->SePlay(
                -1, soundId, panValue, volumeValue & ~((int)(-fadeFrames | fadeFrames) >> 0x1F), 0);
            if (fadeFrames != 0) {
                reinterpret_cast<CRedSound*>(soundObj + 8)->SeVolume(slot, volumeValue, fadeFrames);
            }
        }

        se->m_playId = slot;
        return se->m_handle;
    }

    return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CSound::searchSe3D(int)
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
    float fVar1;
    float fVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    float nearestDistance;
    float nearestT;
    Vec nearestPoint;

    if (se3D->m_lineIndex >= 0) {
        iVar4 = Calc__9CLine(
            (double)se3D->m_farDistance, &SoundData(this).m_lines[se3D->m_lineIndex], &nearestPoint, &nearestDistance,
            (u32*)0, &nearestT, reinterpret_cast<const Vec*>(&CameraPcs._212_4_));
        if (iVar4 != 0) {
            PSMTXMultVec(CameraPcs.m_cameraMatrix, &nearestPoint, &nearestPoint);
            if (nearestDistance < se3D->m_nearDistance) {
                outVolume = 0x7F;
            } else {
                fVar3 = se3D->m_nearDistance;
                outVolume = 0x7F - (int)(FLOAT_80330ce8 * ((nearestDistance - fVar3) / (se3D->m_farDistance - fVar3)));
            }

            iVar4 = (int)nearestPoint.x;
            if (iVar4 < -0x38) {
                iVar5 = -0x38;
            } else {
                iVar5 = 0x38;
                if (iVar4 <= 0x38) {
                    iVar5 = iVar4;
                }
            }
            outPan = iVar5 + 0x40;
        } else {
            outVolume = 0;
            outPan = 0x40;
        }
    } else if ((kLineSegmentMinT == se3D->m_nearDistance) && (kLineSegmentMinT == se3D->m_farDistance)) {
        outVolume = 0x7F;
        outPan = 0x40;
    } else {
        fVar1 = kLineSegmentMaxT;
        if (Game.m_gameWork.m_soundOptionFlag != 0) {
            switch (Game.m_gameWork.m_bossArtifactStageIndex) {
            case 8:
            case 0xE:
                fVar1 = FLOAT_80330cf4;
                break;
            default:
                fVar1 = FLOAT_80330cf8;
                break;
            }
        }

        PSMTXMultVec(CameraPcs.m_cameraMatrix, &se3D->m_position, &nearestPoint);
        fVar3 = fVar1 * PSVECSquareDistance(reinterpret_cast<Vec*>(&CameraPcs._212_4_), &se3D->m_position);
        fVar2 = se3D->m_farDistance * fVar1;
        fVar2 = se3D->m_farDistance * fVar2;
        fVar2 = fVar1 * fVar2;
        if (fVar3 < fVar2) {
            float nearScaled = se3D->m_nearDistance * fVar1;
            nearScaled = se3D->m_nearDistance * nearScaled;
            nearScaled = fVar1 * nearScaled;
            if (fVar3 < nearScaled) {
                outVolume = 0x7F;
            } else {
                outVolume = 0x7F - (int)(FLOAT_80330ce8 * ((fVar3 - nearScaled) / (fVar2 - nearScaled)));
            }
        } else {
            outVolume = 0;
        }

        if (Game.m_currentMapId == 0x21) {
            iVar4 = (int)(nearestPoint.x / FLOAT_80330cfc);
            if (iVar4 < -0x38) {
                iVar5 = -0x38;
            } else {
                iVar5 = 0x38;
                if (iVar4 <= 0x38) {
                    iVar5 = iVar4;
                }
            }
            outPan = iVar5 + 0x40;
        } else {
            iVar4 = (int)nearestPoint.x;
            if (iVar4 < -0x38) {
                iVar5 = -0x38;
            } else {
                iVar5 = 0x38;
                if (iVar4 <= 0x38) {
                    iVar5 = iVar4;
                }
            }
            outPan = iVar5 + 0x40;
        }
    }

    if (outVolume > SoundData(this).m_curMusicVolume) {
        outVolume = SoundData(this).m_curMusicVolume;
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
    char* se = reinterpret_cast<char*>(this) + 0x2C;
    u32 i = 0;

    while (i < 0x80) {
        if ((((static_cast<u8>(*se) >> 7) & 1) != 0) && (*reinterpret_cast<int*>(se + 0x24) >= 0) &&
            (*reinterpret_cast<int*>(se + 0x24) == group)) {
            int se3dHandle = *reinterpret_cast<int*>(se + 4);
            if (se3dHandle < 0) {
                Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
            } else {
                char* found = reinterpret_cast<char*>(this) + 0x2C;
                int count;

                for (count = 0x20; count != 0; count--) {
                    if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                        if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                            goto found_se;
                        }
                    }

                    found += 0x28;
                    if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                        if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                            goto found_se;
                        }
                    }

                    found += 0x28;
                    if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                        if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                            goto found_se;
                        }
                    }

                    found += 0x28;
                    if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                        if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                            goto found_se;
                        }
                    }

                    found += 0x28;
                }
                found = 0;
found_se:
                if (found != 0) {
                    int playId = *reinterpret_cast<int*>(found + 8);
                    if (playId < 0) {
                        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
                    } else {
                        RedSound(this)->SeStop(playId);
                    }
                    reinterpret_cast<CSe3D*>(found)->m_bits.m_active = 0;
                }
            }
            reinterpret_cast<CSe3D*>(se)->m_bits.m_active = 0;
        }

        i++;
        se += 0x28;
    }
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        char* found = reinterpret_cast<char*>(this) + 0x2C;
        int idx = 0;
        int count;

        for (count = 0x20; count != 0; count--) {
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            idx += 3;
            found += 0x28;
        }
        found = 0;

found_entry:
        if (found != 0) {
            const int playId = *reinterpret_cast<int*>(found + 8);
            if (playId < 0) {
                Printf__7CSystemFPce(&System, s_soundMinusOneFmt, idx);
            } else {
                RedSound(this)->SeStop(playId);
            }
            reinterpret_cast<CSe3D*>(found)->m_bits.m_active = 0;
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
        return 0;
    }

    char* found = reinterpret_cast<char*>(this) + 0x2C;
    int ret = 0;
    int count;

    for (count = 0x20; count != 0; count--) {
        if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
            if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                goto found_entry;
            }
        }

        found += 0x28;
        if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
            if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                goto found_entry;
            }
        }

        found += 0x28;
        if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
            if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                goto found_entry;
            }
        }

        found += 0x28;
        if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
            if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                goto found_entry;
            }
        }

        ret += 3;
        found += 0x28;
    }
    found = 0;

found_entry:
    if (found != 0) {
        const int playId = *reinterpret_cast<int*>(found + 8);
        if (playId < 0) {
            Printf__7CSystemFPce(&System, s_soundMinusOneFmt, fadeFrames, ret);
        } else {
            RedSound(this)->SeFadeOut(playId, fadeFrames);
        }
        reinterpret_cast<CSe3D*>(found)->m_bits.m_active = 0;
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
    char* se;
    char* found;
    int count;

    if (se3dHandle < 0) {
        ret = Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        se = reinterpret_cast<char*>(this) + 0x2C;
        ret = 0;
        for (count = 0x20; count != 0; count--) {
            found = se;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            ret += 3;
            se = found + 0x28;
        }
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        char* se = reinterpret_cast<char*>(this) + 0x2C;
        char* found;
        int count;

        for (count = 0x20; count != 0; count--) {
            found = se;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            found += 0x28;
            if (((static_cast<u8>(*found) >> 7) & 1) != 0) {
                if (*reinterpret_cast<int*>(found + 4) == se3dHandle) {
                    goto found_entry;
                }
            }

            se = found + 0x28;
        }
        found = 0;

found_entry:
        if (found != 0) {
            RedSound(this)->SePitch(*reinterpret_cast<int*>(found + 8), pitch << 8, frames);
        }
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

    SoundData(this).m_lines[lineIndex].pointCount = 0;
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
    CSoundLayout& sound = SoundData(this);
    const u32 pointCount = sound.m_lines[lineIndex].pointCount;

    if (pointCount < 10) {
        sound.m_lines[lineIndex].pointCount = pointCount + 1;
        sound.m_lines[lineIndex].points[pointCount] = *position;
        CalcBound__9CLine2(&sound.m_lines[lineIndex]);
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
    u8* soundObj = reinterpret_cast<u8*>(this);
    reinterpret_cast<CRedSound*>(soundObj + 8)->SetReverb(1, reverb);
    reinterpret_cast<CRedSound*>(soundObj + 8)->SetReverbDepth(1, depth, 0xF);
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
        Printf__7CSystemFPce(&System, s_soundMinusOneFmt);
    } else {
        CSoundLayout& sound = SoundData(this);
        bool isPlaying = false;

        if (sound.m_streamPlaying != 0) {
            if (RedSound(this)->StreamPlayState(sound.m_streamID) != 0) {
                isPlaying = true;
            }
        }

        if (isPlaying) {
            RedSound(this)->StreamStop(sound.m_streamID);
        }

        if (sound.m_streamFile != 0) {
            File.Close(sound.m_streamFile);
            sound.m_streamFile = 0;
        }

        sound.m_streamPlaying = 0;

        char streamPath[252];
        sprintf(streamPath, s_dvd_sound_stream_strpct04d_str_801DB110, streamID);
        sound.m_streamFile = File.Open(streamPath, 0, CFile::PRI_LOW);
        if (sound.m_streamFile != 0) {
            CFile::CHandle* streamFile = sound.m_streamFile;
            streamFile->m_chunkSize = 0x20000;
            streamFile->m_currentOffset = 0;
            File.Read(sound.m_streamFile);
            File.SyncCompleted(sound.m_streamFile);
            memcpy(sound.m_streamBuffer, File.m_readBuffer, 0x20000);
            sound.m_streamOffset = 0x20000;
            sound.m_streamHalf = 0;
            sound.m_streamRemain = File.GetLength(sound.m_streamFile) - 0x20000;
            sound.m_streamState = 0;
            sound.m_streamWaveID = streamID;
            File.Close(sound.m_streamFile);
            sound.m_streamFile = 0;
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
    char streamPath[252];
    CSoundLayout& sound = SoundData(this);
    sprintf(streamPath, s_dvd_sound_stream_strpct04d_str_801DB110, sound.m_streamWaveID);

    sound.m_streamFile = File.Open(streamPath, 0, CFile::PRI_LOW);
    if (sound.m_streamFile == 0) {
        return;
    }

    int streamId = sound.m_streamWaveID;
    int volume;
    switch (streamId) {
    case 2:
    case 3:
    case 4:
    case 6:
        volume = 0x7f;
        if (streamId == 6) {
            volume = 0x70;
        }
        break;
    case 1:
    case 5:
        volume = sound.m_bgmMasterVolume;
        if (streamId == 1) {
            volume -= (volume * 0x19) / 0x7f;
        }
        break;
    default:
        volume = sound.m_seMasterVolume;
        break;
    }
    void* streamBuffer = sound.m_streamBuffer;
    CRedSound* redSound = RedSound(this);
    int clampedVolume;
    if (volume < 0) {
        clampedVolume = 0;
    } else {
        clampedVolume = 0x7f;
        if (volume <= 0x7f) {
            clampedVolume = volume;
        }
    }

    int streamNo = redSound->StreamPlay(streamBuffer, 0x20000, 0x40, clampedVolume);
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
        int state = RedSound(this)->StreamPlayState(sound.m_streamID);
        if (state != 0) {
            shouldStop = true;
        }
    }

    if (shouldStop) {
        RedSound(this)->StreamStop(sound.m_streamID);
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
    RedSound(this)->StreamVolume(-1, volume, frames);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CSound::IsPlayStream()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CSound::IsDebugPrint(int)
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
    u8* self = reinterpret_cast<u8*>(this);
    CSoundLayout& sound = *reinterpret_cast<CSoundLayout*>(self);

    reinterpret_cast<CRedSound*>(self + 8)->SePause(-1, static_cast<u32>(-pause | pause) >> 31);
    reinterpret_cast<CRedSound*>(self + 8)->StreamPause(-1, (-static_cast<u32>(pause) | static_cast<u32>(pause)) >> 31);
    sound.m_pauseAllSe = pause;
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
inline void CSound::WaitASync()
{
	// TODO
}
