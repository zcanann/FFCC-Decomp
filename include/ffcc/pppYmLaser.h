#ifndef _PPP_YMLASER_H_
#define _PPP_YMLASER_H_

#include "ffcc/partMng.h"

struct pppYmLaser {
    u8 m_header[0x10];
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    u8 m_pad70[0x10];
};

struct pppYmLaserUnkB {
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

void pppConstructYmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable);
void pppConstruct2YmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable);
void pppDestructYmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable);
void pppFrameYmLaser(pppYmLaser* laser, pppYmLaserUnkB* step, _pppCtrlTable* ctrlTable);
void pppRenderYmLaser(pppYmLaser* laser, pppYmLaserUnkB* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLASER_H_
