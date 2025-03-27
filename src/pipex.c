/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/27 10:06:49 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_utils	utils;
	int		pid;

	if (ac != 5)
		return (-1);
	init_utils(&utils, av);
	pid = fork();
	if (pid == -1)
		ft_error(&utils);
	if (pid == 0)
		do_cmd1(&utils, envp);
	if (pid > 0)
		do_cmd2(&utils, envp);
	clear_pipe(&utils);
	waitpid(pid, NULL, 0);
	set_exit(&utils);
}

void	do_cmd1(t_utils *utils, char **envp)
{
	if (utils->file_exist == -1)
	{
		close_fd(utils);
		free_all(utils);
		exit(1);
	}
	utils->pid = fork();
	if (utils->pid == -1)
		ft_error(utils);
	if (!utils->pid)
	{
		dup2(utils->fd_in, STDIN_FILENO);
		dup2(utils->pipefd[1], STDOUT_FILENO);
		close_fd(utils);
		if (utils->file_exist != -1)
			execve(utils->path1, utils->args1, envp);
		free_all(utils);
		exit(1);
	}
	waitpid(utils->pid, NULL, 0);
	close_fd(utils);
	free_all(utils);
	exit(1);
}

void	do_cmd2(t_utils *utils, char **envp)
{
	utils->pid = fork();
	if (utils->pid == -1)
		ft_error(utils);
	if (utils->pid > 0)
	{
		close(utils->pipefd[1]);
		utils->pipefd[1] = -1;
	}
	if (!utils->pid)
	{
		dup2(utils->pipefd[0], STDIN_FILENO);
		dup2(utils->fd_out, STDOUT_FILENO);
		close_fd(utils);
		if (utils->file2_perm != -1)
			execve(utils->path2, utils->args2, envp);
		free_all(utils);
		exit(1);
	}
	waitpid(utils->pid, &utils->status, 0);
	utils->return_value = WEXITSTATUS(utils->status);
}
