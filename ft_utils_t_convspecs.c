/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_t_convspecs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:42:46 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 18:40:41 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
**  Parse the string pointed by '**str' find the flags if there are any,
**  and fills in the corresponding fields in the t_convspecs structure.
*/

void		ft_flager(const char **str, t_convspecs *cs)
{
	while (**str == '0' || **str == '-' || **str == ' '
	|| **str == '+' || **str == '#')
	{
		**str == '-' ? cs->adj = '-' : 1;
		**str == '0' ? cs->padd = '0' : 1;
		(**str == ' ') && (cs->sign != '+') ? cs->sign = ' ' : 1;
		**str == '+' ? cs->sign = '+' : 1;
		**str == '#' ? cs->alt = '#' : 1;
		(*str)++;
	}
}

/*
**  Parse the string pointed by '**str' find the width and pre if there are any,
**  and fills in the corresponding fields in the t_convspecs structure.
*/

void		ft_width_pre(const char **str, t_convspecs *cs, va_list args)
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
}

/*
**  Parse the string pointed by '**str' find the specified lenth if there are
**  any, and fills in the corresponding fields in the t_convspecs structure.
*/

void		ft_lenth(const char **str, t_convspecs *cs)
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
}
