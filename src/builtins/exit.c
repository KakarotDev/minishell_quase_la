/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:24 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/23 17:29:19 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Erro 1;
// exit com a mensagem de erro "numeric argument required" configura o último status de saída = 2 e encerra o programa;
// possuí precedência sobre o erro "too many arguments", ocorre quando o primeiro argumento passsado para o comando possui
// algum caracter diferente de número.

// Erro 2;
// exit com a mensagem de erro "too many arguments" configura o último status de saída = 1 e não encerra o processo;
// ocorre quando passamos mais de um argumento para o comando.

int	validate_argument(const char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (FALSE);
		arg++;
	}
	return (TRUE);
}

int	builtin_exit(char **matrix)
{
	short int	arg;
	int			index;

	arg = -1;
	index = 1;
	while (matrix[index])
	{
		if (matrix[index][0] && arg == -1)
		{
			if (!validate_argument(matrix[index]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("Error\n exit: numeric argument required\n", 2);
				hook_environ(NULL, 1);
				hook_pwd(NULL, 1);
				ft_free_matrix((void **) matrix);
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				close(STDERR_FILENO);
				exit(2);
			}
			arg = ft_atoi(matrix[index]);
		}
		else if (arg != -1 && matrix[index][0] != '\0')
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("Error\n exit: too many arguments\n", 2);
			return (1);
		}
		index++;
	}
	if (arg != -1)
	{
		ft_putstr_fd("exit\n", 2);
		hook_environ(NULL, 1);
		hook_pwd(NULL, 1);
		ft_free_matrix((void **) matrix);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(arg);
	}
	else if (arg == -1)
	{
		ft_putstr_fd("exit\n", 2);
		hook_environ(NULL, 1);
		hook_pwd(NULL, 1);
		ft_free_matrix((void **) matrix);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(last_exit_status(-1));
	}
	return (0);
}
