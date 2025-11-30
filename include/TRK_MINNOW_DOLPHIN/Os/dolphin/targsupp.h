#ifndef PPC_EXPORT_TARGSUPP_H
#define PPC_EXPORT_TARGSUPP_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

u8 TRKAccessFile(u8 command, u32 file_handle, u32 *length_ptr, u8 *buffer_ptr);
u8 TRKOpenFile(u8 command, u32 file_handle, u32 flags, u8 *buffer_ptr);
u8 TRKCloseFile(u8 command, u32 file_handle);
u8 TRKPositionFile(u8 command, u32 file_handle, u32 *length_ptr, u8 *buffer_ptr);

#ifdef __cplusplus
}
#endif

#endif /* PPC_EXPORT_TARGSUPP_H */
