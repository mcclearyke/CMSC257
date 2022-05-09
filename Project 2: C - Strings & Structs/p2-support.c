/* This program's main function is to practice C strings and structs.
   - Also using gdb and valgrind
   - Become confortable with pointers and makefiles
  This project will have us cretae a menu-driven employee database

   Author: Kendall McCleary
   Last Edit: 10/24/2020 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"
 
int j = 0;
int size;

void initialize (struct DataBase *db) {   

  //(*db).emp
  db->emp = (struct Employee*) malloc(sizeof(struct Employee)*dbSIZE);
  //allocate memory for 100 employees
 
  db->total = 0;
  //there are 0 employees at the beginning
  
  createRecord ("00306", "Wei", "Martin", "wm@aol.com", 98999.99, db);
  createRecord ("00307", "Mitch", "Martinez", "mitch@aol.com", 78999.88, db);
  createRecord ("00408", "David", "Boyle", "db@aol.com", 100000.01, db);
  createRecord ("00204", "Christine", "Bluer", "cb@aol.com", 40009.99, db);
  createRecord ("00305", "Stephen", "Black", "sb@aol.com", 8500.01, db);
  createRecord ("00409", "Chris", "Boyle", "cb@aol.com", 200000.01, db);
  createRecord ("00101", "Paula", "Brown", "pb@aol.com", 1000.37, db);
  createRecord ("00102", "Paul", "Green", "pg@aol.com", 2700.45, db);
  createRecord ("00203", "Chris", "Reddy", "cr@aol.com", 2304.67, db);
  
}
 
//add other function definitions
/* Function that takes in the vlaues from the struct Employees and builds a database with them */
void createRecord(char* ID, char* firstName, char* lastName, char* email, double salary, struct DataBase *db) {	

       db->emp->ID = ID;
	employ[j].ID = ID;

       db->emp->firstName = firstName;
	employ[j].firstName = firstName;

       db->emp->lastName = lastName;
	employ[j].lastName = lastName;	

       db->emp->email = email;
	employ[j].email = email;	

       db->emp->salary = salary;
	employ[j].salary = salary;

	j++;

	db->total = j;	
} 


/* Function that handles most of the implementation

   - Shows the menu for the user to chose from
   - Uses conditionals to perform the task that is determined by the user input
*/
void displayMenu (struct DataBase *db) {

int i;
int k;
int t;
int incr;
size = db->total;

//Show the menu
printf("\n**************************************************************   \n");
printf("***** mcclearyke Employee Database - Total Employees:  %d ***** \n", db->total);
printf("**************************************************************  \n");
printf("Choose one of the menu options below: \n");               
printf("1. Sort with ID\n");
printf("2. Display all employees\n");
printf("3. Search employee by ID\n");
printf("4. Search employee by Last Name\n");
printf("5. Delete employee by ID\n");
printf("6. Delete employee by Last Name\n");
printf("7. Exit\n");
printf("Enter your choice :\n");

	//if the user inputed an accepted number
	if (scanf("%d",&i) == 1 || 
	    scanf("%d",&i) == 2 ||
	    scanf("%d",&i) == 3 ||
            scanf("%d",&i) == 4 ||
            scanf("%d",&i) == 5 ||
            scanf("%d",&i) == 6 ||
            scanf("%d",&i) == 7    ) {

		/* This conditional deals with:
		   Sort the ID's from lowest to highest */
		if (i == 1) {			
		
			/* Create an array to look throught the values */     
	  		char* idCheck[size];
			char* newID[size];
			incr = 0; 
			int resultL;
			int pos;			

			for (k = 0; k < (size); k++) {
			
				//start by saving the value stored in employ[j] into a char array that can be looped through
				idCheck[k] = employ[k].ID;
			}

			while(incr < size) { 

			    /* Loop through the created array and find the max */
                            char* low = idCheck[incr];
			
				for (t = 0; t < size; t++) {

				   resultL = strcmp(idCheck[t], low);
	
					if (resultL < 0) {
				
						low =  idCheck[t];
						pos = t;
					}
					
					if (resultL == 0) {

						low =  idCheck[t];
                                                pos = t;
					}

					if (t == (size - 1)) {
			
						newID[incr] = low;
	
						idCheck[pos] = "99999";		
						
						incr++;
					}

				}
			}	
			
			//send the newly ordered ID's to a new method
			case1(newID, db);
		//shw the menu again
		displayMenu(db);
		//end of case 1
		}

	
		/* This condtional deals with:
		   Display all the information in the database */
		if (i == 2) {
	 		
			int e = 0; 
			int maxN;
			int nameSpace;
			int first;
			int last;
			int emailSpace;
			int email;
			

			printf("No. EmpID Employee Name        Email                Salary    \n");
			printf("--- ----- -------------------- -------------------- ---------- \n");

        		while(e < (db->total)) {
				
			   /*Formatting*/
			   maxN = 0;
                           nameSpace = 0;
			   emailSpace = 0;	
	
			  	first = strlen(employ[e].firstName);
		
		        	last = strlen(employ[e].lastName);

				maxN = (first + last + 1);
		
				nameSpace = (21 - maxN);
	
			   	email = strlen(employ[e].email);

			   	emailSpace = (21 - email);
				
							
				printf("%d   %s %s %s", e, employ[e].ID, employ[e].firstName, employ[e].lastName);

				printf("%*s", nameSpace, "");

			    	printf("%s", employ[e].email);

				printf("%*s", emailSpace, "");
				
				printf("$ ");

				printf("%0.2f\n", employ[e].salary);

                                e++;

			//end while
			}

		displayMenu(db);
		//end of case 2
		}
 

		/* This conditinal deals with:
		   Search the employees by their ID's */
		if (i == 3) {
		
			char enteredID[idSIZE];
			int w;	
			int find;
			int found;
			int z = 0;
			int none = 0;
			
			//Ask for the ID to be searched for
			printf("Please enter the ID of the employee you wish to search:\n");
				scanf("%s", enteredID);
	
			for (w = 0; w < (db->total); w++) {
	
				//check to see if the entered ID is the same as an element in the database
				find = strcmp(employ[w].ID, enteredID);
	
				//if they are the SAME
				if (find == 0) {
				   none++;					
					 printf("No. EmpID Employee Name        Email                Salary    \n");
                       			 printf("--- ----- -------------------- -------------------- ---------- \n");				
					

					int maxN;
                        		int nameSpace;
                        		int first;
                       			int last;
                        		int emailSpace;
                        		int email;
					
					while(z < (db->total)) {
		
	             				found = strcmp(employ[z].ID, enteredID);
			
						if (found == 0) {

						 /*Formatting*/
                           			 maxN = 0;
                          			 nameSpace = 0;
                          			 emailSpace = 0;

                           				first = strlen(employ[z].firstName);
	
        		                	        last = strlen(employ[z].lastName);

                           				maxN = (first + last + 1);

                        	        		nameSpace = (21 - maxN);
					
        			                        email = strlen(employ[z].email);

        	                    		       emailSpace = (21 - email);
	
	
        		                	        printf("%d   %s %s %s", z, employ[z].ID, employ[z].firstName, employ[z].lastName);

                        			        printf("%*s", nameSpace, "");

                        	        		printf("%s", employ[z].email);
					
        	 				        printf("%*s", emailSpace, "");
	
                                	       		printf("$ ");

                                			printf("%0.2f\n", employ[z].salary);

							break;
						}
					
						else {
                                			z++;
						}
					}		
				//end if
				}
				
			        if (w == ((db->total)-1) && none == 0) {
	
					 printf("No. EmpID Employee Name        Email                Salary    \n");
                                         printf("--- ----- -------------------- -------------------- ---------- \n");
				} 

			//end for
			}

		displayMenu(db);		
		//end of case 3
		}


		/* This conditinal deals with:
		   Search the employees by their Last Name */
		if (i == 4) {
		
		 	char enteredName[nameSIZE];
                        int p;
                        int find;
                        int found;
                        int z = 0;

			//Get the last name that is going to be searched for
                        printf("Please enter the Last Name  of the employee you wish to search: \n");
                                scanf("%s", enteredName);

                        for (p = 0; p < (db->total); p++) {
	
				//check to see if the enetered name is in the database
                                find = strcmp(employ[p].lastName, enteredName);

                                //if they are the SAME
                                if (find == 0) {

                                         printf("No. EmpID Employee Name        Email                Salary    \n");
                                         printf("--- ----- -------------------- -------------------- ---------- \n");

                                        int maxN;
                                        int nameSpace;
                                        int first;
                                        int last;
                                        int emailSpace;
                                        int email;

					 while (z < (db->total)) {

                                                found = strcmp(employ[z].lastName, enteredName);

                                                if (found == 0) {
	                                                
						 /*Formatting*/
                                                 maxN = 0;
                                                 nameSpace = 0;
                                                 emailSpace = 0;

                                                	first = strlen(employ[z].firstName);

                                        	        last = strlen(employ[z].lastName);

                                	                maxN = (first + last + 1);

                        	                        nameSpace = (21 - maxN);

                	                                email = strlen(employ[z].email);

        	                                        emailSpace = (21 - email);
	

                                	                printf("%d   %s %s %s", z, employ[z].ID, employ[z].firstName, employ[z].lastName);

                        	                        printf("%*s", nameSpace, "");

                	                                printf("%s", employ[z].email);

        	                                        printf("%*s", emailSpace, "");	   

							printf("$ ");

                                                	printf("%0.2f\n", employ[z].salary);
        			                                        
                                                }
                      
                                                      	z++;
                                        }
				break;
                                //end if
                                }
                        //end for
                        }

		displayMenu(db);
                //end of case 4
                }
	
 
		/* This conditional deals with:
		    Delete an employee based on their ID */		
		if (i == 5) {

			char enteredDeleteID[idSIZE];
			int y;
                        int w;
                        int find;
                        int found;
                        int z = 0;
			int newSize;

			//Get the ID that will be deleted
                        printf("Please enter the ID of the employee you wish to delete:\n ");
                                scanf("%s", enteredDeleteID);

                        for (w = 0; w < (db->total); w++) {

				//look for the enetered ID in the database
                                find = strcmp(employ[w].ID, enteredDeleteID);

                                //if they are the SAME
                                if (find == 0) {

                                         printf("No. EmpID Employee Name        Email                Salary    \n");
                                         printf("--- ----- -------------------- -------------------- ---------- \n");

					int maxN;
                                        int nameSpace;
                                        int first;
                                        int last;
                                        int emailSpace;
                                        int email;
					
                                         while(z < (db->total)) {

                                                found = strcmp(employ[z].ID, enteredDeleteID);

                                                if (found == 0) {
						
						 /*Formatting*/
                                                 maxN = 0;
                                                 nameSpace = 0;
                                                 emailSpace = 0;

                               	                	first = strlen(employ[z].firstName);

                                                	last = strlen(employ[z].lastName);

                                        	        maxN = (first + last + 1);

                                	                nameSpace = (21 - maxN);

                        	                        email = strlen(employ[z].email);

                	                                emailSpace = (21 - email);


        	                                        printf("%d   %s %s %s", z, employ[z].ID, employ[z].firstName, employ[z].lastName);

	                                                printf("%*s", nameSpace, "");

                                                	printf("%s", employ[z].email);

                                                	printf("%*s", emailSpace, "");

                                                	printf("$ ");

                                                	printf("%0.2f\n", employ[z].salary);
                                        
						//end if
					       	}

                                                      	z++;
					//end while				
                                        }
			
					/* Delete the ID */
					newSize = (db->total) - 1;
	
                                	(db->total) = newSize;

					for (y = w; y < newSize; y++) {
			
						employ[y].ID = employ[y + 1].ID;
						employ[y].firstName = employ[y + 1].firstName;
						employ[y].lastName = employ[y + 1].lastName;
						employ[y].email = employ[y + 1].email;		
						employ[y].salary = employ[y + 1].salary; 
					//end for
					}						
		
                                //end if
                                }
			//end of for loop
                        }

		displayMenu(db);
                //end of case 5
                }


		/* This conditional deals with:
		   Delete an empolyee based on their last name */
		if (i == 6) {

			char enteredDeleteName[nameSIZE];
                        int p;
                        int find;
                        int found;
                        int z = 0;
			int u;
			int once = 0;		

			//Get the last name	
                        printf("Please enter the Last Name of the employee you wish to delete: \n");
                                scanf("%s", enteredDeleteName);

                        for (p = 0; p < (db->total); p++) {
	
				//check to see if it is in the database
                                find = strcmp(employ[p].lastName, enteredDeleteName);

 
				 //if they are the SAME
                                if (find == 0) {
					
					int maxN;
                                        int nameSpace;
                                        int first;
                                        int last;
                                        int emailSpace;
                                        int email;

                                         while(z < (db->total)) {

                                                found = strcmp(employ[z].lastName, enteredDeleteName);

                                                if (found == 0 && once == 0) {
 							 printf("No. EmpID Employee Name        Email                Salary    \n");
                                        		 printf("--- ----- -------------------- -------------------- ---------- \n");
							

							/*Formatting*/
                                                 	maxN = 0;
                                                 	nameSpace = 0;
                                                 	emailSpace = 0;

                                                	first = strlen(employ[z].firstName);

                                                	last = strlen(employ[z].lastName);

                                                	maxN = (first + last + 1);

                                                	nameSpace = (21 - maxN);

                                                	email = strlen(employ[z].email);

                                                	emailSpace = (21 - email);


                                                	printf("%d   %s %s %s", z, employ[z].ID, employ[z].firstName, employ[z].lastName);

                                                	printf("%*s", nameSpace, "");

                                                	printf("%s", employ[z].email);

                                               		printf("%*s", emailSpace, "");

                                                	printf("$ ");

                                                	printf("%0.2f\n", employ[z].salary);
							
							once++; //variable to make sure that only the first empolyee with that last name gets deleted
							
							 /* Delete the last name */
                                                        int newSize2 = (db->total) - 1;

                                                        (db->total) = newSize2;

                                                        for (u = p; u < newSize2; u++) {

                                                                employ[u].ID = employ[u + 1].ID;
                                                                employ[u].firstName = employ[u + 1].firstName;
                                                                employ[u].lastName = employ[u + 1].lastName;
                                                                employ[u].email = employ[u + 1].email;
                                                                employ[u].salary = employ[u + 1].salary;

                                                        //end for loop
                                                        }

                                                        break;
                                                //end if
                                               }

                                                        z++;
                                        //end while
                                        }

                                //end if
                                }
                        //end for
                        }
 			
		displayMenu(db);
		//end of case 6
		}
 
		
		/* This conditional deals with:
		   Freeing up memory and exiting the menu */
		if (i == 7) { 
		
			 printf("Bye! \n");
			 quit(db);
			 exit(0);
		//end case 7
		}

        //end if
	}

	//if the user dosen't input an accepted character
	else {

	        printf("Enter only an Integer\n");
                exit(0);
	//end else
	}
}

/* This Function takes in an array with the employee ID's arranged from lowest to highest
   It will update the database */
void case1(char* newID[], struct DataBase *db) {
int q = 0;
int e = 0; 
int change;
int size = db->total;
int y;
char *originID[size];
char *originFN[size];
char *originLN[size];
char *originE[size];
double originS[size];

	while(q < size) {

        	for (e = 0; e < size; e++) {

         		change = strcmp(newID[q], employ[e].ID);

                       	 if (change == 0) {

				originID[q] = employ[e].ID;
				originFN[q] = employ[e].firstName;
				originLN[q] = employ[e].lastName;
				originE[q] = employ[e].email;
				originS[q] = employ[e].salary;
			}

			if (e == (size - 1)) {
				q++;
			}
	      }
	}

	//update
	for (y = 0; y < size; y++) {
	
		employ[y].ID = originID[y];
		
	      	employ[y].firstName = originFN[y];

      		employ[y].lastName = originLN[y];

        	employ[y].email = originE[y];

        	employ[y].salary = originS[y];
	}

}

//This Function frees any allocated memory - preventing leaks
void quit(struct DataBase *db) {

	free(db);

	free(db->emp);
}
