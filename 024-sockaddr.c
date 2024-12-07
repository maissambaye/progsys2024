#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("Erreur : nombre d'arguments insuffisant \n");
		printf("Usage : %s adresse_IP PORT \n", argv[0]);
		return 0;
	}
	

	struct sockaddr_in addrServer;
	//initialiser la structure à 0

	memset(&addrServer, 0, sizeof(struct sockaddr_in));

	addrServer.sin_family = AF_INET;
	addrServer.sin_port   = htons(atoi(argv[2])); 
	addrServer.sin_addr.s_addr = inet_addr(argv[1]);

	printf("Adresse IP : %s :  %X\n", inet_ntoa(addrServer.sin_addr), 
		ntohl(addrServer.sin_addr.s_addr));
	printf("Numero de port %d   : %d \n", ntohs(addrServer.sin_port), 
		addrServer.sin_port);

	return 0;
}