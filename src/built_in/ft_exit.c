/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:50:10 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/02 15:34:36 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static void	exit_clean(unsigned int return_value, t_cmd *cmd, t_env *env)
{
	free_cmd(cmd);
	free_tab(env->envp);
	free(env);
	exit(return_value);
}

void	ft_exit(t_cmd *cmd, t_env *env)
{
	int				result;
	long			exit_value;
	unsigned int	test;

	result = ft_atol((*cmd).cmd[1], &exit_value);
	test = exit_value;
	if (result == 1)
	{
		if (!(*cmd).cmd[1])
			exit_clean(test, cmd, env);
		else if (!(*cmd).cmd[2])
			exit_clean(test, cmd, env);
		else if ((*cmd).cmd[2] != 0)
			write(1, "too many arguments\n", 19);
	}
	else if (result == -1)
	{
		write(1, "only numeric argument\n", 22);
		exit_clean(2, cmd, env);
	}
}
