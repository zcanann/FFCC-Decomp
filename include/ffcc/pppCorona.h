#ifndef _FFCC_PPPCORONA_H_
#define _FFCC_PPPCORONA_H_

struct _pppPObject;
struct _pppCtrlTable;
struct CoronaParam;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCorona(_pppPObject* object, _pppCtrlTable* ctrl);
void pppDestructCorona(_pppPObject* object, _pppCtrlTable* ctrl);
void pppFrameCorona(_pppPObject* object, CoronaParam* data, _pppCtrlTable* ctrl);
void pppRenderCorona(_pppPObject* object, CoronaParam* data, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCORONA_H_
