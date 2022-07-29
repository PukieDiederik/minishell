/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:33:29 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/29 13:33:30 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void print_error(char *prefix, char *error)
{
	if (prefix)
	{
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO,"\n", 1);
}

void print_error_exit(char *prefix, char *error, int exit_code) {
	if (prefix)
	{
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO,"\n", 1);
	exit(exit_code);
}