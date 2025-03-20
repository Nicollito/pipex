/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:34:35 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/20 16:48:28 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_utils_null(t_utils *utils)
{
	utils->fd_in = -1;
	utils->fd_out = -1;
	utils->pipefd[0] = -1;
	utils->pipefd[1] = -1;
	utils->path1 = NULL;
	utils->path2 = NULL;
	utils->args1 = NULL;
	utils->args2 = NULL;
	utils->which_args1 = NULL;
	utils->which_args2 = NULL;
}

void	init_utils(t_utils *utils, char **av)
{
	open_files_read(utils, av);
	utils->args1 = ft_split(av[2], ' ');
	if (!utils->args1)
		ft_error(utils);
	utils->args2 = ft_split(av[3], ' ');
	if (!utils->args2)
		ft_error(utils);
	utils->which_args1 = set_which_args(utils, utils->args1[0]);
	utils->which_args2 = set_which_args(utils, utils->args2[0]);
	// check_cmd(utils);
	utils->path1 = get_path(utils, utils->which_args1);
	utils->path2 = get_path(utils, utils->which_args2);
}

char	**set_which_args(t_utils *utils, char *cmd)
{
	char	**res;

	res = malloc(sizeof(char *) * 3);
	if (!res)
		ft_error(utils);
	res[2] = NULL;
	res[0] = ft_strdup("which");
	if (!res[0])
	{
		free(res);
		ft_error(utils);
	}
	res[1] = ft_strdup(cmd);
	if (!res[1])
	{
		free(res[0]);
		free(res);
		ft_error(utils);
	}
	return (res);
}

char	*get_path(t_utils *utils, char **which_args)
{
	char	*res;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(utils->pipefd[1], STDOUT_FILENO);
		close_fd(utils);
		execve("/usr/bin/which", which_args, NULL);
		free_all(utils);
	}
	wait(NULL);
	res = get_next_line(utils->pipefd[0]);
	if (!res)
		ft_error(utils);
	if (res[ft_strlen(res) - 1] == '\n')
		res[ft_strlen(res) - 1] = '\0';
	return (res);
}
