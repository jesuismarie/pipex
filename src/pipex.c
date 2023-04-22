/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:28:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/22 20:38:18 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	children(t_pipex data, char **cmd, int **fds, int i)
{
	if (i == 2)
	{
		if (dup2(data.fd1, STDIN_FILENO) == -1)
			err();
		if (dup2(fds[i - 2][1], STDOUT_FILENO) == -1)
			err();
	}
	else if (i == data.ac - 2)
	{
		if (dup2(fds[i - 3][0], STDIN_FILENO) == -1)
			err();
		if (dup2(data.fd2, STDOUT_FILENO) == -1)
			err();
	}
	else
	{
		if (dup2(fds[i - 3][0], STDIN_FILENO) == -1)
			err();
		if (dup2(fds[i - 2][1], STDOUT_FILENO) == -1)
			err();
	}
	close_fds(data, fds);
	execve(*cmd, cmd, data.ep);
	err();
}

void	pxik(t_pipex data, int **fds, int i)
{
	pid_t	id;
	char	**cmd;

	cmd = ft_split(data.av[i], ' ');
	if (!cmd)
		err();
	if (cmd[0] && !ft_strchr(cmd[0], '/'))
		*cmd = find_cmd(data, cmd);
	id = fork();
	if (!id)
		children(data, cmd, fds, i);
	free_malloc(cmd);
}

void	pipex(t_pipex data)
{
	int		i;
	int		**fds;

	i = -1;
	fds = malloc(sizeof(int *) * (data.ac - 4));
	while (++i < data.ac - 4)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (pipe(fds[i]) == -1)
			err();
	}
	i = 1;
	while (++i < data.ac - 1)
		pxik(data, fds, i);
	close_fds(data, fds);
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
	if (argc > 5 && !ft_strcmp(argv[1], "here_doc"))
		pipex_heredoc(data);
	else
		pipex(data);
	while (wait(NULL) != -1)
		;
}
