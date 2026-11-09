/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_parser_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:45:46 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:45:47 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_strlen(char *str)
{
	char	*s;

	s = str;
	while (*s)
		s++;
	return (s - str);
}

int	ft_print_string(int cut, t_form *form, char *str)
{
	int	count;
	int	s;

	count = 0;
	s = 0;
	if (!form->minus)
	{
		s = repeat_char(' ', form->sp_padding, &s);
		if (s < 0)
			return (-1);
		count += s;
	}
	if (write(1, str, cut) < 0)
		return (-1);
	count += cut;
	if (form->minus)
	{
		s = repeat_char(' ', form->sp_padding, &s);
		if (s < 0)
			return (-1);
		count += s;
	}
	return (count);
}

int	ft_string_parser(t_form *form, char *str)
{
	int	cut;
	int	null_case;

	null_case = 0;
	cut = 0;
	if (!str)
	{
		null_case = 1;
		str = "(null)";
	}
	cut = ft_strlen(str);
	if (null_case && form->precision >= 0 && form->precision < 6)
		cut = 0;
	else if (form->precision >= 0 && form->precision < cut)
		cut = form->precision;
	form->sp_padding = form->width - cut;
	if (form->sp_padding < 0)
		form->sp_padding = 0;
	return (ft_print_string(cut, form, str));
}
