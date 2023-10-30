/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:59:52 by abiersoh          #+#    #+#             */
/*   Updated: 2023/06/01 16:32:58 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/petit_coquillage.h"

void	lst_delone_token(t_token *lst)
{
	if (!lst)
		return ;
	free(lst->word);
	free(lst);
}

void	lst_delone_env(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->var_name);
	free(lst->var_value);
	free(lst);
}

void	lst_delone_cmd_line(t_cmd_line *lst)
{
	if (!lst)
		return ;
	lst_clear_token(&lst->token);
	if (lst->cmd_args != NULL)
		ft_freesplit(lst->cmd_args);
	lst->cmd_args = NULL;
	free(lst->cmd);
	free(lst);
}
