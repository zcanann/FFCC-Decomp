#include "ffcc/zlist.h"

#include "ffcc/p_MaterialEditor.h"

static const char s_zlist_cpp[] = "zlist.cpp";

/*
 * --INFO--
 * PAL Address: 0x8004DFD0
 * PAL Size: 72b
 * EN Address: 0x8004DDC4
 * EN Size: 72b
 * JP Address: 0x8004D82C
 * JP Size: 72b
 */
void* ZLIST::GetDataIdx(int index)
{
    _ZLISTITEM* it = m_root.m_previous;

    if (it == nullptr)
    {
        it = (_ZLISTITEM*)nullptr;
    }
    else
    {
        while (index-- > 0)
        {
            it = it->m_next;

            if (it == nullptr)
            {
                break;
            }
        }
    }

    if (it == nullptr)
    {
        return nullptr;
    }

    return it->m_data;
}

/*
 * --INFO--
 * PAL Address: 0x8004E018
 * PAL Size: 52b
 * EN Address: 0x8004DE0C
 * EN Size: 52b
 * JP Address: 0x8004D874
 * JP Size: 52b
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
 * PAL Address: 0x8004E04C
 * PAL Size: 188b
 * EN Address: 0x8004DE40
 * EN Size: 188b
 * JP Address: 0x8004D8A8
 * JP Size: 188b
 */
bool ZLIST::AddTail(void* data)
{
	_ZLISTITEM* newItem = new (MaterialEditorPcs.m_stage, const_cast<char*>(s_zlist_cpp), 0x107) _ZLISTITEM;

	if (newItem == (_ZLISTITEM*)nullptr)
	{
		newItem = (_ZLISTITEM*)nullptr;
	}
	else
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
 * PAL Address: 0x8004E108
 * PAL Size: 104b
 * EN Address: 0x8004DEFC
 * EN Size: 104b
 * JP Address: 0x8004D964
 * JP Size: 104b
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
 * PAL Address: 0x8004E170
 * PAL Size: 136b
 * EN Address: 0x8004DF64
 * EN Size: 136b
 * JP Address: 0x8004D9CC
 * JP Size: 136b
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
 * PAL Address: 0x8004E1F8
 * PAL Size: 24b
 * EN Address: 0x8004DFEC
 * EN Size: 24b
 * JP Address: 0x8004DA54
 * JP Size: 24b
 */
ZLIST::ZLIST()
{
	m_root.m_previous = (_ZLISTITEM*)nullptr;
	m_root.m_next = (_ZLISTITEM*)nullptr;
	m_root.m_data = (void*)nullptr;
	m_count = 0;
}
