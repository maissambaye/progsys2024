#include <stdio.h>
#include <unistd.h>

extern char *optarg;
extern int optopt;


int main(int argc, char *argv[])
{
	// declarer la variable qui recoit le code de l'option
	int opt;

	// appel à getopt 
	while( (opt = getopt(argc, argv, ":lm:nk:") ) != -1)
	{
		// Traiter le resultat de getopt
		switch(opt){
			case 'l' :
			case 'n' :
				printf("L'option -%c est fournie \n", opt);
				break;
			case 'm' :
			case 'k' :
				printf("L'option -%c est fournie avec comme argument %s\n", opt, optarg);
				break;
			case ':' :
			// une option qui attend un argument qui est absent
				printf("Erreur : L'option -%c  attend un argument \n",optopt );
				break;
			case '?' :
				printf("Erreur : Option %c inconnue\n", optopt);
				break;
		}

	}
	
	return 0;
}