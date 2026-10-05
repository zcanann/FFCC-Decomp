#ifndef METROTRK_PORTABLE_NOTIFY_H
#define METROTRK_PORTABLE_NOTIFY_H

#include "PowerPC_EABI_Support/MetroTRK/trkenum.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef VERSION_GCCJGC
DSError TRKDoNotifyStopped(u8 cmd);
#else
DSError TRKDoNotifyStopped(MessageCommandID cmd);
#endif

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_NOTIFY_H */
