/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:12:02 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/22 21:27:15 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*ft_join(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*read_str(int fd, char *s)
{
	char	buf[2];
	int		n;

	while (1)
	{
		n = read(fd, buf, 1);
		if (n == -1)
			return (0);
		buf[n] = '\0';
		if (n == 0)
			break ;
		s = ft_join(s, buf);
		if (ft_strchr(s, '\n'))
			break ;
	}
	return (s);
}

char	*ft_find(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	i = -1;
	while (s[++i] && s[i] != '\n')
		str[i] = s[i];
	if (s[i] == '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_remainder(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!str)
		return (0);
	j = 0;
	while (s[i] && s[++i])
		str[j++] = s[i];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	line = 0;
	if (fd < 0)
		return (0);
	str = read_str(fd, str);
	if (!str)
		return (0);
	line = ft_find(str);
	str = ft_remainder(str);
	if (line && !line[0])
	{
		free(line);
		return (0);
	}
	return (line);
}
