/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:45:34 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:45:36 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*get_flags2(char *str, t_form *format)
{
	while (*str == '#' || *str == '-' || *str == '+' || *str == '0'
		|| *str == ' ')
	{
		if (*str == '#')
			format->hash = 1;
		else if (*str == '-')
			format->minus = 1;
		else if (*str == '+')
			format->plus = 1;
		else if (*str == '0')
			format->zero = 1;
		else if (*str == ' ')
			format->space = 1;
		str++;
	}
	return (str);
}

char	*get_flags1(const char *s, t_form *format)
{
	char	*str;

	str = (char *)s;
	format->precision = -1;
	str = get_flags2(str, format);
	format->width = 0;
	while (*str >= '0' && *str <= '9')
		format->width = format->width * 10 + (*str++ - 48);
	if (*str == '.')
	{
		format->precision = 0;
		str++;
		while (*str >= '0' && *str <= '9')
			format->precision = format->precision * 10 + (*str++ - 48);
	}
	if (valid_format(*str))
		format->spec = *str;
	return ((char *)str);
}

int	print_one(const char **args, va_list *ap, t_form *form)
{
	if (**args == '%' && (*args)[1] && (*args)[1] != '%')
	{
		(*args)++;
		*form = (t_form){0};
		*args = get_flags1(*args, form);
		return (despatch_flags(form, ap));
	}
	if (**args == '%' && (*args)[1] == '%')
		(*args)++;
	return (write(1, *args, 1));
}

int	ft_printf_proccess(const char *args, va_list *ap, t_form *form)
{
	int	count;
	int	ret;

	count = 0;
	while (*args)
	{
		ret = print_one(&args, ap, form);
		if (ret < 0)
			return (-1);
		count += ret;
		args++;
	}
	return (count);
}

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	t_form	form;
	int		count;

	if (!args || write(1, 0, 0) < 0)
		return (-1);
	va_start(ap, args);
	count = ft_printf_proccess(args, &ap, &form);
	va_end(ap);
	return (count);
}
