#ifndef _PPP_LENSFLARE_H_
#define _PPP_LENSFLARE_H_

#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLensFlare(pppColum* obj, _pppCtrlTable* ctrlTable);
void pppDestructLensFlare(pppColum* obj, _pppCtrlTable* ctrlTable);
void pppFrameLensFlare(pppColum* obj, pppColumUnkB* step, _pppCtrlTable* ctrlTable);
void pppRenderLensFlare(pppColum* obj, pppColumUnkB* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LENSFLARE_H_
