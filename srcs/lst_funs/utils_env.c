/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:00:06 by abiersoh          #+#    #+#             */
/*   Updated: 2023/03/30 09:00:07 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

t_env	*lst_search(t_env *env, char *str)
{
	if (!str || !*str)
		return (NULL);
	while (env)
	{
		if (env->is_first)
		{
			env = env->next;
			continue ;
		}
		if (env->var_name && ft_strcmp(str, env->var_name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
