#ifndef _PPP_MIASMA_H_
#define _PPP_MIASMA_H_

#include <dolphin/types.h>

struct Vec;
struct _pppPObject;

typedef struct {
    u8 m_pad_0x0[0xc];
    s32 m_graphId;
    u8 m_pad_0x10[0x70];
} pppMiasma;

typedef struct {
    s32 m_graphId;
    u8 m_pad_0x4[0x14];
    s16 m_addPosX;
    s16 m_addPosY;
    s16 m_addPosZ;
    s16 m_addPosW;
    s16 m_addVelX;
    s16 m_addVelY;
    s16 m_addVelZ;
    s16 m_addVelW;
    s16 m_addAccX;
    s16 m_addAccY;
    s16 m_addAccZ;
    s16 m_addAccW;
} pppMiasmaFrameStep;

typedef struct {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
} pppMiasmaCtrl;

void CalcSphereRadius(Vec*, unsigned short);
void CreateScaleMatrix(_pppPObject*, float);

#ifdef __cplusplus
extern "C" {
#endif

void pppRenderMiasma(pppMiasma*, void*, pppMiasmaCtrl*);
void pppConstructMiasma(pppMiasma*, pppMiasmaCtrl*);
void pppConstruct2Miasma(pppMiasma*, pppMiasmaCtrl*);
void pppDestructMiasma(void);
void pppFrameMiasma(pppMiasma*, pppMiasmaFrameStep*, pppMiasmaCtrl*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MIASMA_H_
