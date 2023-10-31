/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:49 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/08 16:09:49 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

int	two_pipe_detector(char *line)
{
	int		i;
	char	quoted;

	if (!line)
		return (0);
	quoted = 0;
	if (line[0] == '\'' || line[0] == '\"')
		quoted = line[0];
	i = 1;
	while (line [i - 1] && line[i])
	{
		if (quoted)
		{
			if (quoted == line[i])
				quoted = 0;
			i++;
			continue ;
		}
		if (line[i] == '\'' || line[i] == '\"')
			quoted = line[i];
		if (line[i - 1] == '|' && line[i] == '|')
			return (SYNTAX_ERROR);
		i++;
	}
	return (0);
}

int	syntax_pipes_2(char **tmp, int i)
{
	while (tmp[i])
		i++;
	i--;
	if (i > 0)
	{
		if (tmp[i] && tmp[i][ft_strlen(tmp[i]) - 1] == '|')
		{
			ft_freesplit(tmp);
			printf("bash: syntax error near unexpected token \'|\'\n");
			return (SYNTAX_ERROR);
		}
	}
	ft_freesplit(tmp);
	return (0);
}

int	syntax_pipes(char *line)
{
	char	**tmp;
	int		i;

	if (two_pipe_detector(line) == SYNTAX_ERROR)
	{
		printf("bash: syntax error near unexpected token \'|\'\n");
		return (SYNTAX_ERROR);
	}
	tmp = ft_split_quoted(line, " \t");
	if (!tmp)
		return (MALLOC_ERROR);
	i = 0;
	if (tmp[0] && tmp[0][0] == '|')
	{
		ft_freesplit(tmp);
		printf("bash: syntax error near unexpected token \'|\'\n");
		return (SYNTAX_ERROR);
	}
	return (syntax_pipes_2(tmp, i));
}
