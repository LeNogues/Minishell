/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:53:42 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/29 16:41:50 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exec(t_cmd *cmd, t_env *env, t_cmd *cmd_origin)
{
	t_pipe	*pipe_fd;

	pipe_fd = malloc(sizeof(t_pipe) * 1);
	if (pipe(pipe_fd->old) == -1)
		return ;
	if (!do_cmd(cmd, cmd_origin, env, pipe_fd))
		return ;
	while (waitpid(0, NULL, 0) != -1)
		;
	return ;
}
