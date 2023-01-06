/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:32:42 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/04 12:13:53 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**all_paths;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	**argv;
	int		pipe[2];
}t_pipex;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	get_cmd_child_1(t_pipex *pipex);
void	get_cmd_child_2(t_pipex *pipex);
int		ft_strlen(const char *s);
void	error_and_exit(char *str);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		my_strcmp(const char *s1, const char *s2);

#endif
