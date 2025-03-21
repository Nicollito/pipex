/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:44 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/21 11:34:32 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"

typedef struct utils
{
	int		fd_in;
	int		fd_out;
	int		pid;
	int		pipefd[2];
	char	*path1;
	char	*path2;
	char	**args1;
	char	**args2;
	char	**which_args1;
	char	**which_args2;
}			t_utils;

// fds.c
void	open_files_read(t_utils *utils, char **av);
void	close_fd(t_utils *utils);

// free_all.c
void	free_all(t_utils *utils);
void	free_matrix(char **mat);

// ft_error.c
void	ft_error(t_utils *utils);
void	error_cmd(t_utils *utils, char *cmd);

// initialize.c
void	set_utils_null(t_utils *utils);
void	init_utils(t_utils *utils, char **av);
char	**set_which_args(t_utils *utils, char *cmd);
char	*get_path(t_utils *utils, char **which_args);

// pipex.c (main)
void	do_cmd(t_utils *utils, char **env);
void	check_cmd(t_utils *utils);

#endif