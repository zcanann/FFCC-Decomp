#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/CircleBuffer.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWTrace.h"
#include "OdemuExi2/odemuexi/DebuggerDriver.h"
#include <dolphin/amc/AmcExi2Comm.h>

#define DDH_ERR_NOT_INITIALIZED -0x2711
#define DDH_ERR_ALREADY_INITIALIZED -0x2715
#define DDH_ERR_READ_ERROR -0x2719

#define DDH_BUF_SIZE (0x800)

typedef struct DdhCcWriteStrings {
    char not_initialized[0x14];
    char output_data[0x2C];
    char sending[0x1C];
} DdhCcWriteStrings;

static CircleBuffer gRecvCB;
static u8 gRecvBuf[DDH_BUF_SIZE];
BOOL gIsInitialized;

static const DdhCcWriteStrings ddh_cc_write_strings = {
    "cc not initialized\n",
    "cc_write : Output data 0x%08x %ld bytes\n",
    "cc_write sending %ld bytes\n",
};
static const char ddh_cc_read_expected_packet_size[] = "Expected packet size : 0x%08x (%ld)\n";
static const char ddh_cc_read_error[] = "cc_read : error reading bytes from EXI2 %ld\n";
static const char ddh_cc_initialize_calling_exi2_init[] = "CALLING EXI2_Init\n";
static const char ddh_cc_initialize_done_calling_exi2_init[] = "DONE CALLING EXI2_Init\n";

int ddh_cc_initialize(void* inputPendingPtrRef, EXICallback monitorCallback)
{
    MWTRACE(1, (char*)ddh_cc_initialize_calling_exi2_init);
    EXI2_Init(inputPendingPtrRef, monitorCallback);
    MWTRACE(1, (char*)ddh_cc_initialize_done_calling_exi2_init);
    CircleBufferInitialize(&gRecvCB, gRecvBuf, DDH_BUF_SIZE);
    return 0;
}

int ddh_cc_shutdown()
{
    return 0;
}

int ddh_cc_open()
{
    if (gIsInitialized != 0) {
        return DDH_ERR_ALREADY_INITIALIZED;
    }

    gIsInitialized = TRUE;
    return 0;
}

int ddh_cc_close()
{
    return 0;
}

int ddh_cc_read(u8* data, int size)
{
    u8 buff[DDH_BUF_SIZE];
    int originalDataSize;
    u32 result;
    int expectedDataSize;
    int poll;

    result = 0;
    if (!gIsInitialized) {
        return DDH_ERR_NOT_INITIALIZED;
    }

    MWTRACE(1, (char*)ddh_cc_read_expected_packet_size, size, size);

    originalDataSize = expectedDataSize = size;
    while ((u32)CBGetBytesAvailableForRead(&gRecvCB) < expectedDataSize) {
        result = 0;

        poll = EXI2_Poll();
        if (poll != 0) {
            result = EXI2_ReadN(buff, poll);
            if (result == 0) {
                CircleBufferWriteBytes(&gRecvCB, buff, poll);
            }
        }
    }

    if (result == 0) {
        CircleBufferReadBytes(&gRecvCB, data, originalDataSize);
    } else {
        MWTRACE(8, (char*)ddh_cc_read_error, result);
    }

    return result;
}

int ddh_cc_write(const u8* bytes, int length)
{
    const DdhCcWriteStrings* strings = &ddh_cc_write_strings;
    int exi2Len;
    int n_copy;
    u32 hexCopy;

    hexCopy = (u32)bytes;
    n_copy = length;

    if (gIsInitialized == FALSE) {
        MWTRACE(8, (char*)strings->not_initialized);
        return DDH_ERR_NOT_INITIALIZED;
    }

    MWTRACE(8, (char*)strings->output_data, bytes, length);

    while (n_copy > 0) {
        MWTRACE(1, (char*)strings->sending, n_copy);
        exi2Len = EXI2_WriteN((const void*)hexCopy, n_copy);
        if (exi2Len == AMC_EXI_NO_ERROR) {
            break;
        }
        hexCopy += exi2Len;
        n_copy -= exi2Len;
    }

    return 0;
}

int ddh_cc_pre_continue()
{
    EXI2_Unreserve();
    return 0;
}

int ddh_cc_post_stop()
{
    EXI2_Reserve();
    return 0;
}

int ddh_cc_peek()
{
    int poll;
    u8 buff[DDH_BUF_SIZE];

    poll = EXI2_Poll();
    if (poll <= 0) {
        return 0;
    }

    if (EXI2_ReadN(buff, poll) == 0) {
        CircleBufferWriteBytes(&gRecvCB, buff, poll);
    } else {
        return DDH_ERR_READ_ERROR;
    }

    return poll;
}

int ddh_cc_initinterrupts()
{
    EXI2_EnableInterrupts();
    return 0;
}
