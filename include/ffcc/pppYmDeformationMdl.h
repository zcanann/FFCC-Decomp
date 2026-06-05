#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmDeformationMdlUnkB;

typedef _pppPObject pppYmDeformationMdl;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppDestructYmDeformationMdl(pppYmDeformationMdl*, _pppCtrlTable*);
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, _pppCtrlTable* param_3);
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_
