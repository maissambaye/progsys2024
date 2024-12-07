#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	printf("Mon PID :  %d\n", getpid());
	printf("Mon PPID :  %d\n", getppid());
	return 0;
}