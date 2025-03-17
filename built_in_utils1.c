/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   built_in_utils1.c                                    ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/12 17:28:59 by sle-nogu             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 17:55:20 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	change_pwd(t_env *env, char *path)
{
	char	*new_pwd;
	int		i;

	i = 0;
	if (!env || !env->envp)
		return ;
	while (env->envp[i])
	{
		if (strncmp("PWD=", env->envp[i], 4) == 0)
			break ;
		i++;
	}
	if (path[0] != '/')
		path = create_new_path(env, path);
	new_pwd = ft_strjoin("PWD=", path);
	if (!new_pwd)
		return (perror("ft_strjoin"));
	free(env->envp[i]);
	free(path);
	env->envp[i] = new_pwd;
}

void	change_old_pwd(t_env *env)
{
	char	*cwd;
	char	*old_pwd;
	int		i;

	i = 0;
	if (!env || !env->envp)
		return ;
	while (env->envp[i])
	{
		if (strncmp("OLDPWD=", env->envp[i], 7) == 0)
			break ;
		i++;
	}
	cwd = ft_getenv("PWD=", env);
	if (!cwd)
		return (perror("ft_getenv"));
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
		return (perror("ft_strjoin"));
	free(env->envp[i]);
	free(cwd);
	env->envp[i] = old_pwd;
}

char	*get_home(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->envp)
		return (0);
	while (env->envp[i])
	{
		if (strncmp("HOME=", env->envp[i], 5) == 0)
			break ;
		i++;
	}
	if (!env->envp[i])
		return (0);
	return (env->envp[i] + 5);
}

int	check_flags(t_cmd cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (!cmd.cmd[1])
		return (1);
	while (cmd.cmd[i] && cmd.cmd[i][0] == '-' && cmd.cmd[i][j] == 'n')
	{
		if (cmd.cmd[i][j] != 'n')
			break ;
		j++;
		if (!cmd.cmd[i][j])
		{
			i++;
			j = 1;
		}
	}
	return (i);
}

char	*ft_getenv(char *value_name, t_env *env)
{
	int		i;
	char	*value_env;
	int		size_value_name;

	if (!env || !env->envp || !value_name)
		return (0);
	size_value_name = ft_strlen(value_name);
	i = 0;
	while (env->envp[i])
	{
		if (strncmp(value_name, env->envp[i], size_value_name) == 0)
			break ;
		i++;
	}
	value_env = ft_strdup(env->envp[i] + size_value_name);
	return (value_env);
}
