#ifndef _FFCC_P_LIGHT_H_
#define _FFCC_P_LIGHT_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <dolphin/gx.h>

class COctTree;
struct Vec;

class CLightPcs : public CProcess
{
public:
    class CBumpLight
    {
    public:
        CBumpLight();
        
        void MakeLightMap();
        void SetTexture(_GXTexMapID, int);
    };
    class CLight
    {
    public:
        CLight();

        void Set(CLightPcs::CLight*);
    };
    enum TARGET
    {
        TODO,
    };

    CLightPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);
    void create();
    void destroy();
    void DestroyBumpLightAll(CLightPcs::TARGET);
    void calc();
    void draw();
    void Clear();
    void Add(CLightPcs::CLight*);
    void GetFreeBumpLight(CLightPcs::TARGET);
    CLightPcs::CBumpLight* AddBump(CLightPcs::CLight*, CLightPcs::TARGET, CMemory::CStage*, int);
    void SetMapColorAlpha(float (*)[4], _GXColor, _GXColor, unsigned char, float, float, float, unsigned char);
    void SetAmbient(_GXColor);
    void SetAmbientAlpha(float);
    void SetNumDiffuse(unsigned long);
    void SetDiffuseColor(unsigned long, _GXColor);
    void EnableLight(int, int);
    void SetDiffuse(unsigned long, _GXColor, Vec*, int);
    void SetPosition(CLightPcs::TARGET, Vec*, unsigned long);
    void SetBit32(CLightPcs::TARGET, unsigned long*);
    void SetPart(CLightPcs::TARGET, void*, unsigned char);
    void InsertOctTree(CLightPcs::TARGET, COctTree&);
    void MakeLightMap();
    void SetBumpTexMatirx(float (*)[4], CLightPcs::CBumpLight*, Vec*, unsigned char);
};

void setchanctrl(CLightPcs::TARGET, unsigned long);

#endif // _FFCC_P_LIGHT_H_
