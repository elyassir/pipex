/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:34:19 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/04 20:10:13 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void	error_and_exit(char *str)
{
	perror(str);
	exit(1);
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

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strcmp(envp[i], "PATH") != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}
