/* Austin Bailey
   baustin1@umbc.edu
   This file is used to parse through instruction types and print out what they are.
   Part 1: Done
   Part 2: Done
   Part 3: Done
   Part 4:
   1. (1) addi R0, R1, 0 (2) rot R0, R1, 0 (3) inci R0, R1, 0 (4) sha R0, R1, 0 (5) shl R0, R1, 0
   2. It isn't needed since ULNAv1 already has addi as an instruction. Since the immediates (5 bits, 8bits, and 11 bits) are all in
twos complement, addi could be used as sub (immediate). So creating another instruction would be redundant.
(Ask Professor Tang about this question to make sure it's right.)
Reference:
stackoverflow.com/questions/3756308/how-to-read-only-the-first-word-from-each-line?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Input: Control Signals
Return value: Nothing
Prints out the control signal values for each instruction.
 */
void ControlSignals(int ALUASrc, int ALUBSrc, char *ALUOp, int BranchType, int ExtSel, int MemRead, int MemToReg, int MemWrite, int RegA, int RegB, int RegW, int RegWrite, int PCSel, int Clock, int Imm5, int Imm8, int Imm11, int CondUpdate, int Reset) {
  if (ALUASrc == 8)
    printf("        ALUASrc = x\n");
  else
    printf("        ALUASrc = %d\n", ALUASrc);
  if (ALUBSrc == 8)
    printf("        ALUBSrc = x\n");
  else
    printf("        ALUBSrc = %d\n", ALUBSrc);
  printf("        ALUOp = %s\n", ALUOp);
  if (BranchType == 8)
    printf("        BranchType = x\n");
  else
    printf("        BranchType = %d\n", BranchType);
  if (ExtSel == 4)
    printf("        ExtSel = x\n");
  else
    printf("        ExtSel = %d\n", ExtSel);
  if (MemRead == 2)
    printf("        MemRead = x\n");
  else
    printf("        MemRead = %d\n", MemRead);
  if (MemToReg == 8)
    printf("        MemToReg = x\n");
  else
    printf("        MemToReg = %d\n", MemToReg);
  if (MemWrite == 2)
    printf("        MemWrite = x\n");
  else
    printf("        MemWrite = %d\n", MemWrite);
  if (RegA == 8)
    printf("        RegA = x\n");
  else
    printf("        RegA = %d\n", RegA);
  if (RegB == 8)
    printf("        RegB = x\n");
  else
    printf("        RegB = %d\n", RegB);
  if (RegW == 8)
    printf("        RegW = x\n");
  else
    printf("        RegW = %d\n", RegW);
  if (RegWrite == 2)
    printf("        RegWrite = x\n");
  else
    printf("        RegWrite = %d\n", RegWrite);
  printf("        PCSel = %d\n", PCSel);
  printf("        Clock = %d\n", Clock);
  if (Imm5 == 32)
    printf("        Imm5 = x\n");
  else
    printf("        Imm5 = %d\n", Imm5);
  if (Imm8 == 256)
    printf("        Imm8 = x\n");
  else
    printf("        Imm8 = %d\n", Imm8);
  if (Imm11 == 2048)
    printf("        Imm11 = x\n");
  else
    printf("        Imm11 = %d\n", Imm11);
  printf("        CondUpdate = %d\n", CondUpdate);
  printf("        Reset = %d\n", Reset);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILE.IMG\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE HERE */
	FILE  * fp;
	//opens image file created by ULNA for parsing
	fp = fopen("bsort.img", "r");
	//first value is used to determine all the aspects for parasing (hex); convert it into binary and go from there
	char word[100000]; //attempt to change to not be a constant later (possibly this?: char *word;)
	//put all instructions into array for specification
	char *specInst[32] = {"or", "add", "and", "stw", "br", "sub", "neg", "ldw", "sha", "addi", "shl", "stwi", "undef - 12", "undef - 13", "rot", "ldwi", "ori", "inci", "andi", "undef - 19", "movi", "cmp", "movis", "call", "b", "b.gt", "b.eq", "b.ge", "b.lt", "b.ne", "b.le", "halt" };
	int skipFirstLine = 0;
	int counter;
	int convertValue = 0;
	int tempType = 0; //used for determining what type the instruction is
	int tempInstruction = 0; //used for specifying which instruction in array
	int tempAReg = 0; //used for reg A
	int tempBReg = 0; //used for reg B
	int tempWReg = 0; //used for reg W
	int immFive = 0; //used for immediate 5 bits
	int immEight = 0; //used for immediate 8 bits
	int immEleven = 0; //used for immediate 11 bits
	int firstMask = 0xc000; //for determining type (first 2 bits)
	int secondMask = 0xf800; //for determining instruction (first 5 bits)
	int aMask = 0x00e0; //for determining register A (if used)
	int bMask = 0x001c; //for determining register B (if used)
	int wMask = 0x0700; //for determining register W (if used)
	int immFiveMask = 0x001f; //determines immediate (last 5 bits)
	int immEightMask = 0x00ff; //determines immediate (last 8 bits)
	int immElevenMask = 0x07ff; //determines immediate (last 11 bits)
	if (fp == NULL)
	  printf("Error.");
	else {
	  while(!feof(fp)) {
	    if (skipFirstLine == 0) {
	      fscanf(fp, "%s%*[^\n]", word);
	      skipFirstLine++;
	    } else {
	      fscanf(fp, "%s%*[^\n]", word);
	      //in here, convert the 4 characters into a 16-bit value
	      if (!feof(fp)) {
		convertValue = 0;
		for (counter = 0; counter < 4; counter++) {
		  if (counter == 0) {
		    if (word[counter] == '0')
		      convertValue += 0x0000;
		    else if (word[counter] == '1')
		      convertValue += 0x1000;
		    else if (word[counter] == '2')
		      convertValue += 0x2000;
		    else if (word[counter] == '3')
		      convertValue += 0x3000;
		    else if (word[counter] == '4')
		      convertValue += 0x4000;
		    else if (word[counter] == '5')
		      convertValue += 0x5000;
		    else if (word[counter] == '6')
		      convertValue += 0x6000;
		    else if (word[counter] == '7')
		      convertValue += 0x7000;
		    else if (word[counter] == '8')
		      convertValue += 0x8000;
		    else if (word[counter] == '9')
		      convertValue += 0x9000;
		    else if (word[counter] == 'a')
		      convertValue += 0xa000;
		    else if (word[counter] == 'b')
		      convertValue += 0xb000;
		    else if (word[counter] == 'c')
		      convertValue += 0xc000;
		    else if (word[counter] == 'd')
		      convertValue += 0xd000;
		    else if (word[counter] == 'e')
		      convertValue += 0xe000;
		    else if (word[counter] == 'f')
		      convertValue += 0xf000;
		  } else if (counter == 1) {
		    if (word[counter] == '0')
		      convertValue += 0x0000;
		    else if (word[counter] == '1')
		      convertValue += 0x0100;
		    else if (word[counter] == '2')
		      convertValue += 0x0200;
		    else if (word[counter] == '3')
		      convertValue += 0x0300;
		    else if (word[counter] == '4')
		      convertValue += 0x0400;
		    else if (word[counter] == '5')
		      convertValue += 0x0500;
		    else if (word[counter] == '6')
		      convertValue += 0x0600;
		    else if (word[counter] == '7')
		      convertValue += 0x0700;
		    else if (word[counter] == '8')
		      convertValue += 0x0800;
		    else if (word[counter] == '9')
		      convertValue += 0x0900;
		    else if (word[counter] == 'a')
		      convertValue += 0x0a00;
		    else if (word[counter] == 'b')
		      convertValue += 0x0b00;
		    else if (word[counter] == 'c')
		      convertValue += 0x0c00;
		    else if (word[counter] == 'd')
		      convertValue += 0x0d00;
		    else if (word[counter] == 'e')
		      convertValue += 0x0e00;
		    else if (word[counter] == 'f')
		      convertValue += 0x0f00;
		  } else if (counter == 2) {
		    if (word[counter] == '0')
		      convertValue += 0x0000;
		    else if (word[counter] == '1')
		      convertValue += 0x0010;
		    else if (word[counter] == '2')
		      convertValue += 0x0020;
		    else if (word[counter] == '3')
		      convertValue += 0x0030;
		    else if (word[counter] == '4')
		      convertValue += 0x0040;
		    else if (word[counter] == '5')
		      convertValue += 0x0050;
		    else if (word[counter] == '6')
		      convertValue += 0x0060;
		    else if (word[counter] == '7')
		      convertValue += 0x0070;
		    else if (word[counter] == '8')
		      convertValue += 0x0080;
		    else if (word[counter] == '9')
		      convertValue += 0x0090;
		    else if (word[counter] == 'a')
		      convertValue += 0x00a0;
		    else if (word[counter] == 'b')
		      convertValue += 0x00b0;
		    else if (word[counter] == 'c')
		      convertValue += 0x00c0;
		    else if (word[counter] == 'd')
		      convertValue += 0x00d0;
		    else if (word[counter] == 'e')
		      convertValue += 0x00e0;
		    else if (word[counter] == 'f')
		      convertValue += 0x00f0;
		  } else {
		    if (word[counter] == '0')
		      convertValue += 0x0000;
		    else if (word[counter] == '1')
		      convertValue += 0x0001;
		    else if (word[counter] == '2')
		      convertValue += 0x0002;
		    else if (word[counter] == '3')
		      convertValue += 0x0003;
		    else if (word[counter] == '4')
		      convertValue += 0x0004;
		    else if (word[counter] == '5')
		      convertValue += 0x0005;
		    else if (word[counter] == '6')
		      convertValue += 0x0006;
		    else if (word[counter] == '7')
		      convertValue += 0x0007;
		    else if (word[counter] == '8')
		      convertValue += 0x0008;
		    else if (word[counter] == '9')
		      convertValue += 0x0009;
		    else if (word[counter] == 'a')
		      convertValue += 0x000a;
		    else if (word[counter] == 'b')
		      convertValue += 0x000b;
		    else if (word[counter] == 'c')
		      convertValue += 0x000c;
		    else if (word[counter] == 'd')
		      convertValue += 0x000d;
		    else if (word[counter] == 'e')
		      convertValue += 0x000e;
		    else if (word[counter] == 'f')
		      convertValue += 0x000f;
		  }
		}
		//now use the bits to parse
		//printf("%d\n", convertValue);
		//aMask, bMask, wMask, immFiveMask, etc
		//tempAReg, tempBReg, etc; immFive, immEight, etc
		tempType = firstMask & convertValue;
		tempType >>= 14;
		tempInstruction = secondMask & convertValue;
		tempInstruction >>= 11;
		tempAReg = aMask & convertValue;
		tempAReg >>= 5;
		tempBReg = bMask & convertValue;
		tempBReg >>= 2;
		tempWReg = wMask & convertValue;
		tempWReg >>= 8;
		immFive = immFiveMask & convertValue;
		immEight = immEightMask & convertValue;
		immEleven = immElevenMask & convertValue;
		if (tempType == 0) {
		  char *temp = specInst[tempInstruction];
		  printf("%s: %s       A = R%d, B = R%d, W = R%d\n", word, temp, tempAReg, tempBReg, tempWReg);
		  if (tempInstruction == 1)
		    //add
		    ControlSignals(tempAReg, tempBReg, "Addition", 8, 4, 0, 8, 0, tempAReg, tempBReg, tempWReg, 1, 0, 1, 32, 256, 2048, 1, 0);
		  if (tempInstruction == 2)
		    //and
		    ControlSignals(tempAReg, tempBReg, "And", 8, 4, 0, 8, 0, tempAReg, tempBReg, tempWReg, 1, 0, 1, 32, 256, 2048, 0, 0);
		  if (tempInstruction == 4)
		    //br
		    ControlSignals(tempAReg, tempBReg, "x", 8, 0, 0, 8, 0, tempAReg, tempBReg, tempWReg, 0, 0, 1, 32, 256, 2048, 0, 0);
		  if (tempInstruction == 7)
		    //ldw
		    ControlSignals(tempAReg, tempBReg, "Addition", 8, 4, 1, 8, 0, tempAReg, tempBReg, tempWReg, 1, 0, 1, 32, 256, 2048, 0, 0);
		  if (tempInstruction == 6)
		    //neg
		    ControlSignals(tempAReg, tempBReg, "x", 8, 4, 0, 8, 0, tempAReg, tempBReg, tempWReg, 1, 0, 1, 32, 256, 2048, 0, 0);
		  if (tempInstruction == 0)
		    //or
		    ControlSignals(tempAReg, tempBReg, "Or", 8, 4, 0, 8, 0, tempAReg, tempBReg, tempWReg, 1, 0, 1, 32, 256, 2048, 0, 0);
		  if (tempInstruction == 3)
		    //stw
		    ControlSignals(tempAReg, tempBReg, "Addition", 8, 4, 0, 8, 1, tempAReg, tempBReg, tempWReg, 0, 0, 1, 32, 256, 2048, 0, 0);
		  if (tempInstruction == 5)
		    //sub
		    ControlSignals(tempAReg, tempBReg, "Subtraction", 8, 4, 0, 8, 0, tempAReg, tempBReg, tempWReg, 1, 0, 1, 32, 256, 2048, 1, 0);
		} else if (tempType == 1) {
		  char *temp = specInst[tempInstruction];
		  const int negative = (immFive & (1 << 4)) != 0;
		  int tempImm;
		  if (negative != 0)
		    tempImm = immFive | ~((1 << 5) - 1);
		  else
		    tempImm = immFive;
		  printf("%s: %s       A = R%d, Imm5 = %d, W = R%d\n", word, temp, tempAReg, tempImm, tempWReg);
		  if (tempInstruction == 9)
		    //addi
		    ControlSignals(tempAReg, 8, "Addition", 8, 4, 0, 0, 0, tempAReg, 8, tempWReg, 1, 0, 1, tempImm, 256, 2048, 1, 0);
		  if (tempInstruction == 15)
		    //ldwi
		    ControlSignals(tempAReg, 8, "Addition", 8, 4, 1, 1, 0, tempAReg, 8, tempWReg, 1, 0, 1, tempImm, 256, 2048, 0, 0);
		  if (tempInstruction == 14)
		    //rot
		    ControlSignals(tempAReg, 8, "Rotate", 8, 4, 0, 2, 0, tempAReg, 8, tempWReg, 1, 0, 1, tempImm, 256, 2048, 0, 0);
		  if (tempInstruction == 8)
		    //sha
		    ControlSignals(tempAReg, 8, "x", 8, 4, 0, 3, 0, tempAReg, 8, tempWReg, 1, 0, 1, tempImm, 256, 2048, 0, 0);
		  if (tempInstruction == 10)
		    //shl
		    ControlSignals(tempAReg, 8, "x", 8, 4, 0, 4, 0, tempAReg, 8, tempWReg, 1, 0, 1, tempImm, 256, 2048, 0, 0);
		  if (tempInstruction == 11)
		    //stwi
		    ControlSignals(tempAReg, 8, "Addition", 8, 4, 0, 5, 1, tempAReg, 8, tempWReg, 0, 0, 1, tempImm, 256, 2048, 0, 0);
		  if (tempInstruction == 12)
		    //undef-12
		    ControlSignals(tempAReg, 8, "x", 8, 4, 2, 6, 2, tempAReg, 8, tempWReg, 2, 0, 1, tempImm, 256, 2048, 0, 0);
		  if (tempInstruction == 13)
		    //undef-13
		    ControlSignals(tempAReg, 8, "x", 8, 4, 2, 7, 2, tempAReg, 8, tempWReg, 2, 0, 1, tempImm, 256, 2048, 0, 0);
		} else if (tempType == 2) {
		  char *temp = specInst[tempInstruction];
		  const int negative = (immEight & (1 << 7)) != 0;
		  int tempImm;
		  if (negative != 0)
		    tempImm = immEight | ~((1 << 8) - 1);
		  else
		    tempImm = immEight;
		  printf("%s: %s       W = R%d, Imm8 = %d\n", word, temp,  tempWReg, tempImm);
		  if (tempInstruction == 18)
		    //andi
		    ControlSignals(8, 8, "And", 8, 4, 0, 8, 0, 8, 8, tempWReg, 1, 0, 1, 32, tempImm, 2048, 0, 0);
		  if (tempInstruction == 23)
		    //call
		    ControlSignals(8, 8, "x", 7, 2, 0, 8, 0, 8, 8, tempWReg, 1, 0, 1, 32, tempImm, 2048, 0, 0);
		  if (tempInstruction == 21)
		    //cmp
		    ControlSignals(8, 8, "Subtraction", 8, 4, 0, 8, 0, 8, 8, tempWReg, 0, 0, 1, 32, tempImm, 2048, 1, 0);
		  if (tempInstruction == 17)
		    //inci
		    ControlSignals(8, 8, "Addition", 8, 4, 0, 8, 0, 8, 8, tempWReg, 1, 0, 1, 32, tempImm, 2048, 1, 0);
		  if (tempInstruction == 20)
		    //movi
		    ControlSignals(8, 8, "x", 8, 4, 0, 8, 0, 8, 8, tempWReg, 1, 0, 1, 32, tempImm, 2048, 0, 0);
		  if (tempInstruction == 22)
		    //movis
		    ControlSignals(8, 8, "Or", 8, 4, 0, 8, 0, 8, 8, tempWReg, 1, 0, 1, 32, tempImm, 2048, 0, 0);
		  if (tempInstruction == 16)
		    //ori
		    ControlSignals(8, 8, "Or", 8, 4, 0, 8, 0, 8, 8, tempWReg, 1, 0, 1, 32, tempImm, 2048, 0, 0);
		  if (tempInstruction == 19)
		    //undef-19
		    ControlSignals(8, 8, "x", 8, 4, 2, 8, 2, 8, 8, tempWReg, 2, 0, 1, 32, tempImm, 2048, 0, 0);
		} else {
		  char *temp = specInst[tempInstruction];
		  const int negative = (immEleven & (1 << 10)) != 0;
		  int tempImm;
		  if (negative != 0)
		    tempImm = immEleven | ~((1 << 11) - 1);
		  else
		    tempImm = immEleven;
		  printf("%s: %s       Imm11 = %d\n", word, temp, tempImm);
		  if (tempInstruction == 24)
		    //b
		    ControlSignals(8, 8, "x", 0, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 26)
		    //b.eq
		    ControlSignals(8, 8, "x", 1, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 27)
		    //b.ge
		    ControlSignals(8, 8, "x", 2, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 25)
		    //b.gt
		    ControlSignals(8, 8, "x", 3, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 30)
		    //b.le
		    ControlSignals(8, 8, "x", 4, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 28)
		    //b.lt
		    ControlSignals(8, 8, "x", 5, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 29)
		    //b.ne
		    ControlSignals(8, 8, "x", 6, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		  if (tempInstruction == 31)
		    //halt
		    ControlSignals(8, 8, "x", 8, 3, 0, 8, 0, 8, 8, 8, 0, 1, 1, 32, 256, tempImm, 0, 0);
		}
	      }
	    }
	  }
	}
	fclose(fp);
	return 0;
}
