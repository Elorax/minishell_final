/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:19:33 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 07:19:34 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

void	trim_whitespaces(t_cmd_line *cmd)
{
	t_token	*cursor;
	char	*tmp;

	while (cmd)
	{
		cursor = cmd->token;
		while (cursor)
		{
			tmp = ft_strtrim(cursor->word, " \t");
			lst_replace_tkn_word(cursor, tmp);
			free(tmp);
			cursor = cursor->next;
		}
		cmd = cmd->next;
	}
}

void	remove_empty_tokens(t_cmd_line *cmd)
{
	t_token	*token;
	t_token	*mem;
	t_token	*mem2;

	token = cmd->token;
	mem = NULL;
	mem2 = NULL;
	while (token)
	{
		mem = token->next;
		mem2 = token;
		if ((!token->word || !*token->word) && !token->was_quoted)
		{
			lst_remove_token(&token);
			if (cmd->token == mem2)
				cmd->token = mem;
		}
		token = mem;
	}
}

int	parse_line_2(t_data *data)
{
	define_type(data->cmd);
	if (error_type(data->cmd) == 2)
		return (error(SYNTAX_ERROR, "<"));
	if (error_type(data->cmd) == 3)
		return (error(SYNTAX_ERROR, ">"));
	if (error_type(data->cmd) == 4)
		return (error(SYNTAX_ERROR, ">>"));
	if (error_type(data->cmd) == 5)
		return (error(SYNTAX_ERROR, "<<"));
	if (error_type(data->cmd) == 1)
		return (error(SYNTAX_ERROR, "newline"));
	if (error_type(data->cmd) == 6)
		return (error(SYNTAX_ERROR, "|"));
	expand(data->cmd, data->env, data->pwd_displayable);
	split_tokens_on_whitespaces(data->cmd);
	define_type(data->cmd);
	trim_whitespaces(data->cmd);
	remove_tokens_quotes(data->cmd);
	remove_empty_tokens(data->cmd);
	return (0);
}

int	parse_line(t_data *data)
{
	data->line = remove_whitespaces(data->line);
	if (!*data->line)
	{
		free(data->line);
		return (0);
	}
	if (!quotes_correct(data->line))
	{
		printf("syntax error: incomplete quotes\n");
		return (SYNTAX_ERROR);
	}
	if (syntax_pipes(data->line) != 0)
		return (SYNTAX_ERROR);
	if (create_cmd_line(data) != 0)
		return (SYNTAX_ERROR);
	return (parse_line_2(data));
}
