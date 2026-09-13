#ifndef _PPP_LASER_H_
#define _PPP_LASER_H_

#include "ffcc/pppLaserCommon.h"

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppLaser;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLaser(pppLaser* laser, _pppCtrlTable* ctrlTable);
void pppConstruct2Laser(pppLaser* laser, _pppCtrlTable* ctrlTable);
void pppDestructLaser(pppLaser* laser, _pppCtrlTable* ctrlTable);
void pppFrameLaser(pppLaser* laser, pppLaserStep* step, _pppCtrlTable* ctrlTable);
void pppRenderLaser(pppLaser* laser, pppLaserStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LASER_H_
