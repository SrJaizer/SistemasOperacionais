#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 5;

int main()
{
  	int  pip[2];
 	int *valueP = &value;
	pipe(pip);

	pid_t pid;

	pid = fork();

	if (pid == 0) { /* child process */
		printf("Entrei no filho!\n");
		value += 15;
    	write(pip[1], valueP, 4);
		printf ("CHILD: value = %d\n",value); /* LINE A */
		return 0;
	}
	else if (pid > 0) { /* parent process */
		wait(NULL);
    	read(pip[0], valueP, 4);
		printf ("PARENT: value = %d\n",value); /* LINE A */
		return 0;
	}
}
