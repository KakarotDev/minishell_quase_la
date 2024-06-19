/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:24 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/17 17:46:02 by myokogaw         ###   ########.fr       */
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

int	builtin_exit(t_ast *root, int *stdout_fd)
{
	short int	arg;
	int			index;

	arg = -1;
	index = 1;
	while (root->cmd_matrix[index])
	{
		if (root->cmd_matrix[index][0] && arg == -1)
		{
			if (!validate_argument(root->cmd_matrix[index]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("Error\n exit: numeric argument required\n", 2);
				close(*stdout_fd);
				last_exit_status(2);
				closing_process(root);
			}
			arg = ft_atoi(root->cmd_matrix[index]);
		}
		else if (arg != -1 && root->cmd_matrix[index][0] != '\0')
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
		last_exit_status(arg);
		close(*stdout_fd);
		closing_process(root);
	}
	else if (arg == -1)
	{
		ft_putstr_fd("exit\n", 2);
		close(*stdout_fd);
		closing_process(root);
	}
	return (0);
}
