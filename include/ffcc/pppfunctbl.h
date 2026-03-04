#ifndef _FFCC_FUNCTBL_H_
#define _FFCC_FUNCTBL_H_

#include "ffcc/partMng.h"

struct _pppSysProgTbl
{
    pppProg* m_progs;
};

extern _pppSysProgTbl pppSysProgTbl;

static inline pppProg* pppGetSysProgTable()
{
    return pppSysProgTbl.m_progs;
}

#endif // _FFCC_FUNCTBL_H_
