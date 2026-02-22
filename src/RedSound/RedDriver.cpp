#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedExecute.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
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
    void* memmove(void*, const void*, unsigned long);
    void* memset(void*, int, unsigned long);
    void SetMusicData__9CRedEntryFP12RedMusicHEAD(void*, void*);
    int SetSeSepData__9CRedEntryFP12RedSeSepHEAD(void*, void*);
    void ClearSeSepData__9CRedEntryFi(void*, int);
    void ClearSeSepDataMG__9CRedEntryFiiii(void*, int, int, int, int);
    int SearchMusicSequence__9CRedEntryFi(void*, int);
    int SearchSeSepSequence__9CRedEntryFi(void*, int);
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
extern int DAT_8032f484;
extern int DAT_8032f434;
extern int DAT_8032f430;
extern int DAT_8032f488;
extern int DAT_8032f44c;
extern int DAT_8032f448;
extern int DAT_8032f47c;
extern int DAT_8032f478;
extern int DAT_8032f424;
extern int DAT_8032f440;
extern int DAT_8032f43c;
extern int DAT_8032f3bc;
extern int DAT_8032f3b8;
extern int DAT_8032e12c;
extern int DAT_8032f458;
extern int DAT_8032daac;
extern int DAT_8032dab0;
extern void* DAT_8032dab4;
extern int DAT_8032dab8;
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
extern int DAT_8032f460;
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
extern FILE DAT_8021d1a8;

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
void _SetMusicData(int* param_1)
{
    SetMusicData__9CRedEntryFP12RedMusicHEAD(&DAT_8032e154, (void*)*param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicStop(int* param_1)
{
    MusicStop__Fi(*param_1);
    if ((*param_1 == -1) || (*(int*)DAT_8032f428 == *param_1)) {
        *(int*)DAT_8032f428 = -1;
    }
    if (*(int*)DAT_8032f428 < 0) {
        DAT_8032f424 = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd0f4
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MusicPlaySequence(int* param_1)
{
    int iVar1;
    int srcBuffer;

    srcBuffer = (int)DAT_8032f3f0;
    if ((((*param_1 != *(int*)(srcBuffer + 0x470)) &&
          (*param_1 != *(int*)(srcBuffer + 0x904))) &&
         (*param_1 != *(int*)(srcBuffer + 0xd98))) &&
        ((iVar1 = SearchMusicSequence__9CRedEntryFi(&DAT_8032e154, *param_1)), -1 < iVar1)) {
        iVar1 = param_1[2];
        if (*(int*)(srcBuffer + 0x470) != -1) {
            if (*(int*)(srcBuffer + 0x904) != -1) {
                MusicStop__Fi(*(int*)(srcBuffer + 0x904));
            }
            if (iVar1 == 0) {
                iVar1 = *(int*)((int)DAT_8032f418 + *param_1 * 4);
                *(int*)((int)DAT_8032f418 + *param_1 * 4) = 0;
            }
            if (iVar1 == 0) {
                memcpy((void*)(srcBuffer + 0x494), (void*)srcBuffer, 0x494);
                *(int*)(srcBuffer + 0x470) = -1;
            }
        }
        MusicPlay__Fiii(*param_1, param_1[1], iVar1);
    }
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
void _MusicNextPlaySequence(int* param_1)
{
    int iVar1;

    if ((((*param_1 != *(int*)((int)DAT_8032f3f0 + 0x470)) &&
          (*param_1 != *(int*)((int)DAT_8032f3f0 + 0x904))) &&
         (*param_1 != *(int*)((int)DAT_8032f3f0 + 0xd98))) &&
        ((iVar1 = SearchMusicSequence__9CRedEntryFi(&DAT_8032e154, *param_1)), -1 < iVar1)) {
        *(int*)DAT_8032f428 = *param_1;
        ((int*)DAT_8032f428)[1] = param_1[1];
        ((int*)DAT_8032f428)[2] = param_1[2];
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicMasterVolume(int* param_1)
{
    unsigned int* puVar1;

    DAT_8032f430 = *param_1 & 0x7f;
    puVar1 = DAT_8032f444;
    if (DAT_8032f430 != 0) {
        DAT_8032f430 = (DAT_8032f430 + 1) * 4 - 1;
    }
    do {
        puVar1[0x2e] = puVar1[0x2e] | 2;
        puVar1 += 0x30;
    } while (puVar1 < DAT_8032f444 + 0xc00);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicVolume(int* param_1)
{
    if (param_1[3] == 1) {
        *(int*)DAT_8032f428 = -1;
        DAT_8032f424 = 0;
    }
    SetMusicVolume(param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetMusicPhraseStop(int* param_1)
{
    DAT_8032f424 = *param_1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeBlockData(int* param_1)
{
    unsigned int uVar1;
    unsigned char* puVar2;

    uVar1 = (unsigned int)*param_1 & 3;
    if ((&DAT_8032e12c)[uVar1] != 0) {
        RedDelete__FPv((void*)(&DAT_8032e12c)[uVar1]);
        (&DAT_8032e12c)[uVar1] = 0;
    }
    if (param_1[1] != 0) {
        puVar2 = (unsigned char*)param_1[1];
        puVar2[0] = 'S';
        puVar2[1] = 'e';
        puVar2[2] = 'B';
        puVar2[3] = 'l';
        puVar2[4] = 'o';
        puVar2[5] = 'c';
        puVar2[6] = 'k';
        (&DAT_8032e12c)[uVar1] = param_1[1];
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeSepData(int* param_1)
{
    SetSeSepData__9CRedEntryFP12RedSeSepHEAD(&DAT_8032e154, (void*)*param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepData(int* param_1)
{
    ClearSeSepData__9CRedEntryFi(&DAT_8032e154, *param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepDataMG(int* param_1)
{
    ClearSeSepDataMG__9CRedEntryFiiii(&DAT_8032e154, param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStop(int* param_1)
{
    SeStopID(param_1[0]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStopMG(int* param_1)
{
    SeStopMG(param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeBlockPlay(int* param_1)
{
    DAT_8032f440 = param_1[5];
    SeBlockPlay(param_1[0], param_1[1], param_1[2], param_1[3], param_1[4]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlay(int* param_1)
{
    int iVar1;

    iVar1 = SetSeSepData__9CRedEntryFP12RedSeSepHEAD(&DAT_8032e154, (void*)param_1[1]);
    if (iVar1 != 0) {
        DAT_8032f440 = param_1[4];
        SeSepPlay(param_1[0], *(int*)(iVar1 + 8), param_1[2], param_1[3]);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlaySequence(int* param_1)
{
    int iVar1;

    iVar1 = SearchSeSepSequence__9CRedEntryFi(&DAT_8032e154, param_1[1]);
    if (-1 < iVar1) {
        DAT_8032f440 = param_1[4];
        SeSepPlay(param_1[0], param_1[1], param_1[2], param_1[3]);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeMasterVolume(int* param_1)
{
    unsigned int* puVar1;

    DAT_8032f434 = *param_1 & 0x7f;
    puVar1 = DAT_8032f444;
    if (DAT_8032f434 != 0) {
        DAT_8032f434 = (DAT_8032f434 + 1) * 4 - 1;
    }
    do {
        puVar1[0x2e] = puVar1[0x2e] | 2;
        puVar1 += 0x30;
    } while (puVar1 < DAT_8032f444 + 0xc00);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeVolume(int* param_1)
{
    SetSeVolume(param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePan(int* param_1)
{
    SetSePan(param_1[0], param_1[1], param_1[2]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePitch(int* param_1)
{
    SetSePitch(param_1[0], param_1[1], param_1[2]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePause(int* param_1)
{
    SePause(param_1[0], param_1[1]);
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
 * PAL Address: 0x801bdbd0
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _ExecuteCommand()
{
	int* executePos = (int*)DAT_8032f3d8;
	int* readPos = (int*)DAT_8032f3dc;

	while (executePos != readPos) {
		if (*readPos != 0) {
			((void (*)(int*))(*readPos))(readPos + 1);
		}
		readPos += 8;
		if (readPos == (int*)DAT_8032f3d4 + 0x800) {
			readPos = (int*)DAT_8032f3d4;
		}
	}

	DAT_8032f3dc = readPos;
}

/*
 * --INFO--
 * PAL Address: 0x801bdc48
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int DeltaTimeSumup(unsigned char** buffer)
{
	unsigned int deltaTime = 0;

	if (buffer != 0) {
		deltaTime = **buffer & 0x7f;
		while ((**buffer & 0x80) != 0) {
			*buffer += 1;
			deltaTime = (deltaTime << 7) | (**buffer & 0x7f);
		}
		*buffer += 1;
	}

	return deltaTime;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GetMyEntryID()
{
    DAT_8032f3bc = (DAT_8032f3bc + 1) & 0x7fffffff;
    if (DAT_8032f3bc == 0) {
        DAT_8032f3bc = 1;
    }
    return DAT_8032f3bc;
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
int _MainThread(void*)
{
    int iVar1;
    int iVar2;
    int iVar3;
    unsigned int uVar4;

    DAT_8032f3c4 = DAT_8032f3c4 | 1;
    while (DAT_8032f3c0 != 0) {
        OSWaitSemaphore(&DAT_8032d778);
        if (DAT_8032f3c0 != 0) {
            iVar2 = OSGetTick();
            iVar1 = (int)DAT_8032f3f0;
            iVar3 = DAT_8032f3b8;
            uVar4 = (unsigned int)(DAT_8032f3b8 - DAT_8032f458);
            if (*(short*)(iVar1 + 0x48e) != 0) {
                *(unsigned int*)(iVar1 + 0x478) = *(unsigned int*)(iVar1 + 0x478) + uVar4;
            }
            DAT_8032f458 = iVar3;
            if (4 < uVar4) {
                uVar4 = 4;
            }
            MainControl(uVar4);
            StreamControl();
            _ExecuteCommand();
            if ((-1 < *(int*)DAT_8032f428) && (*(int*)(iVar1 + 0x470) < 0)) {
                _MusicPlaySequence((int*)DAT_8032f428);
                *(int*)DAT_8032f428 = -1;
                DAT_8032f424 = 0;
            }
            do {
                iVar3 = OSTryWaitSemaphore(&DAT_8032d778);
            } while (0 < iVar3);
            memmove((int*)DAT_8032f3cc + 1, DAT_8032f3cc, 0x18c);
            iVar3 = OSGetTick();
            *(int*)DAT_8032f3cc = iVar3 - iVar2;
        }
    }
    DAT_8032f3c4 = DAT_8032f3c4 & ~1;
    return 0;
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
 * PAL Address: 0x801bdfac
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _DMACheckProcess()
{
    int semCount;
    int* dmaInfo;

    if (DAT_8032f408 != 0) {
        OSReport("[%s]------DMA_CHECK_PROCESS------\n", "RedDriver");
        fflush(&DAT_8021d1a8);

        semCount = OSGetSemaphoreCount(&DAT_8032ddd8);
        OSReport("[%s]Status = %d Semaphore = %d Entry = %d/%d\n", "RedDriver", DAT_8032f468, semCount, DAT_8032f484, DAT_8032f488);
        fflush(&DAT_8021d1a8);
    }

    dmaInfo = (int*)&DAT_8032b860;
    do {
        if ((*dmaInfo != 0) && (DAT_8032f408 != 0)) {
            OSReport("[%s]ID = %d MMem = %8.8X AMem = %8.8X Size = %d %d\n", "RedDriver", dmaInfo[0], dmaInfo[2], dmaInfo[3], dmaInfo[4], dmaInfo[5]);
            fflush(&DAT_8021d1a8);
        }
        dmaInfo += 7;
    } while (dmaInfo < (int*)&DAT_8032d460);

    fflush(&DAT_8021d1a8);
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
 * PAL Address: 0x801be0d0
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedDmaEntry(int param_1, int param_2, int param_3, int param_4, int param_5, void (*param_6)(void*), void* param_7)
{
    unsigned int interrupt;
    void* baseAddr;
    void** queuePtr;
    unsigned int entryID;
    unsigned int size;
    unsigned int chunkSize;
    int* queueEntry;
    int* nextEntry;

    interrupt = OSDisableInterrupts();
    if ((param_1 & 0xffff7fff) == 0) {
        baseAddr = &DAT_8032c660;
        queuePtr = &DAT_8032f3e4;
    } else {
        queuePtr = &DAT_8032f3e0;
        baseAddr = &DAT_8032b860;
    }
    queueEntry = (int*)*queuePtr;
    entryID = GetMyEntryID();
    size = (unsigned int)(param_5 + 0x1f) & 0xffffffe0;
    if ((DAT_8032f43c == 0) && ((param_1 & 0x8000) == 0)) {
        queueEntry[0] = entryID;
        queueEntry[1] = param_2;
        queueEntry[2] = param_3;
        queueEntry[3] = param_4;
        queueEntry[4] = size;
        queueEntry[5] = (int)param_6;
        queueEntry[6] = (int)param_7;
        nextEntry = queueEntry + 7;
        if ((int*)baseAddr + 0x380 <= nextEntry) {
            nextEntry = (int*)baseAddr;
        }
        *queuePtr = nextEntry;
    } else {
        do {
            chunkSize = size;
            if ((int)size > 0x40000) {
                chunkSize = 0x40000;
            }
            queueEntry[0] = entryID;
            size -= chunkSize;
            queueEntry[1] = param_2;
            queueEntry[2] = param_3;
            param_3 += chunkSize;
            queueEntry[3] = param_4;
            param_4 += chunkSize;
            queueEntry[4] = chunkSize;
            queueEntry[6] = (int)param_7;
            if ((int)size < 1) {
                queueEntry[5] = (int)param_6;
            } else {
                queueEntry[5] = 0;
            }
            queueEntry += 7;
            if ((int*)baseAddr + 0x380 <= queueEntry) {
                queueEntry = (int*)baseAddr;
            }
        } while ((int)size > 0);
        *queuePtr = queueEntry;
    }
    OSSignalSemaphore(&DAT_8032ddd8);
    OSRestoreInterrupts(interrupt);
    return entryID;
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
 * PAL Address: 0x801becd8
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetMusicData(void* param_1)
{
    char localHeader[0x20];
    char* musicHeader = (char*)param_1;
    void* copiedHeader;
    int headerSize;
    short musicID;

    if (((musicHeader[0] == 'B') && (musicHeader[1] == 'G')) && (musicHeader[2] == 'M')) {
        memcpy(localHeader, musicHeader, sizeof(localHeader));
        headerSize = *(int*)(localHeader + 0x10);
        copiedHeader = RedNew__Fi(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, musicHeader, headerSize);
            _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
            musicID = *(short*)(localHeader + 4);
            (void)musicID;
            return;
        }
    }
    if (DAT_8032f408 != 0) {
        OSReport("Music Header was broken.\n");
        fflush(&DAT_8021d1a8);
    }
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
 * PAL Address: 0x801bf16c
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetSeSepData(void* param_1)
{
    int iVar1;
    int iVar2;
    void* pvVar3;
    char* pcVar4;

    pcVar4 = (char*)param_1;
    if ((((pcVar4[0] == 'S') && (pcVar4[1] == 'e')) && (pcVar4[2] == 'S')) &&
        ((pcVar4[3] == 'e' && (pcVar4[4] == 'p')))) {
        iVar1 = *(int*)(pcVar4 + 0xc) & 0x7fffffff;
        pvVar3 = RedNew__Fi(iVar1);
        if (pvVar3 != 0) {
            memcpy(pvVar3, param_1, iVar1);
            iVar2 = *(int*)((int)pvVar3 + 8);
            _EntryExecCommand(_SetSeSepData, (int)pvVar3, 0, 0, 0, 0, 0, 0);
            (void)iVar2;
        }
        return;
    }
    if (DAT_8032f408 != 0) {
        OSReport("SE Sep Header was broken.\n");
    }
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
 * PAL Address: 0x801bf384
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SePlayState(int param_1)
{
    unsigned int uVar1;
    int* piVar2;
    int* piVar3;
    int iVar4;

    uVar1 = OSDisableInterrupts();
    iVar4 = 0;
    piVar3 = *(int**)((int)DAT_8032f3f0 + 0xdbc);
    while (piVar3 < (int*)(*(int*)((int)DAT_8032f3f0 + 0xdbc) + 0x2a80)) {
        if ((*piVar3 != 0) && ((param_1 == -1 || (piVar3[0x3e] == param_1)))) {
            iVar4 = 1;
            break;
        }
        piVar3 = piVar3 + 0x55;
    }
    if (iVar4 == 0) {
        piVar3 = (int*)DAT_8032f3dc;
        while (piVar3 != (int*)DAT_8032f3d8) {
            piVar2 = piVar3;
            if (((*piVar2 != 0) &&
                ((((void (*)(int*))*piVar2 == _SeBlockPlay) ||
                  (((void (*)(int*))*piVar2 == _SeSepPlay))) ||
                 ((void (*)(int*))*piVar2 == _SeSepPlaySequence))) &&
                ((param_1 == -1 || (param_1 == piVar2[1])))) {
                iVar4 = 1;
                break;
            }
            piVar3 = piVar2 + 8;
            if (piVar3 == (int*)DAT_8032f3d4 + 0x800) {
                piVar3 = (int*)DAT_8032f3d4;
            }
        }
    }
    OSRestoreInterrupts(uVar1);
    return iVar4;
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
 * PAL Address: 0x801bf540
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePlay(int bank, int sep, int autoID, int unk, int volume, int pitch)
{
	if (bank == -1) {
		if (sep > -1) {
			_EntryExecCommand(_SeSepPlaySequence, autoID, sep, unk, volume, pitch, 0, 0);
		}
	} else if ((bank > -1) && (bank < 4) && (sep > -1) && (sep < 0x200)) {
		_EntryExecCommand(_SeBlockPlay, autoID, bank, sep, unk, volume, pitch, 0);
	}

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
 * PAL Address: 0x801bfc60
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWaveData(int slot, int waveID, void* waveData, int waveSize)
{
    char* waveHeader;

    while (DAT_8032f460 != 0) {
        RedSleep(0);
    }

    DAT_8032dab8 = waveSize;
    waveHeader = (char*)waveData;
    if (waveSize == -1) {
        if ((waveHeader[0] == 'W') && (waveHeader[1] == 'D')) {
            DAT_8032dab8 = *(int*)(waveHeader + 4) +
                           (((*(int*)(waveHeader + 8) * 4) + 0x3fU) & 0xffffffc0) +
                           (*(int*)(waveHeader + 0xc) * 0x60) + 0x20;
        }
        else {
            DAT_8032dab8 = 0;
        }
    }

    DAT_8032daac = slot;
    DAT_8032dab0 = waveID;
    DAT_8032dab4 = waveData;
    OSSignalSemaphore(&DAT_8032daa0);
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
