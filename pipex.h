/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/10 13:21:21 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

void	validate_arguments(int argc);
pid_t	execute_first_command(char **argv, int *pipefd, char **envp);
pid_t	execute_second_command(char **argv, int *pipefd, char **envp);
void	execute_command(char *cmd, char **envp);
int		open_input_file(char *filename);
int		open_output_file(char *filename);
char	**parse_command(char *cmd);
char	*get_command_path(char *cmd, char **envp);
char	*get_env_variable(char *name, char **envp);
void	error_exit(char *message);
void	error_exit_custom(char *prefix, char *detail, int exit_code);
void	cleanup_and_exit(char **array, int exit_code);
void	free_split(char **split);

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