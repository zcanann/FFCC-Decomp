#ifndef _PPP_YMENV_H_
#define _PPP_YMENV_H_

#include "ffcc/p_chara.h"

#include <dolphin/gx.h>

struct _pppMngSt;
struct _pppPObject;
struct _pppEnvSt;
struct CGObject;
struct CTexture;
struct Vec;

void GetModelPtr(CGObject *);
void GetCharaNodeFrameMatrix(_pppMngSt *, float, float (*)[4]);
void CalcGraphValue(_pppPObject *, long, float &, float &, float &, float, float &, float &);
void GetTextureFromRSD(int, _pppEnvSt *);
void GetCharaModelPtr(CCharaPcs::CHandle *);
void GetCharaHandlePtr(CGObject *, long);
void DisableIndWarp(_GXTevStageID, _GXIndTexStageID);
void SetUpPaletteEnv(CTexture *);
void genParaboloidMap(void *, unsigned long *, unsigned short, _GXVtxFmt);
void GXEnd(void);
void drawParaboloidMap(_GXTexObj *, _GXTexObj *, void *, unsigned long, _GXTexObj *, unsigned char);
void GXSetTexCoordGen(void);

#endif // _PPP_YMENV_H_
