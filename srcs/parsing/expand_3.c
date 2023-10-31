/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:32:24 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 08:32:25 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

int	is_char_valid(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

//remove les caracteres entre la position begin
//et la position end de la string str
//En renvoie une version allouee.
//begin compris, end non compris

char	*ft_strremove(char *str, size_t begin, size_t end)
{
	char	*dest;
	size_t	i;
	size_t	j;

	dest = malloc(ft_strlen(str) + 1);
	if (!dest)
	{
		error(MALLOC_ERROR, "expand.c : ft_strremove");
		return (NULL);
	}
	i = 0;
	while (str[i] && i < begin)
	{
		dest[i] = str[i];
		i++;
	}
	j = i;
	while (str[i] && i < end)
		i++;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = 0;
	return (dest);
}

//insere la string to_insert dans str
//a la place des caracteres entre begin et size.
//en renvoie une version allouee.

void	ft_strinsert_2(char *dest, char *tmp, char *to_insert, size_t begin)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tmp[i] && i < begin)
	{
		dest[i] = tmp[i];
		i++;
	}
	j = 0;
	while (to_insert[j])
		dest[i++] = to_insert[j++];
	j = i - j;
	while (tmp[j])
		dest[i++] = tmp[j++];
	dest[i] = 0;
}

char	*ft_strinsert(char *str, size_t begin, size_t end, char *to_insert)
{
	size_t	size;
	char	*dest;
	char	*tmp;

	tmp = ft_strremove(str, begin, end);
	if (!tmp)
		return (NULL);
	size = sizeof(char) * (ft_strlen(tmp) + ft_strlen(to_insert) + 1);
	dest = malloc(size);
	if (!dest)
	{
		error(MALLOC_ERROR, "expand.c : ft_strinsert");
		return (NULL);
	}
	ft_strinsert_2(dest, tmp, to_insert, begin);
	free(tmp);
	return (dest);
}

char	*remove_char_from_string(char *str, int i)
{
	int		j;
	int		k;
	char	*dest;

	j = 0;
	k = 0;
	dest = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[j])
	{
		if (j == i)
		{
			j++;
			continue ;
		}
		dest[k++] = str[j++];
	}
	free(str);
	return (dest);
}
