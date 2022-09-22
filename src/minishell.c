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

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

char		**g_environ;

static int	malloc_env(char **envp)
{
	char			**new_env;
	unsigned int	i;

	new_env = ft_calloc(get_argv_size(envp) + 1, sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
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

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_cmd	*cmdv;

	(void)ac;
	(void)av;
	handle_global_signals();
	if (malloc_env(envp))
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
