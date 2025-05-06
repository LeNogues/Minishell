/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:53:42 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 21:21:34 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	get_nb_heredoc(t_cmd *cmd)
{
	int i;
	int nb_heredoc;
	
	if (!cmd->in_or_out)
		return (0);
	i = 0;
	nb_heredoc = 0;
	while(cmd->in_or_out[i])
	{
		if (cmd->in_or_out[i] == HEREDOC)
			nb_heredoc++;
		i++;
	}
	return (nb_heredoc);
}

void	exec(t_info *info)
{
	t_pipe	*pipe_fd;
	int		status_fils;

	pipe_fd = malloc(sizeof(t_pipe) * 1);
	if (pipe(pipe_fd->old) == -1)
		return ;
	info->cmd->heredoc = get_nb_heredoc(info->cmd);
	if (!do_cmd(info, pipe_fd))
		return ;
	while (waitpid(info->last_pid, &status_fils, 0) != -1)
		;
	while (waitpid(0, NULL, 0) != -1)
		;
	info->return_value = WEXITSTATUS(status_fils);
	return ;
}
