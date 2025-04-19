/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/19 11:10:20 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	handle_first_cmd(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin)
{
	int		id;

	if(choice_of_builtin(cmd, env, cmd_origin, pipe_fd) != 0)
		return (0);
	cmd->full_path = verif_arg(cmd->cmd, env);
	if (!cmd->full_path)
		return (free_tab(cmd->cmd), -1);
	id = fork();
	if (id == 0)
		execute_with_input(cmd, env->envp, pipe_fd);
	return (0);
}

int	handle_last_cmd(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin)
{
	int		id;

	if(choice_of_builtin(cmd, env, cmd_origin, pipe_fd) != 0)
		return (0);
	cmd->full_path = verif_arg(cmd->cmd, env);
	if (!cmd->full_path)
		return (free_tab(cmd->cmd), -1);
	id = fork();
	if (id == 0)
		execute_with_output(cmd, env->envp, pipe_fd);
	return (0);
}
