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
  int i, val_retour, strategy;
  printf("inserer 1 si decimale, 2 si hexadecimale ou 3 si octale: ");
  scanf("%d", &strategy);
  pthread_t thread1, thread2, thread3;
  srand(time(NULL));
  i = 1 + rand() % 100;
  if(strategy == 1){
    int succes1 = pthread_create(&thread1, NULL, lire_entier, (void *) i);
    if (succes1 != 0) {
      fprintf(stderr, "Erreur de creation du thread1 ...");
      exit(0);
    }//fin if (succes != 0)
    pthread_join(thread1, (void *)&val_retour);
    printf("Vous avez lu une valeur entiere egale a %d en decimale \n", val_retour);
  }

  if(strategy == 2){
    int succes2 = pthread_create(&thread2, NULL, lire_entier, (void *) i);
    if (succes2 != 0) {
      fprintf(stderr, "Erreur de creation du thread2 ...");
      exit(0);
    }//fin if (succes != 0)
    pthread_join(thread2, (void *)&val_retour); 
    printf("Vous avez lu une valeur entiere egale a %x en hexadecimale \n", val_retour);
  }

  if(strategy == 3){
    int succes3 = pthread_create(&thread3, NULL, lire_entier, (void *) i);
    if (succes3 != 0) {
      fprintf(stderr, "Erreur de creation du thread3 ...");
      exit(0);
    }//fin if (succes != 0)
    pthread_join(thread3, (void *)&val_retour);
    printf("Vous avez lu une valeur entiere egale a %o en octale \n", val_retour);
  } 
  return 0;
}//fin main()
