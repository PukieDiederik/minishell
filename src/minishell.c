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
	t_cmd	*cmdv;

	printf("CMD: abc \"123\" abc\n");
	cmdv = parse_input("abc \"123\" abc");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: \"123\"\n");
	cmdv = parse_input("\"123\"");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: \n");
	cmdv = parse_input("");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: NULL\n");
	cmdv = parse_input(0);
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD:     \n");
	cmdv = parse_input("    ");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: hello '123' | abc 123\n");
	cmdv = parse_input("hello '123' | abc 123");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: hello '123' |    \n");
	cmdv = parse_input("hello '123' |    ");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: \"hello\" '123' | abc 123 | | \n");
	cmdv = parse_input("\"hello\" '123' | abc 123 | | ");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	//Testing of ENV variables
	printf("CMD: cat $PATH\n");
	cmdv = parse_input("cat $PATH");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: cat $\n");
	cmdv = parse_input("cat $");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: cat $ \n");
	cmdv = parse_input("cat $ ");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: cat $PATH$SHELL\n");
	cmdv = parse_input("cat $PATH$SHELL");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: cat \"$PATH$SHELL\"\n");
	cmdv = parse_input("cat \"$PATH$SHELL\"");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);

	printf("CMD: cat \"Hi$SHELL $PATH\"\n");
	cmdv = parse_input("cat \"Hi$SHELL $PATH\"");
	print_cmdv(cmdv);
	destroy_cmdv(cmdv);
}