/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:34:19 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/01 08:36:40 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_and_exit(char *str, t_pipex *pipex)
{
	write(1, str, ft_strlen(str));
	free_all_(pipex);
	exit(1);
}

// int	ft_strlen(char *s)
// {
// 	int	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	return (len);
// }

// char	*ft_strdup(char *s1)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while (s1[i])
// 		i++;
// 	str = malloc(i * sizeof(char) + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char			*d;
// 	size_t			i;
// 	unsigned int	s_len;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (s_len <= start)
// 		return (ft_strdup(""));
// 	while (i < len && i + start < s_len)
// 		i++;
// 	d = malloc((i + 1) * sizeof(char ));
// 	if (!d)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && i + start < s_len)
// 	{
// 		d[i] = s[start + i];
// 		i++;
// 	}
// 	d[i] = '\0';
// 	return (d);
// }

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
