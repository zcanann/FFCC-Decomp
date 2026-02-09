#include "ffcc/system.h"

#include "ffcc/file.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/memorycard.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/textureman.h"

#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"
#include <string.h>

extern CMath Math;
extern CTextureMan TextureMan;
extern CMaterialMan MaterialMan;
extern CFontMan FontMan;

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
 * PAL Address: 0x80022080
 * PAL Size: 856b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSystem::Init()
{
    m_initialized = 1;
    m_currentOrder = (COrder*)0;
    m_currentOrderIndex = 0;

    OSInit();

    m_execParam = 3;
    Memory.Init();
    Sound.Init();
    Math.Init();
    File.Init();
    Pad.Init();
    Graphic.Init();
    TextureMan.Init();
    MaterialMan.Init();
    FontMan.Init();
    MemoryCardMan.Init();

    m_orderCount = 0;
    m_orderSentinel.m_priority = 0xFF;
    m_orderSentinel.m_next = &m_orderSentinel;
    m_orderSentinel.m_previous = &m_orderSentinel;
    m_freeOrderHead.m_next = &m_orderPool[0];
    for (int i = 0; i < 128; i++)
    {
        if (i == 127)
        {
            m_orderPool[i].m_next = &m_freeOrderHead;
        }
        else
        {
            m_orderPool[i].m_next = &m_orderPool[i + 1];
        }
    }

    m_ownerThread = OSGetCurrentThread();
    m_scenegraphStepMode = 0;
    m_frameCounter = 0;
    m_mapStage = (CStage*)0;
    m_mapBuffer = (void*)0;
    m_mapSize = 0;

    OSErrorHandler handler = (OSErrorHandler)errorHandler;
    OSSetErrorHandler(0, handler);
    OSSetErrorHandler(1, handler);
    OSSetErrorHandler(2, handler);
    OSSetErrorHandler(3, handler);
    OSSetErrorHandler(5, handler);
    OSSetErrorHandler(0xb, handler);
    OSSetErrorHandler(0xd, handler);
    OSSetErrorHandler(0xe, handler);
    OSSetErrorHandler(0xf, handler);

    if (OSGetConsoleSimulatedMemSize() == 0x3000000)
    {
        m_mapStage = (CStage*)Memory.CreateStage(0x400000, (char*)"CSystem", 1);
        CFile::CHandle* fileHandle = File.Open((char*)"gamePalM.map", 0, CFile::PRI_LOW);
        if (fileHandle != (CFile::CHandle*)0)
        {
            m_mapSize = File.GetLength(fileHandle);
            m_mapBuffer = new unsigned char[m_mapSize];
            if (m_mapBuffer != (void*)0)
            {
                unsigned int offset = 0;
                for (unsigned int remaining = m_mapSize; remaining != 0;)
                {
                    unsigned int chunkSize = 0x100000;
                    if (remaining < chunkSize)
                    {
                        chunkSize = remaining;
                    }

                    fileHandle->m_length = chunkSize;
                    fileHandle->m_currentOffset = offset;
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    memcpy((unsigned char*)m_mapBuffer + offset, File.m_readBuffer, chunkSize);

                    offset += chunkSize;
                    remaining -= chunkSize;
                }
            }
            File.Close(fileHandle);
            Printf((char*)"%s", (char*)"");
        }
    }
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
    typedef void* (*GetScenegraphBlockFn)(CProcess*, int);
    GetScenegraphBlockFn getScenegraphBlock = *(GetScenegraphBlockFn*)((u8*)*(void**)process + 0x10);
    int insertIndex = 0;
    u32* description = (u32*)getScenegraphBlock(process, arg);
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
    typedef void* (*GetScenegraphBlockFn)(CProcess*, int);
    GetScenegraphBlockFn getScenegraphBlock = *(GetScenegraphBlockFn*)((u8*)*(void**)process + 0x10);
    void* descBlock = getScenegraphBlock(process, arg);
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
	
    if (__ptmf_test((__ptmf*)((u8*)descBlock + 0x10)) != 0)
    {
        __ptmf_scall(process);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::ScriptChanging(char* script)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			order->m_owner->ScriptChanging(script);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::ScriptChanged(char* script, int value)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			order->m_owner->ScriptChanged(script, value);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::MapChanging(int mapId, int mapVariant)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			order->m_owner->MapChanging(mapId, mapVariant);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::MapChanged(int mapId, int mapVariant, int changedByForce)
{
	for (COrder* order = m_orderSentinel.m_next; order != &m_orderSentinel; order = order->m_next)
	{
		if (order->m_entry == (void*)((int)order->m_descBlock + 0x1c))
		{
			order->m_owner->MapChanged(mapId, mapVariant, changedByForce);
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
 * PAL Address: 0x800b138c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CSystem::GetCounter()
{
	return m_frameCounter;
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
CSystem* CSystem::DumpMapFile(void* name)
{
	// TODO: Where the hell do we get these from?
	// There is very obviously <not> a stopwatch at position 0 in this class. Maybe leftover debug code?
	OSInitStopwatch((OSStopwatch*)this, (char*)name);
	OSResetStopwatch((OSStopwatch*)this);
	return this;
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
 * PAL Address: 0x800223dc
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void OSPanic(const char* file, int line, const char* msg, ...)
{
	// TODO
}
