#include <stdlib.h>
#include <dolphin.h>
#include <dolphin/os.h>
#include <string.h>

#include "dolphin/os/__os.h"

__declspec(section ".ctors") extern void (* _ctors[])();
__declspec(section ".dtors") extern void (* _dtors[])();

// External symbols for initialization
extern char _rom_copy_info[];
extern char _bss_init_info[];

// Structure for ROM copy info
typedef struct {
    void* dst;
    void* src; 
    unsigned int size;
} RomCopyInfo;

// Structure for BSS init info  
typedef struct {
    void* dst;
    unsigned int size;
} BssInitInfo;

static void __init_cpp(void);
static void __fini_cpp(void);

__declspec(section ".init") void __init_data_80003340(void)
{
    RomCopyInfo* romInfo = (RomCopyInfo*)_rom_copy_info;
    
    // Process ROM copy entries
    while (romInfo->size != 0) {
        if (romInfo->dst != romInfo->src) {
            memcpy(romInfo->dst, romInfo->src, romInfo->size);
            __flush_cache(romInfo->dst, romInfo->size);
        }
        romInfo++;
    }
    
    BssInitInfo* bssInfo = (BssInitInfo*)_bss_init_info;
    
    // Process BSS initialization entries  
    while (bssInfo->size != 0) {
        memset(bssInfo->dst, 0, bssInfo->size);
        bssInfo++;
    }
}

__declspec(section ".init") asm void __init_hardware(void)
{ // clang-format off
    nofralloc
    mfmsr r0
    ori  r0,r0,MSR_FP
    mtmsr r0
    mflr    r31
    bl      __OSPSInit
    bl      __OSFPRInit
    bl      __OSCacheInit
    mtlr    r31
    blr
}

__declspec(section ".init") asm void __flush_cache(void *address, unsigned int size)
{ // clang-format off
    nofralloc
    lis     r5, 0xffff
    ori     r5, r5, 0xfff1
    and     r5, r5, r3
    subf    r3, r5, r3
    add     r4, r4, r3
rept:
    dcbst   0,r5
    sync
    icbi    0,r5
    addic   r5,r5,0x8
    subic.  r4,r4,0x8
    bge     rept
    isync
    blr
}

void __init_user(void) {
    __init_cpp();
}

static void __init_cpp(void) {
	void (* * constructor)();

	/*
	 *	call static initializers
	 */
	for (constructor = _ctors; *constructor; constructor++) {
		(*constructor)();
	}
}

static void __fini_cpp(void) {
    void (* * destructor)();

	/*
	 *	call destructors
	 */
    for (destructor = _dtors; *destructor; destructor++) {
        (*destructor)();
    }
}

__declspec(weak)
void abort(void) {
    _ExitProcess();
}

__declspec(weak)
void exit(int status) {
    __fini_cpp();
    _ExitProcess();
}

void _ExitProcess(void) {
    PPCHalt();
}
