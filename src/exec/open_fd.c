/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:27:23 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 20:56:10 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	open_in(t_cmd *cmd, char *name)
{
	cmd->fd_in = open(name, O_RDONLY);
	if (cmd->fd_in == -1)
		return (0);
	if (!dup_fd_in(cmd))
		return (0);
	return (1);
}

int	open_out(t_cmd *cmd, char *name, int type)
{
	if (type == 2)
		cmd->fd_out = open(name, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		cmd->fd_out = open(name, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (cmd->fd_out == -1)
		return (0);
	if (!dup_fd_out(cmd))
		return (0);
	return (1);
}
