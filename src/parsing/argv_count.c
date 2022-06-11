/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:10:30 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/11 14:12:38 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (str[*i] && str[*i] != '|' && str[*i] != ' ')
		(*i)++;
	if (str[*i] == '|')
		return (1);
	return (0);
}

// If you want the 2nd commands argument give the pointer to the start of it
// Assumes that count_commands has been run before it so this does not error check
int count_argv(const char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			while (str[i] == ' ')
				i++;
		else if (str[i] == '"' || str[i] == '\'')
		{
			if (skip_qouted(str, &i))
				return (-1);
			c++;
		}
		else if (skip_regular(str, &i, &c))
			break;
	}
	return (c);
}