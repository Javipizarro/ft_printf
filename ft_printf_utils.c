/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 17:24:58 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/03 13:10:08 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


///
#include <stdio.h>
///

#include "ft_printf.h"

/*
**	Allocates sufficient memory for a copy of the string 'str' once applied
**	a max lenth pre if suitable, does the copy,	and returns a pointer to it.
**	The pointer may subsequently be used as an argument to the function free(3).
*/

char	*ft_spec_s(char *str, t_convspecs *cs)
{
	int		len;
	char	*s;

	if (cs->pre <= 0)
	{
		cs->width -= cs->pre;
		return (ft_strdup(""));
	}
	len = ft_strlen(str);
	len = (cs->pre < len ? cs->pre : len);
	if (!(s = malloc(len + 1)))
		return (NULL);
	ft_memcpy(s, str, len + 1);
	s[len] = 0;
	return (s);
}

/*
**	Allocates (with malloc(3)) and returns a string representing the 
**	long long integer received as an argument or NULL if the allocation fails.
**	If int is negative, the sign will be reflectec in the t_converspec
**	cs->sign field.
*/

char	*ft_spec_di(long long int n, t_convspecs *cs)
{
	char	str[cs->pre > 20 ? cs->pre : 20];
	int		i;

//	printf("pre = %d", cs->pre);
	cs->pre >= 0 ? cs->padd = ' ' : 1;
	i = (cs->pre > 20 ? cs->pre : 20) - 1;
	str[i] = 0;
	if (!n) //restar 1 a pre cuando esto ocurra
		str[--i] = '0';
	if (n < 0)
	{
		cs->sign = '-';
		str[--i] = '0' - n % 10;
		n /= -10;
	}
	while (cs->pre-- > 0 || n % 10 || n / 10)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	return (ft_strdup(&str[i]));
}

/*
**	Allocates (with malloc(3)) and returns a string representing the
**	integer received as 'n' transformed to unsigned hexa as x or X
**	would do in printf or NULL if the allocation fails.
**	Negative numbers are also handled.
*/

char	*ft_itoax(unsigned int n, char x)
{
	char		ret[9];
	short int	i;
	char		*base;

	if (x == 'x')
		base = "0123456789abcdef";
	else if (x == 'X')
		base = "0123456789ABCDEF";
	else
		return ("Error, invalid 'x' argument");
	i = 8;
	ret[i] = 0;
	while (n % 16 || n / 16)
	{
		ret[--i] = base[n % 16];
		n /= 16;
	}
	if (i == 8)
		ret[--i] = base[0];
	return (ft_strdup(&ret[i]));
}

/*
**	Allocates (with malloc(3)) and returns a string representing the
**	long integer received as 'n' transformed to unsigned hexa as lx or lX
**	would do in printf or NULL if the allocation fails.
**	Negative numbers are also handled.
*/

char	*ft_litoax(unsigned long int n, char x)
{
	char		ret[19];
	short int	i;
	char		*base;

	if (x == 'x' || x == 'p')
		base = "0123456789abcdef";
	else if (x == 'X')
		base = "0123456789ABCDEF";
	else
		return ("Error, invalid 'x' argument");
	i = 18;
	ret[i] = 0;
	while (n % 16 || n / 16)
	{
		ret[--i] = base[n % 16];
		n /= 16;
	}
	if (i == 18)
		ret[--i] = base[0];
	if (x == 'p')
		return (ft_strjoin("0x", &ret[i]));
	return (ft_strdup(&ret[i]));
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

char	*ft_exp(int exp, char spec)
{
	char	s[((exp > 99 || exp < -99) ? 3 : 2) + 3];
	int		i;
	int		j;

	if (spec == 'f' || spec == 'j')
		return (ft_strdup(""));
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
	return (ft_strdup(s));
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

char	*ft_base(long double f, short int len, char spe, short int ex)
{
	char				s[len + 1];
	short int			dot;
	short int			i;

	i = 0;
	s[i++] = '0';
	f < 0 ? s[i++] = '-' : 1;
	f = (f < 0 ? -f : f) / ft_dv((spe == 'f' || spe == 'j') && ex < 0 ? 0 : ex);
	while (i < len - 1 && (s[i++] = (char)f + 48))
		f = (f - (int)f) * 10;
	if (f > 4.99)
		while (i-- && (s[i] = s[i] == '9' ? '0' : (s[i]) + 1) == '0')
			if (s[i - 1] == '-' ? s[i - 2] = '-' : 0)
				s[i - 1] = '0';
	dot = ((s[0] == '0' || s[0] == '-') ? 2 : 1) + (s[1] == '-' ? 1 : 0);
	dot += ((spe == 'f' || spe == 'j') && ex >= 0 ? ex : 0);
	while ((spe == 'a' || spe == 'j') && len - 2 >= dot && s[len - 2] == '0')
		len--;
	len = len == dot + 1 ? dot : len;
	i = len - 1;
	while (i > dot && i--)
		s[i + 1] = s[i];
	s[dot] = '.';
	s[len] = 0;
	return (ft_strdup(s[0] == '0' ? &s[1] : s));
}

char	*ft_flotoa(long double f, short int pre, char spec)
{
	short int	exp;
	long double	ff;
	short int	len;

	if (spec != 'e' && spec != 'f' && spec != 'g')
		return (ft_strdup("\n\n\t/./flotoa spec ERROR/./\n\n"));
	exp = 0;
	ff = f < 0 ? -f : f;
	while ((ff >= 10 && ++exp) || (ff < 1 && --exp))
		ff = ff < 1 ? ff * 10 : ff / 10;
	pre = spec == 'g' && pre <= 0 ? 1 : pre;
	pre = spec == 'g' ? pre - 1 : pre;
	pre = pre < 0 ? 0 : pre;
	len = 1 + pre + (spec == 'f' ? exp : 0);
	ff = (f < 0 ? -f : f) / ft_dv(exp);
	while (ff >= 9 && len--)
		ff = (ff - (int)ff) * 10;
	exp = exp + (len <= 0 && ff > 4.99 ? 1 : 0);
	spec = spec == 'g' && (exp < -4 || exp > pre) ? 'a' : spec;
	spec = spec == 'g' ? 'j' : spec;
	len = pre + 3 + (f < 0 ? 1 : 0);
	len += spec == 'f' && exp > 0 ? exp : 0;
	len -= spec == 'j' && exp < 0 ? exp : 0;
	return (ft_sjofree(ft_base(f, len, spec, exp), ft_exp(exp, spec), 3));
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
