/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:53:50 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/10 13:55:09 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

int		run_here_doc_mode(int argc, char **argv, char **envp);
int		run_normal_mode(int argc, char **argv, char **envp);

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		**pipes;
	int		cmd_count;
	int		is_here_doc;
}	t_pipex;
int		execute_multiple_commands(t_pipex *px);
void	execute_command_at_index(int index, t_pipex *px);
void	handle_here_doc(char *limiter, int *temp_pipefd);
int		open_output_file_append(char *filename);

#endif