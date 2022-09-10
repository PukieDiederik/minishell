/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:10:30 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/29 12:01:22 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	is_special_char(char c);

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

static int	skip_arg(const char *str, int *i)
{
	while (str[*i] != ' ' && str[*i] != '|' && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (skip_qouted(str, i))
				return (1);
		}
		else
			while (!is_special_char(str[*i]))
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

static void	skip_non_arg(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == '<' || str[*i] == '>')
			skip_redirect(str, i);
		else
			(*i)++;
	}
}

// If you want the 2nd command's argument give the pointer to the start of it
int	count_argv(const char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	skip_non_arg(str, &i);
	while (str[i] && str[i] != '|')
	{
		if (skip_arg(str, &i))
		{
			return (-1);
		}
		skip_non_arg(str, &i);
		c++;
	}
	return (c);
}
