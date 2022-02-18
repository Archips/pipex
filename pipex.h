/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:36:19 by athirion          #+#    #+#             */
/*   Updated: 2022/02/18 14:43:58 by athirion         ###   ########.fr       */
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

typedef struct	s_data
{
	int			ac;
	char		**av;
	char		**env;

	int			cmd_id;

	char		*prog_name;

	int			fd[2];
	int			file_in;
	int			file_out;

	pid_t		child[2];

	char		**arg_cmd[2];
	char		*cmd[2];
	char		**env_path;
}				t_data;

char	**ft_get_path(char **envp);
char	*ft_command(char *cmd, char **env_path);
char	**ft_arg_cmd(char *cmd);
void	ft_init_data(int argc, char **argv, char **envp, t_data *data);
void	ft_open(t_data *data);
void	ft_exit(t_data *data, int error, int cmd_id);
void	ft_free_all(t_data *data);
void	ft_free_tab(char **tab);
void	ft_child1(t_data *data);
void	ft_child2(t_data *data);

#endif
