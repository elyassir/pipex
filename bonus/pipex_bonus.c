/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:14:47 by yel-mass          #+#    #+#             */
/*   Updated: 2022/12/28 16:40:46 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>

void	get_cmd_path(char **paths, char **av_2)
{
	char	*path;
	char	*tmp;

	if (access(av_2[0], F_OK | X_OK) == 0)
		return ;
	tmp = ft_strjoin("/", av_2[0]);
	free(av_2[0]);
	av_2[0] = tmp;
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, av_2[0]);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		paths++;
		free(path);
	}
	if (*paths == NULL)
	{
		write(2, "Command Not Found\n", 18);
		av_2[0] = NULL;
		return ;
	}
	free(av_2[0]);
	av_2[0] = path;
	return ;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] != '\0' && s2[i] != '\0' && s1[i] != s2[i])
		return (s2[i] - s1[i]);
	return (0);
}

char	**get_paths(char **envp, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->envp = envp;
	pipex->all_paths = NULL;
	pipex->cmd = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	while (envp[i] != NULL && ft_strcmp(envp[i], "PATH") != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

void	ft_open(t_pipex *pipex, char *name, int a)
{
	if (a == 1)
	{
		pipex->infile = open(name, O_RDONLY);
		if (pipex->infile < 0)
			write(2, "Error No such file or directory\n", 33);
	}
	else if (a == 2)
	{
		pipex->outfile = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (pipex->outfile < 0)
			error_and_exit("Error Open Outfile", pipex);
	}
}

void	ft_child_child(t_pipex *pipex, char **argv, int argc)
{
	int i = 2;
	while (++i < argc - 2) 
	{
		if (pipe(pipex->pipe2) == -1)
			error_and_exit("Pipe Error", pipex);
		pipex->cmd = ft_split(argv[i], ' ');
		get_cmd_path(pipex->all_paths, pipex->cmd);
		if (pipex->cmd != NULL && pipex->cmd[0] != NULL)
			get_cmd_child_2(pipex->cmd, pipex->pipe, pipex->pipe2, pipex);
		wait(NULL);
		*pipex->pipe = *pipex->pipe2;
		close(pipex->pipe2[1]);
		free(pipex->cmd[0]);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc >= 5)
	{
		pipex.all_paths = get_paths(envp, &pipex);
		if (pipe(pipex.pipe) == -1)
			error_and_exit("Pipe Error ", &pipex);
		ft_open(&pipex, argv[1], 1);
		pipex.cmd1 = ft_split(argv[2], ' ');
		get_cmd_path(pipex.all_paths, pipex.cmd1);
		if (pipex.cmd1 != NULL && pipex.cmd1[0] != NULL && !(pipex.infile < 0))
			get_cmd_child_1(pipex.cmd1, pipex.pipe, pipex.infile, &pipex);
		close(pipex.pipe[1]);
		wait(NULL);
		ft_child_child(&pipex, argv, argc);
		ft_open(&pipex, argv[argc - 1], 2);
		pipex.cmd2 = ft_split(argv[argc - 2], ' ');
		get_cmd_path(pipex.all_paths, pipex.cmd2);
		if (pipex.cmd2 != NULL && pipex.cmd2[0] != NULL && !(pipex.outfile < 0))
			get_cmd_child_3(pipex.cmd2, pipex.pipe, pipex.outfile, &pipex);
	}
	else
		write(2, "5 Args\n", 7);
	return (0);
}
