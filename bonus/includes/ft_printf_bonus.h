/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 14:32:33 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/30 14:34:29 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>

typedef struct t_form
{
	int		plus;
	int		hash;
	int		width;
	int		precision;
	int		minus;
	int		space;
	int		zero;
	int		zero_padding;
	int		sp_padding;
	int		len;
	char	spec;
}		t_form;

int		ft_printf(const char *str, ...);
int		ft_int_parser(t_form *form, int nb);
int		ft_string_parser(t_form *form, char *str);
int		ft_hex_parser(t_form *form, unsigned int hex, int lower);
int		ft_address_parser(t_form *form, void *addr);
int		ft_char_parser(t_form *form, char c);
int		ft_unsigned_parser(t_form *form, unsigned int nb);
int		get_length_int(int nb);
int		get_length_unsigned(unsigned int nb);
int		repeat_char(char c, int length, int *s);
char	get_sign(t_form *form, int nb);
int		get_len_hex(unsigned int hex);
int		special_nill_case(t_form *form);
int		despatch_flags(t_form *forms, va_list *args);
int		valid_format(char c);

#endif