#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 12 //100
#define TOTAL_TRANSFERS 100
#define TRANSFER_TIME 1

struct c {
  char *name;
  int saldo;
};
typedef struct c conta;

struct tf {
  conta *from;
  conta *to;
  int transferNum;
};
typedef struct tf transferInfo;

pthread_mutex_t mutexTransfer;
sem_t condTransferFromSAccount;
sem_t condTransferFromFAccount;

conta fAccount, sAccount;
int valor;

// The child thread will execute this function
int transfer(transferInfo *arg) {
  printf("(%d)Transferindo 10 para a conta %s...\n", arg->transferNum,
         arg->to->name);
  pthread_mutex_lock(&mutexTransfer);
  sleep(TRANSFER_TIME);
  while (arg->from->saldo < valor) {
    printf("\n(%d)Waiting income money in %s...\n", arg->transferNum,
           arg->from->name);
    pthread_mutex_unlock(&mutexTransfer);
    if ((arg->from) == &fAccount) {
      sem_wait(&condTransferFromFAccount);
    } else {
      sem_wait(&condTransferFromSAccount);
    }
    pthread_mutex_lock(&mutexTransfer);
  }
  arg->from->saldo -= valor;
  arg->to->saldo += valor;

  printf("\n(%d)Transferência concluída com sucesso!\n", arg->transferNum);
  printf("Saldo de c1: %d\n", fAccount.saldo);
  printf("Saldo de c2: %d\n", sAccount.saldo);
  // pthread_cond_signal(&condTransfer);

  if ((arg->to) == &sAccount && sAccount.saldo == valor) {
    sem_post(&condTransferFromSAccount);
  } else if ((arg->to) == &fAccount && fAccount.saldo == valor) {
    sem_post(&condTransferFromFAccount);
  }

  pthread_mutex_unlock(&mutexTransfer);

  free(arg);
  return 0;
}

int main() {
  pthread_t th[TOTAL_TRANSFERS];
  pthread_mutex_init(&mutexTransfer, NULL);
  sem_init(&condTransferFromSAccount, 0, 0);
  sem_init(&condTransferFromFAccount, 0, 0);
  // todas as contas começam com saldo 100
  fAccount.name = "c1";
  fAccount.saldo = 100;
  sAccount.name = "c2";
  sAccount.saldo = 100;

  int i;
  int j;
  valor = 10;

  for (i = 0; i < TOTAL_TRANSFERS; i++) {
    transferInfo *args = malloc(sizeof(transferInfo));

    j = i % 2;
    if (j == 1) { // if(i <= 10) //if(j == 1)
      args->from = &fAccount;
      args->to = &sAccount;
    } else {
      args->from = &sAccount;
      args->to = &fAccount;
    }
    args->transferNum = i;
    if (pthread_create(&th[i], NULL, (void *)&transfer, (void *)args) != 0) {
      // perror("Failed to Create Thread!");
      printf("(%d)Failed to Create Thread!\n", i);
    }
  }

  for (i = 0; i < TOTAL_TRANSFERS; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      perror("Failed to terminate Thread!");
    }
  }

  pthread_mutex_destroy(&mutexTransfer);
  sem_destroy(&condTransferFromSAccount);
  sem_destroy(&condTransferFromFAccount);
  printf("\nTransferências concluídas e memória liberada.\n");
  return 0;
}

//  visualizar execucao no replit:
//  https://replit.com/@SrJaizer/transacaoBancaria2#main.c
