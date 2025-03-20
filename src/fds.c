/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:29:08 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/20 14:29:56 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files_read(t_utils *utils, char **av)
{
	utils->fd_in = open(av[1], O_RDONLY);
	utils->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0655);
	pipe(utils->pipefd);
}

void	close_fd(t_utils *utils)
{
	if (utils->fd_in != -1)
		close(utils->fd_in);
	if (utils->fd_out != -1)
		close(utils->fd_out);
	if (utils->pipefd[0] != -1)
		close(utils->pipefd[0]);
	if (utils->pipefd[1] != -1)
		close(utils->pipefd[1]);
}
