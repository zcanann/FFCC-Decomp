#include "__ppc_eabi_linker.h"
#include "global.h"

extern "C" {
#include "string.h"

SECTION_INIT extern void __flush_cache(void* addr, unsigned int size);
extern void __OSPSInit(void);
extern void __OSFPRInit(void);
extern void __OSCacheInit(void);

inline static void __copy_rom_section(void* dst, const void* src, unsigned int size)
{
    if (size && (dst != src)) {
        memcpy(dst, src, size);
        __flush_cache(dst, size);
    }
}

inline static void __init_bss_section(void* dst, unsigned int size)
{
    if (size) {
        memset(dst, 0, size);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80003340
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
SECTION_INIT void __init_data_80003340(void)
{
    __rom_copy_info* dci;
    __bss_init_info* bii;

    dci = _rom_copy_info;
    while (TRUE) {
        if (dci->size == 0)
            break;
        __copy_rom_section(dci->addr, dci->rom, dci->size);
        dci++;
    }

    bii = _bss_init_info;
    while (TRUE) {
        if (bii->size == 0)
            break;
        __init_bss_section(bii->addr, bii->size);
        bii++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80003400
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
SECTION_INIT asm void __init_hardware(void)
{
    // clang-format off
    nofralloc

    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0
    mflr r31
    bl __OSPSInit
    bl __OSFPRInit
    bl __OSCacheInit
    mtlr r31
    blr
    // clang-format on
}

}
