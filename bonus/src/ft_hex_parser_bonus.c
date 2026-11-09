/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_parser_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:44:41 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:44:42 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_puthex(unsigned int hex, int lower, int *s)
{
	int		count;
	char	*b1;

	b1 = "0123456789abcdef";
	if (!lower)
		b1 = "0123456789ABCDEF";
	count = 0;
	if (hex > 15)
		count += ft_puthex(hex / 16, lower, s);
	count += repeat_char(b1[hex % 16], 1, s);
	if (*s < 0)
		return (-1);
	return (count);
}

int	put_prefix(int lower, int *s)
{
	int	ret;

	ret = 0;
	if (lower)
		ret = write(1, "0x", 2);
	else
		ret = write(1, "0X", 2);
	if (ret < 0)
		*s = -1;
	return (ret);
}

int	ft_print_hex(t_form *form, unsigned int hex, int lower)
{
	int	count;
	int	s;

	s = 0;
	count = 0;
	if (!form->minus)
		count += repeat_char(' ', form->sp_padding, &s);
	if (s == 0 && hex != 0 && form->hash)
		count += put_prefix(lower, &s);
	if (s == 0)
		count += repeat_char('0', form->zero_padding, &s);
	if (s == 0 && form->len)
		count += ft_puthex(hex, lower, &s);
	if (s == 0 && form->minus)
		count += repeat_char(' ', form->sp_padding, &s);
	if (s == -1)
		return (-1);
	return (count);
}

int	ft_hex_parser(t_form *form, unsigned int hex, int lower)
{
	int	length;
	int	hash;

	hash = 0;
	length = get_len_hex(hex);
	if (hex == 0 && form->precision == 0)
		length = 0;
	if (form->hash && hex != 0)
		hash = 2;
	form->len = length;
	form->zero_padding = form->precision - length;
	if (form->zero_padding < 0)
		form->zero_padding = 0;
	form->sp_padding = form->width - (form->zero_padding + length + hash);
	if (form->sp_padding < 0)
		form->sp_padding = 0;
	if (form->zero && !form->minus && form->precision < 0)
	{
		form->zero_padding += form->sp_padding;
		form->sp_padding = 0;
	}
	return (ft_print_hex(form, hex, lower));
}
