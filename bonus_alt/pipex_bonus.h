/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:43:17 by athirion          #+#    #+#             */
/*   Updated: 2022/02/22 14:36:23 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "../libft/libft.h"

/*
 * USAGE 1 -> ./pipex infile cmd1 cmd2 outfile
 * USAGE 2 -> ./pipex here_doc cmd1 cmd2 outfile
 * USAGE 3 -> ./pipex infile cmd1 cmd2 cmd3 ... cmd_n outfile
*/

typedef struct s_data
{

	int		ac;
	char	**av;
	char	**env;
	char	*prog_name;

	int		nb_cmd;

	int		here_doc;

	int		file_in;
	int		file_out;
	int		*child;
	int		**pipe;

	char	**env_path;
	char	**cmd;
	char	***arg_cmd;

}			t_data;

# endif
