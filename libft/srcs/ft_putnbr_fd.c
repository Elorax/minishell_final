/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:13 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:37:37 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	cpy;

	cpy = n * (1 - (2 * (n < 0)));
	write(fd, "-", n < 0);
	if (cpy > 9)
		ft_putnbr_fd(cpy / 10, fd);
	ft_putchar_fd(cpy % 10 + '0', fd);
}
