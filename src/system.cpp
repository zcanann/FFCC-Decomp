#include "ffcc/system.h"

#include "ffcc/file.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
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
#include "ffcc/p_dbgmenu.h"

#include "dolphin/gx/GXPerf.h"
#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "ffcc/p_game.h"
#include "ffcc/p_minigame.h"
#include <string.h>

extern "C" {
#include "PowerPC_EABI_Support/Runtime/ptmf.h"
}

extern void* __vt__7CSystem[];
CSystem System;

class CScenegraphProcessProxy {
public:
    virtual void Init();
    virtual void Quit();
    virtual int GetTable(unsigned long);
};

typedef void (CProcess::*ScenegraphCallback)();

struct CScenegraphEntry {
    ScenegraphCallback m_callback;
    u32 m_priority;
    u32 m_flags;
};

struct CScenegraphDesc {
    const char* m_debugName;
    ScenegraphCallback m_createCallback;
    ScenegraphCallback m_destroyCallback;
    CScenegraphEntry m_entries[1];
};

static const char s_cSystem[] = "CSystem";
static const char s_gamePalM_map[] = "gamePalM.map";
static const char s_system_cpp[] = "system.cpp";

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
int CSystem::IsGdev()
{
	return OSGetConsoleType() >> 0x1C & 1;
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
 * PAL Address: 0x80021760
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSystem::RemoveScenegraph(CProcess* process, int arg)
{
    CScenegraphDesc* descBlock = (CScenegraphDesc*)((CScenegraphProcessProxy*)process)->GetTable(arg);
    COrder* current = m_orderSentinel.m_next;

    do
    {
        COrder* next = current->m_next;
        if (current->m_descBlock == descBlock)
        {
            current->m_previous->m_next = current->m_next;
            current->m_next->m_previous = current->m_previous;
            current->m_next = m_freeOrderHead.m_next;
            m_freeOrderHead.m_next = current;
            m_orderCount--;
        }
        current = next;
    } while (current != &m_orderSentinel);

    if (descBlock->m_destroyCallback)
    {
        (process->*descBlock->m_destroyCallback)();
    }
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CSystem::AddScenegraph(CProcess* process, int arg)
{
    CScenegraphDesc* description = (CScenegraphDesc*)((CScenegraphProcessProxy*)process)->GetTable(arg);

    if (description->m_createCallback)
    {
        (process->*description->m_createCallback)();
    }

    CScenegraphEntry* entry = description->m_entries;
    int insertIndex = 0;
    while (entry->m_callback)
    {
        COrder* first = m_orderSentinel.m_next;
        COrder* current = first;
        do
        {
            if (entry->m_priority < current->m_priority)
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
                order->m_priority = entry->m_priority;
                order->m_debugName = (void*)description->m_debugName;
                m_orderCount++;
                break;
            }
            current = current->m_next;
        } while (current != first);

        entry++;
    }

    return 1;
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
    m_exitFlag = 0;

    do
    {
        unsigned short stepTrigger;
        unsigned short perfTrigger;

        if (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != Game.m_gameWork.m_gamePaused)
        {
            Graphic._WaitDrawDone(const_cast<char*>(s_system_cpp), 0x219);
            Game.m_gameWork.m_gamePaused = Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag;
            if (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == 1)
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
        else
        {
            stepTrigger = 0;
            perfTrigger = 0;
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

        if (((DbgMenuPcs.GetDbgFlagsRaw() & 0x40) != 0) && (Game.m_gameWork.m_gamePaused == 0))
        {
            for (unsigned int port = 0; port < 4; port++)
            {
                unsigned short trigger;
                unsigned short held;
                bool forceOff = false;

                if ((Pad._452_4_ != 0) || ((port == 0) && (Pad._448_4_ != -1)))
                {
                    forceOff = true;
                }
                if (forceOff)
                {
                    trigger = 0;
                }
                else
                {
                    unsigned int padIndex = (Pad._448_4_ == (int)port) ? 0 : port;
                    trigger = *(unsigned short*)((unsigned char*)&Pad + 0xA + padIndex * 0x54);
                }

                forceOff = false;
                if ((Pad._452_4_ != 0) || ((port == 0) && (Pad._448_4_ != -1)))
                {
                    forceOff = true;
                }
                if (forceOff)
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
                    if (System.m_scenegraphStepMode == 2)
                    {
                        Sound.PauseAllSe(0);
                        System.m_scenegraphStepMode = 0;
                        GbaQue.ClrShopMode();
                        GbaQue.SetPauseMode(0);
                    }
                    else if ((*(unsigned int*)(CFlat + 0x12A0) & 0x10) != 0)
                    {
                        Sound.PauseAllSe(1);
                        System.m_scenegraphStepMode = 2;
                        GbaQue.SetPauseMode(1);
                    }
                }
            }
        }

        int scenegraphStepMode = m_scenegraphStepMode;
        unsigned int drawToggle;
        if (scenegraphStepMode == 1)
        {
            drawToggle = ((unsigned int)__cntlzw(m_frameCounter & 3) >> 5) & 0xFF;
        }
        else
        {
            drawToggle = 1;
        }

        unsigned int stepGate = 0;
        if (scenegraphStepMode == 4)
        {
            stepGate = ((-(int)(m_frameCounter & 3)) >> 31);
        }
        else if (scenegraphStepMode < 4)
        {
            if (scenegraphStepMode == 2)
            {
                stepGate = 1;
            }
            else if (scenegraphStepMode > 2)
            {
                stepGate = ((-(int)(m_frameCounter & 7)) >> 31);
            }
        }
        else if (scenegraphStepMode < 6)
        {
            stepGate = m_frameCounter & 1;
        }

        float totalTime = 0.0f;
        CStopWatch watch(reinterpret_cast<char*>(-1));
        DumpMapFile(&watch);

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

            if (Game.m_gameWork.m_gamePaused == 0)
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
                    Graphic._WaitDrawDone(const_cast<char*>(s_system_cpp), 0x2CA);
                    GXReadGP0Metric();
                    GXReadGP1Metric();
                }
                watch.Stop();
                if ((perfTrigger & 1) != 0)
                {
                    order->m_lastTime = watch.Get();
                }
                totalTime += watch.Get();
            }
            else
            {
                order->m_lastTime = 0.0f;
            }
        }

        m_currentOrder = (COrder*)0;
        m_frameCounter++;
    } while (m_exitFlag == 0);

    Graphic._WaitDrawDone(const_cast<char*>(s_system_cpp), 0x2F6);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CSystem::Printf(char* fmt, ...)
{
    if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x1000) == 0)
	{
        return;
	}

    char buffer[0x20C];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    OSReport(buffer);
    USB.Printf(buffer);
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
 * PAL Address: 0x80022080
 * PAL Size: 856b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CSystem::Init()
{
    CFile::CHandle* fileHandle;
    int mapSize;
    int offset;
    int chunkSize;

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
    m_orderSentinel.m_previous = &m_orderSentinel;
    m_orderSentinel.m_next = &m_orderSentinel;
    m_orderSentinel.m_priority = 0xFF;
    m_freeOrderHead.m_next = m_orderPool;
    for (unsigned int i = 0; i < 0x80; i++)
    {
        m_orderPool[i].m_next = (i == 0x7F) ? &m_freeOrderHead : &m_orderPool[i + 1];
    }

    m_ownerThread = OSGetCurrentThread();
    m_scenegraphStepMode = 0;
    m_frameCounter = 0;
    m_mapStage = (CStage*)0;
    m_mapBuffer = (void*)0;
    m_mapSize = 0;

    OSSetErrorHandler(0, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(1, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(2, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(3, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(5, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(0xb, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(0xd, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(0xe, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(0xf, (OSErrorHandler)errorHandler);

    if (OSGetConsoleSimulatedMemSize() == 0x3000000)
    {
        m_mapStage = (CStage*)Memory.CreateStage(0x400000, const_cast<char*>(s_cSystem), 1);
        fileHandle = File.Open(const_cast<char*>(s_gamePalM_map), 0, CFile::PRI_LOW);
        if (fileHandle != (CFile::CHandle*)0)
        {
            mapSize = File.GetLength(fileHandle);
            m_mapSize = mapSize;
            m_mapBuffer = new ((CMemory::CStage*)m_mapStage, const_cast<char*>(s_system_cpp), 0x123) unsigned char[mapSize];
            offset = 0;
            for (; mapSize != 0; mapSize -= chunkSize)
            {
                chunkSize = 0x100000;
                if (mapSize < 0x100000)
                {
                    chunkSize = mapSize;
                }

                fileHandle->m_chunkSize = chunkSize;
                fileHandle->m_currentOffset = offset;
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                memcpy((unsigned char*)m_mapBuffer + offset, File.m_readBuffer, chunkSize);

                offset += chunkSize;
            }
            File.Close(fileHandle);
            Printf(const_cast<char*>(""));
        }
    }
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
