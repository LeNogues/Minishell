/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:28 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/05 17:34:49 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	do_cmd(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	first_cmd(cmd, cmd_origin, env, pipe_fd);
	if (!loop_on_middle(cmd, env, pipe_fd, cmd_origin))
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->nb_cmd >= 2)
	{
		if (!handle_cmd(cmd, env, pipe_fd, cmd_origin))
			return (0);
	}
	if (cmd->nb_cmd > 1)
	{
		close_pipe_fd(pipe_fd->old);
		free(pipe_fd);
	}
	return (1);
}
