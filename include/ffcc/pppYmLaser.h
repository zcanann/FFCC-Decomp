#ifndef _PPP_YMLASER_H_
#define _PPP_YMLASER_H_

#include "ffcc/partMng.h"

struct pppYmLaser {
    u8 field_0x0[0x84];
    f32 field_0x84;
    f32 field_0x88;
    f32 field_0x8c;
    f32 field_0x90;
    f32 field_0x94;
    f32 field_0x98;
    f32 field_0x9c;
    f32 field_0xa0;
    f32 field_0xa4;
    f32 field_0xa8;
    u8 field_0xac;
};

struct pppYmLaserUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_stepValue;
    s32 m_arg3;
    u8* m_payload;
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
