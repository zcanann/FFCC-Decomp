#ifndef _FFCC_P_LIGHT_H_
#define _FFCC_P_LIGHT_H_

void setchanctrl(CLightPcs::TARGET, unsigned long);

class CLightPcs::CBumpLight
{
public:
    void MakeLightMap();
    void SetTexture(_GXTexMapID, int);
    CBumpLight();
};

class CLightPcs::CLight
{
public:
    void operator=(const CLightPcs::CLight &);
    void Set(CLightPcs::CLight *);
    CLight();
};

class CLightPcs
{
public:
    void Init();
    void Quit();
    void GetTable(unsigned long);
    void create();
    void destroy();
    void DestroyBumpLightAll(CLightPcs::TARGET);
    void calc();
    void draw();
    void Clear();
    void Add(CLightPcs::CLight *);
    void GetFreeBumpLight(CLightPcs::TARGET);
    void AddBump(CLightPcs::CLight *, CLightPcs::TARGET, CMemory::CStage *, int);
    void SetMapColorAlpha(float (*)[4], _GXColor, _GXColor, unsigned char, float, float, float, unsigned char);
    void SetAmbient(_GXColor);
    void SetAmbientAlpha(float);
    void SetNumDiffuse(unsigned long);
    void SetDiffuseColor(unsigned long, _GXColor);
    void EnableLight(int, int);
    void SetDiffuse(unsigned long, _GXColor, Vec *, int);
    void SetPosition(CLightPcs::TARGET, Vec *, unsigned long);
    void SetBit32(CLightPcs::TARGET, unsigned long *);
    void SetPart(CLightPcs::TARGET, void *, unsigned char);
    void InsertOctTree(CLightPcs::TARGET, COctTree &);
    void MakeLightMap();
    void SetBumpTexMatirx(float (*)[4], CLightPcs::CBumpLight *, Vec *, unsigned char);
    CLightPcs();
};

#endif // _FFCC_P_LIGHT_H_
