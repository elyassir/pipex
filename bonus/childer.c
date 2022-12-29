/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:28:29 by yel-mass          #+#    #+#             */
/*   Updated: 2022/12/28 16:34:14 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd_child_1(char **cmd, int *fd, int infile)
{
	int k;
	int l;
	
	l = fork();
	if (l < 0)
	{
		error_and_exit("Fork Error");
	}
	if (l == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		k = execve(cmd[0], cmd, NULL);
		if (k < 0)
		{
			error_and_exit("execve Error");
		}
	}
}

void	get_cmd_child_2(char **cmd, int *fd, int *fd2)
{
	int k;
	int l;
	
	l = fork();

	if (l == 0)
	{
		dup2(fd[0], 0);
		dup2(fd2[1], 1);
		k = execve(cmd[0], cmd, NULL);
	}
	if (l < 0)
	// free_parent();
	error_and_exit("execve Error");
}

void	get_cmd_child_3(char **cmd, int *fd, int outfile)
{
	int k;
	int l;
	
	l = fork();
	if (l < 0)
	{
		error_and_exit("Fork Error");
	}
	if (l == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		k = execve(cmd[0], cmd, NULL);
		if (k < 0)
		{
			error_and_exit("execve Error");
		}
	}
}
