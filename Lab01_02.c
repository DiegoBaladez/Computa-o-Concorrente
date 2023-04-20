#include <stdio.h>
#include <pthread.h>

//global
int arrayLimit = 10000;
long bigArray [10000];
int nThreads = 2; 

void *doubleNumbers(void *thread_id)
{     
    for(long i = (long) thread_id; i < arrayLimit; i += nThreads)
    {
      bigArray[i] = bigArray[i] * 2;
      //printf("thread %ld posArray %ld valor %ld\n", (long) thread_id, i, bigArray[i]);
    }    
    pthread_exit(NULL);    
}

long testIfAllNumbersAreDividedByTwo()
{
  for(int i = 0; i < arrayLimit; i++)
  {
    if( bigArray[i] % 2 != 0 ) return bigArray[i];
  }
  return 0;
}

void fillArray()
{
  //fill the array
  for(int i = 0; i < arrayLimit; i++)
  {
    bigArray[i] = i;
  }
}

int main()
{
  pthread_t threadsArray[nThreads];
  int verifyArray;

  fillArray();

  //threads  
  for (long i = 0; i < nThreads; i++)
  {    
    if(pthread_create(&threadsArray[i], NULL, doubleNumbers , (void *) i))
    {
      printf("thread %ld fail", i); return 2;   
    }
      
  }    
  
  for(int i = 0; i < nThreads; i++){
    if(pthread_join(threadsArray[i], NULL)) printf("pthread_join error"); return 3;
  }
  
  verifyArray = testIfAllNumbersAreDividedByTwo();

 /*  for(int i = 0; i < arrayLimit; i++){
    printf("Posicao %d e valor %d \n", i, bigArray[i]);
  } */

  printf("\n\n");
  printf("Should be zero: %d \n", verifyArray); 
  printf("\n\n");

  return 0;
}
