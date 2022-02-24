#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void    ft_free_pipe(int **tab, int i, int j)
{

        while (i >=0)
        {
                //j = 1;
                //while (j >= 0)
                //{
                //        free(tab[i][j]);
                //        j --;
               // }
                //i --;
                free(tab[i]);
				i --;
        }
        free(tab);
}

int main(void)
{
	int **tab;
	int	i;
	int j;

	tab = NULL;
	i = 0;
	j = 0;
	tab = (int **)malloc(sizeof(int *) * 5);
	if (!tab)
		return (1);
	while (i < 5)
	{
		tab[i] = (int *)malloc(sizeof(int) * 2);
		i ++;
	}
	i = 0;
	j = 0;
	while (i < 5)
	{
		while (j < 2)
		{
			tab[i][j] = j;
			j ++;
		}
		j = 0;
		i ++;
	}
	for (i = 0; i < 5; i ++)
		for (j = 0; j < 2; j ++)
				printf("tab[%d][%d] = %d\n", i, j, tab[i][j]);
	
	ft_free_pipe(tab, 4, 1);
	printf("len = %ld\n", ft_strlen("salut"));
	return (0);

}
