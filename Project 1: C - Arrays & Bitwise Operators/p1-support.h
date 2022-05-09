#ifndef CMSC257_A1SUPPORT_INCLUDED
#define CMSC257_A1SUPPORT_INCLUDED

///////////////////////////////////////////////////////////////////////////////
//  File          : p1-support.h
//  Description   : This is a set of general-purpose utility functions we use
//                  for the 257 assignment #1.
//  Author        : Kendall McCleary
//  Last Modified : 10/2/2020
//////////////////////////////////////////////////////////////////////////////

// Functional Prototypes
//
// Include description, input and output for each function here in this file
// You don't need to copy them into the p1-support.c file.	There is a sample
// for main function within the ..p1.c file.


/* Function: To display an array that is passed in - in a single line
   Type: void
   Parameters: int array, int size of array
   Output: the array displayed
*/
void display_array(int array[], int size);


/* Function: Count the number of 1's in a number
   Type: int
   Parameters: integer to count the number of 1's from
   Return: the number of ones in a number
*/
int count_bits(int num);


/* Function: Revese the bits of an unsigned int number that is passed in
   Type: unsigned int
   Parameters: unsigned int that will be reversed
   Return: The reversed of the unsigned int that was passed in
*/
unsigned int reverse_bits(unsigned int num);


/* Function: Fill a text string with a binary representation of the number that's passed in
   Type: void
   Parameters: pointer to a string - I interpted this as a char* array[] - and an unsigned integer
   Output: N/A - here we are filling the pointer string with the values of the unsigned integer that was passed in
*/
void binary_string(char* point[], unsigned int num);


/* Function: Return the mod 128 of a number
   Type: int
   Parameters: integer
   Return: The mod 128 (& 127) of any numbers in the array that are outside of the raange
*/
int bitwise_mod128(int num);


/* Function: Return the absoulte value  of a number
   Type: int
   Parameters: integer
   Return: The absoulte value of the number that was passed in
*/
int bitwise_abs(int num);


/* Function: Extract the specified bit from a given number
   Type: int
   Parameters: 2 integer values
   Return: The rightmost digit in the num1 that was passed in
 */
int bit_get(int num1, int num2);


/* Function: See if the number pssed in is even or odd by returning 1 if number is even or 0 if the number is odd
   Type: int
   Parameters: integer
   Return: 1 if the number is EVEN - 0 if the number is ODD
 */
int even_or_odd(int num);


/* Function: Swap the numbers the pointers are pointing too without a using temp variable
   Type: void
   Parameters: 2 unsigned integer pointers
   Output: N/A - this function swaps the values of the 2 pointers that were passed in
*/
void swap_ints(unsigned int *point1, unsigned  int *point2);

//??? add other helper functions as needed. functions above are minimums.

void check_reverse(unsigned int num);
#endif // CMSC257_A1SUPPORT_INCLUDED
