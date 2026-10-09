#ifndef _FFCC_MAPLIGHTHOLDER_H_
#define _FFCC_MAPLIGHTHOLDER_H_

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

template <class T>
class CPtrArray;

class CMapLightHolder
{
public:
    enum TYPE
    {
        TYPE_CHARA = 0,
    };

    void GetLightHolder(_GXColor*, Vec*);

private:
    _GXColor mColor;
    Vec mVec;
};

typedef CPtrArray<CMapLightHolder*> CMapLightHolderArray;

#endif // _FFCC_MAPLIGHTHOLDER_H_
