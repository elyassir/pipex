/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:32:42 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/06 13:53:58 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/wait.h>
# include "get_next_line.h"

char	*get_next_line(int fd);

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		argc;
	char	**all_paths;
	char	*path;
	char	**cmd1;
	char	**cmd2;
	char	**cmd;
	char	**envp;
	char	**argv;
	int		pipe[2];
	int		pipe2[2];
}t_pipex;

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	get_cmd_child_1(t_pipex *pipex);
void	get_cmd_child_2(t_pipex *pipex, int i);
void	get_cmd_child_3(t_pipex *pipex);
void	error_and_exit(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	free_all_(t_pipex *pipex);
int		ft_strcmp(char *s1, char *s2);
char	**get_paths(char **envp);
void	get_cmd_path(char **paths, char **av_2);
void	ft_open(t_pipex *pipex, int a, char **argv, int argc);
void	ft_free_all_(char **strs);
void	ft_child_child(t_pipex *pipex);

#endif