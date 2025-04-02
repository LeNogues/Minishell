/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:46:15 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/02 17:40:15 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->envp)
		return ;
	while (env->envp[i])
	{
		if (ft_strlen(env->envp[i++]) > 2097152)
		{
			ft_printf("Argument list too long");
			return ;
		}
	}
	i = 0;
	while (env->envp[i])
	{
		write(1, env->envp[i], ft_strlen(env->envp[i]));
		write(1, "\n", 1);
		i++;
	}
}
