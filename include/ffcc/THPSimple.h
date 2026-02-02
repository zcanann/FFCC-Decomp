#ifndef _FFCC_PPP_THPSIMPLE_H_
#define _FFCC_PPP_THPSIMPLE_H_

struct DVDFileInfo;

void checkError();
void _kami_DVDREAD(DVDFileInfo*, void*, long, long);
void THPSimpleInit(void);
void THPSimpleQuit(void);
void THPSimpleOpen(void);
void THPSimpleClose(void);
void THPSimpleCalcNeedMemory(void);
void THPSimpleSetBuffer(void);
void ReadFrameAsync();
void __THPSimpleDVDCallback(long, DVDFileInfo*);
void THPSimplePreLoad(void);
void THPSimpleAudioStart(void);
void THPSimpleAudioStop(void);
void THPSimpleLoadStop(void);
void THPSimpleDecode(void);
void CheckPrefetch();
void VideoDecode(unsigned char*);
int THPSimpleDrawCurrentFrame(int param_1, short param_2, short param_3, short param_4, short param_5);
void MixAudio(short*, short*, unsigned long);
void THPAudioMixCallback();

#endif // _FFCC_PPP_THPSIMPLE_H_
