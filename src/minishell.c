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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_cmd	*cmdv;

	str = 0;
	if (argc != 1)
		printf("%s: minishell does not use any arguments\n", argv[0]);
	while (1)
	{
		free(str);
		str = prompt_user();
		if (!ft_strncmp(str, "exit", 4))
		{
			free(str);
			return (0);
		}
		cmdv = parse_input(str);
		if (!cmdv)
			continue ;
		exec(cmdv, envp);
		destroy_cmdv(cmdv);
	}
}
