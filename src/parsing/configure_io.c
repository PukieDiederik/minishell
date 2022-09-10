/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:49:15 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/10 00:49:17 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(char *str, t_cmd *cmd, int *i);

static int	skip_qouted(const char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (!str[*i])
		return (1);
	(*i)++;
	return (0);
}

static void	set_defaults(t_cmd *cmdv)
{
	int	j;

	j = 0;
	while (cmdv[j].argv)
	{
		cmdv[j].in_type = io_pipe;
		cmdv[j].in_file = 0;
		cmdv[j].out_type = io_pipe;
		cmdv[j].out_file = 0;
		j++;
	}
	cmdv[0].in_type = io_none;
	cmdv[--j].out_type = io_none;
}

int	configure_io(char *str, t_cmd *cmdv)
{
	int		j;
	int		i;

	set_defaults(cmdv);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '>' || str[i] == '<')
		{
			if (handle_redirect(str, cmdv + j, &i))
				return (1);
		}
		else if (str[i] == '\'' || str[i] == '"')
			skip_qouted(str, &i);
		else if (str[i] == '|')
		{
			j++;
			i++;
		}
		else
			skip_regular(str, &i);
	}
	return (0);
}
