/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:28:29 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 13:10:28 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

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
void	get_cmd_path(char **paths, char **command)
{
	char	*path;
	char	*tmp;
	char	**tmp2 = paths;

	if (command == NULL || paths == NULL)
		return ;
	tmp = ft_strjoin("/", command[0]);
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(tmp);
			free(command[0]);
			command[0] = path;
			return ;
		}
		paths++;
		free(path);
	}
	free(tmp);
	ft_free_all_(tmp2);
	write(2, "Command Not Found\n", 18);
	exit(127);
	return ;
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
		close(pipex->pipe[0]); // close to pass this test : ./pipex /dev/stdin cat ls /dev/stdout
		dup2(pipex->infile, STDIN_FILENO);
		execve(pipex->cmd1[0], pipex->cmd1, pipex->envp);
		perror(pipex->cmd1[0]);
		exit(127);
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
			if (pipex->all_paths != NULL)
			{
				get_cmd_path(pipex->all_paths, pipex->cmd2);
			}
		}
		dup2(pipex->pipe[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		execve(pipex->cmd2[0], pipex->cmd2, pipex->envp);
		perror(pipex->cmd2[0]);
		exit(127);
	}
	if (l < 0)
		error_and_exit("fork Error");
}
