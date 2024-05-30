/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:28:57 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/10 21:01:13 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest1;
	unsigned char	*src1;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	i = -1;
	if (n == 0)
		return (dest);
	if (src < dest)
		while (n--)
			*(dest1 + n) = *(src1 + n);
	else
		while (i++, i < n)
			dest1[i] = src1[i];
	return (dest);
}
