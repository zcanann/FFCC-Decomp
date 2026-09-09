#include "ffcc/graphic.h"
#include "global.h"
#include "ffcc/graphic_symbols.h"
#include "ffcc/gxfunc.h"

#include <math.h>
#include <stdarg.h>
#include <string.h>

#include "ffcc/memory.h"
#include "ffcc/memorycard.h"
#include "ffcc/file.h"
#include "ffcc/pad.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppfunctbl.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "dolphin/vi.h"
#include "dolphin/vi/vifuncs.h"

CGraphic Graphic;

GXRenderModeObj _GXPal528IntDf = {
    VI_TVMODE_PAL_INT,
    640, 448, 528,
    40, 23,
    640, 528,
    VI_XFBMODE_DF,
    GX_FALSE, GX_FALSE,
    {
        {6, 6}, {6, 6}, {6, 6}, {6, 6},
        {6, 6}, {6, 6}, {6, 6}, {6, 6},
        {6, 6}, {6, 6}, {6, 6}, {6, 6}
    },
    {8, 8, 10, 12, 10, 8, 8}
};

extern "C" {
OSThread m_thread;
u8 m_threadStack[0x4000] ATTRIBUTE_ALIGN(8);
}

enum GraphicCppStringOffset {
    kGraphicInitCGraphic = 0xA0,
    kGraphicInitSource = 0xB8,
    kGraphicInitCGraphic2 = 0x1F8,
    kGraphicCppPartControlDoneFmt = 0xEC,
    kGraphicCppPartCharaDoneFmt = 0x130,
    kGraphicCppPartDoneFmt = 0x170,
    kGraphicCppDrawDoneFmt = 0x1AC,
};

static inline float LoadFloat(const float& value) {
    return value;
}


extern const float kGraphicZeroF = 0.0f;
extern const float kGraphicOneF = 1.0f;
extern const float FLOAT_8032F6C8 = 640.0f;
extern const float FLOAT_8032F6CC = 448.0f;
extern const float kGraphicSphereNegativeX = -1.0f;
extern const double kGraphicHalfF64 = 4503599627370496.0;
extern const float kGraphicSpherePi = 3.1415927410125732f;
extern const double DOUBLE_8032F6E8 = 4503601774854144.0;
extern const float kGraphicSmallBackTextureWidth = 320.0f;
extern const float kGraphicSmallBackTextureHeight = 224.0f;
extern const float FLOAT_8032F6F8 = 16777215.0f;
extern const float FLOAT_8032F6FC = 0.7f;
extern const float kGraphicSphereRingDivisor = 6.0f;
extern const float kGraphicSphereSegmentAngle = 0.7853981852531433f;
extern const float kGraphicBlurAlphaScale = -100.0f;
extern const float kGraphicNoiseTexScaleU = 0.015625f;
extern const float kGraphicNoiseTexScaleV = 0.010416667163372f;
extern const char sGraphicUnknownOrderName[4] = "---";

struct GraphicSleepAlarm {
    OSAlarm alarm;
    OSThread* thread;
};

STATIC_ASSERT(offsetof(CGraphic, m_renderMode) == 0x71E0);
STATIC_ASSERT(offsetof(CGraphic, m_graphicStage) == 0x4);
STATIC_ASSERT(offsetof(CGraphic, m_scratchStage) == 0x8);
STATIC_ASSERT(offsetof(CGraphic, m_frameReady) == 0xC);
STATIC_ASSERT(offsetof(CGraphic, m_fifoBuffer) == 0x10);
STATIC_ASSERT(offsetof(CGraphic, m_debugStringCount) == 0x14);
STATIC_ASSERT(offsetof(CGraphic, m_debugStringPositions) == 0x18);
STATIC_ASSERT(offsetof(CGraphic, m_debugStrings) == 0x1E0);
STATIC_ASSERT(offsetof(CGraphic, m_frameBuffer) == 0x71E4);
STATIC_ASSERT(offsetof(CGraphic, m_scratchTextureBuffer) == 0x71E8);
STATIC_ASSERT(offsetof(CGraphic, m_savedFrameBuffer) == 0x71EC);
STATIC_ASSERT(offsetof(CGraphic, m_displayCopyEnabled) == 0x71F0);
STATIC_ASSERT(offsetof(CGraphic, m_lastRetraceCount) == 0x71F4);
STATIC_ASSERT(offsetof(CGraphic, m_sphereDisplayListSize) == 0x71F8);
STATIC_ASSERT(offsetof(CGraphic, m_sphereDisplayList) == 0x71FC);
STATIC_ASSERT(offsetof(CGraphic, m_fogColor) == 0x7200);
STATIC_ASSERT(offsetof(CGraphic, m_fogStart) == 0x7204);
STATIC_ASSERT(offsetof(CGraphic, m_fogEnd) == 0x7208);
STATIC_ASSERT(offsetof(CGraphic, m_fifoIndex) == 0x734C);
STATIC_ASSERT(offsetof(CGraphic, m_frameRateOver) == 0x7350);
STATIC_ASSERT(offsetof(CGraphic, m_debugStringVisible) == 0x7354);
STATIC_ASSERT(offsetof(CGraphic, m_defaultCopyClearColor) == 0x735F);
STATIC_ASSERT(offsetof(CGraphic, m_drawDoneWaiting) == 0x7364);
STATIC_ASSERT(offsetof(CGraphic, m_drawDoneFile) == 0x7368);
STATIC_ASSERT(offsetof(CGraphic, m_drawDoneLine) == 0x736C);
STATIC_ASSERT(offsetof(CGraphic, m_drawDoneCounter) == 0x7370);

extern "C" {
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
 * PAL Address: 0x80019b54
 * PAL Size: 1000b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::Init()
{
    char* graphicInitData = const_cast<char*>(sGraphicInitData);

    m_graphicStage = Memory.CreateStage(0x19C000, graphicInitData + kGraphicInitCGraphic, 0);
    m_scratchStage = Memory.CreateStage(0xD6000, graphicInitData + kGraphicInitCGraphic2, 0);

    m_debugStringCount = 0;
    m_fogColor.r = 0;
    m_fogColor.g = 0;
    m_fogColor.b = 0;
    m_fogColor.a = 0;

    m_fogEnd = kGraphicZeroF;
    m_fogStart = kGraphicZeroF;

    m_defaultCopyClearColor.r = m_fogColor.r;
    m_defaultCopyClearColor.g = m_fogColor.g;
    m_defaultCopyClearColor.b = m_fogColor.b;
    m_defaultCopyClearColor.a = m_fogColor.a;
    memset(&m_drawDoneWaiting, 0, 0x10);

    OSCreateThread(&m_thread, reinterpret_cast<void* (*)(void*)>(checkThread), nullptr, m_threadStack + 0x4000, 0x4000, 1, 1);
    OSResumeThread(&m_thread);

    VIInit();
    m_renderMode = &_GXPal528IntDf;
    m_displayCopyEnabled = 1;

    GXRenderModeObj* renderMode = m_renderMode;
    u32 alignedWidth = (renderMode->fbWidth + 0xF) & 0xFFF0;
    u16 efbHeight = renderMode->efbHeight;
    u16 xfbHeight = renderMode->xfbHeight;
    u32 efbBufferSize = alignedWidth * efbHeight * 2;
    u32 xfbBufferSize = alignedWidth * xfbHeight * 2;

    m_frameBuffer = new (m_graphicStage, graphicInitData + kGraphicInitSource, 0x86) u8[xfbBufferSize];
    memset(m_frameBuffer, 0, 4);

    m_savedFrameBuffer = new (m_graphicStage, graphicInitData + kGraphicInitSource, 0x88) u8[efbBufferSize];
    memset(m_savedFrameBuffer, 0, 4);

    u32 scratchBufferSize = (((m_renderMode->fbWidth + 0xF) & 0xFFF0) * m_renderMode->efbHeight * 2) + 0x46000;
    m_scratchTextureBuffer = Memory._Alloc(scratchBufferSize, m_scratchStage, graphicInitData + kGraphicInitSource, 0xB53, 0);
    memset(m_scratchTextureBuffer, 0, 0x46004);

    m_fifoBuffer = new (m_graphicStage, graphicInitData + kGraphicInitSource, 0x8B) u8[0x60000];

    VIConfigure(m_renderMode);
    GXInit(m_fifoBuffer, 0x60000);

    GXSetViewport(kGraphicZeroF, kGraphicZeroF, static_cast<f32>(m_renderMode->fbWidth),
                  static_cast<f32>(m_renderMode->efbHeight), kGraphicZeroF, kGraphicOneF);
    GXSetScissor(0, 0, m_renderMode->fbWidth, m_renderMode->efbHeight);
    GXSetDispCopyYScale(GXGetYScaleFactor(m_renderMode->efbHeight, m_renderMode->xfbHeight));
    GXSetDispCopySrc(0, 0, m_renderMode->fbWidth, m_renderMode->efbHeight);
    GXSetDispCopyDst(m_renderMode->fbWidth, m_renderMode->efbHeight);
    GXSetCopyFilter(m_renderMode->aa, m_renderMode->sample_pattern, GX_TRUE, GXNtsc480IntDf.vfilter);

    if (m_renderMode->aa != 0) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }

    GXSetDispCopySrc(0, 0, m_renderMode->fbWidth, m_renderMode->efbHeight);
    GXSetDispCopyDst(m_renderMode->fbWidth, m_renderMode->efbHeight);
    GXCopyDisp(m_frameBuffer, GX_TRUE);
    GXSetDispCopyGamma(GX_GM_1_0);
    VISetNextFrameBuffer(m_frameBuffer);
    VIFlush();
    VIWaitForRetrace();
    if ((m_renderMode->viTVmode & 1) != 0) {
        VIWaitForRetrace();
    }

    m_lastRetraceCount = VIGetRetraceCount();
    m_frameReady = 0;
    m_fifoIndex = 0;
    m_frameRateOver = 0;
    m_debugStringVisible = 0;
    makeSphere();
    m_blurActive = 0;
    m_blurDelayCounter = 0;
    m_blurBufferIndex = 0;
    m_blurTextureCount = 0;
    GXCopyDisp(m_frameBuffer, GX_TRUE);
    m_drawDoneFile = graphicInitData + kGraphicInitSource;
    m_drawDoneLine = 0xBE;
    m_drawDoneWaiting = 1;
    GXSetDrawDone();
    GXWaitDrawDone();
    m_drawDoneWaiting = 0;
    m_drawDoneCounter += 1;
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
    if (m_savedFrameBuffer != nullptr) {
        delete[] reinterpret_cast<u8*>(m_savedFrameBuffer);
        m_savedFrameBuffer = nullptr;
    }
    if (m_frameBuffer != nullptr) {
        delete[] reinterpret_cast<u8*>(m_frameBuffer);
        m_frameBuffer = nullptr;
    }
    if (m_scratchTextureBuffer != nullptr) {
        delete[] reinterpret_cast<u8*>(m_scratchTextureBuffer);
        m_scratchTextureBuffer = nullptr;
    }
    if (m_sphereDisplayList != nullptr) {
        delete[] reinterpret_cast<u8*>(m_sphereDisplayList);
        m_sphereDisplayList = nullptr;
    }
    if (m_fifoBuffer != nullptr) {
        delete[] reinterpret_cast<u8*>(m_fifoBuffer);
        m_fifoBuffer = nullptr;
    }

    Memory.DestroyStage(m_scratchStage);
    Memory.DestroyStage(m_graphicStage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGraphic::GetProgressive()
{
    u32 mode = VIGetDTVStatus();
    if (mode != 0) {
        mode = OSSetSoundMode();
        mode = (static_cast<unsigned int>(__cntlzw(1 - mode)) >> 5) + 1;
    } else {
        mode = 0;
    }
    return mode;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::ChangeProgressive(int mode)
{
    GXRenderModeObj* defaultRenderMode = &_GXPal528IntDf;
    if (m_renderMode != defaultRenderMode) {
        m_renderMode = defaultRenderMode;
        GXAdjustForOverscan(m_renderMode, m_renderMode, 0, 0x10);
        VIConfigure(m_renderMode);
        GXSetCopyFilter(m_renderMode->aa, m_renderMode->sample_pattern, GX_TRUE, _GXPal528IntDf.vfilter);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
    OSGetProgressiveMode(mode);
}

/*
 * --INFO--
 * PAL Address: 0x80019960
 * PAL Size: 84b
 * EN Address: 0x8001E5B8
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetCopyClear(_GXColor color, int)
{
    m_defaultCopyClearColor = color;
    GXSetCopyClear(color, 0xFFFFFF);
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
    GXSetDispCopySrc(0, 0, m_renderMode->fbWidth, m_renderMode->efbHeight);
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
    GXSetDispCopyDst(m_renderMode->fbWidth, m_renderMode->efbHeight);
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
    if (m_renderMode->aa != 0) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
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
    GXSetViewport(kGraphicZeroF, kGraphicZeroF, static_cast<f32>(m_renderMode->fbWidth), static_cast<f32>(m_renderMode->efbHeight),
                  kGraphicZeroF, kGraphicOneF);
    GXSetScissor(0, 0, m_renderMode->fbWidth, m_renderMode->efbHeight);
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
    GXRenderModeObj* renderMode = m_renderMode;
    u16 width = renderMode->fbWidth;
    u16 height = renderMode->efbHeight;
    GXSetViewport(kGraphicZeroF, kGraphicZeroF, (f32)width, (f32)height, kGraphicZeroF, kGraphicOneF);
    GXInvalidateVtxCache();
    GXInvalidateTexAll();

    const bool useDebugPad = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    u16 buttons;
    if (useDebugPad) {
        buttons = 0;
    } else {
        buttons = Pad.GetPadInputs()[0].lockedButton[1];
    }

    if ((buttons & 2) != 0) {
        m_debugStringVisible = !m_debugStringVisible;
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
    m_debugStringCount = 0;
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
    unsigned int token = (unsigned int)System.m_currentOrderIndex << 8;
    token = (token & 0xFFFFFF00) | (u8)drawDoneId;
    GXSetDrawSync(token);
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
    GraphicSleepAlarm* sleepAlarm = reinterpret_cast<GraphicSleepAlarm*>(alarm);
    OSResumeThread(sleepAlarm->thread);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 140b
 * EN Address: 0x8001e988
 * EN Size: 140b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void sleep()
{
    GraphicSleepAlarm sleepAlarm;
    sleepAlarm.thread = OSGetCurrentThread();
    OSCreateAlarm(&sleepAlarm.alarm);
    OSSetAlarmTag(&sleepAlarm.alarm, 1);
    BOOL interrupts = OSDisableInterrupts();
    OSSetAlarm(&sleepAlarm.alarm, (OS_TIMER_CLOCK / 1000) * 0x32, wakeup);
    OSSuspendThread(sleepAlarm.thread);
    OSRestoreInterrupts(interrupts);
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
    m_drawDoneFile = file;
    m_drawDoneLine = line;
    m_drawDoneWaiting = 1;
    GXSetDrawDone();
    GXWaitDrawDone();
    m_drawDoneWaiting = 0;
    m_drawDoneCounter += 1;
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
    char* debugFmtBase = const_cast<char*>(sGraphicInitData);
    int lastCounter = -1;
    int debugCountdown = 5;

    while (true) {
        if (m_drawDoneWaiting != 0) {
            if (lastCounter != m_drawDoneCounter) {
                debugCountdown = 100;
                lastCounter = m_drawDoneCounter;
            }
            debugCountdown--;

            if (debugCountdown == 0) {
                int drawSyncPart = GXReadDrawSync();
                if ((drawSyncPart & 0x8000) != 0) {
                    drawSyncPart &= 0xFFFF;
                    drawSyncPart &= 0x7FFF;
                    if (drawSyncPart == 0x7FFF) {
                        System.Printf(debugFmtBase + kGraphicCppPartControlDoneFmt, m_drawDoneFile, m_drawDoneLine);
                    } else if (drawSyncPart == 0x7FFE) {
                        System.Printf(debugFmtBase + kGraphicCppPartCharaDoneFmt, m_drawDoneFile, m_drawDoneLine);
                    } else {
                        System.Printf(debugFmtBase + kGraphicCppPartDoneFmt, m_drawDoneFile, m_drawDoneLine,
                                      pppSysProgTbl[drawSyncPart].m_pppName);
                    }
                }

                CSystem::COrder* order = System.GetOrder(drawSyncPart >> 8);
                int drawSyncByte = static_cast<int>(static_cast<char>(drawSyncPart));
                int orderIndex = (order != nullptr) ? order->m_insertIndex : -1;
                const char* orderName = (order != nullptr) ? order->m_debugName : sGraphicUnknownOrderName;
                System.Printf(debugFmtBase + kGraphicCppDrawDoneFmt, m_drawDoneFile, m_drawDoneLine, orderName, orderIndex,
                              drawSyncByte);
            }
        } else {
            debugCountdown = 5;
        }

        static int bDown = 0;
        static int bReset = 0;

        if (OSGetResetButtonState() != 0) {
            bDown = 1;
        } else {
            if (bDown != 0) {
                bReset = 1;
            }
        }

        if ((bReset != 0) && (File.m_fatalDiskErrorFlag == 0) && (MemoryCardMan.m_currentSlot == -1)) {
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            OSCancelAlarms(1);
            OSResetSystem(FALSE, 0, FALSE);
            while (true) {}
        }

        sleep();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGraphic::IsFifoOver()
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
int CGraphic::IsFrameRateOver()
{
	return m_frameRateOver;
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
    if (m_frameReady != 0) {
        if (m_displayCopyEnabled != 0) {
            VISetBlack(FALSE);
            m_displayCopyEnabled = 0;
        }

        if (System.m_scenegraphStepMode != 1) {
            int retraceCount = VIGetRetraceCount();
            if ((u32)(retraceCount - m_lastRetraceCount) > 1) {
                m_frameRateOver = 1;
            } else {
                m_frameRateOver = 0;
                while ((u32)((retraceCount = VIGetRetraceCount()) - m_lastRetraceCount) < 2) {
                    VIWaitForRetrace();
                }
            }
        }

        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXCopyDisp(m_frameBuffer, GX_TRUE);
        m_drawDoneFile = const_cast<char*>(sGraphicSourceStrings);
        m_drawDoneLine = 0x26D;
        m_drawDoneWaiting = 1;
        GXSetDrawDone();
        GXWaitDrawDone();
        m_drawDoneWaiting = 0;
        m_drawDoneCounter += 1;
        VIFlush();

        m_fifoIndex = 1 - m_fifoIndex;

        GXInitFifoBase(&m_fifos[m_fifoIndex], m_fifoBuffer, 0x60000);
        GXInitFifoLimits(&m_fifos[m_fifoIndex], 0x5C000, 0x50000);
        GXSetCPUFifo(&m_fifos[m_fifoIndex]);
        GXSetGPFifo(&m_fifos[m_fifoIndex]);
    }

    m_lastRetraceCount = VIGetRetraceCount();

    int frameReady;
    if (System.m_scenegraphStepMode == 1) {
        frameReady = ((u32)__cntlzw(System.m_frameCounter & 3) >> 5) & 0xFF;
    } else {
        frameReady = 1;
    }
    m_frameReady = frameReady;
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
    if (static_cast<u32>(m_debugStringCount) < 0x70) {
        char buffer[248];
        va_list args;
        va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        va_end(args);

        m_debugStringPositions[m_debugStringCount].x = -1;
        m_debugStringPositions[m_debugStringCount].y = -1;
        int index = m_debugStringCount;
        m_debugStringCount = index + 1;
        strcpy(m_debugStrings[index], buffer);
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
    if (static_cast<u32>(m_debugStringCount) < 0x70) {
        char buffer[256];
        va_list args;
        va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        va_end(args);

        m_debugStringPositions[m_debugStringCount].x = static_cast<short>(x);
        m_debugStringPositions[m_debugStringCount].y = static_cast<short>(y);
        int index = m_debugStringCount;
        m_debugStringCount = index + 1;
        strcpy(m_debugStrings[index], buffer);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DrawDebugString()
{
    Mtx model;
    Mtx44 proj;
    Mtx texMtx;
    GXTexObj texObj;

    GXRenderModeObj* renderMode = m_renderMode;
    C_MTXOrtho(proj,
               kGraphicZeroF,
               static_cast<float>(renderMode->efbHeight),
               kGraphicZeroF,
               static_cast<float>(renderMode->fbWidth),
               kGraphicZeroF,
               kGraphicBlurAlphaScale);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCurrentMtx(0);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    _GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetCurrentMtx(0);

    GXInitTexObj(&texObj, gGraphicNoiseTextureI8_64x96, 0x40, 0x60, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, kGraphicZeroF, kGraphicZeroF, kGraphicZeroF, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    PSMTXScale(texMtx, kGraphicNoiseTexScaleU, kGraphicNoiseTexScaleV, kGraphicOneF);
    GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, 0x7D);

    int y;
    u32 i = 0;
    y = 0x10;
    for (; i < static_cast<u32>(m_debugStringCount); ++i) {
        s16 xCell = m_debugStringPositions[i].x;

        if (xCell == -1) {
            DrawDebugStringDirect(0x10, static_cast<u32>(y), m_debugStrings[i], 0xC);
        } else {
            s16 yCell = m_debugStringPositions[i].y;
            DrawDebugStringDirect(static_cast<u32>(xCell * 0xC + 0x10), static_cast<u32>(yCell * 0xC + 0x10), m_debugStrings[i], 0xC);
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
    Mtx texMtx;
    Mtx44 proj;
    Mtx model;
    GXTexObj texObj;

    GXRenderModeObj* renderMode = m_renderMode;
    C_MTXOrtho(proj,
               kGraphicZeroF,
               static_cast<float>(renderMode->efbHeight),
               kGraphicZeroF,
               static_cast<float>(renderMode->fbWidth),
               kGraphicZeroF,
               kGraphicBlurAlphaScale);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCurrentMtx(0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    _GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetCurrentMtx(0);
    GXInitTexObj(&texObj, gGraphicNoiseTextureI8_64x96, 0x40, 0x60, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, kGraphicZeroF, kGraphicZeroF, kGraphicZeroF, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    PSMTXScale(texMtx, kGraphicNoiseTexScaleU, kGraphicNoiseTexScaleV, kGraphicOneF);
    GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, 0x7D);
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

    char* cursor = text;

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xD, (GXAttrType)1);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)9, (GXCompCnt)1, (GXCompType)3, 0);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)0xD, (GXCompCnt)1, (GXCompType)3, 1);

    int count = 0;
    while (true) {
        int ch;
        while (true) {
            ch = *cursor++;
            if (ch < ' ' || ch > 0x7F) {
                break;
            }
            count += 1;
        }

        if (count > 0) {
            int glyph;
            int px;
            int tx;
            int ty;
            GXBegin((GXPrimitive)0x80, (GXVtxFmt)0, (u16)((count & 0x3FFF) << 2));
            for (int i = 0; i < count; i++) {
                glyph = text[i] - 0x20;
                px = x + i * charSize;
                tx = (glyph % 8) * 16;
                ty = (glyph / 8) * 16;

                GXWGFifo.s16 = px;
                GXWGFifo.u16 = y;
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = tx;
                GXWGFifo.s16 = ty;

                GXWGFifo.s16 = (s16)(charSize + px);
                GXWGFifo.s16 = (s16)y;
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = (s16)(tx + 0x10);
                GXWGFifo.s16 = ty;

                GXWGFifo.s16 = (s16)(charSize + px);
                GXWGFifo.s16 = (s16)(y + charSize);
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = (s16)(tx + 0x10);
                GXWGFifo.s16 = (s16)(ty + 0x10);

                GXWGFifo.s16 = px;
                GXWGFifo.s16 = (s16)(y + charSize);
                GXWGFifo.s16 = 0;
                GXWGFifo.s16 = tx;
                GXWGFifo.s16 = (s16)(ty + 0x10);
            }
            count = 0;
        }

        text = cursor;
        if (ch != '\n') {
            break;
        }
        y += charSize;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGraphic::SaveFrameBuffer(char*)
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
    GXCallDisplayList(m_sphereDisplayList, m_sphereDisplayListSize);
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
    GXCallDisplayList(m_sphereDisplayList, m_sphereDisplayListSize);
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
    GXCallDisplayList(m_sphereDisplayList, m_sphereDisplayListSize);
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
    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetZCompLoc(GX_FALSE);
    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxAttrFmt(GX_VTXFMT0, (GXAttr)9, (GXCompCnt)1, GX_F32, 0);
    GXLoadPosMtxImm(mtx, 0);
    GXSetChanMatColor((GXChannelID)4, color);
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetLineWidth(8, GX_TO_ZERO);
    GXCallDisplayList(m_sphereDisplayList, m_sphereDisplayListSize);
}

/*
 * --INFO--
 * PAL Address: 0x80018300
 * PAL Size: 1124b
 * EN Address: 0x8001FCA8
 * EN Size: 892b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::makeSphere()
{
    float vertices[126];
    float* rowVertex;
    float* vertex;

    int vertexCount = 0;
    vertices[0] = kGraphicSphereNegativeX;
    vertices[1] = kGraphicZeroF;
    vertices[vertexCount * 3 + 2] = kGraphicZeroF;

    vertexCount++;
    vertex = &vertices[vertexCount * 3];

    for (int ring = 0; ring < 5; ring++) {
        float pitch = (kGraphicSpherePi * (float)(ring + 1)) / kGraphicSphereRingDivisor;
        float x = kGraphicSphereNegativeX * (float)cos(pitch);
        float radius = kGraphicSphereNegativeX * (float)sin(pitch);

        rowVertex = vertex;
        for (int seg = 0; seg < 8; seg++) {
            rowVertex[0] = x;
            rowVertex[1] = radius * (float)sin(kGraphicSphereSegmentAngle * (float)seg);
            vertices[vertexCount * 3 + 2] = radius * (float)cos(kGraphicSphereSegmentAngle * (float)seg);
            vertex += 3;
            rowVertex += 3;
            vertexCount++;
        }
    }

    m_sphereDisplayListSize = 0x880;
    vertices[vertexCount * 3 + 0] = kGraphicOneF;
    vertices[vertexCount * 3 + 1] = kGraphicZeroF;
    vertices[vertexCount * 3 + 2] = kGraphicZeroF;

    m_sphereDisplayList = new (m_graphicStage, const_cast<char*>(sGraphicSourceStrings), 0x41A) u8[m_sphereDisplayListSize];

    DCInvalidateRange(m_sphereDisplayList, m_sphereDisplayListSize);
    GXBeginDisplayList(m_sphereDisplayList, m_sphereDisplayListSize);
    GXBegin(GX_LINES, GX_VTXFMT0, 0xB0);

    int ring = 0;
    int ringStart = 1;
    for (; ring < 5; ring++) {
        int current = ringStart;
        for (int seg = 0; seg < 8; seg++) {
            GXPosition3f32(vertices[current * 3 + 1], vertices[current * 3], vertices[current * 3 + 2]);
            int next = ringStart + (seg + 1) % 8;
            GXPosition3f32(vertices[next * 3 + 1], vertices[next * 3], vertices[next * 3 + 2]);
            current++;
        }
        ringStart += 8;
    }

    for (int seg = 0; seg < 8; seg++) {
        int ring = 0;
        int ringBase = 1;
        for (; ring < 6; ring++) {
            int current = ring == 0 ? 0 : (ring - 1) * 8 + seg + 1;
            GXPosition3f32(vertices[current * 3 + 1], vertices[current * 3], vertices[current * 3 + 2]);
            int next = ring + 1 == 6 ? 41 : seg + ringBase;
            GXPosition3f32(vertices[next * 3 + 1], vertices[next * 3], vertices[next * 3 + 2]);
            ringBase += 8;
        }
    }

    m_sphereDisplayListSize = GXEndDisplayList();
    DCFlushRange(m_sphereDisplayList, m_sphereDisplayListSize);
}

/*
 * --INFO--
 * PAL Address: 0x80017f6c
 * PAL Size: 916b
 * EN Address: 0x8002007C
 * EN Size: 792b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::DrawBound(CBound& bound, _GXColor color)
{
    Mtx cameraMtx;

    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetZCompLoc(GX_FALSE);
    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    CameraPcs.GetViewMatrix(cameraMtx);
    GXLoadPosMtxImm(cameraMtx, GX_PNMTX0);
    _GXColor materialColor = color;
    GXSetChanMatColor(GX_COLOR0A0, materialColor);
    _GXColor ambientColor = color;
    GXSetChanAmbColor(GX_COLOR0A0, ambientColor);

    GXBegin(GX_LINES, GX_VTXFMT7, 0x18);
    GXPosition3f32(bound.m_min.x, bound.m_min.y, bound.m_min.z);
    GXPosition3f32(bound.m_max.x, bound.m_min.y, bound.m_min.z);
    GXPosition3f32(bound.m_min.x, bound.m_max.y, bound.m_min.z);
    GXPosition3f32(bound.m_max.x, bound.m_max.y, bound.m_min.z);
    GXPosition3f32(bound.m_min.x, bound.m_min.y, bound.m_max.z);
    GXPosition3f32(bound.m_max.x, bound.m_min.y, bound.m_max.z);
    GXPosition3f32(bound.m_min.x, bound.m_max.y, bound.m_max.z);
    GXPosition3f32(bound.m_max.x, bound.m_max.y, bound.m_max.z);
    GXPosition3f32(bound.m_min.x, bound.m_min.y, bound.m_min.z);
    GXPosition3f32(bound.m_min.x, bound.m_max.y, bound.m_min.z);
    GXPosition3f32(bound.m_max.x, bound.m_min.y, bound.m_min.z);
    GXPosition3f32(bound.m_max.x, bound.m_max.y, bound.m_min.z);
    GXPosition3f32(bound.m_min.x, bound.m_min.y, bound.m_max.z);
    GXPosition3f32(bound.m_min.x, bound.m_max.y, bound.m_max.z);
    GXPosition3f32(bound.m_max.x, bound.m_min.y, bound.m_max.z);
    GXPosition3f32(bound.m_max.x, bound.m_max.y, bound.m_max.z);
    GXPosition3f32(bound.m_min.x, bound.m_min.y, bound.m_min.z);
    GXPosition3f32(bound.m_min.x, bound.m_min.y, bound.m_max.z);
    GXPosition3f32(bound.m_max.x, bound.m_min.y, bound.m_min.z);
    GXPosition3f32(bound.m_max.x, bound.m_min.y, bound.m_max.z);
    GXPosition3f32(bound.m_min.x, bound.m_max.y, bound.m_min.z);
    GXPosition3f32(bound.m_min.x, bound.m_max.y, bound.m_max.z);
    GXPosition3f32(bound.m_max.x, bound.m_max.y, bound.m_min.z);
    GXPosition3f32(bound.m_max.x, bound.m_max.y, bound.m_max.z);
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
    m_fogColor = color;
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
    m_fogStart = startZ;
    m_fogEnd = endZ;
}

/*
 * --INFO--
 * PAL Address: 0x80017ea8
 * PAL Size: 148b
 * EN Address: 0x800203D4
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::SetFog(int useFog, int useBlack)
{
    static _GXColor black = {0, 0, 0, 0};
    float nearZ;
    float farZ;
    CameraPcs.GetClip(&nearZ, &farZ);

    GXSetFog(useFog != 0 ? GX_FOG_LIN : GX_FOG_NONE, m_fogStart, m_fogEnd, nearZ, farZ, useBlack != 0 ? black : m_fogColor);
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
    GXSetTexCopyDst(0x280, 0x1C0, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(m_savedFrameBuffer, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&m_smallBackTexObj, m_savedFrameBuffer, 0x280, 0x1C0, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    float zero = LoadFloat(kGraphicZeroF);
    GXInitTexObjLOD(&m_smallBackTexObj, GX_NEAR, GX_NEAR, zero, zero, zero, GX_FALSE, GX_FALSE, GX_ANISO_1);
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
_GXTexObj* CGraphic::GetBackBufferRect(int& x, int& y, int& width, int& height, int doClear)
{
    if ((x % 2) != 0) {
        x -= 1;
    }
    if ((y % 2) != 0) {
        y -= 1;
    }

    int xEnd = x + width;
    int yEnd = y + height;

    if ((xEnd % 2) != 0) {
        xEnd += 1;
        width += 1;
    }
    if ((yEnd % 2) != 0) {
        yEnd += 1;
        height += 1;
    }

    if ((xEnd < 0) || (yEnd < 0) || (x > static_cast<int>(m_renderMode->fbWidth)) || (yEnd < 0) ||
        (y > static_cast<int>(m_renderMode->efbHeight)) || (width <= 0) || (height <= 0)) {
        return 0;
    }

    int efbWidth = static_cast<int>(m_renderMode->fbWidth);
    if (xEnd > efbWidth) {
        width -= (xEnd - efbWidth);
        xEnd = static_cast<int>(m_renderMode->fbWidth);
    }

    if (x < 0) {
        width += x;
        x = 0;
    }

    if (y < 0) {
        height += y;
        y = 0;
    }

    int efbHeight = static_cast<int>(m_renderMode->efbHeight);
    if (yEnd > efbHeight) {
        height -= (yEnd - efbHeight);
        yEnd = static_cast<int>(m_renderMode->efbHeight);
    }

    if (((xEnd - x) != 0) && ((yEnd - y) != 0)) {
        int texFormat = 6;
        int textureSize = width * height * 4;
        int maxTextureSize =
            (((static_cast<int>(m_renderMode->fbWidth) + 0xF) & 0xFFF0) *
                 static_cast<int>(m_renderMode->efbHeight) * 2) +
            0x46000;
        if (maxTextureSize < textureSize) {
            texFormat = 4;
            textureSize /= 2;
        }

        GXSetTexCopySrc(x, y, width, height);
        GXSetTexCopyDst(width, height, static_cast<_GXTexFmt>(texFormat), GX_FALSE);
        DCInvalidateRange(m_scratchTextureBuffer, textureSize);
        GXCopyTex(m_scratchTextureBuffer, doClear);
        GXPixModeSync();
        GXInvalidateTexAll();
        GXInitTexObj(&m_backBufferTexObj, m_scratchTextureBuffer, width, height,
                     static_cast<_GXTexFmt>(texFormat), GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&m_backBufferTexObj, GX_LINEAR, GX_LINEAR, kGraphicZeroF, kGraphicZeroF,
                        kGraphicZeroF, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else {
        return 0;
    }
    return &m_backBufferTexObj;
}

/*
 * --INFO--
 * PAL Address: 0x80017980
 * PAL Size: 432b
 * EN Address: 0x80020AA8
 * EN Size: 568b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphic::GetBackBufferRect2(void* dstBuffer, _GXTexObj* texObj, int x, int y, int width, int height, int dstOffset,
                                  _GXTexFilter filter, _GXTexFmt format, int doClear)
{
    int xEnd = x + width;
    int yEnd = y + height;
    if ((xEnd < 0) || (yEnd < 0) || (x > m_renderMode->fbWidth) || (yEnd < 0) || (y > m_renderMode->efbHeight) ||
        (width <= 0) || (height <= 0)) {
        return;
    }
    if (xEnd - x == 0) {
        return;
    }
    if (yEnd - y == 0) {
        return;
    }
    {
        int textureSize = GXGetTexBufferSize(width, height, format, GX_FALSE, GX_FALSE);
        dstBuffer = static_cast<u8*>(dstBuffer) + OSRoundUp32B(dstOffset);
        dstBuffer = reinterpret_cast<void*>(OSRoundUp32B(dstBuffer));

        GXSetTexCopySrc(x, y, width, height);
        GXSetTexCopyDst(width, height, format, GX_FALSE);
        DCInvalidateRange(dstBuffer, textureSize);
        GXCopyTex(dstBuffer, doClear);
        GXPixModeSync();
        GXInvalidateTexAll();

        switch (format) {
        case GX_CTF_R4:
        case GX_CTF_RA4:
            format = GX_TF_I4;
            break;
        case GX_CTF_RA8:
        case GX_CTF_A8:
        case GX_CTF_R8:
        case GX_CTF_G8:
        case GX_CTF_B8:
            format = GX_TF_I8;
            break;
        case GX_CTF_RG8:
        case GX_CTF_GB8:
            format = GX_TF_IA8;
            break;
        default:
            break;
        }

        if (texObj != nullptr) {
            GXInitTexObj(texObj, dstBuffer, width, height, format, GX_CLAMP, GX_CLAMP,
                         GX_FALSE);
            float zero = LoadFloat(kGraphicZeroF);
            GXInitTexObjLOD(texObj, filter, filter, zero, zero, zero, GX_FALSE, GX_FALSE,
                            GX_ANISO_1);
        }
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

	float tex1;
	float x2;
	float tex0;
	float x1;
	float y1;
	float z1;
	float y2;
	u32 rgba1;
	u32 rgba3;
	u32 rgba2;
	u32 rgba4;

	x1 = pos1.x;
	y1 = pos1.y;
	GXWGFifo.f32 = x1;
	z1 = pos1.z;
	GXWGFifo.f32 = y1;
	rgba1 = *(u32*)&color1;
	GXWGFifo.f32 = z1;
	const float* tex0Ptr = &kGraphicZeroF;
	tex0 = *tex0Ptr;
	GXWGFifo.u32 = rgba1;
	x2 = pos2.x;
	GXWGFifo.f32 = tex0;
	rgba2 = *(u32*)&color2;
	GXWGFifo.f32 = tex0;
	const float* tex1Ptr = &kGraphicOneF;
	tex1 = *tex1Ptr;

	GXWGFifo.f32 = x2;
	y2 = pos2.y;
	GXWGFifo.f32 = y1;
	rgba4 = *(u32*)&color4;
	GXWGFifo.f32 = z1;
	rgba3 = *(u32*)&color3;
	GXWGFifo.u32 = rgba2;
	GXWGFifo.f32 = tex1;
	GXWGFifo.f32 = tex0;

	GXWGFifo.f32 = x2;
	GXWGFifo.f32 = y2;
	GXWGFifo.f32 = z1;
	GXWGFifo.u32 = rgba4;
	GXWGFifo.f32 = tex1;
	GXWGFifo.f32 = tex1;

	GXWGFifo.f32 = x1;
	GXWGFifo.f32 = y2;
	GXWGFifo.f32 = z1;
	GXWGFifo.u32 = rgba3;
	GXWGFifo.f32 = tex0;
	GXWGFifo.f32 = tex1;
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

	float x2;
	float x1 = pos1.x;
	float y1 = pos1.y;

	GXWGFifo.f32 = x1;
	float z1 = pos1.z;
	GXWGFifo.f32 = y1;
	u32 rgba1 = *(u32*)&color1;
	GXWGFifo.f32 = z1;

	x2 = pos2.x;
	GXWGFifo.u32 = rgba1;
	u32 rgba2 = *(u32*)&color2;
	GXWGFifo.f32 = x2;
	float y2 = pos2.y;
	GXWGFifo.f32 = y1;
	u32 rgba4 = *(u32*)&color4;
	GXWGFifo.f32 = z1;
	u32 rgba3 = *(u32*)&color3;
	GXWGFifo.u32 = rgba2;
	GXWGFifo.f32 = x2;
	GXWGFifo.f32 = y2;
	GXWGFifo.f32 = z1;

	GXWGFifo.u32 = rgba4;
	GXWGFifo.f32 = x1;
	GXWGFifo.f32 = y2;
	GXWGFifo.f32 = z1;
	GXWGFifo.u32 = rgba3;
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
	Vec cameraPos;
	Vec cameraToTarget;
	Vec scaledDir;
	Vec quadMin;
	Vec quadMax;
	float gxProjection[7];
	float gxViewport[6];
	_GXTexObj smallBackTex;
	_GXTexObj backBufferTex;
	Mtx cameraMtx;
	float projX;
	float projY;
	float projZ;
	_GXColor chanColor;
	_GXColor dofColor;
	int nearAlpha;
	int farAlpha;
	unsigned int texBufferSize;
	float xOffset;
	float yOffset;
	int hasNearAlpha;
	int hasFarAlpha;

	if (mode > 3) {
		return;
	}

	if (nearDist < kGraphicZeroF) {
		nearDist = kGraphicZeroF;
	}
	if (nearDist > kGraphicOneF) {
		nearDist = kGraphicOneF;
	}
	if (farDist < nearDist) {
		farDist = nearDist;
	}
	if (blurWidth <= 0) {
		blurWidth = 1;
	}

	nearAlpha = 0;
	farAlpha = 0;
	texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_RGBA8, GX_FALSE, GX_FALSE);

	CameraPcs.GetPosition(&cameraPos);
	hasNearAlpha = 0;
	cameraPos.y = kGraphicZeroF;
	hasFarAlpha = 0;

	targetPos.y = kGraphicZeroF;
	PSVECSubtract(&targetPos, &cameraPos, &cameraToTarget);

	GXGetProjectionv(gxProjection);
	GXGetViewportv(gxViewport);
	CameraPcs.GetViewMatrix(cameraMtx);

	if (mode != 2) {
		PSVECScale(&cameraToTarget, &scaledDir, nearDist);
		GXProject(cameraPos.x + scaledDir.x, targetPos.y, cameraPos.z + scaledDir.z, cameraMtx, gxProjection,
		          gxViewport, &projX, &projY, &projZ);

		nearAlpha = static_cast<unsigned int>(projZ * FLOAT_8032F6F8) >> 16;
		if ((unsigned int)nearAlpha >= 0xFF) {
			nearAlpha = 0xFF;
		}
		hasNearAlpha = 1;
	}

	if (mode != 1) {
		float targetMag = PSVECMag(&cameraToTarget);
		PSVECScale(&cameraToTarget, &scaledDir, farDist / targetMag);

		GXProject(targetPos.x + scaledDir.x, targetPos.y, targetPos.z + scaledDir.z, cameraMtx, gxProjection,
		          gxViewport, &projX, &projY, &projZ);

		farAlpha = static_cast<unsigned int>(projZ * FLOAT_8032F6F8) >> 16;
		if (farAlpha == 0) {
			farAlpha = 0xFF;
		}
		if ((unsigned int)farAlpha >= 0xFF) {
			farAlpha = 0xFF;
		}
		hasFarAlpha = 1;
	}

	if (!hasNearAlpha) {
		nearAlpha = 0;
	}
	if (!hasFarAlpha) {
		farAlpha = 0xFF;
	}

	gUtil.SetVtxFmt_POS_CLR_TEX();
	Graphic.CreateSmallBackTexture(Graphic.m_scratchTextureBuffer, &smallBackTex, 0x140, 0xE0, GX_LINEAR, GX_TF_RGBA8, 0);
	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backBufferTex, 0, 0, 0x280, 0x1C0, texBufferSize, GX_LINEAR,
	                   (_GXTexFmt)0x11, 0);
	gUtil.SetVtxFmt_POS_CLR_TEX0_TEX1();
	gUtil.SetOrthoEnv();

	xOffset = (float)blurWidth;
	yOffset = xOffset * FLOAT_8032F6FC;

	for (int pass = 0; pass < 2; pass++) {
		if ((pass == 0) && !((mode != 2) && hasNearAlpha && (mode != 1) && hasFarAlpha)) {
			continue;
		}

		GXTevKColorID kColorId = (GXTevKColorID)0;
		int kColorSel = 0x0C;
		int kAlphaSel = 0x1C;
		int passAlpha = nearAlpha;

		if (pass != 0) {
			kColorId = (GXTevKColorID)1;
			kColorSel = 0x0D;
			kAlphaSel = 0x1D;
			passAlpha = farAlpha;
		}

		dofColor.r = passAlpha;
		dofColor.g = passAlpha;
		dofColor.b = passAlpha;
		dofColor.a = passAlpha;
		chanColor.r = passAlpha;
		chanColor.g = passAlpha;
		chanColor.b = passAlpha;
		chanColor.a = 0x80;
		GXSetTevKColor(kColorId, dofColor);
		GXSetChanAmbColor(GX_COLOR0A0, chanColor);
		GXSetChanMatColor(GX_COLOR0A0, chanColor);

		_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);

		GXSetTevDirect(GX_TEVSTAGE0);
		GXLoadTexObj(&backBufferTex, GX_TEXMAP0);
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColorSel(GX_TEVSTAGE0, (GXTevKColorSel)kColorSel);
		GXSetTevKAlphaSel(GX_TEVSTAGE0, (GXTevKAlphaSel)kAlphaSel);

		if (pass == 0) {
			_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_KONST, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
		} else {
			_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_KONST, GX_CC_ONE, GX_CC_ZERO);
		}
		_GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_KONST, GX_CA_KONST, GX_CA_ZERO);
		_GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

		GXSetTevDirect(GX_TEVSTAGE1);
		GXLoadTexObj(&smallBackTex, GX_TEXMAP1);
		GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, 0x7D);
		_GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
		_GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
		_GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
		_GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		_GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_RASA, GX_CA_APREV, GX_CA_ZERO);
		_GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

		GXSetNumTevStages(2);
		GXSetNumTexGens(2);

		quadMin.x = kGraphicZeroF;
		quadMin.y = kGraphicZeroF;
		quadMin.z = kGraphicZeroF;
		quadMax.x = FLOAT_8032F6C8;
		quadMax.y = FLOAT_8032F6CC;
		quadMax.z = kGraphicZeroF;
		gUtil.RenderQuadTex2(quadMin, quadMax, chanColor, 0, 0);

		quadMin.x = -xOffset;
		quadMin.y = kGraphicZeroF;
		quadMin.z = kGraphicZeroF;
		quadMax.x = FLOAT_8032F6C8 - xOffset;
		quadMax.y = FLOAT_8032F6CC;
		quadMax.z = kGraphicZeroF;
		gUtil.RenderQuadTex2(quadMin, quadMax, chanColor, 0, 0);

		quadMin.x = xOffset;
		quadMin.y = kGraphicZeroF;
		quadMin.z = kGraphicZeroF;
		quadMax.x = FLOAT_8032F6C8 + xOffset;
		quadMax.y = FLOAT_8032F6CC;
		quadMax.z = kGraphicZeroF;
		gUtil.RenderQuadTex2(quadMin, quadMax, chanColor, 0, 0);

		quadMin.x = kGraphicZeroF;
		quadMin.y = -yOffset;
		quadMin.z = kGraphicZeroF;
		quadMax.x = FLOAT_8032F6C8;
		quadMax.y = FLOAT_8032F6CC - yOffset;
		quadMax.z = kGraphicZeroF;
		gUtil.RenderQuadTex2(quadMin, quadMax, chanColor, 0, 0);

		quadMin.x = kGraphicZeroF;
		quadMin.y = yOffset;
		quadMin.z = kGraphicZeroF;
		quadMax.x = FLOAT_8032F6C8;
		quadMax.y = FLOAT_8032F6CC + yOffset;
		quadMax.z = kGraphicZeroF;
		gUtil.RenderQuadTex2(quadMin, quadMax, chanColor, 0, 0);
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
    Mtx44 projection;

    gUtil.SetOrthoEnv();
    gUtil.SetVtxFmt_POS_CLR_TEX();
    gUtil.DisableIndMtx();

    GXSetNumChans(1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    _GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);

    long halfWidth = width / 2;
    long halfHeight = height / 2;

    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;

    GetBackBufferRect2(m_scratchTextureBuffer, &tempTex, 0, 0, 0x140, 0xE0, 0x46000, filter, GX_TF_RGBA8, 0);
    quadMin.x = kGraphicZeroF;
    quadMin.y = kGraphicZeroF;
    quadMin.z = kGraphicZeroF;
    quadMax.x = static_cast<float>(halfWidth);
    quadMax.y = static_cast<float>(halfHeight);
    quadMax.z = kGraphicZeroF;
    GXLoadTexObj(&tempTex, GX_TEXMAP0);
    gUtil.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(m_scratchTextureBuffer, texObj, 0x140, 0, 0x140, 0xE0, 0, filter, format, 0);
    quadMin.x = static_cast<float>(halfWidth);
    quadMin.y = kGraphicZeroF;
    quadMin.z = kGraphicZeroF;
    quadMax.x = static_cast<float>(width);
    quadMax.y = static_cast<float>(halfHeight);
    quadMax.z = kGraphicZeroF;
    GXLoadTexObj(texObj, GX_TEXMAP0);
    gUtil.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(m_scratchTextureBuffer, texObj, 0, 0xE0, 0x140, 0xE0, 0, filter, format, 0);
    quadMin.x = kGraphicZeroF;
    quadMin.y = static_cast<float>(halfHeight);
    quadMin.z = kGraphicZeroF;
    quadMax.x = static_cast<float>(halfWidth);
    quadMax.y = static_cast<float>(height);
    quadMax.z = kGraphicZeroF;
    GXLoadTexObj(texObj, GX_TEXMAP0);
    gUtil.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(m_scratchTextureBuffer, texObj, 0x140, 0xE0, 0x140, 0xE0, 0, filter, format, 0);
    quadMin.x = static_cast<float>(halfWidth);
    quadMin.y = static_cast<float>(halfHeight);
    quadMin.z = kGraphicZeroF;
    quadMax.x = static_cast<float>(width);
    quadMax.y = static_cast<float>(height);
    quadMax.z = kGraphicZeroF;
    GXLoadTexObj(texObj, GX_TEXMAP0);
    gUtil.RenderQuad(quadMin, quadMax, white, 0, 0);

    GetBackBufferRect2(src, texObj, 0, 0, static_cast<int>(width), static_cast<int>(height), textureSize, filter, format, 0);
    GXLoadTexObj(&tempTex, GX_TEXMAP0);
    quadMin.x = kGraphicZeroF;
    quadMin.y = kGraphicZeroF;
    quadMin.z = kGraphicZeroF;
    quadMax.x = kGraphicSmallBackTextureWidth;
    quadMax.y = kGraphicSmallBackTextureHeight;
    quadMax.z = kGraphicZeroF;
    gUtil.RenderQuad(quadMin, quadMax, white, 0, 0);

    CameraPcs.GetViewMatrix(cameraMtx);
    CameraPcs.GetProjectionMatrix(projection);
    GXLoadPosMtxImm(cameraMtx, 0);
    GXSetProjection(projection, GX_PERSPECTIVE);
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
    m_blurBufferIndex = 0;
    m_blurTextureCount = 0;
    m_blurDelayCounter = 0xE8;
}

/*
 * --INFO--
 * PAL Address: 0x800164c4
 * PAL Size: 1164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    gUtil.DisableIndMtx();
    gUtil.SetOrthoEnv();
    gUtil.SetVtxFmt_POS_CLR_TEX();
    GXSetZCompLoc(GX_FALSE);
    _GXSetAlphaCompare(GX_ALWAYS, 1, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);

    blurColor.r = 0x80;
    blurColor.g = 0x80;
    blurColor.b = 0x80;
    blurColor.a = alpha;
    GXSetChanAmbColor(GX_COLOR0A0, blurColor);
    GXSetChanMatColor(GX_COLOR0A0, blurColor);

    gUtil.SetOrthoEnv();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7D);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);

    int blurOffsetInt = offset;
    for (int i = 0; i < static_cast<int>(m_blurTextureCount); i++) {
        int negativeBlurOffset = -blurOffsetInt;
        u8* textureBase = reinterpret_cast<u8*>(m_savedFrameBuffer) + i * 0x46000;
        GXInitTexObj(&texObj, textureBase, 0x140, 0xE0, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, kGraphicZeroF, kGraphicZeroF, kGraphicZeroF, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);

        if (mode == 1) {
            quadMin.x = kGraphicZeroF;
            quadMin.y = kGraphicZeroF;
            quadMin.z = kGraphicZeroF;
            quadMax.x = FLOAT_8032F6C8;
            quadMax.y = FLOAT_8032F6CC;
            quadMax.z = kGraphicZeroF;
            gUtil.RenderQuad(quadMin, quadMax, blurColor, 0, 0);
        } else if (mode == 0) {
            quadMin.x = static_cast<float>(negativeBlurOffset);
            quadMin.y = static_cast<float>(negativeBlurOffset);
            quadMin.z = kGraphicZeroF;
            quadMax.x = static_cast<float>(640 - negativeBlurOffset);
            quadMax.y = static_cast<float>(448 - negativeBlurOffset);
            quadMax.z = kGraphicZeroF;
            gUtil.RenderQuad(quadMin, quadMax, blurColor, 0, 0);
        }
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(CameraPcs.GetViewMatrix(), 0);
    GXSetCurrentMtx(0);
    GXSetProjection(CameraPcs.GetProjectionMatrix(), GX_PERSPECTIVE);
    GXSetAlphaUpdate(GX_TRUE);

    if (m_blurDelayCounter < textureDelay) {
        m_blurDelayCounter += 1;
    } else if (System.m_scenegraphStepMode != 2) {
        CreateSmallBackTexture(m_savedFrameBuffer, &texObj, 0x140, 0xE0, GX_LINEAR, GX_TF_RGBA8,
                               static_cast<unsigned long>(m_blurBufferIndex) * 0x46000);
        m_blurDelayCounter = 0;
        m_blurTextureCount += 1;
        if (static_cast<int>(m_blurTextureCount) > 2) {
            m_blurTextureCount = 2;
        }
        m_blurBufferIndex += 1;
        if (static_cast<int>(m_blurBufferIndex) > 1) {
            m_blurBufferIndex = 0;
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
	GXRenderModeObj* renderMode = m_renderMode;
	u16 efbHeight = renderMode->efbHeight;
	u32 alignedWidth = (renderMode->fbWidth + 0xF) & 0xFFF0;
	m_scratchTextureBuffer =
	    Memory._Alloc(alignedWidth * (u32)efbHeight * 2 + 0x46000, m_scratchStage, const_cast<char*>(sGraphicSourceStrings),
	                  0xB53, 0);
	memset(m_scratchTextureBuffer, 0, 0x46004);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphic::DestroyTempBuffer()
{
	if (m_scratchTextureBuffer != nullptr) {
		delete[] reinterpret_cast<u8*>(m_scratchTextureBuffer);
		m_scratchTextureBuffer = nullptr;
	}
}

