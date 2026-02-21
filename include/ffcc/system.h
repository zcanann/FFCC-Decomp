#ifndef _FFCC_SYSTEM_H
#define _FFCC_SYSTEM_H

#include <Dolphin/types.h>

#include "ffcc/manager.h"

class CStage;
struct OSContext;
struct OSThread;

class CProcess : public CManager
{
public:
    CProcess();
    void onScriptChanging(char*);
    void onScriptChanged(char*, int);
    void onMapChanging(int, int);
    void onMapChanged(int, int, int);

    virtual void create();
    virtual void destroy();
    virtual void calc();
    virtual void ScriptChanging(char*);
    virtual void ScriptChanged(char*, int);
    virtual void MapChanging(int, int);
    virtual void MapChanged(int, int, int);
};

class CSystem : public CManager
{
public:
    struct COrder
	{
        unsigned int m_priority; // 0x00
        float m_lastTime;        // 0x04
        void* m_debugName;       // 0x08
        int m_insertIndex;       // 0x0C
        COrder* m_previous;      // 0x10
        COrder* m_next;          // 0x14
        CProcess* m_owner;       // 0x18
        void* m_descBlock;       // 0x1C
        void* m_entry;           // 0x20
        // sizeof = 0x24
    };

public:
    CSystem();

    void Init();
    void Quit();
    void Printf(char*, ...);
    void ExecScenegraph();
    unsigned int AddScenegraph(CProcess*, int);
    void RemoveScenegraph(CProcess*, int);
    virtual void ScriptChanging(char*);
    virtual void ScriptChanged(char*, int);
    virtual void MapChanging(int, int);
    virtual void MapChanged(int, int, int);
    COrder* GetFirstOrder();
    COrder* GetNextOrder(COrder*);
    COrder* GetOrder(int);
    unsigned int GetCounter();
    bool IsGdev();
    CSystem* DumpMapFile(void*);
    static void errorHandler(unsigned short, OSContext*, unsigned long, unsigned long);

    // void* vtable;             // 0x0000 (4 bytes)
    int m_exitFlag;              // 0x0004
    COrder m_orderSentinel;      // 0x0008 (size 0x24)
    COrder m_freeOrderHead;      // 0x002C (size 0x24)
    COrder m_orderPool[128];     // 0x0050 (0x24 * 128 = 0x1200)
    int m_orderCount;            // 0x1250
    int m_scenegraphStepMode;    // 0x1254
    unsigned int m_frameCounter; // 0x1258
    int m_execParam;             // 0x125C
    OSThread* m_ownerThread;     // 0x1260
    COrder* m_currentOrder;      // 0x1264
    int m_currentOrderIndex;     // 0x1268
    int m_initialized;           // 0x126C
    CStage* m_mapStage;          // 0x1270
    void* m_mapBuffer;           // 0x1274
    unsigned int m_mapSize;      // 0x1278
};

extern CSystem System;

#endif // _FFCC_SYSTEM_H
