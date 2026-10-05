#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include "OdemuExi2/odemuexi/DebuggerDriver.h"
#include "amcstubs/AmcExi2Stubs.h"
#include "dolphin/base/PPCArch.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef VERSION_GCCJGC
static u8 gWriteBuf[0x110A];
static u8 gReadBuf[0x110A];
BOOL _MetroTRK_Has_Framing;
static int gReadCount;
static int gReadPos;
static int gWritePos;
#else
volatile u8 TRK_Use_BBA = 0;
BOOL _MetroTRK_Has_Framing = FALSE;
#endif
int ddh_cc_initinterrupts(void);
int ddh_cc_initialize(void*, __OSInterruptHandler);
int ddh_cc_shutdown(void);
int ddh_cc_peek(void);
int ddh_cc_read(u8*, int);
int ddh_cc_write(const u8*, int);
int ddh_cc_open(void);
int ddh_cc_close(void);
int ddh_cc_pre_continue(void);
int ddh_cc_post_stop(void);
int gdev_cc_initinterrupts(void);
int gdev_cc_initialize(void*, __OSInterruptHandler);
int gdev_cc_shutdown(void);
int gdev_cc_peek(void);
int gdev_cc_read(u8*, int);
int gdev_cc_write(const u8*, int);
int gdev_cc_open(void);
int gdev_cc_close(void);
int gdev_cc_pre_continue(void);
int gdev_cc_post_stop(void);
int udp_cc_initialize(void);
int udp_cc_shutdown(void);
int udp_cc_peek(void);
int udp_cc_read(u8*, int);
int udp_cc_write(const u8*, int);
int udp_cc_open(void);
int udp_cc_close(void);
int udp_cc_pre_continue(void);
int udp_cc_post_stop(void);

DBCommTable gDBCommTable = {};

asm void TRKLoadContext(OSContext* ctx, u32)
{
#ifdef __MWERKS__ // clang-format off
    nofralloc
    lwz r0, OSContext.gpr[0](r3)
    lwz r1, OSContext.gpr[1](r3)
    lwz r2, OSContext.gpr[2](r3)
    lhz r5, OSContext.state(r3)
    rlwinm. r6, r5, 0, 0x1e, 0x1e
    beq lbl_80371C1C
    rlwinm r5, r5, 0, 0x1f, 0x1d
    sth r5, OSContext.state(r3)
    lmw r5, OSContext.gpr[5](r3)
    b lbl_80371C20
lbl_80371C1C:
    lmw r13, OSContext.gpr[13](r3)
lbl_80371C20:
    mr r31, r3
    mr r3, r4
    lwz r4, OSContext.cr(r31)
    mtcrf 0xff, r4
    lwz r4, OSContext.lr(r31)
    mtlr r4
    lwz r4, OSContext.ctr(r31)
    mtctr r4
    lwz r4, OSContext.xer(r31)
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 0x11, 0xf //Turn off external exceptions
    rlwinm r4, r4, 0, 0x1f, 0x1d //Turn off recoverable exception flag
    mtmsr r4
    mtsprg 1, r2
    lwz r4, OSContext.gpr[3](r31)
    mtsprg 2, r4
    lwz r4, OSContext.gpr[4](r31)
    mtsprg 3, r4
    lwz r2, OSContext.srr0(r31)
    lwz r4, OSContext.srr1(r31)
    lwz r31, OSContext.gpr[31](r31)
    b TRKInterruptHandler
#endif // clang-format on
}

void TRKEXICallBack(__OSInterrupt param_0, OSContext* ctx)
{
    OSEnableScheduler();
    TRKLoadContext(ctx, 0x500);
}

int InitMetroTRKCommTable(int hwId)
{
#ifdef VERSION_GCCJGC
    int result;
    if (hwId == HARDWARE_GDEV) {
        OSReport("MetroTRK : Set to GDEV hardware\n");
        result = Hu_IsStub();
        gDBCommTable.initialize_func = (DBCommInitFunc)DBInitComm;
        gDBCommTable.init_interrupts_func = (DBCommFunc)DBInitInterrupts;
        gDBCommTable.peek_func = (DBCommFunc)DBQueryData;
        gDBCommTable.read_func = (DBCommReadFunc)DBRead;
        gDBCommTable.write_func = (DBCommWriteFunc)DBWrite;
        gDBCommTable.post_stop_func = (DBCommFunc)DBOpen;
        gDBCommTable.pre_continue_func = (DBCommFunc)DBClose;
    } else {
        OSReport("MetroTRK : Set to AMC DDH hardware\n");
        result = AMC_IsStub();
        gDBCommTable.initialize_func = (DBCommInitFunc)EXI2_Init;
        gDBCommTable.init_interrupts_func = (DBCommFunc)EXI2_EnableInterrupts;
        gDBCommTable.peek_func = (DBCommFunc)EXI2_Poll;
        gDBCommTable.read_func = (DBCommReadFunc)EXI2_ReadN;
        gDBCommTable.write_func = (DBCommWriteFunc)EXI2_WriteN;
        gDBCommTable.post_stop_func = (DBCommFunc)EXI2_Reserve;
        gDBCommTable.pre_continue_func = (DBCommFunc)EXI2_Unreserve;
    }
    return result;
#else
    int result = 1;

    OSReport("Devkit set to : %ld\n", hwId);
    TRK_Use_BBA = 0;

    if (hwId == HARDWARE_BBA) {
        OSReport("MetroTRK : Set to BBA\n");
        TRK_Use_BBA = 1;

        gDBCommTable.initialize_func      = (DBCommInitFunc)udp_cc_initialize;
        gDBCommTable.open_func            = udp_cc_open;
        gDBCommTable.close_func           = udp_cc_close;
        gDBCommTable.read_func            = udp_cc_read;
        gDBCommTable.write_func           = udp_cc_write;
        gDBCommTable.shutdown_func        = udp_cc_shutdown;
        gDBCommTable.peek_func            = udp_cc_peek;
        gDBCommTable.pre_continue_func    = udp_cc_pre_continue;
        gDBCommTable.post_stop_func       = udp_cc_post_stop;
        gDBCommTable.init_interrupts_func = NULL;
        return 0;
    }

    if (hwId == HARDWARE_GDEV) {
        OSReport("MetroTRK : Set to GDEV hardware\n");
        result = Hu_IsStub();

        gDBCommTable.initialize_func      = gdev_cc_initialize;
        gDBCommTable.open_func            = gdev_cc_open;
        gDBCommTable.close_func           = gdev_cc_close;
        gDBCommTable.read_func            = gdev_cc_read;
        gDBCommTable.write_func           = gdev_cc_write;
        gDBCommTable.shutdown_func        = gdev_cc_shutdown;
        gDBCommTable.peek_func            = gdev_cc_peek;
        gDBCommTable.pre_continue_func    = gdev_cc_pre_continue;
        gDBCommTable.post_stop_func       = gdev_cc_post_stop;
        gDBCommTable.init_interrupts_func = gdev_cc_initinterrupts;
    } else if (hwId == HARDWARE_AMC_DDH) {

        OSReport("MetroTRK : Set to AMC DDH hardware\n");
        result = AMC_IsStub();

        gDBCommTable.initialize_func      = ddh_cc_initialize;
        gDBCommTable.open_func            = ddh_cc_open;
        gDBCommTable.close_func           = ddh_cc_close;
        gDBCommTable.read_func            = ddh_cc_read;
        gDBCommTable.write_func           = ddh_cc_write;
        gDBCommTable.shutdown_func        = ddh_cc_shutdown;
        gDBCommTable.peek_func            = ddh_cc_peek;
        gDBCommTable.pre_continue_func    = ddh_cc_pre_continue;
        gDBCommTable.post_stop_func       = ddh_cc_post_stop;
        gDBCommTable.init_interrupts_func = ddh_cc_initinterrupts;
    } else {
        OSReport("MetroTRK : Set to UNKNOWN hardware. (%ld)\n", hwId);
        OSReport("MetroTRK : Invalid hardware ID passed from OS\n");
        OSReport("MetroTRK : Defaulting to GDEV Hardware\n");
    }

    return result;
#endif
}

DSError TRKInitializeIntDrivenUART(u32 param_0, u32 param_1, u32 param_2, void* param_3)
{
    gDBCommTable.initialize_func(param_3, TRKEXICallBack);
#ifndef VERSION_GCCJGC
    gDBCommTable.open_func();
#endif
    return DS_NoError;
}

void EnableEXI2Interrupts(void)
{
#ifdef VERSION_GCCJGC
    gDBCommTable.init_interrupts_func();
#else
    if (TRK_Use_BBA == 0 && gDBCommTable.init_interrupts_func != NULL) {
        gDBCommTable.init_interrupts_func();
    }
#endif
}

int TRKPollUART(void) 
{
    return gDBCommTable.peek_func();
}

UARTError TRKReadUARTN(void* bytes, u32 length)
{
    int readErr = gDBCommTable.read_func(bytes, length);
    return readErr == 0 ? 0 : -1;
}

UARTError TRKWriteUARTN(const void* bytes, u32 length)
{
    int writeErr = gDBCommTable.write_func(bytes, length);
    return writeErr == 0 ? 0 : -1;
}

#ifdef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x801AA2C0
 * JP Size: 224b
 */
UARTError WriteUARTFlush(void)
{
    UARTError err = UART_NoError;
    for (; gWritePos < 0x800; gWritePos++) {
        gWriteBuf[gWritePos] = 0;
    }
    if (gWritePos != 0) {
        int writeErr = gDBCommTable.write_func(gWriteBuf, gWritePos);
        err = writeErr == 0 ? 0 : -1;
        gWritePos = 0;
    }
    return err;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x801AA298
 * JP Size: 40b
 */
UARTError WriteUART1(u8 byte)
{
    gWriteBuf[gWritePos++] = byte;
    return UART_NoError;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x801AA1A8
 * JP Size: 240b
 */
UARTError TRKReadUARTPoll(u8* byte)
{
    UARTError err = UART_NoData;

    if (gReadPos >= gReadCount) {
        gReadPos = 0;
        gReadCount = gDBCommTable.peek_func();
        if (gReadCount > 0) {
            int readErr;
            if (gReadCount > (int)sizeof(gReadBuf)) {
                gReadCount = sizeof(gReadBuf);
            }
            readErr = gDBCommTable.read_func(gReadBuf, gReadCount);
            err = readErr == 0 ? 0 : -1;
            if (err != UART_NoError) {
                gReadCount = 0;
            }
        }
    }
    if (gReadPos < gReadCount) {
        *byte = gReadBuf[gReadPos++];
        err = UART_NoError;
    }
    return err;
}
#endif

void ReserveEXI2Port(void) { gDBCommTable.post_stop_func(); }

void UnreserveEXI2Port(void) { gDBCommTable.pre_continue_func(); }

void TRK_board_display(char* str) { OSReport("%s\n", str); }

/*
 * --INFO--
 * PAL Address: 0x801AE160
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitializeProgramEndTrap(void)
{
    static const u32 EndofProgramInstruction = 0x00454E44;
    register u8* ppcHalt = (u8*)PPCHalt;

    TRK_memcpy(ppcHalt + 4, &EndofProgramInstruction, 4);
    ICInvalidateRange(ppcHalt + 4, 4);
    DCFlushRange(ppcHalt + 4, 4);
}

void TRKUARTInterruptHandler() { }
