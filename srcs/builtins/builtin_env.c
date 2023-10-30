/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:58:37 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/03 16:00:48 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

int	builtin_env(t_data *data, int print_export)
{
	t_env	*cursor;

	cursor = data->env;
	while (cursor)
	{
		//printf("\nwesh\n");
		if (cursor->is_first)
		{
			cursor = cursor->next;
			continue;
		}
		if (print_export)
			printf("export ");
		if (print_export || cursor->env_displayable)
			printf("%s", cursor->var_name);
		if (cursor->env_displayable)
			printf("=%s", cursor->var_value);
		if (print_export || cursor->env_displayable)
			printf("\n");
		cursor = cursor->next;
	}
	return (0); //(dans tous les cas success or not)
}
