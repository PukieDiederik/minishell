/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_io_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:22:18 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/10 16:22:19 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	handle_file_in(char *str, t_cmd *cmd)
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

static int	handle_file_hd(char *str, t_cmd *cmd)
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

static int	handle_file_out(char *str, t_cmd *cmd)
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

static int	handle_file_out_append(char *str, t_cmd *cmd)
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

int	handle_redirect(char *str, t_cmd *cmd, int *i)
{
	if (str[*i] == '<' && str[*i + 1] != '<')
	{
		if (handle_file_in(str + *i, cmd))
			return (1);
		skip_redirect(str, i);
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		if (handle_file_hd(str + *i, cmd))
			return (1);
		skip_redirect(str, i);
	}
	else if (str[*i] == '>' && str[*i + 1] != '>')
	{
		if (handle_file_out(str + *i, cmd))
			return (1);
		skip_redirect(str, i);
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		if (handle_file_out_append(str + *i, cmd))
			return (1);
		skip_redirect(str, i);
	}
	return (0);
}
