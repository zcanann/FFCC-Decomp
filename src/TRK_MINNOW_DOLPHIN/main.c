#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/CircleBuffer.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWTrace.h"
#include "OdemuExi2/odemuexi/DebuggerDriver.h"
#include <dolphin/amc/AmcExi2Comm.h>

#define DDH_ERR_NOT_INITIALIZED -0x2711
#define DDH_ERR_ALREADY_INITIALIZED -0x2715
#define DDH_ERR_READ_ERROR -0x2719

#define DDH_BUF_SIZE (0x800)

/* 80450030-80450050 07CD50 001C+04 3/3 0/0 0/0 .bss             gRecvCB */
static CircleBuffer gRecvCB;

/* 8044F830-80450030 07C550 0800+00 1/1 0/0 0/0 .bss             gRecvBuf */
static u8 gRecvBuf[DDH_BUF_SIZE];

/* 804519C0-804519C8 000EC0 0004+04 3/3 0/0 0/0 .sbss            gIsInitialized */
BOOL gIsInitialized;
extern char ddh_cc_initialize_calling_exi2_init[];
extern char ddh_cc_initialize_done_calling_exi2_init[];
extern char ddh_cc_write_trace_strings[];
extern char ddh_cc_read_expected_packet_size_fmt[];
extern char ddh_cc_read_error_fmt[];

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
        CircleBufferWriteBytes(&gRecvCB, buff, poll);
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
int ddh_cc_write(const u8* bytes, int length)
{
    int exi2Len;
    int n_copy;
    u32 hexCopy;
    const char* traceFmt;

    hexCopy = (u32)bytes;
    n_copy = length;
    traceFmt = ddh_cc_write_trace_strings;

    if (gIsInitialized == FALSE)
	{
        MWTRACE(8, (char*)(traceFmt + 0));
        return DDH_ERR_NOT_INITIALIZED;
    }

    MWTRACE(8, (char*)(traceFmt + 0x14), bytes, length);

    while (n_copy > 0)
	{
        MWTRACE(1, (char*)(traceFmt + 0x40), n_copy);
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
int ddh_cc_read(u8* data, int size)
{
    u8 buff[DDH_BUF_SIZE];
    int originalDataSize;
    u32 result;
    int expectedDataSize;
    int poll;

    result = 0;
	
    if (!gIsInitialized)
	{
        return DDH_ERR_NOT_INITIALIZED;
    }

    MWTRACE(1, ddh_cc_read_expected_packet_size_fmt, size, size);
    originalDataSize = expectedDataSize = size;
	
    while ((u32)CBGetBytesAvailableForRead(&gRecvCB) < expectedDataSize)
	{
        result = 0;
        poll = EXI2_Poll();
		
        if (poll != 0)
		{
            result = EXI2_ReadN(buff, poll);
            if (result == 0) {
                CircleBufferWriteBytes(&gRecvCB, buff, poll);
            }
        }
    }

    if (result == 0)
	{
        CircleBufferReadBytes(&gRecvCB, data, originalDataSize);
    }
	else
	{
        MWTRACE(8, ddh_cc_read_error_fmt, result);
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
int ddh_cc_open()
{
    if (gIsInitialized != 0)
	{
        return DDH_ERR_ALREADY_INITIALIZED;
    }

    gIsInitialized = TRUE;
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
int ddh_cc_initialize(void* inputPendingPtrRef, EXICallback monitorCallback)
{
    MWTRACE(1, ddh_cc_initialize_calling_exi2_init);
    EXI2_Init(inputPendingPtrRef, monitorCallback);
    MWTRACE(1, ddh_cc_initialize_done_calling_exi2_init);
    CircleBufferInitialize(&gRecvCB, gRecvBuf, DDH_BUF_SIZE);
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
int gdev_cc_initinterrupts(void)
{ 
	DBInitInterrupts();
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
void gdev_cc_peek(void)
{
	// TODO
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
void gdev_cc_post_stop(void)
{
	// TODO
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
void gdev_cc_pre_continue(void)
{
	// TODO
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
void gdev_cc_write(void)
{
	// TODO
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
void gdev_cc_read(void)
{
	// TODO
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
void gdev_cc_close(void)
{
	// TODO
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
void gdev_cc_open(void)
{
	// TODO
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
void gdev_cc_shutdown(void)
{
	// TODO
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
void gdev_cc_initialize(void)
{
	// TODO
}
