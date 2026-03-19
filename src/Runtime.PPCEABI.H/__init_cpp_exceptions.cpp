#include "PowerPC_EABI_Support/Runtime/NMWException.h"

#if __MWERKS__
#pragma exceptions off
#pragma internal on
#endif

/* 80450AD0-80450AD8 000550 0004+04 2/2 0/0 0/0 .sdata           fragmentID */
static int fragmentID = -2;

static asm char* GetR2(void) {
#ifdef __MWERKS__
    nofralloc
    mr r3, r2
    blr
#endif
}

#ifdef __cplusplus
extern "C" {
#endif

/* 8036283C-80362870 35D17C 0034+00 1/0 1/0 0/0 .text            __fini_cpp_exceptions */
void __fini_cpp_exceptions(void) {
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

/* 80362870-803628AC 35D1B0 003C+00 1/0 1/0 0/0 .text            __init_cpp_exceptions */
void __init_cpp_exceptions(void) {
    char* R2;

    if (fragmentID == -2) {
        R2         = GetR2();
        fragmentID = __register_fragment(_eti_init_info, R2);
    }
}

#ifdef __cplusplus
}
#endif

/* 803737C0-803737C4 000000 0004+00 0/0 1/1 0/0 .ctors           __init_cpp_exceptions_reference */
__declspec(section ".ctors") extern void* const __init_cpp_exceptions_reference = __init_cpp_exceptions;

/* 80373980-80373984 000000 0004+00 0/0 1/1 0/0 .dtors           __destroy_global_chain_reference */
__declspec(section ".dtors") extern void* const __destroy_global_chain_reference = __destroy_global_chain;

/* 80373984-80373988 000004 0004+00 0/0 0/1 0/0 .dtors           __fini_cpp_exceptions_reference */
__declspec(section ".dtors") extern void* const __fini_cpp_exceptions_reference = __fini_cpp_exceptions;
