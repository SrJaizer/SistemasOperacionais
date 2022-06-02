#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//race conditions
int calls = 0;

void sendCall(){
  for (int i = 0; i < 10000000; i++){
    calls++;
  }
}

int main(void){
  pthread_t p[2];

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
  printf("%d \n", calls);
}
