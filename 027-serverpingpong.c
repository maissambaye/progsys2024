#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
 #include <unistd.h>

int main(int argc, char const *argv[])
{

	if (argc < 2)
	{
		printf("Erreur : nombre d'arguments insuffisant \n");
		printf("Usage : %s PORT \n", argv[0]);
		return 0;
	}
	// 1. creation de socket TCP 
	int socketServeurTCP = socket(AF_INET, SOCK_STREAM, 0);

	if (socketServeurTCP == -1)
	{
		perror("Erreur de creation de la socket TCP");
		return 0;
	}
	printf("Creation de la socket TCP avec succès \n");

	// 2. Initialisation de la structure d'adresse 

	struct sockaddr_in addrServer ;

	memset(&addrServer, 0, sizeof(struct sockaddr_in));

	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(atoi(argv[1]));
	addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");

	// 3. Appel de bind 
	int resultat = bind(socketServeurTCP, (struct sockaddr *) &addrServer, 
										sizeof(struct sockaddr_in));

	if (resultat == -1)
	{
		perror("Erreur de lancement de bind");
		return 0;
	}

	printf("Excecution de bind avec succès \n");

	resultat = listen(socketServeurTCP, 5);

	if (resultat == -1)
	{
		perror("Erreur de lancement de listen");
		return 0;
	}

	printf("Excecution de listen avec succès \n");


	// Accept 
		// Declarer la structure qui va contenir l'adresse distante
	struct sockaddr_in addrClient;
	int taille = sizeof(struct sockaddr_in);

	int socketClientTCP; 

	// buffers

	char buffSend[] = "Ping";
	char buffReceive[10];
	int i=0;
	socketClientTCP = accept(socketServeurTCP, 
			(struct sockaddr *) &addrClient,
			 &taille);
		printf("Connexion acceptée pour le client %s:%d\n", 
			inet_ntoa(addrClient.sin_addr), 
							ntohs(addrClient.sin_port) );

	while(1){
		//envoyer ping 
		send(socketClientTCP, buffSend, strlen(buffSend), 0);
		printf("[#Server# %d] (Server) %s:%d > %s:%d : %s \n",i,
				inet_ntoa(addrServer.sin_addr), ntohs(addrServer.sin_port), 
				inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), 
				buffSend );
		sleep(1);
		//recevoir pong
		memset(buffReceive, 0, 10);
		recv(socketClientTCP, buffReceive, 5 * sizeof(char), 0);
		
		printf("[#Server# %d] %s:%d > %s:%d (Server)  : %s \n",i,
				inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port),
				inet_ntoa(addrServer.sin_addr), ntohs(addrServer.sin_port), 
				buffReceive);
		i++;
	}
	close(socketClientTCP);
	return 0;
}