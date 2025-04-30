/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:52:59 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/29 17:34:42 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	dup_first(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->nb_cmd > 1 && !cmd->fd_out)
		if (dup2(pipe_fd->old[1], STDOUT_FILENO) == -1)
			return (0);
	close_pipe_fd(pipe_fd->old);
	return (1);
}

int	dup_middle(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (!cmd->fd_in && !cmd->heredoc)
		if (dup2(pipe_fd->old[0], STDIN_FILENO) == -1)
			return (0);
	if (!cmd->fd_out)
		if (dup2(pipe_fd->new[1], STDOUT_FILENO) == -1)
			return (0);
	close_pipe_fd(pipe_fd->old);
	close_pipe_fd(pipe_fd->new);
	return (1);
}

int	dup_last(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (!cmd->fd_in && !cmd->heredoc)
		if (dup2(pipe_fd->old[0], STDIN_FILENO) == -1)
			return (0);
	close_pipe_fd(pipe_fd->old);
	return (1);
}
