/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:44 by nimadela          #+#    #+#             */
/*   Updated: 2025/04/03 10:38:10 by nimadela         ###   ########.fr       */
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
	int		file_exist;
	int		file2_perm;
	int		fd_in;
	int		fd_out;
	int		pid;
	int		pipefd[2];
	int		status;
	int		return_value;
	int		exit_value;
	int		skip_yes;
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
void	clear_pipe(t_utils *utils);

// free_all.c
void	free_all(t_utils *utils);
void	free_matrix(char **mat);

// ft_error.c
void	ft_error(t_utils *utils);
void	error_cmd(t_utils *utils, char *cmd, int nb_cmd);
void	check_yes(t_utils *utils);
void	set_exit(t_utils *utils);
char	*set_path_none(t_utils *utils);

// initialize.c
void	set_utils_null(t_utils *utils);
void	init_utils(t_utils *utils, char **av);
char	**set_which_args(t_utils *utils, char *cmd);
char	*get_path(t_utils *utils, char **which_args, int nb_cmd);
char	*get_and_set_res(t_utils *utils, char **which_args, int nb_cmd);

// pipex.c (main)
void	do_cmd1(t_utils *utils, char **env);
void	do_cmd2(t_utils *utils, char **env);

#endif