#include "minishell.h"
#include "libft.h"

extern char **g_environ;
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
	while (g_environ[++i])
		if (!ft_strncmp(g_environ[i], env, s_env) && g_environ[i][s_env] == '=')
			return (g_environ + i);
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
	while (g_environ[++i])
		if (!ft_strncmp(g_environ[i], env, s_env) && g_environ[i][s_env] == '=')
			return (ft_strchr(g_environ[i], '=') + 1);
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
	new_env = ft_calloc(get_argv_size(g_environ) + 2, sizeof(char *));
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
		while (g_environ[i])
		{
			new_env[i] = g_environ[i];
			i++;
		}
		new_env[i] = env;
		free(g_environ);
		g_environ = new_env;
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
	new_env = ft_calloc(get_argv_size(g_environ), sizeof(char*));
	if (!new_env)
		return (1);
	env_s = ft_strlen(env);
	i = 0;
	j = 0;
	while (g_environ[i])
	{
		if (!ft_strncmp(g_environ[i], env, env_s) && g_environ[i][env_s] == '=')
			free(g_environ[i]);
		else
			new_env[j++] = g_environ[i];
		i++;
	}
	free(g_environ);
	g_environ = new_env;
	return (0);
}