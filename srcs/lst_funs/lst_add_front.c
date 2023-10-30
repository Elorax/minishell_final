/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:59:46 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 08:59:47 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	lst_add_front_token(t_token **lst, t_token *new)
{
	if (!new)
		return ;
	new->next = *lst;
	new->previous = NULL;
	*lst = new;
}

void	lst_add_front_env(t_env **lst, t_env *new)
{
	if (!new)
		return ;
	new->next = *lst;
	new->previous = NULL;
	*lst = new;
}

void	lst_add_front_cmd_line(t_cmd_line **lst, t_cmd_line *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
