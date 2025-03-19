/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:44 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/19 11:18:35 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

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
}			t_utils;

void	init_utils(t_utils *utils, char **av);
void	do_cmd(t_utils *utils, char **env);
char	*get_path(char *cmd);
void	open_files_read(char *file_in, char *file_out, int *fd_in, int *fd_out);

#endif