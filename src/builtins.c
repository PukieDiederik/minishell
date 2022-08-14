#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int is_builtin(char *str)
{
	return (ft_strncmp(str, "echo", 5) == 0
			|| ft_strncmp(str, "cd", 3) == 0
			|| ft_strncmp(str, "pwd", 4) == 0
			|| ft_strncmp(str, "export", 7) == 0
			|| ft_strncmp(str, "unset", 6) == 0
			|| ft_strncmp(str, "env", 4) == 0);
}

static void dup_stdio(int *orig_fds)
{
	orig_fds[0] = dup(STDIN_FILENO);
	orig_fds[1] = dup(STDOUT_FILENO);
}

static void reset_stdio(int *orig_fds)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(orig_fds[0], STDIN_FILENO);
	dup2(orig_fds[1], STDOUT_FILENO);
	close(orig_fds[0]);
	close(orig_fds[1]);
}

// returns exit status
int launch_builtin(int *fd, t_cmd *cmdv, int i)
{
	int status;
	int orig_fds[2];

	dup_stdio(orig_fds);
	set_child_fds(fd, cmdv + i);
	if (ft_strncmp(cmdv[i].argv[0], "echo", 5) == 0)
		status = b_echo(cmdv + i);
//	if (ft_strncmp(cmdv[i].argv[0], "cd", 3) == 0)
//		status = b_cd(cmdv[i]);
//	if (ft_strncmp(cmdv[i].argv[0], "pwd", 4) == 0)
//		status = b_echo(cmdv[i], str);
	else if (ft_strncmp(cmdv[i].argv[0], "export", 7) == 0)
		status = b_export(cmdv + i);
	if (ft_strncmp(cmdv[i].argv[0], "unset", 6) == 0)
		status = b_unset(cmdv + i);
	if (ft_strncmp(cmdv[i].argv[0], "env", 4) == 0)
		status = b_env(cmdv + i);
	reset_stdio(orig_fds);
	*get_last_exit_p() = SET_EXIT_STATUS(status);
	return (status);
}
