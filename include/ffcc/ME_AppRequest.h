#ifndef _FFCC_ME_APPREQUEST_H_
#define _FFCC_ME_APPREQUEST_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"

struct ZLIST;
struct RSDLISTITEM;
struct ZCANMGRP;

class CMaterialEditorPcs : public CProcess
{
public:
    void ResetRsdList(ZLIST*);
    void DeleteRsdItem(RSDLISTITEM*);
    void DeleteColAnmData(ZCANMGRP**, int);
    int AddRsdList(ZLIST*);
    int SetRsdFlag();
    void GetRsdItemR();
    int SetRsdIndex();
    void GetRsdItem();

    CMemory::CStage* m_stage; // 0x04
};

#endif // _FFCC_ME_APPREQUEST_H_
