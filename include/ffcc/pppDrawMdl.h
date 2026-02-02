#ifndef _FFCC_PPPDRAWMDL_H_
#define _FFCC_PPPDRAWMDL_H_

struct _pppPObject;
struct PDrawMdl;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMdl0(struct _pppPObject*, struct PDrawMdl*, struct _pppCtrlTable*);
void pppDrawMdl(struct _pppPObject*, struct PDrawMdl*, struct _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMDL_H_
