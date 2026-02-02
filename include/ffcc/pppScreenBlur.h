#ifndef _PPP_SCREENBLUR_H_
#define _PPP_SCREENBLUR_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBlur(void* param1, void* param2);
void pppCon2ScreenBlur(void);
void pppDesScreenBlur(void);
void pppFrameScreenBlur(void);
void pppRenderScreenBlur(void* param1, void* param2, void* param3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBLUR_H_
