#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>



char ** buildargv(char * cmd);
void executer(char *argv[]);

int main(int argc, char const *argv[])
{
	char cmd[255];
	char **argvbis;
	do{
		printf("Minishell:~$ > ");
		gets(cmd);
		argvbis = buildargv(cmd);
		executer(argvbis);
	}while(strcmp(cmd,"quit") != 0);

	return 0;
}


char ** buildargv(char * cmd)
{
	char **argvbis = malloc(255 * sizeof(char *));
	int i ;
	for (i = 0; i < 255; ++i)
	{
		argvbis[i] = NULL;
	}

	char *cmdbuff =malloc(255 * sizeof(char));;
	strcpy(cmdbuff, cmd);

	i = 0;
	argvbis[i] = strtok(cmdbuff, " ");
	while((argvbis[i] != NULL) && (i < 255))
	{
		i++;
		argvbis[i] = strtok(NULL, " ");
	}

	return argvbis;
}



void executer(char *argv[])
{
	pid_t pifils = fork();
	switch(pifils)
	{
		case -1:  perror("Erreur de creation du processus "); break;
		case 0 :
			execvp(argv[0], argv);
			perror("Erreur d'execution de exec");
			break;
		default :
			wait(NULL);
	}
}