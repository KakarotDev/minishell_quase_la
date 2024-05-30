/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:05:00 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/10 21:01:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int		ncpy;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	ncpy = n;
	if (ncpy >= 10)
	{
		ft_putnbr_fd(ncpy / 10, fd);
		ft_putnbr_fd(ncpy % 10, fd);
	}
	else
		ft_putchar_fd(ncpy + 48, fd);
}
