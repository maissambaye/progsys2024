#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("Erreur : nombre d'arguments insuffisant \n");
		printf("Usage : %s ADRESSE_IP PORT \n", argv[0]);
		return 0;
	}

	// 1. Creation d'une socket 

	int socketClient = socket(AF_INET, SOCK_STREAM, 0);
	if (socketClient == -1)
	{
		perror("Erreur de creation de la socket");
		return 0;
	}

	//2. Preparation de la structure vers le serveur 
	struct sockaddr_in addrServer;
	memset(&addrServer, 0, sizeof(struct sockaddr_in));
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(atoi(argv[2]));
	addrServer.sin_addr.s_addr = inet_addr(argv[1]);

	// 3. Connect 
	int resultat = connect(socketClient, (struct sockaddr *) &addrServer, 
							sizeof(struct sockaddr_in));
	if (resultat == -1)	{
		perror("Erreur d'ouverture de la connexion "); return 0;
	}
	//4. Logique de l'application 

	char buffReceive[10];
	char buffSend[]="Pong";
	int nbreceive=0;
	int i=0;
	while(1)
	{
		memset(buffReceive,0 , 10*sizeof(char));
		nbreceive = recv(socketClient, buffRecei

			ve, 10*sizeof(char), 0);
		if (nbreceive > 0)
			{
				printf("[#Client# %d] Client > Serveur : %s\n", i, buffReceive);
			}
		sleep(1);
		send(socketClient, buffSend, strlen(buffSend), 0);
		printf("[#Client# %d] Serveur > client : %s\n", i, buffSend);
		i++;
	}

	close(socketClient);

	return 0;
}