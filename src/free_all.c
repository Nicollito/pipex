/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:20:53 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/25 10:33:02 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_utils *utils)
{
	if (utils->path1)
		free(utils->path1);
	if (utils->path2)
		free(utils->path2);
	if (utils->args1)
		free_matrix(utils->args1);
	if (utils->args2)
		free_matrix(utils->args2);
	if (utils->which_args1)
		free_matrix(utils->which_args1);
	if (utils->which_args2)
		free_matrix(utils->which_args2);
}

void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}
