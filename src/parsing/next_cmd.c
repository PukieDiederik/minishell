/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:17:26 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/11 14:37:39 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	skip_qouted(const char **str)
{
	char	c;

	c = **str;
	(*str)++;
	while (**str && **str != c)
		(*str)++;
	if (**str)
		(*str)++;
}

static int	skip_regular(const char **str)
{
	while (**str && **str != '|' && **str != ' ')
		(*str)++;
	if (**str == '|')
		return (1);
	return (0);
}

char *get_next_cmd(const char *str)
{
	while (*str)
	{
		if (*str == ' ')
			while (*str == ' ')
				str++;
		else if (*str == '"' || *str == '\'')
			skip_qouted(&str);
		else if (skip_regular(&str))
			return ((char *)str);
	}
	return ((char *)str);
}