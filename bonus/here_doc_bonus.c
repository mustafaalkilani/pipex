/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/10 13:55:59 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "pipex_bonus.h"

void	handle_here_doc(char *limiter, int *temp_pipefd)
{
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	ft_putstr_fd("heredoc> ", STDERR_FILENO);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, temp_pipefd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
	}
	close(temp_pipefd[1]);
}
