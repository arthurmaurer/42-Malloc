/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/20 16:37:53 by amaurer           #+#    #+#             */
/*   Updated: 2013/12/20 16:38:41 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_abs(int nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}
