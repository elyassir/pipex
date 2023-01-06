/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:28:29 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/05 12:47:17 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd_path(char **paths, char **command)
{
	char	*path;
	char	*tmp;

	if (command == NULL || paths == NULL)
		return ;
	while (*paths != NULL)
	{
		tmp = ft_strjoin(*paths, "/");
		path = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(command[0]);
			command[0] = path;
			return ;
		}
		paths++;
		free(path);
	}
}

void	ft_free_all_(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && my_strcmp(envp[i], "PATH") != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

void	get_cmd_child_1(t_pipex *pipex)
{
	int	l;

	l = fork();
	if (l == 0)
	{
		pipex->cmd1 = ft_split(pipex->argv[2], ' ');
		if (access(pipex->cmd1[0], F_OK | X_OK) != 0)
		{
			pipex->all_paths = get_paths(pipex->envp);
			get_cmd_path(pipex->all_paths, pipex->cmd1);
			if (pipex->all_paths != NULL)
				ft_free_all_(pipex->all_paths);
		}
		dup2(pipex->pipe[1], STDOUT_FILENO);
		dup2(pipex->infile, STDIN_FILENO);
		execve(pipex->cmd1[0], pipex->cmd1, pipex->envp);
		error_and_exit("Command Not Found");
	}
	if (l < 0)
		error_and_exit("fork Error");
}

void	get_cmd_child_2(t_pipex *pipex)
{
	int	l;

	l = fork();
	if (l == 0)
	{
		pipex->cmd2 = ft_split(pipex->argv[3], ' ');
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
		error_and_exit("fork Error");
}
