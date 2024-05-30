/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:13 by myokogaw          #+#    #+#             */
/*   Updated: 2023/10/01 01:22:15 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_words(const char *s, char c);
static char	*substr_split(const char *s, int start, int end);

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	j;
	int		index;

	if (!s)
		return (0);
	ret = (char **) ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!ret)
		return (0);
	j = 0;
	i = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			ret[j++] = substr_split(s, index, i);
			index = -1;
		}
		i++;
	}
	return (ret);
}

static char	*substr_split(const char *s, int start, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *) malloc((end - start + 1) * sizeof(char));
	while (start < end)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

static int	count_words(const char *s, char c)
{
	int	counter;
	int	target;

	counter = 0;
	target = 0;
	while (*s)
	{
		if (*s != c && target == 0)
		{
			target = 1;
			counter++;
		}
		else if (*s == c && target > 0)
			target = 0;
		s++;
	}
	return (counter);
}
