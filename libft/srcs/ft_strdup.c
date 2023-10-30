/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:39:34 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:39:48 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	len = ft_strlen(s);
	dest = (char *) malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (*s)
		*dest++ = *s++;
	*dest = 0;
	return (dest - len);
}
