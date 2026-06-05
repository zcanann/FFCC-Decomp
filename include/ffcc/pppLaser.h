#ifndef _PPP_LASER_H_
#define _PPP_LASER_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppLaserStep;

typedef _pppPObject pppLaser;
typedef pppLaserStep pppLaserUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLaser(pppLaser* pppLaser, _pppCtrlTable* param_2);
void pppConstruct2Laser(pppLaser* pppLaser, _pppCtrlTable* param_2);
void pppDestructLaser(pppLaser* pppLaser, _pppCtrlTable* param_2);
void pppFrameLaser(pppLaser* pppLaser, pppLaserUnkB* param_2, _pppCtrlTable* param_3);
void pppRenderLaser(pppLaser* pppLaser, pppLaserUnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LASER_H_
