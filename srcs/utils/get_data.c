/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:05:09 by abiersoh          #+#    #+#             */
/*   Updated: 2023/10/31 17:05:13 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

t_data	*get_data(t_data *data, int a)
{
	static t_data	*mem = NULL;

	if (a && data)
	{
		free(mem);
		mem = data;
	}
	return (mem);
}
