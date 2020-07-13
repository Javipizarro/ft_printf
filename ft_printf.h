/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 12:05:59 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 21:50:10 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "./libft/libft.h"

typedef struct	s_n
{
	long long int	*arg;
	long long int	nchr;
	struct s_n		*prev;
	struct s_n		*next;
}				t_n;

typedef struct	s_convspecs
{
	char			sign;
	char			adj;
	char			padd;
	char			alt;
	int				width;
	int				pre;
	char			len;
	char			spec;
}				t_convspecs;

int				ft_asignn(t_n *current);
t_convspecs		*ft_csinit(void);
void			ft_flager(const char **str, t_convspecs *cs);
void			ft_lenth(const char **str, t_convspecs *cs);
t_n				*ft_newn(t_n *prev, int nchr);
int				ft_printer(t_convspecs *cs, char *s);
int				ft_printf(const char *str, ...);
void			ft_saven(t_n **n, va_list args, t_convspecs *cs);
int				ft_spec_c(t_convspecs *cs, char c);
int				ft_spec_u(t_convspecs *cs, unsigned long long int num);
int				ft_spec_di(t_convspecs *cs, long long int num);
int				ft_spec_efg(t_convspecs *cs, long double f);
int				ft_spec_o(t_convspecs *cs, unsigned long long int num);
int				ft_spec_px(t_convspecs *cs, unsigned long long int num);
int				ft_spec_s(t_convspecs *cs, char *s);
void			ft_width_pre(const char **str, t_convspecs *cs, va_list args);

#endif
