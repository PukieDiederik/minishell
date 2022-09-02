/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:18:58 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/02 23:18:59 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

extern char	**g_environ;

int	b_exit(t_cmd *cmdv, int i)
{
	if (get_argv_size(cmdv[i].argv) > 1)
	{
		print_error("exit", "Too many arguments");
		return (2);
	}
	if (i != 0)
		return (0);
	destroy_cmdv(cmdv);
	destroy_argv(g_environ);
	exit(0);
}
