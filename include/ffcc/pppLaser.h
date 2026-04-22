#ifndef _PPP_LASER_H_
#define _PPP_LASER_H_

#include "ffcc/partMng.h"

struct pppLaser {
    u8 m_header[0x10];
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    u8 m_pad70[0x10];
};

struct pppLaserUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8 m_payload[0x40];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLaser(struct pppLaser* pppLaser, _pppCtrlTable* param_2);
void pppConstruct2Laser(struct pppLaser* pppLaser, _pppCtrlTable* param_2);
void pppDestructLaser(struct pppLaser* pppLaser, _pppCtrlTable* param_2);
void pppFrameLaser(struct pppLaser* pppLaser, struct pppLaserUnkB* param_2, _pppCtrlTable* param_3);
void pppRenderLaser(struct pppLaser* pppLaser, struct pppLaserUnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LASER_H_
