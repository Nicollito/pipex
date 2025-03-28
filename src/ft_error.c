/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:24:02 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/28 14:23:54 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(t_utils *utils)
{
	close_fd(utils);
	free_all(utils);
	perror("Error");
	exit(1);
}

void	error_cmd(t_utils *utils, char *cmd, int nb_cmd)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("Error: %s not found\n", cmd);
	if (nb_cmd == 2)
		utils->exit_value = 127;
	utils->exit_value = 0;
}

void	set_exit(t_utils *utils)
{
	if (utils->return_value == 1)
		utils->exit_value = 1;
	if (utils->file_exist == -1)
		perror("Error");
	close_fd(utils);
	free_all(utils);
	exit(utils->exit_value);
}
