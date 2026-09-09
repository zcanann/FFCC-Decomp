#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

#include "ffcc/pppChangeTexCommon.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct _pppCtrlTable;
struct _pppPObject;
class CGObject;
class CTexture;

typedef _pppPObject pppChangeTex;

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
void pppFrameChangeTex(pppChangeTex*, ChangeTexStep*, _pppCtrlTable*);
void pppRenderChangeTex(pppChangeTex*, ChangeTexStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGETEX_H_
