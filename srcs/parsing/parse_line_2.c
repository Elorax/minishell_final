/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:19:28 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 07:19:29 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

char	*remove_whitespaces(char *str)
{
	char	*dest;

	dest = ft_strtrim(str, " \t");
	free(str);
	return (dest);
}

int	fill_lst_cmd_line(t_cmd_line **cmd_line, char **cmds)
{
	int			i;
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
	if (quote == 0)
		return (1);
	else
		return (0);
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

int	str_count(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i])
		i++;
	return (i);
}
