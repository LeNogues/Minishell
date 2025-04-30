/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:50:51 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/29 14:37:57 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	first_cmd(t_cmd *cmd, t_cmd *cmd_origin, t_env *env, t_pipe *pipe_fd)
{
	handle_cmd(cmd, env, pipe_fd, cmd_origin);
	if (cmd->next)
		cmd = cmd->next;
	else
	{
		wait(0);
		free(pipe_fd);
		return (1);
	}
	return (1);
}
