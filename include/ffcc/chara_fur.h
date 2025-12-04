#ifndef _FFCC_CGCHARAOBJ_H_
#define _FFCC_CGCHARAOBJ_H_

#include "ffcc/charaobj.h"
#include "ffcc/color.h"

#include <dolphin/gx.h>

class CGObject;
class CGPrgObj;
class CGPartyObj;
class CCombi2Set;
class CCombi2;
class PPPIFPARAM;
class CFont;
class CGObjWork;
struct Vec;
class CFlatRuntime2;

void la(CGObject *);
void SAFE_CAST_WORK(CGObjWork *);

class CHairSet
{
public:
    CHairSet();
};

#endif // _FFCC_CGCHARAOBJ_H_
