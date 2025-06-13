/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: othmaneettaqi <othmaneettaqi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:25:32 by othmaneetta       #+#    #+#             */
/*   Updated: 2025/06/13 17:29:56 by othmaneetta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	advance_heredoc_token_and_ws(t_token **p_parcours)
{
	*p_parcours = (*p_parcours)->next;
	while (*p_parcours && (*p_parcours)->type == WHITESPACE)
		*p_parcours = (*p_parcours)->next;
}
