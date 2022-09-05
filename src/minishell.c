/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:57:10 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/22 20:57:12 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

extern char **environ;
char **g_environ;

static int malloc_env()
{
	char			**new_env;
	unsigned int	i;

	new_env = ft_calloc(get_argv_size(environ) + 1, sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			destroy_argv(new_env);
			return (2);
		}
		i++;
	}
	g_environ = new_env;
	return (0);
}

int	main()
{
	char	*str;
	t_cmd	*cmdv;

	handle_global_signals();
	if (malloc_env())
		print_error_exit("INT_ERR", "Malloc error", 125);
	while (1)
	{
		str = prompt_user();
		cmdv = parse_input(&str);
		free(str);
		if (!cmdv)
		{
			*get_last_exit_p() = 130 * EXIT_MULT;
			continue ;
		}
		exec(cmdv);
		destroy_cmdv(cmdv);
	}
}
