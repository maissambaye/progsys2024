#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	pid_t pidfils;
	//pidfils = fork();
	int profondeur = 0;
	int nbFils;

	for (nbFils = 0; nbFils < 2; )
	{
		pidfils = fork();

		switch(pidfils)
		{
			case -1 : perror("Erreur de creation du processus"); break;
			case 0 : 
				printf("%d   ->  %d ; \n", getppid(), getpid());
				profondeur++;
				if (profondeur > 5)
				{
					return 0;
				}
				
				nbFils = 0;
				break;
				
			default :
				wait(NULL);
				++nbFils;
				if ( nbFils  >= 2)
				{
					return 0;
				}
		}
	}

	return 0;
}