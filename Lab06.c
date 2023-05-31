#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>

// Variaveis globais
#define N  10

sem_t slotCheio, slotVazio;//condicao
sem_t exclusaoMutua;//exclusao mutua
int Buffer[N];

void Insere (int item) {
static int in = 0;
//aguarda slot vazio
sem_wait(&slotVazio);
//exclusao mutua entre produtores
sem_wait(&exclusaoMutua);
Buffer[in] = item;
printf("Produtor está inserindo o item %d no buffer[%d]\n", item, in);
in = (in + 1) % N;
sem_post(&exclusaoMutua);
//sinaliza um slot cheio
sem_post(&slotCheio);
}

int Retira (void) {
    int item;
    static int out = 0;

    sem_wait(&slotCheio);

    sem_wait(&exclusaoMutua);
    item = Buffer[out];
    printf("Consumidor está removendo o item %d do buffer[%d]\n", item, out);
    out = (out + 1) % N;
    sem_post(&exclusaoMutua);

    sem_post(&slotVazio);
    return item;
}

void *produtor(void * arg) {
    int elemento;
    while(1) { 
    //produz um elemento....
    Insere(elemento);
    }
    pthread_exit(NULL);
}

void *consumidor(void * arg) {
    int elemento;
    while(1) {
    elemento = Retira();
    //consome o elemento....
    }
    pthread_exit(elemento);
}

int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[1];

  //Inicilaiza o semaforo  
  sem_init(&exclusaoMutua, 0, 1);  
  sem_init(&slotCheio, 0, 0);
  sem_init(&slotVazio, 0, N);
  
  /* Cria as threads */
  pthread_create(&threads[0], NULL, produtor, NULL);  
  pthread_create(&threads[1], NULL, consumidor, NULL);
    

  /* Espera todas as threads completarem */
  for (i = 0; i < 2; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  sem_destroy(&exclusaoMutua);  
  sem_destroy(&slotVazio);  
  sem_destroy(&slotCheio);
}
