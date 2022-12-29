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

void	ft_free_all_(char **strs)
{
	while (*strs != NULL)
	{
		free(*strs);
		strs++;
	}
	free(strs);
}
void	free_all_(t_pipex *pipex, int i)
{
	if (i == 2)
		ft_free_all_(pipex->cmd2);
	if (pipex->cmd1 != NULL)
		ft_free_all_(pipex->cmd1);
}

void	get_cmd_child_1(char **cmd, int *fd, int infile, t_pipex *pipex)
{
	int l;
	l = fork();
	if (l == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		execve(cmd[0], cmd, pipex->envp);
		free_all_(pipex, 1);
		error_and_exit("execve Error");
	}
	if (l < 0)
	{
		free_all_(pipex, 1);
		error_and_exit("fork Error");
	}
}

void	get_cmd_child_2(char **cmd, int *fd, int outfile, t_pipex *pipex)
{
	int l;

	l = fork();
	if (l == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		execve(cmd[0], cmd, pipex->envp);
		free_all_(pipex, 2);
		error_and_exit("execve Error");
	}
	if (l < 0)
	{
		free_all_(pipex, 2);
		error_and_exit("fork Error");
	}
}
