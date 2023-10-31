/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:32:18 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 08:32:19 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

int	expand_token(t_token *token, t_env *env, int pwd_displayable)
{
	char	*tmp;

	tmp = NULL;
	if (token->type == ARG || token->type == OPEN_FILE
		|| token->type == EXIT_FILE || token->type == EXIT_FILE_APPEND)
	{
		tmp = expand_word(token, env, pwd_displayable);
		if (!tmp)
			return (MALLOC_ERROR);
		lst_replace_tkn_word(token, tmp);
		free(tmp);
	}
	return (0);
}

int	expand(t_cmd_line *cmd_line, t_env *env, int pwd_displayable)
{
	t_token	*cursor;

	while (cmd_line)
	{
		cursor = cmd_line->token;
		while (cursor)
		{
			if (expand_token(cursor, env, pwd_displayable) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			cursor = cursor->next;
		}
		cmd_line = cmd_line->next;
	}
	return (0);
}
