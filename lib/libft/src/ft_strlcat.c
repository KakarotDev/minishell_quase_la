/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:45:39 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/01 01:55:54 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	if ((!dst || !src) && size == 0)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	i = 0;
	if (size < len_dst)
		return ((size + len_src));
	if (size > 0)
	{
		while (src[i] && len_dst < size - 1)
		{
			dst[len_dst] = src[i];
			i++;
			len_dst++;
		}
		dst[len_dst] = '\0';
	}
	return ((len_src + len_dst - i));
}
