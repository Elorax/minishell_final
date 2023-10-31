/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:01:18 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/15 15:58:44 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	ctrl_d(int sigid)
{
	printf("exit\n");
	if (sigid == EOF)
	{
		builtin_exit(NULL, NULL, 0);
	}
}
