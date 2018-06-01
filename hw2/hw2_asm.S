/* Austin Bailey
   baustin1@umbc.edu
   This file is used to run certain instructions and functions, then return back in order to measure how long these particular sequences
	of instructions took.
*/
	.section .text
	.globl	op_func0call
	.globl	op_func1call
	.globl	op_func4call
	.globl	op_add
	.globl	op_sub
	.globl	op_mov
	.globl	op_cmp
	.globl	op_ldr
	.globl	op_str
	.globl	op_b_uncond
	.globl	op_b_taken
	.globl	op_b_nottaken
	.globl	op_largest4
	.globl	op_bubble_sort
//start of largest4 function
op_largest4:
	//part3 (determine largest number of 4 parameters)
	cmp	x0, x1
	b.lt	firstParam
	cmp	x0, x2
	b.lt	secondParam
	cmp	x0, x3
	b.lt	thirdParam
	ret
firstParam:
	mov	x0, x1
	b	op_largest4
secondParam:
	mov	x0, x2
	b	op_largest4
thirdParam:
	mov	x0, x3
	b	op_largest4
//end of largest4 function
//start of bubblesort function
op_bubble_sort:
	//for finishing the bubblesort, have it reach the end of a bunch of cmp and b instructions so it knows its done
	//ldr	x9, [x0, #16] getting a value from the array
	//mov	x10, #8 index (scale by type: 0 for index 0; 8 for index 1; 16 for index 2; 24 for index 3)
	//str	x9, [x0, x10] storing at specific index
	ldr	x9, [x0, #0]
	ldr	x10, [x0, #8]
	cmp	x9, x10
	b.gt	swap_zero_one
	ldr	x9, [x0, #8]
	ldr	x10, [x0, #16]
	cmp	x9, x10
	b.gt	swap_one_two
	ldr	x9, [x0, #16]
	ldr	x10, [x0, #24]
	cmp	x9, x10
	b.gt	swap_two_three
	ret
swap_zero_one:
	str	x9, [x0, #8]
	str	x10, [x0, #0]
	b	op_bubble_sort
swap_one_two:
	str	x9, [x0, #16]
	str	x10, [x0, #8]
	b	op_bubble_sort
swap_two_three:
	str	x9, [x0, #24]
	str	x10, [x0, #16]
	b	op_bubble_sort
//end of bubblesort function
op_func0call:
	ret
op_func1call:
	ret
op_func4call:
	ret
op_add:
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	add	x0, x0, #0
	ret
op_sub:
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	sub	x0, x0, #0
	ret
op_mov:
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	mov	x0, #0
	ret
op_cmp:
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	cmp	x0, #0
	ret
op_ldr:
	//look at slides
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ldr	x0, [x29, #28]
	ret
op_str:
	//look at slides
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	str	x0, [x29, #28]
	ret
op_b_uncond:
	//look at slides
	b	temp1
	ret
op_b_taken:
	//look at slides
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	mov	x0, 0
	cmp	x0, 0
	b.eq	temp10
	ret
op_b_nottaken:
	//look at slides
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	cmp	x0, 10
	b.eq	end
	ret
temp1:
	b	temp2
temp2:
	b	temp3
temp3:
	b	temp4
temp4:
	b	temp5
temp5:
	b	temp6
temp6:
	b	temp7
temp7:
	b	temp8
temp8:
	b	temp9
temp9:
	b	end
temp10:
	cmp	x0, 0
	b.eq	temp11
temp11:
	cmp	x0, 0
	b.eq	temp12
temp12:
	cmp	x0, 0
	b.eq	temp13
temp13:
	cmp	x0, 0
	b.eq	temp14
temp14:
	cmp	x0, 0
	b.eq	temp15
temp15:
	cmp	x0, 0
	b.eq	temp16
temp16:
	cmp	x0, 0
	b.eq	temp17
temp17:
	cmp	x0, 0
	b.eq	temp18
temp18:
	cmp	x0, 0
	b.eq	end
end:
	ret

