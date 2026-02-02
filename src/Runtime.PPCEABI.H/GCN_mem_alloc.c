/**
 * GCN_mem_alloc.c
 * Description:
 */

#include "dolphin/os.h"

inline static void InitDefaultHeap(void) {
	void* arenaLo;
	void* arenaHi;

	OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
	OSReport("Metrowerks CW runtime library initializing default heap\n");

	arenaLo = OSGetArenaLo();
	arenaHi = OSGetArenaHi();

	arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
	OSSetArenaLo(arenaLo);

	arenaLo = (void*)OSRoundUp32B(arenaLo);
	arenaHi = (void*)OSRoundDown32B(arenaHi);

	OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
	OSSetArenaLo(arenaLo = arenaHi);
}

/* 803628AC-80362914 35D1EC 0068+00 0/0 1/1 0/0 .text            __sys_alloc */
void* __sys_alloc(u32 size) {
    if (__OSCurrHeap == -1) {
        InitDefaultHeap();
    }

    return OSAllocFromHeap(__OSCurrHeap, size);
}

/* 80362914-803629CC 35D254 00B8+00 0/0 1/1 0/0 .text            __sys_free */
void __sys_free(void* p) {
    if (__OSCurrHeap == -1) {
        InitDefaultHeap();
    }

    OSFreeToHeap(__OSCurrHeap, p);
}
