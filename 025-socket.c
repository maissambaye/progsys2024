#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	// creation de socket TCP 
	int socketTCP = socket(AF_INET, SOCK_STREAM, 0);

	if (socketTCP == -1)
	{
		perror("Erreur de creation de la socket TCP");
		return 0;
	}
	printf("Creation de la socket TCP avec succès \n");

	// creation de socket UDP 
	int socketUDP = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketUDP == -1)
	{
		perror("Erreur de creation de la socket UDP");
		return 0;
	}
	printf("Creation de la socket UDP avec succès \n");


	return 0;
}