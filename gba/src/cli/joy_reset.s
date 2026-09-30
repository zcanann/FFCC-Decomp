	.syntax unified
	.text
	.thumb

@ Hard reset when running from JOY Bus boot with no cartridge inserted.
	.global JoyBus_HardReset
	.type JoyBus_HardReset, %function
	.thumb_func
JoyBus_HardReset:
	ldr	r3, =0x080000B2
	ldrb	r0, [r3]
	subs	r0, #0x96
	beq	.Ldone
	ldr	r2, =0x04000134
	ldrh	r0, [r2]
	lsrs	r0, r0, #14
	cmp	r0, #3
	bne	.Ldone
	swi	0x26
.Ldone:
	bx	lr
	.align	2, 0
	.pool
	.size JoyBus_HardReset, . - JoyBus_HardReset
