/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:14:47 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/06 13:53:37 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include <stdio.h>

void	get_cmd_path(char **paths, char **command)
{
	char	*path;
	char	*tmp;

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
			free(path);
			command[0] = path;
			return ;
		}
		paths++;
		free(path);
	}
	free(tmp);
	return ;
}

void	ft_open(t_pipex *pipex, int a, char **argv, int argc)
{
	if (a == 1)
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			perror("Error");
	}
	else if (a == 2)
	{
		pipex->outfile = open(argv[argc - 1], O_CREAT | \
		O_TRUNC | O_WRONLY, 0666);
		if (pipex->outfile < 0)
			error_and_exit("Error Open Outfile");
	}
}

void	ft_child_child(t_pipex *pipex)
{
	int	i;

	i = 2;
	while (++i < pipex->argc - 2)
	{
		if (pipe(pipex->pipe2) == -1)
			error_and_exit("Pipe Error");
		get_cmd_child_2(pipex, i);
		wait(NULL);
		close(pipex->pipe[0]);
		*pipex->pipe = *pipex->pipe2;
		close(pipex->pipe2[1]);
	}
}

void	ft_init(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->envp = envp;
	pipex->argv = argv;
	pipex->argc = argc;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	ft_init(argc, argv, envp, &pipex);
	if (argc >= 5)
	{
		if (pipe(pipex.pipe) == -1)
			error_and_exit("Pipe Error ");
		ft_open(&pipex, 1, argv, argc);
		if (!(pipex.infile < 0))
			get_cmd_child_1(&pipex);
		close(pipex.pipe[1]);
		ft_child_child(&pipex);
		ft_open(&pipex, 2, argv, argc);
		get_cmd_child_3(&pipex);
		close(pipex.pipe[0]);
		while (wait(NULL) != -1)
		{
		}
	}
	else
		write(2, "5 Args\n", 7);
	return (0);
}
