/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:00:16 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/26 17:22:45 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ret;
	char		*temp;
	size_t		len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	temp = (char *) s;
	if (start > len_s)
		return (ft_strdup(""));
	if (len + start > len_s)
		len = len_s - start;
	ret = (char *) malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	free(temp);
	return (ret);
}
