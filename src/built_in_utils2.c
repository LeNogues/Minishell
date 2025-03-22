/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:44:33 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/22 15:11:36 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*create_new_path(t_env *env, char *path)
{
	char	*cwd;
	char	*temp;

	cwd = ft_getenv("PWD=", env);
	if (!cwd)
		return (perror("ft_getenv"), NULL);
	temp = ft_strjoin(cwd, "/");
	if (!temp)
		return (free(cwd), perror("ft_strjoin"), NULL);
	free(cwd);
	cwd = ft_strjoin(temp, path);
	if (!cwd)
		return (free(temp), free(path), perror("ft_strjoin"), NULL);
	free(path);
	free(temp);
	path = ft_strdup(cwd);
	if (!path)
		return (free(cwd), perror("ft_strdup"), NULL);
	free(cwd);
	return (path);
}

int	is_in_tab(char *str, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !cmd)
		return (0);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j++] == '=')
				return (0);
		}
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], str, ft_strlen(cmd[i]) + 1) == -61)
			return (1);
		i++;
	}
	return (0);
}
