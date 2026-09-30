	.text
	.arm

	.equ REG_BASE, 0x04000000
	.equ REG_SIO_BASE, REG_BASE + 0x130
	.equ INTR_VECTOR, 0x03007FFC
	.equ PSR_IRQ_MODE, 0x12
	.equ PSR_SYS_MODE, 0x1F

	.global _start
	.type _start, %function
_start:
	b	.Lram_entry

	.include "nintendo_logo.inc"

	.space	12				@ title
.Lgame_code:
	.ascii	"GCCJ"				@ game code
	.ascii	"GC"				@ maker code
	.byte	0x96				@ fixed value
	.byte	0				@ main unit code
	.byte	0				@ device type
	.space	7				@ reserved
	.byte	0				@ software version
	.byte	0xB0				@ complement check
	.space	2				@ reserved

	@ Multiboot header
.Lram_entry:
	b	start_vector			@ RAM entry point
	.byte	0				@ boot mode
	.byte	0				@ slave ID
	.space	26				@ reserved

	.size _start, . - _start

@ JOY Bus boot entry: switch the serial port to JOY Bus mode, send the game code,
@ and wait for the GameCube to reset and echo it back.
	.global joybus_entry
	.type joybus_entry, %function
joybus_entry:
	ldr	r3, =REG_SIO_BASE
	mov	r1, #0
	strh	r1, [r3, #0x10]
	mov	r1, #0xC0
	lsl	r1, r1, #8
	strh	r1, [r3, #4]
1:
	ldrh	r1, [r3, #0x28]
	ands	r1, r1, #8
	bne	1b
	ldr	r2, =.Lgame_code
	ldr	r1, [r2]
	str	r1, [r3, #0x24]
2:
	ldrh	r0, [r3, #0x10]
	and	r0, r0, #7
	cmp	r0, #4
	bne	2b
	strh	r0, [r3, #0x10]
3:
	ldrh	r0, [r3, #0x10]
	and	r0, r0, #7
	cmp	r0, #2
	bne	3b
	strh	r0, [r3, #0x10]
	ldr	r0, [r3, #0x20]
	cmp	r0, r1
4:
	bne	4b

	.size joybus_entry, . - joybus_entry

	.global start_vector
	.type start_vector, %function
start_vector:
	mov	r0, #PSR_IRQ_MODE
	msr	cpsr_fc, r0
	ldr	sp, .Lsp_irq
	mov	r0, #PSR_SYS_MODE
	msr	cpsr_fc, r0
	ldr	sp, .Lsp_usr
	ldr	r1, =INTR_VECTOR
	adr	r0, intr_main
	str	r0, [r1]
	ldr	r1, =AgbMain
	mov	lr, pc
	bx	r1
	b	start_vector

.Lsp_usr:	.word	0x03007E00
.Lsp_irq:	.word	0x03007FA0

	.size start_vector, . - start_vector

@ Acknowledges the highest-priority pending interrupt and jumps to its handler
@ in IntrTable. A game pak interrupt (cartridge removed) halts.
	.global intr_main
	.type intr_main, %function
intr_main:
	mov	r12, #REG_BASE
	add	r3, r12, #0x200
	ldr	r2, [r3]
	and	r1, r2, r2, lsr #16
	mov	r2, #0
	ands	r0, r1, #0x2000
	strneb	r0, [r3, #-0x17C]
.Lloop:
	bne	.Lloop
	ands	r0, r1, #0x80
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x1
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x2
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x4
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x8
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x10
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x20
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x40
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x100
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x200
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x400
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x800
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x1000
.Ljump_intr:
	strh	r0, [r3, #2]
	ldr	r1, =IntrTable
	add	r1, r1, r2
	ldr	r0, [r1]
	bx	r0

	.pool
	.size intr_main, . - intr_main
