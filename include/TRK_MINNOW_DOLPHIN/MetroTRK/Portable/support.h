#ifndef METROTRK_PORTABLE_SUPPORT_H
#define METROTRK_PORTABLE_SUPPORT_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKRequestSend(TRKBuffer* msgBuf, int* bufferId, u32 p1, u32 p2, int p3);
DSError TRKSuppAccessFile(u32 file_handle, u8* data, size_t* count,
                          DSIOResult* io_result, BOOL needReply, BOOL read);
DSError HandleOpenFileSupportRequest(const char* path, u8 replyError, u32* param_3,
                                     DSIOResult* ioResult);
DSError HandleCloseFileSupportRequest(int replyError, DSIOResult* ioResult);
DSError HandlePositionFileSupportRequest(DSReplyError replyErr, u32* param_2,
                                         u8 param_3, DSIOResult* ioResult);

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_SUPPORT_H */
