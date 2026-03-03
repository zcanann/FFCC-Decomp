#ifndef _FFCC_PPPANGACCELE_H_
#define _FFCC_PPPANGACCELE_H_

typedef struct {
    char pad[0x0C];
    int m_graphId; // 0x0C
} pppAngAcceleObj;

typedef struct {
    int m_graphId; // 0x00
    int m_field_04;
    int m_x;
    int m_y;
    int m_z;
} pppAngAcceleUnkB;

typedef struct {
    char pad[0x0C];
    int* m_serializedDataOffsets;
} pppAngAcceleUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngAccele(pppAngAcceleObj* obj, pppAngAcceleUnkB* param_2, pppAngAcceleUnkC* param_3);
void pppAngAcceleCon(pppAngAcceleObj* obj, pppAngAcceleUnkC* param);

#ifdef __cplusplus
}
#endif

#endif
