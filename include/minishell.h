/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:35:51 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/04 13:47:11 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

// Definitions
/* e_io_type - What kind of io a command uses
 *
 * none			- Uses regular io file descriptors
 * pipe			- Remaps regular io file descriptors to a pipe
 * file			- Opens a file and remaps io file descriptors to file descriptor
 * file_append	- Same as file but opens it in append mode
 */
typedef enum e_io_type
{
	io_none,
	io_pipe,
	io_file,
	io_file_append
}	t_iotype;

// Structures

/* s_cmd - structure which holds information for each command
 *
 * argv			- Holds the argument vector for a command
 * in/out_type	- Hold the type of input/output
 * in/out_file	- Holds a path to the input/output file if in/out_type is file
 */
typedef struct s_cmd
{
	char		**argv;
	t_iotype	in_type;
	t_iotype	out_type;
	char		*in_file;
	char		*out_file;
}	t_cmd;

// Functions
// Parsing
t_cmd			*parse_input(char *str);
int				count_commands(const char *str);
int				count_argv(const char *str);
char			*get_next_cmd(const char *str);
char			*insert_env(char *str, int i);
char			**get_argv(char *str);

// Utils
void			destroy_argv(char **argv);
void			destroy_cmdv(t_cmd *cmd);
void			print_cmdv(t_cmd *cmdv);

char			*get_qouted_str(char *str);
char			*get_regular_str(char *str);
char			*process_regular(char *str);
char			*process_qouted_single(char *str);
char			*process_qouted_double(char *str);

#endif