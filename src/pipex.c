/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/13 17:09:20 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 5)
		return (-1);
	if (access(av[1], F_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
}

void	do_command(char **av)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
