/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:53:42 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/21 15:38:54 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	open_fd(t_cmd *cmd)
{
	if (cmd->name_in)
	{
		cmd->fd_in = open(cmd->name_in, O_RDONLY);
		if (cmd->fd_in == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd->name_out && cmd->append == 0)
	{
		cmd->fd_out = open(cmd->name_out, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (cmd->fd_out == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd->name_out && cmd->append == 1)
	{
		cmd->fd_out = open(cmd->name_out, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (cmd->fd_out == -1)
			exit(EXIT_FAILURE);
	}
	return (0);
}

int	exec(t_cmd *cmd, t_env *env, t_cmd *cmd_origin)
{
	t_pipe	*pipe_fd;
	int 	result;

	pipe_fd = malloc(sizeof(t_pipe) * 1);
	if (pipe(pipe_fd->old) == -1)
	    return (-3);
	if (verif_infile(cmd->name_in) != -1)
	{
		result = handle_cmd1_2(cmd, env, pipe_fd, cmd_origin, 1);
		if (result != 0)
			return (result);
		if(cmd->next)
			cmd = cmd->next;
		else
		{
			wait(0);
			free(pipe_fd);
			return (1);
		}
	}
	loop_on_middle(cmd, env, pipe_fd, cmd_origin);
	while(cmd->next)
	{
		cmd = cmd->next;
	}
	if (cmd->nb_cmd >= 2)
	{
		result = handle_cmd1_2(cmd, env, pipe_fd, cmd_origin, 2);
		if (result != 0)
			return (result);
	}
	close(pipe_fd->old[0]);
	close(pipe_fd->old[1]);
	while (waitpid(0, NULL, 0) != -1)
		;
	free(pipe_fd);
	return (1);
}
