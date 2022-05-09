 /**
 * This program will be doing the same function as the code in the part1 dir
 * Create Processes A, B and C from the SAME file using FORK
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h> /* for exit */

#define SHMSZ     27

int
main()
{
    //Process A will be the Parent Process

    //Child Process B
    int pidB;

    //Child Process C
    int pidC;
      
    //INTEGER Shared Memory
    int shmidI;
    key_t keyI;
    char *shmI, *sI;

    //STRING Shared Memory
    int shmidS;
    key_t keyS;
    char *shmS, *sS;

    int sleepSec = 100;

    int status;

    /**************************************
     * Setting Up the INTEGER Shared Memory
     **************************************/

    /* We'll name our INTEGER shared memory segment:  "4112" */
    keyI = 4112;

    /* Create the segment. */
    if ((shmidI = shmget(keyI, SHMSZ, IPC_CREAT | 0666)) < 0 ) {
     	
	perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    if ((shmI = shmat(shmidI, NULL, 0)) == (char *) -1 ) {

     	perror("shmat");
        exit(1);
    }

    /**************************************
     * Setting Up the STRING Shared Memory
     **************************************/

    /* We'll name our STRING shared memory segment "2312". */
    keyS = 2312;

    /* Create the segment. */
    if ((shmidS = shmget(keyS, SHMSZ, IPC_CREAT | 0666)) < 0 ) {
     	
	perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    if ((shmS = shmat(shmidS, NULL, 0)) == (char *) -1 ) {

     	perror("shmat");
        exit(1);
    }


    /* Parent: Now put some things into the memory for the other process to read. */
    sI = shmI;
	
	//Write a "1" to the INTEGER shared memory
	*sI = '1';   

    /* Create a child process - Process B */
    pidB = fork();

	if (pidB == 0) {

	    sS = shmS;

            //if Process A HASN'T written a 1 in the shared memory
            while ( *shmI != '1' ) {
               //sleep and wait
               usleep(sleepSec);
            }

	    //if Process A HAS written a 1 in the shared memory
            sprintf(sS, "shared"); //write message "shared" to the STRING shared m$

 	   /* Signal that it's done by writing a "2" to the INTEGER shared memory */
   	    *shmI = '2';
		exit(0);

	//end child B
	}

    //Parent code -> wait for B
    usleep(900);

         //For Process B
         while( *shmI != '2' ) {
             sleep(1);
         }

     	 //outprint what Process B put in the STRING shared memory
         printf("%s\n", shmS);
	
    /* Create a child process - Process C */
     pidC = fork();
	
         if (pidC == 0) {
	
         //if Process B HASN'T written a 2 in the shared memory
         while ( *shmI != '2' ) {
            //sleep and wait
            usleep(sleepSec);
         } 

         //if Process B HAS written a 2 in the shared memory
         sprintf(shmS, "memory"); //write message "memory" to the STRING shared$

    	 /* Signal that it's done by writing a "2" to the INTEGER shared memory */
	 *shmI = '3';
	     exit(0);

	//end Process C
	}

	//Parent code -> Give process B time to print
	sleep(1);

           //For Process C
           while( *shmI != '3' ) {
              sleep(1);
          }

     	  //outprint what Process C put in the STRING shared memory
          printf("%s\n", shmS);	

	  //Parent code -> Give process C time to print
	  sleep(1);

	  //Goodbye Message
          printf("GoodBye\n");

          /** now detach the INTEGER shared memory segment */
          if (shmdt(shmI) == -1) {
              fprintf(stderr, "Unable to detach\n");
          }

          /** now remove the INTEGER shared memory segment */
          shmctl(shmidI, IPC_RMID, NULL);
	
	  /** now detach the STRING shared memory segment */
          if (shmdt(shmS) == -1) {
              fprintf(stderr, "Unable to detach\n");
          }

	  /** now remove the STRING shared memory segment */
          shmctl(shmidS, IPC_RMID, NULL);

        return 0;
}

