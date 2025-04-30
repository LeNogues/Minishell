/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/04/29 14:12:16 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static int	env_exist(t_env *env, char *cmd)
{
	int	i;
	int	j;

	if (!env->envp || !env->envp[0] || !cmd)
		return (0);
	i = 0;
	while (env->envp[i])
	{
		j = 0;
		while (env->envp[i][j] && cmd[j])
		{
			if (env->envp[i][j] == cmd[j] && cmd[j] != '=')
				j++;
			else
				break ;
		}
		if (env->envp[i][j] == '=')
		{
			free(env->envp[i]);
			env->envp[i] = ft_strdup(cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_arguments(int i, int size, char **cmd, t_env *new_env)
{
	int	j;

	j = 1;
	while (i < size - 1 && cmd[j])
	{
		if (is_valid(cmd[j]))
		{
			if (!env_exist(new_env, cmd[j]))
				new_env->envp[i++] = ft_strdup(cmd[j]);
		}
		j++;
	}
	new_env->envp[i] = NULL;
}

void	ft_export(char **cmd, t_env *env)
{
	int		size;
	int		i;
	t_env	*new_env;

	if (!env || !env->envp)
		return ;
	i = 0;
	size = ft_tablen(env->envp) + ft_tablen(cmd) + 1;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->envp = malloc(sizeof(char *) * size);
	if (!new_env->envp)
		return ;
	while (env->envp[i] != 0)
	{
		new_env->envp[i] = ft_strdup(env->envp[i]);
		i++;
	}
	new_env->envp[i] = NULL;
	add_arguments(i, size, cmd, new_env);
	free_tab(env->envp);
	set_environment(env, new_env->envp);
	free_tab(new_env->envp);
	free(new_env);
}
