/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:36:19 by athirion          #+#    #+#             */
/*   Updated: 2022/03/01 22:17:20 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * USAGE 1: ./pipex infile cmd_1 cmd_2 .. cmd_n outfile
 * -> 		< infile cmd_1 | cmd_2 | .. | cmd_n outfile
 * USAGE 2: ./pipex here_doc LIMITER cmd_1 cmd_2 file
 * -> 		cmd_1 << LIMITER | cmd_2 >> file
 * USAGE 3: ./pipex here_doc LIMITER cmd_1 cmd_2 .. cmd_n file
 * ->		<< LIMITER cmd_1 | cmd_2 | .. | cmd_n >> file
*/


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

	int			child;

	int			nb_cmd;

	int			here_doc;

	char		*prog_name;

	int			fd[2];
	int			file_in;
	int			file_out;

	int			index;

	char		**arg_cmd;
	char		*cmd;
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
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	**ft_get_path(char **envp);
char	*ft_command(char *cmd, char **env_path);
char	**ft_arg_cmd(char *cmd);
void	ft_init_data(int argc, char **argv, char **envp, t_data *data);
void	ft_close(t_data *data, int fd);
void	ft_exit(t_data *data, int error, char *cmd);
void	ft_free_all(t_data *data);
void	ft_free_pipe(t_data *data);
void	ft_free_tab(char **tab);
void	ft_child(t_data *data, int i);
int		ft_parent(t_data *data, int i, int status, int child);

/*
 * * * files_bonus.c
 */

void	ft_open(t_data *data);
void	ft_open_infile(t_data *data);
void	ft_open_outfile(t_data *data);


/*
 * * * here_doc_bonus.c
 */

int		ft_is_heredoc(t_data *data, char *here_doc);
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