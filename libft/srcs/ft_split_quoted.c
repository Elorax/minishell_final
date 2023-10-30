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
	int	nb_w;
    char quote;

    quote = 0;
	nb_w = 0;
//	ft_printf("debug : ->%s<-\n", str);
	while (*str)
	{
		while (*str && ft_is_char_in_base(*str, charset))
		{	
            str++;
        }
		if (*str)
			nb_w++;
		while (*str && !ft_is_char_in_base(*str, charset))
		{
			if (*str == '\"')
				quote = DOUBLE;
			if (*str == '\'')
				quote = SIMPLE;
			if (quote != 0)
			{
				str++;
			//	ft_printf("apres quote : %s\n", str);
				if (!ft_strchr(str, quote))
				{
					ft_printf("syntax error !!\n");//ptete des trucs a faire
					//maybe some things to do before the return
					return (-1);
				}
				else
				{
					while (*str != quote)
						str++;
				}
			//	ft_printf("fin de quote : %s\n", str);
			}
			str++;
			quote = 0;
		}
	}
	return (nb_w);
}


static int	ft_nb_char(char *str, char *charset)
{
	int	 i;
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
			//ft_printf("--apres quote : %s\n", str + i);
			if (!ft_strchr(str + i, quote))
			{
				//En theorie ca trigger jamais, on a deja quitte la fonction dans ce cas ci
			}
			while (str[i]!= quote)
				i++;
			//ft_printf("--fin de quote : %s\n", str + i);
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
			ft_freesplit(dest);
			return (NULL);
		}
		j += ft_nb_char(&str[j], charset);
	}
	return (dest);
}
