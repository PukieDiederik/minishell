#include <stdio.h>
#include "minishell.h"

int main(int argc, char **argv)
{
	int i = -1;
	printf("argc    : %d\n", argc);
	while (++i < argc)
		printf("argv [%d]: %s\n", i, argv[i]);

	// Parsing tests
	parse_input("abc \"123\" abc");
	parse_input("\"123\"");
	parse_input("");
	parse_input(0);
	parse_input("    ");
	parse_input("hello '123' | abc 123");
}