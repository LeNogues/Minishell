/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/27 14:31:22 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	open_and_dup(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	open_fd(cmd, cmd_origin, pipe_fd, env);
	if (cmd->pos == 1)
		dup_first(cmd, cmd_origin, pipe_fd, env);
	if (cmd->pos == 2)
		dup_middle(cmd, cmd_origin, pipe_fd, env);
	if (cmd->pos == 3)
		dup_last(cmd, cmd_origin, pipe_fd, env);
}

int	handle_cmd(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin)
{
	int	id;

	if (!verif_file(cmd, env, pipe_fd))
		return (0);
	id = fork();
	if (id == 0)
	{
		if (choice_of_builtin(cmd, env, cmd_origin, pipe_fd) == 0)
			execute(cmd, env, pipe_fd, cmd_origin);
		else
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
	}
	g_state_signal = 2;
	if (cmd->nb_cmd == 1)
		close_pipe_fd(pipe_fd->old);
	return (1);
}
