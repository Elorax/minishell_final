/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:28:53 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:29:24 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

/*  Retourne le nombre d'arguments d'une ligne de commande. */
int	lst_size(t_cmd_line *cmd_line)
{
	t_token	*token;
	int		i;

	i = 0;
	token = cmd_line->token;
	while (token)
	{
		if (token->type == ARG)
			i++;
		token = token->next;
	}
	return (i);
}

int	lst_cmd_size(t_cmd_line *cmd_line)
{
	t_cmd_line	*token;
	int			i;

	i = 0;
	token = cmd_line;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}
