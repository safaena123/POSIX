#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//La fonction du thread
void* lire_entier(void *arg) {
  int un_entier;
  int val_arg = (int) arg;
  printf("Bienvenue chez le thread ayant comme argument %d\n", val_arg);
  printf("Priere de saisir un entier:");
  scanf("%d", &un_entier);
  pthread_exit((void *) un_entier); 
}//fin lire_entier

int main(void) {
  int i, val_retour;
  pthread_t thread1;
  srand(time(NULL));
  i = 1 + rand() % 100;
  int succes = pthread_create(&thread1, NULL, lire_entier, (void *) i);
  if (succes != 0) {
    fprintf(stderr, "Erreur de creation du thread ...");
    exit(0);
  }//fin if (succes != 0)

  //Attente du thread de lecture
  pthread_join(thread1, (void *)&val_retour); 
  printf("Vous avez lu une valeur entiere egale a %d\n", val_retour);
  return 0;
}//fin main()
