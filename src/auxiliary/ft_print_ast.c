/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:53:52 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 13:53:52 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	ft_print_dlist_ast(t_dlist **head)
//{
//	t_dlist	*temp;
//
//	if (!head)
//		return ;
//	if (!*head)
//		return ;
//	temp = *head;
//	while (temp)
//	{
//		if (temp->tok->lex)
//			printf("%s\n", temp->tok->lex);
//		if (temp->tok->type == 1)
//			printf("%s\n", "DGREAT");
//		else if (temp->tok->type == 2)
//			printf("%s\n", "DLESS");
//		else if (temp->tok->type == 3)
//			printf("%s\n", "PIPE");
//		else if (temp->tok->type == 4)
//			printf("%s\n", "R_OUT");
//		else if (temp->tok->type == 5)
//			printf("%s\n", "R_IN");
//		else if (temp->tok->type == 6)
//			printf("%s\n", "WORD");
//		else if (temp->tok->type == 7)
//			printf("%s\n", "ASSIGNMENT_WORD");
//		if (temp->next == NULL)
//			break ;
//		temp = temp->next;
//	}
//	return ;
//}
//
//void	ft_print_ast(t_ast **root)
//{
//	t_ast	*temp;
//
//	if (!root)
//		return ;
//	if (!*root)
//		return ;
//	temp = *root;
//	while (temp)
//	{
//		if (temp->right)
//		{
//			printf("\nNew Block\n");
//			ft_print_dlist_ast(temp->right->exec_tokens);
//		}
//		if (temp->left == NULL)
//		{
//			printf("\nNew Block\n");
//			ft_print_dlist_ast(temp->exec_tokens);
//			break ;
//		}
//		temp = temp->left;
//	}
//	return ;
//}

