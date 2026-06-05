#ifndef _PPP_YMLASER_H_
#define _PPP_YMLASER_H_

#include "ffcc/pppLaserCommon.h"

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppYmLaser;
typedef pppLaserStep pppYmLaserUnkB;

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
