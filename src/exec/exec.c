/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:53:42 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/23 11:29:19 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	first_cmd(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	if (verif_infile(cmd->name_in) != -1)
	{
		if (!handle_cmd1_2(cmd, env, pipe_fd, cmd_origin, 1))
			return (0);
		if (cmd->next)
			cmd = cmd->next;
		else
		{
			wait(0);
			free(pipe_fd);
			return (1);
		}
	}
	return (1);
}

void	exec(t_cmd *cmd, t_env *env, t_cmd *cmd_origin)
{
	t_pipe	*pipe_fd;

	pipe_fd = malloc(sizeof(t_pipe) * 1);
	if (pipe(pipe_fd->old) == -1)
		return ;
	if (!first_cmd(cmd, cmd_origin, env, pipe_fd))
		return ;
	loop_on_middle(cmd, env, pipe_fd, cmd_origin);
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->nb_cmd >= 2)
		if (!handle_cmd1_2(cmd, env, pipe_fd, cmd_origin, 2))
			return ;
	close_pipe_fd(pipe_fd->old);
	free(pipe_fd);
	while (waitpid(0, NULL, 0) != -1)
		;
	return ;
}
