/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa <mustafa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by mustafa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

static void	fork_all_commands(t_pipex *px, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < px->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			error_exit("fork");
		if (pids[i] == 0)
			execute_command_at_index(i, px);
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

static int	wait_all_children(pid_t *pids, int cmd_count)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 1;
		}
		i++;
	}
	return (last_status);
}

int	execute_multiple_commands(t_pipex *px)
{
	pid_t	*pids;
	int		exit_status;

	pids = malloc(sizeof(pid_t) * px->cmd_count);
	if (!pids)
		error_exit("malloc");
	fork_all_commands(px, pids);
	close_all_pipes(px->pipes, px->cmd_count - 1);
	exit_status = wait_all_children(pids, px->cmd_count);
	free(pids);
	return (exit_status);
}
