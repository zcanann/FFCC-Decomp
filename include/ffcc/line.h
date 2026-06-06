#ifndef _FFCC_LINE_H_
#define _FFCC_LINE_H_

#include <dolphin/mtx.h>

struct CLineSegment {
    Vec delta;
    Vec normal;
    float length;
    float startLength;
};

template <int PointCount>
struct CLine {
    CLine();
    int Calc(Vec*, float*, unsigned long*, float*, Vec*, float);
    int IsInner(Vec*, float);
    void Draw();
    void CalcBound();

    Vec min;
    Vec max;
    unsigned int pointCount;
    unsigned int unused;
    float unk20[3];
    unsigned int m_mask;
    Vec points[PointCount];
    CLineSegment segments[PointCount - 1];
    float totalLength;
};

#endif // _FFCC_LINE_H_
