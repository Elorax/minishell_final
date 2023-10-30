/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:40:28 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:40:29 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lim;
	size_t	size_dest;

	size_dest = ft_strlen(dest);
	lim = size - size_dest - 1;
	if (size <= size_dest)
		return (size + ft_strlen(src));
	while (*dest)
		dest++;
	i = 0;
	while (i < lim && src[i])
		*dest++ = src[i++];
	if (size >= size_dest)
		*dest = 0;
	return (size_dest + ft_strlen(src));
}
