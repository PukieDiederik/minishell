#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int main(int argc, char **argv, char **envp)
{
	int i = -1;
	char *str = 0;
	t_cmd *cmdv = 0;

	printf("argc    : %d\n", argc);
	while (++i < argc)
		printf("argv [%d]: %s\n", i, argv[i]);

	while(1) {
		free(str);
		str = prompt_user();
		if (!ft_strncmp(str, "exit", 4)) {
			free(str);
			return 0;
		}
		cmdv = parse_input(str);
		exec(cmdv, envp);
//		print_cmdv(cmdv);
		destroy_cmdv(cmdv);
	}
}