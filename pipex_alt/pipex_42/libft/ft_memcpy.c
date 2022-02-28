/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:22:36 by athirion          #+#    #+#             */
/*   Updated: 2021/11/27 14:35:25 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d_cpy;
	char		*s_cpy;

	i = 0;
	d_cpy = (char *) dst;
	s_cpy = (char *) src;
	if (!dst || !src)
		return (dst);
	while (i < n)
	{
		d_cpy[i] = s_cpy[i];
		i ++;
	}
	return (dst);
}
