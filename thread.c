/******************************************
 *
 *  Title:  Simple C Threads Implementation
 *  Author: zMrDevJ
 *  Date: 12/21/2017
 *
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/* Declare mutex lock */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Shared variable */
int shared = 0;

/* Thread 1 */
void tRun1(){

	for(int i = 0; i < 30; i++){
		/* Wait for random number between 1 and 3 */
		int r = rand()%3+1;
		sleep(r);

		/* Critical section */
		pthread_mutex_lock(&mutex);

		shared--;
		printf("Th1: %d\n", shared);

		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

/* Thread 2 */
void tRun2(){
	
	for(int i = 0; i < 30; i++){
		/* Wait for random numer between 1 and 3 */
		int r = rand()%3+1;
		sleep(r);

		/* Critical section */
		pthread_mutex_lock(&mutex);

		shared++;
		printf("\t\tTh2: %d\n", shared);

		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

/* Main */
int main(int argc, char const *argv[])
{
	/* Number of threads */
	int n = 2;

	/* Say to kernel the number of threads we're going to create */
	pthread_setconcurrency(2);

	/* Generate a random seed */
	srand(time(NULL));

	/* Inizialize mutex lock */
	pthread_mutex_init(&mutex, NULL);

	/* Create an array of n threads */
	pthread_t t[n];

	/* Run the threads */
	if(pthread_create(&t[0], NULL, (void *) tRun1, NULL) != 0){
		perror("pthread_create");
		exit(-1);
	}
	if(pthread_create(&t[1], NULL, (void *) tRun2, NULL) != 0){
		perror("pthread_create");
		exit(-1);
	}

	/* Main process wait for threads' ends */
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);

	return 0;
}
