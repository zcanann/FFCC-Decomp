#ifndef _PPP_YMLASER_H_
#define _PPP_YMLASER_H_

#include "ffcc/partMng.h"

struct pppYmLaser {
    _pppPObjLink m_link;
    s32 m_graphId;
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    u8 m_pad70[0x10];
    u8 m_workArea[1];
};

struct pppYmLaserUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    union {
        u8 m_payload[0x40];
        struct {
            s32 m_spawnPositionOffset;  // 0x00
            f32 m_lengthStepBase;       // 0x04
            f32 m_lengthStepVelocity;   // 0x08
            f32 m_lengthStepAccel;      // 0x0C
            f32 m_halfWidthBase;        // 0x10
            f32 m_halfWidthVelocity;    // 0x14
            f32 m_halfWidthAccel;       // 0x18
            u8 m_blendMode;             // 0x1C
            u8 m_hitInterval;           // 0x1D
            u8 m_pointCount;            // 0x1E
            u8 m_pad1F;                 // 0x1F
            f32 m_hitRadius;            // 0x20
            f32 m_hitScale;             // 0x24
            u8 m_trailColorR;           // 0x28
            u8 m_trailColorG;           // 0x29
            u8 m_trailColorB;           // 0x2A
            u8 m_trailAlpha;            // 0x2B
            s16 m_shapeFrameStep;       // 0x2C
            u8 m_pad2E[0x02];           // 0x2E
            f32 m_shapeScale;           // 0x30
            f32 m_spawnYOffset;         // 0x34
            u8 m_drawEnvColor0;         // 0x38
            u8 m_drawEnvColor1;         // 0x39
            u8 m_historyFrameCount;     // 0x3A
            u8 m_disableHitCylinder;    // 0x3B
            u8 m_disableHitObject;      // 0x3C
            u8 m_pad3D[0x03];           // 0x3D
        } m_laser;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

void pppRenderYmLaser(pppYmLaser* laser, pppYmLaserUnkB* step, _pppCtrlTable* ctrlTable);
void pppFrameYmLaser(pppYmLaser* laser, pppYmLaserUnkB* step, _pppCtrlTable* ctrlTable);
void pppDestructYmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable);
void pppConstruct2YmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable);
void pppConstructYmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLASER_H_
