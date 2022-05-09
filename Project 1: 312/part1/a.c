
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */


/* 
 * Process A
 * Wirte "1" - INTEGER shared memory
 * Keeps polling the INTEGER shared memory
 *   After B writes "shared" to the STRING shared memory - A prints it out signalled by the "2" in the INTEGER shared memory
 *   After C writes "memory" to the STRING shared memory - A prints it out signalled by the "3" in the INTEGER shared memory
 * A is the last to quit and will print out "GoodBye" message
 */



#define SHMSZ     27


int 
main()
{
    //INTEGER Shared Memory
    int shmidI;
    key_t keyI;
    char *shmI, *sI;

    //STRING Shared Memory  
    int shmidS;
    key_t keyS;
    char *shmS, *sS;

    /**************************************
     * Setting Up the INTEGER Shared Memory
     **************************************/

    /*
     * We'll name our INTEGER shared memory segment
     * "4112".
     */
    keyI = 4112;

    /*
     * Create the segment.
     */
    if( (shmidI = shmget(keyI, SHMSZ, IPC_CREAT | 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if( (shmI = shmat(shmidI, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }

    /**************************************
     * Setting Up the STRING Shared Memory
     **************************************/

    /*
     * We'll name our STRING shared memory segment
     * "2312".
     */
    keyS = 2312;

    /*
     * Create the segment.
     */
    if( (shmidS = shmget(keyS, SHMSZ, IPC_CREAT | 0666)) < 0 )
    {
     	perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if( (shmS = shmat(shmidS, NULL, 0)) == (char *) -1 )
    {
     	perror("shmat");
        exit(1);
    }

     /**************************************
     * Write to the INTEGER Shared Memory
     **************************************/

    /*
     * Now put some things into the INTEGER memory for the
     * other process to read.
     */
    sI = shmI;
         
        //Write a "1" to the INTEGER shared memory
        *sI = '1';


    /*
     * Finally, we wait until the other process changes
     * the value of the INTEGER shared memory
     */

    //For Process B
    while( *shmI != '2' ) {
        sleep(1);
    }
	
	//outprint what Process B put in the STRING shared memory
	printf("%s\n", shmS);

    //For Process C
    while( *shmI != '3' ) {
        sleep(1);
    }

        //outprint what Process C put in the STRING shared memory
        printf("%s\n", shmS);

    //print out a "GoodBye" message before qutting
    printf("GoodBye \n");

    return 0;
}
