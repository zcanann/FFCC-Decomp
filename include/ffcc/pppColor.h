#ifndef _FFCC_PPPCOLOR_H_
#define _FFCC_PPPCOLOR_H_

struct _pppColor
{
    unsigned char r;  // 0x0
    unsigned char g;  // 0x1
    unsigned char b;  // 0x2
    unsigned char a;  // 0x3
}; // Size 0x4

struct _pppColorWork
{
    short r;  // 0x0
    short g;  // 0x2
    short b;  // 0x4
    short a;  // 0x6
    _pppColor result; // 0x8
}; // Size 0xC

// External data references used by pppColor
extern int lbl_8032ED70;
extern float lbl_8032ED50;
extern double lbl_8032FED0;

void pppColor(void* param1, void* param2, void* param3);
void pppColorCon(void* param1, void* param2);

#endif // _FFCC_PPPCOLOR_H_
