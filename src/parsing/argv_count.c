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

#include "minishell.h"

unsigned int	is_special_char(char c);

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
			return (-1);
		skip_non_arg(str, &i);
		c++;
	}
	return (c);
}
