	.syntax unified
	.text
	.thumb

@ Hard reset when running from JOY Bus boot with no cartridge inserted.
	.global fn_0201C734
	.type fn_0201C734, %function
	.thumb_func
fn_0201C734:
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
	.size fn_0201C734, . - fn_0201C734
