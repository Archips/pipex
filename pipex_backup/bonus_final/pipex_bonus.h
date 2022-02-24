/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:10:43 by athirion          #+#    #+#             */
/*   Updated: 2022/02/23 11:31:20 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*
 * TO DEBUG
 */

# include <stdio.h>

/*
 * write - read - close - access - pipe - dup2 - execve - fork
 */

# include <unistd.h>

/*
 * open, unlink
 */ 

# include <fcntl.h>

/*
 * waitpid
 */

# include <sys/wait.h>

/*
 * libft
 */

# include "../libft/libft.h"


/*
 * args.c
 */

int	ft_check_args(int argc, char **argv);

/*
 * here_doc.c
 */

int	ft_is_heredoc(char *s);


#endif
