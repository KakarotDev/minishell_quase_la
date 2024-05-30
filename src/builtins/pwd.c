/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:47 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 17:09:35 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_error(void);

void	pwd_error(char *buf)
{
	perror("Error\n pwd");
	free(buf);
	buf = NULL;
	return ;
}

char	*pwd_erange(char *buf, int size)
{
	static int	n_size;

	if (!n_size)
		n_size = size;
	n_size *= 2;
	if (n_size > 10240)
	{
		perror("Error\n pwd");
		free(buf);
		return (NULL);
	}
	buf = ft_calloc(n_size, sizeof(char));
	if (!buf)
		return (alloc_error());
	return (buf);
}

char	*alloc_error(void)
{
	ft_putstr_fd("Error\n error when alloc memory\n", 2);
	return (NULL);
}

char	*catch_cwd(void)
{
	char	*cwd;
	char	*buf;
	size_t	size;

	size = 1024;
	buf = ft_calloc(size, sizeof(char));
	if (!buf)
		return (alloc_error());
	while (buf)
	{
		cwd = getcwd(buf, size);
		if (cwd)
			return (cwd);
		else
		{
			if (errno == ERANGE)
				buf = pwd_erange(buf, size);
			else
				pwd_error(buf);
		}
	}
	return (NULL);
}

int	pwd(void)
{
	char	*pwd;

	pwd = hook_pwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
