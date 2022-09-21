/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_argvv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:00:41 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/14 14:43:43 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>

// Destroys an argv array
void	destroy_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

// Destroys an t_cmd array
void	destroy_cmd(t_cmd *cmdv)
{
	if (!cmdv)
		return ;
	destroy_argv(cmdv->argv);
	free(cmdv->in_file);
	free(cmdv->out_file);
}

// Destroys an t_cmd array
void	destroy_cmdv(t_cmd *cmdv)
{
	int	i;

	if (!cmdv)
		return ;
	i = 0;
	while (cmdv[i].argv)
		destroy_cmd(cmdv + i++);
	free(cmdv);
}
