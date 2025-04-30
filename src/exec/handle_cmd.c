/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:37:22 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/29 17:31:45 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	dup_no_fd(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->pos == 1)
		dup_first(cmd, pipe_fd);
	if (cmd->pos == 2)
		dup_middle(cmd, pipe_fd);
	if (cmd->pos == 3)
		dup_last(cmd, pipe_fd);
}

int	handle_cmd(t_cmd *cmd, t_env *env, t_pipe *pipe_fd, t_cmd *cmd_origin)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (!verif_file(cmd, cmd_origin, env, pipe_fd))
			free_cmd_env_pipe(cmd_origin, env, pipe_fd);
		dup_no_fd(cmd, pipe_fd);
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
