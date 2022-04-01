#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h> // biblioteca usada para suportar acesso concorrente a zonas de memoria partilhada
#define N 5
#define PENSAR 0
#define FOME 1
#define COMER 2
#define ESQUERDA (nfilosofo+4)%N //agarrar garfo
                                 //da esquerda
#define DIREITA (nfilosofo+1)%N  //agarrar garfo
                                 //da direita
void *filosofo(void *num);
void pegargarfo(int);
void devolvergarfo(int);
void tentar(int);

sem_t mutex;
sem_t S[N]; //inicializacao do semáforo
int estado[N];
int nfilosofo[N]={0,1,2,3,4};

void *filosofo(void *num)
{
   while(1)
   {
      int *i = num;
      sleep(1);
      pegargarfo(*i);
      sleep(1);
      devolvergarfo(*i);
   }
}

void pegargarfo(int nfilosofo)
{
   sem_wait(&mutex);
   estado[nfilosofo] = FOME;
   printf("Filosofo %d tem fome.\n", nfilosofo+1);
   //+1 para imprimir filosofo 1 e nao filosofo 0
   tentar(nfilosofo);
   sem_post(&mutex);
   sem_wait(&S[nfilosofo]);
   sleep(1);
}

void devolvergarfo(int nfilosofo)
{
   sem_wait(&mutex);
   estado[nfilosofo]=PENSAR;
   printf("Filosofo %d devolveu os garfos %d e %d.\n", nfilosofo+1, ESQUERDA+1, nfilosofo+1);
   printf("Filosofo %d esta pensando.\n", nfilosofo+1);
   tentar(ESQUERDA);
   tentar(DIREITA);
   sem_post(&mutex);
}

void tentar(int nfilosofo)
{
   if(estado[nfilosofo]==FOME && estado[ESQUERDA]
 !=COMER && estado[DIREITA]!=COMER)
   {
      estado[nfilosofo]=COMER;
      sleep(2);
      printf("Filosofo %d pegou os garfos %d e %d.\n", nfilosofo+1, ESQUERDA+1, nfilosofo+1);
      printf("Filosofo %d esta comendo.\n", nfilosofo+1);
      sem_post(&S[nfilosofo]);
   }
}

int main() {
   int i;
   pthread_t thread_id[N]; //identificadores das
                           //threads
   sem_init(&mutex,0,1);
   for(i=0;i<N;i++)
      sem_init(&S[i],0,0);
   for(i=0;i<N;i++)
   {
      pthread_create(&thread_id[i], NULL, filosofo, &nfilosofo[i]);
      //criar as threads
      printf("Filosofo %d esta a pensar.\n",i+1);
   }
   for(i=0;i<N;i++)
   pthread_join(thread_id[i],NULL); //para
                                    //fazer a junção das threads
   return(0);
}
