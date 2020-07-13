/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sjofree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:14:32 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 14:15:58 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates (with malloc(3)) and returns a new string, which is the
**	result of the concatenation of ’s1’ and ’s2’.
**	Depending on fr, it frees only s1 (for fr == 1), only s2 (for fr == 2),
** 	both (for fr == 3) or none of them (fot fr == 0).
**	It returns NULL if any s1 or s2 doesn't exist, or fr is not among
**	the expected values.
*/

#include "libft.h"

char	*ft_sjofree(char *s1, char *s2, short int fr)
{
	char	*s;

	if (!s1 || !s2 || fr < 0 || fr > 3)
		return (NULL);
	s = ft_strjoin(s1, s2);
	if (fr == 1 || fr == 3)
	{
		free(s1);
		s1 = NULL;
	}
	if (fr == 2 || fr == 3)
	{
		free(s2);
		s2 = NULL;
	}
	return (s);
}
