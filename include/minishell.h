/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:35:51 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/28 14:26:02 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

// Definitions

// Functions
// Parsing
char			***parse_input(char *str);
int				count_commands(const char *str);
int				count_argv(const char *str);
char			*get_next_cmd(const char *str);
char			*insert_env(char *str, int i);
unsigned int	get_argv(char *str, char **argv);

// Utils
void			print_argvv(char ***argvv);
void			destroy_argv(char **argv);
void			destroy_argvv(char ***argvv);

char			*get_qouted_str(char *str);
char			*get_regular_str(char *str);
char			*process_regular(char *str);
char			*process_qouted_single(char *str);
char			*process_qouted_double(char *str);

#endif