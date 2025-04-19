/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/04/19 11:12:59 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	choice_of_builtin(t_cmd *cmd, t_env *env, t_cmd *cmd_origin, t_pipe *pipe_fd)
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

t_cmd	*lexer()
{
	t_cmd	*cmd0;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	t_cmd	*cmd3;

	cmd3 = NULL;

	cmd2 = malloc(sizeof(t_cmd) * 1);
	cmd2->cmd = ft_split("cat", ' ');
	cmd2->name_in =  NULL;
	cmd2->name_out = ft_strdup("cmd2.txt");
	cmd2->limiter = NULL;
	cmd2->append = 1;
	cmd2->pipe = 1;
	cmd2->fd_in = 0;
	cmd2->fd_out = 0;
	cmd2->nb_cmd = 3;
	cmd2->full_path = NULL;
	cmd2->next = cmd3;

	cmd1 = malloc(sizeof(t_cmd) * 1);
	cmd1->cmd = ft_split("wc -l", ' ');
	cmd1->name_in = NULL;
	cmd1->name_out = NULL;
	cmd1->limiter = NULL;
	cmd1->append = 1;
	cmd1->pipe = 1;
	cmd1->fd_in = 0;
	cmd1->fd_out = 0;
	cmd1->nb_cmd = 3;
	cmd1->full_path = NULL;
	cmd1->next = cmd2;

	cmd0 = malloc(sizeof(t_cmd) * 1);
	cmd0->cmd = ft_split("cat", ' ');
	cmd0->name_in = ft_strdup("test.txt");
	cmd0->name_out = NULL;
	cmd0->limiter = NULL;
	cmd0->append = 1;
	cmd0->pipe = 1;
	cmd0->fd_in = 0;
	cmd0->fd_out = 0;
	cmd0->nb_cmd = 3;
	cmd0->full_path = NULL;
	cmd0->next = cmd1;


	return (cmd0);
}

void	hub(t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*cmd_origin;
	char	*line;

	while (1)
	{
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
			free_cmd(cmd_origin);
		}
	}
}
