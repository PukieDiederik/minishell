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

	printf("CMD: abc \"123\" abc\n");
	argvv = parse_input("abc \"123\" abc");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: \"123\"\n");
	argvv = parse_input("\"123\"");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: \n");
	argvv = parse_input("");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: NULL\n");
	argvv = parse_input(0);
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD:     \n");
	argvv = parse_input("    ");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: hello '123' | abc 123\n");
	argvv = parse_input("hello '123' | abc 123");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: hello '123' |    \n");
	argvv = parse_input("hello '123' |    ");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: \"hello\" '123' | abc 123 | | \n");
	argvv = parse_input("\"hello\" '123' | abc 123 | | ");
	print_argvv(argvv);
	destroy_argvv(argvv);

	//Testing of ENV variables
	printf("CMD: cat $PATH\n");
	argvv = parse_input("cat $PATH");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: cat $\n");
	argvv = parse_input("cat $");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: cat $ \n");
	argvv = parse_input("cat $ ");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: cat $PATH$SHELL\n");
	argvv = parse_input("cat $PATH$SHELL");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: cat \"$PATH$SHELL\"\n");
	argvv = parse_input("cat \"$PATH$SHELL\"");
	print_argvv(argvv);
	destroy_argvv(argvv);

	printf("CMD: cat \"Hi$SHELL $PATH\"\n");
	argvv = parse_input("cat \"Hi$SHELL $PATH\"");
	print_argvv(argvv);
	destroy_argvv(argvv);
}