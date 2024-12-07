#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	pid_t pidfils;
	//pidfils = fork();
	for (int i = 0; i < 10; ++i)
	{
		pidfils = fork();

		switch(pidfils)
		{
			case -1 : perror("Erreur de creation du processus"); break;
			case 0 : 
				printf("%d   ->  %d ; \n", getppid(), getpid());
					
				return 0 ;
			default :
				
				wait(NULL);
				
		}
	}

	return 0;
}