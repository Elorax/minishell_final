/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:57 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 10:17:22 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_nb_words(char const *s, char c)
{
	int	i;
	int	nb_w;

	i = 0;
	nb_w = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			nb_w++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_w);
}

static int	ft_nb_char(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*
static char	*ft_strndup(char const *s, int n)
{
	char	*dest;
	int		i;

	i = -1;
	dest = (char *) malloc (sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (++i < n)
		dest[i] = s[i];
	dest[i] = 0;
	return (dest);
}
*/

void	ft_blabla(char **s, int i)
{
	while (--i >= 0)
		free(s[i]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		nb_w;
	int		i;

	i = -1;
	nb_w = ft_nb_words(s, c);
	dest = (char **) malloc (sizeof(char *) * (nb_w + 1));
	if (!dest)
		return (NULL);
	while (++i < nb_w)
	{
		while (*s && *s == c)
			s++;
		dest[i] = ft_strndup(s, ft_nb_char(s, c));
		if (!dest[i])
		{
			ft_blabla(dest, i);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
	}
	dest[i] = 0;
	return (dest);
}
