/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa <mustafa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by mustafa           #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by mustafa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

static int	is_here_doc_mode(char **argv)
{
	if (!argv || !argv[1])
		return (0);
	return (ft_strncmp(argv[1], "here_doc", 9) == 0);
}

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

static int	run_here_doc_mode(int argc, char **argv, char **envp)
{
	int	**pipes;
	int	cmd_count;
	int	pipe_count;
	int	exit_status;

	if (argc < 6)
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile\n", 2);
		exit(1);
	}
	cmd_count = argc - 4;
	pipe_count = cmd_count - 1;
	setup_here_doc_stdin(argv[2]);
	pipes = create_pipes(pipe_count);
	exit_status = execute_multiple_commands(argc - 1, argv + 1, pipes, envp, 1);
	free_pipes(pipes, pipe_count);
	return (exit_status);
}

static int	run_normal_mode(int argc, char **argv, char **envp)
{
	int	**pipes;
	int	cmd_count;
	int	pipe_count;
	int	exit_status;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
		exit(1);
	}
	cmd_count = argc - 3;
	pipe_count = cmd_count - 1;
	pipes = create_pipes(pipe_count);
	exit_status = execute_multiple_commands(argc, argv, pipes, envp, 0);
	free_pipes(pipes, pipe_count);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
		ft_putstr_fd("   or: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile\n", 2);
		exit(1);
	}
	if (is_here_doc_mode(argv))
		return (run_here_doc_mode(argc, argv, envp));
	return (run_normal_mode(argc, argv, envp));
}
