#include "ffcc/graphic.h"

#include <math.h>
#include <stdarg.h>
#include <string.h>

#include "ffcc/memory.h"
#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/pad.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "dolphin/vi.h"
#include "dolphin/vi/vifuncs.h"

extern "C" char lbl_801E8408[];
extern GXRenderModeObj lbl_801E83C0;
extern u8 DAT_801E83F2[7];
extern char DAT_80238030[];
extern CUtil DAT_8032ec70;
extern "C" u8 DAT_8032ec48;
extern "C" u8 DAT_8032ec4c;
extern "C" u8 DAT_8032ec50;
extern "C" u8 DAT_8032ec54;
extern "C" char __vt__8CManager[];
extern "C" _GXColor DAT_8032e3e8;
extern "C" char DAT_801d637c[];
extern "C" char DAT_801d63c0[];
extern "C" char DAT_801d6400[];
extern "C" char DAT_801d643c[];
extern "C" char DAT_8032f714[];
extern "C" u8 DAT_801fd480[];
extern "C" float FLOAT_8032f6c0;
extern "C" float FLOAT_8032f6c4;
extern "C" double DOUBLE_8032f6d8;
extern "C" float FLOAT_8032f708;
extern "C" float FLOAT_8032f70c;
extern "C" float FLOAT_8032f710;
extern "C" int __cntlzw(unsigned int);

extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
} CameraPcs;

extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" char lbl_801D6348[];
extern "C" char lbl_801D6330[];
extern "C" char lbl_801D6498[];
extern "C" OSThread m_thread;
extern "C" u8 m_threadStack[];

static inline void*& PtrAt(CGraphic* self, u32 offset) {
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + offset);
}

static inline u16 U16At(void* p, u32 offset) {
    return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(p) + offset);
}

static inline int& S32At(CGraphic* self, u32 offset) {
    return *reinterpret_cast<int*>(reinterpret_cast<u8*>(self) + offset);
}

static inline u8& U8At(CGraphic* self, u32 offset) {
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(self) + offset);
}

extern "C" {
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int,
                                                                                                             int, int,
                                                                                                             int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                           int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int,
                                                                                                             int, int,
                                                                                                             int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                           int);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
}

/*
 * --INFO--
 * PAL Address: 0x80019f68
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_graphic_cpp(void)
{
    void* vtbl = __vt__8CManager;
    *reinterpret_cast<void**>(&Graphic) = vtbl;
    *reinterpret_cast<void**>(&Graphic) = lbl_801E8408;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int checkThread(void*)
{
	Graphic.Thread();
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGraphic::CGraphic()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80019b54
 * PAL Size: 1000b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Init()
{
    PtrAt(this, 0x4) = CreateStage__7CMemoryFUlPci(&Memory, 0x19C000, lbl_801D6330, 0);
    PtrAt(this, 0x8) = CreateStage__7CMemoryFUlPci(&Memory, 0xD6000, lbl_801D6498, 0);

    S32At(this, 0x14) = 0;
    U8At(this, 0x7200) = 0;
    U8At(this, 0x7201) = 0;
    U8At(this, 0x7202) = 0;
    U8At(this, 0x7203) = 0;

    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x7204) = 0.0f;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x7208) = 0.0f;

    U8At(this, 0x735F) = U8At(this, 0x7200);
    U8At(this, 0x7360) = U8At(this, 0x7201);
    U8At(this, 0x7361) = U8At(this, 0x7202);
    U8At(this, 0x7362) = U8At(this, 0x7203);
    memset(reinterpret_cast<u8*>(this) + 0x7364, 0, 0x10);

    OSCreateThread(&m_thread, reinterpret_cast<void* (*)(void*)>(checkThread), nullptr, m_threadStack, 0x4000, 1, 1);
    OSResumeThread(&m_thread);

    VIInit();
    PtrAt(this, 0x71E0) = &lbl_801E83C0;
    S32At(this, 0x71F0) = 1;

    void* renderMode = PtrAt(this, 0x71E0);
    u32 alignedWidth = (U16At(renderMode, 4) + 0xF) & 0xFFF0;
    u16 efbHeight = U16At(renderMode, 6);
    u16 xfbHeight = U16At(renderMode, 8);

    PtrAt(this, 0x71E4) = __nwa__FUlPQ27CMemory6CStagePci(alignedWidth * xfbHeight * 2,
                                                           reinterpret_cast<CMemory::CStage*>(PtrAt(this, 0x4)),
                                                           lbl_801D6348, 0x86);
    memset(PtrAt(this, 0x71E4), 0, 4);

    PtrAt(this, 0x71EC) = __nwa__FUlPQ27CMemory6CStagePci(alignedWidth * efbHeight * 2,
                                                           reinterpret_cast<CMemory::CStage*>(PtrAt(this, 0x4)),
                                                           lbl_801D6348, 0x88);
    memset(PtrAt(this, 0x71EC), 0, 4);

    PtrAt(this, 0x71E8) = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, alignedWidth * efbHeight * 2 + 0x46000,
                                                                     reinterpret_cast<CMemory::CStage*>(PtrAt(this, 0x8)),
                                                                     lbl_801D6348, 0xB53, 0);
    memset(PtrAt(this, 0x71E8), 0, 0x46004);

    PtrAt(this, 0x10) =
        __nwa__FUlPQ27CMemory6CStagePci(0x60000, reinterpret_cast<CMemory::CStage*>(PtrAt(this, 0x4)), lbl_801D6348, 0x8B);

    VIConfigure(reinterpret_cast<GXRenderModeObj*>(PtrAt(this, 0x71E0)));
    GXInit(PtrAt(this, 0x10), 0x60000);

    GXSetViewport(0.0f, 0.0f, static_cast<f32>(U16At(renderMode, 4)), static_cast<f32>(U16At(renderMode, 6)), 0.0f, 1.0f);
    GXSetScissor(0, 0, U16At(renderMode, 4), U16At(renderMode, 6));
    GXSetDispCopyYScale(GXGetYScaleFactor(U16At(renderMode, 6), U16At(renderMode, 8)));
    GXSetDispCopySrc(0, 0, U16At(renderMode, 4), U16At(renderMode, 6));
    GXSetDispCopyDst(U16At(renderMode, 4), U16At(renderMode, 6));
    GXSetCopyFilter(reinterpret_cast<GXRenderModeObj*>(renderMode)->aa,
                    reinterpret_cast<GXRenderModeObj*>(renderMode)->sample_pattern, GX_TRUE, DAT_801E83F2);

    if (reinterpret_cast<GXRenderModeObj*>(renderMode)->aa == 0) {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    }

    GXSetDispCopySrc(0, 0, U16At(renderMode, 4), U16At(renderMode, 6));
    GXSetDispCopyDst(U16At(renderMode, 4), U16At(renderMode, 6));
    GXCopyDisp(PtrAt(this, 0x71E4), GX_TRUE);
    GXSetDispCopyGamma(GX_GM_1_0);
    VISetNextFrameBuffer(PtrAt(this, 0x71E4));
    VIFlush();
    VIWaitForRetrace();
    if ((*reinterpret_cast<u32*>(renderMode) & 1) != 0) {
        VIWaitForRetrace();
    }

    S32At(this, 0x71F4) = VIGetRetraceCount();
    S32At(this, 0xC) = 0;
    S32At(this, 0x734C) = 0;
    S32At(this, 0x7350) = 0;
    S32At(this, 0x7354) = 0;
    makeSphere();
    S32At(this, 0x7358) = 0;
    U8At(this, 0x735C) = 0;
    U8At(this, 0x735D) = 0;
    U8At(this, 0x735E) = 0;
    GXCopyDisp(PtrAt(this, 0x71E4), GX_TRUE);
    PtrAt(this, 0x7368) = lbl_801D6348;
    S32At(this, 0x736C) = 0xBE;
    S32At(this, 0x7364) = 1;
    GXSetDrawDone();
    GXWaitDrawDone();
    S32At(this, 0x7364) = 0;
    S32At(this, 0x7370) += 1;
    VIFlush();
}

/*
 * --INFO--
 * PAL Address: 0x80019a94
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Quit()
{
    if (PtrAt(this, 0x71EC) != nullptr) {
        __dla__FPv(PtrAt(this, 0x71EC));
        PtrAt(this, 0x71EC) = nullptr;
    }
    if (PtrAt(this, 0x71E4) != nullptr) {
        __dla__FPv(PtrAt(this, 0x71E4));
        PtrAt(this, 0x71E4) = nullptr;
    }
    if (PtrAt(this, 0x71E8) != nullptr) {
        __dla__FPv(PtrAt(this, 0x71E8));
        PtrAt(this, 0x71E8) = nullptr;
    }
    if (PtrAt(this, 0x71FC) != nullptr) {
        __dla__FPv(PtrAt(this, 0x71FC));
        PtrAt(this, 0x71FC) = nullptr;
    }
    if (PtrAt(this, 0x10) != nullptr) {
        __dla__FPv(PtrAt(this, 0x10));
        PtrAt(this, 0x10) = nullptr;
    }

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, PtrAt(this, 0x8));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, PtrAt(this, 0x4));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGraphic::GetProgressive()
{
    if (VIGetDTVStatus() == 0) {
        return 0;
    }
    return OSSetProgressiveMode() == 0 ? 1 : 2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::ChangeProgressive(int mode)
{
    GXRenderModeObj** renderMode = reinterpret_cast<GXRenderModeObj**>(reinterpret_cast<u8*>(this) + 0x71E0);
    if (*renderMode != &lbl_801E83C0) {
        *renderMode = &lbl_801E83C0;
        GXAdjustForOverscan(*renderMode, *renderMode, 0, 0x10);
        VIConfigure(*renderMode);
        GXSetCopyFilter((*renderMode)->aa, (*renderMode)->sample_pattern, GX_TRUE, DAT_801E83F2);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
    OSGetProgressiveMode(mode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SetCopyClear(_GXColor color, int)
{
    _GXColor* clearColor = reinterpret_cast<_GXColor*>(reinterpret_cast<u8*>(this) + 0x735F);
    *clearColor = color;
    GXSetCopyClear(*clearColor, 0xFFFFFF);
}

/*
 * --INFO--
 * PAL Address: 0x8001992c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetStdDispCopySrc()
{
    void* renderMode = PtrAt(this, 0x71E0);
    GXSetDispCopySrc(0, 0, U16At(renderMode, 4), U16At(renderMode, 6));
}

/*
 * --INFO--
 * PAL Address: 0x80019900
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetStdDispCopyDst()
{
    void* renderMode = PtrAt(this, 0x71E0);
    GXSetDispCopyDst(U16At(renderMode, 4), U16At(renderMode, 6));
}

/*
 * --INFO--
 * PAL Address: 0x800198b8
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetStdPixelFmt()
{
    void* renderMode = PtrAt(this, 0x71E0);
    if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(renderMode) + 0x19) == 0) {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80019830
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetViewport()
{
    register void* renderMode = PtrAt(this, 0x71E0);
    register u16 width = U16At(renderMode, 4);
    register u16 height = U16At(renderMode, 6);

    GXSetViewport(FLOAT_8032f6c0, FLOAT_8032f6c0, (f32)width, (f32)height, FLOAT_8032f6c0, FLOAT_8032f6c4);
    GXSetScissor(0, 0, width, height);
}

/*
 * --INFO--
 * PAL Address: 0x80019724
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::BeginFrame()
{
    GXSetZMode((GXBool)1, GX_LEQUAL, (GXBool)1);
    GXSetColorUpdate((GXBool)1);
    void* renderMode = PtrAt(this, 0x71E0);
    u16 width = U16At(renderMode, 4);
    u16 height = U16At(renderMode, 6);
    GXSetViewport(0.0f, 0.0f, (f32)width, (f32)height, 0.0f, 1.0f);
    GXInvalidateVtxCache();
    GXInvalidateTexAll();

    const bool useDebugPad = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    u16 buttons = 0;
    if (!useDebugPad) {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        buttons = Pad._4_2_;
    }

    if ((buttons & 2) != 0) {
        S32At(this, 0x7354) = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(S32At(this, 0x7354)))) >> 5) & 0xFF;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80019718
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::EndFrame()
{
    S32At(this, 0x14) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800196e0
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetDrawDoneDebugData(signed char drawDoneId)
{
	GXSetDrawSync((u16)(((System.m_currentOrderIndex & 0xFF) << 8) | (drawDoneId & 0xFF)));
}

/*
 * --INFO--
 * PAL Address: 0x800196b8
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetDrawDoneDebugDataPartControl(int partControl)
{
	GXSetDrawSync((u16)(partControl | 0x8000));
}

/*
 * --INFO--
 * PAL Address: 0x80019694
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void wakeup(OSAlarm* alarm, OSContext*)
{
    OSThread** waitingThread = reinterpret_cast<OSThread**>(reinterpret_cast<u8*>(alarm) + 0x28);
    OSResumeThread(*waitingThread);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void sleep()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80019640
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::_WaitDrawDone(char* file, int line)
{
    PtrAt(this, 0x7368) = file;
    S32At(this, 0x736C) = line;
    S32At(this, 0x7364) = 1;
    GXSetDrawDone();
    GXWaitDrawDone();
    S32At(this, 0x7364) = 0;
    S32At(this, 0x7370) += 1;
}

/*
 * --INFO--
 * PAL Address: 0x800193c8
 * PAL Size: 632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Thread()
{
    struct SleepAlarm {
        OSAlarm alarm;
        OSThread* thread;
    };

    int lastCounter = -1;
    int debugCountdown = 5;

    while (true) {
        if (S32At(this, 0x7364) == 0) {
            debugCountdown = 5;
        } else {
            if (lastCounter != S32At(this, 0x7370)) {
                debugCountdown = 100;
                lastCounter = S32At(this, 0x7370);
            }
            debugCountdown--;

            if (debugCountdown == 0) {
                u16 drawSyncRaw = GXReadDrawSync();
                u16 drawSyncPart = drawSyncRaw & 0x7FFF;
                if ((drawSyncRaw & 0x8000) != 0) {
                    if (drawSyncPart == 0x7FFF) {
                        System.Printf(DAT_801d637c, PtrAt(this, 0x7368), S32At(this, 0x736C));
                    } else if (drawSyncPart == 0x7FFE) {
                        System.Printf(DAT_801d63c0, PtrAt(this, 0x7368), S32At(this, 0x736C));
                    } else {
                        System.Printf(DAT_801d6400, PtrAt(this, 0x7368), S32At(this, 0x736C), DAT_8032f714);
                    }
                }

                CSystem::COrder* order = System.GetOrder(drawSyncPart >> 8);
                void* orderName = DAT_8032f714;
                int orderIndex = -1;
                if (order != nullptr) {
                    orderName = order->m_debugName;
                    orderIndex = order->m_insertIndex;
                }
                System.Printf(DAT_801d643c, PtrAt(this, 0x7368), S32At(this, 0x736C), orderName, orderIndex,
                              static_cast<int>(static_cast<char>(drawSyncPart)));
            }
        }

        if (DAT_8032ec4c == 0) {
            DAT_8032ec48 = 0;
            DAT_8032ec4c = 1;
        }
        if (DAT_8032ec54 == 0) {
            DAT_8032ec50 = 0;
            DAT_8032ec54 = 1;
        }

        if (OSGetResetButtonState() == 0) {
            if (DAT_8032ec48 != 0) {
                DAT_8032ec50 = 1;
            }
        } else {
            DAT_8032ec48 = 1;
        }

        if ((DAT_8032ec50 != 0) && (File.m_fatalDiskErrorFlag == 0) && (MemoryCardMan.m_currentSlot == 0xFF)) {
            break;
        }

        SleepAlarm sleepAlarm;
        sleepAlarm.thread = OSGetCurrentThread();
        OSCreateAlarm(&sleepAlarm.alarm);
        OSSetAlarmTag(&sleepAlarm.alarm, 1);
        BOOL interrupts = OSDisableInterrupts();
        OSSetAlarm(&sleepAlarm.alarm, (OS_BUS_CLOCK / 4000) * 0x32, wakeup);
        OSSuspendThread(sleepAlarm.thread);
        OSRestoreInterrupts(interrupts);
    }

    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();
    OSCancelAlarms(1);
    OSResetSystem(FALSE, 0, FALSE);
    while (true) {}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
u8 CGraphic::IsFifoOver()
{
	GXBool overhi;
	GXBool underflow;
	GXBool cpuWrite;
	GXBool gpRead;
	GXBool fifoWrap;
	u32 fifoCount;

	GXGetFifoStatus(GXGetCPUFifo(), &overhi, &underflow, &fifoCount, &cpuWrite, &gpRead, &fifoWrap);
	return fifoWrap;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
u32 CGraphic::IsFrameRateOver()
{
	return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(this) + 0x7350);
}

/*
 * --INFO--
 * PAL Address: 0x800191d8
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Flip()
{
    if (S32At(this, 0xC) != 0) {
        if (S32At(this, 0x71F0) != 0) {
            VISetBlack(FALSE);
            S32At(this, 0x71F0) = 0;
        }

        if (System.m_scenegraphStepMode != 1) {
            int retraceCount = VIGetRetraceCount();
            if ((u32)(retraceCount - S32At(this, 0x71F4)) < 2) {
                S32At(this, 0x7350) = 0;
                do {
                    VIWaitForRetrace();
                    retraceCount = VIGetRetraceCount();
                } while ((u32)(retraceCount - S32At(this, 0x71F4)) < 2);
            } else {
                S32At(this, 0x7350) = 1;
            }
        }

        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXCopyDisp(PtrAt(this, 0x71E4), GX_TRUE);
        PtrAt(this, 0x7368) = lbl_801D6348;
        S32At(this, 0x736C) = 0x26D;
        S32At(this, 0x7364) = 1;
        GXSetDrawDone();
        GXWaitDrawDone();
        S32At(this, 0x7364) = 0;
        S32At(this, 0x7370) += 1;
        VIFlush();

        S32At(this, 0x734C) = 1 - S32At(this, 0x734C);

        GXFifoObj* fifo = reinterpret_cast<GXFifoObj*>(reinterpret_cast<u8*>(this) + 0x724C + S32At(this, 0x734C) * 0x80);
        GXInitFifoBase(fifo, PtrAt(this, 0x10), 0x60000);
        GXInitFifoLimits(fifo, 0x5C000, 0x50000);
        GXSetCPUFifo(fifo);
        GXSetGPFifo(fifo);
    }

    S32At(this, 0x71F4) = VIGetRetraceCount();

    if (System.m_scenegraphStepMode == 1) {
        S32At(this, 0xC) = ((u32)__cntlzw(System.m_frameCounter & 3) >> 5) & 0xFF;
    } else {
        S32At(this, 0xC) = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800190f8
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Printf(char* fmt, ...)
{
    if (*reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x14) < 0x70) {
        char buffer[264];
        va_list args;
        va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        va_end(args);

        int index = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x14);
        *reinterpret_cast<short*>(reinterpret_cast<u8*>(this) + index * 4 + 0x18) = -1;
        *reinterpret_cast<short*>(reinterpret_cast<u8*>(this) + index * 4 + 0x1A) = -1;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x14) = index + 1;
        strcpy(reinterpret_cast<char*>(reinterpret_cast<u8*>(this) + index * 0x70 + 0x1E0), buffer);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80019000
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Printf(unsigned long x, unsigned long y, char* fmt, ...)
{
    if (*reinterpret_cast<unsigned int*>(reinterpret_cast<u8*>(this) + 0x14) < 0x70) {
        char buffer[272];
        va_list args;
        va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        va_end(args);

        int index = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x14);
        *reinterpret_cast<short*>(reinterpret_cast<u8*>(this) + index * 4 + 0x18) = static_cast<short>(x);
        *reinterpret_cast<short*>(reinterpret_cast<u8*>(this) + index * 4 + 0x1A) = static_cast<short>(y);
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x14) = index + 1;
        strcpy(reinterpret_cast<char*>(reinterpret_cast<u8*>(this) + index * 0x70 + 0x1E0), buffer);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawDebugString()
{
    Mtx44 proj;
    Mtx model;
    Mtx texMtx;
    GXTexObj texObj;

    void* renderMode = PtrAt(this, 0x71E0);
    C_MTXOrtho(proj,
               FLOAT_8032f6c0,
               static_cast<float>(U16At(renderMode, 6)),
               FLOAT_8032f6c0,
               static_cast<float>(U16At(renderMode, 4)),
               FLOAT_8032f6c0,
               FLOAT_8032f708);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCurrentMtx(0);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 0, 0, 7, 0);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetCurrentMtx(0);

    GXInitTexObj(&texObj, DAT_801fd480, 0x40, 0x60, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, FLOAT_8032f6c0, FLOAT_8032f6c0, FLOAT_8032f6c0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    PSMTXScale(texMtx, FLOAT_8032f70c, FLOAT_8032f710, FLOAT_8032f6c4);
    GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, 0x7D);

    s16 y = 0x10;
    u8* base = reinterpret_cast<u8*>(this);
    for (u32 i = 0; i < *reinterpret_cast<u32*>(base + 0x14); ++i) {
        s16 xCell = *reinterpret_cast<s16*>(base + 0x18 + i * 4);
        s16 yCell = *reinterpret_cast<s16*>(base + 0x1A + i * 4);
        char* text = reinterpret_cast<char*>(base + 0x1E0 + i * 0x70);

        if (xCell == -1) {
            DrawDebugStringDirect(0x10, static_cast<u32>(y), text, 0xC);
        } else {
            DrawDebugStringDirect(static_cast<u32>(xCell * 0xC + 0x10), static_cast<u32>(yCell * 0xC + 0x10), text, 0xC);
        }

        y += 0xC;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80018bf0
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::InitDebugString()
{
    Mtx44 proj;
    Mtx model;
    Mtx texMtx;
    GXTexObj texObj;

    void* renderMode = PtrAt(this, 0x71E0);
    C_MTXOrtho(proj,
               FLOAT_8032f6c0,
               static_cast<float>(U16At(renderMode, 6)),
               FLOAT_8032f6c0,
               static_cast<float>(U16At(renderMode, 4)),
               FLOAT_8032f6c0,
               FLOAT_8032f708);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCurrentMtx(0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 0, 0, 7, 0);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetCurrentMtx(0);
    GXInitTexObj(&texObj, DAT_801fd480, 0x40, 0x60, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, FLOAT_8032f6c0, FLOAT_8032f6c0, FLOAT_8032f6c0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    PSMTXScale(texMtx, FLOAT_8032f70c, FLOAT_8032f710, FLOAT_8032f6c4);
    GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, 0x7D);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80018a50
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawDebugStringDirect(unsigned long x, unsigned long y, char* text, unsigned long charSize)
{
    if (text == nullptr) {
        return;
    }

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xD, (GXAttrType)1);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)9, (GXCompCnt)1, (GXCompType)3, 0);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)0xD, (GXCompCnt)1, (GXCompType)3, 1);

    u32 count = 0;
    char* lineStart = text;
    while (true) {
        char ch;
        while (true) {
            ch = *text++;
            if (ch < ' ' || ch > 0x7F) {
                break;
            }
            count += 1;
        }

        if (count > 0) {
            GXBegin((GXPrimitive)0x80, (GXVtxFmt)0, (u16)((count & 0x3FFF) << 2));
            s16 i = 0;
            while (count > 0) {
                s16 px = (s16)(x + i * charSize);
                u32 glyph = (u32)(*lineStart - 0x20);
                s16 tx = (s16)((glyph & 7) * 16);
                s16 ty = (s16)((glyph >> 3) * 16);

                i++;
                lineStart++;

                GXWGFifo.s16 = px;
                GXWGFifo.s16 = (s16)y;
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = tx;
                GXWGFifo.s16 = ty;

                GXWGFifo.s16 = (s16)(px + charSize);
                GXWGFifo.s16 = (s16)y;
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = (s16)(tx + 0x10);
                GXWGFifo.s16 = ty;

                GXWGFifo.s16 = (s16)(px + charSize);
                GXWGFifo.s16 = (s16)(y + charSize);
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = (s16)(tx + 0x10);
                GXWGFifo.s16 = (s16)(ty + 0x10);

                GXWGFifo.s16 = px;
                GXWGFifo.s16 = (s16)(y + charSize);
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = tx;
                GXWGFifo.s16 = (s16)(ty + 0x10);

                count -= 1;
            }
            count = 0;
        }

        if (ch != '\n') {
            break;
        }
        y += charSize;
        lineStart = text;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::SaveFrameBuffer(char*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80018a10
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawSphere()
{
    GXSetLineWidth(8, GX_TO_ZERO);
    GXCallDisplayList(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
}

/*
 * --INFO--
 * PAL Address: 0x80018954
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawSphere(float (*mtx)[4], Vec* pos, float scale, _GXColor* color)
{
    Mtx sphereMtx;

    PSMTXScale(sphereMtx, scale, scale, scale);
    sphereMtx[0][3] = pos->x;
    sphereMtx[1][3] = pos->y;
    sphereMtx[2][3] = pos->z;
    PSMTXConcat(mtx, sphereMtx, sphereMtx);
    GXLoadPosMtxImm(sphereMtx, 0);
    GXSetChanMatColor((GXChannelID)4, *color);
    GXSetLineWidth(8, GX_TO_ZERO);
    GXCallDisplayList(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
}

/*
 * --INFO--
 * PAL Address: 0x80018894
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawSphere(float (*mtx)[4], Vec* pos, Vec* scale, _GXColor* color)
{
    Mtx sphereMtx;

    PSMTXScale(sphereMtx, scale->x, scale->y, scale->z);
    sphereMtx[0][3] = pos->x;
    sphereMtx[1][3] = pos->y;
    sphereMtx[2][3] = pos->z;
    PSMTXConcat(mtx, sphereMtx, sphereMtx);
    GXLoadPosMtxImm(sphereMtx, 0);
    GXSetChanMatColor((GXChannelID)4, *color);
    GXSetLineWidth(8, GX_TO_ZERO);
    GXCallDisplayList(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
}

/*
 * --INFO--
 * PAL Address: 0x80018764
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawSphere(float (*mtx)[4], _GXColor color)
{
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 5, 1);
    GXSetZCompLoc(GX_FALSE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxAttrFmt(GX_VTXFMT0, (GXAttr)9, (GXCompCnt)1, GX_F32, 0);
    GXLoadPosMtxImm(mtx, 0);
    GXSetChanMatColor((GXChannelID)4, color);
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetLineWidth(8, GX_TO_ZERO);
    GXCallDisplayList(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
}

/*
 * --INFO--
 * PAL Address: 0x80018300
 * PAL Size: 1124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::makeSphere()
{
    float vertices[126];
    int vertexCount = 1;

    vertices[0] = 1.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int ring = 0; ring < 5; ring++) {
        float pitch = (3.1415927f * (float)(ring + 1)) / 6.0f;
        float x = cosf(pitch);
        float radius = sinf(pitch);

        for (int seg = 0; seg < 8; seg++) {
            float yaw = (6.2831855f * (float)seg) / 8.0f;
            vertices[vertexCount * 3 + 0] = x;
            vertices[vertexCount * 3 + 1] = radius * sinf(yaw);
            vertices[vertexCount * 3 + 2] = radius * cosf(yaw);
            vertexCount++;
        }
    }

    vertices[vertexCount * 3 + 0] = -1.0f;
    vertices[vertexCount * 3 + 1] = 0.0f;
    vertices[vertexCount * 3 + 2] = 0.0f;

    S32At(this, 0x71F8) = 0x880;
    PtrAt(this, 0x71FC) = __nwa__FUlPQ27CMemory6CStagePci(S32At(this, 0x71F8),
                                                           reinterpret_cast<CMemory::CStage*>(PtrAt(this, 4)),
                                                           lbl_801D6348, 0x41A);

    DCInvalidateRange(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
    GXBeginDisplayList(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
    GXBegin(GX_QUADS, GX_VTXFMT0, 0xB0);

    int ringStart = 1;
    for (int ring = 0; ring < 5; ring++) {
        int base = ringStart * 3;
        for (int pair = 0; pair < 4; pair++) {
            int next0 = ringStart + ((pair * 2 + 1) & 7);
            int next1 = ringStart + ((pair * 2 + 2) & 7);
            int nextBase = base + 3;

            GXWGFifo.f32 = vertices[base + 1];
            GXWGFifo.f32 = vertices[base + 0];
            GXWGFifo.f32 = vertices[base + 2];

            GXWGFifo.f32 = vertices[next0 * 3 + 1];
            GXWGFifo.f32 = vertices[next0 * 3 + 0];
            GXWGFifo.f32 = vertices[next0 * 3 + 2];

            GXWGFifo.f32 = vertices[nextBase + 1];
            GXWGFifo.f32 = vertices[nextBase + 0];
            GXWGFifo.f32 = vertices[nextBase + 2];

            GXWGFifo.f32 = vertices[next1 * 3 + 1];
            GXWGFifo.f32 = vertices[next1 * 3 + 0];
            GXWGFifo.f32 = vertices[next1 * 3 + 2];

            base += 6;
        }
        ringStart += 8;
    }

    for (int seg = 0; seg < 8; seg++) {
        int ringOffset = 0;
        int ringPairBase = 1;
        for (int ringPair = 0; ringPair < 3; ringPair++) {
            int idx0 = ringOffset == 0 ? 0 : (ringOffset - 1) * 8 + seg + 1;
            int idx1 = ringOffset * 8 + seg + 1;

            int idx2 = 0x29;
            if (ringOffset != 5) {
                idx2 = seg + ringPairBase;
            }

            int idx3 = 0x29;
            if (ringOffset != 4) {
                idx3 = seg + ringPairBase + 8;
            }

            GXWGFifo.f32 = vertices[idx0 * 3 + 1];
            GXWGFifo.f32 = vertices[idx0 * 3 + 0];
            GXWGFifo.f32 = vertices[idx0 * 3 + 2];

            GXWGFifo.f32 = vertices[idx2 * 3 + 1];
            GXWGFifo.f32 = vertices[idx2 * 3 + 0];
            GXWGFifo.f32 = vertices[idx2 * 3 + 2];

            GXWGFifo.f32 = vertices[idx1 * 3 + 1];
            GXWGFifo.f32 = vertices[idx1 * 3 + 0];
            GXWGFifo.f32 = vertices[idx1 * 3 + 2];

            GXWGFifo.f32 = vertices[idx3 * 3 + 1];
            GXWGFifo.f32 = vertices[idx3 * 3 + 0];
            GXWGFifo.f32 = vertices[idx3 * 3 + 2];

            ringPairBase += 0x10;
            ringOffset += 2;
        }
    }

    S32At(this, 0x71F8) = GXEndDisplayList();
    DCFlushRange(PtrAt(this, 0x71FC), S32At(this, 0x71F8));
}

/*
 * --INFO--
 * PAL Address: 0x80017f6c
 * PAL Size: 916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawBound(CBound& bound, _GXColor color)
{
    float* box = reinterpret_cast<float*>(&bound);
    _GXColor materialColor = color;
    _GXColor ambientColor = color;
    Mtx cameraMtx;

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_FALSE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    GXLoadPosMtxImm(cameraMtx, GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, materialColor);
    GXSetChanAmbColor(GX_COLOR0A0, ambientColor);

    GXBegin(GX_LINES, GX_VTXFMT7, 0x18);
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[1];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[0];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[5];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[2];
    GXWGFifo.f32 = box[3];
    GXWGFifo.f32 = box[4];
    GXWGFifo.f32 = box[5];
}

/*
 * --INFO--
 * PAL Address: 0x80017f48
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetFogColor(_GXColor color)
{
    U8At(this, 0x7200) = color.r;
    U8At(this, 0x7201) = color.g;
    U8At(this, 0x7202) = color.b;
    U8At(this, 0x7203) = color.a;
}

/*
 * --INFO--
 * PAL Address: 0x80017f3c
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetFogParam(float startZ, float endZ)
{
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x7204) = startZ;
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x7208) = endZ;
}

/*
 * --INFO--
 * PAL Address: 0x80017ea8
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetFog(int useFog, int useGlobalColor)
{
    float nearZ = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0x100);
    float farZ = *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0x104);
    _GXColor color = useGlobalColor == 0 ? *reinterpret_cast<_GXColor*>(reinterpret_cast<u8*>(this) + 0x7200) : DAT_8032e3e8;
    GXFogType fogType = useFog == 0 ? GX_FOG_NONE : GX_FOG_LIN;

    GXSetFog(fogType,
             *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x7204),
             *reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + 0x7208),
             nearZ, farZ, color);
}

/*
 * --INFO--
 * PAL Address: 0x80017dfc
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::CopySaveFrameBuffer()
{
    GXSetTexCopySrc(0, 0, 0x280, 0x1C0);
    GXSetTexCopyDst(0x280, 0x1C0, GX_TF_I8, GX_FALSE);
    GXCopyTex(PtrAt(this, 0x71EC), GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(reinterpret_cast<GXTexObj*>(reinterpret_cast<u8*>(this) + 0x722C),
                 PtrAt(this, 0x71EC), 0x280, 0x1C0, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(reinterpret_cast<GXTexObj*>(reinterpret_cast<u8*>(this) + 0x722C),
                    GX_NEAR, GX_NEAR, FLOAT_8032f6c0, FLOAT_8032f6c0, FLOAT_8032f6c0,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
}

/*
 * --INFO--
 * PAL Address: 0x80017b30
 * PAL Size: 716b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::GetBackBufferRect(int& x, int& y, int& width, int& height, int doClear)
{
    if (((x & 1) ^ (x >> 31)) != (x >> 31)) {
        x -= 1;
    }
    if (((y & 1) ^ (y >> 31)) != (y >> 31)) {
        y -= 1;
    }

    int xEnd = x + width;
    int yEnd = y + height;

    if (((xEnd & 1) ^ (xEnd >> 31)) != (xEnd >> 31)) {
        xEnd += 1;
        width += 1;
    }
    if (((yEnd & 1) ^ (yEnd >> 31)) != (yEnd >> 31)) {
        yEnd += 1;
        height += 1;
    }

    if ((xEnd < 0) || (yEnd < 0)) {
        return;
    }

    void* renderMode = PtrAt(this, 0x71E0);
    int efbWidth = static_cast<int>(U16At(renderMode, 4));
    int efbHeight = static_cast<int>(U16At(renderMode, 6));

    if ((x > efbWidth) || (y > efbHeight) || (width <= 0) || (height <= 0)) {
        return;
    }

    if (xEnd > efbWidth) {
        width -= (xEnd - efbWidth);
        xEnd = efbWidth;
    }

    if (x < 0) {
        width += x;
        x = 0;
    }

    if (y < 0) {
        height += y;
        y = 0;
    }

    if (yEnd > efbHeight) {
        height -= (yEnd - efbHeight);
        yEnd = efbHeight;
    }

    if ((xEnd == x) || (yEnd == y)) {
        return;
    }

    int texFormat = 6;
    int textureSize = width * height * 4;
    int maxTextureSize = (((efbWidth + 0xF) & 0xFFF0) * efbHeight * 2) + 0x46000;
    if (maxTextureSize < textureSize) {
        texFormat = 4;
        textureSize /= 2;
    }

    GXSetTexCopySrc(x & 0xFFFF, y & 0xFFFF, width & 0xFFFF, height & 0xFFFF);
    GXSetTexCopyDst(width & 0xFFFF, height & 0xFFFF, static_cast<_GXTexFmt>(texFormat), GX_FALSE);
    DCInvalidateRange(PtrAt(this, 0x71E8), textureSize);
    GXCopyTex(PtrAt(this, 0x71E8), doClear);
    GXPixModeSync();
    GXInvalidateTexAll();
    GXInitTexObj(reinterpret_cast<_GXTexObj*>(reinterpret_cast<u8*>(this) + 0x720C), PtrAt(this, 0x71E8), width & 0xFFFF,
                 height & 0xFFFF, static_cast<_GXTexFmt>(texFormat), GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(reinterpret_cast<_GXTexObj*>(reinterpret_cast<u8*>(this) + 0x720C), GX_LINEAR, GX_LINEAR, FLOAT_8032f6c0,
                    FLOAT_8032f6c0, FLOAT_8032f6c0, GX_FALSE, GX_FALSE, GX_ANISO_1);
}

/*
 * --INFO--
 * PAL Address: 0x80017980
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::GetBackBufferRect2(void* dstBuffer, _GXTexObj* texObj, int x, int y, int width, int height, int dstOffset,
                                  _GXTexFilter filter, _GXTexFmt format, int doClear)
{
    int xEnd = x + width;
    int yEnd = y + height;
    if ((xEnd < 0) || (yEnd < 0)) {
        return;
    }

    void* renderMode = PtrAt(this, 0x71E0);
    int efbWidth = static_cast<int>(U16At(renderMode, 4));
    int efbHeight = static_cast<int>(U16At(renderMode, 6));

    if ((x > efbWidth) || (y > efbHeight) || (width <= 0) || (height <= 0) || (xEnd == x) || (yEnd == y)) {
        return;
    }

    int textureSize = GXGetTexBufferSize(width & 0xFFFF, height & 0xFFFF, format, GX_FALSE, GX_FALSE);
    void* textureBase = reinterpret_cast<void*>((reinterpret_cast<u32>(dstBuffer) + ((dstOffset + 0x1F) & 0xFFFFFFE0) + 0x1F) &
                                                0xFFFFFFE0);

    GXSetTexCopySrc(x & 0xFFFF, y & 0xFFFF, width & 0xFFFF, height & 0xFFFF);
    GXSetTexCopyDst(width & 0xFFFF, height & 0xFFFF, format, GX_FALSE);
    DCInvalidateRange(textureBase, textureSize);
    GXCopyTex(textureBase, doClear);
    GXPixModeSync();
    GXInvalidateTexAll();

    int initFormat = format;
    switch (format) {
    case GX_CTF_R4:
    case GX_CTF_RA4:
        initFormat = 0;
        break;
    case GX_CTF_RA8:
    case GX_CTF_A8:
    case GX_CTF_R8:
    case GX_CTF_G8:
    case GX_CTF_B8:
        initFormat = 1;
        break;
    case GX_CTF_RG8:
    case GX_CTF_GB8:
        initFormat = 3;
        break;
    default:
        break;
    }

    if (texObj != nullptr) {
        GXInitTexObj(texObj, textureBase, width & 0xFFFF, height & 0xFFFF, static_cast<_GXTexFmt>(initFormat), GX_CLAMP,
                     GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(texObj, filter, filter, FLOAT_8032f6c0, FLOAT_8032f6c0, FLOAT_8032f6c0, GX_FALSE, GX_FALSE,
                        GX_ANISO_1);
    }
}

/*
 * --INFO--
 * PAL Address: 800178a4
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::RenderTexQuadGrouad(Vec pos1, Vec pos2, _GXColor color1, _GXColor color2, _GXColor color3, _GXColor color4)
{
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);

	GXWGFifo.f32 = pos1.x;
	GXWGFifo.f32 = pos1.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color1;
	GXWGFifo.f32 = FLOAT_8032f6c0;
	GXWGFifo.f32 = FLOAT_8032f6c0;

	GXWGFifo.f32 = pos2.x;
	GXWGFifo.f32 = pos1.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color2;
	GXWGFifo.f32 = FLOAT_8032f6c4;
	GXWGFifo.f32 = FLOAT_8032f6c0;

	GXWGFifo.f32 = pos2.x;
	GXWGFifo.f32 = pos2.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color4;
	GXWGFifo.f32 = FLOAT_8032f6c4;
	GXWGFifo.f32 = FLOAT_8032f6c4;

	GXWGFifo.f32 = pos1.x;
	GXWGFifo.f32 = pos2.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color3;
	GXWGFifo.f32 = FLOAT_8032f6c0;
	GXWGFifo.f32 = FLOAT_8032f6c4;
}

/*
 * --INFO--
 * PAL Address: 800177f0
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::RenderNoTexQuadGrouad(Vec pos1, Vec pos2, _GXColor color1, _GXColor color2, _GXColor color3, _GXColor color4)
{
	GXBegin(GX_QUADS, GX_VTXFMT6, 4);

	GXWGFifo.f32 = pos1.x;
	GXWGFifo.f32 = pos1.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color1;

	GXWGFifo.f32 = pos2.x;
	GXWGFifo.f32 = pos1.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color2;

	GXWGFifo.f32 = pos2.x;
	GXWGFifo.f32 = pos2.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color4;

	GXWGFifo.f32 = pos1.x;
	GXWGFifo.f32 = pos2.y;
	GXWGFifo.f32 = pos1.z;
	GXWGFifo.u32 = *(u32*)&color3;
}

/*
 * --INFO--
 * PAL Address: 0x80016fb0
 * PAL Size: 2112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::RenderDOF(signed char mode, signed char blurWidth, float nearDist, float farDist, Vec targetPos, int blurPasses)
{
	_GXTexObj smallBackTex;
	_GXTexObj backBufferTex;
	_GXColor dofColor;
	Vec cameraPos;
	Vec cameraToTarget;
	Vec scaledDir;
	Vec quadMin;
	Vec quadMax;
	float gxProjection[7];
	float gxViewport[6];
	Mtx cameraMtx;
	float projX;
	float projY;
	float projZ;
	unsigned int texBufferSize;
	unsigned int depthAlphaNear;
	unsigned int depthAlphaFar;
	unsigned char nearAlpha;
	unsigned char farAlpha;
	float xOffset;
	float yOffset;
	bool hasNearAlpha;
	bool hasFarAlpha;

	if (mode >= 4) {
		return;
	}

	if (nearDist < 0.0f) {
		nearDist = 0.0f;
	}
	if (nearDist > 1.0f) {
		nearDist = 1.0f;
	}
	if (farDist < nearDist) {
		farDist = nearDist;
	}
	if (blurWidth < 1) {
		blurWidth = 1;
	}

	nearAlpha = 0;
	farAlpha = 0;
	hasNearAlpha = false;
	hasFarAlpha = false;
	texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

	cameraPos.x = CameraPcs._224_4_;
	cameraPos.y = 0.0f;
	cameraPos.z = CameraPcs._232_4_;

	targetPos.y = 0.0f;
	PSVECSubtract(&targetPos, &cameraPos, &cameraToTarget);

	GXGetProjectionv(gxProjection);
	GXGetViewportv(gxViewport);
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

	if (mode != 2) {
		PSVECScale(&cameraToTarget, &scaledDir, nearDist);
		GXProject(cameraPos.x + scaledDir.x, targetPos.y, cameraPos.z + scaledDir.z, cameraMtx, gxProjection,
		          gxViewport, &projX, &projY, &projZ);

		depthAlphaNear = (unsigned int)(projZ * 255.0f);
		if (depthAlphaNear > 0xFF) {
			depthAlphaNear = 0xFF;
		}
		nearAlpha = (unsigned char)depthAlphaNear;
		hasNearAlpha = true;
	}

	if (mode != 1) {
		float targetMag = PSVECMag(&cameraToTarget);
		if (targetMag > 0.0f) {
			PSVECScale(&cameraToTarget, &scaledDir, farDist / targetMag);
		} else {
			scaledDir.x = 0.0f;
			scaledDir.y = 0.0f;
			scaledDir.z = 0.0f;
		}

		GXProject(targetPos.x + scaledDir.x, targetPos.y, targetPos.z + scaledDir.z, cameraMtx, gxProjection,
		          gxViewport, &projX, &projY, &projZ);

		depthAlphaFar = (unsigned int)(projZ * 255.0f);
		if (depthAlphaFar == 0) {
			depthAlphaFar = 0xFF;
		}
		if (depthAlphaFar > 0xFF) {
			depthAlphaFar = 0xFF;
		}
		farAlpha = (unsigned char)depthAlphaFar;
		hasFarAlpha = true;
	}

	if (!hasNearAlpha) {
		nearAlpha = 0;
	}
	if (!hasFarAlpha) {
		farAlpha = 0xFF;
	}

	DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
	CreateSmallBackTexture(DAT_80238030, &smallBackTex, 0x140, 0xE0, GX_NEAR, GX_TF_I8, 0);
	GetBackBufferRect2(DAT_80238030, &backBufferTex, 0, 0, 0x280, 0x1C0, texBufferSize, GX_NEAR, (_GXTexFmt)0x11, 0);
	DAT_8032ec70.SetVtxFmt_POS_CLR_TEX0_TEX1();
	DAT_8032ec70.SetOrthoEnv();

	xOffset = (float)blurWidth;
	yOffset = xOffset * (224.0f / 640.0f);

	for (int pass = 0; pass < 2; pass++) {
		int kColorSel = 0x0C;
		int kAlphaSel = 0x1C;
		unsigned char passAlpha = nearAlpha;

		if ((pass == 0) && !((mode != 2) && hasNearAlpha && (mode != 1) && hasFarAlpha)) {
			continue;
		}

		if (pass != 0) {
			kColorSel = 0x0D;
			kAlphaSel = 0x1D;
			passAlpha = farAlpha;
		}

		dofColor.r = passAlpha;
		dofColor.g = passAlpha;
		dofColor.b = passAlpha;
		dofColor.a = passAlpha;
		GXSetTevKColor((GXTevKColorID)pass, dofColor);

		dofColor.a = 0x80;
		GXSetChanAmbColor(GX_COLOR0A0, dofColor);
		GXSetChanMatColor(GX_COLOR0A0, dofColor);

		_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 5);

		GXSetTevDirect(GX_TEVSTAGE0);
		GXLoadTexObj(&backBufferTex, GX_TEXMAP0);
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
		_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
		GXSetTevKColorSel(GX_TEVSTAGE0, (GXTevKColorSel)kColorSel);
		GXSetTevKAlphaSel(GX_TEVSTAGE0, (GXTevKAlphaSel)kAlphaSel);

		if (pass == 0) {
			_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0,
			                                                                                                         0x0E, 8,
			                                                                                                         0x0C,
			                                                                                                         0x0F);
		} else {
			_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 8,
			                                                                                                         0x0E,
			                                                                                                         0x0C,
			                                                                                                         0x0F);
		}
		_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 8, 0, 0, 1, 0);
		_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 4, 6, 6,
		                                                                                                       7);
		_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 8, 0, 0, 1, 0);

		GXSetTevDirect(GX_TEVSTAGE1);
		GXLoadTexObj(&smallBackTex, GX_TEXMAP1);
		GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, 0x7D);
		_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 1, 1, 4);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
		_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0x0F,
		                                                                                                       0x0F, 0x0F,
		                                                                                                       8);
		_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
		_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 5, 0,
		                                                                                                       7);
		_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);

		GXSetNumTevStages(2);
		GXSetNumTexGens(2);

		quadMin.x = 0.0f;
		quadMin.y = 0.0f;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f;
		quadMax.y = 224.0f;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = -xOffset;
		quadMin.y = 0.0f;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f - xOffset;
		quadMax.y = 224.0f;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = xOffset;
		quadMin.y = 0.0f;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f + xOffset;
		quadMax.y = 224.0f;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = 0.0f;
		quadMin.y = -yOffset;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f;
		quadMax.y = 224.0f - yOffset;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);

		quadMin.x = 0.0f;
		quadMin.y = yOffset;
		quadMin.z = 0.0f;
		quadMax.x = 640.0f;
		quadMax.y = 224.0f + yOffset;
		quadMax.z = 0.0f;
		DAT_8032ec70.RenderQuadTex2(quadMin, quadMax, dofColor, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80016968
 * PAL Size: 1608b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::CreateSmallBackTexture(void* src, _GXTexObj* texObj, long width, long height, _GXTexFilter filter, _GXTexFmt format,
                                      unsigned long textureSize)
{
    _GXTexObj tempTex;
    Vec quadMin;
    Vec quadMax;
    _GXColor white;
    Mtx cameraMtx;
    float projection[7];
    int halfWidth = static_cast<int>(width) / 2;
    int halfHeight = static_cast<int>(height) / 2;

    DAT_8032ec70.SetOrthoEnv();
    DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
    DAT_8032ec70.DisableIndMtx();

    GXSetNumChans(1);
    GXSetZCompLoc(0);
    GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 5, 1);
    GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 5, 1);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);

    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;

    GetBackBufferRect2(PtrAt(this, 0x71E8), &tempTex, 0, 0, 0x140, 0xE0, 0x46000, filter, GX_TF_I8, 0);
    GXLoadTexObj(&tempTex, GX_TEXMAP0);
    quadMin.x = 0.0f;
    quadMin.y = 0.0f;
    quadMin.z = 0.0f;
    quadMax.x = static_cast<float>(halfWidth);
    quadMax.y = static_cast<float>(halfHeight);
    quadMax.z = 0.0f;
    DAT_8032ec70.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(PtrAt(this, 0x71E8), texObj, 0x140, 0, 0x140, 0xE0, 0, filter, format, 0);
    GXLoadTexObj(texObj, GX_TEXMAP0);
    quadMin.x = static_cast<float>(halfWidth);
    quadMin.y = 0.0f;
    quadMin.z = 0.0f;
    quadMax.x = static_cast<float>(width);
    quadMax.y = static_cast<float>(halfHeight);
    quadMax.z = 0.0f;
    DAT_8032ec70.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(PtrAt(this, 0x71E8), texObj, 0, 0xE0, 0x140, 0xE0, 0, filter, format, 0);
    GXLoadTexObj(texObj, GX_TEXMAP0);
    quadMin.x = 0.0f;
    quadMin.y = static_cast<float>(halfHeight);
    quadMin.z = 0.0f;
    quadMax.x = static_cast<float>(halfWidth);
    quadMax.y = static_cast<float>(height);
    quadMax.z = 0.0f;
    DAT_8032ec70.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(PtrAt(this, 0x71E8), texObj, 0x140, 0xE0, 0x140, 0xE0, 0, filter, format, 0);
    GXLoadTexObj(texObj, GX_TEXMAP0);
    quadMin.x = static_cast<float>(halfWidth);
    quadMin.y = static_cast<float>(halfHeight);
    quadMin.z = 0.0f;
    quadMax.x = static_cast<float>(width);
    quadMax.y = static_cast<float>(height);
    quadMax.z = 0.0f;
    DAT_8032ec70.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(src, texObj, 0, 0, static_cast<int>(width), static_cast<int>(height), textureSize, filter, format, 0);
    GXLoadTexObj(&tempTex, GX_TEXMAP0);
    quadMin.x = 0.0f;
    quadMin.y = 0.0f;
    quadMin.z = 0.0f;
    quadMax.x = 1.0f;
    quadMax.y = 1.0f;
    quadMax.z = 0.0f;
    DAT_8032ec70.RenderQuad(quadMin, quadMax, white, 0, 0);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    GXGetProjectionv(projection);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjectionv(projection);
}

/*
 * --INFO--
 * PAL Address: 0x80016950
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::InitBlurParameter()
{
    U8At(this, 0x735D) = 0;
    U8At(this, 0x735E) = 0;
    U8At(this, 0x735C) = 0xE8;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::RenderBlur(int unused0, unsigned char mode, unsigned char unused2, unsigned char textureDelay,
                          unsigned char alpha, short offset)
{
    _GXTexObj texObj;
    _GXColor blurColor;
    Vec quadMin;
    Vec quadMax;
    Mtx identity;

    (void)unused0;
    (void)unused2;

    DAT_8032ec70.DisableIndMtx();
    DAT_8032ec70.SetOrthoEnv();
    DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);

    blurColor.r = 0x80;
    blurColor.g = 0x80;
    blurColor.b = 0x80;
    blurColor.a = alpha;
    GXSetChanAmbColor(GX_COLOR0A0, blurColor);
    GXSetChanMatColor(GX_COLOR0A0, blurColor);

    DAT_8032ec70.SetOrthoEnv();
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 0xF,
                                                                                                           0xF, 8);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 7, 7,
                                                                                                           5);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);

    for (int i = 0; i < static_cast<int>(U8At(this, 0x735E)); i++) {
        u8* textureBase = reinterpret_cast<u8*>(PtrAt(this, 0x71EC)) + i * 0x46000;
        GXInitTexObj(&texObj, textureBase, 0x140, 0xE0, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);

        if (mode == 1) {
            quadMin.x = 0.0f;
            quadMin.y = 0.0f;
            quadMin.z = 0.0f;
            quadMax.x = 640.0f;
            quadMax.y = 448.0f;
            quadMax.z = 0.0f;
            DAT_8032ec70.RenderQuad(quadMin, quadMax, blurColor, 0, 0);
        } else if (mode == 0) {
            float blurOffset = static_cast<float>(offset);
            quadMin.x = -blurOffset;
            quadMin.y = -blurOffset;
            quadMin.z = 0.0f;
            quadMax.x = 640.0f + blurOffset;
            quadMax.y = 448.0f + blurOffset;
            quadMax.z = 0.0f;
            DAT_8032ec70.RenderQuad(quadMin, quadMax, blurColor, 0, 0);
        }
    }

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(reinterpret_cast<f32(*)[4]>(reinterpret_cast<u8*>(this) + 0x73A4), GX_ORTHOGRAPHIC);
    GXSetAlphaUpdate(GX_TRUE);

    if (U8At(this, 0x735C) < textureDelay) {
        U8At(this, 0x735C) += 1;
    } else if (System.m_scenegraphStepMode != 2) {
        CreateSmallBackTexture(PtrAt(this, 0x71EC), &texObj, 0x140, 0xE0, GX_NEAR, GX_TF_I8,
                               static_cast<unsigned long>(U8At(this, 0x735D)) * 0x46000);
        U8At(this, 0x735C) = 0;
        U8At(this, 0x735E) += 1;
        if (U8At(this, 0x735E) > 2) {
            U8At(this, 0x735E) = 2;
        }
        U8At(this, 0x735D) += 1;
        if (U8At(this, 0x735D) > 1) {
            U8At(this, 0x735D) = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::CreateTempBuffer()
{
	u32 bufferSize = ((U16At(PtrAt(this, 0x71E0), 4) + 0xF) & 0xFFF0) * U16At(PtrAt(this, 0x71E0), 6) * 2 + 0x46000;
	u8* tempBuffer = reinterpret_cast<u8*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
	    &Memory, bufferSize, reinterpret_cast<CMemory::CStage*>(PtrAt(this, 0x8)), lbl_801D6348, 0xB53, 0));

	PtrAt(this, 0x71E8) = tempBuffer;
	memset(tempBuffer, 0, 0x46004);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DestroyTempBuffer()
{
	if (PtrAt(this, 0x71E8) != nullptr) {
		__dla__FPv(PtrAt(this, 0x71E8));
		PtrAt(this, 0x71E8) = nullptr;
	}
}
