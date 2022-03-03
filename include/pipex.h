/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:36:19 by athirion          #+#    #+#             */
/*   Updated: 2022/03/03 12:03:48 by athirion         ###   ########.fr       */
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

typedef struct s_data
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
 * cmd.c
 */

char	**ft_get_path(char **envp);
char	*ft_command(char *cmd, char **env_path);
char	**ft_arg_cmd(char *cmd);

/*
 * error.c
 */

void	ft_file_error(t_data *data, int infile, int error);
void	ft_cmd_error(t_data *data, char *cmd, int error);

/*
 * files.c
 */

void	ft_open(t_data *data);

/*
 * free.c
 */

void	ft_free_tab(char **tab);

/*
 * pipex.c
 */

int		ft_pipex(t_data *data, int status);
int		ft_parent(t_data *data, int i, int status, int child);
void	ft_child(t_data *data, int i);

/*
 * utils.c
 */

void	ft_init_data(int argc, char **argv, char **envp, t_data *data);
void	ft_close(t_data *data, int fd);
void	ft_exit(t_data *data, int error, char *cmd);

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

#endif
