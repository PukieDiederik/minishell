/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:35:51 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/12 15:06:00 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

// Definitions

// Functions
// Parsing
char	***parse_input(char *str);
int		count_commands(const char *str);
int		count_argv(const char *str);
char	*get_next_cmd(const char *str);
char	*insert_env(char *str, int i);

// Utils
void	print_argvv(char ***argvv);
void	destroy_argv(char **argv);
void	destroy_argvv(char ***argvv);

#endif