/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:47:58 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:06:47 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_process(int consult_or_change)
{
	static int	boolean_val;

	if (consult_or_change != -1)
		boolean_val = consult_or_change;
	return (boolean_val);
}
