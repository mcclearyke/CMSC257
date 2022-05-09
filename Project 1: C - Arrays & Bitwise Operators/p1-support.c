///////////////////////////////////////////////////////////////////////////////
//  File          : p1-support.c
//  Description   : This file will include code for each of the functions that
//		    were declared in p1-support.h. 
//  Author     	  : Kendall McCleary
//  Last Modified : 10/2/2020
//////////////////////////////////////////////////////////////////////////////

//Include Files
#include <stdio.h>
#include "p1-support.h"


/* Function: To display an array that is passed in - in a single line
   Type: void
   Parameters: int array, int size of array
   Output: the array displayed
*/
void display_array(int array[], int size) {
  
   int i;	
   printf("{");

	for (i = 0; i < size; i++) {
			
		//formatting
		if (i == (size - 1)) {

	                //don't print value with comma
			printf("%4d", array[i]);
		}

		else {

		        //print the vlaue with a comma
			printf("%4d,", array[i]);
		}
	}

   printf("} \n");
}


/* Function: Count the number of 1's in a number
   Type: int
   Parameters: integer to count the number of 1's from 
   Return: the number of ones in a number
*/
int count_bits(int num) {
 
   int numOfOnes; //return value
   int countOnes = 0; //counter

	//while num is NOT zero
	while (num != 0) {
	
		//if the least significant bit of num is 1
		if ((num & 1) == 1) {
	
			countOnes++; //increment the count for ones
		}

		//else shift the number to the right by one
		num = num >> 1; //this will eventually push all the ones out of num - to the right
	}	
	
	numOfOnes = countOnes;

	return numOfOnes;	
}


/* Function: Revese the bits of an unsigned int number that is passed in
   Type: unsigned int
   Parameters: unsigned int that will be reversed 
   Return: The reversed of the unsigned int that was passed in
*/
unsigned int reverse_bits(unsigned int num) {	

   unsigned int reversedBit = 0;
   unsigned int i;

        for (i = 0; i < 31; i++) { //31 is used becuase we are dealing with 32 bit numbers

		//if the LSB is 1
		if ((num & 1) == 1) {
	
			//take the OR of the reversed bit and 1
			reversedBit = 1 | reversedBit; //this will put the set bits into the reversed bit value
		}

		//shift	the reversed bit to the LEFT
                reversedBit = reversedBit << 1;

		//shift num to the RIGHT
                num = num >> 1;
        }

	return reversedBit;
}


/* Function: Fill a text string with a binary representation of the number that's passed in
   Type: void
   Parameters: pointer to a string - I interpted this as a char* array[] - and an unsigned integer 
   Output: N/A - here we are filling the pointer string with the values of the unsigned integer that was passed in
*/
void binary_string(char* point[], unsigned int num) {

   int shiftedNum;
   int bitLength;

	for (bitLength = 31; bitLength >= 0; bitLength--) { //Start from the END of the num since that is where the LSB is

		//start by shifting the passed in number to the RIGHT by the current bitLength value	
		shiftedNum = num >> bitLength; //this will push the vlaues in num to the right each time to find the 1's

		//if the LSB is 1
                 if ((shiftedNum & 1) == 1) {
			
			//pass in a 1 to the corresponding index of the string pointer
                 	point[bitLength] = "1";
                 }

		 //if the LSB is NOT 1
                 else {

			//pass in a 0 to the corresponding index of the string pointer
                   	point[bitLength] = "0";
                  }
	}
}

/* Function: Return the mod 128 of a number
   Type: int
   Parameters: integer 
   Return: The mod 128 (& 127) of any numbers in the array that are outside of the raange
*/
int bitwise_mod128(int num) {
   
   int numMod128 = num;

	//check to see if the number is outside of the range 0 ... 128
	if (num > 128) { //no need to check for negatives becuase the abs was taken
		
		/*Rule: mod 128 --> & 127*/
		numMod128 = num & 127;
	}

	return numMod128;
}

/* Function: Return the absoulte value	of a number
   Type: int
   Parameters: integer 
   Return: The absoulte value of the number that was passed in
*/
int bitwise_abs(int num) {

   int absNum; //return value
   int xOrAbs; //value for the xor

   /* Make a mask for the number that is passed in:
       - The mask will be all 1's for NEGATIVE
       - The mask will be all 0's for POSITIVE      */					        
	int absMask = num >> 31; //shift to the RIGHT by 31 - if the MSB is 1 --> absMask is all ones and vise versa

	//take the exclusive or - any double 1's or 0's will become 0's
	xOrAbs = num ^ absMask;	
	
	//subtract the xor by the mask to get the final abs of the passed in value
	absNum = (xOrAbs - absMask);

	return absNum;
}

/* Function: Extract the specified bit from a given number
   Type: int
   Parameters: 2 integer values
   Return: The rightmost digit in the num1 that was passed in
 */
int bit_get(int num1, int num2) {
 
   int specifiedBit; //return vlaue
 
	//shift num1 to the right by num2 and find the LSB and save it to the specified bit
	specifiedBit = (num1 >> num2) & 1; //get the rightmost digit in num1

	return specifiedBit; 

}



/* Function: See if the number pssed in is even or odd by returning 1 if number is even or 0 if the number is odd
   Type: int
   Parameters: integer
   Return: 1 if the number is EVEN - 0 if the number is ODD
 */
int even_or_odd(int num) {

   int evenOrOdd; //return vlaue
	
	//%2 --> &1
	if ((num & 1) == 0) {
	        
		//num is EVEN
		evenOrOdd = 1;
	}

	else {
              
                //num is ODD
		evenOrOdd = 0;
	}

	return evenOrOdd;
}


/* Function: Swap the numbers the pointers are pointing too without a using temp variable
   Type: void
   Parameters: 2 unsigned integer pointers 
   Output: N/A - this function swaps the values of the 2 pointers that were passed in
*/
void swap_ints(unsigned int *point1, unsigned int *point2) {

	*point2 = *point1 ^ *point2;
	*point1 = *point1 ^ *point2;
	*point2 = *point1 ^ *point2;
}
