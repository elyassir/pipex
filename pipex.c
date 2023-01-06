/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:14:47 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/05 12:38:10 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	my_strcmp(const char *s1, const char *s2)
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

void	ft_open(t_pipex *pipex, char *name, int a)
{
	if (a == 1)
	{
		pipex->infile = open(name, O_RDONLY);
		if (pipex->infile < 0)
			perror("Error");
	}
	else if (a == 2)
	{
		pipex->outfile = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (pipex->outfile < 0)
			error_and_exit("Error");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	pipex.envp = envp;
	pipex.argv = argv;
	if (argc == 5)
	{
		if (pipe(pipex.pipe) == -1)
			error_and_exit("Pipe Error");
		ft_open(&pipex, argv[1], 1);
		if (!(pipex.infile < 0))
			get_cmd_child_1(&pipex);
		close(pipex.pipe[1]);
		ft_open(&pipex, argv[4], 2);
		if (!(pipex.outfile < 0))
			get_cmd_child_2(&pipex);
		close(pipex.pipe[0]);
		wait(NULL);
		wait(NULL);
	}
	else
		write(2, "5 Args\n", 7);
	return (0);
}
