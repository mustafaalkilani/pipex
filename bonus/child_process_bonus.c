/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/10 13:56:07 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"
#include "pipex_bonus.h"

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

static void	setup_input(int index, t_pipex *px)
{
	int	fd_in;

	if (index == 0)
	{
		if (px->is_here_doc)
			return ;
		fd_in = open_input_file(px->argv[1]);
		if (fd_in == -1)
		{
			close_all_pipes_in_child(px->pipes, px->cmd_count - 1);
			exit(1);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
			error_exit("dup2");
		close(fd_in);
	}
	else
	{
		if (dup2(px->pipes[index - 1][0], STDIN_FILENO) == -1)
			error_exit("dup2");
	}
}

static void	setup_output(int index, t_pipex *px)
{
	int	fd_out;

	if (index == px->cmd_count - 1)
	{
		if (px->is_here_doc)
			fd_out = open_output_file_append(px->argv[px->cmd_count + 2]);
		else
			fd_out = open_output_file(px->argv[px->cmd_count + 2]);
		if (fd_out == -1)
			exit(1);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error_exit("dup2");
		close(fd_out);
	}
	else
	{
		if (dup2(px->pipes[index][1], STDOUT_FILENO) == -1)
			error_exit("dup2");
	}
}

void	execute_command_at_index(int index, t_pipex *px)
{
	setup_input(index, px);
	setup_output(index, px);
	close_all_pipes_in_child(px->pipes, px->cmd_count - 1);
	execute_command(px->argv[2 + index], px->envp);
}
