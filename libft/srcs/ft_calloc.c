/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:29:39 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:29:40 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	*ft_calloc(size_t nbelem, size_t size)
{
	void	*dest;

	dest = malloc(nbelem * size);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, nbelem * size);
	return (dest);
}
