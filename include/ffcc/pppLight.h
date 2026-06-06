#ifndef _PPP_LIGHT_H_
#define _PPP_LIGHT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct PppLightDataOffsets {
	s32 m_workOffset;
};

struct PppLightStep {
	s32 m_sourceId;
	u8 m_pad04[0x4];
	s16 m_colorDeltas[12];
	f32 m_attenFalloff;
	f32 m_attenFalloffVelocity;
	f32 m_attenFalloffAccel;
	f32 m_attenRadius;
	f32 m_attenRadiusVelocity;
	f32 m_attenRadiusAccel;
	f32 m_spotScale;
	f32 m_spotScaleVelocity;
	f32 m_spotScaleAccel;
	u32 m_targetIndex;
	u8 m_pad48[0x4];
	f32 m_specularScale;
	f32 m_specularScaleVelocity;
	f32 m_specularScaleAccel;
	u8 m_type;
	u8 m_color0Enabled;
	u8 m_color1Enabled;
	u8 m_color2Enabled;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppLight(struct _pppPObject* object, PppLightStep* step, _pppCtrlTable* ctrlTable);
void pppLightCon(struct _pppPObject* object, _pppCtrlTable* ctrlTable);
void pppLightCon3(struct _pppPObject* object, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LIGHT_H_
