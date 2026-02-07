#ifndef _FFCC_ME_APPREQUEST_H_
#define _FFCC_ME_APPREQUEST_H_

struct ZLIST;
struct RSDLISTITEM;
struct ZCANMGRP;

class CMaterialEditorPcs
{
public:
    void ResetRsdList(ZLIST*);
    void DeleteRsdItem(RSDLISTITEM*);
    void DeleteColAnmData(ZCANMGRP**, int);
    void AddRsdList(ZLIST*);
    void SetRsdFlag();
    void GetRsdItemR();
    int SetRsdIndex();
    void GetRsdItem();
};

#endif // _FFCC_ME_APPREQUEST_H_
