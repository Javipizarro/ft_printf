/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:58:45 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 13:42:33 by jpizarro         ###   ########.fr       */
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
	!(cs->spec == 'c' || cs->spec == 's' || cs->spec == 'e' ||
	cs->spec == 'f' || cs->spec == 'g') && cs->pre >= 0 ? cs->padd = ' ' : 1;
	cs->spec == 'c' || cs->spec == 's' || cs->spec == 'u' || cs->spec == 'p' ||
	cs->spec == 'x' || cs->spec == 'X' ? cs->sign = 0 : 1;
	cs->spec == 'c' || cs->spec == 's' || cs->spec == 'd' || cs->spec == 'i' ||
	cs->spec == 'u' || cs->spec == 'p' || cs->spec == 'n' ? cs->alt = 0 : 1;
	cs->pre < 0 && (cs->spec == 'e' || cs->spec == 'f' || cs->spec == 'g') ?
	cs->pre = 6 : 1;
//	printf("\nlen =>\t'%c'\tcs->spec =>\t'%c'\n", cs->len, cs->spec);
}

int		ft_spec(t_convspecs *cs, t_n **n, va_list args)
{
	if (cs->spec == '%')
        (*n)->nchr += ft_spec_c(cs, '%');
	else if (cs->spec == 'c')
        (*n)->nchr += ft_spec_c(cs, (char)va_arg(args, int));
	else if (cs->spec == 's')
		(*n)->nchr += ft_spec_s(cs, va_arg(args, char*));
	else if (cs->spec == 'u' && cs->len == 'H')
		(*n)->nchr += ft_spec_u(cs, (unsigned char)va_arg(args, int));
	else if (cs->spec == 'u' && cs->len == 'h')
		(*n)->nchr += ft_spec_u(cs, (unsigned short int)va_arg(args, int));
	else if (cs->spec == 'u' && !cs->len)
		(*n)->nchr += ft_spec_u(cs, (unsigned int)va_arg(args, int));
	else if (cs->spec == 'u' && cs->len == 'l')
		(*n)->nchr += ft_spec_u(cs, (unsigned long int)va_arg(args, long int));
	else if (cs->spec == 'u' && cs->len == 'L')
		(*n)->nchr += ft_spec_u(cs, (unsigned long long int)va_arg(args, long long int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'H')
		(*n)->nchr += ft_spec_di(cs, (signed char)va_arg(args, int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'h')
		(*n)->nchr += ft_spec_di(cs, (short int)va_arg(args, int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && !cs->len)
		(*n)->nchr += ft_spec_di(cs, (int)va_arg(args, int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'l')
		(*n)->nchr += ft_spec_di(cs, (long int)va_arg(args, long int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'L')
		(*n)->nchr += ft_spec_di(cs, (long long int)va_arg(args, long long int));

	else if (cs->spec == 'o' && cs->len == 'H')
		(*n)->nchr += ft_spec_o(cs ,(unsigned char)va_arg(args, int));
	else if (cs->spec == 'o' && cs->len == 'h')
		(*n)->nchr += ft_spec_o(cs ,(unsigned short int)va_arg(args, int));
	else if (cs->spec == 'o' && !cs->len)
		(*n)->nchr += ft_spec_o(cs ,(unsigned int)va_arg(args, int));
	else if (cs->spec == 'o' && cs->len == 'l')
		(*n)->nchr += ft_spec_o(cs ,(unsigned long int)va_arg(args, long int));
	else if (cs->spec == 'o' && cs->len == 'L')
		(*n)->nchr += ft_spec_o(cs ,(unsigned long long int)va_arg(args, long long int));

	else if (cs->spec == 'p')
		(*n)->nchr += ft_spec_px(cs ,(unsigned long int)va_arg(args, void*));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'H')
		(*n)->nchr += ft_spec_px(cs ,(unsigned char)va_arg(args, int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'h')
		(*n)->nchr += ft_spec_px(cs ,(unsigned short int)va_arg(args, int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && !cs->len)
		(*n)->nchr += ft_spec_px(cs ,(unsigned int)va_arg(args, int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'l')
		(*n)->nchr += ft_spec_px(cs ,(unsigned long int)va_arg(args, long int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'L')
		(*n)->nchr += ft_spec_px(cs ,(unsigned long long int)va_arg(args, long long int));
	else if ((cs->spec == 'f' || cs->spec == 'e' || cs->spec == 'g') && !cs->len)
		(*n)->nchr += ft_spec_efg(cs, (double)va_arg(args, double));
	else if ((cs->spec == 'f' || cs->spec == 'e' || cs->spec == 'g') && cs->len == 'L')
		(*n)->nchr += ft_spec_efg(cs, (long double)va_arg(args, long double));
	else if (cs->spec == 'n')
		ft_saven(n, args, cs);
	else
		return (-1);
	return (0);
}

int		ft_printf(const char *str, ...)
{
	va_list		args;
	t_n			*n;
	t_convspecs	*cs;

	va_start(args, str);
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
			if (ft_spec(cs, &n, args) < 0)
				return (ft_err(--str));
			free(cs);
			cs = NULL;
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
//	int i = 2846;
//	unsigned int u = 4698;
//	int pre = 6;
//	char *hey = "hey!!no";
//	signed char n1 = 0;
//	long long int n2 = 0;
//	double f = -10.99999999;
//	printf("/./n=%i/./ ", printf("%%c=%-5c %%s=%8.5s%hhn %%p=%18p %%d=/./%+8.5d/./ %%i=/./%-+6.*i/./ %lln%%u=%.*u %%x=%#.12x %%X=%#9.6X %%n=%d %%f=%+012f %%e=%e %%g=%g ", c, hey, &n1, &hey, i, pre, i, &n2, pre, u, i, i, n1, f, f, f));
//	printf("n1=%hhd n2=%lld\n", n1, n2);
//	n1 = 0;
//	n2 = 0;
//	ft_printf("/./n=%i/./ ", ft_printf("%%c=%-5c %%s=%8.5s%hhn %%p=%18p %%d=/./%+8.5d/./ %%i=/./%-+6.*i/./ %lln%%u=%.*u %%x=%#.12x %%X=%#9.6X %%n=%d %%f=%+012f %%e=%e %%g=%g ", c, hey, &n1, &hey, i, pre, i, &n2, pre, u, i, i, n1, f, f, f));
//	ft_printf("n1=%hhd n2=%lld\n", n1, n2);
//	printf("printf:\n");
//	printf("%d\n", printf("this %f float", 1.5));
//	printf("ft_printf:\n");
//	ft_printf("%d\n", ft_printf("this %f float", 1.5));
//	printf("\n");

//	DAN PROBLEMAS 
static unsigned long long int		mx_u = ULLONG_MAX;
static char				mx_c = 'G';
static char			   *mx_s = "Hello, World!";
static int				mx_i = 42;
static double			mx_f = 0.625;
static long				mx_li =  4223372036854775800;
static long long		mx_lli = 3223372036654775200;
static short			mx_hi = -3244;
static char				mx_hhi = 'F';



	printf("/./n=%i/./\n", printf(
			"%x%x%x%x%x%X%X%X%X%X\n",
			mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u));
	ft_printf("/./n=%i/./\n", ft_printf(
			"%x%x%x%x%x%X%X%X%X%X\n",
			mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u));
}
