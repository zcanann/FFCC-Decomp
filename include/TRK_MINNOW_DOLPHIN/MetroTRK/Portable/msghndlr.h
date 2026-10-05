#ifndef METROTRK_PORTABLE_MSGHNDLR_H
#define METROTRK_PORTABLE_MSGHNDLR_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

DSError TRKStandardACK(TRKBuffer* buffer, MessageCommandID commandID, DSReplyError replyError);

#endif /* METROTRK_PORTABLE_MSGHNDLR_H */
