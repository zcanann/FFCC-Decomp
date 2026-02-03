#ifndef _PPP_SCREENQUAKE_H_
#define _PPP_SCREENQUAKE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char field0_0x0[128];
} pppScreenQuake;

typedef struct {
    int m_dataValIndex;
    int m_graphId;
    int m_arg3;
    float m_initWOrk;
    float m_stepValue;
    float *m_payload;
} UnkB;

typedef struct {
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
