/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:28:29 by yel-mass          #+#    #+#             */
/*   Updated: 2022/12/28 14:28:35 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd_child_1(char **cmd, int *fd, int infile)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	execve(cmd[0], cmd, NULL);
}

void	get_cmd_child_2(char **cmd, int *fd, int outfile)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	execve(cmd[0], cmd, NULL);
}
