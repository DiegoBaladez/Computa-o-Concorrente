#include <stdio.h>
#include <pthread.h>

//global
int threadNumber = 2;

int arrayLimit = 10000;
long bigArray [10000]; 

void *doubleNumbers(void *thread_id)
{  
    long position = (long) thread_id;
    if(position % 2 == 0)
    {
        bigArray[position] = bigArray[position] * 2;        
    }else
    {
        bigArray[position] = bigArray[position] * 2;        
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
  pthread_t thread1,thread2;
  int verifyArray;

  fillArray();

  //thread 1  
  for (long i = 0; i < arrayLimit; i += 2) {
    pthread_create(&thread1, NULL, doubleNumbers , (void *) i);
  }
  //thread 2  
  for (long i = 1; i < arrayLimit; i += 2) {
    pthread_create(&thread2, NULL, doubleNumbers , (void *) i);
  }  
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  verifyArray = testIfAllNumbersAreDividedByTwo();

  printf("\n\n");
  printf("Should be zero: %d \n", verifyArray); 
  printf("\n\n");

  return 0;
}