#ifndef UTILS_H
#define UTILS_H

struct infofile{
	char nomfichier[255];
	int taille;
	int mode ;
};

struct block_data{
	int taille;
	char data[4096];
};

#endif