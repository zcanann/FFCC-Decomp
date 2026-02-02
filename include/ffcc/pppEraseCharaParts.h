#ifndef _PPP_ERASECHARAPARTS_H_
#define _PPP_ERASECHARAPARTS_H_

#include "ffcc/chara.h"

void EraseCharaParts_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEraseCharaParts(void);
void pppDestructEraseCharaParts(void);
void pppFrameEraseCharaParts(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_ERASECHARAPARTS_H_
