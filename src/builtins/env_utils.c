#include "minishell.h"
#include "libft.h"

extern char **environ;

static int get_size(char **env)
{
	int c;

	c = 0;
	while (*env++)
		c++;
	return (c);
}

static int validate_env(char *env)
{
	while((*env >= 'A' && *env <= 'Z') || (*env >= 'a' && *env <= 'z')
			|| *env == '_')
		env++;
	return (*env == '=' || *env == '\0');
}

int	add_env(char *env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(get_size(environ) + 2, sizeof(char *));
	env = ft_strdup(env);
	if (!env || !new_env || !validate_env(env))
	{
		free(new_env);
		free(env);
		return (1);
	}
	i = 0;
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = env;
	environ = new_env;
	return (0);
}

int remove_env(char *env)
{
	char			**new_env;
	unsigned int	i;
	unsigned int	j;
	unsigned int	env_s;

	new_env = ft_calloc(get_size(environ) + 1, sizeof(char*));
	if (!new_env)
		return (1);
	env_s = ft_strlen(env);
	i = 0;
	j = 0;
	while (environ[i])
	{
		if (!(!ft_strncmp(environ[i], env, env_s) && environ[i][env_s] == '='))
			new_env[j++] = environ[i];
		i++;
	}
	return (0);
}