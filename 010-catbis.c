#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		printf("Erreur : Nombre d'arguments insuffisant \n");
		printf("Usage : %s nomfichier \n", argv[0] );
		return 0;
	}

	// L'ouverture 

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		perror("Erreur d'ouverture ");
		return 0;
	}

	// le parcours du fichier et son affichage 

	char buff; // Buffer de lecture 
	int nbRead = 0;

	do{
		nbRead = read(fd, &buff, sizeof(char));
		if (nbRead > 0)
		{
			printf("%c", buff );
		}

	} while( nbRead > 0);

	close(fd);

	return 0;
}