#ifndef _FFCC_PPPDRAWMDLTS_H_
#define _FFCC_PPPDRAWMDLTS_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct DrawMdlTsDataOffsets {
    s32 m_colorWorkOffset;
    s32 _unused04;
    s32 m_texCoordOffset;
};

struct PDrawMdlTs {
    s32 m_graphId;            // 0x00
    u32 m_modelIndex;         // 0x04
    u8 m_pad8;                // 0x08
    u8 m_blendMode;           // 0x09
    u8 m_fogIndex;            // 0x0A
    u8 m_cullMode;            // 0x0B
    u8 m_zEnable;             // 0x0C
    u8 m_colorUpdate;         // 0x0D
    u8 m_zWrite;              // 0x0E
    u8 m_padF;                // 0x0F
    f32 m_depth;              // 0x10
    f32 m_texCoordAdd[6];     // 0x14
    u8 m_lightTarget;         // 0x2C
};

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMdlTsCon(struct _pppPObject* obj, struct _pppCtrlTable* ctrl);
void pppDrawMdlTsCon3(struct _pppPObject* obj, struct _pppCtrlTable* ctrl);
void pppDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct _pppCtrlTable* ctrl);
void pppDrawDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMDLTS_H_
