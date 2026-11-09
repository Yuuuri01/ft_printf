/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 20:30:21 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/01 16:14:57 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_iparse(int nb, int *s)
{
	long	n;
	int		count;

	n = nb;
	count = 0;
	if (*s == -1)
		return ;
	if (n < 0)
	{
		if (ft_print_char('-') < 0)
			*s = -1;
		n *= -1;
	}
	if (n > 9)
		ft_iparse(n / 10, s);
	if (ft_print_char(n % 10 + 48) < 0)
		*s = -1;
}

int	ft_putnbr(int nb)
{
	int	s;

	s = 0;
	ft_iparse(nb, &s);
	if (s < 0)
		return (-1);
	return (get_len_int(nb));
}
