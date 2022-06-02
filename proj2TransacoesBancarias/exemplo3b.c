#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//race conditions
int calls = 0;
pthread_mutex_t varMutex;

void sendCall(){
  for (int i = 0; i < 10000000; i++){
    pthread_mutex_lock(&varMutex);
    calls++;
    //protecting set of intructions from "calls++"
    //against other threads running
    //"calls++" assembly intructions:
    // -read var "calls"
    // -increment in CPU
    // -write new value in var "calls"
    //until terminate
    pthread_mutex_unlock(&varMutex);
  }
}

int main(void){
  pthread_t p[2];
  pthread_mutex_init(&varMutex, NULL);

  for (int i = 0; i < 2; i++){
    if (pthread_create(&p[i], NULL, (void*)&sendCall, NULL) != 0){
      perror("Failed to create a thread!");
    }
  }

  for (int i = 0; i < 2; i++){
    if (pthread_join(p[i], NULL) != 0){
      perror("Failed to terminate a thread!");
    }
  }
  pthread_mutex_destroy(&varMutex);
  printf("%d \n", calls);
}
