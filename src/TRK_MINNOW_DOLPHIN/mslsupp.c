#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/targsupp.h"

DSIOResult __read_file(u32 handle, u8* buffer, u32* count, void* ref_con);
DSIOResult __write_file(u32 handle, u8* buffer, u32* count, void* ref_con);
DSIOResult __access_file(u32 handle, u8* buffer, u32* count, void* ref_con, MessageCommandID cmd);
DSIOResult __open_file(u32 handle, u8* mode, u32* outHandle);
DSIOResult __close_console(u32 handle);
DSIOResult __position_file(u32 handle, u32 offset, s32 whence);
DSIOResult __close_file(u32 handle);

DSIOResult __read_console(u32 handle, u8* buffer, u32* count, void* ref_con) {
    if (GetUseSerialIO() == 0)
	{
        return DS_IOError;
    }
	
    return __read_file(DS_Stdin, buffer, count, ref_con);
}

DSIOResult __TRK_write_console(u32 handle, u8* buffer, u32* count, void* ref_con)
{
    if (GetUseSerialIO() == 0)
	{
        return DS_IOError;
    }
	
    return __write_file(DS_Stdout, buffer, count, ref_con);
}

static DSIOResult __read_file(u32 handle, u8* buffer, u32* count, void* ref_con)
{
    return __access_file(handle, buffer, count, ref_con, DSMSG_ReadFile);
}

static DSIOResult __write_file(u32 handle, u8* buffer, u32* count, void* ref_con)
{
    return __access_file(handle, buffer, count, ref_con, DSMSG_WriteFile);
}

static inline DSIOResult __access_file(u32 handle, u8* buffer, u32* count, void* ref_con, MessageCommandID cmd)
{
    u32 countTemp;
    u32 r0;

    if (GetTRKConnected() == DS_NoError) {
        return DS_IOError;
    }

    countTemp = *count;
    r0 = TRKAccessFile(cmd, handle, &countTemp, buffer);
    *count = countTemp;

    switch ((u8)r0) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    }

    return DS_IOError;
}

DSIOResult __open_file(u32 handle, u8* mode, u32* outHandle)
{
    u8 mode0;
    u8 mode1;
    u8 accessBits; // top 2 bits of mode[0]
    u8 behaviorBits; // middle 3 bits of mode[0]
    u8 appendBit; // bit 3 of mode[1]
    u8 flags;
    u8 trkResult;

    if (GetTRKConnected() == 0) {
        return DS_IOError;
    }

    mode0 = mode[0];
    mode1 = mode[1];

    /* These bitfields come from MSLs internal FILE mode encoding. */
    accessBits   = (u8)((mode0 >> 6) & 0x3);
    behaviorBits = (u8)((mode0 >> 3) & 0x7);
    appendBit    = (u8)((mode1 >> 3) & 0x1);
    flags = 0;

    /* Access mode: read / write / read-write, encoded in the top 2 bits. */
    switch (accessBits) {
    case 0:         /* read */
        flags |= 0x01;
        break;
    case 2:         /* read/write */
        flags |= 0x02;
        break;
    case 1:         /* write */
        flags |= 0x04;
        break;
    default:
        /* accessBits == 3: no extra flags */
        break;
    }

    /*
     * Behavior bits: truncate, create-if-needed, etc. live in the
     * middle three bits of mode[0].
     */
    switch (behaviorBits) {
    case 1:
        flags |= 0x01;
        break;
    case 2:
        flags |= 0x02;
        break;
    case 6:
        flags |= 0x04;
        break;
    case 3:
        /* special combination: set both 0x10 and 0x02 */
        flags |= 0x12;
        break;
    case 7:
        /* all the low three bits set */
        flags |= 0x07;
        break;
    default:
        /* other encodings don’t add anything */
        break;
    }

    /* Bit 3 of mode[1] is an extra “append / update” flag. */
    if (appendBit == 1) {
        flags |= 0x08;
    }

    trkResult = TRKOpenFile(0xD2, handle, flags, (u8*)outHandle);

    switch (trkResult) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    default:
        return DS_IOError;
    }
}

DSIOResult __close_console(u32 handle)
{
    u8 trkResult;

    if (GetTRKConnected() == 0) {
        return DS_IOError;
    }

    trkResult = (u8)TRKCloseFile(0xD3, handle);

    switch (trkResult) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    default:
        return DS_IOError;
    }
}

DSIOResult __position_file(u32 handle, u32 offset, s32 whence)
{
    u32 mode; /* encoded seek origin: 0, 1, or 2 */
    u8  trkResult;

    mode = 0;

    if (GetTRKConnected() == 0) {
        return DS_IOError;
    }

    /*
     * Translate the standard whence values into the MetroTRK
     * mode encoding. Anything outside 0/1/2 just leaves mode as 0.
     */
    if (whence == 0) {
        mode = 0;
    } else if (whence == 1) {
        mode = 1;
    } else if (whence == 2) {
        mode = 2;
    }


    trkResult = TRKPositionFile(0xD4, handle, offset, mode);

    switch (trkResult) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    default:
        return DS_IOError;
    }
}

DSIOResult __close_file(u32 handle)
{
    u8 trkResult;

    if (GetTRKConnected() == 0) {
        return DS_IOError;
    }

    trkResult = (u8)TRKCloseFile(0xD3, handle);
	
    switch (trkResult) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    default:
        return DS_IOError;
    }
}
