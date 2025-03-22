/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:50:10 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/22 15:18:14 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

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
			ft_printf("too many arguments\n");
	}
	else if (result == -1)
	{
		ft_printf("only numeric argument\n");
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
		ft_printf("%s\n", env->envp[i++]);
}

void	create_new_env(char **cmd, t_env *env, char ***new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*new_env = malloc(sizeof(char *) * ft_tablen(env->envp) + 1);
	if (!*new_env)
		return ;
	while (env->envp[i])
	{
		if (is_in_tab(env->envp[i], cmd) == 0)
		{
			(*new_env)[j] = ft_strdup(env->envp[i]);
			if (!(*new_env)[j])
			{
				free_tab(*new_env);
				*new_env = NULL;
				return ;
			}
			j++;
		}
		i++;
	}
	(*new_env)[j] = NULL;
}

void	ft_unset(char **cmd, t_env *env)
{
	char	**new_env;

	if (!env || !env->envp || !cmd[1])
		return ;
	create_new_env(cmd, env, &new_env);
	if (!new_env)
		return ;
	free_tab(env->envp);
	set_environment(env, new_env);
	free_tab(new_env);
}
