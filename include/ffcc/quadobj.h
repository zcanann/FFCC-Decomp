#ifndef _FFCC_PPP_QUADOBJ_H_
#define _FFCC_PPP_QUADOBJ_H_

struct Vec;

class CGQuadObj
{
public:
    void onCreate();
    void onDestroy();
    void onDraw();
    void isInner(Vec *);
    void Reset(float, float);
    void Add(float, float);
    void GetCID();
};

#endif // _FFCC_PPP_QUADOBJ_H_
