/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:39:05 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/10 21:02:39 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*ptr;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return ((char *) s1);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, *(s1 + start)))
		start += 1;
	while (ft_strchr(set, *(s1 + end - 1)))
		end -= 1;
	len = end - start;
	ptr = ft_substr(s1, start, len);
	return (ptr);
}
