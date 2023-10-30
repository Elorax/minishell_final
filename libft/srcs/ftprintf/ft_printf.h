/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:26:07 by lbisson           #+#    #+#             */
/*   Updated: 2022/07/06 23:02:19 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define FORMAT_SPECIFIERS "cspxXdiu%"

typedef int	(*t_fptr)();

/* CONVERSIONS */
int		print_char(va_list args);
int		print_str(va_list args);
int		print_address(va_list args);
int		print_hexa_lowercase(va_list args);
int		print_hexa_uppercase(va_list args);
int		print_int(va_list args);
int		print_unsigned_int(va_list args);
int		print_percent(va_list args);

#endif
