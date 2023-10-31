/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 06:59:03 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 06:59:05 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

//insere la liste chainee to_insert apres token
//en assurant la liaison entre to_insert et la suite de token

void	lst_insert_token(t_token *token, t_token *to_insert)
{
	t_token	*tmp;

	if (!token)
		return ;
	if (!to_insert)
		return ;
	tmp = token->next;
	token->next = to_insert;
	to_insert->previous = token;
	if (tmp)
		tmp->previous = lst_last_token(to_insert);
	lst_last_token(to_insert)->next = tmp;
}

//delone le token pointe, en assurant la liaison entre le previous et le next
//Met a jour l'adresse du premier maillon si pas de previous

void	lst_remove_token(t_token **token)
{
	t_token	*tmp;

	tmp = NULL;
	if (!token || !*token)
		return ;
	if ((*token)->next)
		(*token)->next->previous = (*token)->previous;
	if (!(*token)->previous)
	{
		tmp = (*token)->next;
		lst_delone_token(*token);
		*token = tmp;
	}
	else
	{
		(*token)->previous->next = (*token)->next;
		lst_delone_token(*token);
	}
}

void	split_tokens(t_token **token)
{
	t_token	*cursor;
	t_token	*new_tokens;
	t_token	*next_cursor;

	new_tokens = NULL;
	cursor = *token;
	while (cursor)
	{
		next_cursor = cursor->next;
		if (ft_strchr(cursor->word, '<') || ft_strchr(cursor->word, '>'))
		{
			new_tokens = split_token(cursor->word);
			if (new_tokens != NULL)
				lst_insert_token(cursor, new_tokens);
			if (cursor == *token)
			{
				*token = cursor->next;
				cursor->next->previous = NULL;
				lst_delone_token(cursor);
			}
			else
				lst_remove_token(&cursor);
		}
		cursor = next_cursor;
	}
}

int	lst_create_tokens(t_cmd_line *cmd_line)
{
	char	**tokens;
	int		i;

	tokens = ft_split_quoted(cmd_line->cmd, " \t");
	if (!tokens)
		return (MALLOC_ERROR);
	if (*tokens)
		cmd_line->token = lst_new_token(tokens[0]);
	else
	{
		printf("bash: syntax error near unexpected token \'|\'\n");
		return (SYNTAX_ERROR);
	}
	i = 0;
	while (tokens[++i])
		lst_add_back_token(&cmd_line->token, lst_new_token(tokens[i]));
	split_tokens(&cmd_line->token);
	ft_freesplit(tokens);
	return (0);
}
