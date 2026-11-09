/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_parser_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:44:31 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:44:31 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_char(t_form *form, char c)
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
	if (write(1, &c, 1) < 0)
		return (-1);
	count += 1;
	if (form->minus)
	{
		count += repeat_char(' ', form->sp_padding, &s);
		if (s == -1)
			return (-1);
	}
	return (count);
}

int	ft_char_parser(t_form *form, char c)
{
	form->sp_padding = form->width - 1;
	if (form->sp_padding < 0)
		form->sp_padding = 0;
	return (print_char(form, c));
}
