/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:55:46 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/20 13:27:27 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	dup_first(t_cmd *cmd, t_pipe *pipe_fd)
{
	close(pipe_fd->old[0]);
	if(cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else
		dup2(pipe_fd->old[1], STDOUT_FILENO);
	if(cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	close(pipe_fd->old[1]);
}

void	dup_middle(t_cmd *cmd, t_pipe *pipe_fd)
{
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
		dup2(pipe_fd->old[0], STDIN_FILENO);
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else
	{
		dup2(pipe_fd->new[1], STDOUT_FILENO);
	}
	close(pipe_fd->old[0]);
	close(pipe_fd->old[1]);
	close(pipe_fd->new[1]);
	close(pipe_fd->new[0]);	
}

void	dup_last(t_cmd *cmd, t_pipe *pipe_fd)
{
	close(pipe_fd->old[1]);
	if(cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
	{
		dup2(pipe_fd->old[0], STDIN_FILENO);
	}
	close(pipe_fd->old[0]);
	if(cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	execute(t_cmd *cmd, char **envp)
{
	execve(cmd->full_path, cmd->cmd, envp);
	free_path_exec(cmd->full_path, cmd->cmd);
	exit(EXIT_FAILURE);
}


