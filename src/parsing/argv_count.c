/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:10:30 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/17 12:00:05 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int is_special_char(char c);

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

static int	skip_regular(const char *str, int *i, int *c)
{
	if (str[*i] != '|')
		(*c)++;
	while (!is_special_char(str[*i]))
		(*i)++;
	if (str[*i] == '|')
		return (1);
	return (0);
}

int skip_redirect(char *str, int *i)
{
	int	dummy;

	dummy = 0;
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
	if (str[*i] == '\'' || str[*i] == '"')
		skip_qouted(str, i);
	else if (is_special_char(str[*i]))
		return (1);
	else
		skip_regular(str, i, &dummy);
	return (0);
}

// If you want the 2nd commands argument give the pointer to the start of it
int	count_argv(const char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if ((str[i] == '<' || str[i] == '>') && skip_redirect((char *)str, &i))
			return (-1);
		else if (str[i] == '"' || str[i] == '\'')
		{
			if (skip_qouted(str, &i))
				return (-1);
			c++;
		}
		else if (skip_regular(str, &i, &c))
			break ;
	}
	return (c);
}
