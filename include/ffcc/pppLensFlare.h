#ifndef _PPP_LENSFLARE_H_
#define _PPP_LENSFLARE_H_

#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"

struct LensFlareDataOffsets {
	s32 _unused0;
	s32 m_colorWorkOffset;
	s32 m_workOffset;
};

struct LensFlareWork {
	u8 _pad00[0x10];
	f32 m_projectedX;
	f32 m_projectedY;
	f32 m_projectedZ;
	f32 _pad1C;
	Vec m_viewPosition;
	s16 m_shapeFrame0;
	s16 m_shapeFrame1;
	s16 m_shapeFrame2;
	u8 m_alpha;
	u8 _pad33;
	f32 m_dot;
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
