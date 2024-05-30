/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:49:34 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/10 21:00:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		i;
	int		ret;

	if (!format)
		return (-1);
	va_start(list, format);
	i = 0;
	ret = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			while (format[i] == ' ')
				i++;
			ret += ft_arg_check(list, format[i]);
			i++;
		}
		else
			ret += ft_putchar(format[i++]);
	}
	return (ret);
}
