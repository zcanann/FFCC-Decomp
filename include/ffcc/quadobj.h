#ifndef _FFCC_PPP_QUADOBJ_H_
#define _FFCC_PPP_QUADOBJ_H_

#include "ffcc/baseobj.h"

struct Vec;

class CGQuadObj : public CGBaseObj
{
public:
    virtual void onCreate();
    virtual void onDestroy();
    virtual void onDraw();
    virtual int GetCID();
    bool isInner(Vec*);
    void Reset(float base, float height);
    void Add(float x, float y);
    
private:
    struct QuadVertex {
        float x;
        float z;
    };

    unsigned char m_vertexCount; // 0x50
    QuadVertex m_vertices[8];    // 0x54 - 0x94
    float m_bboxMinX;            // 0x94
    float m_bboxMinZ;            // 0x98
    float m_bboxMaxX;            // 0x9C
    float m_bboxMaxZ;            // 0xA0
    float m_yBase;               // 0xA4
    float m_yHeight;             // 0xA8
};

#endif // _FFCC_PPP_QUADOBJ_H_
