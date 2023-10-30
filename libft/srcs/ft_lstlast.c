/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:33:06 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:33:07 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*l;

	if (!lst)
		return (NULL);
	l = lst;
	while (l->next)
		l = l->next;
	return (l);
}
