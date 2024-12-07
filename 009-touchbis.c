#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	if (argc < 2 )
	{
		printf("Erreur : Nombre d'arguments insuffisant \n");
		printf("Usage : %s nomfichier \n", argv[0] );
		return 0;
	}

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL , 
					S_IRUSR | S_IWUSR |
					S_IRGRP | 
					S_IROTH
					 );

	if (fd == -1)
	{
		perror("Erreur de creation du fichier ");
		return 0;
	}

	printf("Fichier %s crée avec succès \n", argv[1] );

	close(fd);

	return 0;
}