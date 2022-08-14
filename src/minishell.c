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

char **l_environ;

static int malloc_env()
{
	char			**new_env;
	unsigned int	i;

	new_env = ft_calloc(get_argv_size(l_environ) + 1, sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	while (l_environ[i])
	{
		new_env[i] = ft_strdup(l_environ[i]);
		if (!new_env[i])
		{
			destroy_argv(new_env);
			return (2);
		}
		i++;
	}
	printf("%p\n", new_env);
	l_environ = new_env;
	printf("%p\n", l_environ);

	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_cmd	*cmdv;

	str = 0;
	if (argc != 1)
		printf("%s: minishell does not use any arguments\n", argv[0]);
	l_environ = envp;
	if (malloc_env())
		print_error_exit("INT_ERR", "Malloc error", 125);
	while (1)
	{
		str = prompt_user();
		if (str && !ft_strncmp(str, "exit", 4))
		{
			destroy_argv(l_environ);
			free(str);
			return (0);
		}
		cmdv = parse_input(&str);
		if (!cmdv)
		{
			*get_last_exit_p() = SET_EXIT_STATUS(130);
			free(str);
			continue ;
		}
		exec(cmdv, envp);
		destroy_cmdv(cmdv);
		free(str);
	}
}
