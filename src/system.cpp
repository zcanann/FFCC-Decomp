#include "ffcc/system.h"

#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSystem::CSystem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::Quit()
{
	if (m_mapBuffer != nullptr)
	{
		delete[]m_mapBuffer;
		m_mapBuffer = nullptr;
	}
	
	if (m_mapStage != (CStage*)0x0)
	{
		// DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,m_mapStage);
	}
	
	/*
	Quit__14CMemoryCardManFv(&MemoryCardMan);
	Quit__8CFontManFv(&FontMan);
	Quit__11CTextureManFv(&TextureMan);
	Quit__12CMaterialManFv(&MaterialMan);
	Quit__8CGraphicFv(&Graphic);
	Quit__4CPadFv(&Pad);
	Quit__5CFileFv(&File);
	Quit__6CSoundFv(&Sound);
	Quit__7CMemoryFv(&Memory);
	Quit__5CMathFv(&Math);
	*/
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::Printf(char* fmt, ...)
{
    if (((int)this /* MiniGamePcs._25732_4_ */ &  0x1000) == 0)
	{
        return;
	}

    char buffer[0x20C];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    OSReport(buffer);
    // USB.Printf(buffer);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::ExecScenegraph()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CSystem::AddScenegraph(CProcess* process, int arg)
{
    int insertIndex = 0;
    u32* description = (u32*)this; // process->GetScenegraphBlock(arg));
    u32* entry = description + 7;
	
    if (__ptmf_test((__ptmf*)(description + 1)))
	{
        __ptmf_scall(process);
	}

    while (true)
    {
        if (__ptmf_test((__ptmf*)entry) == 0)
		{
            return 1;
		}

        COrder* sentinel = &m_orderSentinel;
        COrder* current = sentinel->m_next;

        while (true)
        {
            if (entry[3] < current->m_priority)
            {
                COrder* order = m_freeOrderHead.m_next;
                m_freeOrderHead.m_next = order->m_next;
                order->m_next = current;
                order->m_previous = current->m_previous;
                current->m_previous->m_next = order;
                current->m_previous = order;
                order->m_entry = entry;
                order->m_insertIndex = insertIndex++;
                order->m_descBlock = description;
                order->m_owner = process;
                order->m_priority = entry[3];
                order->m_debugName = (void*)description[0];
                m_orderCount++;
				
                break;
            }

            current = current->m_next;
			
            if (current == sentinel)
			{
                break;
			}
        }

        entry += 5;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::RemoveScenegraph(CProcess* process, int arg)
{
    void* descBlock = (void*)this; // proc->GetScenegraphBlock(arg);
    COrder* order = m_orderSentinel.m_next;
	
    while (order != &m_orderSentinel)
    {
        COrder* next = order->m_next;

        if (order->m_descBlock == descBlock)
        {
            order->m_previous->m_next = order->m_next;
            order->m_next->m_previous = order->m_previous;
            order->m_next = m_freeOrderHead.m_next;
            m_freeOrderHead.m_next = order;

            m_orderCount--;
        }

        order = next;
    }
	
	// TODO: Obviously wrong
    if (__ptmf_test((__ptmf*)descBlock + 0x10) != 0)
    {
        __ptmf_scall();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::ScriptChanging(char*)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			//(**(code **)((int)*order->m_owner + 0x14))(order->m_owner,param_2);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::ScriptChanged(char*, int)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			//(**(code **)((int)*order->m_owner + 0x18))(order->m_owner,param_2,param_3);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::MapChanging(int, int)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			//(**(code **)((int)*order->m_owner + 0x1c))(order->m_owner,param_2,param_3)
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::MapChanged(int, int, int)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			//(**(code **)((int)*order->m_owner + 0x20))(order->m_owner,param_2,param_3,param_4);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSystem::COrder* CSystem::GetFirstOrder()
{ 
	COrder* order = m_orderSentinel.m_next;
	
	if (order == &m_orderSentinel)
	{
		return (COrder*)nullptr;
	}
	
	return order;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSystem::COrder* CSystem::GetNextOrder(CSystem::COrder* order)
{ 
	if (order->m_next == &m_orderSentinel)
	{
		return (COrder*)0x0;
	}
	
	return order->m_next;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSystem::COrder* CSystem::GetOrder(int index)
{ 
	COrder* nextOrder = (COrder*)nullptr;

	if (index < 0)
	{
		return nextOrder;
	}
	
	nextOrder = (m_orderSentinel).m_next;
	int foundIndex = 0;
	
	while (nextOrder)
	{
		if (foundIndex == index)
		{
			break;
		}
		
		nextOrder = nextOrder->m_next;
		foundIndex++;
	}
	
	return nextOrder;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CSystem::IsGdev()
{
	return OSGetConsoleType() >> 0x1C & 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::DumpMapFile(void*)
{
	// TODO: Where the hell do we get these from?
	// There is very obviously <not> a stopwatch at position 0 in this class. Maybe leftover debug code?
	OSInitStopwatch((OSStopwatch*)this, (char*)nullptr);
	OSResetStopwatch((OSStopwatch*)this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::errorHandler(unsigned short, OSContext*, unsigned long, unsigned long)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void OSPanic(...)
{
	// TODO
}
