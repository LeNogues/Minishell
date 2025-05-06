/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:37:51 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 21:06:30 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int			g_state_signal = 1;

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = malloc(sizeof(t_info));
	info->env = malloc(sizeof(t_env));
	handle_signal();
	if (!info->env)
		return (-1);
	if (!envp[0])
	{
		if (create_env(info->env))
			return (-1);
	}
	else if (set_environment(info->env, envp))
		return (-1);
	hub(info);
	free_tab(info->env->envp);
	free(info->env);
	free(info);
	return (0);
}
