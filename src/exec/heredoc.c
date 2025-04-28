/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:29:05 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/27 16:12:38 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	open_heredoc(t_cmd *cmd, char *limiter, t_pipe *pipe_fd)
{
	char	*line;

	g_state_signal = 3;
	pipe(pipe_fd->heredoc);
	while (g_state_signal == 3)
	{
		line = readline("heredoc > ");
		if (!line)
			return (0);
		if (g_state_signal == 4)
			return (0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			return (0);
		}
		ft_putstr_fd(line, pipe_fd->heredoc[1]);
		ft_putstr_fd("\n", pipe_fd->heredoc[1]);
		free(line);
	}
	return (1);
}
