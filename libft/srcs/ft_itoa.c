/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:27:52 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:28:09 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_itoa(int n)
{
	int				i;
	char			*dest;
	unsigned int	cpy;

	i = (n < 0);
	cpy = (n * (1 - (2 * (n < 0))));
	while (cpy > 9)
		cpy = (i++, cpy / 10);
	dest = (char *) ft_calloc(i + 2, sizeof(char));
	if (!dest)
		return (NULL);
	dest[0] = '-' + 3 * (n == 0);
	cpy = (n * (1 - (2 * (n < 0))));
	while (cpy > 0)
	{
		dest[i--] = (cpy % 10) + '0';
		cpy /= 10;
	}
	return (dest);
}
