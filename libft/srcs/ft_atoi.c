/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:28:17 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:28:58 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (*nptr == '\t' || *nptr == '\v' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\f' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		nptr++;
		sign = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = (res * 10) + *nptr++ - '0';
	}
	return (res * sign);
}
