/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   built_in_utils2.c                                    ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2025/03/14 11:44:33 by sle-nogu             │││├─┤ │ ├─┤        */
/*   Updated: 2025/03/17 17:55:37 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

static long	convert_string_to_long(const char *str, long *result, int sign)
{
	long	check_overflow;

	check_overflow = 0;
	*result = 0;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10 + (*str - '0');
		if (*result < check_overflow)
			return (-1);
		check_overflow = *result;
		str++;
	}
	*result *= sign;
	return (1);
}

long	ft_atol(const char *str, long *result)
{
	int	sign;

	sign = 1;
	*result = 0;
	if (!str)
		return (1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (convert_string_to_long(str, result, sign) == -1)
		return (-1);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
	{
		*result = 2;
		return (-1);
	}
	return (1);
}

int	is_in_tab(char *str, char **cmd)
{
	int i;
	
	i = 0;
	if(!str || !cmd)
		return (0);
	
	while(cmd[i])
	{
		if(ft_strncmp(cmd[i], str, ft_strlen(cmd[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}
