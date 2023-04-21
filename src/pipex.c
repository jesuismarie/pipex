/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:28:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/21 17:18:10 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_malloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

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

int	find_cmd(t_pipex data, char **cmd)
{
	char	*s;
	char	*tmp;
	int		i;

	i = -1;
	s = ft_strjoin("/", *cmd);
	while (data.path[++i])
	{
		tmp = ft_strjoin(data.path[i], s);
		
		printf("%s\n", tmp);
	}
	return (0);
}

void	pipex(t_pipex data)
{
	int		i;
	// pid_t	id;
	char	**cmd;

	i = 2;
	while (i < data.ac - 1)
	{
		cmd = ft_split(data.av[i], ' ');
		if (!cmd)
			exit(1);
		if (cmd[0] || ft_strchr(cmd[0], '/'))
		{
			printf("-----------\n");
			find_cmd(data, cmd);
		}
		else
		{
			// execve;
		}
		// id = fork();
		// if (!id)
		free_malloc(cmd);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
		return (0);
	data.ac = argc;
	data.av = argv;
	data.ep = envp;
	data.path = ft_split(path_find(envp), ':');
	data.fd1 = open(argv[1], O_RDONLY);
	data.fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex(data);
}
