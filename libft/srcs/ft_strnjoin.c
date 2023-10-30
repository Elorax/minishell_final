/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:53:23 by lea               #+#    #+#             */
/*   Updated: 2023/03/30 10:21:47 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

//si on envoie 1 on free s1
//si on envoie 2 on free s2
//si on envoie 3 on free les 2
char	*ft_strnjoin(char *s1, char *s2, size_t n, int to_free)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!s1)
		return (ft_strndup(s2, n));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n > s2_len)
		n = s2_len;
	new_str = malloc(sizeof(char) * (s1_len + n + 1));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, s1, s1_len);
	ft_strncpy(new_str + s1_len, s2, n);
	if (to_free & 1)
		free(s1);
	if (to_free & 2)
		free(s2);
	new_str[s1_len + n] = '\0';
	return (new_str);
}
