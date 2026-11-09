/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 17:59:52 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/01 16:16:08 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex_pointer(unsigned long nb, int *s)
{
	char	*base;

	base = "0123456789abcdef";
	if (*s == -1)
		return ;
	if (nb >= 16)
		print_hex_pointer(nb / 16, s);
	if (ft_print_char(base[nb % 16]) < 0)
		*s = -1;
}

int	ft_print_address(void *adrr)
{
	unsigned long	nb;
	int				s;

	if (!adrr)
		return (write(1, "(nil)", 5));
	nb = (unsigned long)adrr;
	if (write(1, "0x", 2) < 0)
		return (-1);
	s = 0;
	print_hex_pointer(nb, &s);
	if (s == -1)
		return (-1);
	return (get_len_address(nb) + 2);
}
