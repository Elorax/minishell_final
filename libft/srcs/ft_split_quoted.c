/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:02:41 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/31 15:37:09 by abiersoh         ###   ########.fr       */
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
	int		nb_w;
	char	quote;

	nb_w = ((quote = 0), 0);
	while (*str)
	{
		while (*str && ft_is_char_in_base(*str, charset))
			str++;
		if (*str)
			nb_w++;
		while (*str && !ft_is_char_in_base(*str, charset))
		{
			quote = define_quote(*str, quote);
			if (quote != 0)
			{
				if (!ft_strchr(++str, quote))
					return (ft_printf("syntax error !\n"), -1);
				else
					while (*str != quote)
						str++;
			}
			str = ((quote = 0), str + 1);
		}
	}
	return (nb_w);
}

static int	ft_nb_char(char *str, char *charset)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i] && !(ft_is_char_in_base(str[i], charset)))
	{
		if (str[i] == '\"')
			quote = DOUBLE;
		if (str[i] == '\'')
			quote = SIMPLE;
		if (quote != 0)
		{
			i++;
			while (str[i] != quote)
				i++;
		}
			i++;
		quote = 0;
	}
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

char	**ft_split_quoted(char *str, char *charset)
{
	char	**dest;
	int		i;
	int		j;
	int		size;

	size = ft_nb_words(str, charset);
	if (size == -1)
		return (NULL);
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
			return ((ft_freesplit(dest), NULL));
		}
		j += ft_nb_char(&str[j], charset);
	}
	return (dest);
}
