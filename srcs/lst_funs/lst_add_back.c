/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:59:17 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:36:52 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	lst_add_back_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = lst_last_token(*lst);
		new->previous = tmp;
		tmp->next = new;
	}
}

void	lst_add_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = lst_last_env(*lst);
		new->previous = tmp;
		tmp->next = new;
	}
}

void	lst_add_back_cmd_line(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = lst_last_cmd_line(*lst);
		tmp->next = new;
	}
}
