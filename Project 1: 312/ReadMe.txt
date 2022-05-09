When using make to run code in part5 and part6 be sure to edit avg.h by changing the data struct value from 
double *input_data_val;
char * input_data_val;

All files were last edited on: 2/24/2021
By Kendall McCleary
For 312 Assignment1

dir part1:
	Write a simple program where processes synchronize via polling such that a process A prints out the strings of two other separate writing processes (B 
	first and then C second) from shared memory. Process A needs to 'wait' by polling until B and C finish writing their strings to memory. Each of processes 
	A, B and C should be in different code files. Create TWO different shared memory locations: (i) one for storing the integer identifier and (ii) for storing 
	the string.

dir part2:
	Create processes A, B and C from the same file using fork.

dir part3:
	Review the programs (spock.c and kirk.c).

dir part4:
	Modify the average RPC programs (avg.x, avg_proc.c and ravg.c) so that it computes the median of a maximum of 100 numbers instead of the average of a maximum 
	of 200 numbers.

dir part5:
	Write a program using remote procedure calls where the server simply echoes the word back to the client.

dir part6: I USED THE CONDITION IF THE CLIENT SPELLS IT OUT
	Modify the average RPC program so that the server sends back a list of 'sorted' numbers to the client either in descending or ascending order given by an input 
	parameter when invoking the client, e.g., the word "ascending:, "descending" 
	
