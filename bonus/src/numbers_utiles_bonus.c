/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_utiles_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:45:57 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:45:58 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	repeat_char(char c, int length, int *signal)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (write(1, &c, 1) < 0)
		{
			*signal = -1;
			return (*signal);
		}
		i++;
	}
	return (length);
}

char	get_sign(t_form *format, int nb)
{
	if (nb < 0)
		return ('-');
	else if (format->plus)
		return ('+');
	else if (format->space)
		return (' ');
	return (0);
}

int	get_length_int(int nb)
{
	int		size;
	long	num;

	num = nb;
	if (num == 0)
		return (1);
	if (num < 0)
		num *= -1;
	size = 0;
	while (num)
	{
		num /= 10;
		size++;
	}
	return (size);
}

int	get_length_unsigned(unsigned int num)
{
	int	size;

	if (num == 0)
		return (1);
	size = 0;
	while (num)
	{
		num /= 10;
		size++;
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
		hex /= 16;
		size++;
	}
	return (size);
}
