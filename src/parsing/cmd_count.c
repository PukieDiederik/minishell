/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:30:58 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/17 12:04:17 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	get_return_val(int c, int has_args, const char *str)
{
	int	i;

	if (!has_args && c == 1)
		return (0);
	else if (!has_args)
	{
		i = ft_strlen(str);
		while (i > 0 && str[--i] == ' ');
		if (str[i] == '|')
			print_error("Parsing", "Unclosed pipe at end");
		return (-1);
	}
	return (c);
}

int is_redirect_valid (const char *str)
{
	unsigned int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[++i] == '<')
			i++;
	}
	else if (str[i] == '>')
	{
		if (str[++i] == '>')
			i++;
	}
	while(str[i] == ' ')
		i++;
	return (str[i] == '\0' || str[i] == '<' || str[i] == '>' || str[i] == '|');
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
		if ((str[i] == '<' || str[i] == '>'))
		{
			has_args = 1;
			if (is_redirect_valid(str + i))
			{
				print_error("Parsing", "Redirect is empty");
				return (-1);
			}
			if (skip_redirect((char *)str, &i))
				return (-1);
		}
		else if (str[i] == '"' || str[i] == '\'')
		{
			has_args = 1;
			if (skip_qouted(str, &i))
				return (-1);
		}
		else if (str[i] == '|')
		{
			if (!has_args)
			{
				print_error("parsing", "empty pipe");
				return (-1);
			}
			has_args = 0;
			c++;
			i++;
		}
		else
		{
			skip_regular(str, &i);
			has_args = 1;
		}
	}
	return (get_return_val(c, has_args, str));
}
