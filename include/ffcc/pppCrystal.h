#ifndef _FFCC_PPPCRYSTAL_H_
#define _FFCC_PPPCRYSTAL_H_

struct HSD_ImageBuffer;

void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void MakeRefractionMap(HSD_ImageBuffer*);
void pppConstructCrystal(void);
void pppDestructCrystal(void);
void pppFrameCrystal(void);
void pppRenderCrystal(void);
void GXSetTexCoordGen(void);

#endif // _FFCC_PPPCRYSTAL_H_
