/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:24:32 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 16:24:36 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	define_quote(char c, char quote)
{
	if (c == '\"')
		return (DOUBLE);
	if (c == '\'')
		return (SIMPLE);
	return (quote);
}
