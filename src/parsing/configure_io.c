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

static void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
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
		skip_spaces(str, &i);
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
