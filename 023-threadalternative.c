#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>


int i=0, compteur=0;
sem_t semSecondaire, semTertiaire;


void *fthreadsecondaire(void * arg)
{
	while(1){
			sem_wait(&semSecondaire);
			printf("%d %10d\n",++i , compteur++);
			sem_post(&semTertiaire);
		}
	pthread_exit(NULL);
}


void *fthreadtertiaire(void * arg)
{
	while(1){
			sem_wait(&semTertiaire);
			printf("%d %10d\n",++i , compteur--);
			sem_post(&semSecondaire);
		}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t th1, th2;

	int resultat;


	// initialisation des semaphores 

	resultat = sem_init(&semSecondaire, 0, 10);
	if (resultat == -1 )
	{
		perror("Erreur d'initilisation de la semaphore");
		return 0;
	}


	resultat = sem_init(&semTertiaire, 0, 0);
	if (resultat == -1 )
	{
		perror("Erreur d'initilisation de la semaphore");
		return 0;
	}


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

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}