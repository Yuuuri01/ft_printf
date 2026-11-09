/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 20:28:32 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/26 20:28:33 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_hex(unsigned int hex, int lower, int *s)
{
	char	*base;
	int		count;

	count = 0;
	if (*s == -1)
		return ;
	if (lower)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (hex > 15)
		ft_parse_hex(hex / 16, lower, s);
	if (ft_print_char(base[hex % 16]) < 0)
		*s = -1;
}

int	ft_print_hex(unsigned int hex, int lower)
{
	int	s;

	s = 0;
	ft_parse_hex(hex, lower, &s);
	if (s == -1)
		return (-1);
	return (get_len_hex(hex));
}
