#include "ffcc/zlist.h"

#include "ffcc/p_MaterialEditor.h"

extern char lbl_801D7DC0[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
ZLIST::ZLIST()
{
	m_root.m_previous = (_ZLISTITEM*)nullptr;
	m_root.m_next = (_ZLISTITEM*)nullptr;
	m_root.m_data = (void*)nullptr;
	m_count = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
ZLIST::~ZLIST()
{
    _ZLISTITEM* it = m_root.m_previous;

    if (it != (_ZLISTITEM*)nullptr)
    {
        while (it->m_next != (_ZLISTITEM*)nullptr)
        {
            _ZLISTITEM* next = it->m_next;
            delete it;
            it = next;
        }

        m_root.m_previous = (_ZLISTITEM*)nullptr;
        m_root.m_next = (_ZLISTITEM*)nullptr;
        m_count = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ZLIST::DeleteList()
{
    if (m_root.m_previous != (_ZLISTITEM*)nullptr)
    {
        _ZLISTITEM* it = m_root.m_previous;

        while (it->m_next != (_ZLISTITEM*)nullptr)
        {
            _ZLISTITEM* next = it->m_next;
            delete it;
            it = next;
        }

        m_root.m_previous = (_ZLISTITEM*)nullptr;
        m_root.m_next = (_ZLISTITEM*)nullptr;
        m_count = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool ZLIST::AddTail(void* data)
{
	_ZLISTITEM* newItem = new (MaterialEditorPcs.m_stage, lbl_801D7DC0, 0x107) _ZLISTITEM;

	if (newItem != (_ZLISTITEM*)nullptr)
	{
		newItem->m_previous = (_ZLISTITEM*)nullptr;
		newItem->m_next = (_ZLISTITEM*)nullptr;
	}

	if (newItem == (_ZLISTITEM*)nullptr)
	{
		return false;
	}

    if (m_root.m_next == (_ZLISTITEM*)nullptr)
    {
        m_root.m_previous = newItem;
        m_root.m_next = newItem;
    }
    else
    {
        newItem->m_previous = m_root.m_next;
        m_root.m_next->m_next = newItem;
        m_root.m_next = newItem;
    }

    newItem->m_data = data;

    m_count++;

    return true;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* ZLIST::GetDataNext(_ZLISTITEM** it)
{
	if (it == (_ZLISTITEM**)nullptr)
	{
		return (void*)nullptr;
	}

	_ZLISTITEM* state = *it;

	if (state == (_ZLISTITEM*)nullptr)
	{
		return (void*)nullptr;
	}

	*it = state->m_next;

	return state->m_data;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* ZLIST::GetDataIdx(int index)
{
    _ZLISTITEM* it = m_root.m_previous;

    if (it == nullptr)
	{
        return nullptr;
	}

    while (index-- > 0)
    {
        it = it->m_next;

        if (it == nullptr)
		{
            break;
		}
    }

    if (it == nullptr)
	{
        return nullptr;
	}

    return it->m_data;
}
