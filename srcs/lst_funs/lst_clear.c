/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:59:25 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:35:58 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	lst_clear_token(t_token **lst)
{
	t_token	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		lst_delone_token(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	lst_clear_env(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		lst_delone_env(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	lst_clear_cmd_line(t_cmd_line **lst)
{
	t_cmd_line	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		lst_delone_cmd_line(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
