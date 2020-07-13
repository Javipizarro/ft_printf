/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_diopux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:25:15 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 18:36:43 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Prints the string  that represents the long long integer 'num' once
**	applied the changes specified in the t_convspecs struct pointed by *cs.
**	Negative numbers are also handled.
**	Returns the number of characters printed.
*/

int			ft_spec_di(t_convspecs *cs, long long int num)
{
	char	s[(cs->pre > 21 ? cs->pre : 21) + 1];
	int		i;

	i = cs->pre > 21 ? cs->pre : 21;
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = '0' : 1;
	if (num < 0 && (cs->sign = '-'))
	{
		cs->pre--;
		s[--i] = '0' - num % 10;
		num /= -10;
	}
	while (cs->pre-- > 0 || num)
	{
		s[--i] = num % 10 + '0';
		num /= 10;
	}
	return (ft_printer(cs, &s[i]));
}

/*
**	Prints, in octal base format, the string  that represents the
**	unsigned long long integer 'num' once applied the changes specified
**	in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int			ft_spec_o(t_convspecs *cs, unsigned long long int num)
{
	char		s[(cs->pre > 23 ? cs->pre : 23) + 2];
	int			i;
	char		*base;

	i = (cs->pre > 23 ? cs->pre : 23) + 1;
	base = "01234567";
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = base[0] : 1;
	while (cs->pre-- > 0 || num)
	{
		s[--i] = base[num % 8];
		num /= 8;
	}
	cs->alt && s[i] != base[0] ? s[--i] = base[0] : 1;
	cs->alt = 0;
	return (ft_printer(cs, &s[i]));
}

/*
**	Prints, in hexadecimal base format, the string  that represents the
**	unsigned long long integer 'num' once applied the changes specified
**	in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int			ft_spec_px(t_convspecs *cs, unsigned long long int num)
{
	char		s[(cs->pre > 21 ? cs->pre : 21) + 1];
	int			i;
	char		*base;

	!num ? cs->alt = 0 : 1;
	if (cs->padd == '0' && (cs->spec == 'p' || cs->alt))
	{
		cs->pre = cs->pre < cs->width - 2 ? cs->width - 2 : cs->pre;
		cs->width = 0;
	}
	i = cs->pre > 21 ? cs->pre : 21;
	base = cs->spec == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = base[0] : 1;
	while (cs->pre-- > 0 || num)
	{
		s[--i] = base[num % 16];
		num /= 16;
	}
	return (ft_printer(cs, &s[i]));
}

/*
**	Prints the string  that represents the unsigned long long integer 'num' once
**	applied the changes specified in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int			ft_spec_u(t_convspecs *cs, unsigned long long int num)
{
	char	s[(cs->pre > 21 ? cs->pre : 21) + 1];
	int		i;

	i = cs->pre > 21 ? cs->pre : 21;
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = '0' : 1;
	while (cs->pre-- > 0 || num)
	{
		s[--i] = num % 10 + '0';
		num /= 10;
	}
	return (ft_printer(cs, &s[i]));
}
