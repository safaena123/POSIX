#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
//interface strategie
typedef void* (*converterStrategie)(void *arg);
//fin


//La fonction du thread
void* lire_entier(void *arg) {
  int un_entier;
  int val_arg = (int) arg;
  printf("Bienvenue chez le thread ayant comme argument %d\n", val_arg);
  printf("Priere de saisir un entier:");
  scanf("%d", &un_entier);
  pthread_exit((void *) un_entier); 
}//fin lire_entier


//les fonctions de display
void* octal(void *arg) {
  int val_arg = (int) arg;
  printf("en octal : %o\n", val_arg);
  pthread_exit((void *) arg); 
}
void* hexa(void *arg) {
  int val_arg = (int) arg;
  printf("en hexa : %x\n", val_arg);
  pthread_exit((void *) arg); 
}
void* decimal(void *arg) {
  int val_arg = (int) arg;
  printf("en decimal : %d\n", val_arg);
  pthread_exit((void *) arg); 
}//fin


//array of all the strategies 
converterStrategie algorithms[] = {octal, hexa, decimal};
size_t algoSize = sizeof(algorithms)/sizeof(algorithms[0]);
//fin


int main(void) {
  int i, val_retour, success2,t;
  pthread_t thread1;
  pthread_t thread2;
  clock_t start = clock();
  srand(time(NULL));
  i = 1 + rand() % 100;
  int succes1 = pthread_create(&thread1, NULL, lire_entier, (void *) i);
  if (succes1 != 0) {
    fprintf(stderr, "Erreur de creation du thread ...");
    exit(0);
  }//fin if (succes != 0)

  //Attente du thread de lecture
  pthread_join(thread1, (void *)&val_retour);
  

  //go through all the algos and execute them
  for (t = 0 ; t<algoSize ; t++ ){
  	clock_t threadTime = clock();
  	success2 = pthread_create(&thread2, NULL , algorithms[t] , val_retour);
  	if (success2 != 0) {
    fprintf(stderr, "Erreur de creation du thread ...");
    exit(0);
 	 	}//fin if (succes != 0)
    pthread_join(thread2, (void *)&val_retour); 
    printf("Time used : %f\n",clock()-threadTime);
   }
   printf("Total time used %f\n",clock()-start);
  //end
  return 0;
}//fin main()
