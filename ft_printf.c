/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:58:45 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 16:44:58 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	write(2, &str[i], 1);
	ft_putstr_fd(err_fmt2, 2);
	while (str[i] != '%')
		i--;
	write(2, &str[i], 1);
	while (str[i] && str[i] != 'c' && str[i] != 's' && str[i] != 'p'
	&& str[i] != 'd' && str[i] != 'i' && str[i] != 'u' && str[i] != 'x'
	&& str[i] != 'X' && str[i] != 'f' && str[i] != 'e' && str[i] != 'g'
	&& str[i] != 'n' && i <= 6)
		write(2, &str[++i], 1);
	ft_putstr_fd(err_fmt3, 2);
	return (-1);
}

int		ft_spec2(t_convspecs *cs, t_n **n, va_list args)
{
	if (cs->spec == 'p')
		(*n)->nchr += ft_spec_px(cs, (unsigned long int)va_arg(args, void*));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'H')
		(*n)->nchr += ft_spec_px(cs, (unsigned char)va_arg(args, int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'h')
		(*n)->nchr += ft_spec_px(cs, (unsigned short int)va_arg(args, int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && !cs->len)
		(*n)->nchr += ft_spec_px(cs, (unsigned int)va_arg(args, int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'l')
		(*n)->nchr += ft_spec_px(cs, (unsigned long int)va_arg(args, long int));
	else if ((cs->spec == 'x' || cs->spec == 'X') && cs->len == 'L')
		(*n)->nchr += ft_spec_px(cs,
		(unsigned long long int)va_arg(args, long long int));
	else if ((cs->spec == 'f' || cs->spec == 'e' || cs->spec == 'g') &&
	!cs->len)
		(*n)->nchr += ft_spec_efg(cs,
		(double)va_arg(args, double));
	else if ((cs->spec == 'f' || cs->spec == 'e' || cs->spec == 'g')
	&& cs->len == 'L')
		(*n)->nchr += ft_spec_efg(cs, (long double)va_arg(args, long double));
	else if (cs->spec == 'n')
		ft_saven(n, args, cs);
	else
		return (-1);
	return (0);
}

int		ft_spec1(t_convspecs *cs, t_n **n, va_list args)
{
	if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'H')
		(*n)->nchr += ft_spec_di(cs, (signed char)va_arg(args, int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'h')
		(*n)->nchr += ft_spec_di(cs, (short int)va_arg(args, int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && !cs->len)
		(*n)->nchr += ft_spec_di(cs, (int)va_arg(args, int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'l')
		(*n)->nchr += ft_spec_di(cs, (long int)va_arg(args, long int));
	else if ((cs->spec == 'd' || cs->spec == 'i') && cs->len == 'L')
		(*n)->nchr += ft_spec_di(cs, (long long int)
		va_arg(args, long long int));
	else if (cs->spec == 'o' && cs->len == 'H')
		(*n)->nchr += ft_spec_o(cs, (unsigned char)va_arg(args, int));
	else if (cs->spec == 'o' && cs->len == 'h')
		(*n)->nchr += ft_spec_o(cs, (unsigned short int)va_arg(args, int));
	else if (cs->spec == 'o' && !cs->len)
		(*n)->nchr += ft_spec_o(cs, (unsigned int)va_arg(args, int));
	else if (cs->spec == 'o' && cs->len == 'l')
		(*n)->nchr += ft_spec_o(cs, (unsigned long int)va_arg(args, long int));
	else if (cs->spec == 'o' && cs->len == 'L')
		(*n)->nchr += ft_spec_o(cs, (unsigned long long int)
		va_arg(args, long long int));
	else
		return (ft_spec2(cs, n, args));
	return (0);
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
		(*n)->nchr += ft_spec_u(cs, (unsigned long long int)
		va_arg(args, long long int));
	else
		return (ft_spec1(cs, n, args));
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
