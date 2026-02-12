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

static char s_ME_AppRequest_cpp_801d7da8[] = "ME_AppRequest.cpp";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::ResetRsdList(ZLIST* zlist)
{
	_ZLISTITEM* it = zlist->m_root.m_previous;

	while (it != 0) {
		int* listItem = (int*)zlist->GetDataNext(&it);
		int rsdItem = *listItem;

		if (rsdItem != 0) {
			if (*(void**)(rsdItem + 0xc) != 0) {
				__dla__FPv(*(void**)(rsdItem + 0xc));
				*(int*)(rsdItem + 0xc) = 0;
			}
			if (*(void**)(rsdItem + 0x10) != 0) {
				__dla__FPv(*(void**)(rsdItem + 0x10));
				*(int*)(rsdItem + 0x10) = 0;
			}
			if (*(void**)(rsdItem + 0x14) != 0) {
				__dla__FPv(*(void**)(rsdItem + 0x14));
				*(int*)(rsdItem + 0x14) = 0;
			}
			if (*(void**)(rsdItem + 0x18) != 0) {
				__dla__FPv(*(void**)(rsdItem + 0x18));
				*(int*)(rsdItem + 0x18) = 0;
			}
			__dl__FPv((void*)rsdItem);
		}

		unsigned int* colAnmData = (unsigned int*)listItem[1];
		int colAnmCount = listItem[2];
		if (colAnmData != 0) {
			for (int i = 0; i < colAnmCount; i++) {
				if ((void*)*colAnmData != 0) {
					__dla__FPv((void*)*colAnmData);
					*colAnmData = 0;
				}
				colAnmData += 5;
			}
			if ((void*)listItem[1] != 0) {
				__dla__FPv((void*)listItem[1]);
				listItem[1] = 0;
			}
		}
		__dl__FPv(listItem);
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
	CMemory::CStage* stage = *(CMemory::CStage**)(MaterialEditorPcs + 4);
	int* entry = (int*)__nw__FUlPQ27CMemory6CStagePci(0x10, stage, s_ME_AppRequest_cpp_801d7da8, 0x61);
	if (entry == 0) {
		return 0;
	}

	memset(entry, 0, 0x10);
	int rsdItem = (int)__nw__FUlPQ27CMemory6CStagePci(0x1c, stage, s_ME_AppRequest_cpp_801d7da8, 0x67);
	if (rsdItem == 0) {
		__dl__FPv(entry);
		return 0;
	}

	memset((void*)rsdItem, 0, 0x1c);
	entry[0] = rsdItem;
	entry[3] = 1;
	zlist->AddTail(entry);
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
    ZLIST* list = reinterpret_cast<ZLIST*>(reinterpret_cast<char*>(this) + 0xB4);
    int index = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC4);
    int* rsd = reinterpret_cast<int*>(list->GetDataIdx(index));

    if (rsd != nullptr) {
        rsd[3] = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC0);
    }

    return rsd != nullptr;
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
    ZLIST* list = reinterpret_cast<ZLIST*>(reinterpret_cast<char*>(this) + 0xB4);
    int index = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC4);
    int* rsd = reinterpret_cast<int*>(list->GetDataIdx(index));

    if (rsd == nullptr) {
        return 0;
    }
    if (*rsd == 0) {
        return 0;
    }

    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xBC) = *rsd;
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
