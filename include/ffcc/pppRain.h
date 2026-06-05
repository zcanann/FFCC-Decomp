#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppRain;
typedef _pppCtrlTable RAIN_DATA;

struct PRain;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructRain(pppRain*, RAIN_DATA*);
void pppDestructRain(pppRain*, RAIN_DATA*);
void pppFrameRain(pppRain*, PRain*, RAIN_DATA*);
void pppRenderRain(pppRain*, PRain*, RAIN_DATA*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RAIN_H_
