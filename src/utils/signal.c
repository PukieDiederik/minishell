/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:00:51 by galpers           #+#    #+#             */
/*   Updated: 2022/07/21 10:01:42 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void disable_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		*get_last_exit_p() = 130 * EXIT_MULT;
		printf("\n");
	}
	if (sig == SIGQUIT)
	{
		*get_last_exit_p() = 131 * EXIT_MULT;
		printf("minishell: quit process\n");
	}
}

static void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		*get_last_exit_p() = 130 * EXIT_MULT;
		exit(130);
	}
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

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, handle_cmd_signal);
	signal(SIGINT, handle_cmd_signal);
}

void	handle_heredoc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_signal);
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}