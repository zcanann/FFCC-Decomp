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
#include "ffcc/game.h"
#include "ffcc/p_minigame.h"
#include <string.h>

CSystem System;

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
extern const unsigned char s_systemDebugResources[0x194] = {
    0x64, 0x76, 0x64, 0x2F, 0x67, 0x62, 0x61, 0x2F, 0x00, 0x00, 0x00, 0x00,
    0x66, 0x66, 0x63, 0x63, 0x5F, 0x63, 0x6C, 0x69, 0x2E, 0x62, 0x69, 0x6E,
    0x00, 0x00, 0x00, 0x00, 0x6F, 0x62, 0x6A, 0x64, 0x61, 0x74, 0x2E, 0x73,
    0x70, 0x74, 0x00, 0x00, 0x69, 0x63, 0x6F, 0x6E, 0x2E, 0x64, 0x61, 0x74,
    0x00, 0x00, 0x00, 0x00, 0x46, 0x46, 0x20, 0x43, 0x72, 0x79, 0x73, 0x74,
    0x61, 0x6C, 0x20, 0x43, 0x68, 0x72, 0x6F, 0x6E, 0x69, 0x63, 0x6C, 0x65,
    0x73, 0x00, 0x00, 0x00, 0x83, 0x56, 0x83, 0x58, 0x83, 0x65, 0x83, 0x80,
    0x83, 0x8A, 0x83, 0x5A, 0x83, 0x62, 0x83, 0x67, 0x97, 0xE1, 0x8A, 0x4F,
    0x00, 0x00, 0x00, 0x00, 0x83, 0x7D, 0x83, 0x56, 0x83, 0x93, 0x83, 0x60,
    0x83, 0x46, 0x83, 0x62, 0x83, 0x4E, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00,
    0x8A, 0x4F, 0x95, 0x94, 0x8A, 0x84, 0x82, 0xE8, 0x8D, 0x9E, 0x82, 0xDD,
    0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x83, 0x41, 0x83, 0x89,
    0x83, 0x43, 0x83, 0x81, 0x83, 0x93, 0x83, 0x67, 0x97, 0xE1, 0x8A, 0x4F,
    0x00, 0x00, 0x00, 0x00, 0x83, 0x76, 0x83, 0x8D, 0x83, 0x4F, 0x83, 0x89,
    0x83, 0x80, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x95, 0x82, 0x93, 0xAE,
    0x8F, 0xAC, 0x90, 0x94, 0x93, 0x5F, 0x97, 0x98, 0x97, 0x70, 0x95, 0x73,
    0x89, 0xC2, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x83, 0x66, 0x83, 0x4E,
    0x83, 0x8A, 0x83, 0x81, 0x83, 0x93, 0x83, 0x5E, 0x97, 0xE1, 0x8A, 0x4F,
    0x00, 0x00, 0x00, 0x00, 0x83, 0x56, 0x83, 0x58, 0x83, 0x65, 0x83, 0x80,
    0x83, 0x52, 0x81, 0x5B, 0x83, 0x8B, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00,
    0x83, 0x67, 0x83, 0x8C, 0x81, 0x5B, 0x83, 0x58, 0x97, 0xE1, 0x8A, 0x4F,
    0x00, 0x00, 0x00, 0x00, 0x83, 0x70, 0x83, 0x74, 0x83, 0x48, 0x81, 0x5B,
    0x83, 0x7D, 0x83, 0x93, 0x83, 0x58, 0x83, 0x82, 0x83, 0x6A, 0x83, 0x5E,
    0x81, 0x5B, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x96, 0xBD, 0x97, 0xDF,
    0x83, 0x41, 0x83, 0x68, 0x83, 0x8C, 0x83, 0x58, 0x83, 0x75, 0x83, 0x8C,
    0x81, 0x5B, 0x83, 0x4E, 0x83, 0x7C, 0x83, 0x43, 0x83, 0x93, 0x83, 0x67,
    0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x83, 0x56, 0x83, 0x58,
    0x83, 0x65, 0x83, 0x80, 0x8A, 0xC7, 0x97, 0x9D, 0x8A, 0x84, 0x82, 0xE8,
    0x8D, 0x9E, 0x82, 0xDD, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x00, 0x00,
    0x89, 0xB7, 0x93, 0x78, 0x8A, 0x84, 0x82, 0xE8, 0x8D, 0x9E, 0x82, 0xDD,
    0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x83, 0x81, 0x83, 0x82,
    0x83, 0x8A, 0x95, 0xDB, 0x8C, 0xEC, 0x83, 0x47, 0x83, 0x89, 0x81, 0x5B,
    0x00, 0x00, 0x00, 0x00, 0x95, 0x82, 0x93, 0xAE, 0x8F, 0xAC, 0x90, 0x94,
    0x93, 0x5F, 0x97, 0xE1, 0x8A, 0x4F, 0x00, 0x00,
};
extern const char s_CManager_801D6F14[] = "CManager";
static const char s_system_cpp[12] = "system.cpp";
static const char s_gamePalM_map[16] = "gamePalM.map";
static const char s_compilerMapLoaded[] =
    "\203\122\203\223\203\160\203\103\203\211\202\314\155\141\160\217\356"
    "\225\361\202\360\147\141\155\145\120\141\154\115\056\155\141\160\202"
    "\251\202\347\223\307\202\335\215\236\202\335\202\334\202\265\202\275"
    "\201\102\012";
extern const char s_systemTemplateDebug[28] = "systemTemplateDebug\n";
extern const char s_systemStopwatchName[8];

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
		if (order->m_entry == order->m_descBlock->m_entries)
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
		if (order->m_entry == order->m_descBlock->m_entries)
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
		if (order->m_entry == order->m_descBlock->m_entries)
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
		if (order->m_entry == order->m_descBlock->m_entries)
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
    CScenegraphDesc* descBlock = (CScenegraphDesc*)process->GetTable(arg);
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
    CScenegraphDesc* description = (CScenegraphDesc*)process->GetTable(arg);

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
        u16 stepTrigger;
        u16 perfTrigger;

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

        if (Pad._452_4_ != 0)
        {
            stepTrigger = 0;
        }
        else
        {
            unsigned int stepPad = (Pad._448_4_ == 4) ? 0 : 4;
            stepTrigger = *(unsigned short*)((unsigned char*)&Pad + 0x36 + stepPad * 0x54);
        }
        stepTrigger = (unsigned short)stepTrigger;

        if (Pad._452_4_ != 0)
        {
            perfTrigger = 0;
        }
        else
        {
            unsigned int perfPad = (Pad._448_4_ == 4) ? 0 : 4;
            perfTrigger = *(unsigned short*)((unsigned char*)&Pad + 0x34 + perfPad * 0x54);
        }
        perfTrigger = (unsigned short)perfTrigger;

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
            for (int port = 0; port < 4; port++)
            {
                u16 trigger;
                u16 held;
                bool noInput;

                noInput = false;
                if ((Pad._452_4_ != 0) || ((port == 0) && (Pad._448_4_ != -1)))
                {
                    noInput = true;
                }
                if (noInput)
                {
                    trigger = 0;
                }
                else
                {
                    unsigned int padIndex = (Pad._448_4_ == port) ? 0 : port;
                    trigger = *(unsigned short*)((unsigned char*)&Pad + 0xA + padIndex * 0x54);
                }
                trigger = (unsigned short)trigger;

                noInput = false;
                if ((Pad._452_4_ != 0) || ((port == 0) && (Pad._448_4_ != -1)))
                {
                    noInput = true;
                }
                if (noInput)
                {
                    held = 0;
                }
                else
                {
                    unsigned int padIndex = (Pad._448_4_ == port) ? 0 : port;
                    held = *(unsigned short*)((unsigned char*)&Pad + 0x8 + padIndex * 0x54);
                }
                held = (unsigned short)held;

                if (((held | trigger) & 0x1000) != 0)
                {
                    if (System.m_scenegraphStepMode != 2)
                    {
                        if ((*(unsigned int*)(CFlat + 0x12A0) & 0x10) != 0)
                        {
                            Sound.PauseAllSe(1);
                            System.m_scenegraphStepMode = 2;
                            GbaQue.SetPauseMode(1);
                        }
                    }
                    else
                    {
                        Sound.PauseAllSe(0);
                        System.m_scenegraphStepMode = 0;
                        GbaQue.ClrShopMode();
                        GbaQue.SetPauseMode(0);
                    }
                }
            }
        }

        int scenegraphStepMode = m_scenegraphStepMode;
        int drawToggle;
        if (scenegraphStepMode == 1)
        {
            drawToggle = ((unsigned int)__cntlzw(m_frameCounter & 3) >> 5) & 0xFF;
        }
        else
        {
            drawToggle = 1;
        }

        int stepGate = 0;
        switch (scenegraphStepMode)
        {
        case 5:
            {
                unsigned int frameBit = (m_frameCounter & 1) != 0;
                stepGate = frameBit;
            }
            break;
        case 4:
            stepGate = (m_frameCounter & 3) != 0;
            break;
        case 3:
            stepGate = (m_frameCounter & 7) != 0;
            break;
        case 2:
            stepGate = 1;
            break;
        }

        float totalTime = 0.0f;
        int perfEnabled = perfTrigger & 1;
        CStopWatch watch(const_cast<char*>(s_systemStopwatchName));

        COrder* order = m_orderSentinel.m_next;
        int index = 0;
        for (; order != &m_orderSentinel; order = order->m_next, index++)
        {
            m_currentOrder = order;
            m_currentOrderIndex = index;

            unsigned int flags = order->m_entry->m_flags;
            int skip = 0;
            if ((flags & 1) != 0)
            {
                if (drawToggle == 0)
                {
                    skip = 1;
                }
            }
            else
            {
                if ((stepGate != 0) && (drawToggle != 0) && ((flags & 4) != 0))
                {
                    skip = 0;
                }
                else
                {
                    skip = stepGate;
                }
            }

            if (Game.m_gameWork.m_gamePaused != 0)
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
            else
            {
                if ((flags & 0x10) != 0)
                {
                    skip = 1;
                }
            }

            if (skip == 0)
            {
                watch.Reset();
                watch.Start();
                if ((order->m_entry->m_flags & 1) != 0)
                {
                    Graphic.SetDrawDoneDebugData(-1);
                }
                (order->m_owner->*order->m_entry->m_callback)();
                watch.Stop();
                order->m_lastTime = watch.Get();

                watch.Start();
                if (perfEnabled != 0)
                {
                    Graphic._WaitDrawDone(const_cast<char*>(s_system_cpp), 0x2CA);
                    GXReadGP0Metric();
                    GXReadGP1Metric();
                }
                watch.Stop();
                if (perfEnabled != 0)
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
            unsigned int count;
            unsigned int length;
            unsigned int mapSize;
            unsigned int offset;

            length = File.GetLength(fileHandle);
            m_mapSize = length;
            mapSize = length;
            m_mapBuffer = new ((CMemory::CStage*)m_mapStage, const_cast<char*>(s_system_cpp), 0x123) unsigned char[mapSize];
            for (offset = 0; (int)mapSize != 0; mapSize -= count)
            {
                count = 0x100000;
                if (mapSize < 0x100000)
                {
                    count = mapSize;
                }

                fileHandle->m_chunkSize = count;
                fileHandle->m_currentOffset = offset;
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                memcpy((unsigned char*)m_mapBuffer + offset, File.m_readBuffer, count);

                offset += count;
            }
            File.Close(fileHandle);
            Printf(const_cast<char*>(s_compilerMapLoaded));
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
