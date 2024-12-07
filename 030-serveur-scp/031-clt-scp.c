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
	if (argc < 4)
	{
		printf("Erreur : nombre d'arguments insuffisant \n");
		printf("Usage : %s ADRESSE_IP PORT FICHIER \n", argv[0]);
		return 0;
	}

	// connexion au serveur 
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

	//4. Copie 
	// 4.1 Recuperer les informations du fichier

	struct stat stfile;
	stat(argv[3], &stfile);

	// Envoyer l'information et attendre OK ou NOK 
	struct infofile info;

	info.taille = stfile.st_size;
	info.mode = stfile.st_mode;
	strcpy(info.nomfichier, argv[3]);

	int nbsend = send(socketClient, &info, sizeof(struct infofile), 0);
	if (nbsend <= 0 )
	{
		perror ("Erreur d'envoi des données du fichier ");
		return 0;
	}

	char buffRecv[255];
	memset(buffRecv, 0, 255 * sizeof(char));
	recv(socketClient, buffRecv, 255 * sizeof(char), 0);

	printf("Reponse du serveur %s\n", buffRecv);

	if (strcmp(buffRecv, "OK") != 0)
	{
		perror ("Erreur de creation du fichier distance ");
		return 0;
	}


	// l'envoie des données 

	int fd = open(argv[3], O_RDONLY);
	if (fd == -1)
	{
		perror ("Erreur d'ouverture du fichier à distance");
		return 0;
	}

	int nbread = 0;

	struct block_data bdata;

	do{

		nbread = read(fd, bdata.data, 4096 * sizeof(char));
		if (nbread > 0)
		{
			bdata.taille = nbread;


		}else if(nbread == 0)
			{
				bdata.taille = 0;
			}
			else
				bdata.taille = -1;
		send(socketClient, &bdata, sizeof(struct block_data), 0);

	}while(nbread > 0);


	close(socketClient);
	return 0;
}