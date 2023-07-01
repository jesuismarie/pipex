/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:28:24 by mnazarya          #+#    #+#             */
/*   Updated: 2023/07/01 18:23:02 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	**pipe_fds(t_pipex data)
{
	int	i;
	int	**fds;

	i = -1;
	fds = malloc(sizeof(int *) * (data.ac - 4));
	if (!fds)
		error();
	while (++i < data.ac - 4)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			error();
		if (pipe(fds[i]) == -1)
			pipe_error(fds, i);
	}
	return (fds);
}

static void	children(t_pipex data, int **fds, int i)
{
	if (i == 2)
	{
		if (dup2(data.fd1, STDIN_FILENO) == -1)
			err(data, fds);
		if (dup2(fds[i - 2][1], STDOUT_FILENO) == -1)
			err(data, fds);
	}
	else if (i == data.ac - 2)
	{
		if (dup2(fds[i - 3][0], STDIN_FILENO) == -1)
			err(data, fds);
		if (dup2(data.fd2, STDOUT_FILENO) == -1)
			err(data, fds);
	}
	else
	{
		if (dup2(fds[i - 3][0], STDIN_FILENO) == -1)
			err(data, fds);
		if (dup2(fds[i - 2][1], STDOUT_FILENO) == -1)
			err(data, fds);
	}
	close_fds(data, fds);
	close(data.fd1);
	close(data.fd2);
	free_malloc(data.path);
}

static void	pxik(t_pipex data, int **fds, int i)
{
	pid_t	id;
	char	**cmd;

	cmd = ft_split(data.av[i], ' ');
	if (!cmd)
		err(data, fds);
	if (cmd[0] && !ft_strchr(cmd[0], '/'))
		*cmd = find_cmd(data, cmd);
	id = fork();
	if (id == -1)
		err(data, fds);
	if (!id)
	{
		children(data, fds, i);
		execve(*cmd, cmd, data.ep);
		error();
	}
	free_malloc(cmd);
}

void	pipex(t_pipex data)
{
	int		i;
	int		**fds;

	fds = pipe_fds(data);
	i = 1;
	while (++i < data.ac - 1)
		pxik(data, fds, i);
	close_fds(data, fds);
	close(data.fd1);
	close(data.fd2);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
		return (0);
	data.ac = argc;
	data.av = argv;
	data.ep = envp;
	data.path = path_find(envp);
	if (!data.path)
		return (1);
	if (argc > 5 && !ft_strcmp(argv[1], "here_doc"))
	{
		data.fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		pipex_heredoc(data);
	}
	else
	{
		data.fd1 = open(argv[1], O_RDONLY);
		data.fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		pipex(data);
	}
	while (wait(NULL) != -1)
		;
	free_malloc(data.path);
	return (0);
}
