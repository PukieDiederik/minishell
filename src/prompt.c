/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:49:12 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/25 13:49:47 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

static int	is_empty_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

static int	is_empty(char *str)
{
	while (str && *str && is_empty_char(*str))
		str++;
	return (!(str && !is_empty_char(*str)));
}

char	*prompt_user(void)
{
	char	*str;
	char	*str_trim;

	str = 0;
	while (is_empty(str))
	{
		free(str);
		str = readline(C_GREEN"$"C_CYAN"> "C_RESET);
	}
	str_trim = ft_strtrim(str, " \t\n");
	free(str);
	if (!str_trim)
		return (0);
	add_history(str_trim);
	return (str_trim);
}
