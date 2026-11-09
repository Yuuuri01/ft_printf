/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address_parser_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:44:36 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:44:37 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	get_len_address(unsigned long addr)
{
	int	size;

	size = 0;
	if (addr == 0)
		return (1);
	while (addr)
	{
		size++;
		addr /= 16;
	}
	return (size);
}

void	put_address(unsigned long adr, int *s)
{
	char	*b;

	b = "0123456789abcdef";
	if (adr > 15)
		put_address(adr / 16, s);
	if (*s == -1)
		return ;
	if (write(1, &b[adr % 16], 1) < 0)
		*s = -1;
}

int	ft_print_address(t_form *form, unsigned long adr)
{
	int	count;
	int	s;

	s = 0;
	count = 0;
	if (!form->minus)
	{
		count += repeat_char(' ', form->sp_padding, &s);
		if (s == -1)
			return (-1);
	}
	if (write(1, "0x", 2) < 0)
		return (-1);
	put_address(adr, &s);
	if (s < 0)
		return (-1);
	count += form->len;
	if (form->minus)
	{
		count += repeat_char(' ', form->sp_padding, &s);
		if (s < 0)
			return (-1);
	}
	return (count);
}

int	ft_address_parser(t_form *form, void *addr)
{
	unsigned long	adr;

	if (!addr)
	{
		form->sp_padding = form->width - 5;
		if (form->sp_padding < 0)
			form->sp_padding = 0;
		return (special_nill_case(form));
	}
	adr = (unsigned long)addr;
	form->len = get_len_address(adr) + 2;
	form->sp_padding = form->width - form->len;
	if (form->sp_padding < 0)
		form->sp_padding = 0;
	return (ft_print_address(form, adr));
}
