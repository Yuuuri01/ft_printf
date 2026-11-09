/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 16:13:22 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/01 16:14:21 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_len_int(int nb)
{
	int		size;
	long	num;

	size = 0;
	if (nb == 0)
		return (1);
	num = nb;
	if (nb < 0)
	{
		size++;
		num *= -1;
	}
	while (num)
	{
		size++;
		num /= 10;
	}
	return (size);
}

int	get_len_u(unsigned int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

int	get_len_hex(unsigned int hex)
{
	int	size;

	size = 0;
	if (hex == 0)
		return (1);
	while (hex)
	{
		size++;
		hex /= 16;
	}
	return (size);
}

int	get_len_address(unsigned long adr)
{
	int	size;

	size = 0;
	while (adr)
	{
		size++;
		adr /= 16;
	}
	return (size);
}
