#ifndef _FFCC_PPPCRYSTAL2_H_
#define _FFCC_PPPCRYSTAL2_H_

struct HSD_ImageBuffer;

void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void MakeRefractionMap(HSD_ImageBuffer*);

void pppConstructCrystal2(void);
void pppDestructCrystal2(void);
void pppFrameCrystal2(void);
void pppRenderCrystal2(void);

#endif // _FFCC_PPPCRYSTAL2_H_
