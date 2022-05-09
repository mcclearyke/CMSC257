/* TO DO:
* 1. fix deqeue
* DONE:
* 1. shared memory is set up
* 2. producer is inserting into the buffer
* 3. fork is working
* 4. random numbers are being made correctly
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>

#define SIZE 25
#define LOWERJOBS 1
#define UPPERJOBS 25
#define LOWERSIZE 100
#define UPPERSIZE 1000

/* Create a struct for the new binary semaphores to make them act like a counting one */
struct countingSemaphore {

    int val;

    //binary 1
    sem_t b1; //BSem gate

    //binary 2
    sem_t b2; //BSem mutext

};

/* now define the full_sem and empty_sem */
struct countingSemaphore *full_sem;
struct countingSemaphore *empty_sem;

/* Create a struct for the global buffer */
struct producerPrintRequest {

   //book keeping paramters
   int producerID;
   int jobSize;

   //mutex -> so mutex lock can be used
   pthread_mutex_t bufferMutex;

   //variable to show if a place in the buffer is empty or has something in it
   int emptyOrFull; //NEEDED FOR DEQUEUEING!!
};

struct producerPrintRequest *globalBuffer;
int *bufferIndexProducer;
int *bufferIndexConsumer;

/* MY sem_init function */
void my_sem_init(struct countingSemaphore *cs, int k) {

  //int val = k
  cs->val = k; //set full_sem to the buffer size (SIZE) or empty_sem to 0

    if (cs->val == 0) {

      sem_init(&cs->b1, 0, 0); //b1 is initalized to 0 if val = 0 -> 3rd value
    }

    else if (cs->val > 0) {

      sem_init(&cs->b1, 0, 1); //b1 is initalized to 1 if val > 0 -> 3rd value
    }

  sem_init(&cs->b2, 0, 1); //b2 is initalized to 1 -> 3rd value
}


/* MY sem_wait function */
void my_sem_wait(struct countingSemaphore *cs) {

  //P(gate) -> b1
  sem_wait(&cs->b1);

  //P(mutex) -> b2
  sem_wait(&cs->b2);

  //val = val - 1
  cs->val = cs->val - 1;

    //if (val > 0)
    if (cs->val > 0) {

      //V(gate) -> b1
      sem_post(&cs->b1);
    }

  //V(mutex) -> b2
  sem_post(&cs->b2);
}


/* MY sem_post function */
void my_sem_post(struct countingSemaphore *cs) {

  //P(mutex) -> b2
  sem_wait(&cs->b2);

  //val = val + 1
  cs->val = cs->val + 1;

    //if (val = 1)
    if (cs->val == 1) {

      //V(gate) -> b1
      sem_post(&cs->b1);
    }

  //V(mutex) -> b2
  sem_post(&cs->b2);
}

void insertbuffer(int id, int size, int index) {

  //add the book keeping parameters to the global buffer
  globalBuffer[index].producerID = id;

  globalBuffer[index].jobSize = size;

  //now that there is something in the global buffer at this index -> set the emptyOrFull value to 2
  //2 -> full - has both values added
  globalBuffer[index].emptyOrFull = 2;
}

/*RETURN A producerPrintRequest object*/
//buffer_t dequeuebuffer()
struct producerPrintRequest dequeuebuffer(int index) {

   //the global buffer at the index that was passed in is currently full
   //we want to dequeue at this index so it needs to be 0
   globalBuffer[index].emptyOrFull = 0; //make it empty

   //now return the global buffer at this index
   return globalBuffer[index]; //return buffer[--buffer_index];
}


/* Output "Producer <process-id> added <job_size> to the buffer" */
void producer(int pidProcess, int processJobs) {

  int j = 0;

  int size;

  //each process job will get a random
  while (j < processJobs) {

    //Get a random size (100 - 1000)
    srand(time(0) ^ getpid());
    size = (rand() % (UPPERSIZE - LOWERSIZE + 1)) + LOWERSIZE;

    /* Calling sem_wait --> Call my_sem_wait(&full_sem) */
    my_sem_wait(full_sem); // sem=0: wait. sem>0: go and decrement it

    pthread_mutex_lock(&globalBuffer->bufferMutex); /* protecting critical section */

        insertbuffer(pidProcess, size, *bufferIndexProducer);

        printf("Producer %d added %d to buffer\n", pidProcess, size);

        *bufferIndexProducer = *bufferIndexProducer + 1;

    pthread_mutex_unlock(&globalBuffer->bufferMutex);

    /* Calling sem_post --> Call my_sem_post(&empty_sem) */
    my_sem_post(empty_sem); // post (increment) emptybuffer semaphore

    sleep(2);

    j++;
   
   }

   exit(0);
}

/* Output -> "Consumer <consumer-id> dequeue <process-id, job_size> from buffer" */
void *consumer(void *thread_n) {

  int thread_numb = *(int *)thread_n;

  //buffer_t value
  struct producerPrintRequest delete; //going to be returning globalBuffer[index] -> create a temp producerPrintRequest object to hold it

  //Make an infinite while loop -> 1
  while (1) {

    /* Calling sem_wait --> Call my_sem_wait(&empty_sem) */
    my_sem_wait(empty_sem);

    pthread_mutex_lock(&globalBuffer->bufferMutex);

        //value = dequeuebuffer()
        delete = dequeuebuffer(*bufferIndexConsumer);

        *bufferIndexConsumer = *bufferIndexConsumer + 1;

    pthread_mutex_unlock(&globalBuffer->bufferMutex);

    /* Calling sem_post --> Call my_sem_post(full_sem) */
    my_sem_post(full_sem); // post (increment) fullbuffer semaphore

    sleep(2);

    printf("Consumer %d dequeue %d, %d from buffer\n", thread_numb, delete.producerID, delete.jobSize);
  }
}


int main(int argc, char *argv[]) {

  //full semaphore
  int shmidSemaphoreF;
  key_t keySemaphoreF;

  //empty semaphore
  int shmidSemaphoreE;
  key_t keySemaphoreE;

  //global buffer
  int shmidSemaphoreGB;
  key_t keySemaphoreGB;

  //process
  int i = 0;
  int processJobs;

  //threads
  int j;

  //buffer index variables
  int shmidSemaphoreBIP;
  key_t keySemaphoreBIP;
  int shmidSemaphoreBIC;
  key_t keySemaphoreBIC;

    /* Set up shared memory */

    //FULL SEMAPHORE
    /* We'll name our FULL SEMAPHORE shared memory segment -> "88531". */
    keySemaphoreF = 88531;

    /* Create the segment. */
    if ((shmidSemaphoreF = shmget(keySemaphoreF, sizeof(struct countingSemaphore), IPC_CREAT | 0666)) < 0 ) {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    if ((full_sem = shmat(shmidSemaphoreF, NULL, 0)) == (char *) -1 ) {
        perror("shmat");
        exit(1);
    }

    printf("full_sem connected\n");

    //EMPTY SEMAPHORE
    /* We'll name our EMPTYSEMAPHORE shared memory segment -> "81537". */
    keySemaphoreE = 81537;

    /* Create the segment. */
    if ((shmidSemaphoreE = shmget(keySemaphoreE, sizeof(struct countingSemaphore), IPC_CREAT | 0666)) < 0 ) {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    if ((empty_sem = shmat(shmidSemaphoreE, NULL, 0)) == (char *) -1 ) {
        perror("shmat");
        exit(1);
    }

    printf("empty_sem connected\n");

    //GLOBAL BUFFER
    /* We'll name our GLOBAL BUFFER shared memory segment -> "92635". */
    keySemaphoreGB = 92635;

    /* Create the segment. */
    if ((shmidSemaphoreGB = shmget(keySemaphoreGB, sizeof(struct producerPrintRequest) * 25, IPC_CREAT | 0666)) < 0 ) {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    if ((globalBuffer = shmat(shmidSemaphoreGB, NULL, 0)) == (char *) -1 ) {
        perror("shmat");
        exit(1);
    }

    printf("globalBuffer connected\n");

    //for buffer index variable
    /* We'll name our BUFFER INDEX FOR PRODUCERE shared memory segment -> "46120". */
    keySemaphoreBIP = 46120;

    /* Create the segment. */
    if ((shmidSemaphoreBIP = shmget(keySemaphoreBIP, sizeof(int), IPC_CREAT | 0666)) < 0 ) {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    bufferIndexProducer = (int *) shmat(shmidSemaphoreBIP, NULL, 0);

    printf("bufferIndexProducer connected\n");

    //it'll start at 0
    *bufferIndexProducer = 0;

    /* We'll name our BUFFER INDEX FOR CONSUMER shared memory segment -> "30481". */
    keySemaphoreBIC = 30481;

    /* Create the segment. */
    if ((shmidSemaphoreBIC = shmget(keySemaphoreBIC, sizeof(int), IPC_CREAT | 0666)) < 0 ) {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    bufferIndexConsumer = (int *) shmat(shmidSemaphoreBIC, NULL, 0);

    printf("bufferIndexConsumer connected\n");

    //it'll start at 0
    *bufferIndexConsumer = 0;


    /* Calling sem_init */
    pthread_mutex_init(&globalBuffer->bufferMutex, NULL);

    //sem_init --> full_sem
    my_sem_init(full_sem, SIZE);  //sem_init(&full_sem, 0, SIZE);

    //sem_init --> empty_sem
    my_sem_init(empty_sem, 0);    //sem_init(&empty_sem, 0, 0);


    /* Get the Command Line Arguments
     * use atoi to read the STRING into an INTEGER */

    //get the number of processes
    int inputProcess = atoi(argv[1]);

    //for the each input process get a random number of jobs
    while (i < inputProcess) {

        pid_t pidProducer = fork();
        //book keepint parameter to pass into producer
        int pidProcess = getpid();

          if (pidProducer == 0) {

            //get a random amout of jobs for this process (1 - 25)
            srand(time(NULL) ^ getpid());
            int processJobs = (rand() % (UPPERJOBS - LOWERJOBS + 1)) + LOWERJOBS;
            printf("Procucer %d will have %d many jobs to do\n", pidProcess, processJobs);

              //send to producer
              producer(pidProcess, processJobs);

              exit(0);
           }

           else {

            waitpid();
          }

	  i++;
    
    }

   //get the number of threads
   int inputThreads = atoi(argv[2]);

   pthread_t thread[inputThreads];
   int thread_numb[inputThreads];

    //create inputThreads many threads
    for (j = 0; j < inputThreads; j++) {

      thread_numb[j] = j;

       // playing a bit with thread and thread_numb pointers...
       pthread_create(&thread[j], // pthread_t *t
                       NULL, // const pthread_attr_t *attr
                       consumer, // void *(*start_routine) (void *)
                       &thread_numb[j]);  // void *arg
    }

    for (j = 0; j < inputThreads; j++) {

        pthread_join(thread[j], NULL);
    }

    return 0;
}

                                                              