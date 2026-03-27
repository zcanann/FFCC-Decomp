#include "ffcc/ME_AppRequest.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"

extern "C" {
void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, const char*, int);
void __dl__FPv(void*);
void __dla__FPv(void*);
void* memset(void*, int, unsigned int);
}

static const char s_ME_AppRequest_cpp_801d7da8[] = "ME_AppRequest.cpp";

struct RSDITEM {
    int unk0;
    int unk4;
    int unk8;
    void* ptrC;
    void* ptr10;
    void* ptr14;
    void* ptr18;
};

struct ZCANMGRP {
    void* ptr;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
};

struct RSDLISTITEM {
    RSDITEM* rsdItem;
    ZCANMGRP* colAnmData;
    int colAnmCount;
    int flag;
};

static inline CMemory::CStage* MaterialEditorStage()
{
    return MaterialEditorPcs.m_stage;
}

/*
 * --INFO--
 * PAL Address: 0x8004dce8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::GetRsdItem()
{
    ZLIST* list = reinterpret_cast<ZLIST*>(reinterpret_cast<char*>(this) + 0xC8);
    int index = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x9C);
    list->GetDataIdx(index);
}

/*
 * --INFO--
 * PAL Address: 0x8004dd10
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialEditorPcs::SetRsdIndex()
{
    ZLIST* list = reinterpret_cast<ZLIST*>(reinterpret_cast<char*>(this) + 0xD8);
    int index = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC4);
    unsigned int* rsd = reinterpret_cast<unsigned int*>(list->GetDataIdx(index));

    if (rsd == nullptr) {
        return 0;
    }
    if (*rsd == 0) {
        return 0;
    }

    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0xBC) = *rsd;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8004dd70
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialEditorPcs::SetRsdFlag()
{
    ZLIST* list = reinterpret_cast<ZLIST*>(reinterpret_cast<char*>(this) + 0xD8);
    int index = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC4);
    int* rsd = reinterpret_cast<int*>(list->GetDataIdx(index));

    if (rsd == 0) {
        return 0;
    }

    rsd[3] = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC0);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8004ddc0
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialEditorPcs::AddRsdList(ZLIST* zlist)
{
    RSDLISTITEM* listItem =
        (RSDLISTITEM*)__nw__FUlPQ27CMemory6CStagePci(0x10, MaterialEditorStage(), s_ME_AppRequest_cpp_801d7da8, 0x61);
    if (listItem == 0) {
        return 0;
    }

    memset(listItem, 0, 0x10);
    RSDITEM* rsdItem =
        (RSDITEM*)__nw__FUlPQ27CMemory6CStagePci(0x1c, MaterialEditorStage(), s_ME_AppRequest_cpp_801d7da8, 0x67);
    if (rsdItem == 0) {
        if (listItem != 0) {
            __dl__FPv(listItem);
        }
        return 0;
    }

    memset(rsdItem, 0, 0x1c);
    listItem->rsdItem = rsdItem;
    listItem->flag = 1;
    zlist->AddTail(listItem);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8004de94
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::ResetRsdList(ZLIST* zlist)
{
    ZLIST* list;
    _ZLISTITEM* it[1];
    RSDITEM* rsdItem;
    int i;
    ZCANMGRP* colAnmData;
    int colAnmCount;
    RSDLISTITEM* listItem;

    list = zlist;
    it[0] = list->m_root.m_previous;
    while (it[0] != (_ZLISTITEM*)0) {
        listItem = (RSDLISTITEM*)list->GetDataNext(it);
        rsdItem = listItem->rsdItem;
        if (rsdItem != (RSDITEM*)0) {
            if (rsdItem->ptrC != (void*)0) {
                __dla__FPv(rsdItem->ptrC);
                rsdItem->ptrC = 0;
            }
            if (rsdItem->ptr10 != (void*)0) {
                __dla__FPv(rsdItem->ptr10);
                rsdItem->ptr10 = 0;
            }
            if (rsdItem->ptr14 != (void*)0) {
                __dla__FPv(rsdItem->ptr14);
                rsdItem->ptr14 = 0;
            }
            if (rsdItem->ptr18 != (void*)0) {
                __dla__FPv(rsdItem->ptr18);
                rsdItem->ptr18 = 0;
            }
            if (rsdItem != (RSDITEM*)0) {
                __dl__FPv(rsdItem);
            }
        }
        colAnmCount = listItem->colAnmCount;
        colAnmData = listItem->colAnmData;
        if (colAnmData != (ZCANMGRP*)0) {
            i = 0;
            while (i < colAnmCount) {
                if (colAnmData->ptr != (void*)0) {
                    __dla__FPv(colAnmData->ptr);
                    colAnmData->ptr = 0;
                }
                colAnmData = colAnmData + 1;
                i = i + 1;
            }
            if (listItem->colAnmData != (ZCANMGRP*)0) {
                __dla__FPv(listItem->colAnmData);
                listItem->colAnmData = 0;
            }
            listItem->colAnmData = 0;
        }
        __dl__FPv(listItem);
    }
    list->DeleteList();
}
