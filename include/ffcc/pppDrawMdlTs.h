#ifndef _FFCC_PPPDRAWMDLTS_H_
#define _FFCC_PPPDRAWMDLTS_H_

struct _pppPObject;
struct PDrawMdlTs;
struct _pppCtrlTable;

void pppDrawMdlTsCon(struct _pppPObject* obj, struct PDrawMdlTs* data);
void pppDrawMdlTsCon3(struct _pppPObject* obj, struct PDrawMdlTs* data);
void pppDrawMdlTs(void);
void pppDrawDrawMdlTs0(struct _pppPObject*, struct PDrawMdlTs*, struct _pppCtrlTable*);
void pppDrawDrawMdlTs(void);

#endif // _FFCC_PPPDRAWMDLTS_H_
