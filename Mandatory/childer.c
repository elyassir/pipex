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
	int i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	free_all_(t_pipex *pipex)
{
	if (pipex->cmd2 != NULL)
		ft_free_all_(pipex->cmd2);
	if (pipex->cmd1 != NULL)
		ft_free_all_(pipex->cmd1);
	if (pipex->all_paths != NULL)
		ft_free_all_(pipex->all_paths);
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
		error_and_exit("execve Error", pipex);
	}
	if (l < 0)
		error_and_exit("fork Error", pipex);
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
		error_and_exit("execve Error", pipex);
	}
	if (l < 0)
		error_and_exit("fork Error", pipex);
}
