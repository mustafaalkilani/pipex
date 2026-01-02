/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa <mustafa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/02 22:53:42 by mustafa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPX_H
# define PIPX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

/* ************************************************************************** */
/*                              MANDATORY FUNCTIONS                           */
/* ************************************************************************** */

/* main.c */
void	validate_arguments(int argc);

/* process.c */
pid_t	execute_first_command(char **argv, int *pipefd, char **envp);
pid_t	execute_second_command(char **argv, int *pipefd, char **envp);
void	execute_command(char *cmd, char **envp);

/* file_operations.c */
int		open_input_file(char *filename);
int		open_output_file(char *filename);

/* command_parsing.c */
char	**parse_command(char *cmd);
char	*get_command_path(char *cmd, char **envp);
char	*get_env_variable(char *name, char **envp);

/* error_handling.c */
void	error_exit(char *message);
void	error_exit_custom(char *prefix, char *detail, int exit_code);
void	cleanup_and_exit(char **array, int exit_code);

/* utils.c */
void	free_split(char **split);

/* ************************************************************************** */
/*                              BONUS FUNCTIONS                               */
/* ************************************************************************** */

/* process_bonus.c */
void	execute_multiple_commands(int argc, char **argv,
			int **pipes, char **envp);
void	execute_command_at_index(int index, int cmd_count,
			char **argv, int **pipes, char **envp);
void	handle_here_doc(char *limiter, int *temp_pipefd);

/* file_operations_bonus.c */
int		open_output_file_append(char *filename);

#endif