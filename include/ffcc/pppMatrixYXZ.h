#ifndef _PPP_MATRIXYXZ_H_
#define _PPP_MATRIXYXZ_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppMatrixYXZ(void* matrix_ptr, void* param2, void* param3);
void pppGetRotMatrixYXZ(void* matrix, void* vector);
void PSVECScale(void* src, void* dst, float scale);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MATRIXYXZ_H_
