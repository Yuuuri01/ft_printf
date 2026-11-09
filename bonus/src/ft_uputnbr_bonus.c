/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:45:52 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:45:53 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putnum_unsigned(unsigned int nb, int *s)
{
	char	c;

	if (nb > 9)
		ft_putnum_unsigned(nb / 10, s);
	if (*s == -1)
		return ;
	c = (nb % 10) + '0';
	if (write(1, &c, 1) < 0)
		*s = -1;
}

int	check_and_print_unsigned(unsigned int nb, t_form *format)
{
	int	count;
	int	ret;

	count = 0;
	ret = 0;
	if (format->len)
	{
		ft_putnum_unsigned(nb, &ret);
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

int	ft_uputnbr(t_form *form, unsigned int nb)
{
	int	count;
	int	s;

	count = 0;
	s = 0;
	if (!form->minus)
	{
		count += repeat_char(' ', form->sp_padding, &s);
		if (s < 0)
			return (-1);
	}
	count += repeat_char('0', form->zero_padding, &s);
	if (s < 0)
		return (-1);
	s = check_and_print_unsigned(nb, form);
	if (s < 0)
		return (-1);
	count += s;
	return (count);
}

int	ft_unsigned_parser(t_form *form, unsigned int nb)
{
	int	length;

	length = get_length_unsigned(nb);
	if (nb == 0 && form->precision == 0)
		length = 0;
	form->len = length;
	form->zero_padding = form->precision - length;
	if (form->zero_padding < 0)
		form->zero_padding = 0;
	form->sp_padding = form->width - (form->zero_padding + length);
	if (form->sp_padding < 0)
		form->sp_padding = 0;
	if (form->zero && !form->minus && form->precision < 0)
	{
		form->zero_padding += form->sp_padding;
		form->sp_padding = 0;
	}
	return (ft_uputnbr(form, nb));
}
