#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc, char const *argv[])
{

	if (argc < 2)
	{
		printf("Erreur : Nombre d'arguments insuffisant \n");
		printf("Usage : %s nomfichier\n", argv[0]);

		return 0;
	}

	// declarer un descripteur et appeler open 

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		perror("Erreur d'ouverture en lecture seule");
	}
	else {
		printf("Ouversture en lecture seule OK\n");
	}

	close(fd);

	fd = open(argv[1], O_WRONLY);

	if (fd == -1)
	{
		perror("Erreur d'ouverture en ecriture seule");
	}
	else {
		printf("Ouversture en ecriture seule OK\n");
	}

	close(fd);


	fd = open(argv[1], O_RDWR);

	if (fd == -1)
	{
		perror("Erreur d'ouverture en lecture-ecriture");
	}
	else {
		printf("Ouverture en lecture-ecriture OK\n");
	}

	close(fd);




	return 0;
}