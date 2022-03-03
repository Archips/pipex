/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:54:01 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 11:27:59 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static char	*ft_free_split(char **tab, int i)
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
				ft_free_split(tab, (i - 1));
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
