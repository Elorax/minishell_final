/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:44 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 09:00:45 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

static char	type_of_char(char c, char *quoted)
{
	if (*quoted && c == *quoted)
	{
		*quoted = 0;
		return (CLASSIC_CHAR);
	}
	if (!*quoted && (c == SIMPLE || c == DOUBLE))
	{
		*quoted = c;
		return (CLASSIC_CHAR);
	}
	if (c == '<')
		return (LEFT_CHEVRON);
	if (c == '>')
		return (RIGHT_CHEVRON);
	return (CLASSIC_CHAR);
}

int	split_token_2(char type, char *str, char *quoted, t_token **dest)
{
	char	*tmp;

	tmp = str;
	if (type == LEFT_CHEVRON)
	{
		if (*++str && type_of_char(*str, quoted) == LEFT_CHEVRON)
		{
			lst_add_back_token(dest, lst_new_token("<<"));
			str++;
		}
		else
			lst_add_back_token(dest, lst_new_token("<"));
	}
	else if (type == RIGHT_CHEVRON)
	{
		if (*++str && type_of_char(*str, quoted) == RIGHT_CHEVRON)
		{
			lst_add_back_token(dest, lst_new_token(">>"));
			str++;
		}
		else
			lst_add_back_token(dest, lst_new_token(">"));
	}
	return (str - tmp);
}

char	*split_token_init(t_token **dest, char *type, char *quoted, char *str)
{
	*dest = NULL;
	*quoted = 0;
	*type = type_of_char(*str, quoted);
	return (str);
}

//Split une string en tokens en prenant en compte les quotes.

t_token	*split_token(char *str)
{
	t_token	*dest;
	char	*tmp;
	char	type;
	char	quoted;

	if (!str)
		return (NULL);
	if (!*str)
		return (lst_new_token(""));
	tmp = split_token_init(&dest, &type, &quoted, str);
	while (*str)
	{
		if (type == CLASSIC_CHAR)
		{
			tmp = str;
			while (*(++str)
				&& (type_of_char(*str, &quoted) == CLASSIC_CHAR || quoted))
				;
			lst_add_back_token(&dest, lst_new_n_token(tmp, str - tmp));
		}
		else
			str += split_token_2(type, str, &quoted, &dest);
		type = type_of_char(*str, &quoted);
	}
	return (dest);
}
