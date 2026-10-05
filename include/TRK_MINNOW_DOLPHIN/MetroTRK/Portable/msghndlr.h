#ifndef METROTRK_PORTABLE_MSGHNDLR_H
#define METROTRK_PORTABLE_MSGHNDLR_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

DSError TRKStandardACK(TRKBuffer* buffer, MessageCommandID commandID, DSReplyError replyError);

#ifdef VERSION_GCCJGC
DSError TRKDoUnsupported(TRKBuffer* buffer);
DSError TRKDoCPUType(TRKBuffer* buffer);
DSError TRKDoFlushCache(TRKBuffer* buffer);
#endif

#endif /* METROTRK_PORTABLE_MSGHNDLR_H */
