#ifndef _PPP_LENSFLARE_H_
#define _PPP_LENSFLARE_H_

#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"

struct LensFlareDataOffsets {
	s32 _unused0;
	s32 m_colorWorkOffset;
	s32 m_workOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLensFlare(pppColum* obj, _pppCtrlTable* ctrlTable);
void pppDestructLensFlare(pppColum* obj, _pppCtrlTable* ctrlTable);
void pppFrameLensFlare(pppColum* obj, pppColumStep* step, _pppCtrlTable* ctrlTable);
void pppRenderLensFlare(pppColum* obj, pppColumStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LENSFLARE_H_
