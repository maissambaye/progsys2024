#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[], char  *arge[])
{

	char *argvbis[] = {
		"ls",
		"-l",
		"-a",
		(char *) NULL
	};

	printf("Nouvelle commande ls \n");
	//execlp("ls", "ls", "-l", "-a", (char *) 0);
	execvp("ls",argvbis);
	//execve("/bin/ls", argvbis, arge);
	perror("Erreur d'execution de exec \n");

	return 0;
}