/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:20:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/19 16:45:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	size_t			i;
	size_t			lenght;
	char			*n_string;

	i = -1;
	if (s == NULL)
		lenght = 0;
	else
		lenght = ft_strlen(s);
	n_string = (char *) malloc(lenght * sizeof(char) + 1);
	if (!n_string)
		return (n_string);
	while (i++, i != lenght)
		n_string[i] = s[i];
	n_string[i] = '\0';
	return (n_string);
}
