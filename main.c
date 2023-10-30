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

t_data	*g_data;



/* inutile atm
void	numbers(int *a, int *b, int *c, int action)
{
	static int _a = *a;
	static int _b = *b;
	static int _c = *c;

	if (action == UPDATE)
	{
		_a = *a;
		_b = *b;
		_b = *c;
	}
	else if (action == READ)
	{
		*a = _a;
		*b = _b;
		*c = _c;
	}
}
*/
int	g_exit_status;


int main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac > 1)
	{
		printf("bash: %s: no such file or directory\n", av[1]);
		return (127);
	}
	if (!env || !*env)
	{
		printf("Environnement non trouve\n");
		return (127);
	}
	ft_memset(&data, 0, sizeof(t_data));
	g_exit_status = 0;
	g_data = &data;
	(void) g_data;
	data.env = init_env(env);
	data.pwd_displayable = 1;
	signal(SIGQUIT, SIG_IGN);	//ctrl-\;
	signal(SIGINT, &ctrl_c);	//ctrl-c
	//signal(EOF, &ctrl_d); <-- ctrl d, a gerer autrement.
	/*print_env(data.env);
	printf("\n\n\n\n\n");
	export_env(data.env);*/
	while (1)	//Condition a modifier plus tard pour quitter la boucle en cas de commande exit
	{
		data.line = readline(BOLDYELLOW"🐚Petit coquillage🐚$> "RESET);
		if (data.line == NULL)	//CTRL-D
		{
			ft_putendl_fd("exit", 2);
			free_all_data(&data);
			exit(0);
		}
		data.old_cmd = NULL;
		signal(SIGQUIT, SIG_IGN);	//ctrl-\;
		signal(SIGINT, &ctrl_c);	//ctrl-c
		if (data.line && *data.line)
			add_history(data.line);
		if (data.line && *data.line)
		{
			if (parse_line(&data) == 0)
			{
				if (!data.cmd)
					continue;
				display_cmd_line(data.cmd);
//				builtin_dispatch(&data, data.cmd->token);
				data.old_cmd = data.cmd;
				while (data.cmd)
				{
					if (!data.cmd->token)
						data.cmd = data.cmd->next;
					else
						break;
				}
				if (!data.cmd)
					continue;
				g_exit_status = execute(&data);
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
