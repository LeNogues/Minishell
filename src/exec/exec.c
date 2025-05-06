/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:53:42 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 20:56:25 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exec(t_info *info)
{
	t_pipe	*pipe_fd;
	int		status_fils;

	pipe_fd = malloc(sizeof(t_pipe) * 1);
	if (pipe(pipe_fd->old) == -1)
		return ;
	if (!do_cmd(info, pipe_fd))
		return ;
	while (waitpid(info->last_pid, &status_fils, 0) != -1)
		;
	while (waitpid(0, NULL, 0) != -1)
		;
	info->return_value = WEXITSTATUS(status_fils);
	return ;
}
