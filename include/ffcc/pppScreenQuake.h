#ifndef _PPP_SCREENQUAKE_H_
#define _PPP_SCREENQUAKE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char field0_0x0[128];
} pppScreenQuake;

typedef struct {
    int m_graphId;
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    float m_initWOrk2;
    float m_stepValue2;
    float m_arg4;
    float m_initWOrk3;
    float m_stepValue3;
    float m_quakeParam0;
    float m_quakeParam1;
    float m_quakeParam2;
} UnkB;

typedef struct {
    int m_unk0;
    int m_unk4;
    int m_unk8;
    int *m_serializedDataOffsets;
} UnkC;

void pppConScreenQuake(pppScreenQuake *quake, UnkC *param2);
void pppCon2ScreenQuake(pppScreenQuake *quake, UnkC *param2);
void pppDesScreenQuake(void);
void pppFrameScreenQuake(pppScreenQuake *quake, UnkB *param2, UnkC *param3);
void pppRenderScreenQuake(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENQUAKE_H_
