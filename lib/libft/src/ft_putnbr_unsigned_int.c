/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:01:44 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/10 21:01:42 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putnbr_unsigned_int(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n >= 10)
		ret += ft_putnbr_unsigned_int(n / 10);
	ret += ft_putchar((n % 10) + '0');
	return (ret);
}
