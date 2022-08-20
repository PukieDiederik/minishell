#include "minishell.h"
#include "libft.h"

extern char **l_environ;
#include <stdio.h>

int validate_env(char *env)
{
	while((*env >= 'A' && *env <= 'Z') || (*env >= 'a' && *env <= 'z')
			|| *env == '_')
		env++;
	return (*env == '=' || *env == '\0');
}

static char **get_env_p(char *env)
{
	unsigned int	i;
	unsigned int	s_env;

	i = -1;
	if (ft_strchr(env, '='))
		s_env = ft_strchr(env, '=') - env;
	else
		s_env = ft_strlen(env);
	while (l_environ[++i])
		if (!ft_strncmp(l_environ[i], env, s_env) && l_environ[i][s_env] == '=')
			return (l_environ + i);
	return (0);
}

char *get_env(char *env)
{
	unsigned int	i;
	unsigned int	s_env;

	i = -1;
	if (ft_strchr(env, '='))
		s_env = ft_strchr(env, '=') - env;
	else
		s_env = ft_strlen(env);
	while (l_environ[++i])
		if (!ft_strncmp(l_environ[i], env, s_env) && l_environ[i][s_env] == '=')
			return (ft_strchr(l_environ[i], '=') + 1);
	return (0);
}

int	add_env(char *env)
{
	char	**old_env;
	char	**new_env;
	int		i;

	if (!ft_strchr(env, '='))
		return (0);
	if (!validate_env(env))
		return (2);
	new_env = ft_calloc(get_argv_size(l_environ) + 2, sizeof(char *));
	env = ft_strdup(env);
	if (!env || !new_env || !validate_env(env))
	{
		free(new_env);
		free(env);
		return (1);
	}
	old_env = get_env_p(env);
	if (old_env)
	{
		free(*old_env);
		*old_env = env;
		free(new_env);
		return (0);
	}
	else
	{
		i = 0;
		while (l_environ[i])
		{
			new_env[i] = l_environ[i];
			i++;
		}
		new_env[i] = env;
		free(l_environ);
		l_environ = new_env;
		return (0);
	}
}

int remove_env(char *env)
{
	char			**new_env;
	unsigned int	i;
	unsigned int	j;
	unsigned int	env_s;

	if (!get_env_p(env))
		return (0);
	new_env = ft_calloc(get_argv_size(l_environ), sizeof(char*));
	if (!new_env)
		return (1);
	env_s = ft_strlen(env);
	i = 0;
	j = 0;
	while (l_environ[i])
	{
		if (!ft_strncmp(l_environ[i], env, env_s) && l_environ[i][env_s] == '=')
			free(l_environ[i]);
		else
			new_env[j++] = l_environ[i];
		i++;
	}
	free(l_environ);
	l_environ = new_env;
	return (0);
}