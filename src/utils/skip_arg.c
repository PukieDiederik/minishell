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