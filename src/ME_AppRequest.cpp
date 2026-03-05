#include "ffcc/ME_AppRequest.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"

extern "C" {
void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void __dl__FPv(void*);
void __dla__FPv(void*);
void* memset(void*, int, unsigned int);
}

extern unsigned char MaterialEditorPcs[];

static char lbl_801D7DA8[] = "ME_AppRequest.cpp";

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
    _ZLISTITEM* local_28[4];

    local_28[0] = zlist->m_root.m_previous;
    while (local_28[0] != (_ZLISTITEM*)0) {
        RSDLISTITEM* rsdListItem = (RSDLISTITEM*)zlist->GetDataNext(local_28);
        RSDITEM* rsdItem = rsdListItem->rsdItem;
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
        ZCANMGRP* colAnmData = rsdListItem->colAnmData;
        int colAnmCount = rsdListItem->colAnmCount;
        if (colAnmData != (ZCANMGRP*)0) {
            for (int i = 0; i < colAnmCount; i++) {
                if (colAnmData->ptr != (void*)0) {
                    __dla__FPv(colAnmData->ptr);
                    colAnmData->ptr = 0;
                }
                colAnmData = colAnmData + 1;
            }
            if (rsdListItem->colAnmData != (ZCANMGRP*)0) {
                __dla__FPv(rsdListItem->colAnmData);
                rsdListItem->colAnmData = 0;
            }
            rsdListItem->colAnmData = 0;
        }
        __dl__FPv(rsdListItem);
    }
    zlist->DeleteList();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::DeleteRsdItem(RSDLISTITEM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::DeleteColAnmData(ZCANMGRP **, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMaterialEditorPcs::AddRsdList(ZLIST* zlist)
{
    int* tail = (int*)__nw__FUlPQ27CMemory6CStagePci(0x10, *(CMemory::CStage**)(MaterialEditorPcs + 4),
                                                     lbl_801D7DA8, 0x61);
    if (tail == 0) {
        return 0;
    }

    memset(tail, 0, 0x10);
    int rsdItem = (int)__nw__FUlPQ27CMemory6CStagePci(0x1c, *(CMemory::CStage**)(MaterialEditorPcs + 4),
                                                      lbl_801D7DA8, 0x67);
    if (rsdItem == 0) {
        if (tail != 0) {
            __dl__FPv(tail);
        }
        return 0;
    }

    memset((void*)rsdItem, 0, 0x1c);
    *tail = rsdItem;
    tail[3] = 1;
    zlist->AddTail(tail);
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::GetRsdItemR()
{
	// TODO
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
