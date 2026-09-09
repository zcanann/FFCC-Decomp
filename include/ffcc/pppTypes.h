#ifndef _FFCC_PPP_TYPES_H_
#define _FFCC_PPP_TYPES_H_

#include <Dolphin/mtx.h>

struct pppCVECTOR
{
    unsigned char rgba[4];
};

struct pppFMATRIX
{
    Mtx value;
};

#endif // _FFCC_PPP_TYPES_H_
