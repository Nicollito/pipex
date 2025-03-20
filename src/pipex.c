/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/20 16:47:31 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_utils	utils;

	if (ac != 5)
		return (-1);
	if (access(av[1], F_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	set_utils_null(&utils);
	init_utils(&utils, av);
	do_cmd(&utils, envp);
	close_fd(&utils);
	free_all(&utils);
}

void	do_cmd(t_utils *utils, char **envp)
{
	utils->pid = fork();
	if (utils->pid == -1)
		ft_error(utils);
	if (!utils->pid)
	{
		dup2(utils->fd_in, STDIN_FILENO);
		dup2(utils->pipefd[1], STDOUT_FILENO);
		close_fd(utils);
		execve(utils->path1, utils->args1, envp);
		free_all(utils);
		exit(1);
	}
	utils->pid = fork();
	if (utils->pid == -1)
		ft_error(utils);
	if (!utils->pid)
	{
		dup2(utils->pipefd[0], STDIN_FILENO);
		dup2(utils->fd_out, STDOUT_FILENO);
		close_fd(utils);
		execve(utils->path2, utils->args2, envp);
		free_all(utils);
		exit(1);
	}
}

void	check_cmd(t_utils *utils)
{
	if (access(utils->which_args1[1], F_OK) == -1)
		ft_error(utils);
	if (access(utils->which_args2[1], F_OK) == -1)
		ft_error(utils);
}
