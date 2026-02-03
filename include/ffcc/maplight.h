#ifndef _FFCC_MAPLIGHTHOLDER_H_
#define _FFCC_MAPLIGHTHOLDER_H_

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

class CMapLightHolder
{
public:
    void GetLightHolder(_GXColor*, Vec*);

private:
    _GXColor mColor;
    Vec mVec;
};

#endif // _FFCC_MAPLIGHTHOLDER_H_
