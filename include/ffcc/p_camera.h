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

extern float FLOAT_8032fa78;
extern float FLOAT_8032fa7c;

void dbgDrawSphere(float, float, float, float, unsigned char, unsigned char, unsigned char);

class CCameraPcs : public CProcess
{
public:
    class camdtst
    {
    public:
        
    };

    CCameraPcs() {}

    static unsigned int m_table_desc0[3];
    static unsigned int m_table_desc1[3];
    static unsigned int m_table_desc2[3];
    static unsigned int m_table_desc3[3];
    static unsigned int m_table_desc4[3];
    static unsigned int m_table_desc5[3];
    static unsigned int m_table_desc6[3];
    static unsigned int m_table_desc7[3];
    static unsigned int m_table_desc8[3];
    static unsigned int m_table_desc9[3];
    static unsigned int m_table_desc10[3];
    static unsigned int m_table_desc11[3];
    static unsigned int m_table_desc12[3];
    static unsigned int m_table_desc13[3];
    static unsigned int m_table_desc14[3];
    static unsigned int m_table_desc15[3];
    static unsigned int m_table_desc16[3];
    static unsigned int m_table_desc17[3];
    static unsigned int m_table_desc18[3];
    static unsigned int m_table_desc19[3];
    static unsigned int m_table_desc20[3];
    static unsigned int m_table_desc21[3];
    static unsigned int m_table_desc22[3];
    static unsigned int m_table_desc23[3];
    static unsigned int m_table_desc24[3];
    static unsigned int m_table[7][0x15C / sizeof(unsigned int)];

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

    void SetStdProjectionMatrix();
    void draw();

    void calcViewerCameraMatrix(float (*)[4], const SRT*);
    void SetViewerSRT(const SRT*);
    void GetViewMatrix(float (*)[4]);

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

    Mtx m_cameraMatrix;
    u8 _pad34[0x64 - 0x34];
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
    u8 _pad108[0x404 - 0x108];
    u8 m_fullScreenShadowEnabled; // 0x404
    u8 _pad405[0x414 - 0x405];
    CBound m_shadowRectBound; // 0x414
    u8 _pad42C[0x4C8 - 0x42C];
};

extern "C" void create__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroy__10CCameraPcsFv(CCameraPcs*);
extern "C" void calc__10CCameraPcsFv(CCameraPcs*);
extern "C" void draw__10CCameraPcsFv(CCameraPcs*);
extern "C" void createChara__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroyChara__10CCameraPcsFv(CCameraPcs*);
extern "C" void calcChara__10CCameraPcsFv(CCameraPcs*);
extern "C" void createMap__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroyMap__10CCameraPcsFv(CCameraPcs*);
extern "C" void calcMap__10CCameraPcsFv(CCameraPcs*);
extern "C" void createMaterialEditor__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroyMaterialEditor__10CCameraPcsFv(CCameraPcs*);
extern "C" void calcMaterialEditor__10CCameraPcsFv(CCameraPcs*);
extern "C" void createFunnyShape__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroyFunnyShape__10CCameraPcsFv(CCameraPcs*);
extern "C" void calcFunnyShape__10CCameraPcsFv(CCameraPcs*);
extern "C" void createPart__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroyPart__10CCameraPcsFv(CCameraPcs*);
extern "C" void calcPart__10CCameraPcsFv(CCameraPcs*);
extern "C" void createFullShadow__10CCameraPcsFv(CCameraPcs*);
extern "C" void destroyFullShadow__10CCameraPcsFv(CCameraPcs*);
extern "C" void drawShadowBegin__10CCameraPcsFv(CCameraPcs*);
extern "C" void drawShadowEnd__10CCameraPcsFv(CCameraPcs*);
extern "C" void drawShadowChrBegin__10CCameraPcsFv(CCameraPcs*);
extern "C" void drawShadowEndAll__10CCameraPcsFv(CCameraPcs*);

extern CCameraPcs CameraPcs;

#endif // _FFCC_P_CAMERA_H_
