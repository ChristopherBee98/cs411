/* 	Austin Bailey
	baustin1@umbc.edu
	This file is meant to implement the calc_grade function from the
	hw1.c file. It returns a numeric grade in regards to the given score.*/
//mov w0, ['A']
	.section .text
	.globl calc_grade

calc_grade:
	/* PART 5: YOUR ASSEMBLY CODE HERE */
	//beginning of function
	mov	w1, ['A']
	//greater or equal to 90, an A
	cmp	w0, 90
	b.ge	end
	mov	w1, ['B']
	//greater or equal to 80, a B, etc
	cmp	w0, 80
	b.ge	end
	mov	w1, ['C']
	cmp	w0, 70
	b.ge	end
	mov	w1, ['D']
	cmp	w0, 60
	b.ge	end
	mov	w1, ['F']
end:	
	//end of function
	mov	w0, w1
	ret
	
