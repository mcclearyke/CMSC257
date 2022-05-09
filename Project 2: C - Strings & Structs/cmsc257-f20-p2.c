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


int main () {
  struct DataBase* db; 
  db = malloc(sizeof(struct DataBase));
  initialize (db);
  displayMenu (db);
  return 0;
}

