#ifndef _PPP_ERASECHARAPARTS_H_
#define _PPP_ERASECHARAPARTS_H_

class CChara;

void EraseCharaParts_DrawMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void pppConstructEraseCharaParts(void);
void pppDestructEraseCharaParts(void);
void pppFrameEraseCharaParts(void);

#endif // _PPP_ERASECHARAPARTS_H_
