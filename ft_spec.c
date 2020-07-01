/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:58:45 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/01 01:52:03 by jpizarro         ###   ########.fr       */
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
		**str == '-' ? cs->adjus =  '-' : 1;
		**str == '0' ? cs->padd =  '0' : 1;
		(**str == ' ') && (cs->sign != '+') ? cs->sign =  ' ' : 1;
		**str == '+' ? cs->sign = '+' : 1;
		**str == '#' ? cs->alt = '#' : 1;
		(*str)++;
	}
//	ft_printf("\nadjus =>\t'%c'\npadd => \t'%c'\nsign => \t'%c'\nalt =>  \t'%c'\n", cs->adjus, cs->padd, cs->sign, cs->alt);
}

void	ft_width_pre(const char **str, t_convspecs *cs, va_list args)
{
	if (**str == '*' && (*str)++)
		cs->width = va_arg(args, int);
	else if (ft_isdigit(**str))
		
		cs->width = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
	}
	if(**str == '.' && (*str)++)
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
//	printf("\nwidth =>\t'%i'\npre =>  \t'%i'\n", cs->width, cs->pre);
}

void	ft_lenth(const char **str, t_convspecs *cs)
{
	if (**str == 'l' && (*str)++)
	{
		if (**str == 'l' && (*str)++)
			cs->len = 'L';
		else
			cs->len = 'l';
	}
	if (**str == 'h' && (*str)++)
	{
		if (**str == 'h' && (*str)++)
			cs->len = 'H';
		else
			cs->len = 'h';
	}
//	printf("\nlen =>\t'%c'\n", cs->len);
}

void	ft_spec(const char **str, t_n **n, va_list args, char **s)
{
	char	c[2];

	c[1] = 0;
	if ((**str == '%' && (c[0] = '%')) ||
	(**str == 'c' && (!(c[0] = (char)va_arg(args, int)) ? (*n)->nchr++ : 1)))
		*s = ft_strdup(c);
	else if (**str == 's')
		*s = ft_strdup(va_arg(args, char*));
	else if (**str == 'p')
		*s = ft_litoax((unsigned long int)va_arg(args, void*), 'p');
	else if (**str == 'd' || **str == 'i')
		*s = ft_itoa(va_arg(args, int));
	else if (**str == 'u')
		*s = ft_uitoa((unsigned int)va_arg(args, int));
	else if (**str == 'x' || **str == 'X')
		*s = ft_itoax((unsigned int)va_arg(args, int), **str);
	else if (**str == 'f' || **str == 'e' || **str == 'g')
		*s = ft_flotoa(va_arg(args, double), 6, **str);
	else if (**str == 'n')
	{
		(*n)->arg = va_arg(args, int*);
		(*n)->next = ft_newn(*n, (*n)->nchr);
		*n = (*n)->next;
	}
}
/*
int		ft_builder(t_convspecs *cs, char **s)
{
	char *aux;

	else
	{
		ft_err(*str);
		return (-1);
	}
	return (0);
	(*str)++;
}
*/

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
			ft_spec(&str, &n, args, &s);
//			if (ft_builder(cs, &s) < 0)
//				return (-1);
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
	//	Devolver un -1 en caso de error.
}

int		main(void)
{   
	char c = '\0';
	int i = -2148;
	int u = 4295;
	char *hey = "hey!!";
	int n1 = 0;
	int n2 = 0;
	double f = 179e-3;
	printf("sizeof float: %ld, sizeof double: %ld, sizeof long double: %ld\n", sizeof(float), sizeof(double), sizeof(long double));
	printf("/./n=%i/./ ", printf("%%c=%c %%s=%s%n %%p=%p %%d=%d t%%i=%i %n%%u=%u %%x=%x %%X=%X %%n=%d %%f=%f %%e=%0e %%g=%g ", c, hey, &n1, &hey, i, i, &n2, u, i, i, n1, f, f, f));
	printf("n1=%d n2=%d\n", n1, n2);
	n1 = 0;
	n2 = 0;
	ft_printf("/./n=%i/./ ", ft_printf("%%c=%c %%s=%s%n %%p=%p %%d=%d t%%i=%i %n%%u=%u %%x=%x %%X=%X %%n=%d %%f=%f %%e=%0e %%g=%g ", c, hey, &n1, &hey, i, i, &n2, u, i, i, n1, f, f, f));
	ft_printf("n1=%d n2=%d\n", n1, n2);
}
