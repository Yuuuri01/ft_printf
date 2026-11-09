/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 20:30:33 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/01 16:15:23 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_uparse(unsigned int nb, int *s)
{
	int	count;

	count = 0;
	if (*s == -1)
		return ;
	if (nb >= 10)
		ft_uparse(nb / 10, s);
	if (ft_print_char((nb % 10) + 48) < 0)
		*s = -1;
}

int	ft_uputnbr(unsigned int nb)
{
	int	s;

	s = 0;
	ft_uparse(nb, &s);
	if (s < 0)
		return (-1);
	return (get_len_u(nb));
}
