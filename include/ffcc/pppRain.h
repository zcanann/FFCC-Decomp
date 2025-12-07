#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

struct VRain;
struct PRain;
struct RAIN_DATA;

void InitRainData(VRain*, PRain*, RAIN_DATA*);
void UpdateRain(VRain*, PRain*, RAIN_DATA*);
void pppConstructRain(void);
void pppDestructRain(void);
void pppFrameRain(void);
void pppRenderRain(void);
void GXEnd(void);

#endif // _PPP_RAIN_H_
