/*
LAb 05 - Diego Baladez

Qual o objetivo do programa?
Serao 5 threads
• A thread 1 imprime a frase “Oi Maria!”
• A thread 2 imprime a frase “Oi Jose!”  ́
• A thread 3 imprime a frase “Sente-se por favor.”
• A thread 4 imprime a frase “Ate mais Jos  ́ e!”  ́
• A thread 5 imprime a frase “Ate mais Maria!”

Regra 1 - as threads 1 e 2 nao importam a ordem mas devem imprimir
antes da 3. 
Regra 2 - as threads 4 e 5 nao importam a ordem mas devem sempre imprimir
depois da thread 3.

A ideia eh. Fazer com que as threads 1 e 2 imprimam livremente
e incrementem uma variavel de condicao para poder liberar a thread 3

depois que a thread 3 eh liberada. a thread 3 deve liberar as threads
4 e 5 para serem executadas. aqui devera haver outra variave de condicao.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  5

int liberarThread3 = 0;
int liberarThread4e5 = 0;

pthread_mutex_t x_mutex;
pthread_cond_t liberarThread3_cond;
pthread_cond_t liberarThread4e5_cond;

void *thread01 (void *t)
{
  printf("Oi Maria!\n");

  pthread_mutex_lock(&x_mutex);
  liberarThread3++;

  if (liberarThread3 == 2)
  {    
    pthread_cond_signal(&liberarThread3_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void *thread02 (void *t)
{
  printf("Oi Jose!\n");

  pthread_mutex_lock(&x_mutex);
  liberarThread3++;
  
  if (liberarThread3 == 2)
  {    
    pthread_cond_signal(&liberarThread3_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void *thread03 (void *t)
{
  pthread_mutex_lock(&x_mutex);
  
  if (liberarThread3 < 2)
  {      
    pthread_cond_wait(&liberarThread3_cond, &x_mutex); 
  }
    
  printf("Sente-se por favor.\n");
  liberarThread4e5++;  
  if(liberarThread4e5 > 0)
  {
    pthread_cond_broadcast(&liberarThread4e5_cond);
  }
    
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

void *thread04 (void *t)
{
  pthread_mutex_lock(&x_mutex);
  if (liberarThread4e5 == 0)
  { 
    pthread_cond_wait(&liberarThread4e5_cond, &x_mutex);     
  }
  printf("Ate mais Jose\n");
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

void *thread05 (void *t)
{
  pthread_mutex_lock(&x_mutex);
  if (liberarThread4e5 == 0)
  { 
    pthread_cond_wait(&liberarThread4e5_cond, &x_mutex);     
  }
  printf("Ate mais Maria\n");
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&liberarThread4e5_cond, NULL);
  pthread_cond_init (&liberarThread3_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, thread01, NULL);
  pthread_create(&threads[1], NULL, thread02, NULL);
  pthread_create(&threads[2], NULL, thread03, NULL);
  pthread_create(&threads[3], NULL, thread04, NULL);
  pthread_create(&threads[4], NULL, thread05, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&liberarThread4e5_cond);
  pthread_cond_destroy(&liberarThread3_cond);
}