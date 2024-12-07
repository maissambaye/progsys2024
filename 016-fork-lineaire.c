#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	pid_t pidfils, pidfils2, pidfils3;
	
	pidfils = fork();
	switch(pidfils)
	{
		case -1 : perror("Erreur de creation du processus"); break;
		case 0 : 
			printf("%d   ->  %d ; \n", getppid(), getpid());			
			break;
		default :
			//printf("Processus pere : PID %d : PID_FILS %d \n", getpid(), pidfils );
			wait(NULL);
	}
	pidfils2 = fork();
	switch(pidfils2)
	{
		case -1 : perror("Erreur de creation du processus"); break;
		case 0 : 
			printf("%d   ->  %d ; \n", getppid(), getpid());			
			break;
		default :
			//printf("Processus pere : PID %d : PID_FILS %d \n", getpid(), pidfils );
			wait(NULL);
	}
	pidfils3 = fork();
	switch(pidfils3)
	{
		case -1 : perror("Erreur de creation du processus"); break;
		case 0 : 
			printf("%d   ->  %d ; \n", getppid(), getpid());			
			break;
		default :
			//printf("Processus pere : PID %d : PID_FILS %d \n", getpid(), pidfils );
			wait(NULL);
	}
	pidfils3 = fork();
	switch(pidfils3)
	{
		case -1 : perror("Erreur de creation du processus"); break;
		case 0 : 
			printf("%d   ->  %d ; \n", getppid(), getpid());			
			break;
		default :
			//printf("Processus pere : PID %d : PID_FILS %d \n", getpid(), pidfils );
			wait(NULL);
	}

	return 0;
}