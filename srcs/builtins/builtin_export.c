/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:58:44 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 16:55:56 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

int	is_name_valid(char *str)
{
	if (!str)
		return (0);
	if (ft_isdigit(*str))
		return (0);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (!*str);
}


int	builtin_export(t_data *data, t_token *token)
{
	t_env	*new;
	t_env	*find;

	while (token && token->type != ARG)
		token = token->next;
	if (!token)
		{
			//return (builtin_env(data, 1));
			export_env(data->env);
			return (0);
		}
	while (token)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue;
		}
		new = lst_new_env_v2(token->word);
		if (!new || !new->var_name || !*(new->var_name) || !new->var_value)
		{
//			printf("token non valide : --%s--\n", new->var_value);
			//voir cas export =b
			if (!*new->var_name)
				printf("bash: export: `%s': not a valid identifier\n", token->word);
			lst_delone_env(new);
			token = token->next;
			continue;
		}
		if (!is_name_valid(new->var_name))
		{
			printf("bash: export: `%s': not a valid identifier\n", token->word);
			lst_delone_env(new);
			token = token->next;
			continue;
		}
		find = lst_search(data->env, new->var_name);
		if (!find)
			lst_add_back_env(&data->env, new);
		else
		{
			lst_replace_value_env(find, new->var_value, !!ft_strchr(token->word, '='));
			lst_delone_env(new);
		}
		token = token->next;
	}
	return (0);
}
