#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/main_TRK.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mem_TRK.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/flush_cache.h"
#include "dolphin/ar.h"
#include "dolphin/ar/__ar.h"
#include "dolphin/os/OSReset.h"
#include "stddef.h"

#define EXCEPTIONMASK_ADDR 0x80000044

static u32 lc_base;
extern u32 _db_stack_addr;
extern void* TRK_memcpy(void* dst, const void* src, unsigned int n);

static u32 TRK_ISR_OFFSETS[15] = { PPC_SystemReset,
	                               PPC_MachineCheck,
	                               PPC_DataStorage,
	                               PPC_InstructionStorage,
	                               PPC_ExternalInterrupt,
	                               PPC_Alignment,
	                               PPC_Program,
	                               PPC_FloatingPointUnavaiable,
	                               PPC_Decrementer,
	                               PPC_SystemCall,
	                               PPC_Trace,
	                               PPC_PerformanceMonitor,
	                               PPC_InstructionAddressBreakpoint,
	                               PPC_SystemManagementInterrupt,
	                               PPC_ThermalManagementInterrupt };

/*
 * --INFO--
 * PAL Address: 0x800053E0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
__declspec(section ".init") void __TRK_reset(void) { OSResetSystem(0, 0, 0); }

asm void InitMetroTRK()
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	addi r1, r1, -4
	stw r3, 0(r1)
	lis r3, gTRKCPUState@h
	ori r3, r3, gTRKCPUState@l
	stmw r0, ProcessorState_PPC.Default.GPR(r3) //Save the gprs
	lwz r4, 0(r1)
	addi r1, r1, 4
	stw r1, ProcessorState_PPC.Default.GPR[1](r3)
	stw r4, ProcessorState_PPC.Default.GPR[3](r3)
	mflr r4
	stw r4, ProcessorState_PPC.Default.LR(r3)
	stw r4, ProcessorState_PPC.Default.PC(r3)
	mfcr r4
	stw r4, ProcessorState_PPC.Default.CR(r3)
	//???
	mfmsr r4
	ori r3, r4, (1 << (31 - 16))
	xori r3, r3, (1 << (31 - 16))
	mtmsr r3
	mtsrr1 r4 //Copy msr to srr1
	//Save misc registers to gTRKCPUState
	bl TRKSaveExtended1Block
	lis r3, gTRKCPUState@h
	ori r3, r3, gTRKCPUState@l
	lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
	//Reset IABR and DABR
	li r0, 0
	mtspr  0x3f2, r0
	mtspr  0x3f5, r0
	//Restore stack pointer
	lis r1, _db_stack_addr@h
	ori r1, r1, _db_stack_addr@l
	mr r3, r5
	bl InitMetroTRKCommTable //Initialize comm table
	/*
	If InitMetroTRKCommTable returned 1 (failure), an invalid hardware
	id or the id for GDEV was somehow passed. Since only BBA or NDEV
	are supported, we return early. Otherwise, we proceed with
	starting up TRK.
	*/
	cmpwi r3, 1
	bne initCommTableSuccess
	/*
	BUG: The code probably orginally reloaded gTRKCPUState here, but
	as is it will read the returned value of InitMetroTRKCommTable
	as a TRKCPUState struct pointer, causing the CPU to return to
	a garbage code address.
	*/
	lwz r4, ProcessorState_PPC.Default.LR(r3)
	mtlr r4
	lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
	blr
initCommTableSuccess:
	b TRK_main //Jump to TRK_main
#endif // clang-format on
}

/*
 * --INFO--
 * PAL Address: 0x801ADAD8
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
asm void InitMetroTRK_BBA(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	addi r1, r1, -4
	stw r3, 0(r1)
	lis r3, gTRKCPUState@h
	ori r3, r3, gTRKCPUState@l
	stmw r0, ProcessorState_PPC.Default.GPR(r3)
	lwz r4, 0(r1)
	addi r1, r1, 4
	stw r1, ProcessorState_PPC.Default.GPR[1](r3)
	stw r4, ProcessorState_PPC.Default.GPR[3](r3)
	mflr r4
	stw r4, ProcessorState_PPC.Default.LR(r3)
	stw r4, ProcessorState_PPC.Default.PC(r3)
	mfcr r4
	stw r4, ProcessorState_PPC.Default.CR(r3)
	mfmsr r4
	ori r3, r4, (1 << (31 - 16))
	mtmsr r3
	mtsrr1 r4
	bl TRKSaveExtended1Block
	lis r3, gTRKCPUState@h
	ori r3, r3, gTRKCPUState@l
	lmw r0, ProcessorState_PPC.Default.GPR(r3)
	li r0, 0
	mtspr  0x3f2, r0
	mtspr  0x3f5, r0
	lis r1, _db_stack_addr@h
	ori r1, r1, _db_stack_addr@l
	li r3, 2
	bl InitMetroTRKCommTable
	cmpwi r3, 1
	bne initCommTableSuccessBBA
	lwz r4, ProcessorState_PPC.Default.LR(r3)
	mtlr r4
	lmw r0, ProcessorState_PPC.Default.GPR(r3)
	blr
initCommTableSuccessBBA:
	b TRK_main
	blr
#endif // clang-format on
}

void EnableMetroTRKInterrupts(void) { EnableEXI2Interrupts(); }

u32 TRKTargetTranslate(u32 param_0)
{
	if (param_0 >= lc_base) {
		if ((param_0 < lc_base + 0x4000)
		    && ((gTRKCPUState.Extended1.DBAT3U & 3) != 0)) {
			return param_0;
		}
	}

	if ((param_0 >= 0x7E000000) && (param_0 <= 0x80000000)) {
		return param_0;
	}

	return param_0 & 0x3FFFFFFF | 0x80000000;
}

extern u8 gTRKInterruptVectorTable[];

void TRK_copy_vector(u32 offset)
{
	void* destPtr = (void*)TRKTargetTranslate(offset);
	TRK_memcpy(destPtr, gTRKInterruptVectorTable + offset, 0x100);
	TRK_flush_cache(destPtr, 0x100);
}

void __TRK_copy_vectors(void)
{
	int i;
	u32 mask;

	mask = *(u32*)TRKTargetTranslate(0x44);

	for (i = 0; i <= 14; ++i) {
		if ((mask & (1 << i)) && i != 4) {
			TRK_copy_vector(TRK_ISR_OFFSETS[i]);
		}
	}
}

DSError TRKInitializeTarget()
{
	gTRKState.isStopped = TRUE;
	gTRKState.msr       = __TRK_get_MSR();
	lc_base             = 0xE0000000;
	return DS_NoError;
}

static asm void dataCacheBlockInvalidate(register void* param_1)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	dcbi 0, param_1
	blr
#endif // clang-format on
}

static asm void dataCacheBlockFlush(register void* param_1)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	dcbf 0, param_1
	blr
#endif // clang-format on
}

static asm void trkSync(register int param_1)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	sync
	blr
#endif // clang-format on
}

void TRK__write_aram(register u32 param_1, register u32 param_2, u32* param_3)
{
	u32 uVar1;
	u32 uVar2;
	u16 sVar3;
	u16 sVar4;
	u32 iVar5;
	u32 uVar6;
	u32 uVar7;
	u8 auStack_60[60];

	if (param_2 < 0x4000) {
		return;
	}
	if (0x8000000 < param_2 + *param_3) {
		return;
	}
	uVar1 = param_2 & 0xFFFFFFE0;
	iVar5 = 0;
	uVar2 = (*param_3 + (param_2 & 0x1F) + 0x1F) & 0xFFFFFFE0;
	uVar7 = (uVar2 + 0x1F) >> 5;
	if (uVar2 != 0) {
		uVar6 = (uVar2 + 0x1F) >> 8;
		if (uVar6 != 0) {
			do {
				dataCacheBlockFlush((void*)(param_1 + iVar5));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0x20));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0x40));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0x60));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0x80));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0xA0));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0xC0));
				dataCacheBlockFlush((void*)(param_1 + iVar5 + 0xE0));
				iVar5 += 0x100;
				uVar6--;
			} while (uVar6 != 0);
			uVar7 &= 7;
			if (uVar7 == 0) {
				goto LAB_801adc44;
			}
		}
		do {
			dataCacheBlockFlush((void*)(param_1 + iVar5));
			iVar5 += 0x20;
			uVar7--;
		} while (uVar7 != 0);
	}
LAB_801adc44:
	do {
		iVar5 = ARGetDMAStatus();
	} while (iVar5 != 0);

	sVar3 = __ARGetInterruptStatus();
	uVar7 = 0x8000000;
	if ((param_2 & 0x1F) != 0) {
		dataCacheBlockInvalidate(auStack_60);
		__ARClearInterrupt();
		ARStartDMA(1, (u32)auStack_60, uVar1, 0x20);
		do {
			sVar4 = __ARGetInterruptStatus();
		} while (sVar4 == 0);
		TRK_memcpy((void*)param_1, auStack_60, param_2 & 0x1F);
		dataCacheBlockFlush((void*)param_1);
		uVar7 = uVar1;
	}

	param_2 += *param_3;
	uVar6 = param_2 & 0x1F;
	if (uVar6 != 0) {
		if ((param_2 & 0xFFFFFFE0) != uVar7) {
			dataCacheBlockInvalidate(auStack_60);
			__ARClearInterrupt();
			ARStartDMA(1, (u32)auStack_60, param_2 & 0xFFFFFFE0, 0x20);
			do {
				sVar4 = __ARGetInterruptStatus();
			} while (sVar4 == 0);
		}
		TRK_memcpy((void*)(param_1 + param_2), auStack_60 + uVar6, 0x20 - uVar6);
		dataCacheBlockFlush((void*)(param_1 + param_2));
	}
	trkSync(0);
	__ARClearInterrupt();
	ARStartDMA(0, param_1, uVar1, uVar2);
	if (sVar3 == 0) {
		do {
			sVar3 = __ARGetInterruptStatus();
		} while (sVar3 == 0);
		__ARClearInterrupt();
	}
}

void TRK__read_aram(register u32 param_1, register u32 param_2, u32* param_3)
{
	u32 uVar1;
	u32 uVar2;
	u16 sVar3;
	u16 sVar4;
	u32 iVar5;
	u32 uVar6;
	u32 uVar7;

	if (param_2 < 0x4000) {
		return;
	}
	if (0x8000000 < param_2 + *param_3) {
		return;
	}

	iVar5 = 0;
	uVar1 = (*param_3 + (param_2 & 0x1F) + 0x1F) & 0xFFFFFFE0;
	uVar2 = (uVar1 + 0x1F) >> 5;
	if (uVar1 != 0) {
		uVar6 = (uVar1 + 0x1F) >> 8;
		uVar7 = uVar2;
		if (uVar6 != 0) {
			do {
				dataCacheBlockInvalidate((void*)(param_1 + iVar5));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0x20));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0x40));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0x60));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0x80));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0xA0));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0xC0));
				dataCacheBlockInvalidate((void*)(param_1 + iVar5 + 0xE0));
				iVar5 += 0x100;
				uVar6--;
			} while (uVar6 != 0);
			uVar7 = uVar2 & 7;
			uVar2 = uVar7;
			if (uVar7 == 0) {
				goto LAB_801ade28;
			}
		}
		do {
			dataCacheBlockInvalidate((void*)(param_1 + iVar5));
			iVar5 += 0x20;
			uVar7--;
		} while (uVar7 != 0);
	}
LAB_801ade28:
	do {
		uVar2 = ARGetDMAStatus();
	} while (uVar2 != 0);
	sVar3 = __ARGetInterruptStatus();
	__ARClearInterrupt();
	ARStartDMA(1, param_1, param_2 & 0xFFFFFFE0, uVar1);
	do {
		sVar4 = __ARGetInterruptStatus();
	} while (sVar4 == 0);
	if (sVar3 == 0) {
		__ARClearInterrupt();
	}
}
