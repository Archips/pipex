/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:26:34 by athirion          #+#    #+#             */
/*   Updated: 2021/11/26 10:03:50 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s_cpy;
	char	*d_cpy;

	s_cpy = (char *)src;
	d_cpy = (char *)dst;
	if (dst == src)
		return (dst);
	if (s_cpy < d_cpy)
	{
		while (len--)
			d_cpy[len] = s_cpy[len];
		return (dst);
	}
	while (len--)
		*d_cpy++ = *s_cpy++;
	return (dst);
}
