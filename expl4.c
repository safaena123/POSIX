#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include "sommeh.h"

#define ROWS 20 /*10000*/
#define COLS 20 /*10000*/


/* Matrix pointer: it will be dynamically allocated */
long *bigMatrix;
/* Thread routine : make the summation of all the elements of the assigned matrix rows */

int main (int argc, char *args[]) {
	clock_t start = clock();
	/* Array of thread identifiers */
	int i,j,nThreads;
	/* Get the number of threads from command parameters */
	if (argc != 2) {
	  printf("Usage: %s <numThreads>\n",args[0]);
	  exit (0);
	}//fin if
	sscanf(args[1],"%d",&nThreads);
	/* Allocate the matrix M */
	bigMatrix = malloc(ROWS*COLS*sizeof(long));
	/* Fill the matrix with some values */
	for (i=0;i<ROWS;i++)
	  for (j=0;j<COLS;j++)
		 bigMatrix[i*COLS+j]=i+COLS*j;

	/* Somme de matrice*/
	Somme(nThreads);

	printf(" ***** Total time used %f *****\n ",(double) clock()-start);
	pthread_exit(NULL);
}//fin main
