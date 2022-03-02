#include "pipex.h"

/*
 ** Open the input and output files.
 */

static void	ft_open_files(t_data *data)
{
	data->file[0] = open(data->av[1], O_RDONLY);

	data->file[1] = open
		(data->av[data->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->file[1] < 0)
		ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, data->av[data->ac - 1]));
}

/*
 ** Write to the pipe.
 **
 ** dup N    : File1	← StdOut
 ** dup N - 1: Pipe1	← StdOut
 */

static void	ft_writer(t_data *data)
{
	if (data->file[0] < 0 && data->index == 0)
		ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));

	if (close(data->pipe[0]) < 0)
		ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));

	if (data->index < data->cmdid - 1)
	{
		if (dup2(data->pipe[1], STDOUT_FILENO) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
		if (close(data->pipe[1]) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
	}
	else if (data->index == data->cmdid - 1)
	{
		if (close(data->pipe[1]) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));

		if (dup2(data->file[1], STDOUT_FILENO) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
		if (close(data->file[1]) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
	}

	ft_check_prgs (data, 0);

	dprintf(2, "---[%s: %s: %d]---\n",__FILE__, __func__, __LINE__);
	dprintf(2, "cmdid=%i\n", data->cmdid);
	dprintf(2, "index=%i\n", data->index);

	if (execve(data->prgs[data->index], data->args[data->index], data->env) < 0)
		ft_clear_exit
			(data, ft_perr(data, __FILE__, __LINE__, data->args[0][0]));
}

/*
 ** Pipe's parent
 **
 ** dup 0 : File0	← StdIn
 ** dup N : Pipe0	← StdIn
 */

int	ft_pipe(t_data *data)
{
	int	status;
	int	pid;

	status = 0;

	/* Open files */
	ft_open_files(data);

	/* Connect file and stdin if the file exist */
	if (data->file[0] > 0)
	{
		if (dup2(data->file[0], STDIN_FILENO) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
	}

	/* Generate Processes */
	while (data->index < data->cmdid)
	{
		/* Open pipe */
		if (pipe(data->pipe) < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));

		/* Reader */
		pid = fork();
		if (pid < 0)
			ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
		if (pid == 0)
			ft_writer(data);

		/* Writer */
		if (pid > 0)
		{
			if (close(data->pipe[1]) < 0)
				ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));

			/* if (data->index == 0) */
			/* { */
			/* TODO */
			/* dprintf(2, "---[%s/%s()/l.%d/%s]---\n",__FILE__, __func__, __LINE__, __TIME__); */
			/* if (close(data->pipe[0]) < 0) */
			/* 	ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, "")); */


			/* if (dup2(data->file[0], STDIN_FILENO) < 0) */
			/* 	ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, "")); */
			/* dprintf(2, "---[%s/%s()/l.%d/%s]---\n",__FILE__, __func__, __LINE__, __TIME__); */
			/* if (close(data->file[0]) < 0) */
			/* 	ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, "")); */
			/* } */
			/* else if (data->index > 0) */
			/* { */

			if (dup2(data->pipe[0], STDIN_FILENO) < 0)
				ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));


			if (close(data->pipe[0]) < 0)
				ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));


			if (waitpid(pid, &status, 0) < 0)
				ft_clear_exit (data, ft_perr(data, __FILE__, __LINE__, ""));
			/* } */
		}
		data->index += 1;
	}
	/* TODO close file[0] ? */
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
