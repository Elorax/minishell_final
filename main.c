/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:19:59 by abiersoh          #+#    #+#             */
/*   Updated: 2023/05/12 19:38:33 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/petit_coquillage.h"

int	g_exit_status;

void	init_m(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	g_exit_status = 0;
	data->env = init_env(env);
	data->pwd_displayable = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}

void	m_1(int ac, char **av, char **env, t_data *data)
{
	if (ac > 1)
	{
		printf("bash: %s: no such file or directory\n", av[1]);
		exit(127);
	}
	if (!env || !*env)
	{
		printf("Environnement non trouve\n");
		exit(127);
	}
	init_m(data, env);
}

void	boucle_p1(t_data *data)
{
	data->line = readline(BOLDYELLOW"🐚Petit coquillage🐚$> "RESET);
	if (data->line == NULL)
	{
		ft_putendl_fd("exit", 2);
		free_all_data(data);
		exit(0);
	}
	data->old_cmd = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	if (data->line && *(data->line))
		add_history(data->line);
}

int	func(t_data *data)
{
	if (!data->cmd)
		return (1);
	data->old_cmd = data->cmd;
	while (data->cmd)
	{
		if (!data->cmd->token)
			data->cmd = data->cmd->next;
		else
			break ;
	}
	if (!data->cmd)
		return (1);
	g_exit_status = execute(data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	m_1(ac, av, env, &data);
	get_data(&data, 1);
	while (42)
	{
		boucle_p1(&data);
		if (data.line && *data.line)
		{
			if (parse_line(&data) == 0)
			{
				if (func(&data) == 1)
					continue ;
			}
			else
				g_exit_status = 2;
		}
		if (data.old_cmd)
			data.cmd = data.old_cmd;
		free_data(&data);
	}
	return (0);
}
