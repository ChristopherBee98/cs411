/* Austin Bailey, CMSC 411
   baustin1@umbc.edu
   This file implements uint64_mult and uint64_div, externed from hw3.c.*/
	.section .text
	.globl uint64_mult
	.globl uint64_div

uint64_mult:
	/* YOUR PART1 CODE HERE */
	//Multiplicand = Product
	//no 128 bit registers; need to add multiplicand to another 64 bit register and shift bits between original register and "upper"
	//register
	//x2 is upper half of product
	//x5 is a counter for the operation; stops after 64 iterations (64 bit)
	//Based on Shift-Add Multi Version 3
	mov x2, #0
	mov x5, #0
	mov x6, #0
start:
	//compare LSB to 0; branch to shift if 0
	BFI x6, x0, #0, #1
	cmp x6, #0
	b.eq shift
add:
	//add multiplier to upper half
	add x2, x2, x1
shift:
	//shift lower half of product
	LSR x4, x0, #1
	mov x0, x4
	//move LSB of upper half to MSB of lower half
	BFI x0, x2, #63, #1
	//shift upper half of product
	LSR x3, x2, #1
	mov x2, x3
finish:
	mov x6, #0
	add x5, x5, #1
	//runs 64 times (64 bit)
	cmp x5, #64
	b.ne start
	ret


uint64_div:
	/* Hint: Don't modify x2 throughout this function */

	/* YOUR PART2 CODE HERE */

	// supposing x7 has your quotient, you will need
	// something like below to pass it out of this function
	//str x7, [x2, #0]
	//Based on Shift-Subtract Division version 3
	//counter for 64 iterations
	mov x3, #0
	//x4 upper half of dividend
	mov x4, #0
subShift:
	//used to check for MSB is 1 or 0
	mov x7, #9223372036854775808
	LSL x6, x4, #1
	mov x4, x6
	//use and to compare with x0 and see if x0 MSB is 1, and if so, append 1 to x4
	and x7, x7, x0
	cmp x7, #0
	//compares bitmask to see if MSB is 1; if it is, append 1 to upper half and then shift
	b.eq noAppend
	add x4, x4, #1
noAppend:	
	LSL x5, x0, #1
	mov x0, x5
subtract:
	//sees if the divisor is larger than the remainder; aka if it will be negative if subtracted, branches if its less than
	cmp x4, x1
	b.lt subFinish
	sub x4, x4, x1
	add x0, x0, #1
subFinish:
	//increments and checks to see if the program has run n times (64 bit, n = 64)
	add x3, x3, #1
	cmp x3, #64
	b.ne subShift
	//stores register with upper half to remainder
	str x4, [x2, #0]
	ret
