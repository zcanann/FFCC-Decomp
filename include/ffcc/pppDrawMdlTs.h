#ifndef _FFCC_PPPDRAWMDLTS_H_
#define _FFCC_PPPDRAWMDLTS_H_

struct _pppPObject;
struct PDrawMdlTs;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawMdlTsCon(struct _pppPObject* obj, struct PDrawMdlTs* data);
void pppDrawMdlTsCon3(struct _pppPObject* obj, struct PDrawMdlTs* data);
void pppDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct PDrawMdlTs* param);
void pppDrawDrawMdlTs0(struct _pppPObject*, struct PDrawMdlTs*, struct _pppCtrlTable*);
void pppDrawDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWMDLTS_H_
