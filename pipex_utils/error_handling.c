/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malkilan <malkilan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by malkilan          #+#    #+#             */
/*   Updated: 2026/01/10 13:21:58 by malkilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

void	error_exit(char *message)
{
	perror(message);
	exit(1);
}

void	error_exit_custom(char *prefix, char *detail, int exit_code)
{
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(detail, 2);
	ft_putchar_fd('\n', 2);
	exit(exit_code);
}

void	cleanup_and_exit(char **array, int exit_code)
{
	if (array)
		free_split(array);
	exit(exit_code);
}
