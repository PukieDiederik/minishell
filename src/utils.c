/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:13:56 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/25 14:14:01 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	get_argv_size(char **argv)
{
	int	c;

	if (!argv)
		return (0);
	c = 0;
	while (argv[c])
		c++;
	return (c);
}

unsigned int	is_special_char(char c)
{
	return (c == ' ' || c == '<' || c == '>' || c == '"' || c == '\''
		|| c == '|' || c == '\0');
}

int	*get_last_exit_p(void)
{
	static int	last_exit = 0;

	return (&last_exit);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	get_cmd_size(t_cmd *cmdv)
{
	int	i;

	i = 0;
	if (!cmdv)
		return (0);
	while (cmdv[i].argv)
		i++;
	return (i);
}
