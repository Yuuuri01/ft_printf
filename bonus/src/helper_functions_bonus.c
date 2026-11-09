/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 23:39:38 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/31 23:39:39 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	special_nill_case(t_form *form)
{
	int	count;
	int	s;

	count = 0;
	s = 0;
	if (!form->minus)
	{
		count += repeat_char(' ', form->sp_padding, &s);
		if (s == -1)
			return (-1);
	}
	if (write(1, "(nil)", 5) < 0)
		return (-1);
	count += 5;
	if (form->minus)
	{
		count += repeat_char(' ', form->sp_padding, &s);
		if (s == -1)
			return (-1);
	}
	return (count);
}

int	valid_format(char c)
{
	char	*str;

	str = "sdipXuxc";
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	despatch_flags(t_form *forms, va_list *args)
{
	if (forms->spec == 'd' || forms->spec == 'i')
		return (ft_int_parser(forms, va_arg(*args, int)));
	else if (forms->spec == 's')
		return (ft_string_parser(forms, va_arg(*args, char *)));
	else if (forms->spec == 'x' || forms->spec == 'X')
	{
		if (forms->spec == 'x')
			return (ft_hex_parser(forms, va_arg(*args, unsigned int), 1));
		return (ft_hex_parser(forms, va_arg(*args, unsigned int), 0));
	}
	else if (forms->spec == 'p')
		return (ft_address_parser(forms, va_arg(*args, void *)));
	else if (forms->spec == 'c')
		return (ft_char_parser(forms, va_arg(*args, int)));
	else if (forms->spec == 'u')
		return (ft_unsigned_parser(forms, va_arg(*args, unsigned int)));
	else
		return (write(1, "%", 1));
}
