#ifndef _PPP_POBJPOINT_H_
#define _PPP_POBJPOINT_H_

#include <stddef.h>

struct PppObjData {
    unsigned int id;          // 0x0
    unsigned int field_4;     // 0x4
    void* data;      // 0x8
    unsigned int objId;       // 0xc
};

struct PppPointData {
    void* field_0;   // 0x0
    void* matrix;    // 0x4 - points to transformation matrix
    unsigned int field_8;     // 0x8
    unsigned int id;          // 0xc
    float field_10;    // 0x10
    float field_14;    // 0x14
    float field_18;    // 0x18
    float x;           // 0x1c
    float field_20;    // 0x20
    float field_24;    // 0x24
    float field_28;    // 0x28
    float y;           // 0x2c
    float field_30;    // 0x30
    float field_34;    // 0x34
    float field_38;    // 0x38
    float z;           // 0x3c
};

struct PppContainer {
    unsigned int field_0[3];  // 0x0-0x8
    void* ptrData;   // 0xc
};

struct PppPointObj {
    float x;           // 0x0
    float y;           // 0x4
    float z;           // 0x8
    unsigned char padding[4];   // 0xc
    void* vecPtr;    // 0x10
};

void pppParMatrix(PppPointData* pointData);
void pppPObjPoint(PppPointData* pointData, PppObjData* objData, PppContainer* container);

#endif // _PPP_POBJPOINT_H_
