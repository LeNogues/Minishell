/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:55:46 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/19 11:21:29 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static void	exec1(char *full_path, t_cmd *cmd, char **envp, t_pipe *pipe_fd)
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
	execve(full_path, cmd->cmd, envp);
	free_path_exec(full_path, cmd->cmd);
	exit(EXIT_FAILURE);
}

static void	exec2(char *full_path, t_cmd *cmd, char **envp, t_pipe *pipe_fd)
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
	execve(full_path, cmd->cmd, envp);
	free_path_exec(full_path, cmd->cmd);
	exit(EXIT_FAILURE);
}

void	execute_with_input(t_cmd *cmd, char **envp, t_pipe *pipe_fd)
{
	open_fd(cmd);
	exec1(cmd->full_path, cmd, envp, pipe_fd);
}

void	execute_middle(t_cmd *cmd, char *full_path, t_env *env, t_pipe *pipe_fd)
{
	open_fd(cmd);
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
		printf("test\n");
		dup2(pipe_fd->new[1], STDOUT_FILENO);
	}
	close(pipe_fd->old[0]);
	close(pipe_fd->old[1]);
	close(pipe_fd->new[1]);
	close(pipe_fd->new[0]);
	if (execve(full_path, cmd->cmd, env->envp) == -1)
		perror("execve middle commande");
	free_path_exec(full_path, cmd->cmd);
	exit(EXIT_FAILURE);
}

void	execute_with_output(t_cmd *cmd, char **envp, t_pipe *pipe_fd)
{
	open_fd(cmd);
	exec2(cmd->full_path, cmd, envp, pipe_fd);
}
