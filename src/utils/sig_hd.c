#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_hd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(5);
	}
}
