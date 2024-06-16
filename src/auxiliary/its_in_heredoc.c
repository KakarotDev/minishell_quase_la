/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_in_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:05:44 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/20 16:05:44 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	its_in_heredoc(int it_is)
{
	static int	heredoc;

	if (it_is != -1)
		heredoc = it_is;
	return (heredoc);
}
