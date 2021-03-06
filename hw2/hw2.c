/* Austin Bailey
   baustin1@umbc.edu
   This file is used to measure the times functions and assembly instructions take to run.
   Part1: done
   Part2: done (subtract from overhead)
   Part3: done
   Part4: done
   Part5: done
*/

/* Question 1
The best case would be triggered as long as the largest number was the first argument. The worst case would be if the arguments were entered
from smallest to largest (1 2 3 4). The only aspect that determines which sequence is faster than another is when the program first
encounters the largest number. Something like (1 3 5 2) would be slower than (1 5 3 2) despite containing all the same numbers.
   Question 2
The best case would be triggered when the numbers were entered from smallest to largest already. The worst case would be if they were
entered from largest to smallest. The only aspect that determines which sequence is faster than another is when one sequence is closer
to smallest to largest than the other. (1 3 7 6) would run faster than (1 7 3 6), since the first has the first 2 numbers in the correct
order. The second would have to do one more conditional branch to swap the middle two, and then the last two. 
 */

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TRIALS 100

/**
 * Given an array of 4 longs, in-place buble sort them from
 * largest to smallest. The incoming pointer will be in x0. As
 * per the ARMv8-A calling convention, registers x9 through x15
 * may be safely used in this routine.
 */
extern void op_bubble_sort(long vals[]);

/** 
 * Given four parameters (corresponding to registers x0, x1, x2 and x3),
 * Return the largest of the four.
*/
extern int op_largest4(int a, int b, int c, int d);

/**
 * Used for seeing how long it takes to invoke an assembly function
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_func0call(void);

/**
 * Used for seeing how long it takes to invoke the function 1 in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_func1call(int temp);

/**
 * Used for seeing how long it takes to invoke the function 4 in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern int op_func4call(int temp1, int temp2, int temp3, int temp4);

/**
 * Used for seeing how long it takes to invoke the add instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_add(void);

/**
 * Used for seeing how long it takes to invoke the mov instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_mov(void);

/**
 * Used for seeing how long it takes to invoke the cmp instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_cmp(void);

/**
 * Used for seeing how long it takes to invoke the sub instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_sub(void);

/**
 * Used for seeing how long it takes to invoke the ldr instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_ldr(void);

/**
 * Used for seeing how long it takes to invoke the str instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_str(void);

/**
 * Used for seeing how long it takes to invoke the b (unconditional) instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_b_uncond(void);

/**
 * Used for seeing how long it takes to invoke the b (taken) instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_b_taken(void);

/**
 * Used for seeing how long it takes to invoke the b (not taken) instruction in assembly
 * @param[in] Nothing
 * @return Nothing
 */
extern void op_b_nottaken(void);

/**
 * Calculate and return the difference between two clock values.
 * <strong>You do not need to modify this function.</strong>
 * @param[in] stop Minuend to subtract from
 * @param[in] start Subtrahend to subtract
 * @return Number of nanoseconds that elapsed
 */
static unsigned long clock_diff(const struct timespec *stop,
				const struct timespec *start)
{
	time_t sec_diff = stop->tv_sec - start->tv_sec;
	unsigned long nsec_diff;
	if (stop->tv_nsec < start->tv_nsec) {
		nsec_diff = 1000000000lu + stop->tv_nsec - start->tv_nsec;
		sec_diff--;
	} else
		nsec_diff = stop->tv_nsec - start->tv_nsec;
	nsec_diff += 1000000000lu * sec_diff;
	return nsec_diff;
}

#define TIME_DIFF(a,b) (((a) < (b)) ? 0 : ((a) - (b)))

/**
 * Calculate and return the difference between clock values for overhead of program.
 * @param[in] Nothing
 * @param[in] Nothing
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_timing_overhead(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);
		clock_gettime(CLOCK_MONOTONIC, &stop);
		/* Ignore first trial, to prime cache */
		if (i)
			total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for running a function that finds a largest value in assembly.
 * @param[in] 4 ints named p1, p2, p3, and p4
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_largest4(int p1, int p2, int p3, int p4)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls largest4 with 4 values
		op_largest4(p1, p2, p3, p4);

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
			total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for running a bubble sort in assembly.
 * @param[in] Array of longs
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_bubble_sort(long vals[], long temp[])
{
	unsigned long total_time = 0;	
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
	  //invokes a fresh array for bubble sort
	  for(int j = 0; j < 4; j++) {
	    vals[j] = temp[j];
	  }
	        struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls bubble_sort with 4 values
		op_bubble_sort(vals);

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
			total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for running a basic function in assembly.
 * @param[in] Nothing
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_func0call(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		/* PART 1: YOUR CODE HERE */
		//calls assembly function
		op_func0call();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
			total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for running a function with 1 parameter in assembly.
 * @param[in] Nothing
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_func1call(void)
{
	unsigned long total_time = 0;
	int temp = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);
		
		//calls assembly function
		op_func1call(temp);

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
			total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for running a function with 4 parameters in assembly.
 * @param[in] Nothing
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_func4call(void)
{
	unsigned long total_time = 0;
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;
	int temp4 = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//assembly function called
		op_func4call(temp1, temp2, temp3, temp4);

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
			total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for add instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_add(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; adding
		op_add();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for sub instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_sub(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; subbing
		op_sub();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for mov instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_mov(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; mov
		op_mov();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for cmp instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_cmp(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; cmp
		op_cmp();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for ldr instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_ldr(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; ldr
		op_ldr();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for str instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_str(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; str
		op_str();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for b (uncond) instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_b_uncond(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; b uncond
		op_b_uncond();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	//conversion to picoseconds
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for b (taken) instruction in assembly.
 * @param[in] Nothing
 * @return Number of picoseconds that elapsed
 */
static unsigned long calc_b_taken(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//calls assembly function; b taken
		//note: need to subtract cmp times from this time
		op_b_taken();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	//conversion to picoseconds
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}
/**
 * Calculate and return the difference between clock values for b (not taken) instruction in assembly.
 * @param[in] Nothing
 * @return Number of nanoseconds that elapsed
 */
static unsigned long calc_b_nottaken(void)
{
	unsigned long total_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);

		//assembly instruction b not taken
		//not: subtract cmp times from this
		op_b_nottaken();

		clock_gettime(CLOCK_MONOTONIC, &stop);
		if (i)
		  total_time += clock_diff(&stop, &start);
	}
	unsigned long avg_time = total_time / (NUM_TRIALS - 1);
	return avg_time;
}

int main(int argc, char *argv[])
{
	unsigned long time_overhead = calc_timing_overhead();
	printf("timing overhead: %lu ns\n", time_overhead);

	unsigned long time_func0call = calc_func0call();
	time_func0call = TIME_DIFF(time_func0call, time_overhead);
	printf("func0call: %lu ns\n", time_func0call);

	/* ADD CODE FOR YOUR PART 2 HERE */
	//each of these call run times for respective functions and instructions
	unsigned long time_func1call = calc_func1call();
	time_func1call = TIME_DIFF(time_func1call, time_overhead);
	printf("func1call: %lu ns\n", time_func1call);

	unsigned long time_func4call = calc_func4call();
	time_func4call = TIME_DIFF(time_func4call, time_overhead);
	printf("func4call: %lu ns\n", time_func4call);
	
	unsigned long time_add = calc_add();
	time_add = TIME_DIFF(time_add, time_overhead) * 100;
	printf("add: %lu ps\n", time_add);

	unsigned long time_sub = calc_sub();
	time_sub = TIME_DIFF(time_add, time_overhead) * 100;
	printf("sub: %lu ps\n", time_sub);

	unsigned long time_mov = calc_mov();
	time_mov = TIME_DIFF(time_mov, time_overhead) * 100;
	printf("mov: %lu ps\n", time_mov);

	unsigned long time_cmp = calc_cmp();
	time_cmp = TIME_DIFF(time_cmp, time_overhead) * 100;
	printf("cmp: %lu ps\n", time_cmp);

	unsigned long time_ldr = calc_ldr();
	time_ldr = TIME_DIFF(time_ldr, time_overhead) * 100;
	printf("ldr: %lu ps\n", time_ldr);

	unsigned long time_str = calc_str();
	time_str = TIME_DIFF(time_str, time_overhead) * 100;
	printf("str: %lu ps\n", time_str);

	unsigned long time_b_uncond = calc_b_uncond();
	time_b_uncond = TIME_DIFF(time_b_uncond, time_overhead) * 100;
	printf("b (unconditional): %lu ps\n", time_b_uncond);

	unsigned long time_b_taken = calc_b_taken();
	//subtract time_mov and time_cmp from time_b_nottaken
	time_b_taken = TIME_DIFF(time_b_taken, time_overhead) * 100;
	time_b_taken -= time_cmp;
	time_b_taken -= time_mov;
	printf("b (taken): %lu ps\n", time_b_taken);

	unsigned long time_b_nottaken = calc_b_nottaken();
	//subtract time_cmp from time_b_nottaken
	time_b_nottaken = TIME_DIFF(time_b_nottaken, time_overhead) * 100;
	time_b_nottaken -= time_cmp;
	printf("b (not taken): %lu ps\n", time_b_nottaken);

	if (argc < 5) {
		fprintf(stderr,
			"Need to pass 4 arguments to continue\n");
		exit(EXIT_FAILURE);
	}
	int p1 = atoi(argv[1]);
	int p2 = atoi(argv[2]);
	int p3 = atoi(argv[3]);
	int p4 = atoi(argv[4]);
	long vals[4] = {p1, p2, p3, p4};

	/* ADD CODE FOR YOUR PART 3 HERE */
	int largest = op_largest4(p1, p2, p3, p4);
	printf("largest4: \n");
	//best case is: 3 cmp, 3 b (not taken)
	unsigned long best = time_func4call + (3 * time_cmp) / 1000 + (3 * time_b_nottaken) / 1000;
	//worst case is: 9 cmp, 3 mov, 3 b (uncond), 3 b (taken), 6 b (not taken)
	unsigned long worst = time_func4call + (9 * time_cmp) / 1000 + (3 * time_mov) / 1000 + (3 * time_b_uncond) / 1000 + (3 * time_b_taken) / 1000 + (6 * time_b_nottaken) / 1000;
	printf("  predicted: best case: %lu ns, worst case: %lu ns\n", best, worst);
	printf("  largest value was: %d\n", largest);
	unsigned long time_largest4 = calc_largest4(p1, p2, p3, p4);
	time_largest4 = TIME_DIFF(time_largest4, time_overhead);
	printf("  actual: %lu ns\n", time_largest4);

	/* ADD CODE FOR YOUR PART 4 HERE */
	//tempVals and anotherTemp used for invoking a fresh array in calc_bubble_sort
	long tempVals[4] = {p1, p2, p3, p4};
	long anotherTemp[4] = {p1, p2, p3, p4};
	op_bubble_sort(vals);
	printf("bubble_sort: \n");
	//best case is: 6 ldr, 3 cmp, 3 b (not taken)
	//1000 picoseconds in 1 nanosecond
	unsigned long bestBubble = time_func1call + (6 * time_ldr) / 1000 + (3 * time_cmp) / 1000 + (3 * time_b_nottaken) / 1000;
	//worst case is: 18 ldr, 6 str, 9 cmp, 6 b (not taken), 3 b (uncond), 3 b (taken)
	unsigned long worstBubble = time_func1call + (18 * time_ldr) / 1000 + (6 * time_str) / 1000 + (9 * time_cmp) / 1000 + (6 * time_b_nottaken) / 1000 + (3 * time_b_uncond) / 1000 + (3 * time_b_taken) / 1000;
	printf("  predicted: best case: %lu ns, worst case: %lu ns\n", bestBubble, worstBubble);
	printf("  sorted values are: ");
	for(int i = 0; i < 4; i++)
	  printf("%ld ", vals[i]);
	printf("\n");
	unsigned long time_bubble_sort = calc_bubble_sort(tempVals, anotherTemp);
	time_bubble_sort = TIME_DIFF(time_bubble_sort, time_overhead);
	printf("  actual: %lu ns\n", time_bubble_sort);
	return 0;
}
