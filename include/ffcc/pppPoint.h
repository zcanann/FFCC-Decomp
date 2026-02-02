#ifndef _PPP_POINT_H_
#define _PPP_POINT_H_

struct PppData {
    int id;
    float values[4]; // x, y, z, w
    void* ptr;
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
