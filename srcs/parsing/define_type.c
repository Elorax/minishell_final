/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:27 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 09:00:28 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

static void choose_type(t_token *token)
{
    if (ft_strcmp(token->word, ">") == 0)
        token->type = FILE_OUT;
    else if (ft_strcmp(token->word, "<") == 0)
        token->type = FILE_IN;
    else if (ft_strcmp(token->word, ">>") == 0)
        token->type = FILE_OUT_APPEND;
    else if (ft_strcmp(token->word, "<<") == 0)
        token->type = HERE_DOC;
    else if (token->previous && token->previous->type)
    {
        if (token->previous->type == FILE_IN)
            token->type = OPEN_FILE;
        else if (token->previous->type == HERE_DOC)
            token->type = LIMITOR;
        else if (token->previous->type == FILE_OUT)
            token->type = EXIT_FILE;
        else if (token->previous->type == FILE_OUT_APPEND)
            token->type = EXIT_FILE_APPEND;
		else
			token->type = ARG;
    }
    else
        token->type = ARG;
}

void	define_type(t_cmd_line *lst)
{
	t_token *tkn_cursor;

	if (!lst)
		return ;
	while (lst)
	{
		tkn_cursor = lst->token;
		while (tkn_cursor)
		{
			choose_type(tkn_cursor);
			tkn_cursor = tkn_cursor->next;
		}
		lst = lst->next;
	}
}
