/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:32 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/06 16:14:38 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

void	init_ew(t_ew *a, t_token *token)
{
	a->str = ft_strdup(token->word);
	a->i = -1;
	a->quoted = 0;
	a->dest = NULL;
	a->begin = 0;
	a->value = NULL;
	a->qust = -1;
	a->ret = -1;
	ft_bzero(a->pwd, 256);
}

int	ew_2(t_ew *a)
{
	a->qust = -1;
	if (a->str[a->i] == '\'' || a->str[a->i] == '\"')
	{
		if (a->quoted == a->str[a->i])
			a->quoted = 0;
		else if (a->quoted == 0)
			a->quoted = a->str[a->i];
		return (1);
	}
	if (a->quoted == SIMPLE || a->str[a->i] != '$')
		return (1);
	if (a->str[a->i + 1] && !is_char_valid(a->str[a->i + 1]))
	{
		a->str = remove_char_from_string(a->str, (a->i)--);
		return (1);
	}
	return (0);
}

int	ew_3(t_ew *a)
{
	a->i++;
	if (a->str[a->i] && a->str[a->i] == '?')
		a->qust = a->i;
	a->dest = ft_strnjoin(a->dest, a->str + a->begin, a->i - a->begin - 1, 1);
	if (a->qust >= 0)
		a->dest = ft_strnjoin(a->dest, ft_itoa(g_exit_status), 3, 3);
	a->begin = a->i;
	while (a->str[a->i] && is_char_valid(a->str[a->i]))
	{
		if (a->qust >= 0 && a->str[a->i] == '?')
			a->begin = a->i;
		(a->i)++;
	}
	if (a->qust >= 0)
		a->dest = ft_strnjoin(a->dest, a->str + a->begin + 1,
				a->i - a->begin - 1, 1);
	a->name = ft_substr(a->str, a->begin, a->i - a->begin);
	a->begin = a->i;
	(a->i)--;
	return (0);
}

int	ew_4(t_ew *a, int pwd_displayable, t_env *env)
{
	if (!a->name)
	{
		error(MALLOC_ERROR, "expand.c : expand_word");
		return (1);
	}
	if (ft_strcmp(a->name, "PWD") == 0 && pwd_displayable)
		getcwd(a->pwd, 256);
	else if (lst_search(env, a->name))
		a->value = lst_search(env, a->name)->var_value;
	else
		a->value = NULL;
	if (a->value)
		a->dest = ft_strjoin(a->dest, a->value, 1);
	else if (a->pwd[0])
		a->dest = ft_strjoin(a->dest, a->pwd, 1);
	free(a->name);
	return (0);
}

char	*expand_word(t_token *token, t_env *env, int pwd_displayable)
{
	t_ew	a;

	init_ew(&a, token);
	while (a.str[++(a.i)])
	{
		if (ew_2(&a) == 1)
			continue ;
		if (!a.str[a.i + 1])
			break ;
		ew_3(&a);
		if (ew_4(&a, pwd_displayable, env) == 1)
			return (NULL);
	}
	if (!a.dest)
		return (a.str);
	a.dest = ft_strnjoin(a.dest, a.str + a.begin, a.i - a.begin, 1);
	free(token->word);
	free(a.str);
	token->word = ft_strdup(a.dest);
	return (a.dest);
}
