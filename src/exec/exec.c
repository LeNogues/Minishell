/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:53:42 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/02 17:39:10 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	execute_middle(t_cmd *cmd, char *full_path, t_env *env, t_pipe pipe_fd)
{
	(void)pipe_fd;
	if (cmd->fd_in)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			// close_all(pipe_fd);
			free_path_exec(full_path, (*cmd).cmd);
			exit(EXIT_FAILURE);
		}
		// close(pipe_fd.old[0]);
		// close(pipe_fd.old[1]);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			// close_all(pipe_fd);
			free_path_exec(full_path, (*cmd).cmd);
			exit(EXIT_FAILURE);
		}
		// close(pipe_fd.new[1]);
		// close(pipe_fd.new[0]);
		close(cmd->fd_out);
	}
	if (execve(full_path, (*cmd).cmd, env->envp) == -1)
	{
		perror("execve deuxieme commande");
		return ;
	}
	free_path_exec(full_path, (*cmd).cmd);
	exit(EXIT_FAILURE);
}

int	exec(t_cmd cmd, t_env *env)
{
	t_pipe pipe_fd;

	(void)cmd;
	(void)env;
	(void)pipe_fd;
	// if (pipe(pipe_fd.old) == -1)
	//     return (-3);
	exec_loop(&cmd, env, &pipe_fd);
	// while (waitpid(0, NULL, 0) != -1)
	// 	;
	return (1);
}
