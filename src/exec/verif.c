/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:28:19 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/04/23 11:30:15 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	verif_infile(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "file not found or open\n", 23);
		return (-1);
	}
	close(fd);
	return (1);
}
