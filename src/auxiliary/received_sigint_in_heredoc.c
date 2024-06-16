/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   received_sigint_in_heredoc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:55:26 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/23 16:55:26 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	received_sigint_in_heredoc(int status)
{
	static int	received;

	if (status != -1)
		received = status;
	return (received);
}
