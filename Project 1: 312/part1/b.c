
/*
 * Process B
 * Wait till there is a "1" in the INTEGER shared memory
 * Wirte "shared" to the STRING shared memory
 *   Signal that it is done writing by writing a "2" into the INTEGER shared memory
 * Then quit
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

int
main()
{

    unsigned int sleepSec = 60;

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

    /*
     * Now put some things into the STRING memory for the
     * other process to read.
     */
     sS = shmS;

	//if Process A HASN'T written a 1 in the shared memory
	while ( *shmI != '1' ) {
	   //sleep and wait
	   usleep(sleepSec);
	}

	//if Process A HAS written a 1 in the shared memory
	sprintf(sS, "shared"); //write message "shared" to the STRING shared memory

    /*
     * Signal that it's done by writing a "2" to the INTEGER shared memory
     */
    *shmI = '2';

    return 0;
}
