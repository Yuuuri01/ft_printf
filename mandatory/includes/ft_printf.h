/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 10:38:38 by hamossai          #+#    #+#             */
/*   Updated: 2026/10/27 10:38:39 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putstr(char *str);
int	ft_print_hex(unsigned int hex, int lower);
int	ft_print_char(char c);
int	ft_print_address(void *addr);
int	ft_putnbr(int nb);
int	ft_uputnbr(unsigned int nb);
int	ft_printf(const char *format, ...);
int	get_len_u(unsigned int nb);
int	get_len_int(int nb);
int	get_len_hex(unsigned int hex);
int	get_len_address(unsigned long adr);

#endif
