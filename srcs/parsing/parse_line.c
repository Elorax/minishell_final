/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:39 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/12 16:42:48 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

void	stow_2(t_cmd_line *cmd, char **strs, t_token **cursor)
{
	int	i;

	i = str_count(strs);
	if (i > 1)
	{
		while (i >= 0)
		{
			lst_insert_token(*cursor, lst_new_token(strs[i]));
			i--;
		}
		if (!(*cursor)->previous)
			cmd->token = (*cursor)->next;
		lst_remove_token(cursor);
	}
}

void	stow_3(char **strs, t_token **cursor)
{
	int	i;

	i = 0;
	while (i < str_count(strs) - 1)
	{
		*cursor = (*cursor)->next;
		i++;
	}
	if (strs)
		ft_freesplit(strs);
	*cursor = (*cursor)->next;
}

void	split_tokens_on_whitespaces(t_cmd_line *cmd)
{
	char	**strs;
	t_token	*cursor;

	while (cmd)
	{
		cursor = cmd->token;
		while (cursor)
		{
			strs = ft_split_quoted(cursor->word, " \t");
			stow_2(cmd, strs, &cursor);
			stow_3(strs, &cursor);
		}
		cmd = cmd->next;
	}
}

char	*erase_quotes(char *word, int i, int j)
{
	char	quote;
	char	*dest;

	dest = malloc(ft_strlen(word) + 1);
	if (!dest)
		return (NULL);
	quote = 0;
	while (word[i])
	{
		if (word[i] == SIMPLE || word[i] == DOUBLE)
		{
			if (quote == word[i])
				quote = 0;
			else if (quote == 0)
				quote = word[i];
			else
				dest[j++] = word[i];
		}
		else
			dest[j++] = word[i];
		i++;
	}
	dest[j] = 0;
	free(word);
	return (dest);
}

void	remove_tokens_quotes(t_cmd_line *cmd)
{
	t_token	*cursor;
	size_t	i;

	i = 0;
	while (cmd)
	{
		cursor = cmd->token;
		while (cursor)
		{
			i = ft_strlen(cursor->word);
			if (!cursor->was_quoted)
			{
				printf("%s --> \n", cursor->word);
				cursor->word = erase_quotes(cursor->word, 0, 0);
				printf(" %s\n", cursor->word);
			}
			if (i != ft_strlen(cursor->word))
			{
				cursor->was_quoted = 1;
			}
			cursor = cursor->next;
		}
		cmd = cmd->next;
	}
}
