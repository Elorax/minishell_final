/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:01:37 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/12 18:19:08 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cmd)
		lst_clear_cmd_line(&data->cmd);
	data->line = NULL;
	data->cmd = NULL;
}

void	free_all_data(t_data *data)
{
	free_data(data);
	lst_clear_env(&data->env);
	data->env = NULL;
}
