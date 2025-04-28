/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:37:51 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/24 11:37:33 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int			g_state_signal = 1;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = malloc(sizeof(t_env));
	handle_signal();
	if (!env)
		return (-1);
	if (!envp[0])
	{
		if (create_env(env))
			return (-1);
	}
	else if (set_environment(env, envp))
		return (-1);
	hub(env);
	free_tab(env->envp);
	free(env);
	return (0);
}
