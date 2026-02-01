#ifndef _PPP_POINT_H_
#define _PPP_POINT_H_

struct PppData {
    int id;
    float values[4]; // x, y, z, w
    void* ptr;
};

void pppPoint(void);
void pppPointCon(void);

#endif // _PPP_POINT_H_
