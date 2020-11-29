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
	.file	"sort.c"
	.text
	.align	2
	.global	sort
	.syntax unified
	.thumb
	.thumb_func
	.type	sort, %function
sort:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #28
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7]
	movs	r3, #0
	str	r3, [r7, #20]
	b	.L2
.L6:
	movs	r3, #0
	str	r3, [r7, #16]
	b	.L3
.L5:
	ldr	r3, [r7, #16]
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	ldr	r2, [r3]
	ldr 	r3, [r7, #16]
	add	r3, r3, #1
	lsls	r3, r3, #2
	ldr 	r1, [r7, #4]
	add	r3, r3, r1
	ldr	r3, [r3]
	cmp	r2, r3
	bge	.L4

	;/*交换两个数*/
	ldr	r3, [r7, #16]
	add	r3, r3, #1
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	ldr	r3, [r3]
	str	r3, [r7, #12]
	ldr	r3, [r7, #16]
	add	r3, r3, #1
	lsls	r3, r3, #2  
	ldr	r2, [r7, #4]    
	add	r3, r3, r2
	ldr	r2, [r7, #16]
	lsls	r2, r2, #2
	ldr	r1, [r7, #4]
	add	r2, r2, r1
	ldr	r2, [r2]
	str	r2, [r3]
	ldr	r3, [r7, #16]
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	ldr	r2, [r7, #12]
	str	r2, [r3]

.L4:
	ldr	r3, [r7, #16]
	add	r3, r3, #1
	str	r3, [r7, #16]
.L3:
	ldr	r2, [r7]
	ldr	r3, [r7, #20]
	subs	r3, r2, r3
	subs	r2, r3, #1
	ldr	r3, [r7, #16]
	cmp	r2, r3
	bgt	.L5
	
	;/*内层循环结束,相当于i=i+1*/
	ldr	r3, [r7, #20] 
	adds	r3, r3, #1
	str	r3, [r7, #20]
.L2:
	ldr	r2, [r7, #20]
	ldr	r3, [r7]
	sub 	r3, r3, #1
	cmp	r2, r3
	blt	.L6
	nop
	adds	r7, r7, #28  
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
	.size	sort, .-sort
	.ident	"GCC: (Linaro GCC 5.4-2017.05) 5.4.1 20170404"
	.section	.note.GNU-stack,"",%progbits
