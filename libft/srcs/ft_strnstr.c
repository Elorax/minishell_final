/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:41:21 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:41:24 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	find_len;

	if (!str || !tofind)
		return (NULL);
	find_len = ft_strlen(tofind);
	if (!(*tofind))
		return ((char *)str);
	if (find_len > len)
		return (NULL);
	j = 0;
	while (str[j] && j <= (len - find_len))
	{
		i = 0;
		while (str[i + j] && (str[i + j] == tofind[i]))
		{
			i++;
			if (!(tofind[i]))
				return ((char *) str + j);
		}
		j++;
	}
	return (NULL);
}
