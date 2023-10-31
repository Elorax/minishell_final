/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:58:07 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/31 16:22:10 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

static int	is_it_no_nl_flag(char *word)
{
	int	i;

	if (!word || !*word)
		return (0);
	i = 0;
	if (word[i] == '-')
		i++;
	else
		return (0);
	while (word && word[i] == 'n')
		i++;
	return (!word[i]);
}

void	builtin_echo_2(t_token *token, int fd, int nl)
{
	while (token)
	{
		if (token->type == ARG && (*token->word || token->was_quoted))
		{
			ft_putstr_fd(" ", fd);
			ft_putstr_fd(token->word, fd);
		}
		token = token->next;
	}
	if (nl == 1)
	{
		ft_putstr_fd("\n", fd);
	}
}

void	builtin_echo(t_token *token, int fd)
{
	int	nl;

	nl = 1;
	token = token->next;
	while (token && !*token->word && !token->was_quoted)
		token = token->next;
	while (token && is_it_no_nl_flag(token->word))
	{
		nl = 0;
		token = token->next;
	}
	while (token && ((!*token->word && !token->was_quoted)
			|| token->type != ARG))
		token = token->next;
	if (token)
	{
		ft_putstr_fd(token->word, fd);
		token = token->next;
	}
	builtin_echo_2(token, fd, nl);
}
