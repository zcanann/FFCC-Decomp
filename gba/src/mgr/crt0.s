	.text
	.arm

	.equ REG_BASE, 0x04000000
	.equ INTR_VECTOR, 0x03007FFC
	.equ PSR_IRQ_MODE, 0x12
	.equ PSR_SYS_MODE, 0x1F

	.global _start
	.type _start, %function
_start:
	b	start_vector

	.include "nintendo_logo.inc"

	.space	12				@ title
	.space	4				@ game code
	.ascii	"01"				@ maker code
	.byte	0x96				@ fixed value
	.byte	0				@ main unit code
	.byte	0				@ device type
	.space	7				@ reserved
	.byte	0				@ software version
	.byte	0xF0				@ complement check
	.space	2				@ reserved

	.size _start, . - _start

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

.Lsp_usr:	.word	0x03007F00
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
	ands	r0, r1, #0x4
	bne	.Ljump_intr
	add	r2, r2, #4
	ands	r0, r1, #0x2
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
