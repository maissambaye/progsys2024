#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

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

	
	socketClientTCP = accept(socketServeurTCP, 
			(struct sockaddr *) &addrClient,
			 &taille);
		printf("Connexion acceptée pour le client %s:%d\n", 
			inet_ntoa(addrClient.sin_addr), 
							ntohs(addrClient.sin_port) );

	char buffSend[255]="OK";
	char buffReceive[255];
	
	struct infofile informations_fichier;

	int nbrecv = recv(socketClientTCP, &informations_fichier, 
						sizeof(struct infofile), 0);

	if (nbrecv <= 0)
	{
		strcpy(buffSend, "NOK");
	}

	printf("Creation du fichier %s : \ntaille : %d \nmode : %o \n",
			informations_fichier.nomfichier,
		 	informations_fichier.taille,
		 	informations_fichier.mode);
	// creation du fichier 

	int fd = open(informations_fichier.nomfichier, 
			O_WRONLY | O_CREAT | O_EXCL, 
			informations_fichier.mode);

	if (fd == -1)
	{
		strcpy(buffSend, "NOK");
	}

	send(socketClientTCP, buffSend, strlen(buffSend), 0);

	int nbwrite = 0;

	struct block_data bdata;

	do{
		memset(&bdata, 0, sizeof(struct block_data));
		nbrecv = recv(socketClientTCP, &bdata, sizeof(struct block_data),0);
		if ( (bdata.taille > 0) && (nbrecv > 0) )
		{
			write(fd,bdata.data, bdata.taille* sizeof(char));
		}

	}while (bdata.taille > 0);
	
	printf("Fichier bien recu\n");

	close(socketClientTCP);
	close(fd);
	return 0;
}