	.cpu cortex-m3
	.arch armv7-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"asm_os.s"
	.text
	.align	1
	.global	__asm_set_privilege
	.syntax unified
	.thumb
	.thumb_func
	.type	__asm_set_privilege, %function
__asm_set_privilege:
	MRS r1, CONTROL
	orr r1, r0
	MRS r1, CONTROL
	bx	lr
	.size	__asm_set_privilege, .-__asm_set_privilege
	.align	1
	.global	__asm_os_switch_context
	.syntax unified
	.thumb
	.thumb_func
	.type	__asm_os_switch_context, %function
__asm_os_switch_context:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.

	@ clear interrupt flag
	ldr r0, .L3+0
	ldr r1, [r0]
	ldr r2, .L3+4
	and r1, r2
	str r1, [r0]

	@ load current_context address into r0
	ldr	r0, .L2
	ldr	r0, [r0]

	@ store PSP, R4-R11, CONTROL
	MRS	r3, PSP
	MRS r12, CONTROL
	STMIA r0, {r3-r12, lr}

	@ call C function to update current_context
	@ result is stored in R0
	bl	os_find_next_task

	@ restore PSP, R4-R11, CONTROL
	LDMIA r0, {r3-r12, lr}
	MSR	PSP, r3
	ISB
	MSR CONTROL, r12

	bx lr
	@ Pops PC, xPSR, r0, r1, r2, r3, r12 and LR from stack selected by EXC_RETURN and adjusts SP, if not pre-empted.
.L3:
	.word	1073741840
	.word	-2
	.align	2
.L2:
	.word	current_context
	.size	__asm_os_switch_context, .-__asm_os_switch_context
	.align	1
	.global	__asm_os_start
	.syntax unified
	.thumb
	.thumb_func
	.type	__asm_os_start, %function
__asm_os_start:
	@ r0: task_address
	@ r1: stack_address

	push	{lr}

	MSR	PSP, r1
	MRS r3, CONTROL
	mov	r2, #2
	orr r3, r3, r2
	MSR	CONTROL, r3
	ISB

	blx	r0

	pop		{pc}

	.size	__asm_os_start, .-__asm_os_start
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240926-1715) 12.3.1 20230626"
