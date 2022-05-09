/* This program's main function is to practice C strings and structs.
   - Also using gdb and valgrind
   - Become confortable with pointers and makefiles
  This project will have us cretae a menu-driven employee database

   Author: Kendall McCleary
   Last Edit: 10/24/2020 */

#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 11
#define emailSIZE 21
//add other define Macros
 
struct Employee {
  
	char* ID;
	char* firstName;
	char* lastName;
	char* email;
 	double salary;

} employ[dbSIZE];
 
struct DataBase {
	
	int total;	
	struct Employee* emp;
};
 

 
/////////////////////////////////////////////////////////////////////////////////////
// This is a sample comment for the initialize function	
// You should include a similar comment for each function declared within the .h file
//
// Function     : initialize
// Description  : Initializes the database for CMSC257 project #2 by manually entering // the records using createRecord function
// Inputs       : struct DataBase * - pointer to the database    
// Outputs      : void
/////////////////////////////////////////////////////////////////////////////////////

void initialize (struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : creates the database
// Description  : This function takes the vlaues from the Employee struct and creates a database of information of each empolyee with the informtion the initialize function passes in
// Inputs	: char* ID, char* firstName, char* lastName, char* email, double salary, struct DataBase *db
// Outputs	: void
///////////////////////////////////////////////////////////////////////////////////// 

void createRecord (char* ID, char* firstName, char* lastName, char* email, double salary, struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : displays the menu and implements most of the functionality of this project
// Description  : This function gets the uer input and bases the programs functions off of them - mostly with the use of conditional statements
// Inputs	: struct DataBase *db
// Outputs	: void
///////////////////////////////////////////////////////////////////////////////////// 

void displayMenu (struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : updates how the database is sorted
// Description  : This function updates the database and sorts the empoyee information based in their ID's
// Inputs	: char* newID[] - a char array contain the ID values from lowest to highest and struct DataBase *db
// Outputs      : void
/////////////////////////////////////////////////////////////////////////////////////

void case1(char* newID[], struct DataBase *db);

/////////////////////////////////////////////////////////////////////////////////////
// Function     : free memory
// Description  : This function gets the pointer to the database passes in frees it to clear up memory and prevent leaks
// Inputs	: struct DataBase *db
// Outputs      : void
/////////////////////////////////////////////////////////////////////////////////////

void quit(struct DataBase *db); 
//add other function definitions

