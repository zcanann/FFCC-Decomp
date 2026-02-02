#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

struct VRain;
struct PRain;
struct RAIN_DATA;

void InitRainData(VRain*, PRain*, RAIN_DATA*);
void UpdateRain(VRain*, PRain*, RAIN_DATA*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructRain(void);
void pppDestructRain(void);
void pppFrameRain(void);
void pppRenderRain(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RAIN_H_
