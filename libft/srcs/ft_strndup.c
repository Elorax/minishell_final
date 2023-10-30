/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:28:23 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 10:16:39 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * n + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, src, n);
	new_str[n] = '\0';
	return (new_str);
}
