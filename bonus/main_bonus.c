/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by mustafa           #+#    #+#             */
/*   Updated: 2026/01/10 13:22:26 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

int		run_here_doc_mode(int argc, char **argv, char **envp);
int		run_normal_mode(int argc, char **argv, char **envp);

static int	is_here_doc_mode(char **argv)
{
	if (!argv || !argv[1])
		return (0);
	return (ft_strncmp(argv[1], "here_doc", 9) == 0);
}

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
	ft_putstr_fd("   or: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile\n", 2);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		print_usage();
	if (is_here_doc_mode(argv))
		return (run_here_doc_mode(argc, argv, envp));
	return (run_normal_mode(argc, argv, envp));
}
