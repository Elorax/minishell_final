/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:57:59 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:55:51 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	replace_oldpwd_by_pwd(t_env *var_env, char *new, t_data *data)
{
	t_env		*tmp;
	static int	flag = 0;

	if (data->pwd_displayable == 0)
		flag++;
	else
		flag = 0;
	tmp = var_env;
	if (lst_search(tmp, "OLDPWD"))
	{
		free(lst_search(tmp, "OLDPWD")->var_value);
		lst_search(tmp, "OLDPWD")->var_value = ft_strdup(new);
		if (flag == 1)
			lst_search(tmp, "OLDPWD")->env_displayable = 0;
		else
			lst_search(tmp, "OLDPWD")->env_displayable = 1;
	}
}

//leak probable ligne 56
void	builtin_cd_p2(t_env *tmp, t_data *data, char *cwd, char *new_pwd)
{
	char	*old;

	old = NULL;
	if (lst_search(tmp, "PWD"))
		old = lst_search(tmp, "PWD")->var_value;
	if (old)
		replace_oldpwd_by_pwd(data->env, old, data);
	else
		replace_oldpwd_by_pwd(data->env, new_pwd, data);
	getcwd(cwd, sizeof(cwd));
	old = ft_calloc(260, 1);
	if (!old)
		error(MALLOC_ERROR, "builtin_cd.c");
	ft_memcpy(old, cwd, 256);
	if (lst_search(tmp, "PWD"))
	{
		free(lst_search(tmp, "PWD")->var_value);
		lst_search(tmp, "PWD")->var_value = ft_strdup(old);
	}
	free(old);
}

void	builtin_cd(char *dir, t_data *data)
{
	char	*old;
	t_env	*tmp;
	char	cwd[256];
	char	*new_pwd;

	old = NULL;
	new_pwd = NULL;
	tmp = data->env;
	new_pwd = ft_calloc(260, 1);
	ft_memcpy(new_pwd, cwd, 256);
	if (chdir(dir) != 0)
		error(CD_ERROR, dir);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		else
			builtin_cd_p2(tmp, data, cwd, new_pwd);
	}
	free(new_pwd);
	free(old);
	data->pwd_displayable = 1;
}
