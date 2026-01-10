/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_modes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by mustafa           #+#    #+#             */
/*   Updated: 2026/01/10 13:55:52 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"
#include "pipex_bonus.h"

static int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		error_exit("malloc");
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			error_exit("malloc");
		if (pipe(pipes[i]) == -1)
			error_exit("pipe");
		i++;
	}
	return (pipes);
}

static void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	setup_here_doc_stdin(char *limiter)
{
	int	temp_pipefd[2];

	if (pipe(temp_pipefd) == -1)
		error_exit("pipe");
	handle_here_doc(limiter, temp_pipefd);
	if (dup2(temp_pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2");
	close(temp_pipefd[0]);
}

int	run_here_doc_mode(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		pipe_count;
	int		exit_status;

	if (argc < 6)
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd ... outfile\n", 2);
		exit(1);
	}
	px.cmd_count = argc - 4;
	pipe_count = px.cmd_count - 1;
	setup_here_doc_stdin(argv[2]);
	px.argc = argc - 1;
	px.argv = argv + 1;
	px.envp = envp;
	px.pipes = create_pipes(pipe_count);
	px.is_here_doc = 1;
	exit_status = execute_multiple_commands(&px);
	free_pipes(px.pipes, pipe_count);
	return (exit_status);
}

int	run_normal_mode(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		pipe_count;
	int		exit_status;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
		exit(1);
	}
	px.cmd_count = argc - 3;
	pipe_count = px.cmd_count - 1;
	px.argc = argc;
	px.argv = argv;
	px.envp = envp;
	px.pipes = create_pipes(pipe_count);
	px.is_here_doc = 0;
	exit_status = execute_multiple_commands(&px);
	free_pipes(px.pipes, pipe_count);
	return (exit_status);
}
