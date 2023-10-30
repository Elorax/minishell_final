/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:59:40 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 08:59:41 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	lst_replace_tkn_word(t_token *token, char *new_word)
{
	if (!token)
		return ;
	if (token->word)
		free(token->word);
	token->word = ft_strdup(new_word);
}

void	lst_replace_value_env(t_env *env, char *new_value, int env_displayable)
{
	if (!env)
		return ;
	free(env->var_value);
	env->var_value = ft_strdup(new_value);
	env->env_displayable = env_displayable;
}
