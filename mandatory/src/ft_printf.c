/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 20:28:26 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/01 16:13:57 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	valid_format(char c)
{
	char	*format;

	format = "cspdiuxX";
	while (*format)
	{
		if (*format == c)
			return (1);
		format++;
	}
	return (0);
}

int	format_handler(va_list *args, char c)
{
	if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (c == 'x' || c == 'X')
	{
		if (c == 'x')
			return (ft_print_hex(va_arg(*args, unsigned int), 1));
		return (ft_print_hex(va_arg(*args, unsigned int), 0));
	}
	else if (c == 'p')
		return (ft_print_address(va_arg(*args, void *)));
	else if (c == 'c')
		return (ft_print_char(va_arg(*args, int)));
	else if (c == 'u')
		return (ft_uputnbr(va_arg(*args, unsigned int)));
	else
		return (ft_putnbr(va_arg(*args, int)));
}

int	ft_parse_line(const char **format, va_list *args)
{
	if (**format == '%' && (*format)[1] && valid_format((*format)[1]))
	{
		(*format)++;
		return (format_handler(args, **format));
	}
	if (**format == '%' && (*format)[1] == '%')
		(*format)++;
	return (write(1, *format, 1));
}

int	ft_printf_proccess(const char *format, va_list *args)
{
	int	count;
	int	ret;

	count = 0;
	while (*format)
	{
		ret = ft_parse_line(&format, args);
		if (ret < 0)
			return (-1);
		count += ret;
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format || (write(1, 0, 0) < 0))
		return (-1);
	va_start(args, format);
	count = ft_printf_proccess(format, &args);
	va_end(args);
	return (count);
}
