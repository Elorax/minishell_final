/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:01:11 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/15 15:22:18 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	ctrl_c(int sigid)
{
	t_data	*data;

	data = get_data(0, 0);
	if (sigid == SIGINT)
	{
		g_exit_status = 130;
		if (!data->cmd)
		{
			write(1, "\b\b", 2);
			free(data->line);
			lst_clear_cmd_line(&data->cmd);
			write(2, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(2, "\n", 1);
	}
	if (sigid == SIGQUIT)
	{
		g_exit_status = 131;
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		exit (1);
	}
}
