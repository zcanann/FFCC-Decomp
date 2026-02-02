#ifndef _FFCC_PPPCHANGEBGCOLOR_H_
#define _FFCC_PPPCHANGEBGCOLOR_H_

struct _GXColor;

// Simplified structure definitions for compilation
struct pppChangeBGColor {
    char padding[0x90];  // Padding to reach field_0x88 area
};

struct UnkB {
    char data[16];
};

struct UnkC {
    char padding1[12];             // Padding to reach offset 0xc
    int* m_serializedDataOffsets;  // Array of offsets at 0xc
    char padding2[16];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConChangeBGColor(void);
void pppDesChangeBGColor(void);
void pppFrameChangeBGColor(struct pppChangeBGColor* pppChangeBGColor, struct UnkB* param_2, struct UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGEBGCOLOR_H_
