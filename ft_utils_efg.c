/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_efg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 17:24:58 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 21:59:32 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	The ft_flotoa function group, converts the double 'f' according to
**	the conversion specifier 'spec' and precision 'pre'.
**	The accepted conversion specifiers are 'e', 'f' and 'g'.
**
**	With spec 'e' the double argument is rounded and converted in the style
**	[-]d.dddeÂ±dd where there is one digit before the decimal-point
**	character and the number of digits after it is equal to the precision;
**	if the precision is negative is taken as zero, if the precision is
**	zero, no decimal-point character appears. The exponent always contains
**	at least two digits; if the value is zero, the exponent is 00.
**
**	With spec 'f' the double argument is rounded and converted to decimal
**	notation in the style [-]ddd.ddd, where the number of digits after the
**	decimal-point character is equal to the precision; if the precision
**	is negative is taken as zero, if the precision is zero, no decimal-point
**	character appears. If a decimal point appears, at least one digit appears
**	before it.
**
**	With spec 'g' the double argument is converted in style f or e. The
**	precision specifies the number of significant digits; if the precision
**	is zero, it is treated as 1. Style e is used if the exponent from its
**	conversion is less than -4 or greater than or equal to the precision.
**	Trailing zeros are removed from the fractional part of the result;
**	a decimal point appears only if it is followed by at least one digit.
*/

void		ft_alternative(t_convspecs *cs, int *len, int *dot, int *i)
{
	if (*len == *dot + (!cs->alt ? 1 : 2))
		*len = *dot + (!cs->alt ? 0 : 2);
	*i = !cs->alt ? 1 : 2;
	*len = *len == *dot + *i ? *dot + *i : *len;
	*i = *len - 1;
	cs->alt = 0;
}

long double	ft_dv(int exp)
{
	long double	div;

	div = 1;
	while (exp)
	{
		div = exp < 0 ? div / 10 : div * 10;
		exp < 0 ? exp++ : exp--;
	}
	return (div);
}

int			ft_exp(t_convspecs *cs, int exp)
{
	char	s[((exp > 99 || exp < -99) ? 3 : 2) + 3];
	int		i;
	int		j;
	char	spec;

	if (cs->spec == 'f' || cs->spec == 'j')
		return (0);
	s[0] = 'e';
	s[1] = exp < 0 ? '-' : '+';
	exp = exp < 0 ? -(exp) : exp;
	i = (exp > 99 ? 3 : 2) + 2;
	s[i] = 0;
	j = 2;
	while (j-- > 0 || exp)
	{
		s[--i] = (char)((exp % 10) + 48);
		exp /= 10;
	}
	spec = cs->spec;
	cs = ft_csinit();
	cs->spec = spec;
	return (ft_printer(cs, s));
}

int			ft_base(t_convspecs *cs, long double f, int len, int exp)
{
	char		s[len + 1];
	int			dot;
	int			i;

	i = 0;
	s[i++] = '0';
	1 / f < 0 ? cs->sign = '-' : 1;
	f = (1 / f < 0 ? -f : f) / ft_dv((cs->spec == 'f' || cs->spec == 'j') &&
	exp < 0 ? 0 : exp);
	while (i < len - 1 && (s[i++] = (char)f + 48))
		f = (f - (int)f) * 10;
	if ((f > 5 || (f == 5 && s[i - 1] % 2)) && i--)
		while ((s[i] = s[i] == '9' ? '0' : (s[i]) + 1) == '0')
			i--;
	dot = s[0] == '0' ? 2 : 1;
	dot += ((cs->spec == 'f' || cs->spec == 'j') && exp >= 0 ? exp : 0);
	if ((cs->spec == 'a' || cs->spec == 'j') && !cs->alt)
		while (len - 2 >= dot && s[len - 2] == '0')
			len--;
	ft_alternative(cs, &len, &dot, &i);
	while (i > dot && i--)
		s[i + 1] = s[i];
	s[dot] = '.';
	s[len] = 0;
	return (ft_printer(cs, s[0] == '0' ? &s[1] : s));
}

int			ft_spec_efg(t_convspecs *cs, long double f)
{
	short int	exp;
	long double	ff;
	short int	len;

	exp = 0;
	ff = 1 / f < 0 ? -f : f;
	while ((ff >= 10 && ++exp) || (ff < 1 && --exp))
		ff = ff < 1 ? ff * 10 : ff / 10;
	cs->pre = cs->pre < 0 ? 6 : cs->pre;
	cs->pre = cs->spec == 'g' && cs->pre > 0 ? cs->pre - 1 : cs->pre;
	len = 1 + cs->pre + (cs->spec == 'f' ? exp : 0);
	ff = (1 / f < 0 ? -f : f) / ft_dv(exp);
	while (ff >= 9 && len--)
		ff = (ff - (int)ff) * 10;
	exp += len <= 0 && ff >= 5 ? 1 : 0;
	if (cs->spec == 'g')
		cs->spec = exp < -4 || exp > cs->pre ? 'a' : 'j';
	len = cs->pre + 3;
	len += cs->spec == 'f' && exp > 0 ? exp : 0;
	len -= cs->spec == 'j' && exp < 0 ? exp : 0;
	if (cs->spec == 'a' || cs->spec == 'e')
		cs->width -= exp > 99 || exp < -99 ? 5 : 4;
	return (ft_base(cs, f, len, exp) + ft_exp(cs, exp));
}
