/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/17 17:04:57 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*path1;
	char	*path2;
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		return (-1);
	if (access(av[1], F_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
/* 	if (execve("/usr/bin/ls", args, envp) == -1)
		printf("échec\n"); */
	path1 = get_path(av[2]);
	path2 = get_path(av[3]);
	open_files_read(av[1], av[4], &fd_in, &fd_out);
}

void	do_cmd(int fd_in, int fd_out, char *path1, char *path2)
{
	int		pipefd[2];
	int		pid;
	char	*args1[] = {path1, NULL};
	char	*args2[] = {path2, NULL};

	pipe(pipefd);
	pid = fork();
	if (!pid)
	{
		dup2(fd_in, STDIN_FILENO);
		execve(path1, args1, NULL);
	}
	wait(&pid);
	pid = fork();
	if (!pid)
	{
		
	}
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
	wait(&pid);
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
	fd_in = open(file_in, O_RDONLY);
	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0655);
}
