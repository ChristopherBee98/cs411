/* Austin Bailey, CMSC 411 
   baustin1@umbc.edu
   This file contains parsing as well as externs for assembly functions.

   Part 5
   1. In the best case, my 64 bit multiplication would take 771 cycles to fully complete (no adding required). In the worst case, however,
   is 836 cycles. This is because the way to make it to the add label I added is to go through an untaken branch. So 
   the amount of cycles takes longer as a result.
   2. Similar with the 64 multiplier, the best case is 963 cycles, and the worst case is also 1028 cycles. The program gets to ignore the
   appending add in best case, and in the worst case it has to do it every time. As a result, the worst case takes longer. Something to note
   with both the multiplier and division is that the cycles are similar. This is because of the required number of iterations that is set
   for both operations (64 bits means 64 times).
*/

#define _POSIX_C_SOURCE 200112L

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Perform unsigned integer multiplication of @a m1 and @a m2, then
 * return the product.
 *
 * You have your choice of whatever algorithm to implement. If the
 * product cannot fit in 64-bits, then truncate result to lower
 * 64-bits.
 *
 * SPECIAL RESTRICTION: you may only use addition, subtraction,
 * shifts, rotate, compare, and branch operations. You <strong>may
 * not</strong> use any built-in multiplication instructions for this
 * assignment.
 * @param[in] m1 Multiplicand
 * @param[in] m2 Multiplier
 * @return Product of @m1 times @m2, truncated to lower 64-bits.
 */
extern uint64_t uint64_mult(uint64_t m1, uint64_t m2);

/**
 * Perform unsigned division of @a d1 and @a d2, then return the
 * quotient and remainder.
 * You have your choice of whatever algorithm to implement.
 *
 * SPECIAL RESTRICTION: you may only use addition, subtraction,
 * shifts, rotate, compare, and branch operations. You <strong>may
 * not</strong> use any built-in division instructions for this
 * assignment.
 * 
 * @param[in] d1 Dividend
 * @param[in] d2 Divisor
 * @param[out] quot Remainder
 * @return Quotient of @d1 divided by @d2.
 */
extern uint64_t uint64_div(uint64_t d1, uint64_t d2, uint64_t const *rem);

/**
 * Given a double, break down its IEEE-754 bitwise representation.
 * @param[in] val 64-bit floating point value to analyze.
 */
static void float64_parse(uint64_t val)
{
	double d = *((double *)&(val));
	printf("For the value %g (bit pattern 0x%016" PRIx64 "):\n", d, val);

	/* PART 3: YOUR CODE HERE */
	//need to access sign bit, exponent, significand
	//exponent is 11 bits long, significand is 52 bits
	//significandBits = frexp(d, &exponentBits);
	uint64_t exponentMask = 0x7ff0000000000000;
	uint64_t significandMask = 0xfffffffffffff;
	uint64_t signMask = 0x8000000000000000;
	//use bitwise AND remove bits that aren't the ones needed
	//for exponent, shift to the right 52 times to acquire value
	//don't touch d; use val
	uint64_t temp = val;
	uint64_t temp2 = val;
	//this should make it so only the significand is in significandPart
	uint64_t significandPart = val & significandMask;
	//same with exponentPart
	uint64_t exponentPart = temp & exponentMask;
	uint64_t signBitPart = temp2 & signMask;
	//make this equal to the actual magnitude somehow
	//actual magnitude: 2^(exponent - bias)
	if (signBitPart == 0)
	  signBitPart = 0;
	else
	  signBitPart = 1;
	unsigned long int bias = 1023;
	exponentPart >>= 52;
	//calculates actual magnitude
	signed long int theRealMag = 0;
	if (signBitPart == 0)
	  theRealMag = exponentPart - bias + 1;
	else
	  theRealMag = exponentPart - bias + 0;
	printf("  Sign bit: %lu\n", signBitPart);
	printf("  Exponent bits: %lu (actual magnitude: %ld)\n", exponentPart, theRealMag);
	//gotta display in hex
	printf("  Significand: 0x%016" PRIx64 "\n", significandPart);
	//special vals
	if (significandPart != 0 && exponentPart == 0)
	  printf("    * denormalized\n");
	else if (exponentPart == 2047 && significandPart == 0)
	  printf("    * infinity\n");
	else if (exponentPart == 2047 && significandPart != 0)
	  printf("    * Not A Number\n");
	else if (signBitPart == 1 && significandPart == 0)
	  printf("    * -0\n");
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Need 2 arguments for this program\n");
		exit(EXIT_FAILURE);
	}

	char *endptr;
	unsigned long long arg1 = strtoull(argv[1], &endptr, 0);
	if (!(*(argv[1])) || *endptr) {
		fprintf(stderr, "Argument 1 not a number: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	unsigned long long arg2 = strtoull(argv[2], &endptr, 0);
	if (!*(argv[2]) || *endptr) {
		fprintf(stderr, "Argument 2 not a number: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	uint64_t i1 = (uint64_t) arg1;
	uint64_t i2 = (uint64_t) arg2;
	uint64_t retval1, retval2 = 0;
	retval1 = uint64_mult(i1, i2);
	printf("Calculated multiplication product: %" PRIu64 "\n", retval1);
	printf("  (Correct answer = %" PRIu64 ")\n", i1 * i2);

	retval1 = uint64_div(i1, i2, &retval2);
	printf("Division quotient: %" PRIi64 ", remainder %" PRIi64 "\n",
	       retval1, retval2);
	uint64_t quot = i1 / i2;
	uint64_t rem = i1 - (i1 / i2) * i2;
	printf("  (Correct answer = q %" PRIu64 ", r %" PRIu64 ")\n", quot,
	       rem);

	float64_parse(i1);
	float64_parse(i2);
	return 0;
}
