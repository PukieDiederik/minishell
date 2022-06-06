#include <stdio.h>
#include "minishell.h"

int main(int argc, char **argv)
{
	int i = -1;
	printf("argc    : %d\n", argc);
	while (++i < argc)
		printf("argv [%d]: %s\n", i, argv[i]);
}