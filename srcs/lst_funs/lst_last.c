/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:59:33 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:33:56 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

t_token	*lst_last_token(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*lst_last_env(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd_line	*lst_last_cmd_line(t_cmd_line *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
