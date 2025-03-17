/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   built_in2.c                                          ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/14 12:50:10 by sle-nogu             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 17:55:02 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	exit_clean(unsigned int return_value, char **cmd, t_env *env)
{
	free_tab(cmd);
	free_tab(env->envp);
	free(env);
	exit(return_value);
}

void	ft_exit(char **cmd, t_env *env)
{
	int				result;
	long			exit_value;
	unsigned int	test;

	result = ft_atol(cmd[1], &exit_value);
	test = exit_value;
	if (result == 1)
	{
		if (!cmd[1])
			exit_clean(test, cmd, env);
		else if (!cmd[2])
			exit_clean(test, cmd, env);
		else if (cmd[2] != 0)
			write(1, "too many arguments\n", 19);
	}
	else if (result == -1)
	{
		write(1, "only numeric argument\n", 22);
		exit_clean(2, cmd, env);
	}
}

void	ft_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->envp)
		return ;
	while (env->envp[i] != 0)
	{
		write(1, env->envp[i], ft_strlen(env->envp[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	ft_unset(char **cmd, t_env *env)
{
	int		i;
	int		j;
	char	**new_env;
	int		size;

	
	i = 0;
	j = 0;
	if (!env || !env->envp)
		return ;
	size = ft_tablen(env->envp);
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return ;
	while (env->envp[i])
	{
		if (is_in_tab(env->envp[i], cmd) == 0)
		{
			new_env[j] = ft_strdup(env->envp[i]);
			if (!new_env[j])
				return (free_tab(new_env));
			j++;
		}
		i++;
	}
	new_env[j - 1] = NULL;
	free_tab(env->envp);
	set_environment(env, new_env);
	free_tab(new_env);
	return ;
}
