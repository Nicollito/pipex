/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/25 18:38:37 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_utils	utils;
	int		pid;

	if (ac != 5)
		return (-1);
	utils.file_exist = access(av[1], F_OK | W_OK);
	if (utils.file_exist == -1)
		perror("Error");
	init_utils(&utils, av);
	pid = fork();
	if (pid == 0)
	{
		if (utils.file_exist == -1)
		{
			close_fd(&utils);
			free_all(&utils);
			exit(1);
		}
		do_cmd1(&utils, envp);
	}
	if (pid > 0)
		do_cmd2(&utils, envp);
	clear_pipe(&utils);
	waitpid(pid, NULL, 0);
	set_exit(&utils);
}

void	clear_pipe(t_utils *utils)
{
	int		b_read;
	char	buffer[10];

	b_read = read(utils->pipefd[0], buffer, 10);
	while (b_read == 10)
		b_read = read(utils->pipefd[0], buffer, 10);
}

void	set_exit(t_utils *utils)
{
	int	exit_value;

	exit_value = 0;
	if (utils->return_value == 1)
		exit_value = 1;
	close_fd(utils);
	free_all(utils);
	exit(exit_value);
}

void	do_cmd1(t_utils *utils, char **envp)
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
		execve(utils->path2, utils->args2, envp);
		free_all(utils);
		exit(1);
	}
	waitpid(utils->pid, &utils->status, 0);
	utils->return_value = WEXITSTATUS(utils->status);
}
