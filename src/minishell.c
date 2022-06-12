#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int main(int argc, char **argv)
{
	int i = -1;
	printf("argc    : %d\n", argc);
	while (++i < argc)
		printf("argv [%d]: %s\n", i, argv[i]);

	// Parsing tests
	char ***argvv;

	argvv = parse_input("abc \"123\" abc");
	free(argvv);
	free(parse_input("abc \"123\" abc"));
	free(parse_input("\"123\""));
	free(parse_input(""));
	free(parse_input(0));
	free(parse_input("    "));
	free(parse_input("hello '123' | abc 123"));
	free(parse_input("hello '123' |    "));
	free(parse_input("\"hello\" '123' | abc 123 | | "));
}