#include "__ppc_eabi_linker.h"

#if __MWERKS__
#pragma exceptions off
#pragma internal on
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void __init_cpp_exceptions(void);
extern void __fini_cpp_exceptions(void);

extern void __destroy_global_chain(void);
extern void __unregister_fragment();
extern int __register_fragment(void* info, int TOC);

#ifdef __cplusplus
}
#endif

/* 8032EBF0-8032EBF4 329550 0004+00 2/2 0/0 0/0 .sdata           fragmentID */
static int DAT_8032ebf0 = -2;

extern int GetR2__Fv();
extern void* PTR_PTR_GetF4__10CChunkFileFv_80012850;

/* 801B0678-801B06B8 1AB018 0040+00 1/0 1/0 0/0 .text            __init_cpp_exceptions */
void __init_cpp_exceptions(void) {
    int uVar1;
    
    if (DAT_8032ebf0 == -2) {
        uVar1 = GetR2__Fv();
        DAT_8032ebf0 = __register_fragment((void*)&PTR_PTR_GetF4__10CChunkFileFv_80012850, uVar1);
    }
}

/* 801B0644-801B0678 1AAFE4 0034+00 1/0 1/0 0/0 .text            __fini_cpp_exceptions */
void __fini_cpp_exceptions(void) {
    if (DAT_8032ebf0 != -2) {
        __unregister_fragment();
        DAT_8032ebf0 = -2;
    }
}

/* 803737C0-803737C4 000000 0004+00 0/0 1/1 0/0 .ctors           __init_cpp_exceptions_reference */
#pragma section ".ctors$10"
__declspec(section ".ctors$10")
extern void* const __init_cpp_exceptions_reference = __init_cpp_exceptions;

/* 80373980-80373984 000000 0004+00 0/0 1/1 0/0 .dtors           __destroy_global_chain_reference */
#pragma section ".dtors$10"
__declspec(section ".dtors$10")
extern void* const __destroy_global_chain_reference = __destroy_global_chain;

/* 80373984-80373988 000004 0004+00 0/0 0/1 0/0 .dtors           __fini_cpp_exceptions_reference */
#pragma section ".dtors$15"
__declspec(section ".dtors$15")
extern void* const __fini_cpp_exceptions_reference = __fini_cpp_exceptions;
