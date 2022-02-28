/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:51:42 by athirion          #+#    #+#             */
/*   Updated: 2022/02/28 22:15:25 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_pipex(t_data *data, int status)
{
	int		i;
	int		child;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->fd) == -1)
			ft_exit(data, errno, NULL);
		child = fork();
		if (child == -1)
			ft_exit(data, errno, NULL);
		if (child > 0)
			status = ft_parent(data, status, child);
		if (child == 0)
			ft_child(data, i);
		i ++;
		data->index ++;
	}
	return (status);
}

int	ft_parent(t_data *data, int status, int child)
{
	ft_close(data, data->fd[1]);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_exit(data, errno, NULL);
	ft_close(data, data->fd[0]);
	if (waitpid(child, &status, 0) == -1)
		ft_exit(data, errno, NULL);
	if (WIFEXITED(status) == EXIT_FAILURE)
		status = WEXITSTATUS(status);
	return (status);
}	

void	ft_child(t_data *data, int i)
{
	char	*cmd;
	char	**arg_cmd;

	if (data->file_in < 0 && i == 0)
		ft_exit(data, ENOENT, NULL);
	ft_close(data, data->fd[0]);
	if (i == data->nb_cmd - 1)
	{
		ft_close(data, data->fd[1]);	
		if (dup2(data->file_out, STDOUT_FILENO) == -1)
			ft_exit(data, errno, NULL);
		ft_close(data, data->file_out);
	}
	else
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_exit(data, errno, NULL);
		ft_close(data, data->fd[1]);
	}
	arg_cmd = ft_arg_cmd(data->av[data->index]);
	cmd = ft_command(arg_cmd[0], data->env_path);
	if (!cmd)
		ft_exit(data, 127, arg_cmd[0]);
	if (execve(cmd, arg_cmd, data->env) == -1)
		ft_exit(data, 126, arg_cmd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	data.prog_name = ft_strrchr(argv[0], '/') + 1;
	status = 1;
	if (argc >= 5 + ft_is_heredoc(&data, argv[1]))
	{
		status = 0;
		if (!envp)
			exit(EXIT_FAILURE);
		ft_init_data(argc, argv, envp, &data);
		if (data.file_in != -1)
			if (dup2(data.file_in, STDIN_FILENO) == -1)
				ft_exit(&data, ENOENT, NULL); 
		status = ft_pipex(&data, status);
		if (data.file_in != -1)
			ft_close(&data, data.file_in);
		ft_close(&data, data.file_out);
		ft_free_tab(data.env_path);
		exit(status);
	}
	ft_putstr_fd(data.prog_name, 2);
	ft_putendl_fd(": Error: Arguments missing", 2);
	exit(status);
}
