#ifndef _FFCC_PPPDRAWMDL_H_
#define _FFCC_PPPDRAWMDL_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct PDrawMdl {
    s32 m_graphId;        // 0x00
    u32 m_modelIndex;     // 0x04
    u8 m_pad8;            // 0x08
    u8 m_blendMode;       // 0x09
    u8 m_drawB;           // 0x0A
    u8 m_drawD;           // 0x0B
    u8 m_drawE;           // 0x0C
    u8 m_drawF;           // 0x0D
    u8 m_drawG;           // 0x0E
    u8 m_padF;            // 0x0F
    f32 m_texScale;       // 0x10
    u8 m_drawA;           // 0x14
};

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMdl0(struct _pppPObject*, struct PDrawMdl*, struct _pppCtrlTable*);
void pppDrawMdl(struct _pppPObject*, struct PDrawMdl*, struct _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMDL_H_
