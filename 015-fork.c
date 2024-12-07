#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	pid_t pidfils;
	int compteur_pere=0, compteur_fils=0;
	pidfils = fork();

	switch(pidfils)
	{
		case -1 : perror("Erreur de creation du processus"); break;
		case 0 : 
			//printf("Processus fils : PPID %d   PID : %d\n", getppid(), getpid());
			while(1)
			{
				compteur_fils++;
				printf("%10d | %10d\n", compteur_pere, compteur_fils);
			}

			break;
		default :
			//printf("Processus pere : PID %d : PID_FILS %d \n", getpid(), pidfils );
			//wait(NULL);
		while(1)
			{
				compteur_pere++;
				printf("%10d | %10d\n", compteur_pere, compteur_fils);
			}

	}

	return 0;
}