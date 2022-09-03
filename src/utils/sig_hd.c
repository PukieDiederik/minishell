#include "minishell.h"
#include <sys/signal.h>
#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>

void sig_hd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		*get_last_exit_p() = 130 * EXIT_MULT;
		exit(5);
	}
}
