/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:32:42 by yel-mass          #+#    #+#             */
/*   Updated: 2022/12/28 16:33:11 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**all_paths;
	char	*path;
	char	**cmd1;
	char	**cmd2;
	char	**cmd;
	int		pipe[2];
	int		pipe2[2];
}t_pipex;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	get_cmd_child_1(char **cmd, int *fd, int infile);
void	get_cmd_child_2(char **cmd, int *fd, int *fd2);
void	get_cmd_child_3(char **cmd, int *fd, int outfile);
int		ft_strlen(const char *s);
void	error_and_exit(char *str);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_parent(t_pipex *pipex);

#endif