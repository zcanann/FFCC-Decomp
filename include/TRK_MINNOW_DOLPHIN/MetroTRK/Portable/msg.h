#ifndef METROTRK_PORTABLE_MSG_H
#define METROTRK_PORTABLE_MSG_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKMessageSend(TRKBuffer* msg);

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_MSG_H */
