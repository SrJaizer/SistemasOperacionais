#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
faz o mesmo que o 01multiprocessorFatorial, mas com 2 fihos
*/

int fFatorial, sFatorial;
//int main(int argc, char *argv[])
int main(){
    int num;
    pid_t childpid;
    pid_t parentpid = getpid();
    int pip[2];
    int *fF = &fFatorial, *sF = &sFatorial;
    pipe(pip);

    printf ("Enter the number: ");
    scanf ("%d", &num );
    //int num = atoi(argv[1]);
    int mid = num/2;

    for (int i = 1; i <= 2; i++){
        if (childpid = fork())
            break;
    }
        printf("Cheguei!");

    if (childpid > 0){
        wait(NULL);
        read(pip[0], fF, 4);
        read(pip[0], sF, 4);

        int Fat = fFatorial * sFatorial;
        printf("%d", Fat);

    }else if (getpid() - parentpid == 1){
        fFatorial = num;
        for (int n = num-1; n > mid; n--)
            fFatorial = fFatorial * n;
        write(pip[1], fF, 4);
        return 0;
        
    }else if (getpid() - parentpid == 2){
        sFatorial = mid;
        for (int n = mid-1; n > 0; n--)
            sFatorial = sFatorial * n;
        write(pip[1], sF, 4);
        printf("Cheguei46!");
        return 0;
    }

}