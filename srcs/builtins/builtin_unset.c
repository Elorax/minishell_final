/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:58:51 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 08:58:54 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	lst_remove_env(t_env *env)
{
	t_env	*tmp;
	tmp = NULL;
	if (!env)
		return ;
	if (env->next)
		env->next->previous = env->previous;
	if (env->previous)
	{
		env->previous->next = env->next;
		lst_delone_env(env);
	}
	else
	{
		printf("Eeuh probleme les mecs \nPROBLEME\nALERTE\nOSCOUR\n\n");
		tmp = env->next;
		lst_delone_env(env);
		env = tmp;
	}
}

int	builtin_unset(t_data *data, t_token *token)
{
	t_env	*tmp;

	while (token)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue;
		}
		if (!is_name_valid(token->word))
		{
			token = token->next;
			continue;
		}
		tmp = lst_search(data->env, token->word);

		if (tmp)
			lst_remove_env(tmp);
		if (ft_strcmp(token->word, "PWD") == 0)
			data->pwd_displayable = 0;
		token = token->next;

	}
	return (0);
}
