/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:52:45 by lbisson           #+#    #+#             */
/*   Updated: 2023/03/30 10:15:37 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strjoin(char *s1, char *s2, int to_free)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s2_len + 1);
	if (to_free & 1)
		free(s1);
	if (to_free & 2)
		free(s2);
	return (new_str);
}
