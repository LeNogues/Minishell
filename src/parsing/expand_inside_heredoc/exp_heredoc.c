/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:15:05 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/06/13 17:34:30 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static char	*append_char(char *s, char c)
{
	size_t	len;
	char	*new;

	if (s == NULL)
		len = 0;
	else
		len = ft_strlen(s);
	new = malloc(len + 2);
	if (new == NULL)
		return (NULL);
	if (s != NULL)
		ft_memcpy(new, s, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

static char	*expand_status(char *out, t_info *info)
{
	char	*sts;
	char	*tmp;

	sts = ft_itoa(info->return_value);
	if (sts == NULL)
	{
		free(out);
		return (NULL);
	}
	tmp = ft_strjoin(out, sts);
	free(out);
	free(sts);
	return (tmp);
}

static char	*expand_variable(char *out, char *line, size_t *i, t_info *info)
{
	size_t	start;
	char	*name;
	char	*val;
	char	*tmp;

	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	name = ft_substr(line, start, *i - start);
	if (!name)
	{
		free(out);
		return (NULL);
	}
	val = ft_getenv_bis(name, info->env);
	if (val == NULL)
		val = "";
	tmp = ft_strjoin(out, val);
	free(out);
	free(name);
	return (tmp);
}

static char	*handle_dollar_expansion(char *out, char *line, size_t *i, \
	t_info *info)
{
	(*i)++;
	if (line[*i] == '?')
	{
		out = expand_status(out, info);
		(*i)++;
	}
	else if (!ft_isalpha(line[*i]) && line[*i] != '_')
	{
		out = append_char(out, '$');
	}
	else
	{
		out = expand_variable(out, line, i, info);
	}
	return (out);
}

char	*expand_for_heredoc(char *line, t_info *info)
{
	size_t	i;
	char	*out;

	i = 0;
	out = ft_strdup("");
	if (!out)
		return (free(line), NULL);
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != '\0')
		{
			out = handle_dollar_expansion(out, line, &i, info);
			if (out == NULL)
				return (free(line), NULL);
		}
		else
		{
			out = append_char(out, line[i]);
			if (out == NULL)
				return (free(line), NULL);
			i++;
		}
	}
	free(line);
	return (out);
}
