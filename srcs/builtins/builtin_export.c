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

t_token	*export_2(t_data *data, t_token *token)
{
	while (token && token->type != ARG)
		token = token->next;
	if (!token)
		export_env(data->env);
	return (token);
}

int	export_3(t_token *token, t_env *new)
{
	if (!new || !new->var_name || !*(new->var_name) || !new->var_value)
	{
		if (!*new->var_name)
			printf("bash:export:`%s': not valid identifier\n", token->word);
		lst_delone_env(new);
		return (1);
	}
	if (!is_name_valid(new->var_name))
	{
		printf("bash: export: `%s': not a valid identifier\n", token->word);
		lst_delone_env(new);
		return (1);
	}
	return (0);
}

int	builtin_export(t_data *data, t_token *token)
{
	t_env	*new;
	t_env	*find;

	token = export_2(data, token);
	while (token)
	{
		new = lst_new_env_v2(token->word);
		if (token->type != ARG || export_3(token, new))
		{
			token = token->next;
			continue ;
		}
		find = lst_search(data->env, new->var_name);
		if (!find)
			lst_add_back_env(&data->env, new);
		else
		{
			lst_replace_value_env(find, new->var_value,
				!!ft_strchr(token->word, '='));
			lst_delone_env(new);
		}
		token = token->next;
	}
	return (0);
}
