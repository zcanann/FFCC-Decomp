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
#include "ffcc/stopwatch.h"
#include "ffcc/gbaque.h"
#include "ffcc/textureman.h"
#include "ffcc/usb.h"

#include "dolphin/gx/GXPerf.h"
#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"
#include "ffcc/p_game.h"
#include "ffcc/p_minigame.h"
#include <string.h>

extern CMath Math;
extern CTextureMan TextureMan;
extern CMaterialMan MaterialMan;
extern CFontMan FontMan;
extern "C" int __cntlzw(unsigned int);
extern CMiniGamePcs MiniGamePcs;
extern unsigned char CFlat[];
extern void* __vt__7CSystem[];
CSystem System;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CSystem::CSystem()
{
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
 * PAL Address: 0x80021fb4
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSystem::Quit()
{
    if (m_mapBuffer != nullptr)
    {
        delete[](unsigned char*)m_mapBuffer;
        m_mapBuffer = nullptr;
    }

    if (m_mapStage != nullptr)
    {
        Memory.DestroyStage((CMemory::CStage*)m_mapStage);
    }

    MemoryCardMan.Quit();
    FontMan.Quit();
    TextureMan.Quit();
    MaterialMan.Quit();
    Graphic.Quit();
    Pad.Quit();
    File.Quit();
    Sound.Quit();
    Memory.Quit();
    Math.Quit();
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
    USB.Printf(buffer);
}

/*
 * --INFO--
 * PAL Address: 0x80021934
 * PAL Size: 1480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSystem::ExecScenegraph()
{
    unsigned short stepTrigger = 0;
    unsigned short perfTrigger = 0;
    CStopWatch watch((char*)-1);

    if (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != Game.game.m_gameWork.m_gamePaused)
    {
        Graphic._WaitDrawDone((char*)"system.cpp", 0x219);
        Game.game.m_gameWork.m_gamePaused = Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag;
        if (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0)
        {
            Sound.PauseAllSe(1);
            File.BackAllFilesToQueue((CFile::CHandle*)0);
        }
        else
        {
            Sound.PauseAllSe(0);
        }
    }

    Pad.Frame();
    File.Frame();
    Memory.Frame();

    if (Pad._452_4_ == 0)
    {
        unsigned int stepPad = (Pad._448_4_ == 4) ? 4 : 0;
        stepTrigger = *(unsigned short*)((unsigned char*)&Pad + 0x36 + stepPad * 0x54);
        perfTrigger = *(unsigned short*)((unsigned char*)&Pad + 0x34 + stepPad * 0x54);
    }

    if ((stepTrigger & 0xC) != 0)
    {
        if ((stepTrigger & 8) != 0)
        {
            m_scenegraphStepMode = (unsigned int)__cntlzw((unsigned int)m_scenegraphStepMode) >> 5;
        }
        else if ((stepTrigger & 4) != 0)
        {
            if (m_scenegraphStepMode == 2)
            {
                m_scenegraphStepMode = 3;
            }
            else if (m_scenegraphStepMode == 3)
            {
                m_scenegraphStepMode = 4;
            }
            else if (m_scenegraphStepMode == 4)
            {
                m_scenegraphStepMode = 5;
            }
            else
            {
                m_scenegraphStepMode = 2;
            }
        }
    }

    if (((*(unsigned int*)((unsigned char*)&MiniGamePcs + 0x6484) & 0x40) != 0) &&
        (Game.game.m_gameWork.m_gamePaused == 0))
    {
        for (unsigned int port = 0; port < 4; port++)
        {
            unsigned short trigger;
            if ((Pad._452_4_ != 0) || ((port == 0) && (Pad._448_4_ != -1)))
            {
                trigger = 0;
            }
            else
            {
                unsigned int padIndex = (Pad._448_4_ == (int)port) ? 0 : port;
                trigger = *(unsigned short*)((unsigned char*)&Pad + 0xA + padIndex * 0x54);
            }

            unsigned short held;
            if ((Pad._452_4_ != 0) || ((port == 0) && (Pad._448_4_ != -1)))
            {
                held = 0;
            }
            else
            {
                unsigned int padIndex = (Pad._448_4_ == (int)port) ? 0 : port;
                held = *(unsigned short*)((unsigned char*)&Pad + 0x8 + padIndex * 0x54);
            }

            if (((trigger | held) & 0x1000) != 0)
            {
                if (m_scenegraphStepMode == 2)
                {
                    Sound.PauseAllSe(0);
                    m_scenegraphStepMode = 0;
                    GbaQue.ClrShopMode();
                    GbaQue.SetPauseMode(0);
                }
                else if ((*(unsigned int*)(CFlat + 0x12A0) & 0x10) != 0)
                {
                    Sound.PauseAllSe(1);
                    m_scenegraphStepMode = 2;
                    GbaQue.SetPauseMode(1);
                }
            }
        }
    }

    unsigned int drawToggle;
    if (m_scenegraphStepMode == 1)
    {
        drawToggle = ((unsigned int)__cntlzw(m_frameCounter & 3) >> 5) & 0xFF;
    }
    else
    {
        drawToggle = 1;
    }

    unsigned int stepGate = 0;
    if (m_scenegraphStepMode == 4)
    {
        stepGate = ((-(int)(m_frameCounter & 3)) >> 31);
    }
    else if (m_scenegraphStepMode < 4)
    {
        if (m_scenegraphStepMode == 2)
        {
            stepGate = 1;
        }
        else if (m_scenegraphStepMode > 2)
        {
            stepGate = ((-(int)(m_frameCounter & 7)) >> 31);
        }
    }
    else if (m_scenegraphStepMode < 6)
    {
        stepGate = m_frameCounter & 1;
    }

    int index = 0;
    for (COrder* order = m_orderSentinel.m_next;
         order != &m_orderSentinel;
         order = order->m_next, index++)
    {
        m_currentOrder = order;
        m_currentOrderIndex = index;

        unsigned int flags = *(unsigned int*)((unsigned char*)order->m_entry + 0x10);
        unsigned int skip;
        if ((flags & 1) == 0)
        {
            skip = stepGate;
            if ((stepGate != 0) && (drawToggle != 0) && ((flags & 4) != 0))
            {
                skip = 0;
            }
        }
        else
        {
            skip = (drawToggle == 0);
        }

        if (Game.game.m_gameWork.m_gamePaused == 0)
        {
            if ((flags & 0x10) != 0)
            {
                skip = 1;
            }
        }
        else
        {
            if ((flags & 8) == 0)
            {
                skip = 1;
            }
            if ((flags & 0x10) != 0)
            {
                skip = 0;
            }
        }

        if (skip == 0)
        {
            watch.Reset();
            watch.Start();
            if ((flags & 1) != 0)
            {
                Graphic.SetDrawDoneDebugData(-1);
            }
            __ptmf_scall(order->m_owner);
            watch.Stop();
            order->m_lastTime = watch.Get();

            watch.Start();
            if ((perfTrigger & 1) != 0)
            {
                Graphic._WaitDrawDone((char*)"system.cpp", 0x2CA);
                GXReadGP0Metric();
                GXReadGP1Metric();
            }
            watch.Stop();
            if ((perfTrigger & 1) != 0)
            {
                order->m_lastTime = watch.Get();
            }
            watch.Get();
        }
        else
        {
            order->m_lastTime = 0.0f;
        }
    }

    m_currentOrder = (COrder*)0;
    m_frameCounter++;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CSystem::AddScenegraph(CProcess* process, int arg)
{
    typedef void* (*GetScenegraphBlockFn)(CProcess*, int);
    u32* description = (u32*)(*(GetScenegraphBlockFn*)((u8*)*(void**)process + 0x10))(process, arg);

    if (__ptmf_test((__ptmf*)(description + 1)) != 0)
    {
        __ptmf_scall(process);
    }

    u32* entry = description + 7;
    int insertIndex = 0;
    if (__ptmf_test((__ptmf*)entry) == 0)
    {
        return 1;
    }
    do
    {
        COrder* first = m_orderSentinel.m_next;
        COrder* current = first;
        do
        {
            if ((u32)entry[3] < current->m_priority)
            {
                COrder* order = m_freeOrderHead.m_next;
                m_freeOrderHead.m_next = order->m_next;
                order->m_next = current;
                order->m_previous = current->m_previous;
                current->m_previous->m_next = order;
                current->m_previous = order;
                order->m_entry = entry;
                order->m_insertIndex = insertIndex;
                insertIndex++;
                order->m_descBlock = description;
                order->m_owner = process;
                order->m_priority = entry[3];
                order->m_debugName = (void*)description[0];
                m_orderCount++;
                break;
            }
            current = current->m_next;
        } while (current != first);

        entry += 5;
    } while (__ptmf_test((__ptmf*)entry) != 0);

    return 1;
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
