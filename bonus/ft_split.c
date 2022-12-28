#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	i = 0;
	while (s1[i])
		i++;
	str = malloc(i * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*d;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	if (!s)
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
static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (count);
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

static char	**free_all(char **s, int m)
{
	m--;
	while (m >= 0)
	{
		free(s[m]);
		m--;
	}
	free(s);
	return (NULL);
}

static void	get_len_word(char const *s, char c, int *index, int *len_word)
{
	while (s[*index] == c)
		*index += 1;
	while (s[*index + *len_word] != c && s[*index + *len_word])
		*len_word += 1;
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**words;
	int		m;
	int		index;
	int		len_word;

	count = count_words(s, c);
	words = malloc((count + 1) * sizeof(char *));
	index = 0;
	m = 0;
	if (!words)
		return (NULL);
	while (m < count)
	{
		len_word = 0;
		get_len_word(s, c, &index, &len_word);
		words[m] = ft_substr(s, index, len_word);
		if (!words[m++])
			return (free_all(words, m));
		index += len_word;
	}
	words[m] = 0;
	return (words);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;
	char	*new_string;

	i = -1;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_string = malloc((len_s1 + len_s2 + 1) * sizeof(char ));
	if (!new_string)
		return (NULL);
	while (++i < len_s1)
		new_string[i] = s1[i];
	while ((i + j) < (len_s1 + len_s2))
	{
		new_string[i + j] = s2[j];
		j++;
	}
	new_string[i + j] = '\0';
	return (new_string);
}