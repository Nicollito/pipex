/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:24:02 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/26 14:03:48 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(t_utils *utils)
{
	close_fd(utils);
	free_all(utils);
	perror("Error");
	exit(1);
}

void	error_cmd(t_utils *utils, char *cmd, int nb_cmd)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("Error: %s not found\n", cmd);
	close_fd(utils);
	free_all(utils);
	if (nb_cmd == 2)
		exit(127);
	exit(0);
}
