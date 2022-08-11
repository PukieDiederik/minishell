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
#include "libft.h"
#include <stdio.h>

extern char **environ;

int	b_env(t_cmd *cmdv)
{
	int		i;

	if (get_argv_size(cmdv->argv) > 1)
	{
		print_error(cmdv->argv[0], "Too many arguments");
		return (1);
	}
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}