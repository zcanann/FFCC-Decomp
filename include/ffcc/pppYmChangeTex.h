#ifndef _PPP_YMCHANGETEX_H_
#define _PPP_YMCHANGETEX_H_

#include "ffcc/pppChangeTexCommon.h"

#include <dolphin/gx.h>

struct _pppCtrlTable;
struct _pppPObject;
class CGObject;
class CTexture;

typedef _pppPObject pppYmChangeTex;
typedef ChangeTexStep pppYmChangeTexStep;

struct pppYmChangeTexState {
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
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmChangeTex(pppYmChangeTex*, _pppCtrlTable*);
void pppDestructYmChangeTex(pppYmChangeTex*, _pppCtrlTable*);
void pppFrameYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, _pppCtrlTable*);
void pppRenderYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCHANGETEX_H_
