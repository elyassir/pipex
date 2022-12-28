/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:14:47 by yel-mass          #+#    #+#             */
/*   Updated: 2022/12/28 14:21:53 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	get_cmd_path(char **paths, char **av_2)
{
	char	*path;
	char	*tmp;

	if (access(av_2[0], F_OK | X_OK) == 0)
		return ;
	tmp = ft_strjoin("/", av_2[0], 1);
	free(av_2[0]);
	av_2[0] = tmp;
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, av_2[0], 0);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (b[i] != '\0' && a[i] != '\0' && b[i] == a[i])
		i++;
	if (b[i] != '\0' && a[i] != '\0' && b[i] != a[i])
		return (a[i] - b[i]);
	return (0);
}

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strcmp(envp[i], "PATH") != 0)
		i++;
	return (ft_split(&envp[i] + 5, ':'));
}

void	ft_open(t_pipex *pipex, char *name, int a)
{
	if (a == 1)
	{
		pipex->infile = open(name, O_RDONLY);
		if (pipex->infile < 0)
			write(2, "infile: No such file or directory\n", 35);
	}
	else if (a == 2)
	{
		pipex->outfile = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (pipex->outfile < 0)
			error_and_exit("Error Open Outfile");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.all_paths = get_paths(envp);
		pipe(pipex.pipe);
		ft_open(&pipex, argv[1], 1);
		pipex.cmd1 = ft_split(argv[2], ' ');
		get_cmd_path(pipex.all_paths, pipex.cmd1);
		if (pipex.cmd1[0] != NULL && !(pipex.infile < 0) && fork() == 0)
			get_cmd_child_1(pipex.cmd1, pipex.pipe, pipex.infile);
		close(pipex.pipe[1]);
		wait(NULL);
		ft_open(&pipex, argv[4], 2);
		pipex.cmd2 = ft_split(argv[3], ' ');
		get_cmd_path(pipex.all_paths, pipex.cmd2);
		if (pipex.cmd2[0] != NULL && !(pipex.outfile < 0) && fork() == 0)
			get_cmd_child_2(pipex.cmd2, pipex.pipe, pipex.outfile);
		close(pipex.pipe[0]);
		wait(NULL);
	}
	else
		write(2, "5 Args\n", 7);
	return (0);
}
