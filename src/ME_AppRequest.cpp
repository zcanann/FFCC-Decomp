#include "ffcc/ME_AppRequest.h"
#include "ffcc/zlist.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::ResetRsdList(ZLIST*)
{
	// TODO
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
void CMaterialEditorPcs::AddRsdList(ZLIST*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::SetRsdFlag()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::GetRsdItem()
{
	// TODO
}
