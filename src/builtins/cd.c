/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:58:57 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 20:17:19 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_environment(void)
{
	char	*matrix[3];

	matrix[0] = NULL;
	matrix[1] = ft_strjoin("OLD_PWD=", hook_pwd(NULL, 0));
	matrix[2] = NULL;
	export(matrix);
	free(matrix[1]);
	hook_pwd(NULL, 1);
	hook_pwd(catch_cwd(), 0);
	matrix[1] = ft_strjoin("PWD=", hook_pwd(NULL, 0));
	export(matrix);
	free(matrix[1]);
	return ;
}

int	error_msg_cd(int err, char *path)
{
	if (err == ERRNO)
		perror("Error\n cd");
	else if (err == NOTSETHOME)
		ft_putstr_fd("Error\n cd: HOME not set\n", 2);
	else if (err == TOOMANY)
		ft_putstr_fd("Error\n cd: too many arguments\n", 2);
	if (path)
		free(path);
	return (EXIT_FAILURE);
}

int	try_except_change_dir(char *curpath)
{
	char	*home;

	home = ft_getenv("$HOME");
	if (curpath == NULL && home == NULL)
		return (error_msg_cd(NOTSETHOME, home));
	else if (curpath == NULL && home)
	{
		if (chdir(home))
			return (error_msg_cd(ERRNO, home));
	}
	else if (curpath)
	{
		if (chdir(curpath))
			return (error_msg_cd(ERRNO, home));
	}
	update_environment();
	free(home);
	free(curpath);
	return (EXIT_SUCCESS);
}

int	cd(char **matrix)
{
	char	*curpath;

	curpath = NULL;
	while (*++matrix)
	{
		if (**matrix && curpath == NULL)
			curpath = ft_strdup(*matrix);
		else if (curpath && **matrix != '\0')
			return (error_msg_cd(TOOMANY, curpath));
	}
	return (try_except_change_dir(curpath));
}
