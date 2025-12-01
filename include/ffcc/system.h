#ifndef CSYSTEM_H
#define CSYSTEM_H

#include <Dolphin/types.h>

#include "ffcc/manager.h"

class CProcess;
class CStage;
struct OSContext;
struct OSThread;

class CSystem
{
public:
    struct COrder
	{
        unsigned int   mPriority;  // 0x00
        float      mLastTime;      // 0x04
        void*      mDebugName;     // 0x08
        int    mInsertIndex;       // 0x0C
        COrder*    mPrevious;      // 0x10
        COrder*    mNext;          // 0x14
        CProcess*  mOwner;         // 0x18
        void*      mDescBlock;     // 0x1C
        void*      mEntry;         // 0x20
        // sizeof = 0x24
    };

public:
    static void errorHandler(unsigned short, OSContext*, unsigned long, unsigned long);

    CSystem();
    void Init();
    void Quit();
    void Printf(char*, ...);
    void ExecScenegraph();

    unsigned int AddScenegraph(CProcess*, int);
    void RemoveScenegraph(CProcess*, int);

    void ScriptChanging(char*);
    void ScriptChanged(char*, int);

    void MapChanging(int, int);
    void MapChanged(int, int, int);

    COrder* GetFirstOrder();
    COrder* GetNextOrder(COrder*);
    COrder* GetOrder(int);

    bool IsGdev();

    void DumpMapFile(void*);
    void OSPanic(...);

    // void* vtable;                 // 0x0000 (4 bytes)
    int mExitFlag;                // 0x0004
    COrder mOrderSentinel;        // 0x0008 (size 0x24)
    COrder mFreeOrderHead;        // 0x002C (size 0x24)
    COrder orderPool[128];        // 0x0050 (0x24 * 128 = 0x1200)
    int mOrderCount;              // 0x1250
    int mScenegraphStepMode;      // 0x1254
    unsigned int mFrameCounter;   // 0x1258
    int mExecParam;               // 0x125C
    OSThread* mOwnerThread;       // 0x1260
    COrder* mCurrentOrder;        // 0x1264
    int mCurrentOrderIndex;       // 0x1268
    int mInitialized;             // 0x126C
    CStage* mMapStage;            // 0x1270
    void* mMapBuffer;             // 0x1274
    unsigned int mMapSize;        // 0x1278
};

CSystem g_system;

#endif // CSYSTEM_H
