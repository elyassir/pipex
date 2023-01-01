/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:03:54 by yel-mass          #+#    #+#             */
/*   Updated: 2023/01/01 08:54:39 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_strlen(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

int	ft_strchr(char *s, char c)
{
	int		i;

	i = -1;
	if (s != NULL)
		while (s[++i])
			if (s[i] == c)
				return (i);
	return (-1);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*d;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	if (!s || !len)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	while (i < len && i + start < s_len)
		i++;
	d = malloc((i + 1) * sizeof(char ));
	if (!d)
		return (NULL);
	i = 0;
	while (i < len && i + start < s_len)
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_string;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	new_string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char ));
	if (!new_string)
		return (NULL);
	while (s1[++i])
		new_string[i] = s1[i];
	while (s2[++j])
		new_string[i++] = s2[j];
	new_string[i] = '\0';
	free(s1);
	return (new_string);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1 || !s1[0])
		return (NULL);
	while (s1[i])
		i++;
	str = malloc(i * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = s1[i];
	return (str);
}
