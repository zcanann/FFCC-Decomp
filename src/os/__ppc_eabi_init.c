#include <stdlib.h>
#include <string.h>
#include <dolphin.h>
#include <dolphin/os.h>

#include "dolphin/os/__os.h"

__declspec(section ".ctors") extern void (* _ctors[])();
__declspec(section ".dtors") extern void (* _dtors[])();

extern void* _rom_copy_info[];
extern void* _bss_init_info[];

static void __init_cpp(void);
static void __fini_cpp(void);

__declspec(section ".init") void __init_data_80003340(void)
{
    void** rom_info = _rom_copy_info;
    
    while (rom_info[2] != NULL) {
        void* src = rom_info[0];
        void* dst = rom_info[1];
        void* size = rom_info[2];
        
        if (size != NULL && dst != src) {
            memcpy(dst, src, (size_t)size);
            __flush_cache(dst, (unsigned int)size);
        }
        rom_info += 3;
    }
    
    void** bss_info = _bss_init_info;
    while (bss_info[1] != NULL) {
        if (bss_info[1] != NULL) {
            memset(bss_info[0], 0, (size_t)bss_info[1]);
        }
        bss_info += 2;
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
