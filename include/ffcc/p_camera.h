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

extern unsigned int PTR_s_CCameraPcs_GAME__801e915c[];
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

    CCameraPcs()
    {
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x414) = FLOAT_8032fa78;
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x418) = FLOAT_8032fa78;
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x41C) = FLOAT_8032fa78;
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x420) = FLOAT_8032fa7c;
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x424) = FLOAT_8032fa7c;
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x428) = FLOAT_8032fa7c;

        unsigned int* dst = PTR_s_CCameraPcs_GAME__801e915c;
        dst[0x004 / 4] = m_table_desc0__10CCameraPcs[0];
        dst[0x008 / 4] = m_table_desc0__10CCameraPcs[1];
        dst[0x00C / 4] = m_table_desc0__10CCameraPcs[2];
        dst[0x010 / 4] = m_table_desc1__10CCameraPcs[0];
        dst[0x014 / 4] = m_table_desc1__10CCameraPcs[1];
        dst[0x018 / 4] = m_table_desc1__10CCameraPcs[2];
        dst[0x01C / 4] = m_table_desc2__10CCameraPcs[0];
        dst[0x020 / 4] = m_table_desc2__10CCameraPcs[1];
        dst[0x024 / 4] = m_table_desc2__10CCameraPcs[2];
        dst[0x030 / 4] = m_table_desc3__10CCameraPcs[0];
        dst[0x034 / 4] = m_table_desc3__10CCameraPcs[1];
        dst[0x038 / 4] = m_table_desc3__10CCameraPcs[2];
        dst[0x160 / 4] = m_table_desc4__10CCameraPcs[0];
        dst[0x164 / 4] = m_table_desc4__10CCameraPcs[1];
        dst[0x168 / 4] = m_table_desc4__10CCameraPcs[2];
        dst[0x16C / 4] = m_table_desc5__10CCameraPcs[0];
        dst[0x170 / 4] = m_table_desc5__10CCameraPcs[1];
        dst[0x174 / 4] = m_table_desc5__10CCameraPcs[2];
        dst[0x178 / 4] = m_table_desc6__10CCameraPcs[0];
        dst[0x17C / 4] = m_table_desc6__10CCameraPcs[1];
        dst[0x180 / 4] = m_table_desc6__10CCameraPcs[2];
        dst[0x2BC / 4] = m_table_desc7__10CCameraPcs[0];
        dst[0x2C0 / 4] = m_table_desc7__10CCameraPcs[1];
        dst[0x2C4 / 4] = m_table_desc7__10CCameraPcs[2];
        dst[0x2C8 / 4] = m_table_desc8__10CCameraPcs[0];
        dst[0x2CC / 4] = m_table_desc8__10CCameraPcs[1];
        dst[0x2D0 / 4] = m_table_desc8__10CCameraPcs[2];
        dst[0x2D4 / 4] = m_table_desc9__10CCameraPcs[0];
        dst[0x2D8 / 4] = m_table_desc9__10CCameraPcs[1];
        dst[0x2DC / 4] = m_table_desc9__10CCameraPcs[2];
        dst[0x418 / 4] = m_table_desc10__10CCameraPcs[0];
        dst[0x41C / 4] = m_table_desc10__10CCameraPcs[1];
        dst[0x420 / 4] = m_table_desc10__10CCameraPcs[2];
        dst[0x424 / 4] = m_table_desc11__10CCameraPcs[0];
        dst[0x428 / 4] = m_table_desc11__10CCameraPcs[1];
        dst[0x42C / 4] = m_table_desc11__10CCameraPcs[2];
        dst[0x430 / 4] = m_table_desc12__10CCameraPcs[0];
        dst[0x434 / 4] = m_table_desc12__10CCameraPcs[1];
        dst[0x438 / 4] = m_table_desc12__10CCameraPcs[2];
        dst[0x574 / 4] = m_table_desc13__10CCameraPcs[0];
        dst[0x578 / 4] = m_table_desc13__10CCameraPcs[1];
        dst[0x57C / 4] = m_table_desc13__10CCameraPcs[2];
        dst[0x580 / 4] = m_table_desc14__10CCameraPcs[0];
        dst[0x584 / 4] = m_table_desc14__10CCameraPcs[1];
        dst[0x588 / 4] = m_table_desc14__10CCameraPcs[2];
        dst[0x58C / 4] = m_table_desc15__10CCameraPcs[0];
        dst[0x590 / 4] = m_table_desc15__10CCameraPcs[1];
        dst[0x594 / 4] = m_table_desc15__10CCameraPcs[2];
        dst[0x6D0 / 4] = m_table_desc16__10CCameraPcs[0];
        dst[0x6D4 / 4] = m_table_desc16__10CCameraPcs[1];
        dst[0x6D8 / 4] = m_table_desc16__10CCameraPcs[2];
        dst[0x6DC / 4] = m_table_desc17__10CCameraPcs[0];
        dst[0x6E0 / 4] = m_table_desc17__10CCameraPcs[1];
        dst[0x6E4 / 4] = m_table_desc17__10CCameraPcs[2];
        dst[0x6E8 / 4] = m_table_desc18__10CCameraPcs[0];
        dst[0x6EC / 4] = m_table_desc18__10CCameraPcs[1];
        dst[0x6F0 / 4] = m_table_desc18__10CCameraPcs[2];
        dst[0x82C / 4] = m_table_desc19__10CCameraPcs[0];
        dst[0x830 / 4] = m_table_desc19__10CCameraPcs[1];
        dst[0x834 / 4] = m_table_desc19__10CCameraPcs[2];
        dst[0x838 / 4] = m_table_desc20__10CCameraPcs[0];
        dst[0x83C / 4] = m_table_desc20__10CCameraPcs[1];
        dst[0x840 / 4] = m_table_desc20__10CCameraPcs[2];
        dst[0x844 / 4] = m_table_desc21__10CCameraPcs[0];
        dst[0x848 / 4] = m_table_desc21__10CCameraPcs[1];
        dst[0x84C / 4] = m_table_desc21__10CCameraPcs[2];
        dst[0x858 / 4] = m_table_desc22__10CCameraPcs[0];
        dst[0x85C / 4] = m_table_desc22__10CCameraPcs[1];
        dst[0x860 / 4] = m_table_desc22__10CCameraPcs[2];
        dst[0x86C / 4] = m_table_desc23__10CCameraPcs[0];
        dst[0x870 / 4] = m_table_desc23__10CCameraPcs[1];
        dst[0x874 / 4] = m_table_desc23__10CCameraPcs[2];
        dst[0x880 / 4] = m_table_desc24__10CCameraPcs[0];
        dst[0x884 / 4] = m_table_desc24__10CCameraPcs[1];
        dst[0x888 / 4] = m_table_desc24__10CCameraPcs[2];
    }

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
};

extern CCameraPcs CameraPcs;

#endif // _FFCC_P_CAMERA_H_
