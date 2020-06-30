/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:58:45 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/01 01:03:45 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
