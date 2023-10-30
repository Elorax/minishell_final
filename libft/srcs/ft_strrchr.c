/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:41:28 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:41:37 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*dest;

	dest = NULL;
	while (*s)
		if (*s++ == (char) c)
			dest = (char *)(s - 1);
	return (dest + (unsigned long)s * (!c));
}
