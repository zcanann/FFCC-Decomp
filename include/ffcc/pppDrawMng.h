#ifndef _FFCC_PPPDRAWMNG_H_
#define _FFCC_PPPDRAWMNG_H_

#include "ffcc/p_chara.h"

struct _pppMngSt;

class pppDrawMng {
public:
    void ClearOt();
    void DrawOt();
    void AddPrimOt(unsigned long, _pppMngSt*);
    void AddPrim(float depth, _pppMngSt* pppMngSt, signed char offset);
    void AddPrim(float depth, CCharaPcs::CHandle* handle);

    struct pppDrawPrimitive
    {
        pppDrawPrimitive* m_next; // 0x0
        unsigned char m_type;     // 0x4
        // Unused                 // 0x5-0x7
        void* m_handle;           // 0x8
    }; // Size 0xc

    pppDrawPrimitive* m_primitiveRefs[0x400]; // 0x0
    pppDrawPrimitive m_primitivePool[0x180];  // 0x1000
    pppDrawPrimitive* m_nextFree;             // 0x2200
    float m_depthScale;                       // 0x2204
}; // Size 0x2208

#endif // _FFCC_PPPDRAWMNG_H_
