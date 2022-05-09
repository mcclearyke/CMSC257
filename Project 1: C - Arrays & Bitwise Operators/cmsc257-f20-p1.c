
////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-f20-p1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMSC257.  See the related assignment page for details.
//										
//	Fill in the autsor name and last modified date below
//  Author        : Kendall McCleary
//  Last Modified : 10/2/2020
//

// Include Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Project Includes
#include "p1-support.h"

//
// Functions

////////////////////////////////////////////////////////////////////////////////
// This is a sample comment for the main function	
// You should include a similar comment for each function you imoplemented within the .h file
//
// Function     : main
// Description  : The main function for the CMSC257 project #1
// 
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

// Function 	: ???
// ???

int main(int argc, char *argv[]) {

	// Local variables
	// NOTE: this is where you will want to add some new variables
	int int_array1[10], int_array2[10];
	unsigned int uint_array1[10];
	int i;
	//???
	int b;
	int c;
	int l;
	int r;
	int t;
	int g;
	int h;
	int arraySize = 10;
	int absNum;
	int evenOrOdd;
	int numOfOnes; 
	unsigned int *point1;
	unsigned int *point2;
	int last = 9;
	int number;
	char *pointerString[32];
	
	/* Read in the files */
	if (argc < 11)
	{
		printf("Exiting the program, missing input");
		return 0;	
	}
	// Step a - read in the integer numbers to process
	for (i=1; i<11; i++) {
	
		int_array1[i-1] = atoi(argv[i]);//converting input to integer

	}

	// Step b - Convert numbers into positive values by taking their 
	//           absolute values and save them in int_array2.
	for (b = 0; b < arraySize; b++) {

		//send the values of the array to be taken the absolute value of	
		absNum = bitwise_abs(int_array1[b]);
		
		//place the absolute number into the int_array2[] array
		int_array2[b] = absNum;
	}

	// Print all numbers in a single line using display_array function
	display_array(int_array2, arraySize); //pass the array and the size	


	// Step c - Convert these positive integers to numbers 
	//           in the range 0,…,128 by implementing the  mod operation
	//           save them back into int_array2. 
			
		for (c = 0; c < arraySize; c++) {

			int_array2[c] = bitwise_mod128(int_array2[c]);;
		}
	
	// Print all numbers in a single line using display_array function
	display_array(int_array2, arraySize);

	// Step d - for each integer in int_array2 print: 
	//           number, count of 1 bits, even or odd
	
		for (l = 0; l < arraySize; l++) {
		
			//Pass in the integer value to count the 1's
			numOfOnes = count_bits(int_array2[l]);
			
			//Pass in the integer to see if it is even or odd
			evenOrOdd = even_or_odd(int_array2[l]);

			if (evenOrOdd == 1) { //If the number is even
		
				printf("[number %10d : %10d # of 1 bits:%10d    Even] \n", l,  int_array2[l], numOfOnes);
			}

			else { //If the number is odd - evenOrOdd == 0
				
				printf("[number %10d : %10d # of 1 bits:%10d     Odd] \n", l,  int_array2[l], numOfOnes); 
			}
		}	 

	// Step e - Cast each element of int_array2 to unsigned int
	//			 and store them into uint_array1. 
	
		for (r = 0; r < arraySize; r++) {
		
			//cast as unsigned ints
			uint_array1[r] = (unsigned int) int_array2[r];

		}	

	// Step f - Reverse the order of array elements in uint_array1 
	//           using swap function. 
			
		for (t = 0; t < arraySize; t++) {
			
			//as long as t is less than last - t
			if (t < (last - t)) {		
			
				point1 = &uint_array1[t]; //assign the first pointer to the value at t: starts at 0
				point2 = &uint_array1[last - t]; //assign the second pointer to the value that is last - the vlaue of t: starts at index 9 - 0 = 9
				swap_ints(point1, point2); //send the pointers in	
			}			
		}	


	// Step g - Update each element of uint_array1 by using reverse_bits function. 
	
		for (g = 0; g < arraySize; g++) {
	
			//send the value in to get reversed
			uint_array1[g] = reverse_bits(uint_array1[g]);

			//save the current array value as an integer to get passed into the binary_string function
			number = (int) uint_array1[g];

			//pass in the char* point[] and int number
			binary_string(pointerString, number);
		
	  	// Step h - Print each element of uint_array1 in a separate line along with
        	//           binary representation of each of the numbers using binary_string function.

			printf("[number %10d : reversed :%10u    0b", g, uint_array1[g]);	

					
			for (h = 31; h >= 0; h--) { //It was stored backwards so print backwards

				printf("%s", pointerString[h]);
			}

		if (g == (arraySize-1)) {
		
			printf("]");
		}
	
		else {
			printf("]\n");
		}	
		}

	// Return successfully
	return(0);
}
