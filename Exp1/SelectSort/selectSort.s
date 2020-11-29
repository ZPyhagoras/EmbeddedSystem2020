	.arch armv7-a
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"selectSort.c"
	.text
	.align	2
	.global	selectSort
	.syntax unified
	.thumb
	.thumb_func
	.type	selectSort, %function
selectSort:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #28
	add	r7, sp, #0
	str	r0, [r7, #4]	;/*r0为第一个参数buffer，将buffer保存到[r7,#4]*/
	str	r1, [r7]	;/*r1 bufferlen*/
	cmp	r1, #0
	beq	end
	movs	r3, #0		;/*r3为i*/
	str	r3, [r7, #20]	;/*i存在[r7, #20]*/
loop_1:
	ldr	r3, [r7, #20]	;/*r3 i*/
	ldr	r2, [r7]	;/*r2 bufferlen*/
	sub	r2, r2, #1
	cmp	r2, r3
	ble	end
	movs	r1, r3		;/*r1 minindex*/
	add	r0, r3, #1	;/*r0 j*/
	str	r0, [r7, #16]	;/*j存在[r7, #16]*/
	str	r3, [r7, #20]
loop_2:
	ldr	r2, [r7]	;/*r2 bufferlen*/
	ldr	r3, [r7, #16]	;/*r3 j*/
	cmp	r2, r3
	ble	loop_1_end
	ldr	r2, [r7, #4]	;/*r2 buffer*/
	lsls	r3, r3, #2
	add	r3, r3, r2
	ldr	r3, [r3]	;/*r3 a[j]*/
	ldr	r1, [r7, #20]	;/*r1 a[minindex]*/
	lsls	r1, r1, #2
	add	r1, r1, r2
	ldr	r1, [r1]	;/*r1 a[minindex]*/
	cmp	r1, r3
	ble	loop_2_end
	str	r3, [r7, #12]	;/*[r7, #12]是temp=a[j]*/
	ldr	r3, [r7, #16]
	lsls	r3, r3, #2
	add	r3, r3, r2
	str	r1, [r3]
	ldr	r1, [r7, #20]
	lsls	r1, r1, #2
	add	r1, r1, r2
	ldr	r3, [r7, #12]
	str	r3, [r1]
loop_2_end:
	ldr	r3, [r7, #16]
	add	r3, r3, #1
	str	r3, [r7, #16]
	b	loop_2
loop_1_end:
	ldr	r3, [r7, #20]
	add	r3, r3, #1
	str	r3, [r7, #20]
	b	loop_1
end:
	nop
	adds	r7, r7, #28
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
	.size	selectSort, .-selectSort
	.ident	"GCC: (Linaro GCC 5.4-2017.05) 5.4.1 20170404"
	.section	.note.GNU-stack,"",%progbits
