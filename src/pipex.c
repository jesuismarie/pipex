/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:28:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/19 20:46:47 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*path_find(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp, "PATH=", 5))
			return (ft_strchr(envp[i], '='));
		i++;
	}
	return (0);
}

void	grimiban(int argc, char **argv, char **path, int fd)
{
	int		i;
	char	**str;

	i = 2;
	while (i < argc - 1)
	{
		str = ft_split(argv[i], ' ');
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd1;
	int		fd2;
	char	**path;

	if (argc < 5)
		return (0);
	path = ft_split(path_find(envp), ':');
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

}
