#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern char *optarg;
extern int optopt;

int main(int argc, char *argv[])
{
	int opt ;
	int pas = 1;
	int nmax = 0;

	while( (opt = getopt(argc, argv, ":n:p:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				nmax = atoi(optarg);
				break;
			case 'p':
				pas = atoi(optarg);
				break;
			case ':':
				printf("Erreur, l'option -%c attend un argument\n", optopt );
				break;
			case '?':
				printf("Erreur, l'option -%c est inconnye \n", optopt);
				break;
		}
	}

	int i;
	for (i = 1; i <= nmax; i = i+pas )
	{
		printf("%d\n",i );
	}


	return 0;
}