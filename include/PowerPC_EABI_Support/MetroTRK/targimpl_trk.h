#ifndef METROTRK_TARGIMPL_TRK_H
#define METROTRK_TARGIMPL_TRK_H

#include "dolphin/types.h"
#include "PowerPC_EABI_Support/MetroTRK/dstypes.h"
#include "PowerPC_EABI_Support/MetroTRK/trkenum.h"
#include "PowerPC_EABI_Support/MetroTRK/trktypes.h"
#include "PowerPC_EABI_Support/MetroTRK/ppc_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef MessageBuffer TRKBuffer;

void TRKSaveExtended1Block(void);

DSError TRKDoSetOption(TRKBuffer*);
DSError TRKDoStop(TRKBuffer*);
DSError TRKDoStep(TRKBuffer*);
DSError TRKDoContinue(TRKBuffer*);
DSError TRKDoWriteRegisters(TRKBuffer*);
DSError TRKDoReadRegisters(TRKBuffer*);
DSError TRKDoWriteMemory(TRKBuffer*);
DSError TRKDoReadMemory(TRKBuffer*);
DSError TRKDoSupportMask(TRKBuffer*);
DSError TRKDoVersions(TRKBuffer*);
DSError TRKDoOverride(TRKBuffer*);
DSError TRKDoReset(TRKBuffer*);
DSError TRKDoDisconnect(TRKBuffer*);
DSError TRKDoConnect(TRKBuffer*);

void SetBufferPosition(TRKBuffer*, u32);
void SetTRKConnected(int);
int GetTRKConnected(void);

DSError TRKGetFreeBuffer(int*, TRKBuffer**);
void OutputData(void* data, int length);
void TRKResetBuffer(TRKBuffer* msg, BOOL keepData);

DSError TRKReadBuffer1_ui64(TRKBuffer* buffer, u64* data);
DSError TRKAppendBuffer1_ui64(TRKBuffer* buffer, const u64 data);

void InitMetroTRK(void);
void InitMetroTRK_BBA(void);
void EnableMetroTRKInterrupts(void);

void TRKLoadContext(OSContext* ctx, u32);
void TRKRestoreExtended1Block(void);
int InitMetroTRKCommTable(int);
void TRK_board_display(char*);

int gdev_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int gdev_cc_shutdown(void);
int gdev_cc_open(void);
int gdev_cc_close(void);
int gdev_cc_read(u8* dest, int size);
int gdev_cc_write(const u8* src, int size);
int gdev_cc_pre_continue(void);
int gdev_cc_post_stop(void);
int gdev_cc_peek(void);
int gdev_cc_initinterrupts(void);

int udp_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int udp_cc_shutdown(void);
int udp_cc_open(void);
int udp_cc_close(void);
int udp_cc_read(u8* dest, int size);
int udp_cc_write(const u8* src, int size);
int udp_cc_pre_continue(void);
int udp_cc_post_stop(void);
int udp_cc_peek(void);
int udp_cc_initinterrupts(void);

#define DDH_ERR_NOT_INITIALIZED     -0x2711
#define DDH_ERR_ALREADY_INITIALIZED -0x2715
#define DDH_ERR_READ_ERROR          -0x2719

int ddh_cc_initialize(void* flagOut, __OSInterruptHandler handler);
int ddh_cc_shutdown(void);
int ddh_cc_open(void);
int ddh_cc_close(void);
int ddh_cc_read(u8* dest, int size);
int ddh_cc_write(const u8* src, int size);
int ddh_cc_pre_continue(void);
int ddh_cc_post_stop(void);
int ddh_cc_peek(void);
int ddh_cc_initinterrupts(void);

void TRKConstructEvent(TRKEvent* event, int eventType);
void TRKDestructEvent(TRKEvent* event);
DSError TRKPostEvent(TRKEvent* event);
BOOL TRKGetNextEvent(TRKEvent* event);
DSError TRKDispatchMessage(TRKBuffer*);
void* TRKGetBuffer(int);
void TRKReleaseBuffer(int);
void TRKGetInput(void);

DSError TRKTargetContinue(void);
DSError TRKTargetInterrupt(TRKEvent*);
BOOL TRKTargetStopped(void);
void TRKTargetSetStopped(uint);
DSError TRKTargetSupportRequest(void);

DSError TRKAppendBuffer_ui8(TRKBuffer*, const u8*, int);
DSError TRKSetBufferPosition(TRKBuffer*, u32);

DSError TRKMessageSend(TRKBuffer*);
void TRKSwapAndGo(void);
DSError TRKInitializeNub(void);
DSError TRKTerminateNub(void);
void TRKNubWelcome(void);
void TRKNubMainLoop(void);

DSError TRKInitializeMutex(void*);
DSError TRKAcquireMutex(void*);
DSError TRKReleaseMutex(void*);
void* TRK_memcpy(void* dst, const void* src, size_t n);

DSError TRKInitializeEventQueue(void);
DSError TRKInitializeMessageBuffers(void);
DSError TRKInitializeDispatcher(void);
DSError InitializeProgramEndTrap(void);
DSError TRKInitializeSerialHandler(void);
DSError TRKTerminateSerialHandler(void);
DSError TRKInitializeTarget(void);

void UnreserveEXI2Port(void);
void ReserveEXI2Port(void);

void MWTRACE(u8, char*, ...);

DSError TRKRequestSend(void);
u32 TRKAccessFile(u32, u32, u32*, u8*);

DSError TRK_main(void);
UARTError InitializeUART(UARTBaudRate baudRate);
DSError TRKInitializeIntDrivenUART(u32, u32, u32, void*);
int TRKPollUART(void);
UARTError TRKReadUARTN(void*, u32);
UARTError TRKWriteUARTN(const void* bytes, u32 length);
void usr_put_initialize(void);
void TRKTargetSetInputPendingPtr(void*);
void SetUseSerialIO(u8);
u8 GetUseSerialIO(void);

DSError TRKTargetAddStopInfo(TRKBuffer*);
void TRKTargetAddExceptionInfo(TRKBuffer*);
void TRKInterruptHandler(void);
BOOL usr_puts_serial(const char* msg);

extern BOOL gTRKBigEndian;
extern void* gTRKInputPendingPtr;
extern ProcessorState_PPC gTRKCPUState;
extern ProcessorRestoreFlags_PPC gTRKRestoreFlags;
extern u8 gTRKInterruptVectorTable[];
extern TRKState gTRKState;
extern TRKBuffer gTRKMessageBuffers[3];

static inline DSError TRKAppendBuffer1_ui8(TRKBuffer* buffer, const u8 data)
{
	if (buffer->position >= 0x880) {
		return DS_MessageBufferOverflow;
	}

	buffer->data[buffer->position++] = data;
	buffer->length++;
	return DS_NoError;
}

#ifdef __cplusplus
}
#endif

#endif
