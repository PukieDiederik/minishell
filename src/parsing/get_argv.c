/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:07:07 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/25 13:56:02 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
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

static int get_arg_length(char *str)
{
	int i = 0;
	int j = 0;


	while(str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			skip_qouted(str, &i);
			j += 2;
		}
		else
			skip_regular(str, &i);
	}
	return (i - j);
}

static void get_regular(char *dest, char *src, int *i)
{
	while (!is_special_char(*src) && *src != '\0')
		dest[(*i)++] = *src++;
}

static void get_qouted(char *dest, char *src, int *i)
{
	char qoute = *src++;
	while (*src != qoute)
		dest[(*i)++] = *src++;
}

static char *get_arg(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*arg;

	size = get_arg_length(str);
	arg = ft_calloc(size + 1, sizeof(char));

	i = 0;
	j = 0;
	while (i < size)
	{
		if (str[j] == '\'' || str[j] == '"')
		{
			get_qouted(arg, str + j, &i);
			skip_qouted(str, &j);
		}
		else
		{
			get_regular(arg, str + j, &i);
			skip_regular(str, &j);
		}
	}
	return (arg);
}

static int skip_arg(const char *str, int *i)
{
	while (str[*i] != ' ' && str[*i] != '|' && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (skip_qouted(str, i))
				return (1);
		}
		else
			skip_regular(str, i);
	}
	return (0);
}

static void skip_non_arg(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == '<' || str[*i] == '>')
			skip_redirect(str, i);
		else
			(*i)++;
	}
}

char	**get_argv(char *str)
{
	int				argv_count;
	char			**argv;
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	argv_count = count_argv(str);
	if (argv_count < 0) {
		return (0);
	}
	argv = ft_calloc(argv_count + 1, sizeof(char *));
	if (!argv)
	{
		print_error("INT_ERR", "Malloc error");
		return (0);
	}
	skip_non_arg(str, (int *)&i);
	while (j < argv_count)
	{
		argv[j++] = get_arg(str + i);
		skip_arg(str, (int *)&i);
		skip_non_arg(str, (int *)&i);
	}
	return (argv);
}
