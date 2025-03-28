/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:34:35 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/28 10:26:41 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_utils_null(t_utils *utils)
{
	utils->fd_in = -1;
	utils->fd_out = -1;
	utils->pipefd[0] = -1;
	utils->pipefd[1] = -1;
	utils->exit_value = 0;
	utils->path1 = NULL;
	utils->path2 = NULL;
	utils->args1 = NULL;
	utils->args2 = NULL;
	utils->which_args1 = NULL;
	utils->which_args2 = NULL;
}

void	init_utils(t_utils *utils, char **av)
{
	set_utils_null(utils);
	open_files_read(utils, av);
	utils->file2_perm = access(av[4], W_OK);
	utils->file_exist = access(av[1], F_OK | R_OK);
	utils->args1 = ft_split(av[2], ' ');
	if (!utils->args1)
		ft_error(utils);
	utils->args2 = ft_split(av[3], ' ');
	if (!utils->args2)
		ft_error(utils);
	utils->which_args1 = set_which_args(utils, utils->args1[0]);
	utils->which_args2 = set_which_args(utils, utils->args2[0]);
	utils->path1 = get_path(utils, utils->which_args1, 1);
	utils->path2 = get_path(utils, utils->which_args2, 2);
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
	if (!cmd)
		res[1] = ft_strdup("");
	else
		res[1] = ft_strdup(cmd);
	if (!res[1])
	{
		free(res[0]);
		free(res);
		ft_error(utils);
	}
	return (res);
}

char	*get_path(t_utils *utils, char **which_args, int nb_cmd)
{
	char	*res;
	int		pid;

	pid = fork();
	if (pid > 0)
	{
		close(utils->pipefd[1]);
		utils->pipefd[1] = -1;
	}
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
		error_cmd(utils, which_args[1], nb_cmd);
	if (res && res[ft_strlen(res) - 1] == '\n')
		res[ft_strlen(res) - 1] = '\0';
	close(utils->pipefd[0]);
	pipe(utils->pipefd);
	return (res);
}
