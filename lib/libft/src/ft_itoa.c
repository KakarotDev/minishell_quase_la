/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:13:37 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/29 22:17:09 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	intlen(int n);

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		alloc;
	long int	n_long;
	char		*s;

	n_long = (long int) n;
	alloc = intlen(n);
	i = alloc - 1;
	s = malloc(alloc * sizeof(char));
	if (!s)
		return (malloc(0));
	if (n == 0)
		s[0] = 48;
	if (n_long < 0)
	{
		n_long *= -1;
		s[0] = 45;
	}
	s[i] = 0;
	while (i--, n_long != 0)
	{
		s[i] = n_long % 10 + 48;
		n_long = n_long / 10;
	}
	return (s);
}

static size_t	intlen(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i += 1;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	i++;
	return (i);
}
