#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

#include "ffcc/chara.h"
#include "ffcc/pppChangeTexCommon.h"
#include "ffcc/materialman.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"
#include "dolphin/gx/GXDispList.h"
#include "dolphin/gx/GXVert.h"
#include <dolphin/types.h>

class CGObject;
class CTexture;

struct pppChangeTex {
    _pppPObject m_object;
};

struct pppChangeTexUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    union {
        u8 m_payload[6];
        struct Payload {
            u8 m_mode;
            u8 m_pad01[5];
        } m_changeTex;
    };
    u8 _pad1[1];
};

struct ChangeTexWork {
    float m_value0;
    float m_value1;
    float m_value2;
    GXColor** m_meshColorArrays;
    ChangeTexDisplayListCopy*** m_displayListArrays;
    int _pad14;
    CGObject* m_charaObj;
    CTexture* m_texture;
    int _pad20;
    void* m_context;
    Vec m_bboxMin;
    int _pad34;
    Vec m_bboxMax;
    float m_cachedValue;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppConstruct2ChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppDestructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppFrameChangeTex(pppChangeTex*, pppChangeTexUnkB*, _pppCtrlTable*);
void pppRenderChangeTex(pppChangeTex*, pppChangeTexUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGETEX_H_
