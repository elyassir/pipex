/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:32:42 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/01 09:23:47 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "get_next_line.h"

char	*get_next_line(int fd);

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**all_paths;
	char	*path;
	char	**cmd1;
	char	**cmd2;
	char	**cmd;
	char	**envp;
	int		pipe[2];
	int		pipe2[2];
}t_pipex;

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	get_cmd_child_1(char **cmd, int *fd, int infile, t_pipex *pipex);
void	get_cmd_child_2(char **cmd, int *fd, int *fd2, t_pipex *pipex);
void	get_cmd_child_3(char **cmd, int *fd, int outfile, t_pipex *pipex);
//int		ft_strlen(char *s);
void	error_and_exit(char *str, t_pipex *pipex);
//char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	free_all_(t_pipex *pipex);
int		ft_strcmp(char *s1, char *s2);
void	here_doc(int argc, char **argv, char **envp, t_pipex *pipex);
char	**get_paths(char **envp, t_pipex *pipex);
void	get_cmd_path(char **paths, char **av_2);
void	ft_open(t_pipex *pipex, char *name, int a);
void	ft_free_all_(char **strs);

#endif