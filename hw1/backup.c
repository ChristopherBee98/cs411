/* Austin Bailey
   baustin1@umbc.edu
   This file calculates a grade depending on the numeric score. It also
displays how many bytes are necessary to store variables in numerous
data types.
*/

/* Helpful Sources:
www.geeksforgeeks.org/sizeof-operator-c/
 */

//Signed Variable Types: char, short, int, long, long long
//Unsigned Variable Types: char, short, int, long, long long

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Calculate and return the letter grade given a score, using the
 * standard formula: 'A' for >= 90, 'B' >= 80, 'C' >= 70, 'D' >= 60,
 * otherwise 'F'.
 * @param[in] val Score to evaluate
 * @return Letter grade
 */
extern char calc_grade(int val);

void MinMaxSigned(signed char schar, signed short sshrt, signed int sint, signed long slong, signed long long sllong) {
  //char
  int i = 0;
  int check = 0;
  while (check != 1) {
    i++;
    schar = 1;
    for (int j = 0; j < i; j++)
      schar *= 2;
    schar *= -1;
    if (schar >= 0) {
      i--;
      schar = 1;
      for (int j = 0; j < i; j++)
	schar *= 2;
      check = 1;
    }
  }
  printf("signed char min: %d\n", schar);
  schar *= -1;
  schar -= 1;
  printf("signed char max: %d\n", schar);
  //short
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    sshrt = 1;
    for (int j = 0; j < i; j++)
      sshrt *= 2;
    sshrt *= -1;
    if (sshrt >= 0) {
      i--;
      sshrt = 1;
      for (int j = 0; j < i; j++)
	sshrt *= 2;
      check = 1;
    }
  }
  printf("signed short min: %d\n", sshrt);
  sshrt *= -1;
  sshrt -= 1;
  printf("signed short max: %d\n", sshrt);
  //int
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    sint = 1;
    for (int j = 0; j < i; j++)
      sint *= 2;
    sint *= -1;
    if (sint >= 0) {
      i--;
      sint = 1;
      for (int j = 0; j < i; j++)
	sint *= 2;
      check = 1;
    }
  }
  printf("signed int min: %d\n", sint);
  sint *= -1;
  sint -= 1;
  printf("signed int max: %d\n", sint);
  //long
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    slong = 1;
    for (int j = 0; j < i; j++)
      slong *= 2;
    slong *= -1;
    if (slong >= 0) {
      i--;
      slong = 1;
      for (int j = 0; j < i; j++)
	slong *= 2;
      check = 1;
    }
  }
  printf("signed long min: %ld\n", slong);
  slong *= -1;
  slong -= 1;
  printf("signed long max: %ld\n", slong);
  //long long
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    sllong = 1;
    for (int j = 0; j < i; j++)
      sllong *= 2;
    sllong *= -1;
    if (sllong >= 0) {
      i--;
      sllong = 1;
      for (int j = 0; j < i; j++)
	sllong *= 2;
      check = 1;
    }
  }
  printf("signed long long min: %lld\n", sllong);
  sllong *= -1;
  sllong -= 1;
  printf("signed long long max: %lld\n", sllong);
}

void MinMaxUnsigned(unsigned char uchar, unsigned short ushrt, unsigned int uint, unsigned long ulong, unsigned long long ullong) {
  //char
  int i = 0;
  int check = 0;
  while (check != 1) {
    i++;
    uchar = 1;
    for (int j = 0; j < i; j++)
      uchar *= 2;
    if (uchar == 0) {
      uchar -= 1;
      check = 1;
    }
  }
  printf("unsigned char max: %d\n", uchar);
  //short
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    ushrt = 1;
    for (int j = 0; j < i; j++)
      ushrt *= 2;
    if (ushrt == 0) {
      ushrt -= 1;
      check = 1;
    }
  }
  printf("unsigned short max: %hu\n", ushrt);
  //int
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    uint = 1;
    for (int j = 0; j < i; j++)
      uint *= 2;
    if (uint == 0) {
      uint -= 1;
      check = 1;
    }
  }
  printf("unsigned int max: %u\n", uint);
  //long
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    ulong = 1;
    for (int j = 0; j < i; j++)
      ulong *= 2;
    if (ulong == 0) {
      ulong -= 1;
      check = 1;
    }
  }
  printf("unsigned long max: %lu\n", ulong);
  //long long
  i = 0;
  check = 0;
  while (check != 1) {
    i++;
    ullong = 1;
    for (int j = 0; j < i; j++)
      ullong *= 2;
    if (ullong == 0) {
      ullong -= 1;
      check = 1;
    }
  }
  printf("unsigned long long max: %llu\n", ullong);
}

int main(int argc, char *argv[])
{
	/* PART 4: YOUR CODE HERE */
  /* Need to print out bytes for each datatype */
  printf("bool bytes: %lu\n", sizeof(bool));
  printf("char bytes: %lu\n", sizeof(char));
  printf("short bytes: %lu\n", sizeof(short));
  printf("int bytes: %lu\n", sizeof(int));
  printf("long bytes: %lu\n", sizeof(long));
  printf("long long bytes: %lu\n", sizeof(long long));
  printf("float bytes: %lu\n", sizeof(float));
  printf("double bytes: %lu\n", sizeof(double));
  // Minimum and maximum values of signed variables
  MinMaxSigned(1, 1, 1, 1, 1);
  // Minimum and maximum values of unsigned variables
  MinMaxUnsigned(1, 1, 1, 1, 1);

	if (argc < 2) {
		fprintf(stderr, "Need a grade value.\n");
		exit(EXIT_FAILURE);
	} else {
		int val = atoi(argv[1]);
		/* UNCOMMENT THE FOLLOWING LINE WHEN STARTING PART 5
		printf("Value of %d => grade '%c'\n", val, calc_grade(val));
		*/
	}
	return 0;
}
