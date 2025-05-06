/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:30:20 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/05/06 20:40:57 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	cd_home(t_env *env, char **path)
{
	char	*env_line;

	env_line = ft_getenv("HOME=", env);
	if (!env_line)
		env_line = NULL;
	*path = ft_strdup(env_line);
	if (!*path)
	{
		free(*path);
		free(env_line);
		return (write(1, "HOME not set\n", 13), 0);
	}
	free(env_line);
	return (1);
}

char	*get_parent(t_env *env)
{
	int		last;
	int		i;
	char	*old_pwd;
	char	*temp_pwd;
	char	*new_pwd;

	i = 0;
	last = 0;
	old_pwd = ft_getenv("PWD=", env);
	while (old_pwd[i])
	{
		if (old_pwd[i] == '/')
			last = i;
		i++;
	}
	i = -1;
	temp_pwd = malloc(sizeof(char) * (last));
	while (++i < last)
		temp_pwd[i] = old_pwd[i];
	temp_pwd[i] = 0;
	new_pwd = ft_strjoin("PWD=", temp_pwd);
	free(old_pwd);
	free(temp_pwd);
	return (new_pwd);
}
