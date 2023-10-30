/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:11:15 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 10:16:33 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_is_char_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
		if (base[i++] == c)
			return (1);
	return (0);
}

static int	ft_nb_words(char *str, char *charset)
{
	int	nb_w;

	nb_w = 0;
	while (*str)
	{
		while (*str && ft_is_char_in_base(*str, charset))
			str++;
		if (*str)
			nb_w++;
		while (*str && !ft_is_char_in_base(*str, charset))
			str++;
	}
	return (nb_w);
}

static int	ft_nb_char(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !(ft_is_char_in_base(str[i], charset)))
		i++;
	return (i);
}

static char	*ft_cpyalloc(char *src, unsigned int nb_char)
{
	unsigned int	i;
	char			*dest;

	i = 0;
	dest = malloc(sizeof (char) * (nb_char + 1));
	if (!dest)
		return (NULL);
	dest[nb_char] = 0;
	while (i < nb_char)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	**ft_split_str(char *str, char *charset)
{
	char	**dest;
	int		i;
	int		j;
	int		size;

	size = ft_nb_words(str, charset);
	dest = ft_calloc(sizeof (char *), size + 1);
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < size)
	{
		while (str[j] && ft_is_char_in_base(str[j], charset))
			j++;
		dest[i] = ft_cpyalloc(&str[j], ft_nb_char(&str[j], charset));
		if (!dest[i])
		{
			ft_freesplit(dest);
			return (NULL);
		}
		j += ft_nb_char(&str[j], charset);
	}
	return (dest);
}
