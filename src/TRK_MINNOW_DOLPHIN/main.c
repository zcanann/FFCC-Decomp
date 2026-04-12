#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/CircleBuffer.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWTrace.h"
#include "OdemuExi2/odemuexi/DebuggerDriver.h"
#include <dolphin/amc/AmcExi2Comm.h>

#define DDH_ERR_NOT_INITIALIZED -0x2711
#define DDH_ERR_ALREADY_INITIALIZED -0x2715
#define DDH_ERR_READ_ERROR -0x2719

#define DDH_BUF_SIZE (0x800)

typedef struct DdhRecvCB {
    CircleBuffer cb;
    u32 reserved;
} DdhRecvCB;

typedef struct DdhInitFlag {
    BOOL value;
    u32 reserved;
} DdhInitFlag;

/* 80450030-80450050 07CD50 001C+04 3/3 0/0 0/0 .bss             gRecvCB */
static DdhRecvCB gRecvCB ATTRIBUTE_ALIGN(8);

/* 8044F830-80450030 07C550 0800+00 1/1 0/0 0/0 .bss             gRecvBuf */
static u8 gRecvBuf[DDH_BUF_SIZE];

/* 804519C0-804519C8 000EC0 0004+04 3/3 0/0 0/0 .sbss            gIsInitialized */
static DdhInitFlag gIsInitialized ATTRIBUTE_ALIGN(8);

static const char ddh_cc_write_not_initialized[] = "cc not initialized\n";
static const char ddh_cc_write_output_data[] = "cc_write : Output data 0x%08x %ld bytes\n";
static const char ddh_cc_write_sending[] = "cc_write sending %ld bytes\n";
static const char ddh_cc_expected_packet_size[] = "Expected packet size : 0x%08x (%ld)\n";
static const char ddh_cc_read_error[] = "cc_read : error reading bytes from EXI2 %ld\n";
static const char ddh_cc_initialize_calling_exi2_init[] = "CALLING EXI2_Init\n";
static const char ddh_cc_initialize_done_calling_exi2_init[] = "DONE CALLING EXI2_Init\n";

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_initialize(void* inputPendingPtrRef, EXICallback monitorCallback)
{
    MWTRACE(1, (char*)ddh_cc_initialize_calling_exi2_init);
    EXI2_Init(inputPendingPtrRef, monitorCallback);
    MWTRACE(1, (char*)ddh_cc_initialize_done_calling_exi2_init);
    CircleBufferInitialize(&gRecvCB.cb, gRecvBuf, DDH_BUF_SIZE);
    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_shutdown()
{
    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_open()
{
    if (gIsInitialized.value != 0)
	{
        return DDH_ERR_ALREADY_INITIALIZED;
    }

    gIsInitialized.value = TRUE;
    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_close()
{
    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_read(u8* data, int size)
{
    u8 buff[DDH_BUF_SIZE];
    int originalDataSize;
    u32 result;
    int expectedDataSize;
    int poll;

    result = 0;
	
    if (!gIsInitialized.value)
	{
        return DDH_ERR_NOT_INITIALIZED;
    }

    MWTRACE(1, (char*)ddh_cc_expected_packet_size, size, size);
    originalDataSize = expectedDataSize = size;
	
    while ((u32)CBGetBytesAvailableForRead(&gRecvCB.cb) < expectedDataSize)
	{
        result = 0;
        poll = EXI2_Poll();
		
        if (poll != 0)
		{
            result = EXI2_ReadN(buff, poll);
            if (result == 0) {
                CircleBufferWriteBytes(&gRecvCB.cb, buff, poll);
            }
        }
    }

    if (result == 0)
	{
        CircleBufferReadBytes(&gRecvCB.cb, data, originalDataSize);
    }
	else
	{
        MWTRACE(8, (char*)ddh_cc_read_error, result);
    }

    return result;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_write(const u8* bytes, int length)
{
    int exi2Len;
    int n_copy;
    u32 hexCopy;

    hexCopy = (u32)bytes;
    n_copy = length;

    if (gIsInitialized.value == FALSE)
	{
        MWTRACE(8, (char*)ddh_cc_write_not_initialized);
        return DDH_ERR_NOT_INITIALIZED;
    }

    MWTRACE(8, (char*)ddh_cc_write_output_data, bytes, length);

    while (n_copy > 0)
	{
        MWTRACE(1, (char*)ddh_cc_write_sending, n_copy);
        exi2Len = EXI2_WriteN((const void*)hexCopy, n_copy);
		
        if (exi2Len == AMC_EXI_NO_ERROR)
		{
            break;
        }
		
        hexCopy += exi2Len;
        n_copy -= exi2Len;
    }

    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_pre_continue()
{
    EXI2_Unreserve();
    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_post_stop()
{
    EXI2_Reserve();
    return 0;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_peek()
{
    int poll;
    u8 buff[DDH_BUF_SIZE];

    poll = EXI2_Poll();
    if (poll <= 0)
	{
        return 0;
    }

    if (EXI2_ReadN(buff, poll) == 0)
	{
        CircleBufferWriteBytes(&gRecvCB.cb, buff, poll);
    } else
	{
        return DDH_ERR_READ_ERROR;
    }

    return poll;
}

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 
 * PAL Size: 
 * EN Address: 
 * EN Size: 
 */
int ddh_cc_initinterrupts()
{
    EXI2_EnableInterrupts();
    return 0;
}
