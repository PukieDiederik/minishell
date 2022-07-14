/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:30:58 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/14 12:12:17 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	get_return_val(int c, int has_args)
{
	if (!has_args && c == 1)
		return (0);
	else if (!has_args)
		return (-1);
	return (c);
}

static int	skip_regular(const char *str, int *i, int *has_args, int *c)
{
	if (str[*i] != '|')
		*has_args = 1;
	while (str[*i] && !is_special_char(str[*i]))
		(*i)++;
	if (str[*i] == '|')
	{
		if (!has_args)
			return (1);
		(*c)++;
		(*i)++;
		*has_args = 0;
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			(*i)++;
	}
	return (0);
}

int	count_commands(const char *str)
{
	int	i;
	int	c;
	int	has_args;

	has_args = 0;
	i = 0;
	c = 1;
	while (str[i])
	{
		if (str[i] == ' ')
			while (str[i] == ' ')
				i++;
		else if (str[i] == '"' || str[i] == '\'')
		{
			has_args = 1;
			if (skip_qouted(str, &i))
				return (-1);
		}
		else if (skip_regular(str, &i, &has_args, &c))
			return (-1);
	}
	return (get_return_val(c, has_args));
}
