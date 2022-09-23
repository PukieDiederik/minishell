/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:08:43 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/10 18:08:45 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	skip_regular(const char *str, int *i)
{
	while (str[*i] && !is_special_char(str[*i]))
		(*i)++;
	return (0);
}

int	skip_qouted(const char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (!str[*i])
	{
		print_error("Parsing", "Unclosed qoute");
		return (1);
	}
	(*i)++;
	return (0);
}

int	skip_arg(const char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] != ' ' && str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '\t' && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (skip_qouted(str, i))
				return (1);
		}
		else
			skip_regular(str, i);
	}
	while (str[*i] == ' ')
		(*i)++;
	return (0);
}

int	skip_non_arg(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == '<' || str[*i] == '>')
		{
			if (skip_redirect(str, i))
				return (1);
		}
		else
			(*i)++;
	}
	return (0);
}

int	skip_redirect(const char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] != '<')
		*i += 1;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		*i += 2;
	else if (str[*i] == '>' && str[*i + 1] != '>')
		*i += 1;
	else if (str[*i] == '>' && str[*i + 1] == '>')
		*i += 2;
	while (str[*i] == ' ')
		(*i)++;
	return (skip_arg(str, i));
}
