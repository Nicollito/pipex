/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:44 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/14 11:14:29 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef struct utils
{
	int	fd_in;
	int	fd_out;
	int	pid;
	int	pipfd[2];
}		t_utils;

#endif