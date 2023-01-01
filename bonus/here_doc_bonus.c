/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 08:09:29 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/01 09:55:37 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_child_child(t_pipex *pipex, char **argv, int argc)
{
	int	i;

	i = 2;
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

void	ft_here_doc(t_pipex *pipex, char **argv, int argc, char **envp)
{
	pipex->all_paths = get_paths(envp, pipex);
	if (pipe(pipex->pipe) == -1)
		error_and_exit("Pipe Error ", pipex);
	pipex->infile = open("tmp_file", O_RDONLY);
	pipex->cmd1 = ft_split(argv[3], ' ');
	get_cmd_path(pipex->all_paths, pipex->cmd1);
	if (pipex->cmd1 != NULL && pipex->cmd1[0] != NULL && !(pipex->infile < 0))
		get_cmd_child_1(pipex->cmd1, pipex->pipe, pipex->infile, pipex);
	close(pipex->pipe[1]);
	wait(NULL);
	ft_child_child(pipex, argv, argc);
	ft_open(pipex, argv[argc - 1], 2);
	pipex->cmd2 = ft_split(argv[argc - 2], ' ');
	get_cmd_path(pipex->all_paths, pipex->cmd2);
	if (pipex->cmd2 != NULL && pipex->cmd2[0] != NULL && !(pipex->outfile < 0))
		get_cmd_child_3(pipex->cmd2, pipex->pipe, pipex->outfile, pipex);
}

void	here_doc(int argc, char **argv, char **envp, t_pipex *pipex)
{
	char	*line;
	int		tmp;

	line = "";
	tmp = open("tmp_file", O_WRONLY | O_CREAT, 0644);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, argv[2]) == 0)
		{
			free(line);
			break ;
		}
		write(tmp, line, ft_strlen(line));
		free(line);
	}
	close(tmp);
	ft_here_doc(pipex, argv, argc, envp);
	exit(0);
}
