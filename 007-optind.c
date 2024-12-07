#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern char *optarg;
extern int optopt;
extern int optind; // l'index du premier element de argv qui n'est ni option ni parametre d'option
int main(int argc, char *argv[])
{
	int opt ;
	int n=1;

	while( (opt = getopt(argc, argv, ":n:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				n = atoi(optarg);
				
				break;
			case ':':
				printf("Erreur, l'option -%c attend un argument\n", optopt );
				break;
			case '?':
				printf("Erreur, l'option -%c est inconnye \n", optopt);
				break;
		}
	}

	printf("Nombre de morceaux %d\n", n);
	int i;
	for (i = optind; i <argc; i++ )
	{
		printf("%s\n",argv[i] );
	}


	return 0;
}