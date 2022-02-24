/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 08:13:33 by athirion          #+#    #+#             */
/*   Updated: 2021/11/26 10:06:44 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

static size_t	ft_len_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	i = 0;
	while (ft_check_set(s1[i], set))
	{
		len --;
		i ++;
	}
	i = ft_strlen(s1) - 1;
	while (ft_check_set(s1[i], set) && len)
	{
		len --;
		i --;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	size_t			len;
	char			*str;

	len = ft_len_strtrim(s1, set);
	if (len)
	{
		i = 0;
		while (ft_check_set(s1[i], set))
			i ++;
		str = ft_substr(s1, i, len);
		if (str)
			return (str);
	}
	return (ft_strdup(""));
}
