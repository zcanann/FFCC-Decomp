#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "ffcc/manager.h"
#include <dolphin/gx.h>

// Forward declarations
struct CBound;
struct OSAlarm;
struct OSContext;
struct Vec;
struct Vec2d;
class CGraphic;
class CPad;
class CSystem;
class CMemoryCardMan;
class CFile;
class CUtil;
class CCameraPcs;

int checkThread(void*);
void wakeup(OSAlarm*, OSContext*);
void sleep();
void std_sinf(float);
void std_cosf(float);

class CGraphic : public CManager
{
public:

    void Init();
    void Quit();
    int GetProgressive();
    void ChangeProgressive(int);
    void SetCopyClear(_GXColor, int);
    void SetStdDispCopySrc();
    void SetStdDispCopyDst();
    void SetStdPixelFmt();
    void SetViewport();
    void BeginFrame();
    void EndFrame();
    void SetDrawDoneDebugData(signed char);
    void SetDrawDoneDebugDataPartControl(int);
    void _WaitDrawDone(char*, int);
    void Thread();
    u8 IsFifoOver();
    u32 IsFrameRateOver();
    void Flip();

    void Printf(char*, ...);
    void Printf(unsigned long, unsigned long, char*, ...);

    void DrawDebugString();
    void InitDebugString();

    void DrawDebugStringDirect(unsigned long, unsigned long, char*, unsigned long);

    void SaveFrameBuffer(char*);
    void DrawSphere();
    void DrawSphere(float (*)[4], Vec*, float, _GXColor*);
    void DrawSphere(float (*)[4], Vec*, Vec*, _GXColor*);
    void DrawSphere(float (*)[4], _GXColor);

    void makeSphere();

    void DrawBound(CBound&, _GXColor);

    void SetFogColor(_GXColor);
    void SetFogParam(float, float);
    void SetFog(int, int);

    void CopySaveFrameBuffer();

    _GXTexObj* GetBackBufferRect(int&, int&, int&, int&, int);
    void GetBackBufferRect2(void*, _GXTexObj*, int, int, int, int, int, _GXTexFilter, _GXTexFmt, int);
    unsigned char* GetTmpFrameBuffer();

    void RenderTexQuadGrouad(Vec, Vec, _GXColor, _GXColor, _GXColor, _GXColor);
    void RenderNoTexQuadGrouad(Vec, Vec, _GXColor, _GXColor, _GXColor, _GXColor);

    void RenderDOF(signed char, signed char, float, float, Vec, int);

    void CreateSmallBackTexture(void*, _GXTexObj*, long, long, _GXTexFilter, _GXTexFmt, unsigned long);

    void InitBlurParameter();
    void RenderBlur(int, unsigned char, unsigned char, unsigned char, unsigned char, short);

    void CreateTempBuffer();
    void DestroyTempBuffer();

    u8 _pad_0x4_to_0x71DF[0x71DC];
    void* m_renderMode;
    void* m_frameBuffer;
    void* m_scratchTextureBuffer;
    void* m_savedFrameBuffer;
    s32 m_displayCopyEnabled;
    s32 m_lastRetraceCount;
    u8 _pad_0x71F8_to_0x71FF[0x8];
    _GXColor m_fogColor;
    f32 m_fogStart;
    f32 m_fogEnd;
    _GXTexObj m_backBufferTexObj;
    _GXTexObj m_smallBackTexObj;
    GXFifoObj m_fifos[2];
    s32 m_fifoIndex;
    u32 m_frameRateOver;
    u8 _pad_0x7354_to_0x7357[0x4];
    int m_blurActive;
    u8 m_blurDelayCounter;
    u8 m_blurBufferIndex;
    u8 m_blurTextureCount;
    _GXColor m_defaultCopyClearColor;
    u8 _pad_0x7363_to_0x7373[0x11];
};

extern CGraphic Graphic;

#endif // _GRAPHIC_H_
