#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int compteurPrincipal=0, compteurSecondaire=0, compteurTertiaire=0;
int i=0;

void *fthreadsecondaire(void * arg)
{

	while(1)
		printf("%d %10d %10d %10d\n",++i , compteurPrincipal, compteurSecondaire++, compteurTertiaire);
	pthread_exit(NULL);
}


void *fthreadtertiaire(void * arg)
{
	exit(0);

	while(1)
		printf("%d %10d %10d %10d\n",++i , compteurPrincipal, compteurSecondaire, compteurTertiaire++);
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t th1, th2;
	int resultat;

	resultat = pthread_create(&th1, NULL,fthreadsecondaire, (void *)NULL );
	if (resultat == -1)
	{
		perror("Erreur de lancement du thread secondaire ");
		return 0;
	}

	resultat = pthread_create(&th2, NULL,fthreadtertiaire, (void *)NULL );
	if (resultat == -1)
	{
		perror("Erreur de lancement du thread secondaire ");
		return 0;
	}

	//while(compteurPrincipal < 10000)
		while(1)
		printf("%d %10d %10d %10d\n",++i , compteurPrincipal++, compteurSecondaire, compteurTertiaire);
	
	pthread_join(th1, NULL);

	return 0;
}