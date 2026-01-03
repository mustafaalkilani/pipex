#include "../pipex.h"
#include "../libft/libft.h"

pid_t	execute_first_command(char **argv, int *pipefd, char **envp)
{
	pid_t	pid;
	int		fd_in;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		fd_in = open_input_file(argv[1]);
		if (fd_in == -1)
		{
			close(pipefd[1]);
			exit(1);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
			error_exit("dup2");
		close(fd_in);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			error_exit("dup2");
		close(pipefd[1]);
		execute_command(argv[2], envp);
	}
	return (pid);
}

pid_t	execute_second_command(char **argv, int *pipefd, char **envp)
{
	pid_t	pid;
	int		fd_out;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(pipefd[1]);
		fd_out = open_output_file(argv[4]);
		if (fd_out == -1)
		{
			close(pipefd[0]);
			exit(1);
		}
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			error_exit("dup2");
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error_exit("dup2");
		close(fd_out);
		close(pipefd[0]);
		execute_command(argv[3], envp);
	}
	return (pid);
}

static void	handle_path_command_error(char **cmd_args)
{
	if (access(cmd_args[0], F_OK) != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_split(cmd_args);
		exit(127);
	}
	if (access(cmd_args[0], X_OK) != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_split(cmd_args);
		exit(126);
	}
	free_split(cmd_args);
	exit(127);
}

void	execute_command(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = parse_command(cmd);
	if (!cmd_args)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	cmd_path = get_command_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		if (ft_strchr(cmd_args[0], '/') == NULL)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putstr_fd(cmd_args[0], 2);
			ft_putstr_fd("\n", 2);
			free_split(cmd_args);
			exit(127);
		}
		handle_path_command_error(cmd_args);
	}
	execve(cmd_path, cmd_args, envp);
	perror("pipex");
	free_split(cmd_args);
	free(cmd_path);
	exit(126);
}
