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
    int* piVar1;
    unsigned int* puVar2;
    int iVar3;
    int iVar4;
    _ZLISTITEM* local_28[4];

    local_28[0] = zlist->m_root.m_previous;
    while (local_28[0] != (_ZLISTITEM*)0) {
        piVar1 = (int*)zlist->GetDataNext(local_28);
        iVar4 = *piVar1;
        if (iVar4 != 0) {
            if (*(void**)(iVar4 + 0xC) != (void*)0) {
                __dla__FPv(*(void**)(iVar4 + 0xC));
                *(unsigned int*)(iVar4 + 0xC) = 0;
            }
            if (*(void**)(iVar4 + 0x10) != (void*)0) {
                __dla__FPv(*(void**)(iVar4 + 0x10));
                *(unsigned int*)(iVar4 + 0x10) = 0;
            }
            if (*(void**)(iVar4 + 0x14) != (void*)0) {
                __dla__FPv(*(void**)(iVar4 + 0x14));
                *(unsigned int*)(iVar4 + 0x14) = 0;
            }
            if (*(void**)(iVar4 + 0x18) != (void*)0) {
                __dla__FPv(*(void**)(iVar4 + 0x18));
                *(unsigned int*)(iVar4 + 0x18) = 0;
            }
            if (iVar4 != 0) {
                __dl__FPv((void*)iVar4);
            }
        }
        puVar2 = (unsigned int*)piVar1[1];
        iVar4 = piVar1[2];
        if (puVar2 != (unsigned int*)0) {
            for (iVar3 = 0; iVar3 < iVar4; iVar3 = iVar3 + 1) {
                if ((void*)*puVar2 != (void*)0) {
                    __dla__FPv((void*)*puVar2);
                    *puVar2 = 0;
                }
                puVar2 = puVar2 + 5;
            }
            if ((void*)piVar1[1] != (void*)0) {
                __dla__FPv((void*)piVar1[1]);
                piVar1[1] = 0;
            }
            piVar1[1] = 0;
        }
        __dl__FPv(piVar1);
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
