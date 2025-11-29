#ifndef GBA_GBAKEY_H
#define GBA_GBAKEY_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

static void F23(void* task);
static void F25(void* task);
void __GBAX02(s32 chan, u8* readbuf);

#ifdef __cplusplus
}
#endif

#endif /* GBA_GBAKEY_H */
