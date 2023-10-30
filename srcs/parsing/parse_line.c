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



//fonction temporaire de debug
void	display_cmd_line(t_cmd_line *cmd_line)
{
	t_cmd_line	*cmd_cursor;
	t_token		*tkn_cursor;

	cmd_cursor = cmd_line;
	while (cmd_cursor)
	{
		tkn_cursor = cmd_cursor->token;
		while (tkn_cursor)
		{
			printf("%s ; type = %d\n", tkn_cursor->word, tkn_cursor->type);
			tkn_cursor = tkn_cursor->next;
		}
		cmd_cursor = cmd_cursor->next;
		if (cmd_cursor)
			printf(" | \n");
	}
}

//fonction temporaire d'execute.
/*static void	execute_cmd_line(t_data *data)
{
	(void) data;
	printf("\\\\\\Ligne valide\\\\\\\n");
}*/


char	*remove_whitespaces(char *str)
{
	char	*dest;

	dest = ft_strtrim(str, " \t");
	free(str);
	return (dest);
}

int		fill_lst_cmd_line(t_cmd_line **cmd_line, char **cmds)
{
	int	i;
	t_cmd_line	*cursor;

	i = 1;
	while (cmds[i])
	{
		cursor = lst_new_cmd_line(cmds[i]);
		lst_add_back_cmd_line(cmd_line, cursor);
		if (lst_create_tokens(cursor) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		i++;
	}
	return (0);
}

int	quotes_correct(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (quote != 0)
		{
			if (str[i] == quote)
			quote = 0;
		}
		else if (str[i] == '"' || str[i] == '\'')
			quote = str[i];
		i++;
	}
	if (quote == 0){
		printf("quotes correctes\n");
		return (1);}
	else{
		printf("quotes incorrectes\n");
		return (0);}
}

int	create_cmd_line(t_data *data)
{
	char		**cmds;
	t_cmd_line	*cmd_line;

	cmds = ft_split_quoted(data->line, "|");
	if (!cmds)
		return (MALLOC_ERROR);
	cmd_line = lst_new_cmd_line(cmds[0]);
	if (lst_create_tokens(cmd_line) == SYNTAX_ERROR)
	{
		printf("bash : syntax error\n");
		ft_freesplit(cmds);
		lst_clear_cmd_line(&cmd_line);
		return (SYNTAX_ERROR);
	}
	if (fill_lst_cmd_line(&cmd_line, cmds) == SYNTAX_ERROR)
	{
		ft_freesplit(cmds);
		lst_clear_cmd_line(&cmd_line);
		return (SYNTAX_ERROR);
	}
	data->cmd = cmd_line;
	ft_freesplit(cmds);
	return (0);
}

int		str_count(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i])
		i++;
	return (i);	
}

void	split_tokens_on_whitespaces(t_cmd_line *cmd)
{
	int		i;
	char	**strs;
	t_token	*cursor;

	while (cmd)
	{
		cursor = cmd->token;
		while (cursor)
		{
			strs = ft_split_quoted(cursor->word, " \t");
			i = str_count(strs);
			if (i > 1)
			{
				while (i >= 0)
				{
					lst_insert_token(cursor, lst_new_token(strs[i]));
					i--;
				}
				if (!cursor->previous)
					cmd->token = cursor->next;
				lst_remove_token(&cursor);
			}

			i = 0;
			while (i < str_count(strs) - 1)
			{
				cursor = cursor->next;
				i++;
			}
			if (strs)
				ft_freesplit(strs);
			cursor = cursor->next;
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
				quote = 0;			//fermeture des quotes
			else if (quote == 0)
				quote = word[i];	//ouverture des quotes
			else
				dest[j++] = word[i];//quote qu'on recopie <3
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

/*void	print_token(t_cmd_line *cmd)
{
	t_token *cursor;
	
	while (cmd)
	{
		cursor = cmd->token;
		while (cursor)
		{
			printf("->%s<-\n", cursor->word);
		}
		cmd = cmd->next;
	}
}*/

void	print_cmd_line(t_cmd_line *data)
{
	int	i = 0;
	t_token *token = data->token;
	while (token)
	{
		printf("token %d : -->%s<--\n", i, token->word);
		i++;
		token = token->next;
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

int	parse_line(t_data *data)
{
	//On enleve les whitespaces inutiles
	data->line = remove_whitespaces(data->line);
	if (!*data->line)
	{
		free(data->line);
		return (0);	//seul cas valide ou data->cmd reste NULL
	}

	//Verification de la position des pipes

	if (!quotes_correct(data->line))
	{
		printf("syntax error: incomplete quotes\n");
		return (SYNTAX_ERROR);
	}
	if (syntax_pipes(data->line) != 0)
		return (SYNTAX_ERROR);
	//printf("pipes ok\n");
	//creation des lignes de commande
	if (create_cmd_line(data) != 0)
		return (SYNTAX_ERROR);
	//printf("Pas d'erreur de syntaxe\n");
	//Definition des types
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
	
	expand(data->cmd, data->env, data->pwd_displayable);	//ca a l'air ok,a voir pour les $ seuls ou suites de $

	split_tokens_on_whitespaces(data->cmd);
	define_type(data->cmd);
	trim_whitespaces(data->cmd);
	print_cmd_line(data->cmd);
	remove_tokens_quotes(data->cmd);
	remove_empty_tokens(data->cmd);
	print_cmd_line(data->cmd);
	//execute(data);
	return (0);
}

