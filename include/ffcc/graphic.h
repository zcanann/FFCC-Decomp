#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

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

void checkThread(void*);
void wakeup(OSAlarm*, OSContext*);
void sleep();
void std_sinf(float);
void std_cosf(float);

class CGraphic
{
public:
    CGraphic();

    void Init();
    void Quit();
    void GetProgressive();
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
    void IsFifoOver();
    void IsFrameRateOver();
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

    void GetBackBufferRect(int&, int&, int&, int&, int);
    void GetBackBufferRect2(void*, _GXTexObj*, int, int, int, int, int, _GXTexFilter, _GXTexFmt, int);

    void RenderTexQuadGrouad(Vec, Vec, _GXColor, _GXColor, _GXColor, _GXColor);
    void RenderNoTexQuadGrouad(Vec, Vec, _GXColor, _GXColor, _GXColor, _GXColor);

    void RenderDOF(signed char, signed char, float, float, Vec, int);

    void CreateSmallBackTexture(void*, _GXTexObj*, long, long, _GXTexFilter, _GXTexFmt, unsigned long);

    void InitBlurParameter();
    void RenderBlur(int, unsigned char, unsigned char, unsigned char, unsigned char, short);

    void CreateTempBuffer();
    void DestroyTempBuffer();
};

extern CGraphic Graphic;

#endif // _GRAPHIC_H_
