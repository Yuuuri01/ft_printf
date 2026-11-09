/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:45:41 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:45:42 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putnum(long nb, int *s)
{
	char	c;

	if (nb > 9)
		ft_putnum(nb / 10, s);
	if (*s == -1)
		return ;
	c = ((nb % 10) + 48);
	if (write(1, &c, 1) < 0)
		*s = -1;
}

int	check_and_print_int(long nb, t_form *format)
{
	int	count;
	int	ret;

	count = 0;
	ret = 0;
	if (format->len)
	{
		ft_putnum(nb, &ret);
		if (ret < 0)
			return (-1);
		count += format->len;
	}
	if (format->minus)
	{
		count += repeat_char(' ', format->sp_padding, &ret);
		if (ret < 0)
			return (-1);
	}
	return (count);
}

int	ft_putnbr(long num, char sign, t_form *format)
{
	int	count;
	int	s;

	s = 0;
	count = 0;
	if (!format->minus)
	{
		s = repeat_char(' ', format->sp_padding, &s);
		if (s < 0)
			return (-1);
		count += s;
	}
	if (sign)
	{
		if (write(1, &sign, 1) < 0)
			return (-1);
	}
	s = repeat_char('0', format->zero_padding, &s);
	if (s < 0)
		return (-1);
	count += s;
	s = check_and_print_int(num, format);
	if (s < 0)
		return (-1);
	return (count + s + (sign != 0));
}

int	ft_int_parser(t_form *format, int nb)
{
	char	sign;
	int		length;
	long	num;

	length = get_length_int(nb);
	if (nb == 0 && format->precision == 0)
		length = 0;
	format->len = length;
	sign = get_sign(format, nb);
	format->zero_padding = format->precision - length;
	if (format->zero_padding < 0)
		format->zero_padding = 0;
	format->sp_padding = format->width - ((sign != 0) + format->zero_padding
			+ length);
	if (format->sp_padding < 0)
		format->sp_padding = 0;
	if (format->zero && !format->minus && format->precision < 0)
	{
		format->zero_padding += format->sp_padding;
		format->sp_padding = 0;
	}
	num = nb;
	if (num < 0)
		num *= -1;
	return (ft_putnbr(num, sign, format));
}
