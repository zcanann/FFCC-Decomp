#ifndef _FFCC_P_CAMERA_H_
#define _FFCC_P_CAMERA_H_

#include "ffcc/system.h"

#include <dolphin/gx.h>

class SRT;
class CBound;
struct Vec;
class CVector;
class CMapPcs;
class CGObject;
class CPad;
class CColor;

void dbgDrawSphere(float, float, float, float, unsigned char, unsigned char, unsigned char);

class CCameraPcs : public CProcess
{
public:
    class camdtst
    {
    public:
        
    };

    CCameraPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

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
    void GetShadowRect(CBound&);
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
    void SetOffsetZBuff(float);
    void SetZRotate(float);
    void SetPosition(Vec*);
    void SetRefPosition(Vec*);
    void addWorldMap();
    void SetIsAbsolute(int);
    int IsAbsolute();
    void SetWorldMapMatrix(float (*)[4]);
    void GetWorldMapInverseMatrix(float (*)[4]);

    // TODO
    float _228_4_;
};

extern CCameraPcs CameraPcs;

#endif // _FFCC_P_CAMERA_H_
