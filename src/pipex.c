/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:28:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/20 20:41:59 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*path_find(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_strchr(envp[i], '/'));
		i++;
	}
	return (0);
}

void	pipex(t_pipex data)
{
	int		i;
	pid_t	;
	char	**cmd;

	i = 2;
	while (i < data.ac - 1)
	{
		cmd = ft_split(data.av[i], ' ');
		if (!cmd)
			exit(1);
		if (cmd[0] || ft_strchr(cmd[0], '/'))
		{
			;
		}
		
		// execve;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	char	**path;

	if (argc < 5)
		return (0);
	data.path = ft_split(path_find(envp), ':');
	int i = -1;
	while (data.path[++i])
		printf ("%s\n", data.path[i]);
	data.fd1 = open(argv[1], O_RDONLY);
	data.fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex(data);
}
