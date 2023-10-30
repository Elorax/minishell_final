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

//peut aller dans un utils
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

//Split une string en tokens en prenant en compte les quotes.
t_token	*split_token(char *str)
{
	t_token *dest;
	char	*tmp;
	char	type;
	char	quoted;

	quoted = 0;
	if (!str)
		return (NULL);
	if (!*str)
		return (lst_new_token(""));	//Peut etre NULL
	type = type_of_char(*str, &quoted);
	tmp = str;
	dest = NULL;
	while (*str)
	{
		if (type == CLASSIC_CHAR)
		{
			tmp = str;
			while (*(++str) && (type_of_char(*str, &quoted) == CLASSIC_CHAR || quoted))
				;
			lst_add_back_token(&dest, lst_new_n_token(tmp, str - tmp));
		}
		else if (type == LEFT_CHEVRON)
		{
			if (*++str && type_of_char(*str, &quoted) == LEFT_CHEVRON)
			{
				lst_add_back_token(&dest, lst_new_token("<<"));
				str++;
			}
			else
				lst_add_back_token(&dest, lst_new_token("<"));
		}
		else if (type == RIGHT_CHEVRON)
		{
			if (*++str && type_of_char(*str, &quoted) == RIGHT_CHEVRON)
			{
				lst_add_back_token(&dest, lst_new_token(">>"));
				str++;
			}
			else
				lst_add_back_token(&dest, lst_new_token(">"));
		}
		type = type_of_char(*str, &quoted);
	}
	return (dest);
}


//insere la liste chainee to_insert apres token
//en assurant la liaison entre to_insert et la suite de token

void	lst_insert_token(t_token *token, t_token *to_insert)
{
	t_token	*tmp;

	if (!token)
	{
		printf("cas a la con !\n");
		return ;
	}
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

//fonction temporaire de debug
void	lst_print_tokens(t_token *token)
{
	int	i = 0;
	while (token)
	{
		printf("%d : %s\n", ++i, token->word);
		token = token->next;
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
		//On est dans le cas ou deux pipes d'affilee
		printf("blabla unexpected token near |\n");
		return (SYNTAX_ERROR);
	}
	i = 0;
	while (tokens[++i])
		lst_add_back_token(&cmd_line->token, lst_new_token(tokens[i]));
	split_tokens(&cmd_line->token);
	ft_freesplit(tokens);
	return (0);
}
