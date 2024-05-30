/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:48:23 by myokogaw          #+#    #+#             */
/*   Updated: 2023/09/30 22:46:26 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_arg_check(va_list list, const char flag)
{
	int	ret;

	ret = 0;
	if (flag == 'c')
		ret += ft_putchar(va_arg(list, int));
	if (flag == 's')
		ret += ft_putstr(va_arg(list, char *));
	if (flag == 'd')
		ret += ft_putnbr_int(va_arg(list, int));
	if (flag == 'i')
		ret += ft_putnbr_int(va_arg(list, int));
	if (flag == 'p')
		ret += ft_putnbr_p(va_arg(list, unsigned long int));
	if (flag == 'x')
		ret += ft_putnbr_hex(va_arg(list, unsigned int), flag);
	if (flag == 'X')
		ret += ft_putnbr_hex(va_arg(list, unsigned int), flag);
	if (flag == 'u')
		ret += ft_putnbr_unsigned_int(va_arg(list, unsigned int));
	if (flag == '%')
		ret += ft_putchar('%');
	return (ret);
}
