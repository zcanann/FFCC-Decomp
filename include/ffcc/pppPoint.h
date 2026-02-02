#ifndef _PPP_POINT_H_
#define _PPP_POINT_H_

struct PppData {
    int id;
    float values[4]; // x, y, z, w
    void* ptr;
};

void pppPoint(PppData* a, PppData* b, PppData* c);
void pppPointCon(PppData* a, PppData* b);

#endif // _PPP_POINT_H_
