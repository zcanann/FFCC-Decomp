#ifndef _FFCC_P_CAMERA_H_
#define _FFCC_P_CAMERA_H_

#include "ffcc/system.h"
#include "ffcc/mapocttree.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class SRT;
struct Vec;
class CVector;
class CMapPcs;
class CGObject;
class CPad;
class CColor;

extern const float kCameraBoundsMinInitial;
extern const float kCameraBoundsMaxInitial;

void dbgDrawSphere(float, float, float, float, unsigned char, unsigned char, unsigned char);

class CFullScreenShadow
{
public:
    void* m_shadowTexture;   // 0x00
    u8* m_rampTexture;       // 0x04
    GXTexObj m_texObjs[2];   // 0x08
    float m_rotX;            // 0x48
    float m_rotY;            // 0x4C
    float m_span;            // 0x50
    float m_scale;           // 0x54
    Mtx m_shadowTexMtx;      // 0x58
    Mtx m_depthMtx;          // 0x88
    Mtx m_depthScaleMtx;     // 0xB8
};

class CCameraPcs : public CProcess
{
public:
    class camdtst
    {
    public:
        
    };

    struct ViewerState
    {
        Vec m_position;
        float m_rotX;
        float m_rotY;
        float m_distance;
        Vec m_scale;
    };

    struct CameraState
    {
        Mtx m_cameraMatrix;
        Mtx m_worldMapMatrix;
        Mtx m_cameraWorldMtx;
        Mtx44 m_screenMatrix;
        Vec m_target;
        Vec m_position;
        Vec m_direction;
        float m_yaw;
        float m_fov;
        float m_nearZ;
        float m_farZ;
        float m_zRotate;
    };

    struct QuakeState
    {
        unsigned char m_mode;
        unsigned char m_pad01[3];
        int m_state;
        int m_keepMoving;
        short m_signX;
        short m_signY;
        short m_signZ;
        unsigned char m_pad12[2];
        Vec m_positionAmplitude;
        Vec m_jitterAmplitude;
        short m_startTimer;
        short m_startDuration;
        short m_endTimer;
        short m_endDuration;
    };

    struct WorldMapEffectState
    {
        unsigned char m_flags;
        unsigned char m_pad01;
        short m_duration;
        short m_timer;
        unsigned char m_pad06[2];
        float m_rotX;
        float m_rotY;
        float m_scale;
    };

    CCameraPcs()
    {
        m_shadowRectBound.m_min.z = kCameraBoundsMinInitial;
        m_shadowRectBound.m_min.y = kCameraBoundsMinInitial;
        m_shadowRectBound.m_min.x = kCameraBoundsMinInitial;
        m_shadowRectBound.m_max.z = kCameraBoundsMaxInitial;
        m_shadowRectBound.m_max.y = kCameraBoundsMaxInitial;
        m_shadowRectBound.m_max.x = kCameraBoundsMaxInitial;
    }

    static CProcessTable m_table[7];

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void onScriptChanging(char*);
    void onScriptChanged(char*, int);

    void SetQuakeParameter(int, int, short, short, float, float, float, float, float, float, int);
    void CalcQuake();
    void calc();

    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80022F18
     * EN Size: 36b
     * JP Address: TODO
     * JP Size: TODO
     */
    void GetClip(float* nearZ, float* farZ)
    {
        if (nearZ != 0) {
            *nearZ = m_nearZ;
        }
        if (farZ != 0) {
            *farZ = m_farZ;
        }
    }

    void SetStdProjectionMatrix();
    void draw();

    void calcViewerCameraMatrix(float (*)[4], const SRT*);
    void SetViewerSRT(const SRT*);
    /*
     * --INFO--
     * PAL Address: 0x800B965C
     * PAL Size: 36b
     * EN Address: 0x80022E94
     * EN Size: 132b
     * JP Address: TODO
     * JP Size: TODO
     */
    void GetViewMatrix(Mtx out)
    {
        PSMTXCopy(m_cameraMatrix, out);
    }

    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80022F3C
     * EN Size: 132b
     * JP Address: TODO
     * JP Size: TODO
     */
    void GetPosition(Vec* out)
    {
        out->x = m_positionX;
        out->y = m_positionY;
        out->z = m_positionZ;
    }

    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80022FC0
     * EN Size: 132b
     * JP Address: TODO
     * JP Size: TODO
     */
    void GetProjectionMatrix(Mtx44 out)
    {
        PSMTX44Copy(m_screenMatrix, out);
    }

    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80023044
     * EN Size: 8b
     * JP Address: TODO
     * JP Size: TODO
     */
    MtxPtr GetProjectionMatrix()
    {
        return m_screenMatrix;
    }

    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x8002304C
     * EN Size: 8b
     * JP Address: TODO
     * JP Size: TODO
     */
    MtxPtr GetViewMatrix()
    {
        return m_cameraMatrix;
    }

    // Chara
    void createChara();
    void destroyChara();
    void calcChara();

    // Map
    void createMap();
    void destroyMap();
    void calcMap();

    // Shadow & rendering features
    void createRampTex8();
    void createFullShadow();
    void destroyFullShadow();
    int GetShadowRect(CBound&);
    void drawShadowBegin();
    void drawShadowEnd();
    void drawShadowChrBegin();
    void SetFullScreenShadow(float (*)[4], long);
    void SetFullScreenShadowCamLen(float);
    void SetFullScreenShadowRot(float, float);
    void SetFullScreenShadowPos(Vec*, float);
    void SetFullScreenShadowEnable(unsigned char);
    void drawShadowEndAll();

    // Material editor
    void createMaterialEditor();
    void destroyMaterialEditor();
    void calcMaterialEditor();

    // Funny shape
    void createFunnyShape();
    void destroyFunnyShape();
    void calcFunnyShape();

    // Part
    void createPart();
    void destroyPart();
    void calcPart();

    // Misc
    void SetShadowAuto(int);
    void SetFov(float);
    void SetFromScript();
    void SetOffsetZBuff(float);
    void SetZRotate(float);
    void SetPosition(Vec*);
    void SetRefPosition(Vec*);
    int IsAbsolute();
    void addWorldMap();
    void SetIsAbsolute(int);
    void SetWorldMapMatrix(float (*)[4]);
    void GetWorldMapMatrix(float (*)[4]);
    void GetWorldMapInverseMatrix(float (*)[4]);
    CameraState& CurrentCameraState()
    {
        return *reinterpret_cast<CameraState*>(&m_cameraMatrix);
    }
    Vec& TargetVec()
    {
        return *reinterpret_cast<Vec*>(&m_targetX);
    }
    Vec& PositionVec()
    {
        return *reinterpret_cast<Vec*>(&m_positionX);
    }
    Vec& DirectionVec()
    {
        return *reinterpret_cast<Vec*>(&m_directionX);
    }

    Mtx m_cameraMatrix;
    Mtx m_worldMapMatrix; // 0x34
    Mtx m_cameraWorldMtx; // 0x64
    Mtx44 m_screenMatrix;
    float m_targetX;
    float m_targetY;
    float m_targetZ;
    float m_positionX;
    float m_positionY;
    float m_positionZ;
    float m_directionX;
    float m_directionY;
    float m_directionZ;
    float m_yaw;
    float m_fov;
    float m_nearZ;
    float m_farZ;
    float m_zRotate; // 0x108
    CameraState m_savedCamera; // 0x10C
    CameraState m_shadowCamera; // 0x214
    CFullScreenShadow m_fullScreenShadow; // 0x31C
    u8 m_fullScreenShadowEnabled; // 0x404
    u8 _pad405[0x408 - 0x405];
    Vec m_fullScreenShadowPosition; // 0x408
    CBound m_shadowRectBound; // 0x414
    float m_fullScreenShadowDepth; // 0x42C
    float m_fullScreenShadowCamLen; // 0x430
    int m_shadowAuto; // 0x434
    int m_fromScript; // 0x438
    float m_distance; // 0x43C
    float m_pitch; // 0x440
    int m_isAbsolute; // 0x444
    ViewerState m_viewer; // 0x448
    int m_viewerOverride; // 0x46C
    float m_mapRotX; // 0x470
    float m_mapRotY; // 0x474
    float m_mapRotZ; // 0x478
    WorldMapEffectState m_worldMapEffect; // 0x47C
    QuakeState m_quake; // 0x490
};

extern CCameraPcs CameraPcs;

#endif // _FFCC_P_CAMERA_H_
