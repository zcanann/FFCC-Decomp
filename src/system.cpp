#include "ffcc/system.h"
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"

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

#ifdef VERSION_GCCP01
#define SYSTEM_MAP_FILE "gamePalM.map"
#else
#define SYSTEM_MAP_FILE "gameM.map"
#endif
#ifdef VERSION_GCCJGC
enum {
    SystemMapAllocationLine = 0x10E,
    SystemFrameWaitLine = 0x204,
    SystemMetricWaitLine = 0x2B5,
    SystemFinalWaitLine = 0x2E1
};
#else
enum {
    SystemMapAllocationLine = 0x123,
    SystemFrameWaitLine = 0x219,
    SystemMetricWaitLine = 0x2CA,
    SystemFinalWaitLine = 0x2F6
};
#endif

/*
 * --INFO--
 * PAL Address: 0x800223DC
 * PAL Size: 80b
 * EN Address: 0x800221D0
 * EN Size: 80b
 * JP Address: 0x80021C68
 * JP Size: 80b
 */
void OSPanic(const char* file, int line, const char* msg, ...)
{
	// TODO
}
/*
 * --INFO--
 * PAL Address: 0x800223D8
 * PAL Size: 4b
 * EN Address: 0x800221CC
 * EN Size: 4b
 * JP Address: 0x80021C64
 * JP Size: 4b
 */
void CSystem::errorHandler(unsigned short, OSContext*, unsigned long, unsigned long)
{
    static const char* pTable[17] = {
        "システムリセット例外",
        "マシンチェック例外",
        "DSI",
        "ISI",
        "外部割り込み例外",
        "アライメント例外",
        "プログラム例外",
        "浮動小数点利用不可例外",
        "デクリメンタ例外",
        "システムコール例外",
        "トレース例外",
        "パフォーマンスモニター例外",
        "命令アドレスブレークポイント例外",
        "システム管理割り込み例外",
        "温度割り込み例外",
        "メモリ保護エラー",
        "浮動小数点例外",
    };
	return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: UNUSED
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void systemTemplateDebug()
{
    System.Printf("systemTemplateDebug\n");
}
/*
 * --INFO--
 * PAL Address: 0x80022080
 * PAL Size: 856b
 * EN Address: 0x80021E74
 * EN Size: 856b
 * JP Address: 0x8002190C
 * JP Size: 856b
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
        m_mapStage = (CStage*)Memory.CreateStage(0x400000, "CSystem", 1);
        unsigned int count;
        CFile::CHandle* fileHandle = File.Open(SYSTEM_MAP_FILE, 0, CFile::PRI_LOW);
        if (fileHandle != (CFile::CHandle*)0)
        {
            unsigned int remaining;
            unsigned int mapSize;
            unsigned int offset;

            mapSize = File.GetLength(fileHandle);
            m_mapSize = mapSize;
            remaining = mapSize;
            m_mapBuffer = new ((CMemory::CStage*)m_mapStage, "system.cpp", SystemMapAllocationLine) unsigned char[mapSize];
            for (offset = 0; (int)remaining != 0; remaining -= count)
            {
                if (remaining >= 0x100000)
                {
                    count = 0x100000;
                }
                else
                {
                    count = remaining;
                }

                fileHandle->SetReadSize(count, offset);
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                memcpy((unsigned char*)m_mapBuffer + offset, File.m_readBuffer, count);

                offset += count;
            }
            File.Close(fileHandle);
            Printf("コンパイラのmap情報を" SYSTEM_MAP_FILE "から読み込みました。\n");
        }
    }
}
/*
 * --INFO--
 * PAL Address: 0x80021FB4
 * PAL Size: 204b
 * EN Address: 0x80021DA8
 * EN Size: 204b
 * JP Address: 0x80021840
 * JP Size: 204b
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
 * PAL Address: 0x80021EFC
 * PAL Size: 184b
 * EN Address: 0x80021CF0
 * EN Size: 184b
 * JP Address: 0x80021788
 * JP Size: 184b
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
 * PAL Address: 0x80021934
 * PAL Size: 1480b
 * EN Address: 0x80021728
 * EN Size: 1480b
 * JP Address: 0x800211C0
 * JP Size: 1480b
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
            Graphic._WaitDrawDone("system.cpp", SystemFrameWaitLine);
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

        stepTrigger = Pad.GetDebugButtonDown(4);

        perfTrigger = Pad.GetDebugButton(4);

        if ((stepTrigger & 0xC) != 0)
        {
            if ((stepTrigger & 8) != 0)
            {
                m_scenegraphStepMode = m_scenegraphStepMode ? 0 : 1;
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
                u16 trigger = Pad.GetGbaButtonDown(port);
                u16 held = Pad.GetButtonDown(port);

                if (((held | trigger) & 0x1000) != 0)
                {
                    if (System.m_scenegraphStepMode != 2)
                    {
                        if ((CFlatEventFlags() & 0x10) != 0)
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
            drawToggle = (m_frameCounter & 3) == 0;
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
        CStopWatch watch;

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
                    Graphic._WaitDrawDone("system.cpp", SystemMetricWaitLine);
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

    Graphic._WaitDrawDone("system.cpp", SystemFinalWaitLine);
}
/*
 * --INFO--
 * PAL Address: 0x8002182C
 * PAL Size: 264b
 * EN Address: 0x80021620
 * EN Size: 264b
 * JP Address: 0x800210B8
 * JP Size: 264b
 */
unsigned int CSystem::AddScenegraph(CProcess* process, int arg)
{
    CProcessCallbackTable* description = (CProcessCallbackTable*)process->GetTable(arg);

    if (description->m_create)
    {
        (process->*description->m_create)();
    }

    CProcessCallbackTable::Entry* entry = description->m_entries;
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
                order->m_debugName = description->m_name;
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
 * PAL Address: 0x80021760
 * PAL Size: 204b
 * EN Address: 0x80021554
 * EN Size: 204b
 * JP Address: 0x80020FEC
 * JP Size: 204b
 */
void CSystem::RemoveScenegraph(CProcess* process, int arg)
{
    CProcessCallbackTable* descBlock = (CProcessCallbackTable*)process->GetTable(arg);
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

    if (descBlock->m_destroy)
    {
        (process->*descBlock->m_destroy)();
    }
}
/*
 * --INFO--
 * PAL Address: 0x800216E4
 * PAL Size: 124b
 * EN Address: 0x800214D8
 * EN Size: 124b
 * JP Address: 0x80020F70
 * JP Size: 124b
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
 * PAL Address: 0x80021658
 * PAL Size: 140b
 * EN Address: 0x8002144C
 * EN Size: 140b
 * JP Address: 0x80020EE4
 * JP Size: 140b
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
 * PAL Address: 0x800215CC
 * PAL Size: 140b
 * EN Address: 0x800213C0
 * EN Size: 140b
 * JP Address: 0x80020E58
 * JP Size: 140b
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
 * PAL Address: 0x80021550
 * PAL Size: 124b
 * EN Address: 0x80021344
 * EN Size: 124b
 * JP Address: 0x80020DDC
 * JP Size: 124b
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
 * PAL Address: 0x80021530
 * PAL Size: 32b
 * EN Address: 0x80021324
 * EN Size: 32b
 * JP Address: 0x80020DBC
 * JP Size: 32b
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
 * PAL Address: 0x80021510
 * PAL Size: 32b
 * EN Address: 0x80021304
 * EN Size: 32b
 * JP Address: 0x80020D9C
 * JP Size: 32b
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
 * PAL Address: 0x800214D8
 * PAL Size: 56b
 * EN Address: 0x800212CC
 * EN Size: 56b
 * JP Address: 0x80020D64
 * JP Size: 56b
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
 * PAL Address: 0x800214B4
 * PAL Size: 36b
 * EN Address: 0x800212A8
 * EN Size: 36b
 * JP Address: 0x80020D40
 * JP Size: 36b
 */
int CSystem::IsGdev()
{
	return OSGetConsoleType() >> 0x1C & 1;
}
