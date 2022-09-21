/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 02:09:34 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/08 02:09:36 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	disable_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		*get_last_exit_p() = 1 * EXIT_MULT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}
