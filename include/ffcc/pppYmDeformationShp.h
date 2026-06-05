#ifndef _PPP_YMDEFORMATIONSHP_H_
#define _PPP_YMDEFORMATIONSHP_H_

struct _pppCtrlTable;
struct _pppPObject;
struct pppYmDeformationShpUnkB;

typedef _pppPObject pppYmDeformationShp;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*);
void pppConstruct2YmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*);
void pppDestructYmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*);
void pppFrameYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkB*, _pppCtrlTable*);
void pppRenderYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSHP_H_
