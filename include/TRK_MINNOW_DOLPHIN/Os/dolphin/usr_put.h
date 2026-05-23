#ifndef OS_DOLPHIN_USR_PUT_H
#define OS_DOLPHIN_USR_PUT_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

BOOL GetTRKConnected(void);
void SetTRKConnected(BOOL connected);
void usr_put_initialize(void);

#ifdef __cplusplus
}
#endif

#endif /* OS_DOLPHIN_USR_PUT_H */
