/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 02:07:07 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/08 02:07:08 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

void	sig_hd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		*get_last_exit_p() = 130 * EXIT_MULT;
		exit(5);
	}
}
