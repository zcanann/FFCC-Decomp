	.include "asm/function.inc"
	.include "asm/asm.inc"
	.include "asm/gba_constants.inc"
	.include "asm/m4a_constants.inc"

	.syntax unified


	.text

	thumb_func_start umul3232H32
umul3232H32:
	adr r2, __umul3232H32
	bx r2
	.arm
__umul3232H32:
	umull r2, r3, r0, r1
	add r0, r3, 0
	bx lr
	thumb_func_end umul3232H32

	thumb_func_start m4aSoundVSync
m4aSoundVSync:
	ldr r0, lt2_SOUND_INFO_PTR
	ldr r0, [r0]

	@ Exit the function if ident is not ID_NUMBER or ID_NUMBER+1.
	ldr r2, lt2_ID_NUMBER
	ldr r3, [r0, o_SoundInfo_ident]
	subs r3, r2
	cmp r3, 1
	bhi m4aSoundVSync_Done

	@ Decrement the PCM DMA counter. If it reaches 0, we need to do a DMA.
	ldrb r1, [r0, o_SoundInfo_pcmDmaCounter]
	subs r1, 1
	strb r1, [r0, o_SoundInfo_pcmDmaCounter]
	bgt m4aSoundVSync_Done

	@ Reload the PCM DMA counter.
	ldrb r1, [r0, o_SoundInfo_pcmDmaPeriod]
	strb r1, [r0, o_SoundInfo_pcmDmaCounter]

	ldr r2, =REG_DMA1

	ldr r1, [r2, 0x8] @ DMA1CNT
	lsls r1, 7
	bcc m4aSoundVSync_SkipDMA1 @ branch if repeat bit isn't set

	ldr r1, =((DMA_ENABLE | DMA_START_NOW | DMA_32BIT | DMA_SRC_INC | DMA_DEST_FIXED) << 16) | 4
	str r1, [r2, 0x8] @ DMA1CNT

m4aSoundVSync_SkipDMA1:
	ldr r1, [r2, 0xC + 0x8] @ DMA2CNT
	lsls r1, 7
	bcc m4aSoundVSync_SkipDMA2 @ branch if repeat bit isn't set

	ldr r1, =((DMA_ENABLE | DMA_START_NOW | DMA_32BIT | DMA_SRC_INC | DMA_DEST_FIXED) << 16) | 4
	str r1, [r2, 0xC + 0x8] @ DMA2CNT

m4aSoundVSync_SkipDMA2:

	@ turn off DMA1/DMA2
	movs r1, DMA_32BIT >> 8
	lsls r1, 8
	strh r1, [r2, 0xA]       @ DMA1CNT_H
	strh r1, [r2, 0xC + 0xA] @ DMA2CNT_H

	@ turn on DMA1/DMA2 direct-sound FIFO mode
	movs r1, (DMA_ENABLE | DMA_START_SPECIAL | DMA_32BIT | DMA_REPEAT) >> 8
	lsls r1, 8 @ LSB is 0, so DMA_SRC_INC is used (destination is always fixed in FIFO mode)
	strh r1, [r2, 0xA]       @ DMA1CNT_H
	strh r1, [r2, 0xC + 0xA] @ DMA2CNT_H

m4aSoundVSync_Done:
	bx lr

	.pool
	thumb_func_end m4aSoundVSync

	thumb_func_start MPlayMain
MPlayMain:
	ldr r2, lt2_ID_NUMBER
	ldr r3, [r0, o_MusicPlayerInfo_ident]
	cmp r2, r3
	beq _081DD82E
	bx lr
_081DD82E:
	adds r3, 0x1
	str r3, [r0, o_MusicPlayerInfo_ident]
	push {r0,lr}
	ldr r3, [r0, o_MusicPlayerInfo_func]
	cmp r3, 0
	beq _081DD840
	ldr r0, [r0, o_MusicPlayerInfo_intp]
	bl call_r3
_081DD840:
	pop {r0}
	push {r4-r7}
	mov r4, r8
	mov r5, r9
	mov r6, r10
	mov r7, r11
	push {r4-r7}
	adds r7, r0, 0
	ldr r0, [r7, o_MusicPlayerInfo_status]
	cmp r0, 0
	bge _081DD858
	b _081DDA6C
_081DD858:
	ldr r0, lt2_SOUND_INFO_PTR
	ldr r0, [r0]
	mov r8, r0
	adds r0, r7, 0
	bl FadeOutBody
	ldr r0, [r7, o_MusicPlayerInfo_status]
	cmp r0, 0
	bge _081DD86C
	b _081DDA6C
_081DD86C:
	ldrh r0, [r7, o_MusicPlayerInfo_tempoC]
	ldrh r1, [r7, o_MusicPlayerInfo_tempoI]
	adds r0, r1
	b _081DD9BC
_081DD874:
	ldrb r6, [r7, o_MusicPlayerInfo_trackCount]
	ldr r5, [r7, o_MusicPlayerInfo_tracks]
	movs r3, 0x1
	movs r4, 0
_081DD87C:
	ldrb r0, [r5]
	movs r1, 0x80
	tst r1, r0
	bne _081DD886
	b _081DD998
_081DD886:
	mov r10, r3
	orrs r4, r3
	mov r11, r4
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq _081DD8BA
_081DD892:
	ldrb r1, [r4]
	movs r0, 0xC7
	tst r0, r1
	beq _081DD8AE
	ldrb r0, [r4, 0x10]
	cmp r0, 0
	beq _081DD8B4
	subs r0, 0x1
	strb r0, [r4, 0x10]
	bne _081DD8B4
	movs r0, 0x40
	orrs r1, r0
	strb r1, [r4]
	b _081DD8B4
_081DD8AE:
	adds r0, r4, 0
	bl ClearChain
_081DD8B4:
	ldr r4, [r4, 0x34]
	cmp r4, 0
	bne _081DD892
_081DD8BA:
	ldrb r3, [r5, o_MusicPlayerTrack_flags]
	movs r0, 0x40
	tst r0, r3
	beq _081DD938
	adds r0, r5, 0
	bl Clear64byte
	movs r0, 0x80
	strb r0, [r5]
	movs r0, 0x2
	strb r0, [r5, o_MusicPlayerTrack_bendRange]
	movs r0, 0x40
	strb r0, [r5, o_MusicPlayerTrack_volX]
	movs r0, 0x16
	strb r0, [r5, o_MusicPlayerTrack_lfoSpeed]
	movs r0, 0x1
	adds r1, r5, 0x6
	strb r0, [r1, o_MusicPlayerTrack_ToneData_type - 0x6]
	b _081DD938
_081DD8E0:
	ldr r2, [r5, o_MusicPlayerTrack_cmdPtr]
	ldrb r1, [r2]
	cmp r1, 0x80
	bhs _081DD8EC
	ldrb r1, [r5, o_MusicPlayerTrack_runningStatus]
	b _081DD8F6
_081DD8EC:
	adds r2, 0x1
	str r2, [r5, o_MusicPlayerTrack_cmdPtr]
	cmp r1, 0xBD
	bcc _081DD8F6
	strb r1, [r5, o_MusicPlayerTrack_runningStatus]
_081DD8F6:
	cmp r1, 0xCF
	bcc _081DD90C
	mov r0, r8
	ldr r3, [r0, o_SoundInfo_plynote]
	adds r0, r1, 0
	subs r0, 0xCF
	adds r1, r7, 0
	adds r2, r5, 0
	bl call_r3
	b _081DD938
_081DD90C:
	cmp r1, 0xB0
	bls _081DD92E
	adds r0, r1, 0
	subs r0, 0xB1
	strb r0, [r7, o_MusicPlayerInfo_cmd]
	mov r3, r8
	ldr r3, [r3, o_SoundInfo_MPlayJumpTable]
	lsls r0, 2
	ldr r3, [r3, r0]
	adds r0, r7, 0
	adds r1, r5, 0
	bl call_r3
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	cmp r0, 0
	beq _081DD994
	b _081DD938
_081DD92E:
	ldr r0, lt_gClockTable
	subs r1, 0x80
	adds r1, r0
	ldrb r0, [r1]
	strb r0, [r5, o_MusicPlayerTrack_wait]
_081DD938:
	ldrb r0, [r5, o_MusicPlayerTrack_wait]
	cmp r0, 0
	beq _081DD8E0
	subs r0, 0x1
	strb r0, [r5, o_MusicPlayerTrack_wait]
	ldrb r1, [r5, o_MusicPlayerTrack_lfoSpeed]
	cmp r1, 0
	beq _081DD994
	ldrb r0, [r5, o_MusicPlayerTrack_mod]
	cmp r0, 0
	beq _081DD994
	ldrb r0, [r5, o_MusicPlayerTrack_lfoDelayC]
	cmp r0, 0
	beq _081DD95A
	subs r0, 0x1
	strb r0, [r5, o_MusicPlayerTrack_lfoDelayC]
	b _081DD994
_081DD95A:
	ldrb r0, [r5, o_MusicPlayerTrack_lfoSpeedC]
	adds r0, r1
	strb r0, [r5, o_MusicPlayerTrack_lfoSpeedC]
	adds r1, r0, 0
	subs r0, 0x40
	lsls r0, 24
	bpl _081DD96E
	lsls r2, r1, 24
	asrs r2, 24
	b _081DD972
_081DD96E:
	movs r0, 0x80
	subs r2, r0, r1
_081DD972:
	ldrb r0, [r5, o_MusicPlayerTrack_mod]
	muls r0, r2
	asrs r2, r0, 6
	ldrb r0, [r5, o_MusicPlayerTrack_modM]
	eors r0, r2
	lsls r0, 24
	beq _081DD994
	strb r2, [r5, o_MusicPlayerTrack_modM]
	ldrb r0, [r5]
	ldrb r1, [r5, o_MusicPlayerTrack_modT]
	cmp r1, 0
	bne _081DD98E
	movs r1, 0xC
	b _081DD990
_081DD98E:
	movs r1, 0x3
_081DD990:
	orrs r0, r1
	strb r0, [r5, o_MusicPlayerTrack_flags]
_081DD994:
	mov r3, r10
	mov r4, r11
_081DD998:
	subs r6, 0x1
	ble _081DD9A4
	movs r0, 0x50
	adds r5, r0
	lsls r3, 1
	b _081DD87C
_081DD9A4:
	ldr r0, [r7, o_MusicPlayerInfo_clock]
	adds r0, 0x1
	str r0, [r7, o_MusicPlayerInfo_clock]
	cmp r4, 0
	bne _081DD9B6
	movs r0, 0x80
	lsls r0, 24
	str r0, [r7, o_MusicPlayerInfo_status]
	b _081DDA6C
_081DD9B6:
	str r4, [r7, o_MusicPlayerInfo_status]
	ldrh r0, [r7, o_MusicPlayerInfo_tempoC]
	subs r0, 0x96
_081DD9BC:
	strh r0, [r7, o_MusicPlayerInfo_tempoC]
	cmp r0, 0x96
	bcc _081DD9C4
	b _081DD874
_081DD9C4:
	ldrb r2, [r7, o_MusicPlayerInfo_trackCount]
	ldr r5, [r7, o_MusicPlayerInfo_tracks]
_081DD9C8:
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	movs r1, 0x80
	tst r1, r0
	beq _081DDA62
	movs r1, 0xF
	tst r1, r0
	beq _081DDA62
	mov r9, r2
	adds r0, r7, 0
	adds r1, r5, 0
	bl TrkVolPitSet
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq _081DDA58
_081DD9E6:
	ldrb r1, [r4, o_SoundChannel_status]
	movs r0, 0xC7
	tst r0, r1
	bne _081DD9F6
	adds r0, r4, 0
	bl ClearChain
	b _081DDA52
_081DD9F6:
	ldrb r0, [r4, o_SoundChannel_type]
	movs r6, 0x7
	ands r6, r0
	ldrb r3, [r5, o_MusicPlayerTrack_flags]
	movs r0, 0x3
	tst r0, r3
	beq _081DDA14
	bl ChnVolSetAsm
	cmp r6, 0
	beq _081DDA14
	ldrb r0, [r4, o_CgbChannel_mo]
	movs r1, 0x1
	orrs r0, r1
	strb r0, [r4, o_CgbChannel_mo]
_081DDA14:
	ldrb r3, [r5, o_MusicPlayerTrack_flags]
	movs r0, 0xC
	tst r0, r3
	beq _081DDA52
	ldrb r1, [r4, o_SoundChannel_ky]
	movs r0, 0x8
	ldrsb r0, [r5, r0]
	adds r2, r1, r0
	bpl _081DDA28
	movs r2, 0
_081DDA28:
	cmp r6, 0
	beq _081DDA46
	mov r0, r8
	ldr r3, [r0, o_SoundInfo_MidiKeyToCgbFreq]
	adds r1, r2, 0
	ldrb r2, [r5, o_MusicPlayerTrack_pitM]
	adds r0, r6, 0
	bl call_r3
	str r0, [r4, o_CgbChannel_fr]
	ldrb r0, [r4, o_CgbChannel_mo]
	movs r1, 0x2
	orrs r0, r1
	strb r0, [r4, o_CgbChannel_mo]
	b _081DDA52
_081DDA46:
	adds r1, r2, 0
	ldrb r2, [r5, o_MusicPlayerTrack_pitM]
	ldr r0, [r4, o_SoundChannel_wav]
	bl MidiKeyToFreq
	str r0, [r4, o_SoundChannel_freq]
_081DDA52:
	ldr r4, [r4, o_SoundChannel_np]
	cmp r4, 0
	bne _081DD9E6
_081DDA58:
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	movs r1, 0xF0
	ands r0, r1
	strb r0, [r5, o_MusicPlayerTrack_flags]
	mov r2, r9
_081DDA62:
	subs r2, 0x1
	ble _081DDA6C
	movs r0, 0x50
	adds r5, r0
	bgt _081DD9C8
_081DDA6C:
	ldr r0, lt2_ID_NUMBER
	str r0, [r7, o_MusicPlayerInfo_ident]
	pop {r0-r7}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	pop {r3}

call_r3:
	bx r3

	.align 2, 0
lt_gClockTable:     .word gClockTable
lt2_SOUND_INFO_PTR: .word SOUND_INFO_PTR
lt2_ID_NUMBER:      .word ID_NUMBER
	thumb_func_end MPlayMain

	thumb_func_start TrackStop
TrackStop:
	push {r4-r6,lr}
	adds r5, r1, 0
	ldrb r1, [r5, o_MusicPlayerTrack_flags]
	movs r0, 0x80
	tst r0, r1
	beq TrackStop_Done
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq TrackStop_3
	movs r6, 0
TrackStop_Loop:
	ldrb r0, [r4, o_SoundChannel_status]
	cmp r0, 0
	beq TrackStop_2
	ldrb r0, [r4, o_SoundChannel_type]
	movs r3, 0x7
	ands r0, r3
	beq TrackStop_1
	ldr r3, =SOUND_INFO_PTR
	ldr r3, [r3]
	ldr r3, [r3, o_SoundInfo_CgbOscOff]
	bl call_r3
TrackStop_1:
	strb r6, [r4, o_SoundChannel_status]
TrackStop_2:
	str r6, [r4, o_SoundChannel_track]
	ldr r4, [r4, o_SoundChannel_np]
	cmp r4, 0
	bne TrackStop_Loop
TrackStop_3:
	str r4, [r5, o_MusicPlayerTrack_chan]
TrackStop_Done:
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end TrackStop

	thumb_func_start ChnVolSetAsm
ChnVolSetAsm:
	ldrb r1, [r4, 0x12]
	movs r0, 0x14
	ldrsb r2, [r4, r0]
	movs r3, 0x80
	adds r3, r2
	muls r3, r1
	ldrb r0, [r5, 0x10]
	muls r0, r3
	asrs r0, 14
	cmp r0, 0xFF
	bls _081DDAE8
	movs r0, 0xFF
_081DDAE8:
	strb r0, [r4, 0x2]
	movs r3, 0x7F
	subs r3, r2
	muls r3, r1
	ldrb r0, [r5, 0x11]
	muls r0, r3
	asrs r0, 14
	cmp r0, 0xFF
	bls _081DDAFC
	movs r0, 0xFF
_081DDAFC:
	strb r0, [r4, 0x3]
	bx lr
	thumb_func_end ChnVolSetAsm

	thumb_func_start ply_note
ply_note:
	push {r4-r7,lr}
	mov r4, r8
	mov r5, r9
	mov r6, r10
	mov r7, r11
	push {r4-r7}
	sub sp, 0x18
	str r1, [sp]
	adds r5, r2, 0
	ldr r1, =SOUND_INFO_PTR
	ldr r1, [r1]
	str r1, [sp, 0x4]
	ldr r1, =gClockTable
	adds r0, r1
	ldrb r0, [r0]
	strb r0, [r5, o_MusicPlayerTrack_gateTime]
	ldr r3, [r5, o_MusicPlayerTrack_cmdPtr]
	ldrb r0, [r3]
	cmp r0, 0x80
	bhs _081DDB46
	strb r0, [r5, o_MusicPlayerTrack_key]
	adds r3, 0x1
	ldrb r0, [r3]
	cmp r0, 0x80
	bhs _081DDB44
	strb r0, [r5, o_MusicPlayerTrack_velocity]
	adds r3, 0x1
	ldrb r0, [r3]
	cmp r0, 0x80
	bhs _081DDB44
	ldrb r1, [r5, o_MusicPlayerTrack_gateTime]
	adds r1, r0
	strb r1, [r5, o_MusicPlayerTrack_gateTime]
	adds r3, 0x1
_081DDB44:
	str r3, [r5, o_MusicPlayerTrack_cmdPtr]
_081DDB46:
	movs r0, 0
	str r0, [sp, 0x14]
	adds r4, r5, 0
	adds r4, o_MusicPlayerTrack_ToneData_type
	ldrb r2, [r4]
	movs r0, TONEDATA_TYPE_RHY | TONEDATA_TYPE_SPL
	tst r0, r2
	beq _081DDB98
	ldrb r3, [r5, o_MusicPlayerTrack_key]
	movs r0, TONEDATA_TYPE_SPL
	tst r0, r2
	beq _081DDB66
	ldr r1, [r5, o_MusicPlayerTrack_ToneData_keySplitTable]
	adds r1, r3
	ldrb r0, [r1]
	b _081DDB68
_081DDB66:
	adds r0, r3, 0
_081DDB68:
	lsls r1, r0, 1
	adds r1, r0
	lsls r1, 2
	ldr r0, [r5, o_MusicPlayerTrack_ToneData_wav]
	adds r1, r0
	mov r9, r1
	mov r6, r9
	ldrb r1, [r6]
	movs r0, 0xC0
	tst r0, r1
	beq _081DDB80
	b _081DDCEA
_081DDB80:
	movs r0, 0x80
	tst r0, r2
	beq _081DDB9C
	ldrb r1, [r6, 0x3]
	movs r0, 0x80
	tst r0, r1
	beq _081DDB94
	subs r1, 0xC0
	lsls r1, 1
	str r1, [sp, 0x14]
_081DDB94:
	ldrb r3, [r6, 0x1]
	b _081DDB9C
_081DDB98:
	mov r9, r4
	ldrb r3, [r5, 0x5]
_081DDB9C:
	str r3, [sp, 0x8]
	ldr r6, [sp]
	ldrb r1, [r6, 0x9]
	ldrb r0, [r5, 0x1D]
	adds r0, r1
	cmp r0, 0xFF
	bls _081DDBAC
	movs r0, 0xFF
_081DDBAC:
	str r0, [sp, 0x10]
	mov r6, r9
	ldrb r0, [r6]
	movs r6, 0x7
	ands r6, r0
	str r6, [sp, 0xC]
	beq _081DDBEC
	ldr r0, [sp, 0x4]
	ldr r4, [r0, 0x1C]
	cmp r4, 0
	bne _081DDBC4
	b _081DDCEA
_081DDBC4:
	subs r6, 0x1
	lsls r0, r6, 6
	adds r4, r0
	ldrb r1, [r4]
	movs r0, 0xC7
	tst r0, r1
	beq _081DDC40
	movs r0, 0x40
	tst r0, r1
	bne _081DDC40
	ldrb r1, [r4, 0x13]
	ldr r0, [sp, 0x10]
	cmp r1, r0
	bcc _081DDC40
	beq _081DDBE4
	b _081DDCEA
_081DDBE4:
	ldr r0, [r4, 0x2C]
	cmp r0, r5
	bcs _081DDC40
	b _081DDCEA
_081DDBEC:
	ldr r6, [sp, 0x10]
	adds r7, r5, 0
	movs r2, 0
	mov r8, r2
	ldr r4, [sp, 0x4]
	ldrb r3, [r4, 0x6]
	adds r4, 0x50
_081DDBFA:
	ldrb r1, [r4]
	movs r0, 0xC7
	tst r0, r1
	beq _081DDC40
	movs r0, 0x40
	tst r0, r1
	beq _081DDC14
	cmp r2, 0
	bne _081DDC18
	adds r2, 0x1
	ldrb r6, [r4, 0x13]
	ldr r7, [r4, 0x2C]
	b _081DDC32
_081DDC14:
	cmp r2, 0
	bne _081DDC34
_081DDC18:
	ldrb r0, [r4, 0x13]
	cmp r0, r6
	bcs _081DDC24
	adds r6, r0, 0
	ldr r7, [r4, 0x2C]
	b _081DDC32
_081DDC24:
	bhi _081DDC34
	ldr r0, [r4, 0x2C]
	cmp r0, r7
	bls _081DDC30
	adds r7, r0, 0
	b _081DDC32
_081DDC30:
	bcc _081DDC34
_081DDC32:
	mov r8, r4
_081DDC34:
	adds r4, 0x40
	subs r3, 0x1
	bgt _081DDBFA
	mov r4, r8
	cmp r4, 0
	beq _081DDCEA
_081DDC40:
	adds r0, r4, 0
	bl ClearChain
	movs r1, 0
	str r1, [r4, 0x30]
	ldr r3, [r5, 0x20]
	str r3, [r4, 0x34]
	cmp r3, 0
	beq _081DDC54
	str r4, [r3, 0x30]
_081DDC54:
	str r4, [r5, 0x20]
	str r5, [r4, 0x2C]
	ldrb r0, [r5, 0x1B]
	strb r0, [r5, 0x1C]
	cmp r0, r1
	beq _081DDC66
	adds r1, r5, 0
	bl clear_modM
_081DDC66:
	ldr r0, [sp]
	adds r1, r5, 0
	bl TrkVolPitSet
	ldr r0, [r5, 0x4]
	str r0, [r4, 0x10]
	ldr r0, [sp, 0x10]
	strb r0, [r4, 0x13]
	ldr r0, [sp, 0x8]
	strb r0, [r4, 0x8]
	ldr r0, [sp, 0x14]
	strb r0, [r4, 0x14]
	mov r6, r9
	ldrb r0, [r6]
	strb r0, [r4, 0x1]
	ldr r7, [r6, 0x4]
	str r7, [r4, 0x24]
	ldr r0, [r6, 0x8]
	str r0, [r4, 0x4]
	ldrh r0, [r5, 0x1E]
	strh r0, [r4, 0xC]
	bl ChnVolSetAsm
	ldrb r1, [r4, 0x8]
	movs r0, 0x8
	ldrsb r0, [r5, r0]
	adds r3, r1, r0
	bpl _081DDCA0
	movs r3, 0
_081DDCA0:
	ldr r6, [sp, 0xC]
	cmp r6, 0
	beq _081DDCCE
	mov r6, r9
	ldrb r0, [r6, 0x2]
	strb r0, [r4, 0x1E]
	ldrb r1, [r6, 0x3]
	movs r0, 0x80
	tst r0, r1
	bne _081DDCBA
	movs r0, 0x70
	tst r0, r1
	bne _081DDCBC
_081DDCBA:
	movs r1, 0x8
_081DDCBC:
	strb r1, [r4, 0x1F]
	ldrb r2, [r5, 0x9]
	adds r1, r3, 0
	ldr r0, [sp, 0xC]
	ldr r3, [sp, 0x4]
	ldr r3, [r3, 0x30]
	bl call_r3
	b _081DDCDC
_081DDCCE:
	ldrb r2, [r5, 0x9]
	adds r1, r3, 0
	adds r0, r7, 0
	bl MidiKeyToFreq
_081DDCDC:
	str r0, [r4, 0x20]
	movs r0, 0x80
	strb r0, [r4]
	ldrb r1, [r5]
	movs r0, 0xF0
	ands r0, r1
	strb r0, [r5]
_081DDCEA:
	add sp, 0x18
	pop {r0-r7}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	pop {r0}
	bx r0
	.pool
	thumb_func_end ply_note

	thumb_func_start ply_endtie
ply_endtie:
	push {r4,r5}
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	cmp r3, 0x80
	bhs _081DDD16
	strb r3, [r1, o_MusicPlayerTrack_key]
	adds r2, 0x1
	str r2, [r1, o_MusicPlayerTrack_cmdPtr]
	b _081DDD18
_081DDD16:
	ldrb r3, [r1, o_MusicPlayerTrack_key]
_081DDD18:
	ldr r1, [r1, o_MusicPlayerTrack_chan]
	cmp r1, 0
	beq _081DDD40
	movs r4, 0x83
	movs r5, 0x40
_081DDD22:
	ldrb r2, [r1, o_SoundChannel_status]
	tst r2, r4
	beq _081DDD3A
	tst r2, r5
	bne _081DDD3A
	ldrb r0, [r1, o_SoundChannel_mk]
	cmp r0, r3
	bne _081DDD3A
	movs r0, 0x40
	orrs r2, r0
	strb r2, [r1, o_SoundChannel_status]
	b _081DDD40
_081DDD3A:
	ldr r1, [r1, o_SoundChannel_np]
	cmp r1, 0
	bne _081DDD22
_081DDD40:
	pop {r4,r5}
	bx lr
	thumb_func_end ply_endtie

	thumb_func_start clear_modM
clear_modM:
	movs r2, 0
	strb r2, [r1, o_MusicPlayerTrack_modM]
	strb r2, [r1, o_MusicPlayerTrack_lfoSpeedC]
	ldrb r2, [r1, o_MusicPlayerTrack_modT]
	cmp r2, 0
	bne _081DDD54
	movs r2, 0xC
	b _081DDD56
_081DDD54:
	movs r2, 0x3
_081DDD56:
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx lr
	thumb_func_end clear_modM

	thumb_func_start ld_r3_tp_adr_i_unchecked
ld_r3_tp_adr_i_unchecked:
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	adds r3, r2, 1
	str r3, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	bx lr
	thumb_func_end ld_r3_tp_adr_i_unchecked

	thumb_func_start ply_lfos
ply_lfos:
	mov r12, lr
	bl ld_r3_tp_adr_i_unchecked
	strb r3, [r1, o_MusicPlayerTrack_lfoSpeed]
	cmp r3, 0
	bne _081DDD7C
	bl clear_modM
_081DDD7C:
	bx r12
	thumb_func_end ply_lfos

	thumb_func_start ply_mod
ply_mod:
	mov r12, lr
	bl ld_r3_tp_adr_i_unchecked
	strb r3, [r1, o_MusicPlayerTrack_mod]
	cmp r3, 0
	bne _081DDD90
	bl clear_modM
_081DDD90:
	bx r12
	thumb_func_end ply_mod

	.align 2, 0 @ Don't pad with nop.
