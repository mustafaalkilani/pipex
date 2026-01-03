#include "../pipex.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

static void	fork_all_commands(int cmd_count, char **argv,
				int **pipes, char **envp, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			error_exit("fork");
		if (pids[i] == 0)
			execute_command_at_index(i, cmd_count, argv, pipes, envp);
		i++;
	}
}

static void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	wait_all_children(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}

void	execute_multiple_commands(int argc, char **argv,
			int **pipes, char **envp)
{
	int		cmd_count;
	pid_t	*pids;

	cmd_count = argc - 3;
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		error_exit("malloc");
	fork_all_commands(cmd_count, argv, pipes, envp, pids);
	close_all_pipes(pipes, cmd_count - 1);
	wait_all_children(pids, cmd_count);
	free(pids);
}

static void	close_all_pipes_in_child(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	setup_input(int index, char **argv, int **pipes)
{
	int	fd_in;

	if (index == 0)
	{
		fd_in = open_input_file(argv[1]);
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
	else
		dup2(pipes[index - 1][0], STDIN_FILENO);
}

static void	setup_output(int index, int cmd_count, char **argv, int **pipes)
{
	int	fd_out;

	if (index == cmd_count - 1)
	{
		fd_out = open_output_file(argv[cmd_count + 2]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(pipes[index][1], STDOUT_FILENO);
}

void	execute_command_at_index(int index, int cmd_count,
			char **argv, int **pipes, char **envp)
{
	setup_input(index, argv, pipes);
	setup_output(index, cmd_count, argv, pipes);
	close_all_pipes_in_child(pipes, cmd_count - 1);
	execute_command(argv[2 + index], envp);
}

void	handle_here_doc(char *limiter, int *temp_pipefd)
{
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, temp_pipefd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	}
	close(temp_pipefd[1]);
}
