/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:07:51 by galpers           #+#    #+#             */
/*   Updated: 2022/07/26 14:09:47 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

extern char	**g_environ;

/* b_env - BUILTIN env
 *
 * Lists all enviroment variables in g_environ
 * If it has arguments, exit
 * else go through each environ variable and print it
 */
int	b_env(t_cmd *cmdv)
{
	int	i;

	if (get_argv_size(cmdv->argv) > 1)
	{
		print_error(cmdv->argv[0], "Too many arguments");
		return (1);
	}
	i = 0;
	while (g_environ[i])
		printf("%s\n", g_environ[i++]);
	return (0);
}
