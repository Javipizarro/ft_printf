/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 17:24:58 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/09 12:42:51 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


///
#include <stdio.h>
///

#include "ft_printf.h"

/*
**	Receives the string s apply the specs adj, sign and padd, and prints
**	the result.
**	Returns the number of characters printed.
*/
//	if (cs->spec == 'p' || (cs->spec == 'x' && cs->alt))
//		return (ft_strjoin("0x", &s[i]));
//	else if (cs->spec == 'X' && cs->alt)
//		return (ft_strjoin("0X", &s[i]));

int		ft_printer(t_convspecs *cs, char *s)
{
	int		add;
	int 	len;

	add = 0;
	len = ft_strlen(s);
	cs->width -=  cs->sign ? 1 : 0;
	cs->width -=  (cs->spec == 'p' || cs->alt) ? 2 : 0;
	add += (cs->spec == 'p' || cs->alt) ? 2 : 0;
	if (cs->sign && (cs->adj || cs->padd == '0') && ++add)
		write(1, &cs->sign, 1);
	if ((cs->adj || cs->padd == '0') && (cs->spec == 'p' || cs->alt))
		write(1, cs->spec == 'X' ? "0X" : "0x", 2);
	if (cs->adj == '-')
		write(1, s, len);
	while (cs->width-- > len && ++add)
		write(1, &cs->padd, 1);
	if (cs->sign && !cs->adj && cs->padd == ' ' && ++add)
		write(1, &cs->sign, 1);
	if (!cs->adj && cs->padd == ' ' && (cs->spec == 'p' || cs->alt))
		write(1, cs->spec == 'X' ? "0X" : "0x", 2);
	if (!cs->adj)
		write(1, s, len);
	return (len + add);
}

/*
**	Prints the char 'c' once applied the changes
**	specified in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int		ft_spec_c(t_convspecs *cs, char c)
{
	int		padd;
	
	padd = 0;
	if (cs->adj == '-')
		write(1, &c, 1);
	while (++padd < cs->width)
		if (cs->padd == '0' && !cs->adj)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	if (!cs->adj)
		write(1, &c, 1);
	return (padd);
}

/*
**	Prints the string  that represents the long long integer 'num' once
**	applied the changes specified in the t_convspecs struct pointed by *cs.
**	Negative numbers are also handled.
**	Returns the number of characters printed.
*/

int		ft_spec_di(t_convspecs *cs, long long int num)
{
	char	s[cs->pre > 21 ? cs->pre : 21];
	int		i;

	i = (cs->pre > 21 ? cs->pre : 21) - 1;
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = '0' : 1;
	if (num < 0 && 	(cs->sign = '-'))
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
	return(ft_printer(cs, &s[i]));
}

/*
**	Prints the string 's' once applied the changes expecified in
**	the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int		ft_spec_s(t_convspecs *cs, char *s)
{
	int		padd;
	int		len;

	s = !s ? "(null)" : s;
	len = ft_strlen(s);
	len = cs->pre >= 0 && cs->pre < len ? cs->pre : len;
	if (cs->adj == '-')
		write(1, s, len);
	padd = 0;
	while (cs->width-- > len && ++padd)
		write(1, &cs->padd, 1);
	if (!cs->adj)
		write(1, s, len);
	return (len + padd);
}

/*
**	Prints, in hexadecimal base format, the string  that represents the
**	unsigned long long integer 'num' once applied the changes specified
**	in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int		ft_spec_px(t_convspecs *cs, unsigned long long int num)
{
	char		s[cs->pre > 21 ? cs->pre : 21];
	int			i;
	char		*base;

	if (cs->padd == '0' && (cs->spec == 'p' || cs->alt))
	{
		cs->pre = cs->pre < cs->width - 2 ? cs->width - 2 : cs->pre;
		cs->width = 0;
	}
	i = (cs->pre > 21 ? cs->pre : 21) - 1;
	base = cs->spec == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = base[0] : 1;
	while (cs->pre-- > 0 || num)
	{
		s[--i] = base[num % 16];
		num /= 16;
	}
	return(ft_printer(cs, &s[i]));
}

/*
**	Prints the string  that represents the unsigned long long integer 'num' once
**	applied the changes specified in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int		ft_spec_u(t_convspecs *cs, unsigned long long int num)
{
	char	s[cs->pre > 21 ? cs->pre : 21];
	int		i;

	i = (cs->pre > 21 ? cs->pre : 21) - 1;
	s[i] = 0;
	!num && cs->pre < 0 ? s[--i] = '0' : 1;
	while (cs->pre-- > 0 || num)
	{
		s[--i] = num % 10 + '0';
		num /= 10;
	}
	return(ft_printer(cs, &s[i]));
}

/*
**	Allocates (with malloc(3)), creates fresh t_convspecs
**	structure, ready to work with it.
**	Returns a pointer to the created element.
*/

t_convspecs	*ft_csinit(void)
{
    t_convspecs	*new;

	if (!(new = malloc(sizeof(t_convspecs))))
		return (NULL);
	new->sign = 0;
	new->adj = 0;
	new->padd = ' ';
	new->alt = 0;
	new->width = 0;
	new->pre = -1;
	new->len = 0;
	new->spec = 0;
	return (new);
}

/*
**	Allocates (with malloc(3)) and creates a new t_n double linked list
**	object in the space pointed by 'prev', and stores the number 'n'
**	of character read in nchr.
*/

t_n		*ft_newn(t_n *prev, int nchr)
{
	t_n		*new;

	if (!(new = malloc(sizeof(t_n))))
		return (NULL);
	new->prev = prev;
	new->arg = NULL;
	new->nchr = nchr;
	new->next = NULL;
	return (new);
}

/*
**	Given a valid link in a t_n list, it traverses the whole chain,
**	from first to last link, assigning the nchar values to the variables
**	pointed by arg and freeing the links as it goes.
*/

int		ft_asignn(t_n *current)
{
	int n;

	n = current->nchr;
	while (current->prev)
		current = current->prev;
	while (current->arg)
	{
		*(current->arg) = current->nchr;
		current = current->next;
		free(current->prev);
	}
	free(current);
	current = NULL;
	return (n);
}

/*
**	Algo hará
*/
/*
void	ft_saven(t_n **n, va_list args, t_convspecs *cs)
{
	if (cs->len == 'H')
		(*n)->arg = (signed char *)va_arg(args, int*);
	else if (cs->len == 'h')
		(*n)->arg = (short int *)va_arg(args, int*);
	else if (!cs->len)
		(*n)->arg = va_arg(args, int*);
	else if (cs->len == 'l')
		(*n)->arg = (long int *)va_arg(args, int*);
	else if (cs->len == 'L')
		(*n)->arg = (long long int *)va_arg(args, int*);
	(*n)->next = ft_newn(*n, (*n)->nchr);
	*n = (*n)->next;
}
*/
void	ft_saven(t_n **n, va_list args)
{
	(*n)->arg = va_arg(args, int*);
	(*n)->next = ft_newn(*n, (*n)->nchr);
	*n = (*n)->next;
}

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

int		ft_exp(t_convspecs *cs, int exp)
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

long double		ft_dv(int exp)
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

int		ft_base(t_convspecs *cs, long double f, short int len, short int ex)
{
	char				s[len + 1];
	short int			dot;
	short int			i;

	i = 0;
	s[i++] = '0';
	1/f < 0 ? s[i++] = '-' : 1;
	f = (1/f < 0 ? -f : f) / ft_dv((cs->spec == 'f' || cs->spec == 'j') && ex < 0 ? 0 : ex);
	while (i < len - 1 && (s[i++] = (char)f + 48))
		f = (f - (int)f) * 10;
	if (f > 4.99)
		while (i-- && (s[i] = s[i] == '9' ? '0' : (s[i]) + 1) == '0')
			if (s[i - 1] == '-' ? s[i - 2] = '-' : 0)
				s[i - 1] = '0';
	dot = ((s[0] == '0' || s[0] == '-') ? 2 : 1) + (s[1] == '-' ? 1 : 0);
	dot += ((cs->spec == 'f' || cs->spec == 'j') && ex >= 0 ? ex : 0);
	while ((cs->spec == 'a' || cs->spec == 'j') && len - 2 >= dot && s[len - 2] == '0')
		len--;
	len = len == dot + 1 ? dot : len;
	i = len - 1;
	while (i > dot && i--)
		s[i + 1] = s[i];
	s[dot] = '.';
	s[len] = 0;
	return (ft_printer(cs, s[0] == '0' ? &s[1] : s));
}

//	char	*ft_flotoa(long double f, short int pre, char spec)
int		ft_spec_efg(t_convspecs *cs, long double f)
{
	short int	exp;
	long double	ff;
	short int	len;

	exp = 0;
	ff = 1/f < 0 ? -f : f;
	while ((ff >= 10 && ++exp) || (ff < 1 && --exp))
		ff = ff < 1 ? ff * 10 : ff / 10;
	cs->pre = cs->spec == 'g' && cs->pre <= 0 ? 1 : cs->pre;
	cs->pre = cs->spec == 'g' ? cs->pre - 1 : cs->pre;
	cs->pre = cs->pre < 0 ? 0 : cs->pre;
	len = 1 + cs->pre + (cs->spec == 'f' ? exp : 0);
	ff = (1/f < 0 ? -f : f) / ft_dv(exp);
	while (ff >= 9 && len--)
		ff = (ff - (int)ff) * 10;
	exp = exp + (len <= 0 && ff > 4.99 ? 1 : 0);
	cs->spec = cs->spec == 'g' && (exp < -4 || exp > cs->pre) ? 'a' : cs->spec;
	cs->spec = cs->spec == 'g' ? 'j' : cs->spec;
	len = cs->pre + 3 + (1/f < 0 ? 1 : 0);
	len += cs->spec == 'f' && exp > 0 ? exp : 0;
	len -= cs->spec == 'j' && exp < 0 ? exp : 0;
//	return (ft_sjofree(ft_base(f, len, spec, exp), ft_exp(exp, spec), 3));
	return (ft_base(cs, f, len, exp) + ft_exp(cs, exp));
}

/*
int		main(void)
{
	double d = -9.999e4;
	char *str = ft_flotoa(d, 4, 'g');
	printf("/./%s/./\n", str);
	printf("/./%.4g/./\n", d);
	free(str);
	str = NULL;
}
*/
