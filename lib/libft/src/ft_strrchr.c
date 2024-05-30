/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:28:37 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/26 17:22:32 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = (char *) s + ft_strlen(s);
	while (ret >= s)
	{
		if (*ret == (char) c)
			return ((char *)ret);
		ret--;
	}
	return (NULL);
}
