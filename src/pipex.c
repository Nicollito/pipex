/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/14 11:40:55 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	char *args[] = {"ls", NULL};

	if (ac != 5)
		return (-1);
	if (access(av[1], F_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	if (execve("/usr/bin/ls", args, NULL) == -1)
		printf("échec\n");
}
