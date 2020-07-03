/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 12:05:59 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/03 05:33:12 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "./libft/libft.h"

typedef struct		s_n
{
	int				*arg;
	int				nchr;
	struct s_n		*prev;
	struct s_n		*next;
}					t_n;

typedef struct		s_convspecs
{
	char			sign;		//	si num <= 0 nada por defecto, '+' un + (prioritario); ' ' espacio como signo
	char			adj;		//	por defecto a la derecha, '-' a la izq
	char			padd;		//	por defecto ' ', '0' solo si adjus dcha
	char			alt;		//	nada por defecto, '#' añade puntos decimales si no los tiene, no elimina 0 finales con g, tb añade prefijos... ECHAR UN VISTAZO AL MAN
	int				width;		//	mín nro de caractéres a imprimir
	int				pre;		//	6 por defecto, precedida de un '.', número de dígitos decimales (e y f) o cifras significativas (g)
	char			len;		//	nada por defecto, 'l' long, 'll' long long, 'h' short
	char			spec;		//	tiene que haber una y solo una
}					t_convspecs;

int			ft_asignn(t_n *current);
t_convspecs	*ft_csinit(void);
char		*ft_flotoa(long double f, short int pre, char type);
char		*ft_itoax(unsigned int n, char x);
char		*ft_litoax(unsigned long int n, char x);
t_n			*ft_newn(t_n *prev, int nchr);
int			ft_printf(const char *str, ...);
void		ft_saven(t_n **n, va_list args);
char		*ft_spec_di(long long int n, t_convspecs *cs);
char		*ft_spec_s(char *str, t_convspecs *cs);

#endif
