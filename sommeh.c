#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>

#define MAX_THREADS 256
#define COLS 20
#define ROWS 20

struct argument {
  int startRow ;
  int nRows ;
  long partialSum;
} threadArgs[MAX_THREADS];

/* Matrix pointer: it will be dynamically allocated */
long *bigMatrix;

void Afficher(){
	int i, j;
	printf("Your matrix is as follows:\n");
	for (i=0;i<ROWS;i++) {
		printf("[");
		for (j=0;j<COLS;j++){
			printf("%d:",i+COLS*j);
		 }
		printf("]\n");
	}//fin for
	printf("Please hit enter to continue ...");
}

/* Thread routine : make the summation of all the elements of the assigned matrix rows */
void *thread_routine(void *arg) {
  int i,j;
  /* Type−cast passed pointer to expected structure containing the start row,the number of rows to be summed and the return sum argument */
  struct argument *currArg = (struct argument *) arg;
  long sum=0;
  for (i=0;i<currArg->nRows;i++)
    for (j=0;j<COLS;j++)
        sum +=bigMatrix[(currArg->startRow+i)*COLS+j];
  currArg->partialSum=sum ;
  return NULL ;
}//fin thread_routine()

void Somme(int nThreads){
	int i,rowsPerThread,lastThreadRows;
	pthread_t threads[MAX_THREADS];
	long totalSum ;
	rowsPerThread = ROWS/nThreads;
	if (ROWS%nThreads==0)
		lastThreadRows=rowsPerThread;
	else
		lastThreadRows=rowsPerThread+ROWS%nThreads;
		/* Prepare arguments for threads */
	for (i=0;i<nThreads;i++) {
		/* Prepare Thread arguments */
		threadArgs[i].startRow=i*rowsPerThread;
		if (i==nThreads-1)
			threadArgs[i].nRows=lastThreadRows;
		else
			threadArgs[i].nRows=rowsPerThread;
	}//fin for
	clock_t thread_c[nThreads];
	for (i=0;i<nThreads;i++){
		thread_c[i] = clock();
		pthread_create(&threads[i],NULL,thread_routine,&threadArgs[i]);
	}
		/* Display the values of the matrix */
	Afficher();
	getchar();
	/* Wait thread termination and use the corresponding sum value for the final summation */
	totalSum=0;
	for (i=0;i<nThreads;i++) {
		pthread_join(threads[i],NULL);
		printf("Thread %d just terminated with its partial sum %ld\n",i, threadArgs[i].partialSum);
		printf("***** time used for the thread %d is %lu *****\n\n ",i ,  clock()-thread_c[i]);
		totalSum +=threadArgs[i].partialSum;
	}//fin for
		/* Display the total sum calculated */
	printf("The total sum calculated by all the threads is %ld\n",totalSum);
}
