#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

#include "ffcc/partMng.h"

class CCameraPcs;
struct Vec;

struct pppYmDeformationScreen {
	_pppPObject m_object;
};

struct YmDeformationScreenOffsetData {
	int unk0;
	int unk1;
	int offset;
};

struct YmDeformationScreenParam {
	char pad[0xc];
	YmDeformationScreenOffsetData* offsetData;
};

struct VYmDeformationScreen {
	float m_depth;
	s16 m_angle;
	u8 m_direction;
	u8 m_pad;
	float m_scale;
	float m_values[5];
};

struct YmDeformationScreenData {
	char pad[0xc];
	int* m_serializedDataOffsets;
};

struct YmDeformationScreenStep {
	int m_graphId;
	int m_dataValIndex;
	float m_initWOrk;
	float m_stepValue;
	float m_arg3;
	float m_payload0;
	float m_payload1;
	float m_payload2;
	short m_payload3;
	char m_payloadBytes[0x1a];
};

void SetUpIndWarp(VYmDeformationScreen*);
void CCameraPcs_GetRefPosition(Vec*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationScreen(pppYmDeformationScreen*, void*);
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen*, void*);
void pppDestructYmDeformationScreen(pppYmDeformationScreen*, void*);
void pppFrameYmDeformationScreen(pppYmDeformationScreen*, void*, void*);
void pppRenderYmDeformationScreen(pppYmDeformationScreen*, void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSCREEN_H_
