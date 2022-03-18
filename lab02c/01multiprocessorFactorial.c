#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

long int fFatorial, sFatorial;

int main(){
    int num;
    pid_t childpid;
    //pid_t parentpid = getpid();
    int pip[2];
    long int *fF = &fFatorial;
    pipe(pip);

    printf ("Enter the number: ");
    scanf ("%d", &num );

    int mid = num/2;

    for (int i = 1; i <= 1; i++){
        if (childpid = fork())
            break;
    }
        //printf("Cheguei!");

    if (childpid > 0){
        wait(NULL);
        sFatorial = mid;
        for (int n = mid-1; n > 0; n--)
            sFatorial = sFatorial * n;
        read(pip[0], fF, 4);

        printf("\n%d!/%d! = %li",num, mid, *fF);
        printf("\n%d! = %li",mid, sFatorial);

        long int Fat = fFatorial * sFatorial;
        printf("\n%d! = %li", num, Fat);
        return 0;

    }else if (childpid == 0){
        fFatorial = num;
        for (int n = num-1; n > mid; n--)
            fFatorial = fFatorial * n;
        write(pip[1], fF, 4);
        return 0;
    }

}