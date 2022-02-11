/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:36:19 by athirion          #+#    #+#             */
/*   Updated: 2022/02/11 16:10:16 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define ERR_1 "Malloc Error"

typedef struct	s_data
{
	int			fd[2];
	int			fd_in;
	int			fd_out;

	pid_t		child1;
	pid_t		child2;

	char		**arg_cmd1;
	char		**arg_cmd2;
	char		*cmd1;
	char		*cmd2;
	char		**env_path;

}				t_data;

char	**ft_path(char **envp);
char	*ft_command(char *cmd, char **env_path);
char	**arg_cmd(char *cmd);
void	ft_open(char **argv, t_data *data);
int		ft_error(int error);
void	ft_free_tab(char **tab);
void	ft_child1(t_data *data, char **argv, char **envp);
void	ft_child2(t_data *data, char **argv, char **envp);

#endif
