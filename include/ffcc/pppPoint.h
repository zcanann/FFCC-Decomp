#ifndef _PPP_POINT_H_
#define _PPP_POINT_H_

struct PppData {
    int id;          // offset 0x0
    float values[2]; // offset 0x4, 0x8 
    void* ptr;       // offset 0xc
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPoint(PppData* a, PppData* b, PppData* c);
void pppPointCon(PppData* a, PppData* b);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINT_H_
