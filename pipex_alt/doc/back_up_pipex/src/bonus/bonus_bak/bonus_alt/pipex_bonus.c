/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:40:45 by athirion          #+#    #+#             */
/*   Updated: 2022/02/23 09:43:30 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_child(t_data *data)
{
	data->child = (int *)malloc(sizeof(int) * data->nb_cmd);
	if (!data->child)
		exit(errno);
}

void	ft_init_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->pipe = (int **)malloc(sizeof(int *) * (data->nb_cmd - 1));
	if (!data->pipe)
		/* free(stuff - data->child); */
		exit(errno);
	while (i < (data->nb_cmd - 1))
	{
		data->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipe[i])
			/* free( anterior pipe) */	
			exit(EXIT_FAILURE);
		if (pipe(data->pipe[i]) == -1)
			exit(EXIT_FAILURE);
		i ++;
	}
}

int		ft_is_here_doc(char	*s)
{
	if (!ft_strncmp("here_doc", s, 8))
		return (1);
	else
		return (0);
}

char	**ft_init_cmd(t_data *data)
{
	char	**cmd;

	cmd = (char **)malloc(sizeof(char *) * data->nb_cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	***ft_init_arg_cmd(t_data *data)
{
	char	***arg_cmd;

	arg_cmd = (char ***)malloc(sizeof(char **) * data->nb_cmd);
	if (!arg_cmd)
		return (NULL);
	return (arg_cmd);
}

char	**ft_init_path(char **envp)
{
	char	*path;
	char	**env_path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_strdup(*envp + 5);
	if (!path)
		return (NULL);
	env_path = ft_split(path, ':');
	free(path);
	if (!env_path)
		return (NULL);
	return (env_path);
}

char    *ft_command(char *cmd, char **env_path)
{
	char    *command;
	char    *new_path;

	if (access(cmd, 0) == 0)
	{
		command = ft_strdup(cmd);
		return (command);
	}
	while (*env_path)
	{
		new_path = ft_strjoin(*env_path, "/");
		if (!new_path)
			return (NULL);
		command = ft_strjoin(new_path, cmd);
		if (access(command, 0) == 0)
		{
			free(new_path);
			return (command);
		}
		env_path ++;
		free(new_path);
		free(command);
	}
	return (NULL);
}

char    **ft_arg_cmd(char *cmd)
{
	char    **arg_cmd;
	arg_cmd = ft_split(cmd, ' ');
	if (!arg_cmd)
		return (NULL);
	return (arg_cmd);
}


void	ft_init_struct(t_data *data, int argc, char **argv, char **envp)
{
	int	i;
	int	id;

	id = 0;
	data->ac = argc;
	data->av = argv;
	data->env = envp;
	data->prog_name = data->av[0];
	data->here_doc = ft_is_here_doc(data->av[1]);
	data->nb_cmd = data->ac - 3 - data->here_doc;
	data->file_in = 0;
	data->file_out = 0;
	ft_init_child(data);
	ft_init_pipe(data);
	data->cmd = ft_init_cmd(data);
	data->arg_cmd = ft_init_arg_cmd(data);
	data->env_path = ft_init_path(data->env);
	i = data->nb_cmd - 1 + data->here_doc;
	while (i < data->ac - 1)
	{
		data->arg_cmd[id] = ft_arg_cmd(data->av[i]);
		data->cmd[id] = ft_command(data->arg_cmd[id][0], data->env_path);
		i ++;
		id ++;
	}
}

void	ft_dup(int read, int write)
{
	if (dup2(read, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(write, STDOUT_FILENO) == -1)
	{
		perror("dup2-2");
		exit(EXIT_FAILURE);
	}
}

void	ft_open(t_data *data)
{
	data->file_in = open(data->av[1], O_RDONLY);
	data->file_out = open
		(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->file_out == -1)
	{
		perror("open file_out");
		exit(EXIT_FAILURE);
	}
}

void	ft_close_fd(t_data *data, int index)
{
	int	j;

	j = 0;
	while (j < data->nb_cmd)
	{
		if (index != j)
			close(data->pipe[j][0]);
		if (index + 1 != j)
			close(data->pipe[j][1]);
		j ++;
	}
}

int		ft_pipex(t_data *data, int status, int i)
{
	data->child[i] = fork();
	if (data->child[i] == -1)
	{
		perror("fork");
		exit(errno);
	}
	if (data->child[i] == 0)
	{
		printf("We are in child process [%d]\n", i);
	//	ft_close_fd(data, i);
		if (i == 0)
		{
			printf("Cmd[%d] = %s\n", i, data->cmd[i]);
			ft_open(data);
			close(data->file_out);
			close(data->pipe[i][0]);
			ft_dup(data->file_in, data->pipe[i][1]);
			close(data->file_in);
			close(data->pipe[i][1]);
		}
		else if (i == data->nb_cmd - 1)
		{
			printf("Cmd[%d] = %s\n", i, data->cmd[i]);
			ft_open(data);
			if (data->file_in > 0)
			close(data->file_in);
			close(data->pipe[i][0]);
			ft_dup(data->pipe[i][0], data->file_out);
			close(data->pipe[i][0]);
			close(data->file_out);
		}
		else
		{
			printf("Cmd[%d] = %s\n", i, data->cmd[i]);
			ft_dup(data->pipe[i][0], data->pipe[i + 1][1]);
			close(data->pipe[i][0]);
			close(data->pipe[i + 1][1]);
		}
		execve(data->cmd[i], data->arg_cmd[i], data->env);
	}
	return (status);
}

		


/* int	ft_pipex(t_data *data, int status) */
/* { */
/* 	int	i; */
/* 	int j; */

/* 	i = 0; */
/* 	j = 0; */
/* 	while (i < data->nb_cmd) */
/* 	{ */
/* 		data->child[i] = fork(); */
/* 		printf("fork[%d] = %d\n", i, data->child[i]); */
/* 		if (data->child[i] == -1) */
/* 		{ */
/* 			perror("fork"); */
/* 			exit(errno); */
/* 		} */
/* 		if (data->child[i] == 0) */
/* 		{ */
/* 			printf("Entering child[%d]\n", i); */
/* 			while (j < data->nb_cmd) */
/* 			{ */
/* 				printf("data->nb_cmd = %d\n", data->nb_cmd); */
/* 				printf("j = %d && i = %d\n", j, i); */
/* 				if (i != j) */
/* 				{ */
/* 					if (close(data->pipe[j][0]) == -1) */ 
/* 					{ */
/* 						perror("close 0"); */
/* 						exit(EXIT_FAILURE); */
/* 					} */
/* 				} */
/* 				if (i + 1 != j) */
/* 				{ */
/* 					if (close(data->pipe[j][1]) == -1) */
/* 					{ */
/* 						perror("close 1"); */
/* 						exit(EXIT_FAILURE); */
/* 					} */
/* 				} */
/* 				j ++; */
/* 			} */
/* 			printf("helloeeeee\n"); */
/* 			j = 0; */
/* 			if (i == 0) */
/* 			{ */
/* 				printf("hello\n"); */
/* 				printf("i = 0 = [%d]\n", i); */
/* 				ft_open(data); */
/* 				if (close(data->pipe[i][0]) == -1 || close(data->file_out) == -1) */
/* 				{ */
/* 					perror("close 2"); */
/* 					exit(EXIT_FAILURE); */
/* 				} */
/* 				ft_dup(data->file_in, data->pipe[i][1]); */
/* 				if (close(data->pipe[i][1]) == -1 || close(data->file_in) == -1) */
/* 				{ */
/* 					perror("close 3"); */
/* 					exit(EXIT_FAILURE); */
/* 				} */
/* 			} */
/* 			else if (i == data->nb_cmd - 1) */
/* 			{ */
/* 				printf("i = %d = [%d]\n", data->nb_cmd - 1, i); */
/* 				ft_open(data); */
/* 				if (data->file_in > 0) */
/* 					if (close(data->file_in) == -1) */
/* 					{ */	
/* 						perror("close 4"); */
/* 						exit(EXIT_FAILURE); */
/* 					} */
/* 				if (close(data->pipe[i][1]) == -1) */
/* 				{ */
/* 					perror("close 5"); */
/* 					exit(EXIT_FAILURE); */
/* 				} */
/* 				ft_dup(data->pipe[i][0], data->file_out); */
/* 				if (close(data->pipe[i][0]) == -1 */ 
/* 						|| close(data->pipe[i + 1][0]) == -1) */
/* 				{ */
/* 					perror("close 6"); */
/* 					exit(EXIT_FAILURE); */
/* 				} */
/* 			} */
/* 			else */
/* 			{ */
/* 				ft_dup(data->pipe[i][0], data->pipe[i + 1][1]); */
/* 				if (close(data->pipe[i][0]) == -1 || close(data->pipe[i + 1][1]) == -1) */
/* 				{ */
/* 					perror("close 7"); */
/* 					exit(EXIT_FAILURE); */
/* 				} */
/* 			} */
/* 			printf("data->cmd[%d] = %s\n", i, data->cmd[i]); */
/* 			if (execve(data->cmd[i], data->arg_cmd[i], data->env) == -1) */
/* 			{ */
/* 				perror("execve"); */
/* 				exit(127); */
/* 			} */
/* 			i ++; */
/* 		} */
/* 	} */	
/* 	return (status); */
/* } */


int main(int argc, char **argv, char **envp)
{
	t_data 	data;
	int		status;
	int		i;

	data.prog_name = ft_strrchr(argv[0], '/') + 1;
	status = 1;
	if (argc >= 2)
	{
		ft_init_struct(&data, argc, argv, envp);
	//	printf("C'est fini pour l'init\n");
		i = 0;
		while (i < data.nb_cmd)
		{
			status = ft_pipex(&data, status, i);
			i ++;
		}	
		i = 0;
		while (i < data.nb_cmd)
		{
			wait(NULL);
			i ++;
		}
		/* { */
		/* 	printf("wait for child[%d] to finish\n", i); */
		/* 	if (i < data.nb_cmd - 1) */
		/* 	{ */	
		/* 		if (waitpid(data.child[i], NULL, 0) == -1) */
		/* 		{ */
		/* 			perror("waitpid"); */
		/* 			exit(EXIT_FAILURE); */
		/* 		} */
		/* 	} */
		/* 	else */
		/* 		waitpid(data.child[i], &status, 0); */
		/* 	if (WIFEXITED(status)) */
		/* 		status = WEXITSTATUS(status); */
		/* 	i ++; */
		/* } */
		exit(status);
	}
	ft_putstr_fd(data.prog_name, 2);
	ft_putendl_fd(": Error: Arguments missing", 2);
	exit(status);
}
