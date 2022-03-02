#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_data 
{
	char	*s;
}				t_data;

int main(void)
{
	int		**tab;
	t_data	data;

	data = malloc(data);
	if (!data)
		return (-1);
	bzero(data, 1);
	printf("bzero of data has been done\n");
	printf("data.s = %s\n", data.s);
	tab = malloc(sizeof(tab) * 5);
	if (!tab)
		return (1);
	bzero(tab, 5);
	printf("bzero of tab has been done\n");
	for (int i = 0; i < 5; i ++)
	{
		tab[i] = malloc(sizeof(tab[i]) * 2);
		if (!tab[i])
		{
			while (i - 1 >= 0)
			{
				free(tab[i]);
				i --;
			}
			return (2);
		}
		bzero(tab[i], 2);
		printf("tab[%d][0] = %d | tab[%d][1] = %d\n", i, tab[i][0], i, tab[i][1]);
	}
	for (int i = 0; i < 5; i ++)
		free(tab[i]);
	free(tab);
	printf("tab has been freed\n");
	return (0);
}
