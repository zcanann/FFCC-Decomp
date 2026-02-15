#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

#include "ffcc/chara.h"
#include "ffcc/materialman.h"
#include "ffcc/mapmesh.h"
#include "dolphin/gx/GXDispList.h"
#include "dolphin/gx/GXVert.h"
#include <dolphin/types.h>

struct pppChangeTex {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
};

struct UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u8 _pad0[2];
    float m_stepValue;
    u8 m_arg3;
    u8 m_payload[6];
    u8 _pad1[1];
};

struct UnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif
void ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f2(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f2(CChara::CModel*, void*, void*, int, float (*)[4]);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructChangeTex(pppChangeTex*, UnkC*);
void pppConstruct2ChangeTex(pppChangeTex*, UnkC*);
void pppDestructChangeTex(pppChangeTex*, UnkC*);
void pppFrameChangeTex(pppChangeTex*, UnkB*, UnkC*);
void pppRenderChangeTex(pppChangeTex*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGETEX_H_
