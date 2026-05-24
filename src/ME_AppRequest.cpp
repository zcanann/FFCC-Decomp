#include "ffcc/ME_AppRequest.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"

extern "C" {
void* memset(void*, int, unsigned int);
}

extern const char s_ME_AppRequest_cpp[] = "ME_AppRequest.cpp";

struct ZCANMGRP {
    u8* ptr;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
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
RSDLISTITEM* CMaterialEditorPcs::GetRsdItem()
{
    return reinterpret_cast<RSDLISTITEM*>(m_zlist1.GetDataIdx(reinterpret_cast<int>(m_usbStream.m_stageLoad)));
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
RSDITEM* CMaterialEditorPcs::GetReadRsd()
{
    return reinterpret_cast<RSDLISTITEM*>(m_zlist1.GetDataIdx(reinterpret_cast<int>(m_usbStream.m_stageLoad)))->rsdItem;
}
#endif

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
    unsigned int* rsd = reinterpret_cast<unsigned int*>(m_zlist2.GetDataIdx(m_rsdListIndex));

    if (rsd == nullptr) {
        return 0;
    }
    if (*rsd == 0) {
        return 0;
    }

    m_rsdIndex = *rsd;
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
    int* rsd = reinterpret_cast<int*>(m_zlist2.GetDataIdx(m_rsdListIndex));

    if (rsd == 0) {
        return 0;
    }

    rsd[3] = m_rsdFlag;
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
        new (MaterialEditorStage(), const_cast<char*>(s_ME_AppRequest_cpp), 0x61) RSDLISTITEM;
    if (listItem == 0) {
        return 0;
    }

    memset(listItem, 0, 0x10);
    RSDITEM* rsdItem =
        new (MaterialEditorStage(), const_cast<char*>(s_ME_AppRequest_cpp), 0x67) RSDITEM;
    if (rsdItem == 0) {
        if (listItem != 0) {
            delete listItem;
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
 * PAL Address: UNUSED
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void CMaterialEditorPcs::DeleteColAnmData(ZCANMGRP** colAnmData, int colAnmCount)
{
    ZCANMGRP* entry = *colAnmData;

    if (entry != (ZCANMGRP*)0) {
        int i = 0;
        while (i < colAnmCount) {
            if (entry->ptr != (u8*)0) {
                delete[] entry->ptr;
                entry->ptr = (u8*)0;
            }
            entry = entry + 1;
            i = i + 1;
        }
        delete[] reinterpret_cast<u8*>(*colAnmData);
        *colAnmData = (ZCANMGRP*)0;
    }
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void CMaterialEditorPcs::DeleteRsdItem(RSDLISTITEM* listItem)
{
    RSDITEM* rsdItem = listItem->rsdItem;

    if (rsdItem != (RSDITEM*)0) {
        if (rsdItem->ptrC != (void*)0) {
            delete[] static_cast<u8*>(rsdItem->ptrC);
            rsdItem->ptrC = 0;
        }
        if (rsdItem->ptr10 != (void*)0) {
            delete[] static_cast<u8*>(rsdItem->ptr10);
            rsdItem->ptr10 = 0;
        }
        if (rsdItem->ptr14 != (void*)0) {
            delete[] static_cast<u8*>(rsdItem->ptr14);
            rsdItem->ptr14 = 0;
        }
        if (rsdItem->ptr18 != (void*)0) {
            delete[] static_cast<u8*>(rsdItem->ptr18);
            rsdItem->ptr18 = 0;
        }
        delete rsdItem;
        listItem->rsdItem = (RSDITEM*)0;
    }

    DeleteColAnmData(&listItem->colAnmData, listItem->colAnmCount);
    delete listItem;
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
RSDLISTITEM* CMaterialEditorPcs::GetRsdItemR()
{
    return reinterpret_cast<RSDLISTITEM*>(m_zlist2.GetDataIdx(m_rsdListIndex));
}
#endif

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
                delete[] static_cast<u8*>(rsdItem->ptrC);
                rsdItem->ptrC = 0;
            }
            if (rsdItem->ptr10 != (void*)0) {
                delete[] static_cast<u8*>(rsdItem->ptr10);
                rsdItem->ptr10 = 0;
            }
            if (rsdItem->ptr14 != (void*)0) {
                delete[] static_cast<u8*>(rsdItem->ptr14);
                rsdItem->ptr14 = 0;
            }
            if (rsdItem->ptr18 != (void*)0) {
                delete[] static_cast<u8*>(rsdItem->ptr18);
                rsdItem->ptr18 = 0;
            }
            if (rsdItem != (RSDITEM*)0) {
                delete rsdItem;
            }
        }
        colAnmCount = listItem->colAnmCount;
        colAnmData = listItem->colAnmData;
        if (colAnmData != (ZCANMGRP*)0) {
            for (i = 0; i < colAnmCount; colAnmData++, i++) {
                if (colAnmData->ptr != (u8*)0) {
                    delete[] colAnmData->ptr;
                    colAnmData->ptr = (u8*)0;
                }
            }
            if (listItem->colAnmData != (ZCANMGRP*)0) {
                delete[] reinterpret_cast<u8*>(listItem->colAnmData);
                listItem->colAnmData = (ZCANMGRP*)0;
            }
            listItem->colAnmData = (ZCANMGRP*)0;
        }
        delete listItem;
    }
    list->DeleteList();
}
