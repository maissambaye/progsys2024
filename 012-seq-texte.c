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
		printf("Usage : %s nombre nomfichier \n", argv[0] );
		return 0;
	}

	int nmax = atoi(argv[1]);

	int fd = open(argv[2], O_WRONLY | O_CREAT , 
						   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier ");
		return 0;
	}

	// AJouter les données dans le fichier 

	int nbWrite = 0;
	char textBuff[255]; // buffer de texte 

	for (int i = 1; i <= nmax; ++i)
	{
		// construction d'une chaine à partir des variables 
		sprintf(textBuff, "%d ", i);

		// ecriture de la chaine de caractère 
		nbWrite = write(fd, textBuff, strlen(textBuff));

		if (nbWrite <= 0)
		{
			perror ("Erreur d'ecriture");
			return 0;
		}
	}

	close(fd);
	return 0;
}