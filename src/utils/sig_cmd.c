/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 02:10:28 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/08 02:10:30 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/signal.h>

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		printf("\n");
}

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, handle_cmd_signal);
	signal(SIGINT, handle_cmd_signal);
}
