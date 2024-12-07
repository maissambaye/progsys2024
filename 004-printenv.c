#include <stdio.h>


int main(int argc, char *argv[], char *arge[])
{

	int i = 0;
	while(arge[i] != NULL){
			printf("arge[%d] = %s\n", i, arge[i]);
			i++;
		};

}