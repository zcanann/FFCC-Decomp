#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedStream.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
#include "dolphin/os.h"

// Global objects that need initialization
extern CRedMemory DAT_8032f480;
extern CRedEntry DAT_8032e154;
extern void* DAT_8032e13c;
extern void* DAT_8032e148;

extern "C" {
    void __register_global_object(void*, void (*)(void*), void*);
    void* __ct__10CRedMemoryFv(void*);
    void* __ct__9CRedEntryFv(void*);
    void __dt__10CRedMemoryFv(void*);
    void __dt__9CRedEntryFv(void*);
    void* RedNew__Fi(int);
    void RedDelete__FPv(void*);
    void* memcpy(void*, const void*, unsigned long);
    void* memset(void*, int, unsigned long);
    int SearchMusicSequence__9CRedEntryFi(void*, int);
    void MusicStop__Fi(int);
    void MusicPlay__Fiii(int, int, int);
    void AXSetCompressor(int);
    void AXFXSetHooks(void (*)(unsigned long), void (*)(void*));
}

// Global data references from Ghidra
extern int DAT_8032f3c4;
extern int DAT_8032f3c0;
extern int DAT_8032f3c8;
extern int DAT_8032f408;
extern int DAT_8032f400;
extern int DAT_8032f414;
extern int DAT_8032f404;
extern int DAT_8032f410;
extern int DAT_8032f40c;
extern int DAT_8032f468;
extern int DAT_8032f434;
extern int DAT_8032f430;
extern int DAT_8032f488;
extern int DAT_8032f44c;
extern int DAT_8032f448;
extern int DAT_8032f47c;
extern int DAT_8032f478;
extern int DAT_8032f424;
extern int DAT_8032f43c;
extern int DAT_8032f3b8;
extern int DAT_8032e12c;
extern int DAT_8032f458;
extern int DAT_8032daac;
extern void* DAT_8032f3f0;
extern void* DAT_8032f418;
extern int DAT_8032f42c;
extern void* DAT_8032f3cc;
extern void* DAT_8032f3d0;
extern void* DAT_8032f41c;
extern void* DAT_8032f420;
extern void* DAT_8032f3d4;
extern void* DAT_8032f3d8;
extern void* DAT_8032f3dc;
extern void* DAT_8032f3f4;
extern void* DAT_8032f3fc;
extern unsigned int* DAT_8032f444;
extern void* DAT_8032f450;
extern void* DAT_8032f474;
extern void** DAT_8032f428;
extern void* DAT_8032f438;
extern void* DAT_8032f3e0;
extern void* DAT_8032f3e8;
extern void* DAT_8032f3e4;
extern void* DAT_8032f3ec;
extern void* DAT_8032f464;
extern void* DAT_8032f45c;
extern void* DAT_8032f46c;
extern void* DAT_8032f454;
extern void* DAT_8032b860;
extern void* DAT_8032c660;
extern OSSemaphore DAT_8032ddd8;
extern OSSemaphore DAT_8032daa0;
extern OSSemaphore DAT_8032e120;
extern OSSemaphore DAT_8032d778;
extern OSThread DAT_8032dac0;
extern OSThread DAT_8032d788;
extern OSThread DAT_8032de08;
extern OSThread DAT_8032d460;
extern ARQRequest DAT_8032dde4;

extern void ReverbAreaAlloc(unsigned long);
extern void ReverbAreaFree(void*);
extern void InitReverb();

/*
 * --INFO--
 * PAL Address: 0x801bfed8
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_RedDriver_cpp(void)
{
    void* uVar1;
    
    uVar1 = __ct__10CRedMemoryFv(&DAT_8032f480);
    __register_global_object(uVar1, __dt__10CRedMemoryFv, &DAT_8032e13c);
    uVar1 = __ct__9CRedEntryFv(&DAT_8032e154);
    __register_global_object(uVar1, __dt__9CRedEntryFv, &DAT_8032e148);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSoundMode(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetReverbDepth(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetMusicData(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicStop(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicPlaySequence(int*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801bd1fc
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MusicCrossPlaySequence(int* param_1)
{
    int iVar1;
    void* pvVar2;
    
    param_1[2] = param_1[2] * 200;
    iVar1 = param_1[2] / 0x3c + (param_1[2] >> 0x1f);
    param_1[2] = iVar1 - (iVar1 >> 0x1f);
    if (param_1[2] == 0) {
        param_1[2] = param_1[2] + 1;
    }
    pvVar2 = DAT_8032f3f0;
    if ((*param_1 != *(int*)((int)DAT_8032f3f0 + 0x470)) &&
       (*param_1 != *(int*)((int)DAT_8032f3f0 + 0xd98))) {
        if (*param_1 == *(int*)((int)DAT_8032f3f0 + 0x904)) {
            *(int*)((int)DAT_8032f3f0 + 0x458) = -*(int*)((int)DAT_8032f3f0 + 0x454) / param_1[2];
            *(int*)((int)pvVar2 + 0x45c) = param_1[2];
            pvVar2 = DAT_8032f3f0;
            *(int*)((int)DAT_8032f3f0 + 0x8ec) =
                 (0x1ff800 - *(int*)((int)DAT_8032f3f0 + 0x8e8)) / param_1[2];
            *(int*)((int)pvVar2 + 0x8f0) = param_1[2];
            pvVar2 = RedNew__Fi(0x494);
            memcpy(pvVar2, (void*)((int)DAT_8032f3f0 + 0x494), 0x494);
            memcpy((void*)((int)DAT_8032f3f0 + 0x494), DAT_8032f3f0, 0x494);
            memcpy(DAT_8032f3f0, pvVar2, 0x494);
            RedDelete__FPv(pvVar2);
        }
        else {
            iVar1 = SearchMusicSequence__9CRedEntryFi(&DAT_8032e154, *param_1);
            if (-1 < iVar1) {
                DAT_8032f42c = param_1[2];
                iVar1 = 0;
                if (*(int*)((int)pvVar2 + 0x470) != -1) {
                    if (*(int*)((int)pvVar2 + 0x904) != -1) {
                        MusicStop__Fi(*(int*)((int)pvVar2 + 0x904));
                    }
                    *(int*)((int)pvVar2 + 0x458) = -*(int*)((int)pvVar2 + 0x454) / param_1[2];
                    *(int*)((int)pvVar2 + 0x45c) = param_1[2];
                    iVar1 = *(int*)((char*)DAT_8032f418 + *param_1 * 4);
                    *(int*)((char*)DAT_8032f418 + *param_1 * 4) = 0;
                    if (iVar1 == 0) {
                        memcpy((void*)((int)pvVar2 + 0x494), pvVar2, 0x494);
                        *(int*)((int)pvVar2 + 0x470) = 0xffffffff;
                    }
                }
                MusicPlay__Fiii(*param_1, param_1[1], iVar1);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicNextPlaySequence(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicMasterVolume(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicVolume(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetMusicPhraseStop(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeBlockData(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeSepData(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepData(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepDataMG(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStop(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStopMG(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeBlockPlay(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlay(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlaySequence(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeMasterVolume(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeVolume(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePan(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePitch(int*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePause(int*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801bda34
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamStop(int* param_1)
{
	StreamStop(*param_1);
}

/*
 * --INFO--
 * PAL Address: 0x801bda64
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamPlay(int* param_1)
{
	StreamPlay(param_1[0], (void*)param_1[1], param_1[2], param_1[3], param_1[4]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdaa4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamVolume(int* param_1)
{
	SetStreamVolume(param_1[0], param_1[1], param_1[2]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdadc
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamPause(int* param_1)
{
	StreamPause(param_1[0], param_1[1]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _EntryExecCommand(void (*) (int*), int, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ExecuteCommand()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DeltaTimeSumup(unsigned char **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GetMyEntryID()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MyAlarmHandler(OSAlarm*, OSContext*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RedSleep(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MainThread(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _WaveSettingThread(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _DMACheckProcess()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _DmaCallback(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int RedDmaEntry(int, int, int, int, int, void (*) (void*), void*)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int RedDmaSearchID(int)
{
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be2dc
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _DmaExecute()
{
    unsigned int uVar1;
    int iVar2;
    int iVar3;
    int* piVar4;
    int** ppiVar5;
    int* piVar6;
    int* piVar7;
    int* piVar8;

    do {
        do {
            if ((DAT_8032f3e0 == DAT_8032f3e8) && (DAT_8032f3e4 == DAT_8032f3ec)) {
                DAT_8032f488 = 0;
                return;
            }
            if (DAT_8032f3e0 == DAT_8032f3e8) {
                ppiVar5 = (int**)&DAT_8032f3ec;
                piVar4 = (int*)&DAT_8032c660;
            } else {
                ppiVar5 = (int**)&DAT_8032f3e8;
                piVar4 = (int*)&DAT_8032b860;
            }
            piVar7 = *ppiVar5;
            DAT_8032f488 = 2;
            piVar6 = 0;
            if (*piVar7 != 0) {
                DAT_8032f468 = 1;
                if (piVar7[1] == 0) {
                    DCFlushRange((void*)piVar7[2], (u32)piVar7[4]);
                    iVar3 = piVar7[2];
                    iVar2 = piVar7[3];
                } else {
                    DCInvalidateRange((void*)piVar7[2], (u32)piVar7[4]);
                    iVar3 = piVar7[3];
                    iVar2 = piVar7[2];
                }
                DAT_8032f488 = 3;
                ARQSetChunkSize((u32)piVar7[4]);
                ARQPostRequest(&DAT_8032dde4, 0x469, (u32)piVar7[1], 1, (u32)iVar3, (u32)iVar2,
                               (u32)piVar7[4], _DmaCallback);
                piVar6 = piVar7;
            }
            piVar8 = piVar7 + 7;
            if (piVar4 + 0x380 <= piVar7 + 7) {
                piVar8 = piVar4;
            }
            *ppiVar5 = piVar8;
        } while (piVar6 == 0);
        while (piVar6 != 0) {
            DAT_8032f488 = 7;
            if (DAT_8032f468 == 0) {
                DAT_8032f488 = 8;
                if (piVar6[5] != 0) {
                    uVar1 = OSDisableInterrupts();
                    ((void (*)(void*))piVar6[5])((void*)piVar6[6]);
                    OSRestoreInterrupts(uVar1);
                }
                DAT_8032f488 = 9;
                if (piVar6[1] == 1) {
                    DCFlushRange((void*)piVar6[2], (u32)piVar6[4]);
                }
                *piVar6 = 0;
                break;
            }
            RedSleep(0);
        }
    } while (true);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _DmaExecuteThread(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicSkipThread(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _RedAXCallback()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRedDriver::CRedDriver()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRedDriver::~CRedDriver()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801be654
 * PAL Size: 1316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::Init()
{
    char cVar1;
    int iVar2;
    int iVar4;
    int iVar5;
    int iVar6;
    void* uVar3;

    DAT_8032f3c4 = 0;
    DAT_8032f3c0 = 1;
    DAT_8032f408 = 1;
    DAT_8032f3c8 = 0;
    GetSoundMode();
    if (DAT_8032f400 == 2) {
        AXSetMode(2);
    } else {
        AXSetMode(0);
    }
    DAT_8032f3cc = RedNew__Fi(400);
    memset(DAT_8032f3cc, 0, 400);
    AXSetCompressor(0);
    DAT_8032f414 = 0;
    DAT_8032f404 = 0;
    DAT_8032f410 = 0;
    DAT_8032f40c = 0;
    DAT_8032f468 = 0;
    DAT_8032f42c = 0;
    DAT_8032f434 = 0x1ff;
    DAT_8032f430 = 0x1ff;
    iVar6 = 0;
    do {
        iVar5 = iVar6 + 1;
        (&DAT_8032e12c)[iVar6] = 0;
        iVar6 = iVar5;
    } while (iVar5 < 4);
    DAT_8032f3d0 = RedNew__Fi(0x1000);
    memset(DAT_8032f3d0, 0, 0x1000);
    DAT_8032f418 = RedNew__Fi(0x400);
    memset(DAT_8032f418, 0, 0x400);
    DAT_8032f41c = RedNew__Fi(0xc);
    memset(DAT_8032f41c, 0, 0xc);
    DAT_8032f420 = RedNew__Fi(0xc);
    memset(DAT_8032f420, 0, 0xc);
    DAT_8032f3d4 = RedNew__Fi(0x2000);
    DAT_8032f3d8 = DAT_8032f3d4;
    DAT_8032f3dc = DAT_8032f3d4;
    memset(DAT_8032f3d4, 0, 0x2000);
    DAT_8032f3f0 = RedNew__Fi(0x1250);
    DAT_8032f3f4 = DAT_8032f3f0;
    memset(DAT_8032f3f0, 0, 0x1250);
    *(int*)((char*)DAT_8032f3f4 + 0xdd8) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0x944) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0x4b0) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0x1c) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0x1210) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0xd7c) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0x8e8) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0x454) = 0x1ff000;
    *(int*)((char*)DAT_8032f3f4 + 0xd98) = -1;
    *(int*)((char*)DAT_8032f3f4 + 0x904) = -1;
    *(int*)((char*)DAT_8032f3f4 + 0x470) = -1;
    DAT_8032f3fc = RedNew__Fi(0x600);
    memset(DAT_8032f3fc, 0, 0x600);
    DAT_8032f444 = (unsigned int*)RedNew__Fi(0x3000);
    memset(DAT_8032f444, 0, 0x3000);
    iVar6 = 0;
    do {
        iVar2 = iVar6 * 0xc0;
        iVar5 = iVar6 * 0x8000000;
        iVar4 = iVar6 >> 0x1f;
        iVar6 = iVar6 + 1;
        *(unsigned int*)((char*)DAT_8032f444 + iVar2 + 0xa8) =
            (iVar4 * 0x20 | (unsigned int)(iVar5 + iVar4) >> 0x1b) - iVar4;
    } while (iVar6 < 0x40);
    DAT_8032f44c = 0;
    DAT_8032f448 = 0;
    uVar3 = RedNew__Fi(0x2a80);
    *(void**)((char*)DAT_8032f3f0 + 0xdbc) = uVar3;
    memset(*(void**)((char*)DAT_8032f3f0 + 0xdbc), 0, 0x2a80);
    iVar5 = 0;
    iVar6 = (int)*(void**)((char*)DAT_8032f3f0 + 0xdbc);
    do {
        iVar4 = iVar5 * 0x154;
        cVar1 = (char)iVar5;
        iVar5 = iVar5 + 1;
        *(char*)(iVar6 + iVar4 + 0x14e) = (char)(cVar1 + ' ');
    } while (iVar5 < 0x20);
    DAT_8032f450 = RedNew__Fi(0x154);
    memset(DAT_8032f450, 0, 0x154);
    DAT_8032f474 = RedNew__Fi(0x18);
    memset(DAT_8032f474, 0, 0x18);
    DAT_8032f47c = 0;
    DAT_8032f478 = 0;
    DAT_8032f428 = (void**)RedNew__Fi(0x10);
    *DAT_8032f428 = (void*)-1;
    DAT_8032f424 = 0;
    DAT_8032f438 = RedNew__Fi(0x4c0);
    memset(DAT_8032f438, 0, 0x4c0);
    DAT_8032f43c = 0;
    memset(&DAT_8032b860, 0, 0x1c00);
    DAT_8032f3e0 = &DAT_8032b860;
    DAT_8032f3e8 = &DAT_8032b860;
    DAT_8032f3e4 = &DAT_8032c660;
    DAT_8032f3ec = &DAT_8032c660;
    DAT_8032f3b8 = 0;
    AXRegisterCallback(_RedAXCallback);
    AXFXSetHooks(ReverbAreaAlloc, ReverbAreaFree);
    InitReverb();
    OSInitSemaphore(&DAT_8032ddd8, 0);
    DAT_8032f464 = RedNew__Fi(0x1000);
    OSCreateThread(&DAT_8032dac0, (void* (*)(void*))_DmaExecuteThread, 0, (char*)DAT_8032f464 + 0x1000, 0x1000,
                   3, 1);
    OSResumeThread(&DAT_8032dac0);
    OSInitSemaphore(&DAT_8032daa0, 0);
    DAT_8032f45c = RedNew__Fi(0x1000);
    OSCreateThread(&DAT_8032d788, (void* (*)(void*))_WaveSettingThread, &DAT_8032daac,
                   (char*)DAT_8032f45c + 0x1000, 0x1000, 4, 1);
    OSResumeThread(&DAT_8032d788);
    OSInitSemaphore(&DAT_8032e120, 0);
    DAT_8032f46c = RedNew__Fi(0x1000);
    OSCreateThread(&DAT_8032de08, (void* (*)(void*))_MusicSkipThread, 0, (char*)DAT_8032f46c + 0x1000, 0x1000,
                   4, 1);
    OSResumeThread(&DAT_8032de08);
    OSInitSemaphore(&DAT_8032d778, 0);
    DAT_8032f458 = 0;
    DAT_8032f454 = RedNew__Fi(0x1000);
    OSCreateThread(&DAT_8032d460, (void* (*)(void*))_MainThread, 0, (char*)DAT_8032f454 + 0x1000, 0x1000, 4, 1);
    OSResumeThread(&DAT_8032d460);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::End()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::GetProgramTime()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetSoundMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::GetSoundMode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetMusicData(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ReentryMusicData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicPlay(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicCrossPlay(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicNextPlay(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicMasterVolume(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicFadeOut(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::MusicVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetMusicPhraseStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetSeBlockData(int, void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetSeSepData(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ClearSeSepData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ClearSeSepDataMG(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ReentrySeSepData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SePlayState(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SeStop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SeStopMG(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SePlay(int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SeMasterVolume(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SeFadeOut(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SeVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SePan(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SePitch(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SePause(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::GetSeVolume(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ReportSeLoop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::DisplaySePlayInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::StreamPlayState(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::GetStreamPlayPoint(int, int*, int*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801bfa74
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamStop(int param_1)
{
	_EntryExecCommand(_StreamStop, param_1, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfabc
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamPlay(int param_1, void* param_2, int param_3, int param_4, int param_5)
{
	_EntryExecCommand(_StreamPlay, param_1, (int)param_2, param_3, param_4, param_5, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::StreamVolume(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::StreamPause(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ClearWaveData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ClearWaveDataM(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ClearWaveBank(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetWaveData(int, int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::ReentryWaveData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::DisplayWaveInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetReverb(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetReverbDepth(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::TestProcess(int)
{
	// TODO
}
