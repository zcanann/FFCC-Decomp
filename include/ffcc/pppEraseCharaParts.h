#ifndef _PPP_ERASECHARAPARTS_H_
#define _PPP_ERASECHARAPARTS_H_

#include "ffcc/chara.h"
#include <dolphin/types.h>

struct pppEraseCharaParts {
    u8 field0_0x0[8];
    u8 pad_0x8[0x80];
    u8 field_0x88[4];
};

struct UnkB {
    u8 m_unk0[4];
    s8 m_meshIndex;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

void EraseCharaParts_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEraseCharaParts(pppEraseCharaParts*, UnkC*);
void pppDestructEraseCharaParts(void);
void pppFrameEraseCharaParts(pppEraseCharaParts*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_ERASECHARAPARTS_H_
