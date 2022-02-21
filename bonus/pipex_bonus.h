/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:36:19 by athirion          #+#    #+#             */
/*   Updated: 2022/02/21 13:24:14 by athirion         ###   ########.fr       */
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
# include "../libft/libft.h"

# ifndef LIMITER
# define LIMITER "stop"
# endif

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

typedef struct	s_data
{
	int			ac;
	char		**av;
	char		**env;

	int			nb_cmd;
	int			cmd_id;

	int			here_doc;

	char		*prog_name;

	pid_t		child[2];

	int			fd[2];
	int			file_in;
	int			file_out;

	pid_t		*pipe;

	char		**arg_cmd[2];
	char		*cmd[2];
	char		**env_path;
}				t_data;

char	**ft_get_path(char **envp);
char	*ft_command(char *cmd, char **env_path);
char	**ft_arg_cmd(char *cmd);
void	ft_init_data(int argc, char **argv, char **envp, t_data *data);
void	ft_open(t_data *data);
void	ft_close(t_data *data, int fd);
void	ft_exit(t_data *data, int error, int cmd_id);
void	ft_free_all(t_data *data);
void	ft_free_tab(char **tab);
void	ft_child1(t_data *data);
void	ft_child2(t_data *data);

/*
 * * * files_bonus.c
 */

void	ft_get_filenames(t_data *data);


/*
 * * * here_doc_bonus.c
 */

int		ft_is_heredoc(t_data *data);
void	ft_here_doc(t_data *data);


/*
 * * *  get_next_line.c
 */

char	*ft_update_temp(char *temp);
char	*ft_get_line(char *temp);
char	*get_next_line(int fd);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
int		ft_is_nl(char *str);
int		ft_len_newline(char *str);


#endif
