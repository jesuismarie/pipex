/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:28:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/21 19:33:18 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	children(t_pipex data, char **cmd)
{
	dup2(data.fd1, 0);
	
	execve(*cmd, cmd, data.ep);
}

void	pipex(t_pipex data)
{
	int		i;
	pid_t	id;
	char	**cmd;

	i = 2;
	while (i < data.ac - 1)
	{
		cmd = ft_split(data.av[i], ' ');
		if (!cmd)
		{
			perror("Error🐙");
			exit(1);
		}
		if (cmd[0] && !ft_strchr(cmd[0], '/'))
			*cmd = find_cmd(data, cmd);
		id = fork();
		if (!id)
		{
			children(data, cmd);
		}
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
