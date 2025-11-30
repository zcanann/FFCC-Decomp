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
	if (mMapBuffer != nullptr)
	{
		delete[]mMapBuffer;
		mMapBuffer = nullptr;
	}
	
	if (mMapStage != (CStage *)0x0)
	{
		// DestroyStage__7CMemoryFPQ27CMemory6CStage(&g_memory,mMapStage);
	}
	
	/*
	Quit__14CMemoryCardManFv(&g_memoryCardMan);
	Quit__8CFontManFv(&g_fontMan);
	Quit__11CTextureManFv(&g_textureMan);
	Quit__12CMaterialManFv(&g_materialMan);
	Quit__8CGraphicFv(&g_Graphic);
	Quit__4CPadFv(&g_pad);
	Quit__5CFileFv(&g_file);
	Quit__6CSoundFv(&g_sound);
	Quit__7CMemoryFv(&g_memory);
	Quit__5CMathFv(&g_math);
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

        COrder* sentinel = &mOrderSentinel;
        COrder* current = sentinel->mNext;

        while (true)
        {
            if (entry[3] < current->mPriority)
            {
                COrder* order = mFreeOrderHead.mNext;
                mFreeOrderHead.mNext = order->mNext;
                order->mNext = current;
                order->mPrevious = current->mPrevious;
                current->mPrevious->mNext = order;
                current->mPrevious = order;
                order->mEntry = entry;
                order->mInsertIndex = insertIndex++;
                order->mDescBlock = description;
                order->mOwner = process;
                order->mPriority = entry[3];
                order->mDebugName = (void*)description[0];
                mOrderCount++;
				
                break;
            }

            current = current->mNext;
			
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
    COrder* order = mOrderSentinel.mNext;
	
    while (order != &mOrderSentinel)
    {
        COrder* next = order->mNext;

        if (order->mDescBlock == descBlock)
        {
            order->mPrevious->mNext = order->mNext;
            order->mNext->mPrevious = order->mPrevious;
            order->mNext = mFreeOrderHead.mNext;
            mFreeOrderHead.mNext = order;

            mOrderCount--;
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
void CSystem::ScriptChanging(char *)
{
	for (COrder* order = mOrderSentinel.mNext; order != &mOrderSentinel; order = order->mNext)
	{
		if (order->mEntry == (void *)((int)order->mDescBlock + 0x1c))
		{
			//(**(code **)((int)*order->mOwner + 0x14))(order->mOwner,param_2);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::ScriptChanged(char *, int)
{
	for (COrder* order = mOrderSentinel.mNext; order != &mOrderSentinel; order = order->mNext)
	{
		if (order->mEntry == (void *)((int)order->mDescBlock + 0x1c))
		{
			//(**(code **)((int)*order->mOwner + 0x18))(order->mOwner,param_2,param_3);
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
	for (COrder* order = mOrderSentinel.mNext; order != &mOrderSentinel; order = order->mNext)
	{
		if (order->mEntry == (void *)((int)order->mDescBlock + 0x1c))
		{
			//(**(code **)((int)*order->mOwner + 0x1c))(order->mOwner,param_2,param_3)
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
	for (COrder* order = mOrderSentinel.mNext; order != &mOrderSentinel; order = order->mNext)
	{
		if (order->mEntry == (void *)((int)order->mDescBlock + 0x1c))
		{
			//(**(code **)((int)*order->mOwner + 0x20))(order->mOwner,param_2,param_3,param_4);
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
	COrder* order = mOrderSentinel.mNext;
	
	if (order == &mOrderSentinel)
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
	if (order->mNext == &mOrderSentinel)
	{
		return (COrder*)0x0;
	}
	
	return order->mNext;
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
	
	nextOrder = (mOrderSentinel).mNext;
	int foundIndex = 0;
	
	while (nextOrder)
	{
		if (foundIndex == index)
		{
			break;
		}
		
		nextOrder = nextOrder->mNext;
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
void CSystem::DumpMapFile()
{ 
	// OSInitStopwatch();
	// OSResetStopwatch(();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::errorHandler(unsigned short, OSContext *, unsigned long, unsigned long)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void OSPanic(void)
{
	// TODO
}

