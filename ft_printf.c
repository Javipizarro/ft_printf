/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:58:45 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/07 01:04:33 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*	BORRAR	*/	#include <stdio.h>

int		ft_err(const char *str)
{
	char		*err_fmt1;
	char		*err_fmt2;
	char		*err_fmt3;
	int			i;

	i = 0;
	err_fmt1 = "\n----- ERROR: the \'";
	err_fmt2 = "\' in \"";
	err_fmt3 = "\" is not supported. -----\n";
	ft_putstr_fd(err_fmt1, 2);
	write (2, &str[i], 1);
	ft_putstr_fd(err_fmt2, 2);
	while (str[i] != '%')
		i--;
	write (2, &str[i], 1);
	while (str[i] && str[i] != 'c' && str[i] != 's' && str[i] != 'p'
	&& str[i] != 'd' && str[i] != 'i' && str[i] != 'u' && str[i] != 'x'
	&& str[i] != 'X' && str[i] != 'f' && str[i] != 'e' && str[i] != 'g'
	&& str[i] != 'n' && i <= 6)
		write(2, &str[++i], 1);
	ft_putstr_fd(err_fmt3, 2);
	return (-1);
}

void	ft_flager(const char **str, t_convspecs *cs)
{
	while (**str == '0' || **str == '-' || **str == ' '
	|| **str == '+' || **str == '#')
	{
		**str == '-' ? cs->adj =  '-' : 1;
		**str == '0' ? cs->padd =  '0' : 1;
		(**str == ' ') && (cs->sign != '+') ? cs->sign =  ' ' : 1;
		**str == '+' ? cs->sign = '+' : 1;
		**str == '#' ? cs->alt = '#' : 1;
		(*str)++;
	}
//	cs->adj == '-' ? cs->padd = ' ' : 1;
//	printf("\nadj =>\t'%c'\npadd => \t'%c'\nsign => \t'%c'\nalt =>  \t'%c'\n", cs->adj, cs->padd, cs->sign, cs->alt);
}

void	ft_width_pre(const char **str, t_convspecs *cs, va_list args)
{
	if (**str == '*' && (*str)++)
		cs->width = va_arg(args, int);
	else if (ft_isdigit(**str))
	{	
		cs->width = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
	}
	if (cs->width < 0 && (cs->width *= -1))
		cs->adj = '-';
	if (**str == '.' && (*str)++)
	{
		if (**str == '*' && (*str)++)
			cs->pre = va_arg(args, int);
		else if (!(ft_isdigit(**str)))
			cs->pre = 0;
		else if (ft_isdigit(**str))
		{
			cs->pre = ft_atoi(*str);
			while (ft_isdigit(**str))
				(*str)++;
		}
	}
	cs->adj == '-' ? cs->padd = ' ' : 1;
//	printf("\nwidth =>\t'%i'\npre =>  \t'%i'\n", cs->width, cs->pre);
}

void	ft_lenth(const char **str, t_convspecs *cs)
{
	if (**str == 'L' && (*str)++)
			cs->len = 'L';
	else if (**str == 'l' && (*str)++)
	{
		if (**str == 'l' && (*str)++)
			cs->len = 'L';
		else
			cs->len = 'l';
	}
	else if (**str == 'h' && (*str)++)
	{
		if (**str == 'h' && (*str)++)
			cs->len = 'H';
		else
			cs->len = 'h';
	}
	cs->spec = *(*str)++;
//	printf("\nlen =>\t'%c'\n", cs->len);
}

int		ft_builder(t_convspecs *cs, char **s)
{
	cs->width -= ft_strlen(*s);
	if (cs->padd == ' ' && cs->sign)
		*s = ft_sjofree(ft_charlloc(1, cs->sign), *s, 3);
	if ((cs->width -= (cs->sign ? 1 : 0)) > 0)
		*s = cs->adj ? ft_sjofree(*s, ft_charlloc(cs->width, cs->padd), 3)
		: ft_sjofree(ft_charlloc(cs->width, cs->padd), *s, 3);
	if (cs->sign && cs->padd == '0')
		*s = ft_sjofree(ft_charlloc(1, cs->sign), *s, 3);
	
	return (0);
}

int		ft_spec(t_convspecs *cs, t_n **n, va_list args, char **s)
{
	!(cs->spec == 'c' || cs->spec == 's') && cs->pre >= 0 ? cs->padd = ' ' : 1;
	cs->spec == 'c' || cs->spec == 's' || cs->spec == 'x' || cs->spec == 'X' ||
	cs->spec == 'p' || cs->spec == 'u' ? cs->sign = 0 : 1;
	if (cs->spec == '%')
		*s = ft_spec_cu((unsigned int)cs->spec, cs, n);
	else if (cs->spec == 's')
		*s = ft_spec_s(va_arg(args, char*), cs);
	else if ((cs->spec == 'u' && cs->len == 'H') || cs->spec == 'c')
		*s = ft_spec_cu((unsigned char)va_arg(args, int), cs, n);
	else if (cs->spec == 'u' && cs->len == 'h')
		*s = ft_spec_cu((unsigned short int)va_arg(args, int), cs, n);
	else if (cs->spec == 'u' && !cs->len)
		*s = ft_spec_cu((unsigned int)va_arg(args, int), cs, n);
	else if (cs->spec == 'u' && cs->len == 'l')
		*s = ft_spec_cu((unsigned long int)va_arg(args, int), cs, n);
	else if (cs->spec == 'u' && cs->len == 'L')
		*s = ft_spec_cu((unsigned long long int)va_arg(args, int), cs, n);
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'H')
		*s = ft_spec_di((signed char)va_arg(args, int), cs);
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'h')
		*s = ft_spec_di((short int)va_arg(args, int), cs);
	else if ((cs->spec == 'd' || cs->spec == 'i') && !cs->len)
		*s = ft_spec_di((int)va_arg(args, int), cs);
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'l')
		*s = ft_spec_di((long int)va_arg(args, int), cs);
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'L')
		*s = ft_spec_di((long long int)va_arg(args, int), cs);
	else if (cs->spec == 'p')
		*s = ft_spec_px((unsigned long int)va_arg(args, void*), cs);
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'H')
		*s = ft_spec_px((unsigned char)va_arg(args, int), cs);
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'h')
		*s = ft_spec_px((unsigned short int)va_arg(args, int), cs);
	else if ((cs->spec == 'x' || cs->spec == 'X') && !cs->len)
		*s = ft_spec_px((unsigned int)va_arg(args, int), cs);
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'l')
		*s = ft_spec_px((unsigned long int)va_arg(args, int), cs);
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'L')
		*s = ft_spec_px((unsigned long long int)va_arg(args, int), cs);
	else if (cs->spec == 'f' || cs->spec == 'e' || cs->spec == 'g')
		*s = ft_flotoa(va_arg(args, double), 6, cs->spec);
	else if (cs->spec == 'n')
		ft_saven(n, args/*, cs*/);
	else
		return (-1);
	return (*s ? ft_builder(cs, s) : 0);
}

int		ft_printf(const char *str, ...)
{
	va_list		args;
	char		*s;
	t_n			*n;
	t_convspecs	*cs;

	va_start(args, str);
	s = NULL;
	n = ft_newn(NULL, 0);
	while (*str)
	{
		if (*str != '%' && (n->nchr += 1))
			write(1, str++, 1);
		else if (*str++)
		{
			cs = ft_csinit();
			ft_flager(&str, cs);
			ft_width_pre(&str, cs, args);
			ft_lenth(&str, cs);
			if (ft_spec(cs, &n, args, &s) < 0)
				return (ft_err(--str));
			free(cs);
			cs = NULL;
		}
		if (s)
		{
			n->nchr += ft_strlen(s);
			ft_putstr_fd(s, 1);
			free(s);
			s = NULL;
		}
	}
	va_end(args);
	return (ft_asignn(n));
}

int		main(void)
{   
//	printf("u\t%%hhu=%hhu %%hu=%hu %%u=%u %%lu=%lu %%llu=%llu\n", CHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
//	ft_printf("u\t%%hhu=%hhu %%hu=%hu %%u=%u %%lu=%lu %%llu=%llu\n", CHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
//	printf("i\t%%hhi=%hhi %%hi=%hi %%i=%i %%li=%li %%lli=%lli\n", SCHAR_MAX, SHRT_MAX, INT_MAX, LONG_MAX, LLONG_MAX);
//	ft_printf("i\t%%hhi=%hhi %%hi=%hi %%i=%i %%li=%li %%lli=%lli\n", SCHAR_MAX, SHRT_MAX, INT_MAX, LONG_MAX, LLONG_MAX);
//	printf("i\t%%hhi=%hhi %%hi=%hi %%i=%i %%li=%li %%lli=%lli\n", SCHAR_MIN, SHRT_MIN, INT_MIN, LONG_MIN, LLONG_MIN);
//	ft_printf("i\t%%hhi=%hhi %%hi=%hi %%i=%i %%li=%li %%lli=%lli\n", SCHAR_MIN, SHRT_MIN, INT_MIN, LONG_MIN, LLONG_MIN);
//	printf("x\t%%hhx=%hhx %%hx=%hx %%x=%x %%lx=%lx %%llx=%llx\n", CHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
//	ft_printf("x\t%%hhx=%hhx %%hx=%hx %%x=%x %%lx=%lx %%llx=%llx\n", CHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
//	printf("sizeof float: %ld, sizeof double: %ld, sizeof long double: %ld\n", sizeof(float), sizeof(double), sizeof(long double));
//	printf("/./n=%i/./ ", printf("%%c=%-5c %%s=%8.5s%n %%p=%018p %%d=/./%+8.5d/./ %%i=/./%-+6.*i/./ %n%%u=%.*u %%x=%#.12x %%X=%#X %%n=%d %%f=%f %%e=%0e %%g=%g ", c, hey, &n1, &hey, i, pre, i, &n2, pre, u, i, i, n1, f, f, f));
//	printf("n1=%d n2=%d\n", n1, n2);
//	n1 = 0;
//	n2 = 0;
//	char c = 'J';
//	int i = 0;
//	unsigned int u = 4698;
//	int pre = 6;
//	char *hey = "hey!!no";
//	int n1 = 0;
//	int n2 = 0;
//	double f = 179e-3;
//	printf("/./n=%i/./ ", printf("%%c=%-5c %%s=%8.5s%n %%p=%18p %%d=/./%+8.5d/./ %%i=/./%-+6.*i/./ %n%%u=%.*u %%x=%#.12x %%X=%#9.6X %%n=%d %%f=%f %%e=%0e %%g=%g ", c, hey, &n1, &hey, i, pre, i, &n2, pre, u, i, i, n1, f, f, f));
//	printf("n1=%d n2=%d\n", n1, n2);
//	n1 = 0;
//	n2 = 0;
//	ft_printf("/./n=%i/./ ", ft_printf("%%c=%-5c %%s=%8.5s%n %%p=%18p %%d=/./%+8.5d/./ %%i=/./%-+6.*i/./ %n%%u=%.*u %%x=%#.12x %%X=%#9.6X %%n=%d %%f=%f %%e=%0e %%g=%g ", c, hey, &n1, &hey, i, pre, i, &n2, pre, u, i, i, n1, f, f, f));
//	ft_printf("n1=%d n2=%d\n", n1, n2);
	printf("printf:\n");
	printf("%d", printf("%0*i", -7, -54));
	printf("\n");
	printf("ft_printf:\n");
	ft_printf("%d", ft_printf("%0*i", -7, -54));
	printf("\n");
}
