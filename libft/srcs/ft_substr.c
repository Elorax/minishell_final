/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:42:02 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:42:06 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	size;

	i = 0;
	if (ft_strlen(s) < start)
		size = 0;
	else
		size = min(ft_strlen(s) - start, len);
	dest = (char *)malloc (sizeof (char) * (size + 1));
	if (!dest)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		dest[0] = 0;
		return (dest);
	}
	while ((i < size) && s[i + start])
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
