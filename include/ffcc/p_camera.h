#ifndef _FFCC_P_CAMERA_H_
#define _FFCC_P_CAMERA_H_

#include "ffcc/system.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class SRT;
class CBound;
struct Vec;
class CVector;
class CMapPcs;
class CGObject;
class CPad;
class CColor;

extern unsigned int PTR_s_CCameraPcs_GAME__801e915c[][0x15C / sizeof(unsigned int)];
extern unsigned int m_table_desc0__10CCameraPcs[];
extern unsigned int m_table_desc1__10CCameraPcs[];
extern unsigned int m_table_desc2__10CCameraPcs[];
extern unsigned int m_table_desc3__10CCameraPcs[];
extern unsigned int m_table_desc4__10CCameraPcs[];
extern unsigned int m_table_desc5__10CCameraPcs[];
extern unsigned int m_table_desc6__10CCameraPcs[];
extern unsigned int m_table_desc7__10CCameraPcs[];
extern unsigned int m_table_desc8__10CCameraPcs[];
extern unsigned int m_table_desc9__10CCameraPcs[];
extern unsigned int m_table_desc10__10CCameraPcs[];
extern unsigned int m_table_desc11__10CCameraPcs[];
extern unsigned int m_table_desc12__10CCameraPcs[];
extern unsigned int m_table_desc13__10CCameraPcs[];
extern unsigned int m_table_desc14__10CCameraPcs[];
extern unsigned int m_table_desc15__10CCameraPcs[];
extern unsigned int m_table_desc16__10CCameraPcs[];
extern unsigned int m_table_desc17__10CCameraPcs[];
extern unsigned int m_table_desc18__10CCameraPcs[];
extern unsigned int m_table_desc19__10CCameraPcs[];
extern unsigned int m_table_desc20__10CCameraPcs[];
extern unsigned int m_table_desc21__10CCameraPcs[];
extern unsigned int m_table_desc22__10CCameraPcs[];
extern unsigned int m_table_desc23__10CCameraPcs[];
extern unsigned int m_table_desc24__10CCameraPcs[];
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
    u8 _pad34[0x94 - 0x34];
    Mtx44 m_screenMatrix;
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    float _236_4_;
    float _240_4_;
    float _244_4_;
    float _248_4_;
    float _252_4_;
    u8 _pad100[0x4C8 - 0x100];
};

extern CCameraPcs CameraPcs;

#endif // _FFCC_P_CAMERA_H_
