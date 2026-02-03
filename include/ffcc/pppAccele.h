#ifndef _FFCC_PPPACCELE_H_
#define _FFCC_PPPACCELE_H_

typedef struct {
    char pad[8];      // padding to offset 0x08
    int m_graphId;    // 0x08
} pppAcceleObj;

typedef struct {
    int m_field_00;         // 0x00
    int m_field_04;         // 0x04  
    int m_graphId;          // 0x08
    float m_initWOrk;       // 0x0C
    float m_stepValue;      // 0x10
    float m_arg3;          // 0x14
} UnkB;

typedef struct {
    char pad[0x0C];           // padding to 0x0C
    int* m_serializedDataOffsets; // 0x0C
} UnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppAccele(pppAcceleObj* obj, UnkB* param_2, UnkC* param_3);
void pppAcceleCon(pppAcceleObj* obj, UnkC* param);

#ifdef __cplusplus
}
#endif

#endif
