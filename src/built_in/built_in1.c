/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/04/29 19:14:41 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	choice_of_builtin(t_cmd *cmd, t_env *env, t_cmd *cmd_origin,
		t_pipe *pipe_fd)
{
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (ft_cd(cmd->cmd, env), 1);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (ft_pwd(env), 1);
	else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (ft_echo(cmd), 1);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		return (ft_env(env), 1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (ft_unset(cmd->cmd, env), 1);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (ft_export(cmd->cmd, env), 1);
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		ft_exit(cmd_origin, env, pipe_fd);
	return (0);
}

t_cmd	*lexer(void)
{
	t_cmd	*cmd0;
	// t_cmd	*cmd1;
	t_cmd	*cmd2;

	cmd2 = NULL;

	cmd0 = malloc(sizeof(t_cmd) * 1);
	cmd0->cmd = ft_split("wc -l", ' ');
	cmd0->name = ft_split("EOF CAT input.txt output.txt", ' ');
	cmd0->in_or_out = malloc(sizeof(int) * 4);
	cmd0->in_or_out[0] = HEREDOC;
	cmd0->in_or_out[1] = HEREDOC;
	cmd0->in_or_out[2] = INPUT;
	cmd0->in_or_out[3] = OUTPUT_APPEND;
	cmd0->heredoc = 2;
	cmd0->pos = 1;
	cmd0->pipe = 1;
	cmd0->fd_in = 0;
	cmd0->fd_out = 0;
	cmd0->nb_cmd = 1;
	cmd0->full_path = NULL;
	cmd0->next = cmd2;
	
	return (cmd0);
}

void	hub(t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*cmd_origin;
	char	*line;

	while (1)
	{
		g_state_signal = 1;
		line = readline("\001\e[32m\002Minishell : \001\e[0m\002");
		if (!line)
			return ;
		if (line[0] != 0)
		{
			add_history(line);
			cmd = lexer();
			cmd_origin = cmd;
			free(line);
			exec(cmd, env, cmd_origin);
			free_all_cmd(cmd_origin);
		}
	}
}
