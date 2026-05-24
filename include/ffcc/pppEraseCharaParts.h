#ifndef _PPP_ERASECHARAPARTS_H_
#define _PPP_ERASECHARAPARTS_H_

#include "ffcc/chara.h"
#include "ffcc/partMng.h"
#include <dolphin/types.h>

struct pppEraseCharaParts {
    _pppPObject m_object;
};

struct pppEraseCharaPartsUnkB {
    u8 m_unk0[4];
    s8 m_meshIndex;
};

struct pppEraseCharaPartsUnkC {
    u8 m_unk0[0xC];
    s32* m_serializedDataOffsets;
};

void EraseCharaParts_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEraseCharaParts(pppEraseCharaParts*, pppEraseCharaPartsUnkC*);
void pppDestructEraseCharaParts(pppEraseCharaParts*, pppEraseCharaPartsUnkC*);
void pppFrameEraseCharaParts(pppEraseCharaParts*, pppEraseCharaPartsUnkB*, pppEraseCharaPartsUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_ERASECHARAPARTS_H_

