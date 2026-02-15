#ifndef _PPP_YMLOOKON_H_
#define _PPP_YMLOOKON_H_

#ifdef __cplusplus
extern "C" {
#endif

struct pppYmLookOn {
    int field0_0x0[2];
};

struct UnkB {
    int m_graphId;
    float m_dataValIndex;
};

struct UnkC {
    unsigned char pad[0x0C];
    int* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmLookOn(struct pppYmLookOn* pppYmLookOn, struct UnkC* param_2);
void pppFrameYmLookOn(struct pppYmLookOn* pppYmLookOn, struct UnkB* param_2, struct UnkC* param_3);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLOOKON_H_
