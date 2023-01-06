/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childer_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:28:29 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/05 12:43:40 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void	ft_free_all_(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	get_cmd_child_1(t_pipex *pipex)
{
	int	l;

	l = fork();
	if (l < 0)
		error_and_exit("Fork Error");
	if (l == 0)
	{
		pipex->cmd1 = ft_split(pipex->argv[2], ' ');
		if (pipex->cmd1 != NULL || access(pipex->cmd1[0], F_OK | X_OK) != 0)
		{
			pipex->all_paths = get_paths(pipex->envp);
			get_cmd_path(pipex->all_paths, pipex->cmd1);
			if (pipex->all_paths != NULL)
				ft_free_all_(pipex->all_paths);
		}
		dup2(pipex->pipe[1], STDOUT_FILENO);
		dup2(pipex->infile, STDIN_FILENO);
		execve(pipex->cmd1[0], pipex->cmd1, pipex->envp);
		error_and_exit("Command Not Found 3");
	}
}

void	get_cmd_child_2(t_pipex *pipex, int i)
{
	int	l;

	l = fork();
	if (l == 0)
	{
		pipex->cmd = ft_split(pipex->argv[i], ' ');
		if (pipex->cmd != NULL || access(pipex->cmd[0], F_OK | X_OK) != 0)
		{
			pipex->all_paths = get_paths(pipex->envp);
			get_cmd_path(pipex->all_paths, pipex->cmd);
			if (pipex->all_paths != NULL)
				ft_free_all_(pipex->all_paths);
		}
		dup2(pipex->pipe[0], 0);
		dup2(pipex->pipe2[1], 1);
		execve(pipex->cmd[0], pipex->cmd, pipex->envp);
		error_and_exit("Command Not Found 1");
	}
	if (l < 0)
		error_and_exit("Error ");
}

void	get_cmd_child_3(t_pipex *pipex)
{
	int	l;

	l = fork();
	if (l == 0)
	{
		pipex->cmd2 = ft_split(pipex->argv[pipex->argc - 2], ' ');
		if (pipex->cmd2 != NULL || access(pipex->cmd2[0], F_OK | X_OK) != 0)
		{
			pipex->all_paths = get_paths(pipex->envp);
			get_cmd_path(pipex->all_paths, pipex->cmd2);
			if (pipex->all_paths != NULL)
				ft_free_all_(pipex->all_paths);
		}
		dup2(pipex->pipe[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		execve(pipex->cmd2[0], pipex->cmd2, pipex->envp);
		error_and_exit("Command Not Found");
	}
	if (l < 0)
		error_and_exit("Error ");
}
