/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:36:19 by athirion          #+#    #+#             */
/*   Updated: 2022/02/24 15:46:20 by athirion         ###   ########.fr       */
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

	int			**pipe;

	int			here_doc;

	char		*prog_name;

	pid_t		child[2];
	
	int			fd[2];
	int			file_in;
	int			file_out;

	char		**arg_cmd[2];
	char		*cmd[2];
	char		**env_path;
}				t_data;

/*
 * LIB C FUNCTIONS
 */


int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

char	**ft_get_path(char **envp);
char	*ft_command(char *cmd, char **env_path);
char	**ft_arg_cmd(char *cmd);
void	ft_init_data(int argc, char **argv, char **envp, t_data *data);
void	ft_open(t_data *data);
void	ft_close(t_data *data, int fd);
void	ft_exit(t_data *data, int error, int cmd_id);
void	ft_free_all(t_data *data);
void	ft_free_pipe(t_data *data);
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
