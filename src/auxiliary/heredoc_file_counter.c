/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_counter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:17:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/20 16:17:55 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	heredoc_file_counter(int filenum)
{
	static int	current;

	if (filenum != -1)
		current = filenum;
	return (current);
}
