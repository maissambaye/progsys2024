#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("Erreur : Nombre d'arguments insuffisant \n");
		printf("Usage : %s source destination \n", argv[0] );
		return 0;
	}

	// ouverture du fichier source 
	int fdSrc = open(argv[1], O_RDONLY);

	if (fdSrc ==-1)
	{
		perror("Erreur d'ouverture du fichier source");
		return 0;
	}

	printf("Ouverture du fichier %s avec succès\n", argv[1]);

	// recuperation des informations du fichier source : mode, taille 

	// int fstat(int fd, struct stat *statbuf);

	struct stat stFichierSrc;
	int resultat = fstat(fdSrc, &stFichierSrc);
	if (resultat == -1)
	{
		perror("Erreur de recuperation des informations sur le fichier source");
		return 0;
	}

	printf("Taille %ld\n",  stFichierSrc.st_size);
	printf("Permissions:  %o\n",  stFichierSrc.st_mode);

	// creation du fichier de destination 

	 int fdDst = open(argv[2], O_WRONLY | O_CREAT , stFichierSrc.st_mode);

	 if (fdDst ==-1)
	{
		perror("Erreur d'ouverture du fichier de destination");
		return 0;
	}

	printf("Création du fichier %s avec succès \n", argv[2]);

	// copie des données 

	char *buff = malloc(512 * sizeof(char));
	int nbRead, nbWrite;
	int nbTotal = 0;
	do{
		// Lecture dans le fichier source 

		nbRead = read(fdSrc, buff, 512 * sizeof(char));
		//Ecriture dans le fichier de destination
		if (nbRead > 0 )
		{
			nbWrite = write(fdDst, buff, nbRead * sizeof(char));

			if (nbWrite <= 0 )
				{
					perror("Erreur d'Ecriture dans le fichier de destnation");
					return 0;
				}
			else{
				nbTotal = nbTotal + nbWrite;

				printf("\r%.4f%% ",100.0 * nbTotal /  stFichierSrc.st_size );
				for (int j = 0; j <= (nbTotal % 80); ++j)
				{
					printf("=");
				}
				printf(">");
				fflush(stdin);
			}	
		}

	}while (nbRead > 0);

	close(fdSrc);
	close(fdDst);

	return 0;
}