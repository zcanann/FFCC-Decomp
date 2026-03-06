#ifndef _FFCC_PPPACCELE_H_
#define _FFCC_PPPACCELE_H_

typedef struct {
    char pad[0x0C];   // padding to offset 0x0C
    int m_graphId;    // 0x0C
} pppAcceleObj;

typedef struct {
    int m_graphId;          // 0x00
    int m_field_04;         // 0x04
    float m_initWOrk;       // 0x08
    float m_stepValue;      // 0x0C
    float m_arg3;           // 0x10
} pppAcceleUnkB;

typedef struct {
    char pad[0x0C];           // padding to 0x0C
    int* m_serializedDataOffsets; // 0x0C
} pppAcceleUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppAccele(pppAcceleObj* obj, pppAcceleUnkB* param_2, pppAcceleUnkC* param_3);
void pppAcceleCon(pppAcceleObj* obj, pppAcceleUnkC* param);

#ifdef __cplusplus
}
#endif

#endif

