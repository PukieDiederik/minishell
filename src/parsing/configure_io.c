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
#include <stdlib.h>

static int	skip_regular(const char *str, int *i, int *c)
{
	while (str[*i] && !is_special_char(str[*i]))
		(*i)++;
	if (str[*i] == '|')
	{
		(*c)++;
		(*i)++;
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			(*i)++;
	}
	return (0);
}

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

static int handle_file_in(char *str, t_cmd *cmd)
{
	if (*str != '<')
		return (1);
	if (cmd->in_file)
		free(cmd->in_file);
	cmd->in_type = io_file;
	str++;
	while (*str == ' ')
		str++;
	if (*str == '"' || *str == '\'')
		cmd->in_file = get_qouted_str(str);
	else if (is_special_char(*str))
		return (1);
	else
		cmd->in_file = get_regular_str(str);
	return (cmd->in_file == 0);
}

static int handle_file_hd(char *str, t_cmd *cmd)
{
	char	*tmp_str;

	if (*str != '<' || *(str + 1) != '<')
		return (1);
	if (cmd->in_file)
		free(cmd->in_file);
	cmd->in_type = io_file;
	str += 2;
	while (*str == ' ')
		str++;
	if (*str == '"' || *str == '\'')
		tmp_str = get_qouted_str(str);
	else if (is_special_char(*str))
		return (1);
	else
		tmp_str = get_regular_str(str);
	if (!tmp_str)
		return (1);
	cmd->in_file = launch_hd(tmp_str);
	free(tmp_str);
	return (cmd->in_file == 0);
}

static int handle_file_out(char *str, t_cmd *cmd)
{
	if (*str != '>')
		return (1);
	if (cmd->out_file)
		free(cmd->out_file);
	cmd->out_type = io_file;
	str++;
	while (*str == ' ')
		str++;
	if (*str == '"' || *str == '\'')
		cmd->out_file = get_qouted_str(str);
	else if (is_special_char(*str))
		return (1);
	else
		cmd->out_file = get_regular_str(str);
	return (cmd->out_file == 0);
}

static int handle_file_out_append(char *str, t_cmd *cmd)
{
	if (*str != '>' || *(str + 1) != '>')
		return (1);
	if (cmd->out_file)
		free(cmd->out_file);
	cmd->out_type = io_file_append;
	str += 2;
	while (*str == ' ')
		str++;
	if (*str == '"' || *str == '\'')
		cmd->out_file = get_qouted_str(str);
	else if (is_special_char(*str))
		return (1);
	else
		cmd->out_file = get_regular_str(str);
	return (cmd->out_file == 0);
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
		if (str[i] == '<' && str[i + 1] != '<')
		{
			if (handle_file_in(str + i, cmdv + j))
				return (1);
			skip_redirect(str, &i);
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			if (handle_file_hd(str + i, cmdv + j))
				return (1);
			skip_redirect(str, &i);
		}
		else if (str[i] == '>' && str[i + 1] != '>')
		{
			if (handle_file_out(str + i, cmdv + j))
				return (1);
			skip_redirect(str, &i);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			if (handle_file_out_append(str + i, cmdv + j))
				return (1);
			skip_redirect(str, &i);
		}
		if (str[i] == '\'' || str[i] == '"')
			skip_qouted(str, &i);
		else
			skip_regular(str, &i, &j);
	}
	return (0);
}
