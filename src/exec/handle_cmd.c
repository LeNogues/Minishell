/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/19 13:27:06 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	handle_cmd1_2(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin)
{
	int		id;

	id = fork();
	if (id == 0)
	{
		open_fd(cmd);
		dup_first(cmd, pipe_fd);
		if(choice_of_builtin(cmd, env, cmd_origin, pipe_fd) != 0)
			return (0);
		cmd->full_path = verif_arg(cmd->cmd, env);
		if (!cmd->full_path)
			return (free_tab(cmd->cmd), -1);
		execute(cmd, env->envp);
	}
	return (0);
}
