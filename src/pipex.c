/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/19 17:16:42 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <stdio.h>

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
	init_utils(&utils, av);
	do_cmd(&utils, envp);
}

void	init_utils(t_utils *utils, char **av)
{
	utils->args1 = ft_split(av[2], ' ');
	utils->args2 = ft_split(av[3], ' ');
	utils->path1 = get_path(utils->args1[0]);
	if (utils->path1[ft_strlen(utils->path1) - 1] == '\n')
		utils->path1[ft_strlen(utils->path1) - 1] = '\0';
	utils->path2 = get_path(utils->args2[0]);
	if (utils->path2[ft_strlen(utils->path2) - 1] == '\n')
		utils->path2[ft_strlen(utils->path2) - 1] = '\0';
	pipe(utils->pipefd);
	open_files_read(av[1], av[4], &utils->fd_in, &utils->fd_out);
}

void	do_cmd(t_utils *utils, char **envp)
{
	utils->pid = fork();
	if (!utils->pid)
	{
		dup2(utils->fd_in, STDIN_FILENO);
		dup2(utils->pipefd[1], STDOUT_FILENO);
		close(utils->fd_out);
		close(utils->fd_in);
		close(utils->pipefd[0]);
		close(utils->pipefd[1]);
		execve(utils->path1, utils->args1, envp);
		exit(1);
	}
	utils->pid = fork();
	if (!utils->pid)
	{
		dup2(utils->pipefd[0], STDIN_FILENO);
		dup2(utils->fd_out, STDOUT_FILENO);
		close(utils->fd_out);
		close(utils->fd_in);
		close(utils->pipefd[0]);
		close(utils->pipefd[1]);
		execve(utils->path2, utils->args2, envp);
		exit(1);
	}
	return ;
}

char	*get_path(char *cmd)
{
	char	*args[] = {"which", cmd, NULL};
	char	*res;
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
	{
		perror("Error");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		execve("/usr/bin/which", args, NULL);
	}
	wait(NULL);
	res = get_next_line(pipefd[0]);
	if (!res)
	{
		perror("Error");
		exit(1);
	}
	return (res);
}

void	open_files_read(char *file_in, char *file_out, int *fd_in, int *fd_out)
{
	*fd_in = open(file_in, O_RDONLY);
	*fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0655);
}
