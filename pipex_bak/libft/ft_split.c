/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:24:45 by athirion          #+#    #+#             */
/*   Updated: 2021/11/26 10:04:40 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	int		i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i ++;
			words ++;
		}
		while (s[i] && s[i] == c)
			i ++;
	}
	return (words);
}

static char	*ft_free_tab(char **tab, int i)
{
	while (tab[i--])
		free((void *)tab[i]);
	free(tab);
	return (NULL);
}

static char	*ft_malloc_word(char const *s, char c)
{
	size_t		i;
	char		*word;

	i = 0;
	while (s[i] && s[i] != c)
		i ++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i ++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{	
			tab[i++] = ft_malloc_word(s, c);
			if (!tab[i - 1])
			{	
				ft_free_tab(tab, (i - 1));
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}	
		while (*s && *s == c)
			s++;
	}		
	tab[i] = 0;
	return (tab);
}
